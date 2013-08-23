// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QApplication>
#include <QWheelEvent>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

#include <qlayout/qlayoutscene.h>
#include <qlayout/qlayoutview.h>

#include <copasi.h>
#include <layout/CLayout.h>
#include <layout/CListOfLayouts.h>
#include <layout/CLDefaultStyles.h>
#include <CopasiDataModel/CCopasiDataModel.h>
#include <resourcesUI/CQIconResource.h>

QLayoutView::~QLayoutView()
{
}

void updateLayoutList(QComboBox* list, CCopasiDataModel* dataModel)
{
  if (list == NULL || dataModel == NULL) return;

  list->clear();
  CCopasiVector<CLayout> & layouts = *dataModel->getListOfLayouts();
  CCopasiVector<CLayout>::iterator it = layouts.begin();

  while (it != layouts.end())
    {
      const CLayout* layout = *it;
      list->addItem(layout->getObjectName().c_str());
      ++it;
    }
}

#define RENDERINFORMATION_TYPE_GLOBAL 0
#define RENDERINFORMATION_TYPE_LOCAL 1
#define RENDERINFORMATION_TYPE_DEFAULT 2

CLRenderInformationBase* updateRenderInformationList(QComboBox* list, CCopasiDataModel* dataModel, CLayout* layout)
{

  if (list == NULL || dataModel == NULL) return NULL;

  bool skipGlobal = list->count() > 0;
  CLRenderInformationBase* result = NULL;

  // remove oldItems
  if (skipGlobal)
    {
      for (size_t i = list->count(); i > 0; --i)
        {
          QString current = list->itemText(i - 1);
          int type = list->itemData(i - 1).toInt();

          if (type == RENDERINFORMATION_TYPE_LOCAL)
            list->removeItem(i - 1);
        }
    }

  // add local information
  if (layout != NULL)
    {
      CCopasiVector<CLLocalRenderInformation> & render = layout->getListOfLocalRenderInformationObjects();
      CCopasiVector<CLLocalRenderInformation>::iterator it = render.begin();

      while (it != render.end())
        {
          CLLocalRenderInformation* current = *it;

          if (result == NULL) result = current;

          if (current->getName().empty())
            list->insertItem(0, current->getKey().c_str(), QVariant::fromValue(RENDERINFORMATION_TYPE_LOCAL));
          else
            list->insertItem(0, current->getName().c_str(), QVariant::fromValue(RENDERINFORMATION_TYPE_LOCAL));

          ++it;
        }
    }

  // bail
  if (skipGlobal)
    {
      if (result == NULL && dataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size() > 0)
        result = dataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects()[0];

      if (result == NULL && getNumDefaultStyles() > 0)
        result = getDefaultStyle(0);

      return result;
    }

  // add global ones
  {
    CCopasiVector<CLGlobalRenderInformation> & render = dataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects();
    CCopasiVector<CLGlobalRenderInformation>::const_iterator it = render.begin();

    while (it != render.end())
      {
        CLGlobalRenderInformation* current = *it;

        if (result == NULL) result = current;

        if (current->getName().empty())
          list->addItem(current->getKey().c_str(), QVariant::fromValue(RENDERINFORMATION_TYPE_GLOBAL));
        else
          list->addItem(current->getName().c_str(), QVariant::fromValue(RENDERINFORMATION_TYPE_GLOBAL));

        ++it;
      }

    // add default ones
    {
      size_t i, iMax = getNumDefaultStyles();
      CLRenderInformationBase* current = NULL;

      for (i = 0; i < iMax; ++i)
        {
          current = getDefaultStyle(i);

          if (result == NULL) result = current;

          std::string text = current->getKey();

          if (!current->getName().empty())
            {
              text = current->getName();
            }

          list->addItem(text.c_str(), QVariant::fromValue(RENDERINFORMATION_TYPE_DEFAULT));
        }
    }
  }

  return result;
}

void QLayoutView::slotRenderInformationChanged(int index)
{
  if (mIgnoreEvents || index < 0) return;

  if (mpDataModel == NULL) return;

  QLayoutScene* current = dynamic_cast<QLayoutScene*>(scene());

  if (current == NULL || current->getCurrentLayout() == NULL) return;

  CLRenderInformationBase* render  = NULL;
  int numLocal = current->getCurrentLayout()->getListOfLocalRenderInformationObjects().size();

  if (numLocal > index)
    {
      render  = current->getCurrentLayout()->getListOfLocalRenderInformationObjects()[index];
    }

  int numGlobal = mpDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size();

  if (render == NULL && numLocal + numGlobal > index)
    {
      render = mpDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects()[index - numLocal];
    }

  size_t numDefault = getNumDefaultStyles();

  if (render == NULL && numLocal + numGlobal + numDefault > (size_t)index)
    {
      render = getDefaultStyle(index - numGlobal - numLocal);
    }

  if (render == NULL)
    return;

  current->setRenderInformation(mpDataModel, render);
  current->recreate();
}

void QLayoutView::slotLayoutChanged(int index)
{
  if (mIgnoreEvents || index < 0) return;

  if (mpDataModel == NULL) return;

  QLayoutScene* current = dynamic_cast<QLayoutScene*>(scene());

  if (current == NULL) return;

  CLayout* layout  = (*mpDataModel->getListOfLayouts())[index];

  if (layout == NULL || layout == current->getCurrentLayout()) return;

  mIgnoreEvents = true;
  // update the corresponding render information list
  CLRenderInformationBase* render = updateRenderInformationList(mpRenderDropdown, mpDataModel, layout);

  if (render != NULL)
    {
      if (render->getName().empty())
        mpRenderDropdown->setCurrentIndex(mpRenderDropdown->findText(render->getKey().c_str()));
      else
        mpRenderDropdown->setCurrentIndex(mpRenderDropdown->findText(render->getName().c_str()));
    }

  mIgnoreEvents  = false;
  current->setLayout(layout, mpDataModel, render);
  current->recreate();
}

QLayoutView::QLayoutView(QWidget*parent)
  : QGraphicsView(parent)
  , mScaleFactor(1.15)
  , mIgnoreEvents(false)
{
  setDragMode(QGraphicsView::ScrollHandDrag);
  createActions();
}

void QLayoutView::slotSaveToFile(const QString& fileName)
{
  QLayoutScene* layoutScene =  dynamic_cast<QLayoutScene*>(scene());

  if (layoutScene == NULL) return;

  layoutScene->saveToFile(
    fileName.toStdString(),
    QFileInfo(fileName).suffix().toStdString()
  );
}

QLayoutView::QLayoutView(QLayoutScene *scene)
  : QGraphicsView(scene)
  , mScaleFactor(1.15)
  , mIgnoreEvents(false)

{
  setDragMode(QGraphicsView::ScrollHandDrag);
  createActions();
}

void QLayoutView::fillZoomMenu(QMenu* menu)
{
  if (menu == NULL) return;

  menu->addAction(mpActFitOnScreen);
  menu->addAction(mpActZoomIn);
  menu->addAction(mpActZoomOut);
  menu->addAction(mpActResetZoom);
}

void QLayoutView::fillZoomTooBar(QToolBar* toolBar)
{
  if (toolBar == NULL) return;

  toolBar->addAction(mpActFitOnScreen);
  toolBar->addAction(mpActZoomIn);
  toolBar->addAction(mpActZoomOut);
  toolBar->addAction(mpActResetZoom);
}

void QLayoutView::createActions()
{
  mpActFitOnScreen = new QAction(tr("Fit On Screen"), this);
  mpActFitOnScreen->setShortcut(QKeySequence::fromString("F5"));
  mpActFitOnScreen->setIcon(CQIconResource::icon(CQIconResource::viewmagfit));
  connect(mpActFitOnScreen, SIGNAL(triggered()), this, SLOT(slotFitOnScreen()));
  addAction(mpActFitOnScreen);

  mpActResetZoom = new QAction(tr("Reset Zoom"), this);
  mpActResetZoom->setIcon(CQIconResource::icon(CQIconResource::viewmag1));
  connect(mpActResetZoom, SIGNAL(triggered()), this, SLOT(slotResetZoom()));
  addAction(mpActResetZoom);

  mpActZoomIn = new QAction(tr("Zoom In"), this);
  mpActZoomIn->setIcon(CQIconResource::icon(CQIconResource::viewmagPlus));
  mpActZoomIn->setShortcut(QKeySequence::ZoomIn);
  connect(mpActZoomIn, SIGNAL(triggered()), this, SLOT(slotZoomIn()));
  addAction(mpActZoomIn);

  mpActZoomOut = new QAction(tr("Zoom Out"), this);
  mpActZoomOut->setIcon(CQIconResource::icon(CQIconResource::viewmagMinus));
  mpActZoomOut->setShortcut(QKeySequence::ZoomOut);
  connect(mpActZoomOut, SIGNAL(triggered()), this, SLOT(slotZoomOut()));
  addAction(mpActZoomOut);

  mpLayoutDropdown = new QComboBox;
  mpLayoutDropdown->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

  mpRenderDropdown = new QComboBox;
  mpRenderDropdown->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

  connect(mpLayoutDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLayoutChanged(int)));
  connect(mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInformationChanged(int)));

  setInteractive(true);
  setRenderHints(QPainter::Antialiasing);
}

void QLayoutView::fillSelectionToolBar(QToolBar* toolBar)
{
  QFrame* pFrame1 = new QFrame;
  QHBoxLayout* pLayout = new QHBoxLayout;
  pLayout->setSpacing(3);
  pFrame1->setLayout(pLayout);
  QLabel* pLabel = new QLabel(tr("Layout:"));
  pLayout->addWidget(pLabel);
  pLayout->addWidget(mpLayoutDropdown);

  QFrame* pFrame2 = new QFrame;
  pLayout = new QHBoxLayout;
  pLayout->setSpacing(3);
  pFrame2->setLayout(pLayout);
  QLabel* mpRenderLabel = new QLabel(tr("Render Information:"));
  pLayout->addWidget(mpRenderLabel);
  pLayout->addWidget(mpRenderDropdown);

  toolBar->addWidget(pFrame1);
  toolBar->addWidget(pFrame2);
}

void QLayoutView::slotFitOnScreen()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
  update();
}
void QLayoutView::slotResetZoom()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  resetMatrix();
  ensureVisible(scene()->itemsBoundingRect());
  update();
}
void QLayoutView::slotZoomIn()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  scale(mScaleFactor, mScaleFactor);
}
void QLayoutView::slotZoomOut()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  scale(1.0 / mScaleFactor, 1.0 / mScaleFactor);
}

CCopasiDataModel* QLayoutView::getDataModel()
{
  return mpDataModel;
}

void QLayoutView::setDataModel(CCopasiDataModel* dataModel, CLayout* layout)
{
  mpDataModel = dataModel;

  updateLayoutList(mpLayoutDropdown, dataModel);

  if (layout != NULL)
    mpLayoutDropdown->setCurrentIndex(mpLayoutDropdown->findText(layout->getObjectName().c_str()));

  updateRenderInformationList(mpRenderDropdown, dataModel, layout);
}

void QLayoutView::wheelEvent(QWheelEvent* event)
{
  if (QApplication::keyboardModifiers() == Qt::ControlModifier ||
      QApplication::keyboardModifiers() == Qt::MetaModifier ||
      QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
      if (event->delta() > 0)
        {
          // Zoom in
          slotZoomIn();
        }
      else
        {
          // Zooming out
          slotZoomOut();
        }
    }
  else
    {
      QGraphicsView::wheelEvent(event);
    }
}
