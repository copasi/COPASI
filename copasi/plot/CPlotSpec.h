/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/01/14 16:59:28 $
   End CVS Header */

#ifndef COPASI_CPLOTSPEC
#define COPASI_CPLOTSPEC

#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h" 
//#include "CCopasiStaticString.h"
#include <string>
#include <vector>
#include <qwt_plot.h>

class CDataChannelSpec
  {
  public:
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

    CDataChannelSpec(C_INT32 idx = 0)
        : index(idx),
        min(0.0),
        max(0.0),
        autoscale(true)
    {}

    CDataChannelSpec(C_INT32 idx, C_FLOAT64 minimum, C_FLOAT64 maximum)
        : index(idx),
        min(minimum),
        max(maximum),
        autoscale(false)
    {}};

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

    // the variable(i.e. column) indices in the data from the output file (TODO: explain more later)...
    // the order(relative indices) of the columns for the particular curve among all those selected
    // e.g. if columns 0,1 and 4 are selected for two curves, and the second curve requires
    // data from columns 1 and 4, then coordX = 0 and coordY = 2
    // these can/should be determined from the GUI parameters
    //int coordX, coordY;

    CDataChannelSpec xChannel, yChannel;

    //std::vector<std::string> axisTitles;

    // constructor and destructor
    /*Curve2DSpec(std::string title,
              int xIndex, int yIndex,          // the indices of the variables
              int axis_h = 2, int axis_v = 0,     // specifies which axes to use
              std::string xTitle = "X", std::string yTitle = "Y")
        : curveTitle(title), coordX(xIndex), coordY(yIndex)
    {
      xAxis = QwtPlot::Axis(axis_h);
      yAxis = QwtPlot::Axis(axis_v);

      axisTitles.push_back(xTitle);
      axisTitles.push_back(yTitle);
    }*/
    Curve2DSpec(const std::string& t, C_INT32 indexX = 0, C_INT32 indexY = 1)
        : title(t),
        xAxis(QwtPlot::xBottom),
        yAxis(QwtPlot::yLeft),
        xChannel(indexX),
        yChannel(indexY)
    {}

    ~Curve2DSpec()
    {}
  };

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

    inline const std::string & getKey() const
      {
        return mKey;
      }
  };

#endif
