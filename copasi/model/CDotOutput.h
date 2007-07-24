// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CDotOutput.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/24 09:45:44 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

    void writeDependencies(std::ostream & os, const CCopasiObject * rootNode = NULL);

    void setSkipDependenciesOnCompartments(bool b) {mSkipCompartments = b;};
    void setOnlyAlgebraicDependencies(bool b) {mOnlyAlgebraicDependencies = b;};
    void simpleCall();

  protected:

    class ObjectData
      {
      public:
        bool mInUpToDateList;
        int mSimulatedRefreshesIndex;
        int mNonSimulatedRefreshesIndex;
        int mConstantRefreshesIndex;

        ObjectData()
            : mInUpToDateList(false),
            mSimulatedRefreshesIndex(-1),
            mNonSimulatedRefreshesIndex(-1),
            mConstantRefreshesIndex(-1)
        {};
      };

    void writeDotRecursively(const CCopasiObject * obj, std::ostream & os);

    void writeObjectNode(std::ostream & os, const CCopasiObject * ptr, const ObjectData & od) const;

    void writeEdge(std::ostream & os, const CCopasiObject * ptr1, const CCopasiObject * ptr2, bool indirect = false);

    void updateObjectNodesFromModel(const CModel* model);

    ObjectData * getObjectDataFromRefresh(const Refresh* ref);

    void findObjectsWithUpdateMethod(const CCopasiObject * obj, std::set<const CCopasiObject*> & objectSet, unsigned int recursion = 0) const;

    // member variables

    bool mSkipCompartments;
    bool mOnlyAlgebraicDependencies;

    std::map <const CCopasiObject*, ObjectData> mObjects;
  };

#endif
