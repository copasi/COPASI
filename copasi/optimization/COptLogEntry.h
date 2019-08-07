// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_COptLogEntry
#define COPASI_COptLogEntry

#include <string>
#include <sstream>
#include <vector>
#include <ctime>

#include "copasi/copasi.h"

class COptLogEntry
{
  // Attributes
public:

protected:

  /**
   * One message header
   */
  std::string MsgHeader;

  /**
   * One message subtext
   */
  std::string MsgSubtext;

  /**
   * A string containing further detailed information of the current state of the optimization method (optional).
   */
  std::string StatusDump;

private:

  // Operations
private:

protected:

public:
  /**
   * Constructor.
   */
  COptLogEntry(const std::string &header, const std::string &subtext = "", const std::string &status = "");

  COptLogEntry();

  /**
   * Destructor
   */
  virtual ~COptLogEntry();

  /*
   * not sure we need these...

  void setHeader(std::string );

  void setSubtext(std::string );

  void setStatusDetails(std::string );

  */

  std::string getHeader() const;

  std::string getSubtext() const;

  std::string getStatusDetails() const;
};

#endif  // COPASI_COptLogEntry
