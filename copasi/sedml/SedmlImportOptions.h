// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef SEDML_IMPORT_OPTIONS_H
#define SEDML_IMPORT_OPTIONS_H

#include <string>
#include <vector>

class SedmlImportOptions
{
  std::string mTaskId;
  std::string mModelId;
  std::vector< std::string > mPlots;
  std::string mReportId;
  std::string mReportFile;
  bool mSkipModelImport;

public:
  SedmlImportOptions(
    const std::string & taskId = "",
    const std::string & modelId = "",
    const std::vector< std::string > & plots = std::vector< std::string >(),
    const std::string & reportId = "",
    const std::string & reportFilename = "");

  SedmlImportOptions & operator=(const SedmlImportOptions & rhs);

  void setSkipModelImport(bool skipModelLoading);
  bool skipModelImport() const;

  const std::string & getTaskId() const;
  const std::string & getModelId() const;
  const std::string & getReportId() const;
  const std::string & getReportFile() const;
  const std::vector< std::string > & getPlots() const;
  bool ignoreOutput(const std::string & outputId) const;
  bool isValid() const;
};

#endif // SEDML_IMPORT_OPTIONS_H
