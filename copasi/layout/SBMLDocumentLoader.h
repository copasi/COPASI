// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/SBMLDocumentLoader.h,v $
//   $Revision: 1.3.22.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/13 09:48:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLDOCUMENTLOADER_H_
#define SBMLDOCUMENTLOADER_H_

#include <string>
#include <map>

class CCopasiObject;
class CCopasiContainer;
class CListOfLayouts;
class CLayout;

class Layout;
class ListOf;
class SBase;
class TextGlyph;

class SBMLDocumentLoader
  {

  public:

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
  };

#endif /*SBMLDOCUMENTLOADER_H_*/
