/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotItem.cpp,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:30:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

const char* CPlotItem::XMLType[] =
  {
    "Unset",
    "Curve2D",
    "Histogram1DItem",

    "Plot2D",
    "SimWiz",
    NULL
  };

const std::string CPlotItem::RecordingActivityName[] =
  {
    "",
    "Before",
    "During",
    "",
    "After"
  };

const char* CPlotItem::XMLRecordingActivity[] =
  {
    "NotSet",
    "before",
    "during",
    "before&during",
    "after",
    "before&after",
    "during&after",
    "before&during&after",
    NULL
  };

CPlotItem::Type CPlotItem::TypeNameToEnum(const std::string & typeName) //static
{
  unsigned C_INT32 i = 0;
  while (TypeName[i] != typeName && TypeName[i] != "") i++;

  if (CPlotItem::TypeName[i] != "") return (CPlotItem::Type) i;
  else return CPlotItem::unset;
}

CPlotItem::CPlotItem(const std::string & name,
                     const CCopasiContainer * pParent,
                     const CPlotItem::Type & type):
    CCopasiParameterGroup(TypeName[type], pParent, "PlotItem"),
    mActivity(),
    mpXMLActivity(NULL),
    mType(unset)
{
  //setObjectName(TypeName[mType]); //TODO
  setObjectName(name);
  setType(type); //to create the parameters
}

CPlotItem::CPlotItem(const CPlotItem & src,
                     const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(unset),
    mActivity(),
    mpXMLActivity(NULL),
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
  setType(src.mType);
}

void CPlotItem::setType(CPlotItem::Type type)
{
  if (type == mType) return;
  if (mType != unset) clear();

  mType = type;

  //create parameters
  if (type == curve2d)
    {
      assertParameter("Line type", CCopasiParameter::UINT, (unsigned C_INT32) 0);
    }

  if (type == histoItem1d)
    {
      assertParameter("increment", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.1);
    }

  if (type == curve2d || type == histoItem1d)
    {
      mpXMLActivity =
        assertParameter("Recording Activity", CCopasiParameter::STRING, std::string("during"))->getValue().pSTRING;

      const char ** pActivity = XMLRecordingActivity;
      while (*pActivity && mpXMLActivity->compare(*pActivity))
        pActivity++;
      mActivity = (COutputInterface::Activity) (pActivity - XMLRecordingActivity);

      if (mActivity < COutputInterface::BEFORE ||
          (COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER) < mActivity)
        {
          mActivity = COutputInterface:: DURING;
          * mpXMLActivity = XMLRecordingActivity[mActivity];
        }
    }

  if (type == plot2d)
    {
      assertParameter("log X", CCopasiParameter::BOOL, false);
      assertParameter("log Y", CCopasiParameter::BOOL, false);
      mpXMLActivity = NULL;
      mActivity = (COutputInterface::Activity) 0;
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

void CPlotItem::setActivity(const COutputInterface::Activity & activity)
{
  switch (mType)
    {
    case curve2d:
    case histoItem1d:
      mActivity = activity;
      assert (COutputInterface::BEFORE <= mActivity &&
              mActivity <= (COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER));
      * mpXMLActivity = XMLRecordingActivity[mActivity];
      break;

    default:
      mActivity = (COutputInterface::Activity) 0;
      break;
    }
}

const COutputInterface::Activity & CPlotItem::getActivity() const
  {
    const char ** pActivity = XMLRecordingActivity;
    COutputInterface::Activity Activity;

    switch (mType)
      {
      case curve2d:
      case histoItem1d:
        if (!mpXMLActivity)
          const_cast<CPlotItem *>(this)->mpXMLActivity =
            getParameter("Recording Activity")->getValue().pSTRING;

        while (*pActivity && mpXMLActivity->compare(*pActivity)) pActivity++;

        Activity =
          (COutputInterface::Activity) (pActivity - XMLRecordingActivity);

        if (Activity < COutputInterface::BEFORE ||
            (COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER) < Activity)
          {
            Activity = COutputInterface::DURING;
            * mpXMLActivity = XMLRecordingActivity[Activity];
          }

        const_cast<CPlotItem *>(this)->mActivity = Activity;

        break;

      default:
        break;
      }

    return mActivity;
  }

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
