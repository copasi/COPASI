// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQElementProperties.h"
#include "ui_CQElementProperties.h"

#include <sbml/packages/render/sbml/RenderGroup.h>

#include <copasi/layout/CLGlyphs.h>
#include <copasi/layout/CLayout.h>
#include <copasi/layout/CLRenderInformationBase.h>
#include <copasi/layout/CLRenderResolver.h>

#include <copasi/qlayout/CQLayoutScene.h>
#include <copasi/qlayout/CQStyledGraphicsItem.h>
#include <copasi/qlayout/CQConnectionGraphicsItem.h>
#include <copasi/qlayout/CQRenderConverter.h>

#include <copasi/core/CRootContainer.h>
#include <copasi/report/CKeyFactory.h>
#include <copasi/UI/qtUtilities.h>
#include <copasi/UI/copasiui3window.h>
#include <copasi/UI/listviews.h>

#include <QMessageBox>

CQElementProperties::CQElementProperties(QWidget *parent)
  : QWidget(parent)
  , mpScene(NULL)
  , ui(new Ui::CQElementProperties)
{
  ui->setupUi(this);
}

CQElementProperties::~CQElementProperties()
{
  delete ui;
}

void CQElementProperties::setScene(CQLayoutScene * scene)
{

  if (mpScene != NULL)
    {
      disconnect(mpScene, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
    }

  mpScene = scene;


  if (scene == NULL)
    return;

  fillStylesFromScene(scene);

  connect(mpScene, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
}


void CQElementProperties::fillStylesFromScene(CQLayoutScene* scene)
{
  ui->cmbStyles->clear();

  if (scene == NULL)
    return;

  auto * render = scene->getCurrentRenderInfo();

  if (render != NULL)
    {
      for (size_t i = 0; i < render->getNumStyles(); ++i)
        {
          auto * style = render->getStyle(i);

          if (style == NULL)
            continue;

          std::string title = style->getKey() + " " + style->getRoleListString() + " " + style->getTypeListString();
          ui->cmbStyles->addItem(FROM_UTF8(title), FROM_UTF8(style->getKey()));
        }
    }

}

void CQElementProperties::removeGlyphFromStyle(const std::string & glyphKey, const std::string & styleKey)
{
  CDataObject * obj = CRootContainer::getKeyFactory()->get(styleKey);
  CLLocalStyle * pGO = dynamic_cast< CLLocalStyle * >(obj);

  if (pGO == NULL)
    return;

  pGO->removeKey(glyphKey);

}

void CQElementProperties::addGlyphToStyle(const std::string & glyphKey, const std::string & styleKey)
{
  CDataObject * obj = CRootContainer::getKeyFactory()->get(styleKey);
  CLLocalStyle * pLocal = dynamic_cast< CLLocalStyle * >(obj);

  if (pLocal != NULL)
    {
      pLocal->addKey(glyphKey);
      mpScene->getResolver()->addKeyToMap(glyphKey, pLocal);
      return;
    }

  CLStyle * pGlobal = dynamic_cast< CLStyle * >(obj);
  obj = CRootContainer::getKeyFactory()->get(glyphKey);
  CLGraphicalObject* pGlyph = dynamic_cast< CLGraphicalObject * >(obj);

  if (pGlobal == NULL || pGlyph == NULL)
    return;

  pGlyph->setObjectRole(glyphKey);
  pGlobal->addRole(glyphKey);
  mpScene->getResolver()->addKeyToMap(glyphKey, pGlobal);
}


void CQElementProperties::loadFromGlyph(CLGraphicalObject * pGO)
{
  mGlyphKey = "";
  mTargetCN = "";
  mTextKey = "";
  mStyleKey = "";

  ui->txtGlyph->setText("");
  ui->txtTarget->setText("");
  ui->txtText->setText("");
  ui->txtCurrentStyle->setText("");
  ui->txtObjectRole->setText("");

  if (!pGO)
    return;

  mGlyphKey = pGO->getKey();
  CDataObject * pTarget = pGO->getModelObject();
  mTargetCN = pTarget == NULL ? std::string() : pTarget->getCN();

  if (mpScene)
    {

for (auto & text : mpScene->getCurrentLayout()->getListOfTextGlyphs())
        {
          if (text.getGraphicalObjectKey() == mGlyphKey)
            {
              mTextKey = text.getKey();
              ui->txtText->setText(FROM_UTF8(mTextKey));
              break;
            }
        }

      const CLStyle * pStyle = mpScene->getCurrentRenderInfo()->getStyleForGraphicalObject(pGO);

      if (pStyle != NULL)
        {
          mStyleKey = pStyle->getKey();
          ui->txtCurrentStyle->setText(FROM_UTF8(mStyleKey));
        }
    }

  ui->txtX->setText(QString::number(pGO->getX()));
  ui->txtY->setText(QString::number(pGO->getY()));
  ui->txtHeight->setText(QString::number(pGO->getHeight()));
  ui->txtWidth->setText(QString::number(pGO->getWidth()));

  ui->txtGlyph->setText(FROM_UTF8(pGO->getKey()));
  ui->txtTarget->setText(FROM_UTF8(pGO->getModelObjectDisplayName()));
  ui->txtObjectRole->setText(FROM_UTF8(pGO->getObjectRole()));

  for (int i = 0; i < ui->cmbStyles->count(); ++i)
    {
      std::string current = TO_UTF8(ui->cmbStyles->itemData(i).toString());

      if (current == mStyleKey)
        {
          ui->cmbStyles->setCurrentIndex(i);
          break;
        }
    }

}

void CQElementProperties::loadFromGlyph(const std::string & key)
{
  CDataObject * obj = CRootContainer::getKeyFactory()->get(key);
  CLGraphicalObject * pGO = dynamic_cast< CLGraphicalObject * >(obj);

  if (pGO == NULL)
    return;

  loadFromGlyph(pGO);
}

void CQElementProperties::slotApply()
{
  if (mGlyphKey.empty())
    return;

  CDataObject * obj = CRootContainer::getKeyFactory()->get(mGlyphKey);
  CLGraphicalObject * pGO = dynamic_cast< CLGraphicalObject * >(obj);

  if (pGO == NULL)
    return;

  pGO->setX(ui->txtX->text().toDouble());
  pGO->setY(ui->txtY->text().toDouble());
  pGO->setWidth(ui->txtWidth->text().toDouble());
  pGO->setHeight(ui->txtHeight->text().toDouble());

  pGO->setObjectRole(TO_UTF8(ui->txtObjectRole->text()));

  std::string styleKey = TO_UTF8(ui->cmbStyles->itemData(ui->cmbStyles->currentIndex()).toString());

  if (styleKey != mStyleKey)
    {
      removeGlyphFromStyle(mGlyphKey, mStyleKey);
      addGlyphToStyle(mGlyphKey, styleKey);
      loadFromGlyph(mGlyphKey);
    }

  mpScene->recreate();

}

void CQElementProperties::slotDisplayStyle()
{
  if (mStyleKey.empty())
    return;

  CDataObject * obj = CRootContainer::getKeyFactory()->get(mStyleKey);
  CLStyle * pStyle = dynamic_cast< CLStyle * >(obj);

  if (pStyle == NULL)
    return;

  RenderGroup * pGroup = pStyle->getGroup()->toSBML(3, 1);
  char * sbml = pGroup->toSBML();
  delete pGroup;

  QMessageBox::information(this, "Style code", sbml);

  free(sbml);

}

void CQElementProperties::slotSelectTextGlyph()
{
  if (mTextKey.empty())
    return;

  CDataObject * obj = CRootContainer::getKeyFactory()->get(mTextKey);
  CLGraphicalObject * pGO = dynamic_cast< CLGraphicalObject * >(obj);

  if (pGO == NULL)
    return;

  loadFromGlyph(pGO);
}

void CQElementProperties::slotSelectTarget()
{
  if (mTargetCN.empty())
    return;

  CopasiUI3Window::getMainWindow()->getMainWidget()->switchToOtherWidget(ListViews::WidgetType::NotFound, mTargetCN);
}

void CQElementProperties::slotRenderInformationChanged()
{
  fillStylesFromScene(mpScene);
  loadFromGlyph(mGlyphKey);
}

void CQElementProperties::slotSelectionChanged()
{
  if (!isVisible())
    return;

  QList< QGraphicsItem * > selection = mpScene->selectedItems();

for (auto * item : selection)
    {
      std::string key = TO_UTF8(item->data(COPASI_LAYOUT_KEY).toString());

      if (key.empty())
        continue;

      loadFromGlyph(key);
    }
}
