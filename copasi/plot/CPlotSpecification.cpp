/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotSpecification.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/13 14:35:42 $
   End CVS Header */

/**
 *  CCopasiMethod class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CPlotSpecification.h" 
//#include "CCopasiMessage.h"

const std::string CPlotItem::TypeName[] =
  {
    "Not set",
    "2D Curve",
    ""
  };

const char* CPlotItem::XMLType[] =
  {
    "NotSet",
    "Curve2D",
    NULL
  };

CPlotItem::Type CPlotItem::TypeNameToEnum(const std::string & typeName)
{
  unsigned C_INT32 i = 0;
  while (TypeName[i] != typeName && TypeName[i] != "") i++;

  if (CPlotItem::TypeName[i] != "") return (CPlotItem::Type) i;
  else return CPlotItem::unset;
}

CPlotItem::Type CPlotItem::XMLNameToEnum(const char * xmlTypeName)
{
  unsigned C_INT32 i = 0;
  while (strcmp(xmlTypeName, XMLType[i]) && XMLType[i]) i++;

  if (XMLType[i]) return (CPlotItem::Type) i;
  else return CPlotItem::unset;
}

CPlotItem::CPlotItem():
    CCopasiParameterGroup("NoName", NULL, "PlotItem"),
    mType(CPlotItem::unset)
{setName(TypeName[mType]);}

CPlotItem::CPlotItem(const CPlotItem::Type & type,
                     const CCopasiContainer * pParent):
    CCopasiParameterGroup(TypeName[type], pParent, "PlotItem"),
    mType(type)
{setName(TypeName[mType]);}

CPlotItem::CPlotItem(const CPlotItem & src,
                     const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType)
{}

CPlotItem::~CPlotItem() {}

const CPlotItem::Type & CPlotItem::getType() const
  {return mType;}

void CPlotItem::setType(CPlotItem::Type type)
{mType = type;}

std::vector<CPlotDataChannelSpec> & CPlotItem::getChannels()
{return channels;}

//**************************************************************
