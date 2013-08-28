// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <layout/CLayoutState.h>

#include <layout/CLBase.h>
#include <layout/CLCurve.h>
#include <layout/CLayout.h>

void tagKey(CLGraphicalObject* element)
{
  element->setTag(element->getKey());
}

void CLayoutState::tagLayout(CLayout* layout)
{
  if (layout == NULL) return;

  CCopasiVector<CLGeneralGlyph> & general = layout->getListOfGeneralGlyphs();
  CCopasiVector<CLGeneralGlyph>::iterator generalIt = general.begin();

  while (generalIt != general.end())
    {
      tagKey((*generalIt));

      CCopasiVector<CLReferenceGlyph>::iterator refIt = (*generalIt)->getListOfReferenceGlyphs().begin();

      for (; refIt != (*generalIt)->getListOfReferenceGlyphs().end(); ++refIt)
        tagKey(*refIt);

      CCopasiVector<CLGraphicalObject>::iterator subIt = (*generalIt)->getListOfSubglyphs().begin();

      for (; subIt  != (*generalIt)->getListOfSubglyphs().end(); ++subIt)
        tagKey(*subIt);

      ++generalIt;
    }

  CCopasiVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  CCopasiVector<CLCompartmentGlyph>::iterator compIt = comps.begin();

  while (compIt != comps.end())
    {
      tagKey((*compIt));
      ++compIt;
    }

  CCopasiVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CCopasiVector<CLReactionGlyph>::iterator reactIt = reactions.begin();

  while (reactIt != reactions.end())
    {
      tagKey((*reactIt));

      CCopasiVector<CLMetabReferenceGlyph>::iterator refIt = (*reactIt)->getListOfMetabReferenceGlyphs().begin();

      for (; refIt != (*reactIt)->getListOfMetabReferenceGlyphs().end(); ++refIt)
        tagKey(*refIt);

      ++reactIt;
    }

  CCopasiVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  CCopasiVector<CLMetabGlyph>::iterator speciesIt = species.begin();

  while (speciesIt != species.end())
    {
      tagKey((*speciesIt));
      ++speciesIt;
    }

  CCopasiVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CCopasiVector<CLTextGlyph>::iterator textIt = texts .begin();

  while (textIt != texts .end())
    {
      tagKey((*textIt));
      ++textIt;
    }
}

CLayoutState::CLayoutState(const CLayout* layout)
  : mAdditionalState()
  , mCompartmentState()
  , mReactionState()
  , mSpeciesState()
  , mTextState()
  , mCurves()
{
  if (layout == NULL) return;

  const CCopasiVector<CLGeneralGlyph> & general = layout->getListOfGeneralGlyphs();
  CCopasiVector<CLGeneralGlyph>::const_iterator generalIt = general.begin();

  while (generalIt != general.end())
    {
      mAdditionalState[(*generalIt)->getTag()] = new CLBoundingBox((*generalIt)->getBoundingBox());
      ++generalIt;
    }

  const CCopasiVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  CCopasiVector<CLCompartmentGlyph>::const_iterator compIt = comps.begin();

  while (compIt != comps.end())
    {
      mCompartmentState[(*compIt)->getTag()] = new CLBoundingBox((*compIt)->getBoundingBox());
      ++compIt;
    }

  const CCopasiVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CCopasiVector<CLReactionGlyph>::const_iterator reactIt = reactions.begin();

  while (reactIt != reactions.end())
    {
      mReactionState[(*reactIt)->getTag()] = new CLBoundingBox((*reactIt)->getBoundingBox());

      mCurves[(*reactIt)->getTag()] = new CLCurve((*reactIt)->getCurve());

      CCopasiVector<CLMetabReferenceGlyph>::const_iterator refIt = (*reactIt)->getListOfMetabReferenceGlyphs().begin();

      for (; refIt != (*reactIt)->getListOfMetabReferenceGlyphs().end(); ++refIt)
        mCurves[(*refIt)->getTag()] = new CLCurve((*refIt)->getCurve());

      ++reactIt;
    }

  const CCopasiVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  CCopasiVector<CLMetabGlyph>::const_iterator speciesIt = species.begin();

  while (speciesIt != species.end())
    {
      mSpeciesState[(*speciesIt)->getTag()] = new CLBoundingBox((*speciesIt)->getBoundingBox());
      ++speciesIt;
    }

  const CCopasiVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CCopasiVector<CLTextGlyph>::const_iterator textIt = texts.begin();

  while (textIt != texts .end())
    {
      mTextState[(*textIt)->getTag()] = new CLBoundingBox((*textIt)->getBoundingBox());
      ++textIt;
    }
}

CLayoutState::~CLayoutState()
{
  std::map<std::string, CLBoundingBox*>::reverse_iterator it;

  for (it = mAdditionalState.rbegin(); it != mAdditionalState.rend(); ++it)
    {
      delete it->second;
    }

  for (it = mCompartmentState.rbegin(); it != mCompartmentState.rend(); ++it)
    {
      delete it->second;
    }

  for (it = mReactionState.rbegin(); it != mReactionState.rend(); ++it)
    {
      delete it->second;
    }

  for (it = mSpeciesState.rbegin(); it != mSpeciesState.rend(); ++it)
    {
      delete it->second;
    }

  for (it = mTextState.rbegin(); it != mTextState.rend(); ++it)
    {
      delete it->second;
    }

  std::map<std::string, CLCurve*>::reverse_iterator curveIt;

  for (curveIt = mCurves.rbegin(); curveIt != mCurves.rend(); ++curveIt)
    {
      delete curveIt->second;
    }
}

#define STATE_SET_POSITIONS(objectMap, it, endIt)\
  {\
    for (;it != endIt; ++it)\
      {\
        const std::string& key = ((*it)->getTag());\
        StringBoundMap::const_iterator boundIt = objectMap.find(key);\
        if (boundIt == objectMap.end()) \
          continue;    \
        CLBoundingBox* current = boundIt->second;\
        (*it)->setPosition(current->getPosition());\
      }\
  }

void CLayoutState::applyTo(CLayout *layout) const
{
  if (layout == NULL) return;

  CLayoutState current(layout);

  CCopasiVector<CLGeneralGlyph> & general = layout->getListOfGeneralGlyphs();
  CCopasiVector<CLGeneralGlyph>::iterator generalIt = general.begin();
  STATE_SET_POSITIONS(mAdditionalState, generalIt, general.end());

  CCopasiVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  CCopasiVector<CLCompartmentGlyph>::iterator compIt = comps.begin();
  STATE_SET_POSITIONS(mCompartmentState, compIt, comps.end());

  CCopasiVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CCopasiVector<CLReactionGlyph>::iterator reactIt = reactions.begin();
  STATE_SET_POSITIONS(mReactionState, reactIt, reactions.end());

  for (reactIt = reactions.begin(); reactIt != reactions.end(); ++reactIt)
    {
      const std::string& rkey = ((*reactIt)->getTag());
      StringCurveMap::const_iterator cIt = mCurves.find(rkey);

      if (cIt != mCurves.end())
        {
          CLCurve* current = cIt->second;
          (*reactIt)->setCurve(*current);
        }

      CCopasiVector<CLMetabReferenceGlyph>::iterator refIt = (*reactIt)->getListOfMetabReferenceGlyphs().begin();

      for (; refIt != (*reactIt)->getListOfMetabReferenceGlyphs().end(); ++refIt)
        {
          const std::string& key = ((*refIt)->getTag());
          cIt = mCurves.find(key);

          if (cIt == mCurves.end())
            continue;

          CLCurve* current = cIt->second;
          (*refIt)->setCurve(*current);
        }
    }

  CCopasiVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  CCopasiVector<CLMetabGlyph>::iterator speciesIt = species.begin();
  STATE_SET_POSITIONS(mSpeciesState, speciesIt, species.end());

  CCopasiVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CCopasiVector<CLTextGlyph>::iterator textIt = texts .begin();
  STATE_SET_POSITIONS(mTextState, textIt, texts.end());
}
