#ifndef VIEW_CURRRENT_ARGUMENTS_H
#define VIEW_CURRRENT_ARGUMENTS_H

#include <string>

class CCopasiTask;

class Arguments {

public:

  Arguments(int argc, char* argv[]);

  const std::string& getFilename() const;

  std::string prepareModel() const;

  char** getInitArgs() const;

  bool haveFile() const;

  bool isRunScheduled() const;

  bool isSwitchToTask() const;

  bool isValid() const;

  int getTaskToSwitchTo() const;

  bool isGenerateOutput() const;

  int getOutputToGenerate() const;

  bool haveReportFile() const;

  const std::string& getReportFile() const;

  bool haveTaskName() const;

  const std::string& getTaskName() const;

  bool isSolutionStatistic() const;

  bool isDisableStatistic() const;

  bool isDisablePlots() const;

  bool isDisableRandomizeStartValues() const;

  bool isHideWindow() const;

  static CCopasiTask* getFirstScheduledTask();

private:

  void parseArgs(int arc, char* argv[]);

  CCopasiTask* getTaskForName(const std::string& name) const;

  CCopasiTask* getTask() const;

  std::string mFilename;

  std::string mTask;

  std::string mReportFile;

  bool mRunScheduled;

  bool mSetSolutionStatistic;

  bool mDisableStatistic;

  bool mDisablePlots;

  bool mDisableRandomizeStartValues;

  bool mHideWindow;

  bool mClearTargets;

  int mSwitchToTask;

  int mGenerateOutput;

  int mArgc;

  char** mArgv;

};

#endif
