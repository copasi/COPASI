// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef VIEW_CURRRENT_ARGUMENTS_H
#define VIEW_CURRRENT_ARGUMENTS_H

#include <string>

class CCopasiTask;

class Arguments
{

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

  bool haveOutputDir() const;

  const std::string& getOutputDir() const;

  bool haveTaskName() const;

  const std::string& getTaskName() const;

  const std::string& getFileType() const;

  bool isSolutionStatistic() const;

  bool isDisableStatistic() const;

  bool isDisablePlots() const;

  bool isDisableRandomizeStartValues() const;

  bool isHideWindow() const;

  bool isSaveLayout() const;

  bool handleCommandLine() const;

  bool isQuitAfterTaskExecution() const;

  static CCopasiTask* getFirstScheduledTask();

private:

  void parseArgs(int arc, char* argv[]);

  CCopasiTask* getTaskForName(const std::string& name) const;

  CCopasiTask* getTask() const;

  std::string mFilename;

  std::string mOutputDir;

  std::string mTask;

  std::string mReportFile;

  std::string mFileType;

  bool mRunScheduled;

  bool mSaveLayout;

  bool mSetSolutionStatistic;

  bool mDisableStatistic;

  bool mDisablePlots;

  bool mDisableRandomizeStartValues;

  bool mHideWindow;

  bool mQuitAfterTaskExecution;

  bool mClearTargets;

  int mSwitchToTask;

  int mGenerateOutput;

  int mArgc;

  char** mArgv;
};

#endif
