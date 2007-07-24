// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CDotOutput.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/24 09:45:44 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CDotOutput.h"

#include "report/CCopasiContainer.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

CDotOutput::CDotOutput()
    : mSkipCompartments(false),
    mOnlyAlgebraicDependencies(false)
{}

void CDotOutput::writeDependencies(std::ostream & os, const CCopasiObject * rootNode)
{
  const CCopasiObject * obj;
  if (rootNode)
    obj = rootNode;
  else
    obj = CCopasiContainer::Root;

  mObjects.clear();

  os << "digraph G {\n";

  //edges
  writeDotRecursively(obj, os);

  //this is done after the edges since it requires all relevant object to be in the mObjects map
  updateObjectNodesFromModel(CCopasiDataModel::Global->getModel());

  //nodes
  std::map<const CCopasiObject*, ObjectData>::const_iterator it, itEnd = mObjects.end();
  for (it = mObjects.begin(); it != itEnd; ++it)
    {
      writeObjectNode(os, it->first, it->second);
    }

  os << "}" << std::endl;
}

void CDotOutput::findObjectsWithUpdateMethod(const CCopasiObject * obj, std::set<const CCopasiObject*> & objectSet, unsigned int recursion) const
  {
    if (!obj) return;
    if (recursion > 10) return; //limit recursion
    //it is assumed  *obj has no UpdateMethod

    std::set< const CCopasiObject * >::const_iterator it, itEnd = obj->getDirectDependencies().end();
    //std::cout << pO->getObjectName() <<  pO->getValueReference()->getDirectDependencies().size() << std::endl;
    for (it = obj->getDirectDependencies().begin(); it != itEnd; ++it)
      {
        if ((*it)->hasUpdateMethod())
          objectSet.insert(*it);
        else
          findObjectsWithUpdateMethod(*it, objectSet, recursion + 1);
      }
  }

void CDotOutput::writeDotRecursively(const CCopasiObject * obj, std::ostream & os)
{

  if ((!mOnlyAlgebraicDependencies) || obj->hasUpdateMethod())
    {
      std::set< const CCopasiObject * >::const_iterator it, itEnd = obj->getDirectDependencies().end();
      //std::cout << pO->getObjectName() <<  pO->getValueReference()->getDirectDependencies().size() << std::endl;
      for (it = obj->getDirectDependencies().begin(); it != itEnd; ++it)
        {
          //skip deps on compartments
          if (mSkipCompartments)
            if ((*it)->getObjectParent() && ((*it)->getObjectParent()->getObjectType() == "Compartment"
                                             || (*it)->getObjectType() == "Compartment")) continue;
          if (mOnlyAlgebraicDependencies)
            {
              if ((*it)->hasUpdateMethod())
                writeEdge(os, obj, *it);
              else
                {//find indirect dependencies
                  std::set<const CCopasiObject* > tmpObjectSet;
                  findObjectsWithUpdateMethod(*it, tmpObjectSet);
                  std::set<const CCopasiObject* >::const_iterator tmpIt, tmpItEnd = tmpObjectSet.end();
                  for (tmpIt = tmpObjectSet.begin(); tmpIt != tmpItEnd; ++tmpIt)
                    writeEdge(os, obj, *tmpIt, true); //
                }
            }
          else
            writeEdge(os, obj, *it);
          //os << "\"" << obj->getObjectDisplayName() << "\" -> \"" << (*it)->getObjectDisplayName() << "\"\n";
        }
    }

  //recursion
  if (obj->isContainer())
    {
      CCopasiContainer* container;
      container = (CCopasiContainer*)obj;

      CCopasiContainer::objectMap::const_iterator it = container->getObjects().begin();
      // int cnt = container->getObjects().size();

      for (; it != container->getObjects().end(); ++it)
        {
          //the next line skips name references...
          if (it->second->getObjectName() == "Name") continue;

          if (it->second->getObjectType() == "Function") continue;

          //skip if the contained object is not owned by this container
          if (it->second->getObjectParent() != container) continue;

          writeDotRecursively(it->second, os);
        }
      //return;
    }
}

void CDotOutput::writeObjectNode(std::ostream & os, const CCopasiObject * ptr, const ObjectData & od) const
  {
    os << "//" << std::endl;

    bool flagUM = ptr->hasUpdateMethod();
    bool flagRM = ptr->getRefresh() != NULL;
    bool flagInUpToDateList = od.mInUpToDateList;

    std::ostringstream oss;
    if (od.mSimulatedRefreshesIndex != -1)
      oss << "SR=" << od.mSimulatedRefreshesIndex << " ";
    if (od.mNonSimulatedRefreshesIndex != -1)
      oss << "NSR=" << od.mNonSimulatedRefreshesIndex << " ";
    if (od.mConstantRefreshesIndex != -1)
      oss << "CR=" << od.mConstantRefreshesIndex << " ";

    os << "\"" << ptr->getObjectDisplayName() << "\" [shape=plaintext, color=blue, " << std::endl;
    os << "label=<\n";
    os << "<TABLE CELLSPACING=\"0\">\n";
    os << "  <TR><TD COLSPAN=\"4\">" << ptr->getObjectDisplayName() << "</TD></TR>\n";
    os << "  <TR>\n";
    os << "    <TD " << (flagUM ? "BGCOLOR=\"red\"" : " ") << "><FONT POINT-SIZE=\"7.0\">UM</FONT>" << "" << "</TD>\n";
    os << "    <TD " << (flagRM ? "BGCOLOR=\"green\"" : " ") << "><FONT POINT-SIZE=\"7.0\">RM</FONT>" << "" << "</TD>\n";
    os << "    <TD " << (flagInUpToDateList ? "BGCOLOR=\"blue\"" : " ") << "><FONT POINT-SIZE=\"7.0\">UtD</FONT>" << "" << "</TD>\n";
    os << "    <TD><FONT POINT-SIZE=\"7.0\">" << oss.str() << " </FONT></TD>\n";
    os << "  </TR>\n";
    os << "</TABLE>\n";
    os << "\n";
    os << ">];\n";
  }

void CDotOutput::writeEdge(std::ostream & os, const CCopasiObject * ptr1, const CCopasiObject * ptr2, bool indirect)
{
  assert(ptr1);
  assert(ptr2);

  mObjects[ptr1];
  mObjects[ptr2];

  os << "\"" << ptr1->getObjectDisplayName() << "\" -> \"" << ptr2->getObjectDisplayName() << "\"";

  if (indirect) os << " [color=blue]";

  os << "\n";
}

void CDotOutput::updateObjectNodesFromModel(const CModel* model)
{
  const std::set< const CCopasiObject * > & objectSet = model->getUpToDateObjects();

  std::set< const CCopasiObject * >::const_iterator it, itEnd = objectSet.end();
  for (it = objectSet.begin(); it != itEnd; ++it)
    {
      mObjects[*it].mInUpToDateList = true;
    }

  unsigned int i, imax;

  imax = model->getListOfSimulatedRefreshes().size();
  for (i = 0; i < imax; ++i)
    {
      ObjectData * pOD = getObjectDataFromRefresh(model->getListOfSimulatedRefreshes()[i]);
      if (pOD) pOD->mSimulatedRefreshesIndex = i;
    }

  imax = model->getListOfNonSimulatedRefreshes().size();
  for (i = 0; i < imax; ++i)
    {
      ObjectData * pOD = getObjectDataFromRefresh(model->getListOfNonSimulatedRefreshes()[i]);
      if (pOD) pOD->mNonSimulatedRefreshesIndex = i;
    }

  imax = model->getListOfConstantRefreshes().size();
  for (i = 0; i < imax; ++i)
    {
      ObjectData * pOD = getObjectDataFromRefresh(model->getListOfConstantRefreshes()[i]);
      if (pOD) pOD->mConstantRefreshesIndex = i;
    }

  /*   const std::vector< Refresh * > getListOfSimulatedRefreshes() const; //mSimulatedRefreshes;
     const std::vector< Refresh * > getListOfConstantRefreshes() const; //mConstantRefreshes;
     const std::vector< Refresh * > getListOfNonSimulatedRefreshes() const; //mNonSimulatedRefreshes;
  */
}

CDotOutput::ObjectData * CDotOutput::getObjectDataFromRefresh(const Refresh* ref)
{
  std::map <const CCopasiObject*, ObjectData>::iterator it, itEnd = mObjects.end();
  for (it = mObjects.begin(); it != itEnd; ++it)
    {
      if (it->first->getRefresh() == ref) return &it->second;
    }

  std::cout << "Object for Refresh method not found!" << std::endl;
  return NULL;
}

void CDotOutput::simpleCall()
{
  std::ofstream os;
  os.open("CopasiDependencies.dot", std::ios::out);

  setSkipDependenciesOnCompartments(true);
  setOnlyAlgebraicDependencies(true);
  writeDependencies(os);

  os.close();
}
