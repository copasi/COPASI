/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotItem.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:59 $
   End CVS Header */

#include "CPlotItem.h"

const std::string CPlotItem::TypeName[] =
  {
    "Unset",
    "2D Curve",
    "2D Plot",
    "SimWiz",
    ""
  };

const std::string CPlotItem::XMLType[] =
  {
    "Unset",
    "Curve2D",
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
    //    mKey(GlobalKeys.add("PlotItem", this)),
    mType(type)
{
  //setObjectName(TypeName[mType]); //TODO
  setObjectName(name);
}

CPlotItem::CPlotItem(const CPlotItem & src,
                     const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    //    mKey(GlobalKeys.add("PlotItem", this)),
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

CPlotItem::~CPlotItem()
{
  //  GlobalKeys.remove(mKey);
}

void CPlotItem::cleanup()
{
  //TODO: parametergroup cleanup
}

void CPlotItem::initObjects()
{}

const CPlotItem::Type & CPlotItem::getType() const
  {return mType;}

void CPlotItem::setType(CPlotItem::Type type)
{mType = type;}

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

//const std::string & CPlotItem::getKey() const
//{return mKey;}

const std::string & CPlotItem::getTitle() const
  {
    return getObjectName();
  }

void CPlotItem::setTitle(const std::string & title)
{
  setObjectName(title);
}
