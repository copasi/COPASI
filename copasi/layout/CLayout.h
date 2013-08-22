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

#ifndef CLAYOUT_H_
#define CLAYOUT_H_

#include <string>

#include "utilities/CCopasiVector.h"

#include "CLBase.h"
#include "CLGlyphs.h"
#include "CLReactionGlyph.h"

#ifdef USE_CRENDER_EXTENSION
#include "copasi/layout/CLLocalRenderInformation.h"
#endif /* USE_CRENDER_EXTENSION */

#include <layout/CCopasiSpringLayout.h>

class Layout;
class CCompartment;
class CReaction;
class CMetab;

/**
 * This class describes a reaction network layout. Its structure
 * is exactly corresponding to the sbml layout extension
 */
class CLayout : public CLBase, public CCopasiContainer
{
protected:

  std::string mKey;

  CLDimensions mDimensions;

  CCopasiVector<CLCompartmentGlyph> mvCompartments;
  CCopasiVector<CLMetabGlyph> mvMetabs;
  CCopasiVector<CLReactionGlyph> mvReactions;
  CCopasiVector<CLTextGlyph> mvLabels;
  CCopasiVector<CLGeneralGlyph> mvGraphicalObjects;
#ifdef USE_CRENDER_EXTENSION
  CCopasiVector<CLLocalRenderInformation> mvLocalRenderInformationObjects;
#endif /* USE_CRENDER_EXTENSION */

public:

  CLayout(const std::string & name = "Layout",
          const CCopasiContainer * pParent = NULL);

  CLayout(const CLayout & src,
          const CCopasiContainer * pParent = NULL);

  /**
   * constructor from libsbml object.
   * Does not read the whole libsbml tree. Additional
   * work is done in SBMLDocumentLoader
   */
  CLayout(const Layout & sbml,
          std::map<std::string, std::string> & layoutmap,
          const CCopasiContainer * pParent = NULL);

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

  const CCopasiVector<CLCompartmentGlyph> & getListOfCompartmentGlyphs() const
  {return mvCompartments;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addCompartmentGlyph(CLCompartmentGlyph * glyph);

  //*******************

  const CCopasiVector<CLMetabGlyph> & getListOfMetaboliteGlyphs() const
  {return mvMetabs;};

  CCopasiVector<CLMetabGlyph> & getListOfMetaboliteGlyphs()
  {return mvMetabs;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addMetaboliteGlyph(CLMetabGlyph * glyph);

  //*******************

  const CCopasiVector<CLReactionGlyph> & getListOfReactionGlyphs() const
  {return mvReactions;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addReactionGlyph(CLReactionGlyph * glyph);

  //*******************

  const CCopasiVector<CLTextGlyph> & getListOfTextGlyphs() const
  {return mvLabels;};

  CCopasiVector<CLTextGlyph> & getListOfTextGlyphs()
  {return mvLabels;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addTextGlyph(CLTextGlyph * glyph);

  //*******************

  const CCopasiVector<CLGeneralGlyph> & getListOfGeneralGlyphs() const
  {return mvGraphicalObjects;};

  /**
   *  add Glyph to layout. The layout takes ownership of the glyph.
   */
  void addGeneralGlyph(CLGeneralGlyph * glyph);

#ifdef USE_CRENDER_EXTENSION
  //*******************

  /**
   * Returns a const reference to the list of local render information objects.
   */
  const CCopasiVector<CLLocalRenderInformation> & getListOfLocalRenderInformationObjects() const
  {return this->mvLocalRenderInformationObjects;};

  /**
   * Returns a reference to the list of local render information objects.
   */
  CCopasiVector<CLLocalRenderInformation> & getListOfLocalRenderInformationObjects()
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

#endif /* USE_CRENDER_EXTENSION */
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
  void exportToSBML(Layout * layout, const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                    std::map<std::string, const SBase*>& sbmlIDs
#ifdef USE_CRENDER_EXTENSION
                    , const std::map<std::string, std::string>& globalKeyToIdMap
                    //    ,const std::map<std::string,std::map<std::string,std::string> >& globalColorKeyToIdMapMap
                    //    ,const std::map<std::string,std::map<std::string,std::string> >& globalGradientKeyToIdMapMap
                    //    ,const std::map<std::string,std::map<std::string,std::string> >& globalLineEndingKeyToIdMapMap
#endif /* USE_CRENDER_EXTENSION */
                   ) const;

  /**
   * Randomizes the layout
   */
#ifdef COPASI_AUTOLAYOUT
  void randomize(CCopasiSpringLayout::Parameters* params = NULL);
  static CLayout* createLayout(
    CCopasiContainer* parent,
    const std::set<const CCompartment*>& compartments,
    const std::set<const CReaction*>& reactions,
    const std::set<const CMetab*>& metabs,
    const std::set<const CMetab*>& sideMetabs,
    CCopasiSpringLayout::Parameters* params = NULL
  );
#endif //COPASI_AUTOLAYOUT

protected:
  void writeDotNode(std::ostream & os, const std::string & id,
                    const std::string & label,
                    int t = 0) const;

  void writeDotEdge(std::ostream & os, const std::string & id1,
                    const std::string & id2,
                    int t = 0) const;
};

#endif
