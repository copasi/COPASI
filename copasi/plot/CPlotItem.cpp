// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CPlotItem.h"

#include "../undo/CData.h"
#include "report/CKeyFactory.h"
#include "utilities/utility.h"

const std::string CPlotItem::TypeName[] =
{
  "Unset",
  "2D Curve",
  "Histogram",
  "Banded Graph",
  "Surface",

  "2D Plot",
  "SimWiz",
  "Spectogram",
  ""
};

const char* CPlotItem::XMLType[] =
{
  "Unset",
  "Curve2D",
  "Histogram1DItem",
  "BandedGraph",
  "Surface",

  "Plot2D",
  "SimWiz",
  "Spectogram",
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

// static
CPlotItem * CPlotItem::fromData(const CData & data)
{
  return new CPlotItem(data.getProperty(CData::OBJECT_NAME).toString(),
                       NO_PARENT,
                       (CPlotItem::Type) data.getProperty(CData::PLOT_ITEM_TYPE).toUint());
}

CPlotItem::CPlotItem(const std::string & name,
                     const CCopasiContainer * pParent,
                     const CPlotItem::Type & type):
  CCopasiParameterGroup(TypeName[type], pParent, "PlotItem"),
  mType(unset),
  mActivity(),
  mpXMLActivity(NULL)
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
  setType(src.mType);
}

void CPlotItem::setType(CPlotItem::Type type)
{
  if (type == mType) return;

  if (mType != unset) clear();

  mType = type;

  //create parameters
  if (type == curve2d || type == bandedGraph)
    {
      assertParameter("Line type", CCopasiParameter::UINT, (unsigned C_INT32) 0);
      assertParameter("Line subtype", CCopasiParameter::UINT, (unsigned C_INT32) 0);
      assertParameter("Line width", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0);
      assertParameter("Symbol subtype", CCopasiParameter::UINT, (unsigned C_INT32) 0);
    }

  if (type == spectogram)
    {
      assertParameter("logZ", CCopasiParameter::BOOL, false);
      assertParameter("bilinear", CCopasiParameter::BOOL, true);
      assertParameter("contours", CCopasiParameter::STRING, std::string(""));
      assertParameter("maxZ", CCopasiParameter::STRING, std::string(""));
      assertParameter("colorMap", CCopasiParameter::STRING, std::string("Default"));
    }

  if (type == histoItem1d)
    {
      assertParameter("increment", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
    }

  if (type == curve2d || type == histoItem1d || type == bandedGraph || type == surface || type == spectogram)
    {
      assertParameter("Color", CCopasiParameter::STRING, std::string("auto"));

      mpXMLActivity = assertParameter("Recording Activity", CCopasiParameter::STRING, std::string("during"));

      mActivity = toEnum(mpXMLActivity->c_str(), XMLRecordingActivity, COutputInterface::DURING);

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
      case bandedGraph:
      case histoItem1d:
      case spectogram:
      case surface:
        mActivity = activity;
        *mpXMLActivity = XMLRecordingActivity[mActivity];
        break;

      default:
        mActivity = (COutputInterface::Activity) 0;
        break;
    }
}

const COutputInterface::Activity & CPlotItem::getActivity() const
{
  COutputInterface::Activity Activity;

  switch (mType)
    {
      case curve2d:
      case bandedGraph:
      case histoItem1d:
      case spectogram:
      case surface:

        if (!mpXMLActivity)
          const_cast<CPlotItem *>(this)->mpXMLActivity =
            &const_cast<CPlotItem *>(this)->getParameter("Recording Activity")->getValue< std::string >();

        Activity = toEnum(mpXMLActivity->c_str(), XMLRecordingActivity, COutputInterface::DURING);

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

size_t CPlotItem::getNumChannels() const
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
