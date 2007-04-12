// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphNode.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/12 17:33:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CGRAPHNODE_H_
#define CGRAPHNODE_H_

#include <vector>

#include "copasi.h"

#include "layout/CLGlyphs.h"
#include "layout/CLCurve.h"

class CGraphNode : public CLMetabGlyph
  {
  private:
    C_FLOAT64 msize;
    std::string morigNodeKey;
    std::vector<CLCurve*> mConnectedCurves;
  public:

    CGraphNode(const std::string & name = "GraphNode",
               const CCopasiContainer * pParent = NULL);

    CGraphNode(const CLMetabGlyph & src,
               const CCopasiContainer * pParent = NULL);

    CGraphNode(const CGraphNode & src,
               const CCopasiContainer * pParent = NULL);

    C_FLOAT64 getSize(){return this->msize;}
    void setSize(C_FLOAT64 newSize);

    std::string getOrigNodeKey(){return this->morigNodeKey;}

    std::vector<CLCurve*> getCurves(){return this->mConnectedCurves;}

    void addCurve(CLCurve* pcurve)
    {
      this->mConnectedCurves.push_back(pcurve);
      std::cout << "add curve: " << *pcurve << std::endl;
    }

    virtual void scale (const double & scaleFactor)
    {
      this->mBBox.scale(scaleFactor);
      this->msize = this->msize * scaleFactor;
    }
  };

#endif
