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

#ifndef CLAYOUT_H_
#define CLAYOUT_H_

#include <string>

#include "copasi/core/CDataVector.h"

#include "CLBase.h"
#include "CLGlyphs.h"
#include "CLReactionGlyph.h"

#include "copasi/layout/CLLocalRenderInformation.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class Layout;
LIBSBML_CPP_NAMESPACE_END

/**
 * This class describes a reaction network layout. Its structure
 * is exactly corresponding to the sbml layout extension
 */
class CLayout : public CLBase, public CDataContainer
{
protected:

  std::string mKey;

  CLDimensions mDimensions;

  CDataVector<CLCompartmentGlyph> mvCompartments;
  CDataVector<CLMetabGlyph> mvMetabs;
  CDataVector<CLReactionGlyph> mvReactions;
  CDataVector<CLTextGlyph> mvLabels;
  CDataVector<CLGeneralGlyph> mvGraphicalObjects;
  CDataVector<CLLocalRenderInformation> mvLocalRenderInformationObjects;

  CLayout(const CLayout & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLayout * pDataObject
   */
  static CLayout * fromData(const CData & data, CUndoObjectInterface * pParent);

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

  CLayout(const std::string & name = "Layout",
          const CDataContainer * pParent = NO_PARENT);

  CLayout(const CLayout & src,
          const CDataContainer * pParent);

  /**
   * constructor from libsbml object.
   * Does not read the whole libsbml tree. Additional
   * work is done in SBMLDocumentLoader
   */
  CLayout(const Layout & sbml,
          std::map<std::string, std::string> & layoutmap,
          const CDataContainer * pParent = NO_PARENT);

  ~CLayout();

  /**
   *  Retrieves the key of the layout
   */
  virtual const std::string & getKey() const
  {return mKey;};

  virtual void moveBy(const CLPoint &p);

  const CLDimensions & getDimensions() const {return mDimensions;};
  void setDimensions(const CLDimensions & d) {mDimensions = d;};

  //*******************

  const CDataVector<CLCompartmentGlyph> & getListOfCompartmentGlyphs() const
  {return mvCompartments;};

  CDataVector<CLCompartmentGlyph> & getListOfCompartmentGlyphs()
  {return mvCompartments;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addCompartmentGlyph(CLCompartmentGlyph * glyph);

  //*******************

  const CDataVector<CLMetabGlyph> & getListOfMetaboliteGlyphs() const
  {return mvMetabs;};

  CDataVector<CLMetabGlyph> & getListOfMetaboliteGlyphs()
  {return mvMetabs;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addMetaboliteGlyph(CLMetabGlyph * glyph);

  //*******************

  const CDataVector<CLReactionGlyph> & getListOfReactionGlyphs() const
  {return mvReactions;};

  CDataVector<CLReactionGlyph> & getListOfReactionGlyphs()
  {return mvReactions;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addReactionGlyph(CLReactionGlyph * glyph);

  //*******************

  const CDataVector<CLTextGlyph> & getListOfTextGlyphs() const
  {return mvLabels;};

  CDataVector<CLTextGlyph> & getListOfTextGlyphs()
  {return mvLabels;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addTextGlyph(CLTextGlyph * glyph);

  //*******************

  const CDataVector<CLGeneralGlyph> & getListOfGeneralGlyphs() const
  {return mvGraphicalObjects;};

  CDataVector<CLGeneralGlyph> & getListOfGeneralGlyphs()
  {return mvGraphicalObjects;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addGeneralGlyph(CLGeneralGlyph * glyph);

  //*******************

  /**
   * Returns a const reference to the list of local render information objects.
   */
  const CDataVector<CLLocalRenderInformation> & getListOfLocalRenderInformationObjects() const
  {return this->mvLocalRenderInformationObjects;};

  /**
   * Returns a reference to the list of local render information objects.
   */
  CDataVector<CLLocalRenderInformation> & getListOfLocalRenderInformationObjects()
  {return this->mvLocalRenderInformationObjects;};

  /**
   * Returns a const pointer to the local render information with the given index or NULL
   * if the index is invalid.
   */
  const CLLocalRenderInformation* getRenderInformation(size_t index) const;

  /**
   * Returns a pointer to the local render information with the given index or NULL
   * if the index is invalid.
   */
  CLLocalRenderInformation* getRenderInformation(size_t index);

  /**
   *  add local render information to layout. The layout takes ownership of the object.
   */
  void addLocalRenderInformation(CLLocalRenderInformation* pRenderInfo);

  /**
   * This methods calculates the bounding box of the layout.
   * It traverses all layout objects and looks for the minimal and maximal x
   * and y values that occur in the layout.
   * These values are returned in the form of a bounding box where the minimal
   * values are stored in the position and the maxima are given as the minimal
   * values plus the corresponding dimension.
   */
  CLBoundingBox calculateBoundingBox() const;

  /**
   * Calculates the Bounding Box, moves the layout to the origin and assigns it to the layout.
   */
  void calculateAndAssignBounds();

  virtual void scale(const double & scaleFactor) {this->mDimensions.scale(scaleFactor);}
  /**
    * insert operator
    */
  friend std::ostream & operator<<(std::ostream &os, const CLayout & g);
  void print(std::ostream * ostream) const;

  void exportToDotFile(std::ostream & os) const;

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object
   */
  void exportToSBML(Layout * layout, const std::map<const CDataObject*, SBase*> & copasimodelmap,
                    std::map<std::string, const SBase*>& sbmlIDs
                    , const std::map<std::string, std::string>& globalKeyToIdMap
                   ) const;

protected:
  void writeDotNode(std::ostream & os, const std::string & id,
                    const std::string & label,
                    int t = 0) const;

  void writeDotEdge(std::ostream & os, const std::string & id1,
                    const std::string & id2,
                    int t = 0) const;
};

#endif
