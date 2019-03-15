// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CLMETABG_H_
#define CLMETABG_H_

//#include<string>
//#include"utils.h"

#include "CLGraphicalObject.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class SpeciesGlyph;
class CompartmentGlyph;
class TextGlyph;
LIBSBML_CPP_NAMESPACE_END

/**
 * Graphical representation of a metabolite
 */
class CLMetabGlyph : public CLGraphicalObject
{
protected:
  CLMetabGlyph(const CLMetabGlyph & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLMetabGlyph * pDataObject
   */
  static CLMetabGlyph * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  CLMetabGlyph(const std::string & name = "MetabGlyph",
               const CDataContainer * pParent = NO_PARENT);

  CLMetabGlyph(const CLMetabGlyph & src,
               const CDataContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLMetabGlyph(const SpeciesGlyph & sbml,
               const std::map<std::string, std::string> & modelmap,
               std::map<std::string, std::string> & layoutmap,
               const CDataContainer * pParent = NO_PARENT);

  /**
   * assignment operator
   */
  CLMetabGlyph & operator= (const CLMetabGlyph & rhs);

  //virtual void scale (const double & scaleFactor){this->mBBox.scale(scaleFactor);}

  virtual CLGraphicalObject* clone() const {return new CLMetabGlyph(*this, NULL);};

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object
   */
  virtual void exportToSBML(SpeciesGlyph * g,
                            const std::map<const CDataObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs) const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLMetabGlyph & g);
  void print(std::ostream * ostream) const;
};

/**
 * Graphical representation of a compartment
 */
class CLCompartmentGlyph : public CLGraphicalObject
{
protected:
  CLCompartmentGlyph(const CLCompartmentGlyph & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLCompartmentGlyph * pDataObject
   */
  static CLCompartmentGlyph * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  CLCompartmentGlyph(const std::string & name = "CompartmentGlyph",
                     const CDataContainer * pParent = NO_PARENT);

  CLCompartmentGlyph(const CLCompartmentGlyph & src,
                     const CDataContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLCompartmentGlyph(const CompartmentGlyph & sbml,
                     const std::map<std::string, std::string> & modelmap,
                     std::map<std::string, std::string> & layoutmap,
                     const CDataContainer * pParent = NO_PARENT);

  //virtual void scale (const double & scaleFactor){this->mBBox.scale(scaleFactor);}

  /**
   * assignment operator
   */
  CLCompartmentGlyph & operator= (const CLCompartmentGlyph & rhs);

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLCompartmentGlyph & g);
  void print(std::ostream * ostream) const;

  virtual CLGraphicalObject* clone() const {return new CLCompartmentGlyph(*this, NULL);};

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object
   */
  virtual void exportToSBML(CompartmentGlyph * cg,
                            const std::map<const CDataObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs) const;
};

/**
 * Graphical representation of a Label
 */
class CLTextGlyph : public CLGraphicalObject
{
protected:

  /**
   * indicates if a text is set. If the text is not set the
   * label text is taken from the model object.
   */
  bool mIsTextSet;
  std::string mText;

  /**
   * Key of a layout element. If this is set the text glyph is
   * considered to be a label to this layout element.
   */
  std::string mGraphicalObjectKey;

  CLTextGlyph(const CLTextGlyph & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLTextGlyph * pDataObject
   */
  static CLTextGlyph * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  CLTextGlyph(const std::string & name = "TextGlyph",
              const CDataContainer * pParent = NO_PARENT);

  CLTextGlyph(const CLTextGlyph & src,
              const CDataContainer * pParent);

  /**
   * constructor from libsbml object
   */
  CLTextGlyph(const TextGlyph & sbml,
              const std::map<std::string, std::string> & modelmap,
              std::map<std::string, std::string> & layoutmap,
              const CDataContainer * pParent = NO_PARENT);

  /**
   * assignment operator.
   */
  CLTextGlyph & operator= (const CLTextGlyph & rhs);

  virtual std::string getText() const;

  void setText(const std::string & t);

  void clearText();

  bool isTextSet() const {return mIsTextSet;};

  const std::string & getGraphicalObjectKey() const {return mGraphicalObjectKey;};
  CLGraphicalObject* getGraphicalObject() const;
  void setGraphicalObjectKey(const std::string & k);

  virtual CLGraphicalObject* clone() const {return new CLTextGlyph(*this, NULL);};

  //virtual void scale (const double & scaleFactor){this->mBBox.scale(scaleFactor);}

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object.
   * The reference to other graphical objects cannot be done in this method
   * since when this method is called not necessarily all other graphical objects
   * have been created.
   */
  virtual void exportToSBML(TextGlyph * g,
                            const std::map<const CDataObject*, SBase*> & copasimodelmap,
                            std::map<std::string, const SBase*>& sbmlIDs) const;

  /**
   * handle the reference to another graphical object for sbml export.
   * This should only be called after all other graphical objects are in the
   * layout map.
   */
  void exportReferenceToSBML(TextGlyph * g, const std::map<const CLBase*, const SBase*> & layoutmap) const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLTextGlyph & g);
  void print(std::ostream * ostream) const;
};

#endif
