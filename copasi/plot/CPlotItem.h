/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotItem.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 17:43:46 $
   End CVS Header */

/**
 *  
 */

#ifndef COPASI_PLOT_ITEM
#define COPASI_PLOT_ITEM

#include <string>
#include <vector>
#include "copasi.h"

#include "utilities/CCopasiParameterGroup.h"
#include "report/CCopasiObjectName.h"
#include "utilities/COutputHandler.h"

class CPlotDataChannelSpec : public CRegisteredObjectName
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
        : CRegisteredObjectName(),
        min(0.0),
        max(0.0),
        minAutoscale(true),
        maxAutoscale(true)
    {}

    CPlotDataChannelSpec(const CCopasiObjectName & obj)
        : CRegisteredObjectName(obj),
        min(0.0),
        max(0.0),
        minAutoscale(true),
        maxAutoscale(true)
    {}

    CPlotDataChannelSpec(const CCopasiObjectName & obj, C_FLOAT64 minimum, C_FLOAT64 maximum)
        : CRegisteredObjectName(obj),
        min(minimum),
        max(maximum),
        minAutoscale(false),
        maxAutoscale(false)
    {}};

//****************************************************************************************

class CPlotItem : public CCopasiParameterGroup
  {
  public:
    /**
     * Enumeration of the sub types of methods known to COPASI.
     */
    enum Type
    {
      unset = 0, curve2d, histoItem1d,            //for plot items
      plot2d, simWiz   //for plot specifications
    };

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
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

  public:
    CPlotItem(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL,
              const Type & type = curve2d);

    CPlotItem(const CPlotItem & src,
              const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CPlotItem();

    void cleanup();

    /**
     * Convert a TypeName to the matching enum value.
     * Returns CPlotItem::unset if no match is found.
     * @param (const std::string & subTypeName)
     * @return CPlotItem::Type type
     */
    static
    CPlotItem::Type TypeNameToEnum(const std::string & typeName);

    /**
     * Convert a XMLType to the matching enum value
     * Returns CCopasiMethod::unset if no match is found.
     * @param (const char * xmlTypeName)
     * @return CCopasiMethod::SubType type
     */ 
    //static
    //CPlotItem::Type XMLNameToEnum(const char * xmlTypeName);
    static
    CPlotItem::Type XMLNameToEnum(const std::string& xmlTypeName);

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
    unsigned C_INT32 getNumChannels() const;
    void addChannel(const CPlotDataChannelSpec & channel);
  };

#endif
