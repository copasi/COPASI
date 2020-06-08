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

#ifndef CCOMPARTMENTGRAPHNODE_H_
#define CCOMPARTMENTGRAPHNODE_H_

#include "copasi/layout/CLGlyphs.h"

class CCompartmentGraphNode : public CLCompartmentGlyph
{
private:
  std::string mOrigNodeKey;
  std::string mObjectKey; // corresponding sbml object key

protected:
  CCompartmentGraphNode(const CCompartmentGraphNode & src);

public:
  CCompartmentGraphNode(const CCompartmentGraphNode & src,
                        const CDataContainer * pParent);

  CCompartmentGraphNode(const std::string & name = "GraphNode",
                        const CDataContainer * pParent = NO_PARENT);

  CCompartmentGraphNode(const CLCompartmentGlyph & src,
                        const CDataContainer * pParent);

  std::string getObjectKey() {return this->mObjectKey;}
  void setObjectKey(std::string key) {mObjectKey = key;}

  std::string getOrigNodeKey() {return this->mOrigNodeKey;}

  friend std::ostream & operator<<(std::ostream &os, const CCompartmentGraphNode & gn);
};

#endif // CCOMPARTMENTGRAPHNODE_H_
