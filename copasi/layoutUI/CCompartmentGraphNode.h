// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
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

protected:
  CCompartmentGraphNode(const CCompartmentGraphNode & src);

public:
  CCompartmentGraphNode(const CCompartmentGraphNode & src,
                        const CCopasiContainer * pParent);

  CCompartmentGraphNode(const std::string & name = "GraphNode",
                        const CCopasiContainer * pParent = NO_PARENT);

  CCompartmentGraphNode(const CLCompartmentGlyph & src,
                        const CCopasiContainer * pParent);

  std::string getObjectKey() {return this->mObjectKey;}
  void setObjectKey(std::string key) {mObjectKey = key;}

  std::string getOrigNodeKey() {return this->mOrigNodeKey;}

  friend std::ostream & operator<<(std::ostream &os, const CCompartmentGraphNode & gn);
};

#endif // CCOMPARTMENTGRAPHNODE_H_
