// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include <copasi/layout/CLayoutState.h>

#include <copasi/layout/CLBase.h>
#include <copasi/layout/CLCurve.h>
#include <copasi/layout/CLayout.h>

void tagKey(CLGraphicalObject* element)
{
  element->setTag(element->getKey());
}

void CLayoutState::tagLayout(CLayout* layout)
{
  if (layout == NULL) return;

  CDataVector<CLGeneralGlyph> & general = layout->getListOfGeneralGlyphs();
  CDataVector<CLGeneralGlyph>::iterator generalIt = general.begin();

  while (generalIt != general.end())
    {
      tagKey(generalIt);

      CDataVector<CLReferenceGlyph>::iterator refIt = generalIt->getListOfReferenceGlyphs().begin();

      for (; refIt != generalIt->getListOfReferenceGlyphs().end(); ++refIt)
        tagKey(refIt);

      CDataVector<CLGraphicalObject>::iterator subIt = generalIt->getListOfSubglyphs().begin();

      for (; subIt  != generalIt->getListOfSubglyphs().end(); ++subIt)
        tagKey(subIt);

      ++generalIt;
    }

  CDataVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  CDataVector<CLCompartmentGlyph>::iterator compIt = comps.begin();

  while (compIt != comps.end())
    {
      tagKey(compIt);
      ++compIt;
    }

  CDataVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CDataVector<CLReactionGlyph>::iterator reactIt = reactions.begin();

  while (reactIt != reactions.end())
    {
      tagKey(reactIt);

      CDataVector<CLMetabReferenceGlyph>::iterator refIt = reactIt->getListOfMetabReferenceGlyphs().begin();

      for (; refIt != reactIt->getListOfMetabReferenceGlyphs().end(); ++refIt)
        tagKey(refIt);

      ++reactIt;
    }

  CDataVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  CDataVector<CLMetabGlyph>::iterator speciesIt = species.begin();

  while (speciesIt != species.end())
    {
      tagKey(speciesIt);
      ++speciesIt;
    }

  CDataVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CDataVector<CLTextGlyph>::iterator textIt = texts .begin();

  while (textIt != texts .end())
    {
      tagKey(textIt);
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

  const CDataVector<CLGeneralGlyph> & general = layout->getListOfGeneralGlyphs();
  CDataVector<CLGeneralGlyph>::const_iterator generalIt = general.begin();

  while (generalIt != general.end())
    {
      mAdditionalState[generalIt->getTag()] = new CLBoundingBox(generalIt->getBoundingBox());
      ++generalIt;
    }

  const CDataVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  CDataVector<CLCompartmentGlyph>::const_iterator compIt = comps.begin();

  while (compIt != comps.end())
    {
      mCompartmentState[compIt->getTag()] = new CLBoundingBox(compIt->getBoundingBox());
      ++compIt;
    }

  const CDataVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CDataVector<CLReactionGlyph>::const_iterator reactIt = reactions.begin();

  while (reactIt != reactions.end())
    {
      mReactionState[reactIt->getTag()] = new CLBoundingBox(reactIt->getBoundingBox());

      mCurves[reactIt->getTag()] = new CLCurve(reactIt->getCurve());

      CDataVector<CLMetabReferenceGlyph>::const_iterator refIt = reactIt->getListOfMetabReferenceGlyphs().begin();

      for (; refIt != reactIt->getListOfMetabReferenceGlyphs().end(); ++refIt)
        mCurves[refIt->getTag()] = new CLCurve(refIt->getCurve());

      ++reactIt;
    }

  const CDataVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  CDataVector<CLMetabGlyph>::const_iterator speciesIt = species.begin();

  while (speciesIt != species.end())
    {
      mSpeciesState[speciesIt->getTag()] = new CLBoundingBox(speciesIt->getBoundingBox());
      ++speciesIt;
    }

  const CDataVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CDataVector<CLTextGlyph>::const_iterator textIt = texts.begin();

  while (textIt != texts .end())
    {
      mTextState[textIt->getTag()] = new CLBoundingBox(textIt->getBoundingBox());
      ++textIt;
    }
}

CLayoutState::~CLayoutState()
{
  std::map<const std::string, CLBoundingBox*>::reverse_iterator it;

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

  std::map<const std::string, CLCurve*>::reverse_iterator curveIt;

  for (curveIt = mCurves.rbegin(); curveIt != mCurves.rend(); ++curveIt)
    {
      delete curveIt->second;
    }
}

#define STATE_SET_POSITIONS(objectMap, it, endIt)\
  {\
    for (;it != endIt; ++it)\
      {\
        const std::string& key = (it->getTag());\
        StringBoundMap::const_iterator boundIt = objectMap.find(key);\
        if (boundIt == objectMap.end()) \
          continue;    \
        CLBoundingBox* current = boundIt->second;\
        it->setPosition(current->getPosition());\
      }\
  }

void CLayoutState::applyTo(CLayout *layout) const
{
  if (layout == NULL) return;

  CLayoutState current(layout);

  CDataVector<CLGeneralGlyph> & general = layout->getListOfGeneralGlyphs();
  CDataVector<CLGeneralGlyph>::iterator generalIt = general.begin();
  STATE_SET_POSITIONS(mAdditionalState, generalIt, general.end());

  CDataVector<CLCompartmentGlyph> & comps = layout->getListOfCompartmentGlyphs();
  CDataVector<CLCompartmentGlyph>::iterator compIt = comps.begin();
  STATE_SET_POSITIONS(mCompartmentState, compIt, comps.end());

  CDataVector<CLReactionGlyph> & reactions = layout->getListOfReactionGlyphs();
  CDataVector<CLReactionGlyph>::iterator reactIt = reactions.begin();
  STATE_SET_POSITIONS(mReactionState, reactIt, reactions.end());

  for (reactIt = reactions.begin(); reactIt != reactions.end(); ++reactIt)
    {
      const std::string& rkey = (reactIt->getTag());
      StringCurveMap::const_iterator cIt = mCurves.find(rkey);

      if (cIt != mCurves.end())
        {
          CLCurve* current = cIt->second;
          reactIt->setCurve(*current);
        }

      CDataVector<CLMetabReferenceGlyph>::iterator refIt = reactIt->getListOfMetabReferenceGlyphs().begin();

      for (; refIt != reactIt->getListOfMetabReferenceGlyphs().end(); ++refIt)
        {
          const std::string& key = (refIt->getTag());
          cIt = mCurves.find(key);

          if (cIt == mCurves.end())
            continue;

          CLCurve* current = cIt->second;
          refIt->setCurve(*current);
        }
    }

  CDataVector<CLMetabGlyph> & species = layout->getListOfMetaboliteGlyphs();
  CDataVector<CLMetabGlyph>::iterator speciesIt = species.begin();
  STATE_SET_POSITIONS(mSpeciesState, speciesIt, species.end());

  CDataVector<CLTextGlyph> & texts = layout->getListOfTextGlyphs();
  CDataVector<CLTextGlyph>::iterator textIt = texts .begin();
  STATE_SET_POSITIONS(mTextState, textIt, texts.end());
}
