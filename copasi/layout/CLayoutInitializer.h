// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLayoutInitializer.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/16 16:56:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef LAYOUTINI_H
#define LAYOUTINI_H

#include <map>
#include <string>

class CLayout;
class CModel;

class CLCompartmentGlyph;
class CCompartment;

class CLMetabGlyph;
class CMetab;

class CLReactionGlyph;
class CReaction;

/**
 * This class contains (static) methods that initialize
 * the layout data structure from a copasi model.
 * A proper layout is not generated, this is rather a
 * starting point for the layout algorithms
 */
class CLayoutInitializer
  {
  public:

    /**
     * one layout element is created for every model element.
     * This acts as a pseudo constructor for a CLayout.
     */
    //static CLayout* createLayoutFromCModel(const CModel* model);

  protected:
    static CLCompartmentGlyph* createCompartmentGlyph(const CCompartment* c);
    static CLMetabGlyph * createMetabGlyph(const CMetab * m);

    static CLReactionGlyph * createReactionGlyph(const CReaction * r,
        const std::map<std::string, std::string> & mm);
  };

#endif
