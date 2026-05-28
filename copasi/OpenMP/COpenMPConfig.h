// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <memory>
#include <functional>
#include <vector>
#
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/commandline/COptions.h"

/**
 *  COpenMPConfig class.
 */
class COpenMPConfig : public CCopasiParameterGroup
{
private:
  static std::vector< std::weak_ptr< std::function< void() > > >  ApplyCallbacks;

  static int AppliedNumThreads;

public:
  static void RegisterApplyCallback(const std::shared_ptr< std::function< void() > > & callback);

  static std::string Info();

  static void Apply();

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
  static const CEnumAnnotation< omp_sched_t, ScheduleStrategy > ScheduleStrategyOpenMP;

  enum struct Monotonic
  {
    nonmonotonic = 0,
    monotonic,
    __SIZE
  };

  typedef CEnumAnnotation< std::string, Monotonic > MonotonicName;
  static const MonotonicName MonotonicNames;
  static const CEnumAnnotation< omp_sched_t, Monotonic > MonotonicOpenMP;

  static const int MaxNumThreads;

  COpenMPConfig() = delete;

  /**
   * Default constructor
   * @param const std::string & name (default: MIRIAM Resource)
   * @param const CDataContainer * pParent (default: NULL)
   */
  COpenMPConfig(const std::string & name = "Parallel Processing",
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

  void apply() const;

  bool *mpIsEnabled;

  C_UINT32 *mpMaxNumThreads;

  std::string *mpScheduleStrategy;

  std::string *mpMonotonic;

  C_UINT32 *mpChunkSize;
};
