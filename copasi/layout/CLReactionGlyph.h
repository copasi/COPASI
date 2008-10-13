// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLReactionGlyph.h,v $
//   $Revision: 1.13.2.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/13 15:36:52 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLREACG_H_
#define CLREACG_H_

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
  public:

    /**
     * Enum type for the role of the metab reference
     * This enum must be synchronized with the corresponding
     * enum in libsbml (sbml/layout/SpeciesReferenceRole.h)
     */
    enum Role
    {
      UNDEFINED,
      SUBSTRATE,
      PRODUCT,
      SIDESUBSTRATE,
      SIDEPRODUCT,
      MODIFIER,
      ACTIVATOR,
      INHIBITOR
    };

    /**
     * String literals for the GUI to display the role of
     * a metab reference
     */
    static const std::string RoleName[];

    /**
     * XML type names of the roles. This is used in the xml
     * importer and exporter
     */
    static const std::string XMLRole[];

  private:

    /**
     * Key of a CLMetabGlyph.
     */
    std::string mMetabGlyphKey;

    CLCurve mCurve;

    Role mRole;

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

    /**
     * assignment operator.
     */
    CLMetabReferenceGlyph & operator= (const CLMetabReferenceGlyph & rhs);

    const std::string & getMetabGlyphKey() const {return mMetabGlyphKey;};
    CLMetabGlyph* getMetabGlyph() const;
    void setMetabGlyphKey(const std::string & k) {mMetabGlyphKey = k;};

    const CLCurve & getCurve() const {return mCurve;};
    CLCurve & getCurve() {return mCurve;};
    void setCurve(const CLCurve & c) {mCurve = c;};

    const Role & getRole() const {return mRole;};
    Role & getRole() {return mRole;};
    void setRole(const Role & r) {mRole = r;};

    const std::string & getRoleDisplayName() const
      {return RoleName[mRole];};

    /**
     * This method writes the information of the copasi layout object into the
     * corresponding sbml object
     * layoutmap contains a map from copasi layout objects to libsbml layout objects.
     * this is needed for resolving the reference to the metab glyph.
     */
    virtual void exportToSBML(SpeciesReferenceGlyph * g,
                              const std::map<CCopasiObject*, SBase*> & copasimodelmap,
                              std::map<std::string, const SBase*>& sbmlIDs,
                              const std::map<const CLBase*, const SBase*> layoutmap) const;

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g);
    void print(std::ostream * ostream) const;
  };

/**
 * Graphical representation of a reaction
 */
class CLReactionGlyph : public CLGraphicalObject
  {
  private:
    CLCurve mCurve;

    CCopasiVector<CLMetabReferenceGlyph> mvMetabReferences;

  public:
    CLReactionGlyph(const std::string & name = "ReactionGlyph",
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

    /**
     * assignment operator.
     * makes a deep copy
     */
    CLReactionGlyph & operator= (const CLReactionGlyph & rhs);

    const CCopasiVector<CLMetabReferenceGlyph> & getListOfMetabReferenceGlyphs() const
      {return mvMetabReferences;};

    /**
     *  add Glyph to reaction glyph. The reaction glyph takes ownership of the glyph.
     */
    void addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph);

    const CLCurve & getCurve() const {return mCurve;};
    CLCurve & getCurve() {return mCurve;};
    void setCurve(const CLCurve & c) {mCurve = c;};

    /**
     * This method writes the information of the copasi layout object into the
     * corresponding sbml object
     * layoutmap contains a map from copasi layout objects to libsbml layout objects.
     * the exported metab reference glyphs will be added.
     */
    virtual void exportToSBML(ReactionGlyph * g,
                              const std::map<CCopasiObject*, SBase*> & copasimodelmap,
                              std::map<std::string, const SBase*>& sbmlIDs,
                              std::map<const CLBase*, const SBase*> layoutmap) const;

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g);
    void print(std::ostream * ostream) const;
  };

#endif
