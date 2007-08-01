// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLayout.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/01 18:35:43 $
// End CVS Header

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

class Layout;

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
    CCopasiVector<CLGraphicalObject> mvGraphicalObjects;

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

    /**
     *  add Glyph to layout. The layout takes ownership of the glyph.
     */
    void addTextGlyph(CLTextGlyph * glyph);

    //*******************

    const CCopasiVector<CLGraphicalObject> & getListOfGraphicalObjects() const
      {return mvGraphicalObjects;};

    /**
     *  add Glyph to layout. The layout takes ownership of the glyph.
     */
    void addGraphicalObject(CLGraphicalObject * glyph);

    virtual void scale (const double & scaleFactor){this->mDimensions.scale(scaleFactor);}
    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLayout & g);
    void print(std::ostream * ostream) const;

    void exportToDotFile(std::ostream & os) const;

  protected:
    void writeDotNode(std::ostream & os, const std::string & id,
                      const std::string & label,
                      int t = 0) const;

    void writeDotEdge(std::ostream & os, const std::string & id1,
                      const std::string & id2,
                      int t = 0) const;
  };

#endif
