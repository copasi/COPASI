#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QPrinter>
#include <QImage>
#include <qgraphicseffect.h>

#include <copasi.h>

#include <qlayout/qlayoutscene.h>
#include <qlayout/qcopasieffect.h>
#include <qlayout/qlabelgraphicsitem.h>
#include <qlayout/qstyledgraphicsitem.h>
#include <qlayout/qconnectiongraphicsitem.h>
#include <qlayout/qrenderconverter.h>
#include <layout/CLayout.h>
#include <layout/CLGlyphs.h>
#include <layout/CLText.h>
#include <layout/CLReactionGlyph.h>
#include <layout/CLRenderResolver.h>
#include <layout/CLGlobalRenderInformation.h>
#include <layout/CListOfLayouts.h>
#include <layout/CLLocalRenderInformation.h>
#include <CopasiDataModel/CCopasiDataModel.h>

QLayoutScene::QLayoutScene(CLayout* layout, CCopasiDataModel* model, CLRenderInformationBase* renderInformation)
  : QGraphicsScene()
  , mpLayout(layout)
  , mpRender(renderInformation)
  , mpResolver(NULL)
{ 
  initializeResolver(model, renderInformation);  
}

void QLayoutScene::setLayout(CLayout *layout, CCopasiDataModel* model, CLRenderInformationBase* renderInformation)
{
  mpLayout = layout;  
  setRenderInformation(model, renderInformation);
}

void QLayoutScene::setRenderInformation(CCopasiDataModel* model, CLRenderInformationBase* renderInformation)
{
  initializeResolver(model, renderInformation);  
}

const CLayout* QLayoutScene::getCurrentLayout() const
{
  return mpLayout;
}

const CLRenderInformationBase* QLayoutScene::getCurrentRenderInfo() const
{
  return mpRender;
}


void QLayoutScene::saveToFile(const std::string& fileName, const std::string& fileType /*= "pdf"*/)
{
  if (fileType == "pdf")
  {
    QPrinter printer (QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName.c_str());            
    QPainter painter(&printer);
    painter.setRenderHints(
      QPainter::Antialiasing |QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
    render(&painter, QRect(), itemsBoundingRect());
    painter.end();
  }
  else
  {
    const int scale = 2;
    QImage image(QSize(width()*scale, height()*scale), QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setRenderHints(
      QPainter::Antialiasing |QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
    render(&painter, image.rect(), itemsBoundingRect());
    painter.end();
    image.save(fileName.c_str(), fileType.c_str());
  }
}

void QLayoutScene::initializeResolver(CCopasiDataModel* model, CLRenderInformationBase* renderInformation)
{
  if (model == NULL)
    return;

  if (renderInformation == NULL)
  {
    if (mpLayout != NULL && mpLayout->getListOfLocalRenderInformationObjects().size() > 0)
      mpRender = mpLayout->getListOfLocalRenderInformationObjects()[0];
    else if (model->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size() > 0)
      mpRender = model->getListOfLayouts()->getListOfGlobalRenderInformationObjects()[0];
  }
  else 
    mpRender = renderInformation;

  if (mpLayout == NULL || mpRender == NULL)
    return;

  CLLocalRenderInformation* local = dynamic_cast<CLLocalRenderInformation*>(mpRender);
  if (local != NULL)
    mpResolver = new CLRenderResolver(*local, mpLayout->getListOfLocalRenderInformationObjects(),   model->getListOfLayouts()->getListOfGlobalRenderInformationObjects());    
  else 
    mpResolver = new CLRenderResolver(*dynamic_cast<CLGlobalRenderInformation*>(mpRender), model->getListOfLayouts()->getListOfGlobalRenderInformationObjects());  

}

void QLayoutScene::setResolver(const CLRenderResolver* resolver)
{
  mpResolver = resolver;
}

const CLRenderResolver* QLayoutScene::getResolver() const
{
  return mpResolver;
}

QLayoutScene::~QLayoutScene()
{
}

void QLayoutScene::recreate()
{
  fillFromLayout(mpLayout);
  invalidate();
}

void QLayoutScene::addGlyph(const CLGraphicalObject* go)
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
     item = new QConnectionGraphicsItem(curveGlyph, 
       mpResolver == NULL ? NULL : mpResolver);         

  }
  else if (text != NULL)
  {        
    item = new QLabelGraphicsItem(text, mpResolver == NULL ? NULL : mpResolver);
  }
  else 
  {
    item = new QStyledGraphicsItem(go, mpResolver == NULL ? NULL : mpResolver);
  }

  if (item != NULL)
  {
    CCopasiObject* obj = go->getModelObject();
    if (obj != NULL && text == NULL)
    {
      item->setData(COPASI_OBJECT_CN, QString(obj->getCN().c_str()));      
      mItems[obj->getCN()]= item;
    }
    addItem(item);
  }
}
  
QGraphicsItem* QLayoutScene::getItemFor(const std::string& cn)
{
  return mItems[cn];
}

void QLayoutScene::fillFromLayout(const CLayout* layout)
{
  if (layout == NULL) return;
    
  clear();
  mItems.clear();

  if (mpRender != NULL && mpResolver != NULL)
  {
      QRenderConverter::setBackground(this, mpRender->getBackgroundColor(), mpResolver);
  }

  const CCopasiVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  CCopasiVector<CLCompartmentGlyph>::const_iterator itComp = comps.begin();
  while (itComp != comps.end())   
  {
    addGlyph(*itComp);
    ++itComp;
  }

  const CCopasiVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CCopasiVector<CLReactionGlyph>::const_iterator itReactions = reactions.begin();
  while (itReactions != reactions.end())   
  {
    addGlyph(*itReactions);
    ++itReactions;
  }
  
  const CCopasiVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  CCopasiVector<CLMetabGlyph>::const_iterator itSpecies = species.begin();
  while (itSpecies != species.end())   
  {
    addGlyph(*itSpecies);
    ++itSpecies;
  }
  
  const CCopasiVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CCopasiVector<CLTextGlyph>::const_iterator itTexts = texts.begin();
  while (itTexts != texts.end())   
  {
    addGlyph(*itTexts);
    ++itTexts;
  }

  const CCopasiVector<CLGeneralGlyph> & list = layout->getListOfGeneralGlyphs();
  CCopasiVector<CLGeneralGlyph>::const_iterator itList = list.begin();
  while (itList != list.end())   
  {
    addGlyph(*itList);
    ++itList;
  }
}

void QLayoutScene::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event )
{
	qDebug("dragLeaveEvent");
}
