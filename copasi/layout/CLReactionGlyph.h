// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

LIBSBML_CPP_NAMESPACE_BEGIN
class SpeciesReferenceGlyph;
class ReactionGlyph;

#if LIBSBML_VERSION >= 50800
class ReferenceGlyph;
class GeneralGlyph;
#endif // LIBSBML_VERSION >= 50800
LIBSBML_CPP_NAMESPACE_END

class CLGlyphWithCurve : public CLGraphicalObject
{
protected:
  CLCurve mCurve;

  CLGlyphWithCurve(const CLGlyphWithCurve & src);

public:
  CLGlyphWithCurve(const std::string & name = "ReferenceGlyph",
                   const CCopasiContainer * pParent = NO_PARENT);

  CLGlyphWithCurve(const CLGlyphWithCurve & src,
                   const CCopasiContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLGlyphWithCurve(const GraphicalObject & sbml, //TODO preliminary
                   const std::map<std::string, std::string> & modelmap,
                   std::map<std::string, std::string> & layoutmap,
                   const CCopasiContainer * pParent = NO_PARENT);

  /**
   * assignment operator.
   */
  CLGlyphWithCurve & operator= (const CLGlyphWithCurve & rhs);

  const CLCurve & getCurve() const;

  CLCurve & getCurve();

  void setCurve(const CLCurve & c);

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

  CLReferenceGlyph(const CLReferenceGlyph & src);

public:
  static CLReferenceGlyph * create(const CData & data);

  CLReferenceGlyph(const std::string & name = "ReferenceGlyph",
                   const CCopasiContainer * pParent = NO_PARENT);

  CLReferenceGlyph(const CLReferenceGlyph & src,
                   const CCopasiContainer * pParent);

#if LIBSBML_VERSION >= 50800
  /**
   * constructor from libsbml object
   */
  CLReferenceGlyph(const ReferenceGlyph & sbml, //TODO preliminary
                   const std::map<std::string, std::string> & modelmap,
                   std::map<std::string, std::string> & layoutmap,
                   const CCopasiContainer * pParent = NO_PARENT);
#endif // LIBSBML_VERSION >= 50800

  /**
   * assignment operator.
   */
  CLReferenceGlyph & operator= (const CLReferenceGlyph & rhs);

  const std::string& getRole() const;

  void setRole(const std::string& r);

  const std::string & getTargetGlyphKey() const;

  CLGraphicalObject* getTargetGlyph() const;

  void setTargetGlyphKey(const std::string & k);

  virtual CLGraphicalObject* clone() const;

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

  /**
   * The role of the metab, as used for rendering, this is also used in SBML
   */
  Role mRole;

  /**
   * The role of the metab, logically. This may be used for automatic layout
   */
  Role mFunctionalRole;

protected:
  CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src);

public:
  static CLMetabReferenceGlyph * create(const CData & data);

  CLMetabReferenceGlyph(const std::string & name = "MetabReferenceGlyph",
                        const CCopasiContainer * pParent = NO_PARENT);

  CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
                        const CCopasiContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLMetabReferenceGlyph(const SpeciesReferenceGlyph & sbml,
                        const std::map<std::string, std::string> & modelmap,
                        std::map<std::string, std::string> & layoutmap,
                        const CCopasiContainer * pParent = NO_PARENT);

  /**
   * assignment operator.
   */
  CLMetabReferenceGlyph & operator= (const CLMetabReferenceGlyph & rhs);

  const std::string & getMetabGlyphKey() const;

  CLMetabGlyph* getMetabGlyph() const;

  void setMetabGlyphKey(const std::string & k);

  Role getRole() const;

  void setRole(Role r);

  Role getFunctionalRole() const;

  void setFunctionalRole(Role r);

  const std::string & getRoleDisplayName() const;

  virtual CLGraphicalObject* clone() const;

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
  CLGeneralGlyph(const CLGeneralGlyph & src);

public:
  static CLGeneralGlyph * create(const CData & data);

  CLGeneralGlyph(const std::string & name = "GeneralGlyph",
                 const CCopasiContainer * pParent = NO_PARENT);

  CLGeneralGlyph(const CLGeneralGlyph & src,
                 const CCopasiContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLGeneralGlyph(const GraphicalObject & sbml, //TODO
                 const std::map<std::string, std::string> & modelmap,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent = NO_PARENT);

//    CLGeneralGlyph(const ReactionGlyph & sbml, //TODO
//                   const std::map<std::string, std::string> & modelmap,
//                   std::map<std::string, std::string> & layoutmap,
//                   const CCopasiContainer * pParent = NO_PARENT);

  /**
   * assignment operator.
   * makes a deep copy
   */
  CLGeneralGlyph & operator= (const CLGeneralGlyph & rhs);

  const CCopasiVector<CLReferenceGlyph> & getListOfReferenceGlyphs() const;

  CCopasiVector<CLReferenceGlyph> & getListOfReferenceGlyphs();

  const CCopasiVector<CLGraphicalObject> & getListOfSubglyphs() const;

  CCopasiVector<CLGraphicalObject> & getListOfSubglyphs();

  /**
   *  add Glyph to general glyph. The general glyph takes ownership of the glyph.
   */
  void addReferenceGlyph(CLReferenceGlyph * glyph);

  /**
   *  add sub glyph to general glyph. The general glyph takes ownership of the glyph.
   */
  void addSubglyph(CLGraphicalObject * glyph);

  virtual void moveBy(const CLPoint &p);

  virtual CLGraphicalObject* clone() const;

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

  CLReactionGlyph(const CLReactionGlyph & src);

public:
  static CLReactionGlyph * create(const CData & data);

  CLReactionGlyph(const std::string & name = "ReactionGlyph",
                  const CCopasiContainer * pParent = NO_PARENT);

  CLReactionGlyph(const CLReactionGlyph & src,
                  const CCopasiContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLReactionGlyph(const ReactionGlyph & sbml,
                  const std::map<std::string, std::string> & modelmap,
                  std::map<std::string, std::string> & layoutmap,
                  const CCopasiContainer * pParent = NO_PARENT);

  /**
   * assignment operator.
   * makes a deep copy
   */
  CLReactionGlyph & operator= (const CLReactionGlyph & rhs);

  const CCopasiVector<CLMetabReferenceGlyph> & getListOfMetabReferenceGlyphs() const;

  CCopasiVector<CLMetabReferenceGlyph> & getListOfMetabReferenceGlyphs();

  /**
   *  add Glyph to reaction glyph. The reaction glyph takes ownership of the glyph.
   */
  void addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph);

  virtual void moveBy(const CLPoint &p);

  virtual CLGraphicalObject* clone() const;

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
