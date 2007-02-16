// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLReactionGlyph.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/16 10:13:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLREACG_H_
#define CLREACG_H_

//#include<string>
//#include"utils.h"

#include "utilities/CCopasiVector.h"

#include "CLCurve.h"
#include "CLGraphicalObject.h"
#include "CLGlyphs.h"

class SpeciesReferenceGlyph;
class ReactionGlyph;

/**
 * Graphical representation of a CChemEqElement. This correspondents to
 * the sbml SpeciesReferenceGlyph. The copasi equivalent is the CChemEqElement,
 * however it has no key, so it cannot be referred to.
 */
class CLMetabReferenceGlyph : public CLGraphicalObject
  {
  private:

    /**
     * Key of a CLMetabGlyph.
     */
    std::string mMetabGlyphKey;

    CLCurve mCurve;

  public:
    CLMetabReferenceGlyph(const std::string & name = "MetabReferenceGlyph",
                          const CCopasiContainer * pParent = NULL);

    CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
                          const CCopasiContainer * pParent = NULL);

    /**
     * constructor from libsbml object
     */
    CLMetabReferenceGlyph(const SpeciesReferenceGlyph & sbml,
                          const std::map<std::string, std::string> & modelmap,
                          std::map<std::string, std::string> & layoutmap,
                          const CCopasiContainer * pParent = NULL);

    const std::string & getMetabGlyphKey() const {return mMetabGlyphKey;};
    CLMetabGlyph* getMetabGlyph() const;
    void setMetabGlyphKey(const std::string & k) {mMetabGlyphKey = k;};

    const CLCurve & getCurve() const {return mCurve;};
    CLCurve & getCurve() {return mCurve;};
    void setCurve(const CLCurve & c) {mCurve = c;};

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g);
  };

/**
 * Graphical representation of a reaction
 */
class CLReactionGlyph : public CLGraphicalObject
  {
  private:
    CCopasiVector<CLMetabReferenceGlyph> mvMetabReferences;

  public:
    CLReactionGlyph(const std::string & name = "MetabGlyph",
                    const CCopasiContainer * pParent = NULL);

    CLReactionGlyph(const CLReactionGlyph & src,
                    const CCopasiContainer * pParent = NULL);

    /**
     * constructor from libsbml object
     */
    CLReactionGlyph(const ReactionGlyph & sbml,
                    const std::map<std::string, std::string> & modelmap,
                    std::map<std::string, std::string> & layoutmap,
                    const CCopasiContainer * pParent = NULL);

    const CCopasiVector<CLMetabReferenceGlyph> & getListOfMetabReferenceGlyphs() const
      {return mvMetabReferences;};

    /**
     *  add Glyph to layout. The layout takes ownership of the glyph.
     */
    void addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph);

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g);
  };

#endif
