// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/SBMLDocumentLoader.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/16 00:09:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLDOCUMENTLOADER_H_
#define SBMLDOCUMENTLOADER_H_

#include <vector>
#include <string>
#include <map>

#include "sbml/SBMLReader.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/layout/Layout.h"
#include "sbml/ListOf.h"
#include "sbml/layout/Curve.h"
//#include "node.h"
//#include "network.h"
//#include "curveSegment.h"

class CCopasiObject;
class CCopasiContainer;

class CLBase;
class CListOfLayouts;
class CLayout;
class CLGraphicalObject;

class Layout;

class Model;

class SBMLDocumentLoader
  {

  private:
    SBMLDocument * sbmlDocP;
    //network* mapLayoutToGraph(Model *model,Layout *layout);
    //vector <curveSegment*> getCurveSegments(Curve *curve);
    Model *modelP;
    //bool hasID(node *n, const string& s);
    //ListOf* layoutList;

  public:
    //SBMLDocumentLoader():layoutList(0){};
    CLayout* loadDocument(const char *filename);

    static void readListOfLayouts(CListOfLayouts & lol,
                                  const ListOf & sbmlList,
                                  const std::map<CCopasiObject*, SBase*> & copasimodelmap);

  protected:

    static CLayout * createLayout(const Layout & sbmlLayout,
                                  const std::map<std::string, std::string> & modelmap,
                                  std::map<std::string, std::string> & layoutmap,
                                  const CCopasiContainer * pParent = NULL);

    /**
     * resolves the graphical object reference of the text glyph
     */
    static void postprocessTextGlyph(const TextGlyph & sbml,
                                     const std::map<std::string, std::string> & layoutmap);

    //static void loadSBase(CLBase*, const SBase*) {};

    //static void loadGraphicalObject(CLGraphicalObject* c, const GraphicalObject *s);

    //static CLGraphicalObject* createGraphicalObject(const GraphicalObject *s);
  };

#endif /*SBMLDOCUMENTLOADER_H_*/
