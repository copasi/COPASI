/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotItem.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/10 02:20:37 $
   End CVS Header */

#include "CPlotItem.h"
#include "report/CKeyFactory.h"

const std::string CPlotItem::TypeName[] =
  {
    "Unset",
    "2D Curve",
    "Histogram",

    "2D Plot",
    "SimWiz",
    ""
  };

const std::string CPlotItem::XMLType[] =
  {
    "Unset",
    "Curve2D",
    "Histogram1DItem",

    "Plot2D",
    "SimWiz",
    ""
  };

CPlotItem::Type CPlotItem::TypeNameToEnum(const std::string & typeName) //static
{
  unsigned C_INT32 i = 0;
  while (TypeName[i] != typeName && TypeName[i] != "") i++;

  if (CPlotItem::TypeName[i] != "") return (CPlotItem::Type) i;
  else return CPlotItem::unset;
}

/*CPlotItem::Type CPlotItem::XMLNameToEnum(const char * xmlTypeName) //static
{
  unsigned C_INT32 i = 0;
  while (strcmp(xmlTypeName, XMLType[i]) && XMLType[i]) i++;
 
  if (XMLType[i]) return (CPlotItem::Type) i;
  else return CPlotItem::unset;
}*/

CPlotItem::Type CPlotItem::XMLNameToEnum(const std::string & xmlTypeName) //static
{
  unsigned C_INT32 i = 0;
  while (xmlTypeName != XMLType[i] && XMLType[i] != "") i++;

  if (XMLType[i] != "") return (CPlotItem::Type) i;
  else return CPlotItem::unset;
}

CPlotItem::CPlotItem(const std::string & name,
                     const CCopasiContainer * pParent,
                     const CPlotItem::Type & type):
    CCopasiParameterGroup(TypeName[type], pParent, "PlotItem"),
    mType(unset)
{
  //setObjectName(TypeName[mType]); //TODO
  setObjectName(name);
  setType(type); //to create the parameters
}

CPlotItem::CPlotItem(const CPlotItem & src,
                     const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType),
    channels(src.getChannels())
{
  /*
  std::cout << "Creating new PlotItem from Template: " << this << std::endl;
  for(unsigned int counter=0; counter < src.getChannels().size(); counter++)
  {
     std::cout << "Channel " << counter << ": " << src.getChannels()[counter] << std::endl;
  } 
  for(unsigned int counter=0; counter < this->getChannels().size(); counter++)
  {
     std::cout << "New Channel " << counter << ": " << this->getChannels()[counter] << std::endl;
  } 
  */
}

void CPlotItem::setType(CPlotItem::Type type)
{
  if (type == mType) return;

  mType = type;
  clear();

  //create parameters
  if (type == curve2d)
    {
      addParameter("Line type", CCopasiParameter::UINT, (unsigned C_INT32)0);
    }

  if (type == plot2d)
    {
      addParameter("log X", CCopasiParameter::BOOL, false);
      addParameter("log Y", CCopasiParameter::BOOL, false);
    }

  if (type == histoItem1d)
    {
      addParameter("increment", CCopasiParameter::DOUBLE, (C_FLOAT64)0.1);
    }
}

CPlotItem::~CPlotItem()
{}

void CPlotItem::cleanup()
{
  //TODO: parametergroup cleanup
}

void CPlotItem::initObjects()
{}

const CPlotItem::Type & CPlotItem::getType() const
  {return mType;}

std::vector<CPlotDataChannelSpec> & CPlotItem::getChannels()
{return channels;}

const std::vector<CPlotDataChannelSpec> & CPlotItem::getChannels() const
  {return channels;}

unsigned C_INT32 CPlotItem::getNumChannels() const
  {return channels.size();}

void CPlotItem::addChannel(const CPlotDataChannelSpec & channel)
{
  channels.push_back(channel);
}

const std::string & CPlotItem::getTitle() const
  {
    return getObjectName();
  }

void CPlotItem::setTitle(const std::string & title)
{
  setObjectName(title);
}
