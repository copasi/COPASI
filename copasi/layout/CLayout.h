// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLayout.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/16 00:08:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLAYOUT_H_
#define CLAYOUT_H_

#include <string>
//#include <vector>

#include "utilities/CCopasiVector.h"

#include "CLBase.h"
#include "CLGlyphs.h"
#include "CLReactionGlyph.h"

//#include "node.h"
//#include "reaction.h"
//#include "label.h"

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
    //vector<node*> nodePVec;
    //vector<reaction*> reactionPVec;
    //vector<label*> labelPVec;

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

    /*    CLayout(const CLDimensions & dim)
          :mDimensions(dim)
          {};*/

    /*    network(double w, double h, vector<node*> nPVec,vector<reaction*> rPVec,vector<label*> lPVec){
            width = w; height = h;
            nodePVec = vector<node*> (nPVec);
            reactionPVec = vector<reaction*> (rPVec);
            labelPVec = vector<label*>(lPVec);
            }*/

    //CLDimensions & dimensions() {return mDimensions;};
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

    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLayout & g);
    void print(std::ostream * ostream) const;

    /*    void setNodes(vector<node*> nPVec){nodePVec = vector<node*> (nPVec);}
        vector<node*> getNodes(){return nodePVec;}
        void setReactions(vector<reaction*> rPVec){reactionPVec = vector<reaction*> (rPVec);}
        vector<reaction*>getReactions(){return reactionPVec;}
        void setLabels(vector<label*> lPVec){labelPVec = vector<label*> (lPVec);}
        vector<label*> getLabels(){return labelPVec;}*/
  };

#endif
