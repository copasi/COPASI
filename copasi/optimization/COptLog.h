// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_COptLog
#define COPASI_COptLog

#include <vector>
#include <string>

#include "COptLogEntry.h"

class COptLog
{
  // Attributes
public:
  std::vector< COptLogEntry >::const_iterator begin() const;
  std::vector< COptLogEntry >::const_iterator end() const;
protected:

private:

  /**
   * A vector of all log entries
   */
  std::vector< COptLogEntry > mLogEntries;

  // Operations
private:

protected:

public:
  /**
   * Default constructor.
   */
  COptLog();

  /**
   * Destructor
   */
  virtual ~COptLog();

  /**
   * Enter a log message
   * @param COptLogEntry entry
   */
  void enterLogEntry(COptLogEntry entry);

  /**
   * Get the log element count
   * @return unsigned C_INT32 elementCount
   */
  size_t getElementCount() const;

  /**
   * Retrieve the method log as plain text.
   * Uses html tables for detailed log.
   * @return std::string plainLog
   */
  std::string getPlainLog() const;

  /**
   * Retrieve the method log as rich text.
   * Uses html headings, divs and tables.
   * @return std::string richLog
   */
  std::string getRichLog() const;
};

#endif  // COPASI_COptLog
