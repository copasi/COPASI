#include <QGraphicsScene>
#include <QGraphicsItem>

#include <copasi.h>

#include <qlayout/qlayoutscene.h>
#include <qlayout/qlabelgraphicsitem.h>
#include <qlayout/qstyledgraphicsitem.h>
#include <qlayout/qconnectiongraphicsitem.h>
#include <layout/CLayout.h>
#include <layout/CLGlyphs.h>
#include <layout/CLText.h>
#include <layout/CLReactionGlyph.h>
#include <layout/CLRenderResolver.h>


QLayoutScene::QLayoutScene(CLayout* layout)
  : QGraphicsScene()
  , mpLayout(layout)
{  
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
}

void QLayoutScene::addGlyph(const CLGraphicalObject* go)
{
  if (go == NULL) return;

  const CLGlyphWithCurve* curveGlyph = dynamic_cast<const CLGlyphWithCurve*>(go);
  const CLReactionGlyph* reaction = dynamic_cast<const CLReactionGlyph*>(go);
  const CLTextGlyph* text = dynamic_cast<const CLTextGlyph*>(go);
  if (curveGlyph != NULL)
  {
    addItem(new QConnectionGraphicsItem(curveGlyph, 
      mpResolver == NULL ? NULL : mpResolver));
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
}

void QLayoutScene::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event )
{
	qDebug("dragLeaveEvent");
}
