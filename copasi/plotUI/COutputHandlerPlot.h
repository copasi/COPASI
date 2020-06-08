// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifndef OUTPUT_HANDLER_PLOT
#define OUTPUT_HANDLER_PLOT

#include <map>

#include "copasi/output/COutputHandler.h"

class COutputDefinitionVector;
class PlotWindow;

/**
 *  This is used to call the plotting routines from the tasks
 *  We do not want to call gui stuff directly from the trajectory task.
 */
class COutputHandlerPlot : public COutputHandler
{
public:
  /**
   * Default constructor
   */
  COutputHandlerPlot();

  /**
   * Copy constructor
   * @param const COutputHandlerPlot & src
   */
  COutputHandlerPlot(const COutputHandlerPlot & src);

  /**
   * Destructor
   */
  virtual ~COutputHandlerPlot();

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @param  const CDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList listOfContainer);

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  // virtual void output(const Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  // virtual void separate(const Activity & activity);

  /**
   * Finish the output
   */
  // virtual void finish();

  /**
   * Remove an interface
   * @param COutputInterface * pInterface;
   */
  virtual void removeInterface(COutputInterface * pInterface);

  void setOutputDefinitionVector(COutputDefinitionVector * pDefinitionVector);

private:
  /**
   * The plot definition
   */
  COutputDefinitionVector * mpDefinitionVector;

  /**
   * This maps the key of a plot spec to a plot window
   */
  std::map<std::string, PlotWindow*> mPlotMap;
};

#endif
