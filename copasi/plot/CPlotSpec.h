/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/19 09:43:21 $
   End CVS Header */

#ifndef COPASI_CPLOTSPEC
#define COPASI_CPLOTSPEC

#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h" 
//#include "CPlotSpecVector.h"
//#include "CCopasiStaticString.h"
#include <string>
#include <vector>
#include <qwt_plot.h>

class CPlotSpecVector;

class CDataChannelSpec
  {
  public:
    /**
     *  CN of the data
     */
    CCopasiObjectName object;

    /**
     *  Index of the column in the data stream
     */
    C_INT32 index;

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

    CDataChannelSpec()
        : object(),
        index(0),
        min(0.0),
        max(0.0),
        autoscale(true)
    {}

    CDataChannelSpec(const CCopasiObjectName obj)
        : object(obj),
        index(0),
        min(0.0),
        max(0.0),
        autoscale(true)
    {}

    CDataChannelSpec(const CCopasiObjectName & obj, C_FLOAT64 minimum, C_FLOAT64 maximum)
        : object(obj),
        index(0),
        min(minimum),
        max(maximum),
        autoscale(false)
    {}

    bool compile(CPlotSpecVector * ps);
  };

/**
 *  This describes one curve in a qwtPlot
 */
class Curve2DSpec
  {
  public:

    // perhaps curve name here...
    std::string title;

    // The flags that indicate which axis to be used
    QwtPlot::Axis xAxis, yAxis;

    //CDataChannelSpec xChannel, yChannel;
    std::vector<CDataChannelSpec> mChannels;

    Curve2DSpec()
        : title(""),
        xAxis(QwtPlot::xBottom),
        yAxis(QwtPlot::yLeft)
    {
      mChannels.resize(2);
    }

    Curve2DSpec(const std::string& t,
                CCopasiObjectName objX, CCopasiObjectName objY)
        : title(t),
        xAxis(QwtPlot::xBottom),
        yAxis(QwtPlot::yLeft)
    {
      mChannels.resize(2);
      mChannels[0].object = objX;
      mChannels[1].object = objY;
    }

    bool compile(CPlotSpecVector * ps)
    {
      if (!mChannels[0].compile(ps)) return false;
      if (!mChannels[1].compile(ps)) return false;
      return true;
    }

    ~Curve2DSpec()
    {}};

/**
 *  This describes one axis in a qwtPlot
 */
class CPlotAxisSpec
  {
  public:
    bool active;
    bool autoscale;
    C_FLOAT64 min, max;
    QString title;
  };

class CModel;

/**
 *  This describes one qwtPlot
 */
class CPlotSpec : public CCopasiObject
  {
  private:
    std::string mKey;

    std::vector<Curve2DSpec> curves;

    std::vector<CPlotAxisSpec> axes;

    std::string title;

  public:
    /**
     *  Default constructor.
     */
    CPlotSpec(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     */
    CPlotSpec(const CPlotSpec & src,
              const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CPlotSpec();

    /**
     * 
     */
    void updateAxes();

    /**
     * cleanup
     */
    void cleanup();

    //TODO a lot of methods to set and query all the attributes
    //void setTitle(std::string t); ...
    const std::string & getTitle() const {return title;};

    const std::vector<Curve2DSpec> & getCurves() const {return curves;};
    std::vector<Curve2DSpec> & getCurves() {return curves;};
    void createDebugPlot();
    bool createDefaultPlot(const CModel* model);

    bool compile(CPlotSpecVector * ps);

    virtual const std::string & getKey() const
      {
        return mKey;
      }
  };

#endif
