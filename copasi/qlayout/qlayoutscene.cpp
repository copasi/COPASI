#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QPrinter>
#include <QImage>

#include <copasi.h>

#include <qlayout/qlayoutscene.h>
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
    QImage image(QSize(width(), height()), QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setRenderHints(
      QPainter::Antialiasing |QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
    render(&painter, QRect(), itemsBoundingRect());
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
  clear();
  fillFromLayout(mpLayout);
  QRenderConverter::setBackground(this, mpRender->getBackgroundColor(), mpResolver);
}

void QLayoutScene::addGlyph(const CLGraphicalObject* go)
{
  if (go == NULL) return;

  const CLGlyphWithCurve* curveGlyph = dynamic_cast<const CLGlyphWithCurve*>(go);
  const CLReactionGlyph* reaction = dynamic_cast<const CLReactionGlyph*>(go);
  const CLTextGlyph* text = dynamic_cast<const CLTextGlyph*>(go);
  const CLGeneralGlyph* general = dynamic_cast<const CLGeneralGlyph*>(go);
  if (curveGlyph != NULL)
  {
    if (curveGlyph->getCurve().getNumCurveSegments() > 0)
     addItem(new QConnectionGraphicsItem(curveGlyph, 
       mpResolver == NULL ? NULL : mpResolver));
      
    if (general != NULL)
    {        
      addItem(new QStyledGraphicsItem(general, 
        mpResolver == NULL ? NULL : mpResolver));      
    }

  }
  else if (text != NULL)
  {        
    addItem(new QLabelGraphicsItem(text, 
      mpResolver == NULL ? NULL : mpResolver));
  }
  else 
  {
    addItem(new QStyledGraphicsItem(go, 
      mpResolver == NULL ? NULL : mpResolver));    
  }

}
  
void QLayoutScene::fillFromLayout(const CLayout* layout)
{
  if (layout == NULL) return;

  const CCopasiVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  auto itComp = comps.begin();
  while (itComp != comps.end())   
  {
    addGlyph(*itComp);
    ++itComp;
  }

  const CCopasiVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  auto itReactions = reactions.begin();
  while (itReactions != reactions.end())   
  {
    addGlyph(*itReactions);
    ++itReactions;
  }
  
  const CCopasiVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  auto itSpecies = species.begin();
  while (itSpecies != species.end())   
  {
    addGlyph(*itSpecies);
    ++itSpecies;
  }
  
  const CCopasiVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  auto itTexts = texts.begin();
  while (itTexts != texts.end())   
  {
    addGlyph(*itTexts);
    ++itTexts;
  }

  const CCopasiVector<CLGeneralGlyph> & list = layout->getListOfGeneralGlyphs();
  auto itList = list.begin();
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
