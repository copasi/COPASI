// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QCoreApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QPrinter>
#include <QSvgGenerator>
#include <QImage>
#include <QGraphicsEffect>

#include "copasi/copasi.h"

#include "copasi/qlayout/CQLayoutScene.h"
#include "copasi/qlayout/CQCopasiEffect.h"
#include "copasi/qlayout/CQLabelGraphicsItem.h"
#include "copasi/qlayout/CQStyledGraphicsItem.h"
#include "copasi/qlayout/CQConnectionGraphicsItem.h"
#include "copasi/qlayout/CQRenderConverter.h"
#include "copasi/layout/CLayout.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLText.h"
#include "copasi/layout/CLReactionGlyph.h"
#include "copasi/layout/CLRenderResolver.h"
#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/layout/CLLocalRenderInformation.h"
#include "copasi/layout/CLDefaultStyles.h"
#include "copasi/layout/CCopasiSpringLayout.h"

#include <copasi/model/CModel.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CChemEq.h>
#include <copasi/utilities/CVersion.h>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

CQLayoutScene::CQLayoutScene(CLayout* layout, CDataModel* model, CLRenderInformationBase* renderInformation)
  : QGraphicsScene()
  , mpLayout(layout)
  , mpRender(renderInformation)
  , mpResolver(NULL)
{
  initializeResolver(model, renderInformation);
  connect(this, SIGNAL(recreateNeeded()), this, SLOT(recreate()), Qt::QueuedConnection);
}

void CQLayoutScene::setLayout(CLayout *layout, CDataModel* model, CLRenderInformationBase* renderInformation)
{
  mpLayout = layout;
  setRenderInformation(model, renderInformation);
}

void CQLayoutScene::setRenderInformation(CDataModel* model, CLRenderInformationBase* renderInformation)
{
  initializeResolver(model, renderInformation);
}

const CLayout* CQLayoutScene::getCurrentLayout() const
{
  return mpLayout;
}

CLayout* CQLayoutScene::getCurrentLayout()
{
  return mpLayout;
}

const CLRenderInformationBase* CQLayoutScene::getCurrentRenderInfo() const
{
  return mpRender;
}

void CQLayoutScene::saveToFile(const std::string& fileName, const std::string& fileType /*= "pdf"*/)
{
  if (fileType == "pdf")
    {
      QPrinter printer(QPrinter::HighResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setOutputFileName(fileName.c_str());
      QPainter painter(&printer);
      painter.setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
      render(&painter, QRect(), itemsBoundingRect());
      painter.end();
    }
  else if (fileType == "svg")
    {
      QRectF rect = itemsBoundingRect();
      QSvgGenerator generator;
      generator.setTitle(getCurrentLayout()->getObjectName().c_str());
      generator.setDescription(QString("Exported using COPASI: %1").arg(CVersion::VERSION.getVersion().c_str()));
      generator.setFileName(fileName.c_str());
      generator.setViewBox(rect);
      generator.setSize(QSize(rect.width(), rect.height()));
      QPainter painter;
      painter.begin(&generator);
      render(&painter);
      painter.end();
    }
  else
    {
      const int scale = 2;
      QImage image(QSize(width()*scale, height()*scale), QImage::Format_ARGB32);
      QPainter painter(&image);
      painter.setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
      render(&painter, image.rect(), itemsBoundingRect());
      painter.end();
      image.save(fileName.c_str(), fileType.c_str());
    }
}

void CQLayoutScene::initializeResolver(CDataModel* model, CLRenderInformationBase* renderInformation)
{
  if (model == NULL)
    return;

  if (renderInformation == NULL)
    {
      if (mpLayout != NULL && mpLayout->getListOfLocalRenderInformationObjects().size() > 0)
        mpRender = &mpLayout->getListOfLocalRenderInformationObjects()[0];
      else if (model->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size() > 0)
        mpRender = &model->getListOfLayouts()->getListOfGlobalRenderInformationObjects()[0];
      else
        mpRender = getDefaultStyle(0);
    }
  else
    mpRender = renderInformation;

  if (mpLayout == NULL || mpRender == NULL)
    return;

  CLLocalRenderInformation* local = dynamic_cast<CLLocalRenderInformation*>(mpRender);

  if (local != NULL)
    mpResolver = QSharedPointer<CLRenderResolver>(new CLRenderResolver(*local, mpLayout->getListOfLocalRenderInformationObjects(),   model->getListOfLayouts()->getListOfGlobalRenderInformationObjects()));
  else
    mpResolver = QSharedPointer<CLRenderResolver>(new CLRenderResolver(*dynamic_cast<CLGlobalRenderInformation*>(mpRender), model->getListOfLayouts()->getListOfGlobalRenderInformationObjects()));
}

void CQLayoutScene::setResolver(CLRenderResolver* resolver)
{
  mpResolver = QSharedPointer<CLRenderResolver>(resolver);
}

const CLRenderResolver* CQLayoutScene::getResolver() const
{
  return mpResolver.data();
}

CLRenderResolver * CQLayoutScene::getResolver()
{
  return mpResolver.data();
}

CQLayoutScene::~CQLayoutScene()
{
}

void CQLayoutScene::recreate()
{
  fillFromLayout(mpLayout);
  invalidate();
}

void CQLayoutScene::addGlyph(const CLGraphicalObject* go)
{
  if (go == NULL) return;

  const CLGlyphWithCurve* curveGlyph = dynamic_cast<const CLGlyphWithCurve*>(go);
  const CLReactionGlyph* reaction = dynamic_cast<const CLReactionGlyph*>(go);
  const CLTextGlyph* text = dynamic_cast<const CLTextGlyph*>(go);
  const CLGeneralGlyph* general = dynamic_cast<const CLGeneralGlyph*>(go);
  QGraphicsItem *item = NULL;

  if (curveGlyph != NULL)
    {
      if (curveGlyph->getCurve().getNumCurveSegments() > 0 || reaction != NULL || general != NULL)
        item = new CQConnectionGraphicsItem(curveGlyph,
                                            mpResolver == NULL ? NULL : mpResolver.data());
    }
  else if (text != NULL)
    {
      item = new CQLabelGraphicsItem(text, mpResolver == NULL ? NULL : mpResolver.data());
    }
  else
    {
      item = new CQStyledGraphicsItem(go, mpResolver == NULL ? NULL : mpResolver.data());
    }

  if (item != NULL && !dynamic_cast<CQCopasiGraphicsItem*>(item)->isValid())
    {
      delete item;
      item = NULL;
    }

  if (item != NULL)
    {
      CDataObject* obj = go->getModelObject();

      if (obj != NULL && text == NULL)
        {
          item->setData(COPASI_OBJECT_CN, QString(obj->getCN().c_str()));
          mItems[obj->getCN()] = item;
        }

      // if we have a z position, use it
      double z = go->getPosition().getZ();

      if (z == z && z != 0)
        item->setZValue(z);

      addItem(item);
    }

  if (general != NULL)
    {
      const CDataVector<CLGraphicalObject> & subGlyphs = general->getListOfSubglyphs();
      CDataVector<CLGraphicalObject>::const_iterator it = subGlyphs.begin();

      while (it != subGlyphs.end())
        {
          addGlyph(it);
          ++it;
        }
    }
}

QGraphicsItem* CQLayoutScene::getItemFor(const std::string& cn)
{
  return mItems[cn];
}

void CQLayoutScene::fillFromLayout(const CLayout* layout)
{
  if (layout == NULL) return;

  clear();
  mItems.clear();

  if (mpRender != NULL && mpResolver != NULL)
    {
      CQRenderConverter::setBackground(this, mpRender->getBackgroundColor(), mpResolver.data());
    }

  const CDataVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();

  CDataVector<CLCompartmentGlyph>::const_iterator itComp = comps.begin();

  while (itComp != comps.end())
    {
      addGlyph(itComp);
      ++itComp;
    }

  const CDataVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();

  CDataVector<CLReactionGlyph>::const_iterator itReactions = reactions.begin();

  while (itReactions != reactions.end())
    {
      addGlyph(itReactions);
      ++itReactions;
    }

  const CDataVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();

  CDataVector<CLMetabGlyph>::const_iterator itSpecies = species.begin();

  while (itSpecies != species.end())
    {
      addGlyph(itSpecies);
      ++itSpecies;
    }

  const CDataVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();

  CDataVector<CLTextGlyph>::const_iterator itTexts = texts.begin();

  while (itTexts != texts.end())
    {
      addGlyph(itTexts);
      ++itTexts;
    }

  const CDataVector<CLGeneralGlyph> & list = layout->getListOfGeneralGlyphs();

  CDataVector<CLGeneralGlyph>::const_iterator itList = list.begin();

  while (itList != list.end())
    {
      addGlyph(itList);
      ++itList;
    }
}

CLGraphicalObject* getTextForItem(const CLayout* layout, const CLGraphicalObject* obj)
{
  const CDataVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CDataVector<CLTextGlyph>::const_iterator it = texts.begin();

  while (it != texts.end())
    {
      if (it->getGraphicalObjectKey() == obj->getKey())
        return it.constCast();

      ++it;
    }

  return NULL;
}

CLGraphicalObject* getReactionGlyphForKey(const CLayout* layout, const std::string& key)
{
  const CDataVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CDataVector<CLReactionGlyph>::const_iterator it = reactions.begin();

  while (it != reactions.end())
    {
      if (it->getModelObjectKey() == key)
        return it.constCast();

      ++it;
    }

  return NULL;
}

CLGraphicalObject* getMetabGlyphForKey(const CLayout* layout, const CMetab* metab)
{
  const CDataVector<CLMetabGlyph> & metabs = layout->getListOfMetaboliteGlyphs();
  CDataVector<CLMetabGlyph>::const_iterator it = metabs.begin();

  while (it != metabs.end())
    {
      if (it->getModelObjectKey() == metab->getKey())
        return it.constCast();

      ++it;
    }

  return NULL;
}

void moveObject(CLGraphicalObject* obj, const CLPoint& delta, CLayout* layout)
{
  if (obj == NULL) return;

  CLReactionGlyph* pRG  = dynamic_cast<CLReactionGlyph*>(obj);

  if (pRG != NULL)
    {
      CLPoint position = pRG->getPosition();

      if (position.getX() == 0 && position.getY() == 0
          && pRG->getDimensions().getWidth() == 0
          && pRG->getDimensions().getHeight() == 0
          && pRG->getCurve().getNumCurveSegments() > 0)
        {
          position = pRG->getCurve().getCurveSegments()[0].getStart();
          pRG->setPosition(position);
        }
    }

  // move object
  obj->moveBy(delta);

  // move its label
  CLGraphicalObject* text = getTextForItem(layout, obj);

  if (text != NULL)
    text->moveBy(delta);

  // move species within compartments as well
  CLCompartmentGlyph* lcomp = dynamic_cast<CLCompartmentGlyph*>(obj);

  if (lcomp == NULL)
    return;

  CCompartment*  comp = dynamic_cast<CCompartment*>(lcomp ->getModelObject());

  if (comp == NULL)
    return;

  CDataVectorNS < CMetab > & metabs = comp->getMetabolites();
  CDataVectorNS < CMetab >::const_iterator it = metabs.begin();

  std::set<std::string> reactionKeys;

  while (it != metabs.end())
    {
      moveObject(getMetabGlyphForKey(layout, it), delta, layout);

      CDataVectorNS < CReaction > &  reactions = comp->getObjectDataModel()->getModel()->getReactions();
      CDataVectorNS < CReaction >::const_iterator rit = reactions.begin();

      for (; rit != reactions.end(); ++rit)
        {
          const CReaction* reaction = rit;
          const CChemEq& eqn = reaction->getChemEq();

          const std::set< const CCompartment * >& compartments = eqn.getCompartments();
          std::set< const CCompartment * >::const_iterator cit = compartments.begin();

          for (; cit != compartments.end(); ++cit)
            {
              if ((*cit)->getKey() == comp->getKey())
                reactionKeys.insert(reaction->getKey());
            }
        }

      ++it;
    }

  std::set<std::string>::const_iterator kit = reactionKeys.begin();

  for (; kit != reactionKeys.end(); ++kit)
    {
      moveObject(getReactionGlyphForKey(layout, (*kit)), delta, layout);
    }
}

void CQLayoutScene::updatePosition(const QString& key, const QPointF& newPos)
{
  CKeyFactory* kf = CRootContainer::getKeyFactory();

  if (kf == NULL) return;

  CLGraphicalObject* obj = dynamic_cast<CLGraphicalObject*>(kf->get(key.toStdString()));

  if (obj == NULL) return;

  CLPoint delta(newPos.x(), newPos.y());
  moveObject(obj, delta, mpLayout);

  // restore lines
  CCopasiSpringLayout::Parameters p;
  CCopasiSpringLayout l(mpLayout, &p);
  l.finalizeState();

  emit recreateNeeded();
}
