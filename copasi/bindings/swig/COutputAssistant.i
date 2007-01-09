%{

#include "report/COutputAssistant.h"

%}
class CDefaultOutputDescription
  {
  public:

    CDefaultOutputDescription()
        : name(""), description(""), isPlot(true), mTaskType(CCopasiTask::steadyState) {}

    //C_INT32 id;
    std::string name;
    std::string description;
    bool isPlot;
    CCopasiTask::Type mTaskType;
  };

%template(ReportTypeIdStdVector) std::vector<C_INT32>;

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
     *  get an index of a default output report that is
     *  recommended  for the given problem.
     *  If no such report exists, -1 is returned
     */
    static
    C_INT32 getDefaultReportIndex(const CCopasiProblem * problem);


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
     *  if activate==true and the ouput is a report the report is set as
     *  the current report for the task (possibly replacing an already set report)
     */
    static
    CCopasiObject* createDefaultOutput(C_INT32 id, CCopasiTask * task, bool activate = true);

  };



