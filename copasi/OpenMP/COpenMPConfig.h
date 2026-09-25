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
public:
  enum struct ScheduleStrategy
  {
    Static = 0,
    Dynamic,
    Guided,
    Automatic,
    Undefined
  };

  constexpr static CEnumAnnotation ScheduleStrategyNames{
    ScheduleStrategy::Undefined,
    MapNode{ScheduleStrategy::Static, "static"},
    MapNode{ScheduleStrategy::Dynamic, "dynamic"},
    MapNode{ScheduleStrategy::Guided, "guided"},
    MapNode{ScheduleStrategy::Automatic, "automatic"},
    MapNode{ScheduleStrategy::Undefined, "undefind"}};

  constexpr static CEnumAnnotation ScheduleStrategyOpenMP{
    ScheduleStrategy::Undefined,
    MapNode{ScheduleStrategy::Static, omp_sched_static},
    MapNode{ScheduleStrategy::Dynamic, omp_sched_dynamic},
    MapNode{ScheduleStrategy::Guided, omp_sched_guided},
    MapNode{ScheduleStrategy::Automatic, omp_sched_auto},
    MapNode{ScheduleStrategy::Undefined, (omp_sched_t) 0x0}};

  enum struct Monotonic
  {
    nonmonotonic = 0,
    monotonic,
    undefined
  };

  constexpr static CEnumAnnotation MonotonicNames{
    Monotonic::undefined,
    MapNode{Monotonic::nonmonotonic, "nonmonotonic"},
    MapNode{Monotonic::monotonic, "monotonic"},
    MapNode{Monotonic::undefined, "undefined"}};

  constexpr static CEnumAnnotation MonotonicOpenMP{
    Monotonic::nonmonotonic,
    MapNode{Monotonic::nonmonotonic, (omp_sched_t) 0x0}, // nonmonotonic
    MapNode{Monotonic::monotonic, omp_sched_monotonic}};

private:
  static std::vector< std::weak_ptr< std::function< void() > > >  ApplyCallbacks;

  static int AppliedNumThreads;

  struct _ScheduleStrategyOpenMP
  {
    bool isEnabled = false;
    int MaxNumThreads = 0;
    ScheduleStrategy scheduleStrategy = ScheduleStrategy::Static;
    Monotonic monotonicity = COpenMPConfig::Monotonic::nonmonotonic;
    C_UINT32 chunkSize = 0;
  };

  static _ScheduleStrategyOpenMP EnvironmentOpenMP;

  static void InitFromEnvironment();

public:
  static void RegisterApplyCallback(const std::shared_ptr< std::function< void() > > & callback);

  static std::string Info();

  static void Apply();

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
