// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CCompartmentGraphNode.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/15 15:03:13 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CCOMPARTMENTGRAPHNODE_H_
#define CCOMPARTMENTGRAPHNODE_H_

#include "layout/CLGlyphs.h"

class CCompartmentGraphNode : public CLCompartmentGlyph
  {
  private:
    std::string mOrigNodeKey;
    std::string mObjectKey; // corresponding sbml object key

  public:
    CCompartmentGraphNode(const CCompartmentGraphNode & src,
                          const CCopasiContainer * pParent = NULL);

    CCompartmentGraphNode(const std::string & name = "GraphNode",
                          const CCopasiContainer * pParent = NULL);

    CCompartmentGraphNode(const CLCompartmentGlyph & src,
                          const CCopasiContainer * pParent = NULL);

    std::string getObjectKey(){return this->mObjectKey;}
    void setObjectKey(std::string key){mObjectKey = key;}

    std::string getOrigNodeKey(){return this->mOrigNodeKey;}

    friend std::ostream & operator<<(std::ostream &os, const CCompartmentGraphNode & gn);
  };

#endif // CCOMPARTMENTGRAPHNODE_H_
