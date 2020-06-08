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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CGRAPHNODE_H_
#define CGRAPHNODE_H_

#include <vector>

#include "copasi/copasi.h"

#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLCurve.h"

class CGraphNode : public CLMetabGlyph
{
private:
  C_FLOAT64 msize;
  std::string morigNodeKey;
  std::string mObjectKey; // corresponding sbml object key

  std::string mLabelText; // if node has a label, the string content should be stored here (additionally to label)

  CLPoint getPointOnRectangle(CLBoundingBox r, CLPoint p);
  //std::vector<int> mConnectedCurveIndices; // indices of curves in CQGLNetworkPainter viewerNodes attached to the node

public:

  CGraphNode(const std::string & name = "GraphNode",
             const CDataContainer * pParent = NO_PARENT);

  CGraphNode(const CLMetabGlyph & src,
             const CDataContainer * pParent);

  CGraphNode(const CGraphNode & src,

             const CDataContainer * pParent = NO_PARENT);

  C_FLOAT64 getSize() {return this->msize;}
  //void setSize(C_FLOAT64 newSize, std::vector<CLCurve> *viewerCurves);
  void setSize(C_FLOAT64 newSize);

  std::string getObjectKey() {return this->mObjectKey;}
  void setObjectKey(std::string key) {mObjectKey = key;}

  //void adaptCurvesForRectangles(std::vector<CLCurve> *viewerCurves);

  std::string getOrigNodeKey() {return this->morigNodeKey;}

  std::string getLabelText() {return this->mLabelText;}
  void setLabelText(std::string name);

  //std::vector<int> getCurveIndices(){return this->mConnectedCurveIndices;}

  //    void addCurveIndex(int indx)
  //    {
  //      this->mConnectedCurveIndices.push_back(indx);
  //}
  //
  //    void addArrowIndex(int indx)
  //    {
  //      this->mConnectedCurveIndices.push_back(indx);
  //}
  //    void addCurveIndex(int indx)
  //    {
  //      this->mConnectedCurveIndices.push_back(indx);
  //}

  virtual void scale(const double & scaleFactor)
  {
    this->mBBox.scale(scaleFactor);
    this->msize = this->msize * scaleFactor;
  }

  virtual void scale(const double & scaleFactor, bool changeSizeP)
  {
    this->mBBox.scale(scaleFactor);

    if (changeSizeP)
      this->msize = this->msize * scaleFactor;
  }

  friend std::ostream & operator<<(std::ostream &os, const CGraphNode & gn);
};

#endif
