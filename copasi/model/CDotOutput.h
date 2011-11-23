// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CDotOutput.h,v $
//   $Revision: 1.2.4.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/11/23 15:36:00 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CDotOutput
#define COPASI_CDotOutput

#include <iostream>
#include <map>
#include <set>

class CCopasiObject;
class CModel;
class Refresh;

class CDotOutput
{

public:

  CDotOutput();

  void writeDependencies(std::ostream & os, const CModel* pModel, const CCopasiObject * rootNode = NULL);

  void setSkipDependenciesOnCompartments(bool b) {mSkipCompartments = b;};
  void setOnlyAlgebraicDependencies(bool b) {mOnlyAlgebraicDependencies = b;};
  void simpleCall(const CModel* pModel);

protected:

  class ObjectData
  {
  public:
    bool mInUpToDateList;
    size_t mSimulatedRefreshesIndex;
    size_t mNonSimulatedRefreshesIndex;
    size_t mConstantRefreshesIndex;

    ObjectData();
  };

  void writeDotRecursively(const CCopasiObject * obj, std::ostream & os);

  void writeObjectNode(std::ostream & os, const CCopasiObject * ptr, const ObjectData & od) const;

  void writeEdge(std::ostream & os, const CCopasiObject * ptr1, const CCopasiObject * ptr2, bool indirect = false);

  void updateObjectNodesFromModel(const CModel* model);

  ObjectData * getObjectDataFromRefresh(const Refresh* ref);

  void findObjectsWithUpdateMethod(const CCopasiObject * obj, std::set<const CCopasiObject*> & objectSet, size_t recursion = 0) const;

  // member variables

  bool mSkipCompartments;
  bool mOnlyAlgebraicDependencies;

  std::map <const CCopasiObject*, ObjectData> mObjects;
};

#endif
