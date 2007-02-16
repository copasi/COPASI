// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGlyphs.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/16 00:09:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLMETABG_H_
#define CLMETABG_H_

//#include<string>
//#include"utils.h"

#include "CLGraphicalObject.h"

class SpeciesGlyph;
class CompartmentGlyph;
class TextGlyph;

/**
 * Graphical representation of a metabolite
 */
class CLMetabGlyph : public CLGraphicalObject
  {
  public:
    CLMetabGlyph(const std::string & name = "MetabGlyph",
                 const CCopasiContainer * pParent = NULL);

    CLMetabGlyph(const CLMetabGlyph & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     * constructor from libsbml object
     */
    CLMetabGlyph(const SpeciesGlyph & sbml,
                 const std::map<std::string, std::string> & modelmap,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent = NULL);

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CLMetabGlyph & g);

    //          (double a, double b) {id = utils::createID("nd_");x=a;y=b;}
    //node (){id = "empty"; x=0.0;y=0.0;} // no unique id when using empty constructor
    //~node(){utils::removeID("nd_",id);}

    //string getID(){return id;}
    //bool hasID(string);
    //bool hasID();
    //void printObject();
    //void markAsCopy();
  };

/**
 * Graphical representation of a compartment
 */
class CLCompartmentGlyph : public CLGraphicalObject
  {
  public:
    CLCompartmentGlyph(const std::string & name = "CompartmentGlyph",
                       const CCopasiContainer * pParent = NULL);

    CLCompartmentGlyph(const CLCompartmentGlyph & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     * constructor from libsbml object
     */
    CLCompartmentGlyph(const CompartmentGlyph & sbml,
                       const std::map<std::string, std::string> & modelmap,
                       std::map<std::string, std::string> & layoutmap,
                       const CCopasiContainer * pParent = NULL);

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CLCompartmentGlyph & g);
  };

/**
 * Graphical representation of a Label
 */
class CLTextGlyph : public CLGraphicalObject
  {
  private:

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

  public:
    CLTextGlyph(const std::string & name = "TextGlyph",
                const CCopasiContainer * pParent = NULL);

    CLTextGlyph(const CLTextGlyph & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * constructor from libsbml object
     */
    CLTextGlyph(const TextGlyph & sbml,
                const std::map<std::string, std::string> & modelmap,
                std::map<std::string, std::string> & layoutmap,
                const CCopasiContainer * pParent = NULL);

    std::string text() const;

    void setText(const std::string & t);

    void clearText();

    bool isTextSet() const {return mIsTextSet;};

    const std::string & getGraphicalObjectKey() const {return mGraphicalObjectKey;};
    CLGraphicalObject* getGraphicalObject() const;
    void setGraphicalObjectKey(const std::string & k) {mGraphicalObjectKey = k;};

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CLTextGlyph & g);
  };

#endif
