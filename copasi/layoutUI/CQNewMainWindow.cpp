// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQNewMainWindow.cpp,v $
//   $Revision: 1.1.2.20 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/10/21 06:26:19 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// SBML includes
#include <copasi/CopasiDataModel/CCopasiDataModel.h>
#include <copasi/model/CModel.h>
#include <copasi/layout/CLayout.h>
#include <copasi/layout/CListOfLayouts.h>
#ifdef COPASI_DEBUG
#include <copasi/elementaryFluxModes/CEFMTask.h>
#include <copasi/elementaryFluxModes/CEFMProblem.h>
#include <copasi/elementaryFluxModes/CFluxMode.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CChemEq.h>
#include <copasi/model/CChemEqElement.h>
#include <copasi/model/CMetab.h>
#endif // COPASI_DEBUG

// local includes
#include "CQGLLayoutPainter.h"
#include "CQGLLayoutViewer.h"
#include "CQNewMainWindow.h"
#include "CQPlayerControlWidget.h"
#include "CQScreenshotOptionsDialog.h"

// Qt includes
#include <QAction>
#include <QActionGroup>
#include <QCloseEvent>
#include <QColor>
#include <QColorDialog>
#include <QComboBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QIcon>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QMenuBar>
#include <QMessageBox>
#include <QStackedWidget>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>

#include "CQGLLayoutViewer.h"
#include "CQLayoutMainWindow.h"

#include <copasi/layout/CLDefaultStyles.h>

#include <string.h>

#include "../UI/icons/photo.xpm"
#include "revert_curve.xpm"
#include "film_strip.xpm"
#include "graph.xpm"
#include "load_data.xpm"

const char* const CQNewMainWindow::ZOOM_FACTOR_STRINGS[] = {"1%", "2%", "3%", "4%", "5%", "10%", "20%", "30%", "40%", "50%", "100%", "150%", "200%", "300%", "400%", "500%", "1000%"};
const double CQNewMainWindow::ZOOM_FACTORS[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 10.0};

// TODO implement signals that allow enabling and disabling the save and save as actions.

CQNewMainWindow::CQNewMainWindow(CCopasiDataModel* pDatamodel):
    QMainWindow(),
    mMode(CQNewMainWindow::GRAPH_MODE),
    mpWidgetStack(NULL),
    mpLayoutViewer(NULL),
    mpAnimationWindow(NULL),
    mpDataModel(pDatamodel),
    mpCurrentLayout(NULL),
    mpCurrentRenderInformation(NULL),
    mDocumentChanged(false),
    mCurDir(""),
    mGraphIcon(QPixmap(graph_xpm)),
    mAnimationIcon(QPixmap(film_strip_xpm))
#ifdef COPASI_DEBUG
    , mpFogColorPixmap(new QPixmap(32, 32))
    , mpHighlightColorPixmap(new QPixmap(32, 32))
    , mpHighlightModeAction(NULL)
    , mpChangeColorAction(NULL)
#endif // COPASI_DEBUG
{
  // first we load the default styles if they don't already exist
  if (DEFAULT_STYLES == NULL)
    {
      DEFAULT_STYLES = loadDefaultStyles();
    }

  this->mCurDir = pDatamodel->getReferenceDirectory();
  this->mpWidgetStack = new QStackedWidget(this);
  this->setCentralWidget(this->mpWidgetStack);
  this->mpLayoutViewer = new CQGLLayoutViewer(this->mpWidgetStack);
  // add the first page
  this->mpWidgetStack->addWidget(this->mpLayoutViewer);
  this->mpAnimationWindow = new CQLayoutMainWindow(this->mpWidgetStack);
  this->mpWidgetStack->addWidget(this->mpAnimationWindow);
  connect(this->mpLayoutViewer, SIGNAL(singleCurveSelected(bool)), this, SLOT(slotSingleCurveSelected(bool)));
  connect(this->mpLayoutViewer->getPainter(), SIGNAL(status_message(const QString&, int)), this, SLOT(setStatusMessage(const QString&, int)));
  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  setUnifiedTitleAndToolBarOnMac(true);
  this->addGlobalRenderInfoItemsToList();
  this->addDefaultRenderInfoItemsToList();
  this->updateLayoutList();
#ifdef COPASI_DEBUG
  // fill the two pixmaps with the current fog and highlight color
  // We have to do that after the call to updateLayoutList because before that call
  // the rnederer does not exist yet.
  const GLfloat* c = this->mpLayoutViewer->getPainter()->getFogColor();
  this->mpFogColorPixmap->fill(QColor((int)(c[0]*255.0), (int)(c[1]*255.0), (int)(c[2]*255.0), (int)(c[3]*255.0)));
  c = this->mpLayoutViewer->getPainter()->getHighlightColor();
  this->mpHighlightColorPixmap->fill(QColor((int)(c[0]*255.0), (int)(c[1]*255.0), (int)(c[2]*255.0), (int)(c[3]*255.0)));
  this->mpChangeColorAction->setIcon(QIcon(*this->mpHighlightColorPixmap));
#endif // COPASI_DEBUG

}

void CQNewMainWindow::createActions()
{

  mpSwitchModeAct = new QAction(mAnimationIcon, tr("animation mode"), this);
  mpSwitchModeAct->setStatusTip(tr("Switch to animation mode."));
  mpSwitchModeAct->setEnabled(true);
  connect(mpSwitchModeAct, SIGNAL(triggered()), this, SLOT(switchMode()));
  mpRevertCurveAct = new QAction(QPixmap(revert_curve_xpm), tr("Revert curve"), this);
  mpRevertCurveAct->setStatusTip(tr("Reverts the currently selected curve."));
  mpRevertCurveAct->setEnabled(false);
  connect(mpRevertCurveAct, SIGNAL(triggered()), this->mpLayoutViewer, SLOT(slotRevertCurve()));

  mpScreenshotAct = new QAction(QPixmap(photo), tr("Export bitmap..."), this);
  mpScreenshotAct->setStatusTip(tr("Export diagram as bitmap."));
  mpScreenshotAct->setEnabled(true);
  connect(mpScreenshotAct, SIGNAL(triggered()), this, SLOT(slotScreenshot()));

  mpCloseAct = new QAction(tr("Close"), this);
  mpCloseAct->setShortcut(tr("Ctrl+Q"));
  mpCloseAct->setStatusTip(tr("Exit the application"));
  connect(mpCloseAct, SIGNAL(triggered()), this, SLOT(close()));

  mpLoadDataAct = new QAction(QPixmap(load_data_xpm), tr("update trajectory data"), this);
  mpLoadDataAct->setStatusTip(tr("Update time course data"));
  mpLoadDataAct->setEnabled(true);
  connect(this->mpLoadDataAct, SIGNAL(activated()), this->mpAnimationWindow, SLOT(loadData()));

  mpRectangularShape = new QAction("Rectangle", this);
  mpRectangularShape->setShortcut(Qt::CTRL + Qt::Key_R);
  mpRectangularShape->setStatusTip("Show labels as rectangles");
  connect(mpRectangularShape, SIGNAL(activated()), this->mpAnimationWindow, SLOT(mapLabelsToRectangles()));

  mpCircularShape = new QAction("Circle", this);
  mpCircularShape->setShortcut(Qt::CTRL + Qt::Key_C);
  mpCircularShape->setStatusTip("Show labels as circles");
  connect(mpCircularShape, SIGNAL(activated()), this->mpAnimationWindow, SLOT(mapLabelsToCircles()));

  mpMimaNodeSizes = new QAction("Set Min/Max Node Sizes", this);
  mpMimaNodeSizes->setShortcut(Qt::CTRL + Qt::Key_M);
  mpMimaNodeSizes->setToolTip("Change Min/Max for node sizes within animation");
  connect(mpMimaNodeSizes, SIGNAL(activated()), this->mpAnimationWindow, SLOT(changeMinMaxNodeSizes()));

  mpSFontSize = new QAction("Set Font Size", this);
  mpSFontSize->setShortcut(Qt::CTRL + Qt::Key_F);
  mpSFontSize->setToolTip("Change the font size of the node labels in the graph view");
  connect(mpSFontSize, SIGNAL(activated()), this->mpAnimationWindow, SLOT(changeFontSize()));
}

void CQNewMainWindow::createMenus()
{
  mpFileMenu = menuBar()->addMenu(tr("&File"));
  mpFileMenu->addAction(mpSwitchModeAct);
  mpFileMenu->addSeparator();
  mpFileMenu->addAction(mpCloseAct);

  // play menu
  mpPlayMenu = menuBar()->addMenu(tr("Play"));
  mpPlayMenu->setVisible(false);
  this->mpPlayMenu->addAction(this->mpAnimationWindow->getControlWidget()->getPlayAction());
  this->mpPlayMenu->addAction(this->mpAnimationWindow->getControlWidget()->getPauseAction());
  this->mpPlayMenu->addAction(this->mpAnimationWindow->getControlWidget()->getStopAction());
  this->mpPlayMenu->addAction(this->mpAnimationWindow->getControlWidget()->getForwardAction());
  this->mpPlayMenu->addAction(this->mpAnimationWindow->getControlWidget()->getBackwardAction());
  this->mpPlayMenu->addAction(this->mpAnimationWindow->getControlWidget()->getStepForwardAction());
  this->mpPlayMenu->addAction(this->mpAnimationWindow->getControlWidget()->getStepBackwardAction());
  this->mpPlayMenu->addSeparator();
  this->mpLoopItemAction = this->mpPlayMenu->addAction(tr("loop animation"));
  this->mpLoopItemAction->setCheckable(true);
  this->mpLoopItemAction->setChecked(false);
  connect(this->mpLoopItemAction, SIGNAL(toggled(bool)) , this->mpAnimationWindow, SLOT(slotLoopActivated(bool)));
  this->mpPlayMenu->addSeparator();
  this->mpPlayMenu->addAction(this->mpLoadDataAct);

  // view menu
  mpViewMenu = menuBar()->addMenu(tr("View"));
  mpViewMenu->addAction(tr("Reset View"), this, SLOT(slotResetView()));
  mpViewMenu->addAction(tr("Fit to Screen"), this, SLOT(slotFitToScreen()));
  this->mpZoomMenu = this->mpViewMenu->addMenu(tr("Zoom"));
  this->mpZoomActionGroup = new QActionGroup(this);
  QAction* pAction = this->mpZoomActionGroup->addAction("1%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("2%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("3%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("4%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("5%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("10%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("20%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("30%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("40%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("50%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("100%");
  pAction->setCheckable(true);
  pAction->setChecked(true);
  pAction = this->mpZoomActionGroup->addAction("150%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("200%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("300%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("400%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("500%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("1000%");
  pAction->setCheckable(true);
  connect(this->mpZoomActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotZoomMenuItemActivated(QAction*)));
  this->mpZoomMenu->addActions(this->mpZoomActionGroup->actions());
#ifdef COPASI_DEBUG
  this->mpViewMenu->addSeparator();
  this->mpHighlightModeAction = this->mpViewMenu->addAction(tr("highlight"));
  this->mpHighlightModeAction->setCheckable(true);
  this->mpHighlightModeAction->setChecked(true);
  this->mpHighlightModeAction->setToolTip(tr("determines whether selected elements are highlighted or if unselected items are toned down."));
  connect(this->mpHighlightModeAction, SIGNAL(toggled(bool)), this, SLOT(toggleHighlightSlot(bool)));
  this->mpChangeColorAction = this->mpViewMenu->addAction(tr("highlight color ..."));
  connect(this->mpChangeColorAction, SIGNAL(triggered(bool)), this, SLOT(changeColorSlot(bool)));
  this->mpChangeColorAction->setToolTip(tr("depending on the highlight mode lets you select the color for highlighting or down toning elements"));
  this->mpElementaryModesMenu = this->mpViewMenu->addMenu("ElementaryModes");
  this->mpElementaryModesMenu->setToolTip(tr("displays a list of elementary modes if any have been calculated and lets you select one or more that are emphasized in the layout displayed"));
  this->mpElementaryModesMenu->addAction(tr("none"));
  connect(this->mpElementaryModesMenu, SIGNAL(aboutToShow()), this, SLOT(checkForElementaryModesSlot()));
#endif // COPASI_DEBUG
  this->mpViewMenu->addSeparator();
  this->mpViewMenu->addAction(this->mpScreenshotAct);

  // options menu
  mpOptionsMenu = menuBar()->addMenu(tr("Options"));
  mpOptionsMenu->setVisible(false);
  QMenu* pM = this->mpOptionsMenu->addMenu(tr("Shape of Label"));
  pM->addAction(this->mpRectangularShape);
  pM->addAction(this->mpCircularShape);
  this->mpOptionsMenu->addAction(this->mpMimaNodeSizes);
  this->mpOptionsMenu->addAction(this->mpSFontSize);

  menuBar()->addSeparator();

  mpHelpMenu = menuBar()->addMenu(tr("&Help"));
}

void CQNewMainWindow::createToolBars()
{
  this->mpFileToolBar = addToolBar(tr("File"));
  this->mpFileToolBar->addAction(this->mpSwitchModeAct);
  this->mpFileToolBar->addAction(this->mpRevertCurveAct);
  this->mpFileToolBar->addAction(this->mpLoadDataAct);
  this->mpLoadDataAct->setVisible(false);
  this->mpFileToolBar->addAction(this->mpScreenshotAct);

  // add a toolbar for the selection widgets
  mpSelectionToolBar = addToolBar(tr("Select"));
  QFrame* pFrame1 = new QFrame;
  QVBoxLayout* pLayout = new QVBoxLayout;
  pLayout->setSpacing(3);
  QLabel* pLabel = new QLabel(tr("Layout:"));
  pLayout->addWidget(pLabel);
  this->mpLayoutDropdown = new QComboBox;
  this->mpLayoutDropdown->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
  pFrame1->setLayout(pLayout);
  pLayout->addWidget(this->mpLayoutDropdown);

  QFrame* pFrame2 = new QFrame;
  pLayout = new QVBoxLayout;
  pLayout->setSpacing(3);
  pFrame2->setLayout(pLayout);
  this->mpRenderLabel = new QLabel(tr("Render Information:"));
  pLayout->addWidget(this->mpRenderLabel);
  this->mpRenderDropdown = new QComboBox;
  this->mpRenderDropdown->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
  pLayout->addWidget(this->mpRenderDropdown);


  QFrame* pFrame3 = new QFrame;
  pLayout = new QVBoxLayout;
  pLayout->setSpacing(3);
  pFrame3->setLayout(pLayout);
  pLabel = new QLabel(tr("Zoom Factor:"));
  pLayout->addWidget(pLabel);
  this->mpZoomDropdown = new QComboBox;
  this->mpZoomDropdown->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
  pLayout->addWidget(this->mpZoomDropdown);
  // fill the zoom factor box
  unsigned int i, iMax = sizeof(CQNewMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);
  int defaultIndex = -1;

  for (i = 0; i < iMax; ++i)
    {
      this->mpZoomDropdown->addItem(QString(CQNewMainWindow::ZOOM_FACTOR_STRINGS[i]));

      if (std::string(CQNewMainWindow::ZOOM_FACTOR_STRINGS[i]) == std::string("100%"))
        {
          defaultIndex = i;
        }
    }

  // set 100% as the default zoom factor
  assert(defaultIndex != -1);
  this->mpZoomDropdown->setCurrentIndex(defaultIndex);
  this->mpSelectionToolBar->addWidget(pFrame1);
  this->mpSelectionToolBar->addWidget(pFrame2);
  this->mpSelectionToolBar->addWidget(pFrame3);
  // connect the combobox signals
  connect(this->mpLayoutDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLayoutChanged(int)));
  connect(this->mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInfoChanged(int)));
  connect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
}

void CQNewMainWindow::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void CQNewMainWindow::updateRenderer()
{
  // pass the datamodel, the layout and the render info to the
  // LayoutViewer
  this->resetView();
  this->mpLayoutViewer->update(this->mpDataModel, this->mpCurrentLayout, this->mpCurrentRenderInformation, QString(this->mCurDir.c_str()));
  this->mpAnimationWindow->setLayout(this->mpCurrentLayout);

  if (this->mpCurrentRenderInformation == getDefaultStyle(0))
    {
      this->mpLayoutViewer->change_style(this->mpCurrentRenderInformation, true);
    }
}

void CQNewMainWindow::resetView()
{
  unsigned int i, iMax = sizeof(CQNewMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);
  int defaultIndex = -1;

  for (i = 0; i < iMax; ++i)
    {
      if (std::string(CQNewMainWindow::ZOOM_FACTOR_STRINGS[i]) == std::string("100%"))
        {
          defaultIndex = i;
        }
    }

  // set 100% as the default zoom factor
  assert(defaultIndex != -1);
  disconnect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
  this->mpZoomDropdown->setCurrentIndex(defaultIndex);
  connect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
}

void CQNewMainWindow::slotResetView()
{
  this->resetView();
  // if we are not in animation mode, we have to repaint
  this->mpLayoutViewer->setZoomFactor(1.0);
  this->mpAnimationWindow->slotResetView();
}

/**
 * This slot is called when the "Fit To Screen" menu item
 * is activated.
 */
void CQNewMainWindow::slotFitToScreen()
{
  double zoom = 1.0;

  if (this->mMode == CQNewMainWindow::ANIMATION_MODE)
    {
      zoom = this->mpAnimationWindow->slotFitToScreen();
      // set the zoom factor on the other GL window
      this->mpLayoutViewer->setZoomFactor(zoom);
    }
  else
    {
      zoom = this->mpLayoutViewer->fitToScreen();
      // set the zoom factor on the other GL window
      this->mpAnimationWindow->setZoomFactor(zoom);

    }

  // uncheck the zoom entry in the menu
  QList<QAction*> actions = this->mpZoomActionGroup->actions();
  QList<QAction*>::iterator it = actions.begin(), endit = actions.end();

  while (it != endit)
    {
      if ((*it)->isChecked())
        {
          (*it)->setChecked(false);
          // only one can be checked
          break;
        }

      ++it;
    }

  // add a new entry for the current zoom factor to the zoom dropdown list
  disconnect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
  // add a new entry for the zoom factor
  QString s = QString("%1").arg(zoom * 100);
  s.append("%");
  const size_t n = sizeof(CQNewMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);

  if ((size_t)this->mpZoomDropdown->count() > n)
    {
      this->mpZoomDropdown->setItemText(0, s);
    }
  else
    {
      this->mpZoomDropdown->insertItem(0, s);
    }

  this->mpZoomDropdown->setCurrentIndex(0);
  connect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));

}


void CQNewMainWindow::slotLayoutChanged(int index)
{
  //std::cout << "new layout " << index << std::endl;
  CLayout* pTmpLayout = (*this->mpDataModel->getListOfLayouts())[index];

  if (pTmpLayout != this->mpCurrentLayout)
    {
      this->mpCurrentLayout = pTmpLayout;
      // update the corresponding render information list
      this->updateRenderInformationList();
      this->updateRenderer();
    }
}

void CQNewMainWindow::slotRenderInfoChanged(int index)
{
  // check if a local or a global render information has been selected
  CLRenderInformationBase* pRenderInfo = NULL;

  // the local render information is first in the list
  if (index == -1)
    {
      //std::cout << "index is -1" << std::endl;
      return;
    }

  size_t Index = (size_t) index;

  size_t numLocalRenderInfo = this->mpCurrentLayout->getListOfLocalRenderInformationObjects().size();
  size_t numFileRenderInfo = numLocalRenderInfo + this->mpDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size();

  if (Index >= numLocalRenderInfo)
    {
      // it is a global render information or a default render info
      if (Index >= numFileRenderInfo)
        {
          // it must be a default render information
          pRenderInfo = getDefaultStyle(Index - numFileRenderInfo);

          if (pRenderInfo != this->mpCurrentRenderInformation)
            {
              this->mpCurrentRenderInformation = pRenderInfo;
              this->change_style(true);
            }
        }
      else
        {
          pRenderInfo = this->mpDataModel->getListOfLayouts()->getRenderInformation(Index - numLocalRenderInfo);

          if (pRenderInfo != this->mpCurrentRenderInformation)
            {
              this->mpCurrentRenderInformation = pRenderInfo;
              this->change_style();
            }
        }
    }
  else
    {
      // it is a local render information
      pRenderInfo = this->mpCurrentLayout->getRenderInformation(Index);

      if (pRenderInfo != this->mpCurrentRenderInformation)
        {
          this->mpCurrentRenderInformation = pRenderInfo;
          this->change_style();
        }
    }
}

void CQNewMainWindow::updateRenderInformationList()
{
  // disconnect the slot
  disconnect(this->mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInfoChanged(int)));
  // remove the local render information items
  size_t num = this->mpDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size() + getNumDefaultStyles();

  while ((size_t) this->mpRenderDropdown->count() > num)
    {
      this->mpRenderDropdown->removeItem(0);
    }

  // add the new local render information items
  if (this->mpCurrentLayout)
    {
      num = this->mpCurrentLayout->getListOfLocalRenderInformationObjects().size();
      size_t i;
      CLRenderInformationBase* pTmpRenderInfo = NULL;

      for (i = num; i > 0; --i)
        {
          pTmpRenderInfo = this->mpCurrentLayout->getRenderInformation(i - 1);
          std::string text = pTmpRenderInfo->getKey();

          if (!pTmpRenderInfo->getName().empty())
            {
              text += " (";
              text += pTmpRenderInfo->getName();
              text += ")";
            }

          this->mpRenderDropdown->insertItem(0, QString(text.c_str()));
        }
    }

  // if the current render information is a global render information, keep
  // the selection
  // otherwise select the first render information if there is one
  if (dynamic_cast<const CLGlobalRenderInformation*>(this->mpCurrentRenderInformation))
    {
      // find the correct index
      size_t i, iMax = this->mpDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size();

      for (i = 0; i < iMax; ++i)
        {
          if (this->mpCurrentRenderInformation == this->mpDataModel->getListOfLayouts()->getRenderInformation(i))
            {
              break;
            }
        }

      if (i == iMax)
        {
          // it must be a default style
          num += i;
          iMax = getNumDefaultStyles();

          for (i = 0; i < iMax; ++i)
            {
              if (this->mpCurrentRenderInformation == getDefaultStyle(i))
                {
                  break;
                }
            }

          assert(i != iMax);
          this->mpRenderDropdown->setCurrentIndex((int)(num + i));
        }
      else
        {
          this->mpRenderDropdown->setCurrentIndex((int)(num + i));
        }
    }
  else
    {
      if (this->mpRenderDropdown->count() > 0)
        {
          if (num > 0)
            {
              // take the first local render information
              if (this->mpCurrentLayout != NULL)
                {
                  this->mpCurrentRenderInformation = this->mpCurrentLayout->getRenderInformation(0);
                }
              else
                {
                  this->mpCurrentRenderInformation = NULL;
                }

              this->mpRenderDropdown->setCurrentIndex(0);
            }
          else if (this->mpDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size() > 0)
            {
              // take the first global render information
              this->mpCurrentRenderInformation = this->mpDataModel->getListOfLayouts()->getRenderInformation(0);
              this->mpRenderDropdown->setCurrentIndex((int) num);
            }
          else if (getNumDefaultStyles() > 0)
            {
              this->mpCurrentRenderInformation = getDefaultStyle(0);
            }
          else
            {
              this->mpCurrentRenderInformation = NULL;
            }
        }
      else
        {
          this->mpCurrentRenderInformation = NULL;
        }
    }

  // reconnect the slot
  connect(this->mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInfoChanged(int)));
}

void CQNewMainWindow::addGlobalRenderInfoItemsToList()
{
  // disconnect the slot
  disconnect(this->mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInfoChanged(int)));
  this->mpRenderDropdown->clear();
  size_t i, iMax = this->mpDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size();
  CLRenderInformationBase* pTmpRenderInfo = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pTmpRenderInfo = this->mpDataModel->getListOfLayouts()->getRenderInformation(i);
      std::string text = pTmpRenderInfo->getKey();

      if (!pTmpRenderInfo->getName().empty())
        {
          text += " (";
          text += pTmpRenderInfo->getName();
          text += ")";
        }

      this->mpRenderDropdown->addItem(QString(text.c_str()));
    }

  // reconnect the slot
  connect(this->mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInfoChanged(int)));
}

void CQNewMainWindow::addDefaultRenderInfoItemsToList()
{
  // disconnect the slot
  disconnect(this->mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInfoChanged(int)));
  size_t i, iMax = getNumDefaultStyles();
  CLRenderInformationBase* pTmpRenderInfo = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pTmpRenderInfo = getDefaultStyle(i);
      std::string text = pTmpRenderInfo->getKey();

      if (!pTmpRenderInfo->getName().empty())
        {
          text += " (";
          text += pTmpRenderInfo->getName();
          text += ")";
        }

      this->mpRenderDropdown->addItem(QString(text.c_str()));
    }

  // reconnect the slot
  connect(this->mpRenderDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRenderInfoChanged(int)));
}

void CQNewMainWindow::slotZoomChanged(int index)
{
  // check if the number of zoom factors in the combobox is greater than
  // the numbers of items in the zoom combo box
  //
  // if so, delete the first entry from the list and reduce the index by 1 because the first entry must be
  // the item that has been added by fitToScreen.
  const size_t n = sizeof(CQNewMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);

  if ((size_t)this->mpZoomDropdown->count() > n && index != 0)
    {
      --index;
      disconnect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
      this->mpZoomDropdown->removeItem(0);
      this->mpZoomDropdown->setCurrentIndex(index);
      connect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
    }

  this->mpLayoutViewer->setZoomFactor(CQNewMainWindow::ZOOM_FACTORS[index]);
  // also change the zoom factor for the animation window
  this->mpAnimationWindow->setZoomFactor(this->mpZoomDropdown->currentText());

  // also set the zoom factor in the menu
  if ((int) index < this->mpZoomActionGroup->actions().size())
    {
      this->mpZoomActionGroup->actions().at(index)->setChecked(true);
    }
}

void CQNewMainWindow::slotZoomMenuItemActivated(QAction* pAction)
{
  int index = this->mpZoomActionGroup->actions().indexOf(pAction);
  // check if the number of zoom factors in the combobox is greater than
  // the number of items in the combobox
  //
  // if so, delete the first entry from the list because this
  // item that has been added by fitToScreen.
  const size_t n = sizeof(CQNewMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);

  if ((size_t)this->mpZoomDropdown->count() > n)
    {
      disconnect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
      this->mpZoomDropdown->removeItem(0);
      connect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));
    }

  this->mpLayoutViewer->setZoomFactor(CQNewMainWindow::ZOOM_FACTORS[index]);
  // also set the zoom factor in the combobox
  disconnect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));

  if (index < this->mpZoomDropdown->count())
    {
      this->mpZoomDropdown->setCurrentIndex(index);
    }

  connect(this->mpZoomDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomChanged(int)));

  // also change the zoom factor for the animation window
  this->mpAnimationWindow->setZoomFactor(this->mpZoomDropdown->currentText());
}

void CQNewMainWindow::change_style(bool defaultStyle)
{
  this->mpLayoutViewer->change_style(this->mpCurrentRenderInformation, defaultStyle);
}

/**
 * This slot is called when something in the document changes.
 */
void CQNewMainWindow::slotSingleCurveSelected(bool selected)
{
  // check if a single curve is selected
  if (selected)
    {
      this->mpRevertCurveAct->setEnabled(true);
    }
  else
    {
      this->mpRevertCurveAct->setEnabled(false);
    }
}

/**
 * This slot initiates the export
 * of the layout as a bitmap.
 * The user gets to choose which part of the
 * layout is to be exported and how large the
 * resulting bitmap is supposed to be.
 */
void CQNewMainWindow::slotScreenshot()
{
  CQGLLayoutPainter* pPainter = this->mpLayoutViewer->getPainter();

  if (pPainter != NULL)
    {
      double layoutX = pPainter->minX();
      double layoutY = pPainter->minY();
      double layoutWidth = pPainter->maxX() - layoutX;
      double layoutHeight = pPainter->maxY() - layoutY;
      double x = pPainter->getCurrentPositionX();
      double y = pPainter->getCurrentPositionY();
      double width = pPainter->getCurrentWidth();
      double height = pPainter->getCurrentHeight();
      CQScreenshotOptionsDialog* pDialog = new CQScreenshotOptionsDialog(layoutX, layoutY, layoutWidth, layoutHeight,
          x, y, width, height, pPainter->width() , pPainter->height(), -1, this);

      if (pDialog->exec() == QDialog::Accepted)
        {
          // ask for the filename
          QString fileName = QFileDialog::getSaveFileName(this, QString("Export to"), "", QString("PNG (*.png);;All files (*)"));

          if (!fileName.isEmpty())
            {
              export_bitmap(fileName, pDialog->getX(), pDialog->getY(), pDialog->getWidth(), pDialog->getHeight(), pDialog->getImageWidth(), pDialog->getImageHeight(), pDialog->isSetDrawSelectionDecoration());
            }
        }

      delete pDialog;
    }
}

/**
 * Exports a bitmap of the given size to
 * the file with the given name.
 */
void CQNewMainWindow::export_bitmap(const QString& filename, double x, double y, double width, double height, unsigned int imageWidth, unsigned int imageHeight, bool drawSelection)
{
  // check if the size of the final image is ok.
  double size = imageWidth * imageHeight * 4;

  // I don't think we should write images that are larger than 500MB
  if (size < 5e8)
    {
      //
      // before we even start, we check if the file can be written to at all
      // if not, we don't have to do anything
      QFileInfo info(filename);

      if (info.exists())
        {
          if (!info.isFile())
            {
              // create an error message and cancel saving
              QMessageBox::critical(this, tr("Not a file"),
                                    tr("Path exists, but it is not a file."));
              return;
            }
          else
            {
              if (!info.isWritable())
                {
                  // create an error message and cancel saving
                  QMessageBox::critical(this, tr("Not writable"),
                                        tr("Can't write to file."));
                  return;
                }
            }
        }
      else
        {
          // check if the directory exists.
        }

      // now we try to create the image
      CQGLLayoutPainter* pPainter = this->mpLayoutViewer->getPainter();

      if (pPainter != NULL)
        {
          GLubyte* pImageData = pPainter->export_bitmap(x, y, width, height, imageWidth, imageHeight, drawSelection);

          if (pImageData != NULL)
            {
              QImage* pImage = new QImage(pImageData, imageWidth, imageHeight, 4*imageWidth, QImage::Format_ARGB32);
              bool result = pImage->save(filename, "PNG");

              if (result == false)
                {
                  QMessageBox::critical(this, tr("Save error"),
                                        tr("An error occured while saving the file.\nThe file might be invalid."));
                }

              delete pImage;
              delete[] pImageData;
            }
        }
    }
  else
    {
      // give an error message that the image is to large
      QMessageBox::critical(this, tr("Image too large"),
                            tr("Sorry, refusing to create images that are larger than 500MB."));
    }
}

void CQNewMainWindow::updateLayoutList()
{
  if (this->mpDataModel == NULL) return;

  disconnect(this->mpLayoutDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLayoutChanged(int)));
  this->mpLayoutDropdown->clear();
  const CLayout* pTmpLayout = NULL;
  size_t i, iMax = this->mpDataModel->getListOfLayouts()->size();

  for (i = 0; i < iMax; ++i)
    {
      pTmpLayout = (*this->mpDataModel->getListOfLayouts())[i];
      std::string text = pTmpLayout->getKey();

      if (!pTmpLayout->getObjectName().empty())
        {
          text += "(";
          text += pTmpLayout->getObjectName();
          text += ")";
        }

      this->mpLayoutDropdown->addItem(text.c_str());
    }

  if (iMax > 0)
    {
      this->mpCurrentLayout = (*this->mpDataModel->getListOfLayouts())[0];
    }

  this->updateRenderInformationList();

  if (this->mpCurrentLayout && this->mpCurrentRenderInformation)
    {
      this->updateRenderer();
    }

  connect(this->mpLayoutDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLayoutChanged(int)));
}

/**
 * switches the display mode between animation mode and
 * graph mode.
 */
void CQNewMainWindow::switchMode()
{
  switch (this->mMode)
    {
      case CQNewMainWindow::GRAPH_MODE:
        disconnect(mpScreenshotAct, SIGNAL(triggered()), this, SLOT(slotScreenshot()));
        connect(this->mpScreenshotAct, SIGNAL(triggered()), this->mpAnimationWindow, SLOT(saveImage()));
        this->mpSwitchModeAct->setIcon(mGraphIcon);
        this->mpSwitchModeAct->setStatusTip(tr("Switch to graph mode."));
        this->mpSwitchModeAct->setText(tr("graph mode"));
        this->mMode = CQNewMainWindow::ANIMATION_MODE;
        this->setAnimationToolbar();
        this->setAnimationMenu();
        this->mpWidgetStack->setCurrentIndex(1);
#ifdef COPASI_DEBUG
        this->mpElementaryModesMenu->setEnabled(false);
        this->mpHighlightModeAction->setEnabled(false);
        this->mpChangeColorAction->setEnabled(false);
#endif // COPASI_DEBUG
        break;
      case CQNewMainWindow::ANIMATION_MODE:
        disconnect(this->mpScreenshotAct, SIGNAL(triggered()), this->mpAnimationWindow, SLOT(saveImage()));
        connect(mpScreenshotAct, SIGNAL(triggered()), this, SLOT(slotScreenshot()));
        this->mpSwitchModeAct->setIcon(mAnimationIcon);
        this->mpSwitchModeAct->setStatusTip(tr("Switch to animation mode."));
        this->mpSwitchModeAct->setText(tr("animation mode"));
        this->mMode = CQNewMainWindow::GRAPH_MODE;
        this->setGraphToolbar();
        this->setGraphMenu();
        this->mpWidgetStack->setCurrentIndex(0);
#ifdef COPASI_DEBUG
        this->mpElementaryModesMenu->setEnabled(true);
        this->mpHighlightModeAction->setEnabled(true);
        this->mpChangeColorAction->setEnabled(true);
#endif // COPASI_DEBUG
        break;
    }
}

void CQNewMainWindow::setAnimationToolbar()
{
  // remove revert curve action
  this->mpRevertCurveAct->setVisible(false);
  // add load data action
  this->mpLoadDataAct->setVisible(true);
  // hide the render information box
  this->mpRenderLabel->hide();
  this->mpRenderDropdown->hide();
}

void CQNewMainWindow::setGraphToolbar()
{
  // remove load data action
  this->mpLoadDataAct->setVisible(false);
  // add revert curve action
  this->mpRevertCurveAct->setVisible(true);
  // show the render information box
  this->mpRenderLabel->show();
  this->mpRenderDropdown->show();
}

void CQNewMainWindow::setAnimationMenu()
{
  this->mpPlayMenu->menuAction()->setVisible(true);
  this->mpOptionsMenu->menuAction()->setVisible(true);
}

void CQNewMainWindow::setGraphMenu()
{
  this->mpPlayMenu->menuAction()->setVisible(false);
  this->mpOptionsMenu->menuAction()->setVisible(false);
}

void CQNewMainWindow::setStatusMessage(const QString& message, int timeout)
{
  this->statusBar()->showMessage(message, timeout);
}


#ifdef COPASI_DEBUG
/**
 * Checks for calculated elementary modes.
 */
void CQNewMainWindow::checkForElementaryModesSlot()
{
  bool fluxModesChanged = false;

  if (this->mpDataModel != NULL)
    {
      const CCopasiVectorN< CCopasiTask >* pTaskList = this->mpDataModel->getTaskList();
      assert(pTaskList != NULL);

      if (pTaskList != NULL)
        {
          // get the metabolic control analysis task object
          const CEFMTask* pTask = dynamic_cast<const CEFMTask*>((*pTaskList)["Elementary Flux Modes"]);

          if (pTask != NULL)
            {
              const CEFMProblem* pProblem = dynamic_cast<const CEFMProblem*>(pTask->getProblem());

              if (pProblem != NULL && !pProblem->getFluxModes().empty())
                {
                  const std::vector< CFluxMode >& fluxModes = pProblem->getFluxModes();
                  size_t iMax = fluxModes.size();

                  if (this->mFluxModes.size() != iMax)
                    {
                      fluxModesChanged = true;
                    }
                  else
                    {
                      unsigned int i = 0;

                      while (i < iMax && fluxModesChanged == false)
                        {
                          if (&(fluxModes[i]) != this->mFluxModes[i])
                            {
                              fluxModesChanged = true;
                            }

                          ++i;
                        }
                    }

                  if (fluxModesChanged)
                    {
                      this->mpElementaryModesMenu->clear();
                      this->mFluxModes.clear();

                      if (fluxModes.empty())
                        {
                          this->mpElementaryModesMenu->addAction("None");
                          disconnect(this->mpElementaryModesMenu, SIGNAL(triggered(QAction*)), this, SLOT(elementaryModeTriggeredSlot(QAction*)));
                        }
                      else
                        {
                          unsigned int i = 0;
                          const CFluxMode* pFluxMode = NULL;

                          while (i < iMax)
                            {
                              pFluxMode = &(fluxModes[i]);
                              this->mFluxModes.push_back(pFluxMode);
                              std::string desc = pTask->getFluxModeDescription(*pFluxMode);
                              QAction* pAction = this->mpElementaryModesMenu->addAction(QString(desc.c_str()));
                              pAction->setCheckable(true);
                              ++i;
                            }

                          connect(this->mpElementaryModesMenu, SIGNAL(triggered(QAction*)), this, SLOT(elementaryModeTriggeredSlot(QAction*)));
                        }
                    }
                }
            }
        }
    }
}

/**
 * Checks which elementary mode has been toggled and updates the
 * highlighted objects list.
 */
void CQNewMainWindow::elementaryModeTriggeredSlot(QAction* pAction)
{
  // determine the index of the flux mode
  unsigned int index = this->mpElementaryModesMenu->actions().indexOf(pAction);
  // get the set of currently highlighted objects
  assert(this->mpLayoutViewer != NULL && this->mpLayoutViewer->getPainter() != NULL);
  std::set<const CCopasiObject*>& highlighted = this->mpLayoutViewer->getPainter()->getHighlightedModelObjects();

  // if the action is checked, we need to add all the reactions of the flux mode
  // to the highlighted objects
  if (pAction->isChecked())
    {
      const CFluxMode* pFlux = this->mFluxModes[index];
      CFluxMode::const_iterator it = pFlux->begin(), endit = pFlux->end();
      const CReaction* pReaction = NULL;
      assert(this->mpDataModel != NULL && this->mpDataModel->getModel() != NULL);
      const CModel* pModel = this->mpDataModel->getModel();

      while (it != endit)
        {
          assert(pModel->getReactions().size() > it->first);
          pReaction = this->mpDataModel->getModel()->getReactions()[it->first];
          assert(pReaction != NULL);
          highlighted.insert(pReaction);
          // now we need to add the arrows and species
          const CChemEq& chemEq = pReaction->getChemEq();
          const CCopasiVector<CChemEqElement>& substrates = chemEq.getSubstrates();
          CCopasiVector<CChemEqElement>::const_iterator it2 = substrates.begin(), endit2 = substrates.end();

          while (it2 != endit2)
            {
              assert((*it2) != NULL);
              highlighted.insert(*it2);
              assert((*it2)->getMetabolite() != NULL);
              highlighted.insert((*it2)->getMetabolite());
              ++it2;
            }

          const CCopasiVector<CChemEqElement>& products = chemEq.getProducts();

          it2 = products.begin();

          endit2 = products.end();

          while (it2 != endit2)
            {
              assert((*it2) != NULL);
              highlighted.insert(*it2);
              assert((*it2)->getMetabolite() != NULL);
              highlighted.insert((*it2)->getMetabolite());
              ++it2;
            }

          ++it;
        }
    }
  // if the node is unchecked, we need to remove all the reactions from the
  // highlighted objects, but only those that are not part of another selected flux mode
  else
    {
      // we first need to find all objects that belong to other flux modes
      const QList<QAction*>& actions = this->mpElementaryModesMenu->actions();
      QList<QAction*>::const_iterator ait = actions.begin(), aendit = actions.end();
      unsigned int i;
      const CFluxMode* pFlux = NULL;
      std::set<const CCopasiObject*> remaining;

      while (ait != aendit)
        {
          if ((*ait)->isChecked())
            {
              i = actions.indexOf(*ait);
              assert(i < this->mFluxModes.size());
              pFlux = this->mFluxModes[i];
              CFluxMode::const_iterator it = pFlux->begin(), endit = pFlux->end();
              const CReaction* pReaction = NULL;
              assert(this->mpDataModel != NULL && this->mpDataModel->getModel() != NULL);
              const CModel* pModel = this->mpDataModel->getModel();

              while (it != endit)
                {
                  assert(pModel->getReactions().size() > it->first);
                  pReaction = this->mpDataModel->getModel()->getReactions()[it->first];
                  assert(pReaction != NULL);
                  remaining.insert(pReaction);
                  // now we need to add the arrows and species
                  const CChemEq& chemEq = pReaction->getChemEq();
                  const CCopasiVector<CChemEqElement>& substrates = chemEq.getSubstrates();
                  CCopasiVector<CChemEqElement>::const_iterator it2 = substrates.begin(), endit2 = substrates.end();

                  while (it2 != endit2)
                    {
                      remaining.insert(*it2);
                      remaining.insert((*it2)->getMetabolite());
                      ++it2;
                    }

                  const CCopasiVector<CChemEqElement>& products = chemEq.getProducts();

                  it2 = products.begin();

                  endit2 = products.end();

                  while (it2 != endit2)
                    {
                      highlighted.insert(*it2);
                      highlighted.insert((*it2)->getMetabolite());
                      ++it2;
                    }

                  ++it;
                }

            }

          ++ait;
        }

      // now we remove all object from the unselected flux
      // that are not in remaining
      pFlux = this->mFluxModes[index];
      CFluxMode::const_iterator it = pFlux->begin(), endit = pFlux->end();
      const CReaction* pReaction = NULL;
      assert(this->mpDataModel != NULL && this->mpDataModel->getModel() != NULL);
      const CModel* pModel = this->mpDataModel->getModel();

      while (it != endit)
        {
          assert(pModel->getReactions().size() > it->first);
          pReaction = this->mpDataModel->getModel()->getReactions()[it->first];
          assert(pReaction != NULL);

          if (remaining.find(pReaction) == remaining.end())
            {
              highlighted.erase(highlighted.find(pReaction));
            }

          // now we need to add the arrows and species
          const CChemEq& chemEq = pReaction->getChemEq();
          const CCopasiVector<CChemEqElement>& substrates = chemEq.getSubstrates();
          CCopasiVector<CChemEqElement>::const_iterator it2 = substrates.begin(), endit2 = substrates.end();
          std::set<const CCopasiObject*>::iterator pos;

          while (it2 != endit2)
            {
              pos = highlighted.find(*it2);

              if (remaining.find((*it2)) == remaining.end() && pos != highlighted.end())
                {
                  highlighted.erase(pos);
                }

              pos = highlighted.find((*it2)->getMetabolite());

              if (remaining.find((*it2)->getMetabolite()) == remaining.end() && pos != highlighted.end())
                {
                  highlighted.erase(pos);
                }

              ++it2;
            }

          const CCopasiVector<CChemEqElement>& products = chemEq.getProducts();

          it2 = products.begin();

          endit2 = products.end();

          while (it2 != endit2)
            {
              pos = highlighted.find((*it2));

              if (remaining.find((*it2)) == remaining.end() && pos != highlighted.end())
                {
                  highlighted.erase(pos);
                }

              pos = highlighted.find((*it2)->getMetabolite());

              if (remaining.find((*it2)->getMetabolite()) == remaining.end() && pos != highlighted.end())
                {
                  highlighted.erase(pos);
                }

              ++it2;
            }

          ++it;
        }

    }

  // redraw the GL window
  if (this->mMode == GRAPH_MODE)
    {
      this->mpLayoutViewer->getPainter()->update();
    }
}

/**
 * Is called when the menu entry for toggling highlighting
 * of elementary modes is toggled.
 */
void CQNewMainWindow::toggleHighlightSlot(bool checked)
{
  this->mpLayoutViewer->getPainter()->setHighlightFlag(checked);

  // update the icon and the text
  if (checked)
    {
      this->mpChangeColorAction->setText(tr("highlight color ..."));
      this->mpChangeColorAction->setIcon(QIcon(*this->mpHighlightColorPixmap));
    }
  else
    {
      this->mpChangeColorAction->setText(tr("fog color ..."));
      this->mpChangeColorAction->setIcon(QIcon(*this->mpFogColorPixmap));
    }

  // we need to redraw the gl window
  if (this->mMode == GRAPH_MODE)
    {
      this->mpLayoutViewer->getPainter()->update();
    }
}


/**
 * This slot is triggered when the user wants to change
 * the fog or the highlighting color, depending on the current
 * highlighting mode.
 */
void CQNewMainWindow::changeColorSlot(bool)
{
  // find the correct color for the current mode
  const GLfloat* c = NULL;

  if (this->mpHighlightModeAction->isChecked())
    {
      c = this->mpLayoutViewer->getPainter()->getHighlightColor();
    }
  else
    {
      c = this->mpLayoutViewer->getPainter()->getFogColor();
    }

  // open a color selection dialog
  QColorDialog* pDialog = new QColorDialog(QColor((int)(c[0]*255.0), (int)(c[1]*255.0), (int)(c[2]*255.0), (int)(c[3]*255.0)), this);

  if (pDialog->exec() == QDialog::Accepted)
    {
      // the dialog has been closed with the OK button
      // so we need to get the new color
      QColor color = pDialog->selectedColor();
      GLfloat newColor[4] = {((GLfloat)color.red()) / 255.0, ((GLfloat)color.green()) / 255.0, ((GLfloat)color.blue()) / 255.0, ((GLfloat)color.alpha()) / 255.0};

      // update the pixmap and the icon for the mpHighlightModeAction
      if (this->mpHighlightModeAction->isChecked())
        {
          this->mpLayoutViewer->getPainter()->setHighlightColor(newColor);
          this->mpHighlightColorPixmap->fill(color);
          this->mpChangeColorAction->setIcon(QIcon(*this->mpHighlightColorPixmap));
        }
      else
        {
          this->mpLayoutViewer->getPainter()->setFogColor(newColor);
          this->mpFogColorPixmap->fill(color);
          this->mpChangeColorAction->setIcon(QIcon(*this->mpFogColorPixmap));
        }

      // redraw the GL window
      if (this->mMode == GRAPH_MODE)
        {
          this->mpLayoutViewer->getPainter()->update();
        }
    }
}
#endif // COPASI_DEBUG

