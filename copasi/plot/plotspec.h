#ifndef PLOTSPEC_H
#define PLOTSPEC_H

#include <string> // or perhaps QString
#include <fstream>  // or perhaps the Qt equivalent
#include <qwt_plot.h> // this goes with class CurveSpec
#include <vector> // goes with class PlotTaskSpec

// a data structure to hold properties of a curve, this could be a subclass of an abstract PlotSpec class
// if other types of plots are supported
class CurveSpec
  {
  public:   // or maybe private, but with a few friend classes

    // perhaps curve name here...
    std::string curveTitle;

    // the axes to be used
    QwtPlot::Axis xAxis, yAxis;

    // the variable(i.e. column) indices in the data from the output file (TODO: explain more later)...
    // the order(relative indices) of the columns for the particular curve among all those selected
    // e.g. if columns 0,1 and 4 are selected for two curves, and the second curve requires
    // data from columns 1 and 4, then coordX = 0 and coordY = 2
    // these can/should be determined from the GUI parameters
    int coordX, coordY;

    std::vector<std::string> axisTitles;

    // constructor and destructor
    CurveSpec(std::string title,
              int xIndex, int yIndex,        // the indices of the variables
              int axis_h = 2, int axis_v = 0,   // specifies which axes to use
              std::string xTitle = "X", std::string yTitle = "Y")
        : curveTitle(title), coordX(xIndex), coordY(yIndex)
    {
      xAxis = QwtPlot::Axis(axis_h);
      yAxis = QwtPlot::Axis(axis_v);

      axisTitles.push_back(xTitle);
      axisTitles.push_back(yTitle);
    }

    ~CurveSpec()
    {
      //shouldn't be necessary?
      axisTitles.pop_back();
      axisTitles.pop_back();
    }
  };

// a class to pack up all the parameters for a plot task
class PlotTaskSpec
  {
  public:
    // an enumeration of all types of plots supported - included to allow for extension
    // currently no provision for mixing these in one plot
    // not sure if it should be in this class
    enum PlotType {curve, pieChart, histogram};

    // the stream from the copasi output file -> this is probably retrieved somehow from the underlying interface rather than from the GUI
    // alternatively, maybe provide the functionality of plotting a second simulation trace produced outside the current simulation run?
    // ...in which case we might need the user to specify the file...
    // may also be a QString...
    std::istream& sourceStream;

    // the title of the plot
    std::string plotTitle;   // could be QString, if taken straight from the GUI

    // type of the plot - by default it is curve and the only one supported for now
    // -> some processing could be necessary when the user makes the choice
    PlotType plotType;

    // a vector containing the column indices of the simulation variables in the output file - or some reference to this information
    // the plotting function needs to retrieve data from the desired columns, (as well as the name of the variables as axis titles - perhaps)
    // whether this field sits here depends on where these variable names come from
    // currently it's essential that the indices in the vector are in ascending order
    std::vector<int> varIndices;   // this could be obtained from the spec for each curve

    // a vector of pointers to curve specifications (could make use of some Copasi vector when this is integrated with the rest of the project
    // its size indicates the number of curves in each plot
    std::vector<CurveSpec*> curves;

    // constructor
    PlotTaskSpec(std::istream& source,
                 std::string ptitle,
                 std::vector<int> varIn,
                 std::vector<CurveSpec*> curvespecs,
                 PlotType ptype = PlotType(curve))
        : sourceStream(source), plotTitle(ptitle), plotType(ptype), varIndices (varIn), curves(curvespecs)
    {}

    // destructor
    ~PlotTaskSpec()
    {
      for (unsigned int i = 0; i < curves.size(); i++)
        delete curves[i];
    }
  };

#endif // PLOTSPEC_H
