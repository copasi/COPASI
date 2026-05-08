// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include "copasi/utilities/CCopasiParameter.h"

/**
 *  COpenMPConfig class.
 */
class COpenMPConfig : public CCopasiParameterGroup
{
public:
  static std::string Info();

  enum struct ScheduleStrategy
  {
    Static = 0,
    Dynamic,
    Guided,
    Automatic,
    __SIZE
  };

  typedef CEnumAnnotation< std::string, ScheduleStrategy > ScheduleStrategyName;
  static const ScheduleStrategyName ScheduleStrategyNames;

  static const int MaxNumThreads;

  COpenMPConfig() = delete;

  /**
   * Default constructor
   * @param const std::string & name (default: MIRIAM Resource)
   * @param const CDataContainer * pParent (default: NULL)
   */
  COpenMPConfig(const std::string & name = "OpenMP Configuration",
                const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const COpenMPConfig & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COpenMPConfig(const COpenMPConfig & src,
                const CDataContainer * pParent);

  /**
   * Specific constructor
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: NULL)
   */
  COpenMPConfig(const CCopasiParameterGroup & group,
                const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COpenMPConfig();

  /**
   * Assignment operator
   * @param const COpenMPConfig & rhs
   * @return COpenMPConfig & lhs
   */
  COpenMPConfig & operator=(const COpenMPConfig & rhs);

  void apply() const;

  const bool & getIsEnabled() const;

  const unsigned C_INT32 & getMaxNumThreads() const;

  const std::string & getScheduleStrategy() const;

  bool setIsEnabled(const bool & isEnabled);

  bool setMaxNumThreads(const unsigned C_INT32 & maxNumThreads);

  bool setScheduleStrategy(const std::string & scheduleStrategy);

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  bool *mpIsEnabled;

  unsigned C_INT32 *mpMaxNumThreads;

  std::string *mpScheduleStrategy;
};
