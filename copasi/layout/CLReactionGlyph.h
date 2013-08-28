// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLREACG_H_
#define CLREACG_H_

#include "sbml/common/libsbml-version.h"
#include "utilities/CCopasiVector.h"

#include "CLCurve.h"
#include "CLGraphicalObject.h"
#include "CLGlyphs.h"

class SpeciesReferenceGlyph;
class ReactionGlyph;

#if LIBSBML_VERSION >= 50800
class ReferenceGlyph;
class GeneralGlyph;
#endif // LIBSBML_VERSION >= 50800

class CLGlyphWithCurve : public CLGraphicalObject
{
protected:
  CLCurve mCurve;

public:
  CLGlyphWithCurve(const std::string & name = "ReferenceGlyph",
                   const CCopasiContainer * pParent = NULL);

  CLGlyphWithCurve(const CLGlyphWithCurve & src,
                   const CCopasiContainer * pParent = NULL);

  /**
   * constructor from libsbml object
   */
  CLGlyphWithCurve(const GraphicalObject & sbml, //TODO preliminary
                   const std::map<std::string, std::string> & modelmap,
                   std::map<std::string, std::string> & layoutmap,
                   const CCopasiContainer * pParent = NULL);

  /**
   * assignment operator.
   */
  CLGlyphWithCurve & operator= (const CLGlyphWithCurve & rhs);

  const CLCurve & getCurve() const {return mCurve;};
  CLCurve & getCurve() {return mCurve;};
  void setCurve(const CLCurve & c) {mCurve = c;};

  virtual void moveBy(const CLPoint &p);

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLGlyphWithCurve & g);
  void print(std::ostream * ostream) const;
};

/**
 * Graphical representation of a Link between different Glyphs. This correspondents to
 * the sbml ReferenceGlyph.
 */
class CLReferenceGlyph : public CLGlyphWithCurve
{
protected:

  /**
   * Key of a Glyph.
   */
  std::string mGlyphKey;
  std::string mRole;

public:
  CLReferenceGlyph(const std::string & name = "ReferenceGlyph",
                   const CCopasiContainer * pParent = NULL);

  CLReferenceGlyph(const CLReferenceGlyph & src,
                   const CCopasiContainer * pParent = NULL);

#if LIBSBML_VERSION >= 50800
  /**
   * constructor from libsbml object
   */
  CLReferenceGlyph(const ReferenceGlyph & sbml, //TODO preliminary
                   const std::map<std::string, std::string> & modelmap,
                   std::map<std::string, std::string> & layoutmap,
                   const CCopasiContainer * pParent = NULL);
#endif // LIBSBML_VERSION >= 50800

  /**
   * assignment operator.
   */
  CLReferenceGlyph & operator= (const CLReferenceGlyph & rhs);

  const std::string& getRole() const {return mRole;}
  void setRole(const std::string& r) {mRole = r;}

  const std::string & getTargetGlyphKey() const {return mGlyphKey;}
  CLGraphicalObject* getTargetGlyph() const;
  void setTargetGlyphKey(const std::string & k) {mGlyphKey = k;}

  virtual CLGraphicalObject* clone() const {return new CLReferenceGlyph(*this, NULL);};

#if LIBSBML_VERSION >= 50800
  /**
   * This method writes the information of the COPASI layout object into the
   * corresponding SBML object
   * layoutmap contains a map from COPASI layout objects to libsbml layout objects.
   * this is needed for resolving the reference to the metab glyph.
   */
  virtual void exportToSBML(ReferenceGlyph * g, //TODO
                            const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs,
                            const std::map<const CLBase*, const SBase*> & layoutmap) const;
#endif // LIBSBML_VERSION >= 50800

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLReferenceGlyph & g);
  void print(std::ostream * ostream) const;
};

/**
 * Graphical representation of a CChemEqElement. This correspondents to
 * the sbml SpeciesReferenceGlyph. The copasi equivalent is the CChemEqElement,
 * however it has no key, so it cannot be referred to.
 */
class CLMetabReferenceGlyph : public CLGlyphWithCurve
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
   * XML type names of the roles. This is used in the XML
   * importer and exporter
   */
  static const std::string XMLRole[];

private:
  /**
   * Key of a CLMetabGlyph.
   */
  std::string mMetabGlyphKey;

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

  Role getRole() const {return mRole;};
  void setRole(Role r) {mRole = r;};

  const std::string & getRoleDisplayName() const
  {return RoleName[mRole];};

  virtual CLGraphicalObject* clone() const {return new CLMetabReferenceGlyph(*this, NULL);};

  /**
   * This method writes the information of the COPASI layout object into the
   * corresponding SBML object
   * layoutmap contains a map from COPASI layout objects to libsbml layout objects.
   * this is needed for resolving the reference to the metab glyph.
   */
  virtual void exportToSBML(SpeciesReferenceGlyph * g,
                            const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs,
                            const std::map<const CLBase*, const SBase*> & layoutmap) const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g);
  void print(std::ostream * ostream) const;
};

/**
 * general glyph
 */
class CLGeneralGlyph : public CLGlyphWithCurve
{
protected:
  CCopasiVector<CLReferenceGlyph> mvReferences;
  CCopasiVector<CLGraphicalObject> mvSubglyphs;

public:
  CLGeneralGlyph(const std::string & name = "GeneralGlyph",
                 const CCopasiContainer * pParent = NULL);

  CLGeneralGlyph(const CLGeneralGlyph & src,
                 const CCopasiContainer * pParent = NULL);

  /**
   * constructor from libsbml object
   */
  CLGeneralGlyph(const GraphicalObject & sbml, //TODO
                 const std::map<std::string, std::string> & modelmap,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent = NULL);

//    CLGeneralGlyph(const ReactionGlyph & sbml, //TODO
//                   const std::map<std::string, std::string> & modelmap,
//                   std::map<std::string, std::string> & layoutmap,
//                   const CCopasiContainer * pParent = NULL);

  /**
   * assignment operator.
   * makes a deep copy
   */
  CLGeneralGlyph & operator= (const CLGeneralGlyph & rhs);

  const CCopasiVector<CLReferenceGlyph> & getListOfReferenceGlyphs() const
  {return mvReferences;};

  CCopasiVector<CLReferenceGlyph> & getListOfReferenceGlyphs()
  {return mvReferences;};

  const CCopasiVector<CLGraphicalObject> & getListOfSubglyphs() const
  {return mvSubglyphs;};

  CCopasiVector<CLGraphicalObject> & getListOfSubglyphs()
  {return mvSubglyphs;};

  /**
   *  add Glyph to general glyph. The general glyph takes ownership of the glyph.
   */
  void addReferenceGlyph(CLReferenceGlyph * glyph);

  /**
   *  add sub glyph to general glyph. The general glyph takes ownership of the glyph.
   */
  void addSubglyph(CLGraphicalObject * glyph);

  virtual void moveBy(const CLPoint &p);

  virtual CLGraphicalObject* clone() const {return new CLGeneralGlyph(*this, NULL);};

  /**
   * this exports the general glyph to a generic SBML GraphicalObject (throwing away most of the information)
   * This should be removed once libsbml supports general glyphs.
   */
  virtual void exportToSBML(GraphicalObject * g,
                            const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs,
                            std::map<const CLBase*, const SBase*> & layoutmap) const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLGeneralGlyph & g);
  void print(std::ostream * ostream) const;
};

/**
 * Graphical representation of a reaction
 */
class CLReactionGlyph : public CLGlyphWithCurve
{
protected:
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

  CCopasiVector<CLMetabReferenceGlyph> & getListOfMetabReferenceGlyphs()
  {return mvMetabReferences;};

  /**
   *  add Glyph to reaction glyph. The reaction glyph takes ownership of the glyph.
   */
  void addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph);

  virtual void moveBy(const CLPoint &p);

  virtual CLGraphicalObject* clone() const {return new CLReactionGlyph(*this, NULL);};
  /**
   * This method writes the information of the COPASI layout object into the
   * corresponding SBML object
   * layoutmap contains a map from COPASI layout objects to libsbml layout objects.
   * the exported metab reference glyphs will be added.
   */
  virtual void exportToSBML(ReactionGlyph * g,
                            const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs,
                            std::map<const CLBase*, const SBase*> & layoutmap) const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g);
  void print(std::ostream * ostream) const;
};

#endif
