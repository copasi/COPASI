/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.h,v $
  $Revision: 1.13 $
  $Name:  $
  $Author: shoops $
  $Date: 2009/03/02 21:02:16 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef OUTPUT_HANDLER_PLOT
#define OUTPUT_HANDLER_PLOT

#include <map>

#include "utilities/COutputHandler.h"

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
     * @param std::vector< CCopasiContainer * > listOfContainer
     * @param  const CCopasiDataModel* pDataModel
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer, const CCopasiDataModel* pDataModel);

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
