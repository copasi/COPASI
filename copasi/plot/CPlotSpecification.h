/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotSpecification.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/13 14:35:43 $
   End CVS Header */

/**
 *  
 */

#ifndef COPASI_PLOT_SPECIFICATION
#define COPASI_PLOT_SPECIFICATION

#include <string>

#include "utilities/CCopasiParameterGroup.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiVector.h"

class CPlotDataChannelSpec : public CCopasiObjectName
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
    bool autoscale;

    CPlotDataChannelSpec()
        : CCopasiObjectName(),
        min(0.0),
        max(0.0),
        autoscale(true)
    {}

    CPlotDataChannelSpec(const CCopasiObjectName obj)
        : CCopasiObjectName(obj),
        min(0.0),
        max(0.0),
        autoscale(true)
    {}

    CPlotDataChannelSpec(const CCopasiObjectName & obj, C_FLOAT64 minimum, C_FLOAT64 maximum)
        : CCopasiObjectName(obj),
        min(minimum),
        max(maximum),
        autoscale(false)
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
      unset = 0, curve2d //dummy
    };

    /**
     * String literals for the GUI to display sub type names of methods known
     * to COPASI.
     */
    static const std::string TypeName[];

    /**
     * XML sub type names of methods known to COPASI.
     */
    static const char* XMLType[];

    // Attributes
  private:

    /**
     * The type of the method
     */
    Type mType;

    /**
     *  Key 
     */
    std::string mKey;

    std::vector<CPlotDataChannelSpec> channels;

    /**
     * Default constructor
     */
    CPlotItem();

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CPlotItem(const CPlotItem::Type & taskType,
              const CCopasiContainer * pParent = NULL);

  public:
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
    static
    CPlotItem::Type XMLNameToEnum(const char * xmlTypeName);

    /**
     * Copy constructor
     * @param const CCopasiMethodr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CPlotItem(const CPlotItem & src,
              const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CPlotItem();

    /**
     * Retrieve the type of the method
     */
    const CPlotItem::Type & getType() const;

    void setType(CPlotItem::Type type);

    virtual const std::string & getKey() const;

    std::vector<CPlotDataChannelSpec> & getChannels();
  };

//****************************************************************************************

class CPlotSpecification : public CPlotItem
  {
  public:
    /**
     * Enumeration of the sub types of methods known to COPASI.
     */
    enum Type
    {
      unset = 0, plot2d, simWiz
    };

    /**
     * String literals for the GUI to display sub type names of methods known
     * to COPASI.
     */
    static const std::string TypeName[];

    /**
     * XML sub type names of methods known to COPASI.
     */
    static const char* XMLType[];

    // Attributes
  private:
    /**
     * The type of the method
     */
    Type mType;

    CCopasiVector<CPlotDataChannelSpec> items;

    /**
     * Default constructor
     */
    CPlotSpecification();

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CPlotSpecification(const CPlotSpecification::Type & taskType,
                       const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Convert a TypeName to the matching enum value.
     * Returns CPlotItem::unset if no match is found.
     * @param (const std::string & subTypeName)
     * @return CPlotItem::Type type
     */
    static
    CPlotSpecification::Type TypeNameToEnum(const std::string & typeName);

    /**
     * Convert a XMLType to the matching enum value
     * Returns CCopasiMethod::unset if no match is found.
     * @param (const char * xmlTypeName)
     * @return CCopasiMethod::SubType type
     */
    static
    CPlotSpecification::Type XMLNameToEnum(const char * xmlTypeName);

    /**
     * Copy constructor
     * @param const CCopasiMethodr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CPlotSpecification(const CPlotSpecification & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CPlotSpecification();

    /**
     * Retrieve the type of the method
     * @return  const string & type
     */
    const CPlotSpecification::Type & getType() const;
  };

#endif
