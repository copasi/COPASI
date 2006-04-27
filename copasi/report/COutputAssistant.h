/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/COutputAssistant.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:31:10 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COutputAssistant
#define COPASI_COutputAssistant

#include <vector>
#include <string>
#include <map>
#include "copasi.h"

class CCopasiTask;
class CCopasiProblem;
class CPlotSpecification;
class CReportDefinition;
class CCopasiObject;

class CDefaultOutputDescription
  {
  public:

    CDefaultOutputDescription()
        : name(""), description(""), isPlot(true) {}

    //C_INT32 id;
    std::string name;
    std::string description;
    bool isPlot;
  };

class COutputAssistant
  {
  public:

    /**
     *  get a list of indices of default output definitions that are
     *  suitable for the problem.
     *  If problem=NULL (default) all indices in the map are returned.
     */
    static
    std::vector<C_INT32> getListOfDefaultOutputDescriptions(const CCopasiProblem * problem = NULL);

    /**
     *  get title of output definition with index id.
     */
    static
    const std::string & getItemName(C_INT32 id);

    /**
     *  get complete description of output definition with index id.
     */
    static
    const CDefaultOutputDescription & getItem(C_INT32 id);

    /**
     *  create a plot or report from template with index id.
     *  returns a pointer to the plot or report definition (or NULL)
     */
    static
    CCopasiObject* createDefaultOutput(C_INT32 id, CCopasiTask * task);

  private:           //************************************

    typedef std::map<C_INT32, CDefaultOutputDescription> Map;

    static
    Map mMap;

    //this method creates the lists of output descriptions
    static
    bool initialize();

    static
    CPlotSpecification* createPlot(const std::string & name,
                                   const CCopasiObject* x,
                                   const std::vector<const CCopasiObject*> & y);

    static
    CReportDefinition* createTable(const std::string & name,
                                   const std::vector<const CCopasiObject*> & d,
                                   const std::string & comment);

    static const std::string emptyString;
    static const CDefaultOutputDescription emptyItem;
  };

#endif
