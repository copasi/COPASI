// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *
 */

#ifndef COPASI_PLOT_ITEM
#define COPASI_PLOT_ITEM

#include <string>
#include <vector>
#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/output/COutputHandler.h"

#undef min
#undef max

class CPlotDataChannelSpec : public CRegisteredCommonName
{
public:
  /**
   *  Minimum value of the data in this channel
   */
  C_FLOAT64 min;

  /**
   *  Maximum value of the data in this channel
   */
  C_FLOAT64 max;

  /**
   * Should autoscaling be attempted?
   */
  bool minAutoscale;
  bool maxAutoscale;

  CPlotDataChannelSpec()
    : CRegisteredCommonName(),
      min(0.0),
      max(0.0),
      minAutoscale(true),
      maxAutoscale(true)
  {}

  CPlotDataChannelSpec(const CCommonName & obj)
    : CRegisteredCommonName(obj),
      min(0.0),
      max(0.0),
      minAutoscale(true),
      maxAutoscale(true)
  {}

  CPlotDataChannelSpec(const CCommonName & obj, C_FLOAT64 minimum, C_FLOAT64 maximum)
    : CRegisteredCommonName(obj),
      min(minimum),
      max(maximum),
      minAutoscale(false),
      maxAutoscale(false)
  {}
};

//****************************************************************************************

class CPlotItem : public CCopasiParameterGroup
{
public:
  /**
   * Enumeration of the sub types of curve types known to COPASI.
   */
  enum Type
  {
    unset = 0,
    curve2d,
    histoItem1d,            //for plot items
    bandedGraph,
    surface,
    plot2d,
    simWiz,   //for plot specifications
    spectogram
  };

  enum class LineType
  {
    Lines = 0,
    Points,
    Symbols,
    LinesAndSymbols,
    __SIZE
  };

  static const CEnumAnnotation< std::string, LineType > LineTypeNames;

  enum class LineStyle
  {
    Solid = 0,
    Dotted,
    Dashed,
    DotDash,
    DotDotDash,
    None,
    __SIZE
  };

  /**
   * String literals for the GUI to display type names of line types known
   * to COPASI.
   */
  static const CEnumAnnotation< std::string, LineStyle > LineStyleNames;

  enum class SymbolType
  {
    SmallCross = 0,
    LargeCross,
    Circle,
    Square,
    Diamond,
    xCross,
    Plus,
    Star,
    TriangleUp,
    TriangleDown,
    TriangleLeft,
    TriangleRight,
    hDash,
    vDash,
    None,
    __SIZE
  };

  /**
   * String literals for the GUI to display type names of symbol known
   * to COPASI.
   */
  static const CEnumAnnotation< std::string, SymbolType > SymbolNames;

  /**
   * String literals for the GUI to display plot item names of methods known
   * to COPASI.
   */
  static const std::string TypeName[];

  /**
   * XML sub type names of methods known to COPASI.
   */
  static const char * XMLType[];

  /**
   * String literals for the GUI to display recording activity names of plots known
   * to COPASI.
   */
  static const std::string RecordingActivityName[];

  /**
   * XML recording activity names of plots known to COPASI.
   */
  static const char* XMLRecordingActivity[];

  // Attributes
private:

  /**
   * The type of the method
   */
  Type mType;

  /**
   * The recording activity for items of type curve2d and histoItem1d
   */
  COutputInterface::Activity mActivity;

  /**
   * A pointer to the string containing the XML representation of the activity
   */
  std::string * mpXMLActivity;

  std::vector<CPlotDataChannelSpec> channels;

  /**
   * Initialize the contained CDataObjects
   */
  void initObjects();

protected:
  CPlotItem(const CPlotItem & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CPlotItem * pDataObject
   */
  static CPlotItem * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  CPlotItem(const std::string & name = "NoName",
            const CDataContainer * pParent = NO_PARENT,
            const Type & type = curve2d);

  CPlotItem(const CPlotItem & src,
            const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CPlotItem();

  void cleanup();

  /**
   * Retrieve the type of the method
   */
  const CPlotItem::Type & getType() const;

  void setType(CPlotItem::Type type);

  void setActivity(const COutputInterface::Activity & activity);

  const COutputInterface::Activity & getActivity() const;

  const std::string & getTitle() const; //TODO later replace with something more generic
  void setTitle(const std::string & title);

  std::vector<CPlotDataChannelSpec> & getChannels();
  const std::vector<CPlotDataChannelSpec> & getChannels() const;
  size_t getNumChannels() const;
  void addChannel(const CPlotDataChannelSpec & channel);
};

#endif
