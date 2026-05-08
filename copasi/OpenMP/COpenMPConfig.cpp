// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/COpenMPConfig.h"
#include "copasi/OpenMP/CContext.h"

#ifdef USE_OMP
# include <omp.h>
#else
# define omp_sched_static 1u
# define omp_sched_dynamic 2u
# define omp_sched_guided 3u
# define omp_sched_auto 4u
typedef unsigned int omp_sched_t;
#endif // USE_OMP

// static
const COpenMPConfig::ScheduleStrategyName COpenMPConfig::ScheduleStrategyNames({
  "static",
  "dynamic",
  "guided",
  "automatic"
});

// static
const CEnumAnnotation< omp_sched_t, COpenMPConfig::ScheduleStrategy > ScheduleStrategyOpenMP({
  omp_sched_static,
  omp_sched_dynamic,
  omp_sched_guided,
  omp_sched_auto
});

// static
const int COpenMPConfig::MaxNumThreads = omp_get_max_threads();

COpenMPConfig::COpenMPConfig(const std::string & name,
                             const CDataContainer * pParent)
  : CCopasiParameterGroup(name, pParent)
  , mpIsEnabled(nullptr)
  , mpMaxNumThreads(nullptr)
  , mpScheduleStrategy(nullptr)
{
  initializeParameter();
}

COpenMPConfig::COpenMPConfig(const COpenMPConfig & src,
                             const CDataContainer * pParent)
  : CCopasiParameterGroup(src, pParent)
  , mpIsEnabled(nullptr)
  , mpMaxNumThreads(nullptr)
  , mpScheduleStrategy(nullptr)
{
  initializeParameter();
}

COpenMPConfig::COpenMPConfig(const CCopasiParameterGroup & group,
                             const CDataContainer * pParent)
  : CCopasiParameterGroup(group, pParent)
  , mpIsEnabled(nullptr)
  , mpMaxNumThreads(nullptr)
  , mpScheduleStrategy(nullptr)
{
  initializeParameter();
}

// virtual
COpenMPConfig::~COpenMPConfig()
{}

COpenMPConfig & COpenMPConfig::operator=(const COpenMPConfig & rhs)
{
  if (this != &rhs)
    {
      CCopasiParameterGroup::operator=(rhs);
      initializeParameter();
    }

  return *this;
}

void COpenMPConfig::apply() const
{
#ifdef USE_OMP
  if (*mpIsEnabled)
    {
      omp_set_num_threads(*mpMaxNumThreads);
      omp_set_schedule(ScheduleStrategyOpenMP[ScheduleStrategyNames.toEnum(*mpScheduleStrategy)], 0);
    }
  else
    {
      omp_set_num_threads(1);
    }
#endif // USE_OMP
}

const bool & COpenMPConfig::getIsEnabled() const
{
  return *mpIsEnabled;
}

const unsigned C_INT32 & COpenMPConfig::getMaxNumThreads() const
{
  return *mpMaxNumThreads;
}

const std::string & COpenMPConfig::getScheduleStrategy() const
{
  return *mpScheduleStrategy;
}

bool COpenMPConfig::setIsEnabled(const bool & isEnabled)
{
  *mpIsEnabled = isEnabled;
  return true;
}

bool COpenMPConfig::setMaxNumThreads(const unsigned C_INT32 & maxNumThreads)
{
  if (maxNumThreads == 0 || maxNumThreads > MaxNumThreads)
    return false;

  *mpMaxNumThreads = maxNumThreads;

#ifdef USE_OMP
  omp_set_num_threads(maxNumThreads);
#endif // USE_OMP

  return true;
}

bool COpenMPConfig::setScheduleStrategy(const std::string & scheduleStrategy)
{
  if (ScheduleStrategyNames.toEnum(scheduleStrategy) == ScheduleStrategy::__SIZE)
    return false;

  *mpScheduleStrategy = scheduleStrategy;

#ifdef USE_OMP
  omp_set_schedule(ScheduleStrategyOpenMP[ScheduleStrategyNames.toEnum(scheduleStrategy)], 0);
#endif // USE_OMP

  return true;
}

void COpenMPConfig::initializeParameter()
{
  mpIsEnabled = assertParameter("Enabled", CCopasiParameter::Type::BOOL, false);
  mpMaxNumThreads = assertParameter("Max Number Threads", CCopasiParameter::Type::UINT, (C_UINT32) ceil(MaxNumThreads / 2.0));
  mpScheduleStrategy = assertParameter("Schedule Strategy", CCopasiParameter::Type::STRING, std::string("static"));

  CCopasiParameter * pMaxNumThreadsParameter = getParameter("Max Number Threads");
  pMaxNumThreadsParameter->setValidValues(std::vector<std::pair<C_UINT32, C_UINT32>>({{1, MaxNumThreads}}));

  CCopasiParameter * pScheduleStrategyParameter = getParameter("Schedule Strategy");
  pScheduleStrategyParameter->setValidValues(ScheduleStrategyNames);
}

std::string COpenMPConfig::Info()
{
  std::ostringstream Info;

#ifdef USE_OMP
  Info << " (OpenMP threads: " << omp_get_max_threads() << " schedule: ";
  omp_sched_t Schedule;
  int Chunk;
  omp_get_schedule(&Schedule, &Chunk);

  // Schedule may have the monotonic modifier, we masked it.
  Schedule = (omp_sched_t)(Schedule & ~omp_sched_monotonic);
  Info << ScheduleStrategyNames[ScheduleStrategyOpenMP.toEnum(Schedule)];
  Info << "," << Chunk << ")";
#endif // USE_OMP

  return Info.str();
}
