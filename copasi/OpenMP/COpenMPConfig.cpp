// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/COpenMPConfig.h"
#include "copasi/OpenMP/CContext.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

// static
const CEnumAnnotation< std::string, COpenMPConfig::ScheduleStrategy > 
  COpenMPConfig::ScheduleStrategyNames({"static",
                                        "dynamic",
                                        "guided",
                                        "automatic"});

// static
const CEnumAnnotation< omp_sched_t, COpenMPConfig::ScheduleStrategy > 
  COpenMPConfig::ScheduleStrategyOpenMP({omp_sched_static,
                                         omp_sched_dynamic,
                                         omp_sched_guided,
                                         omp_sched_auto});

// static
const CEnumAnnotation< std::string, COpenMPConfig::Monotonic >
  COpenMPConfig::MonotonicNames({"nonmonotonic",
                                 "monotonic"});

// static
const CEnumAnnotation< omp_sched_t, COpenMPConfig::Monotonic > 
  COpenMPConfig::MonotonicOpenMP({(omp_sched_t) 0x0, // nonmonotonic
  omp_sched_monotonic});

// static
COpenMPConfig::_ScheduleStrategyOpenMP COpenMPConfig::EnvironmentOpenMP;

// static
int COpenMPConfig::AppliedNumThreads = -1;

// static
std::vector< std::weak_ptr< std::function< void() > > > COpenMPConfig::ApplyCallbacks;

// static
void COpenMPConfig::RegisterApplyCallback(const std::shared_ptr< std::function< void() > > & callback)
{
  ApplyCallbacks.push_back(callback);
}

// static 
void COpenMPConfig::InitFromEnvironment()
{
  if (AppliedNumThreads > -1)
    return;

  AppliedNumThreads = 0;

  EnvironmentOpenMP.MaxNumThreads = omp_get_max_threads();
  std::string OMP_NUM_THREADS = COptions::getEnvironmentVariable("OMP_NUM_THREADS");

  if (!OMP_NUM_THREADS.empty())
    {
      EnvironmentOpenMP.isEnabled = true;
      EnvironmentOpenMP.MaxNumThreads = std::stoi(OMP_NUM_THREADS);
    }

  std::string OMP_THREAD_LIMIT = COptions::getEnvironmentVariable("OMP_THREAD_LIMIT");

  if (!OMP_THREAD_LIMIT.empty())
    {
      if (!EnvironmentOpenMP.isEnabled)
        {
          EnvironmentOpenMP.isEnabled = true;
          EnvironmentOpenMP.MaxNumThreads = std::stoi(OMP_THREAD_LIMIT);
        }
      else
        {
          EnvironmentOpenMP.MaxNumThreads = std::min(EnvironmentOpenMP.MaxNumThreads, std::stoi(OMP_THREAD_LIMIT));
        }
    }

  std::string OMP_SCHEDULE = COptions::getEnvironmentVariable("OMP_SCHEDULE");
  std::string Monotonic = "";

  std::string::size_type Pos = OMP_SCHEDULE.find(":");

  if (Pos != std::string::npos)
    {
      Monotonic = OMP_SCHEDULE.substr(0, Pos);
      OMP_SCHEDULE = OMP_SCHEDULE.substr(Pos + 1);

#ifndef OMP_HAVE_MONOTONIC
      Monotonic = "nonmonotonic";
#endif // OMP_HAVE_MONOTONIC
    }

  std::string ChunkSize;
  Pos = OMP_SCHEDULE.find(",");

  if (Pos != std::string::npos)
    {
      ChunkSize = OMP_SCHEDULE.substr(Pos + 1);
      OMP_SCHEDULE = OMP_SCHEDULE.substr(0, Pos);
    }

  EnvironmentOpenMP.scheduleStrategy = COpenMPConfig::ScheduleStrategyNames.toEnum(OMP_SCHEDULE);
  EnvironmentOpenMP.monotonicity = COpenMPConfig::MonotonicNames.toEnum(Monotonic);
  EnvironmentOpenMP.chunkSize = (C_UINT32) ChunkSize.empty() ? -1 : std::stoi(ChunkSize);
  EnvironmentOpenMP.isEnabled |= (EnvironmentOpenMP.scheduleStrategy != ScheduleStrategy::__SIZE);

  return;
}

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

// static
void COpenMPConfig::Apply()
{
  const COpenMPConfig & OpenMPConfig = CRootContainer::getConfiguration()->getOpenMPConfig();
  CRootContainer::getConfiguration()->getOpenMPConfig().apply();

  if (AppliedNumThreads != omp_get_max_threads())
    {
      AppliedNumThreads = omp_get_max_threads();

      for (auto it = ApplyCallbacks.begin(); it != ApplyCallbacks.end();)
        {
          if (auto callback = it->lock())
            {
              (*callback)();
              ++it;
            }
          else
            {
              it = ApplyCallbacks.erase(it);
            }
        }
      }
}

void COpenMPConfig::apply() const
{
  C_UINT32 MaxNumThreads = std::min((C_UINT32) EnvironmentOpenMP.MaxNumThreads, *mpMaxNumThreads);

  if (MaxNumThreads == 0)
    MaxNumThreads = EnvironmentOpenMP.MaxNumThreads;
    
  std::string ScheduleStrategy = EnvironmentOpenMP.scheduleStrategy == ScheduleStrategy::__SIZE ? *mpScheduleStrategy : ScheduleStrategyNames[EnvironmentOpenMP.scheduleStrategy];
  std::string Monotonic = EnvironmentOpenMP.monotonicity == Monotonic::__SIZE ? *mpMonotonic : MonotonicNames[EnvironmentOpenMP.monotonicity];
  C_UINT32 ChunkSize = EnvironmentOpenMP.chunkSize == (C_UINT32) -1 ? *mpChunkSize : EnvironmentOpenMP.chunkSize;

#ifdef USE_OMP
  if (*mpIsEnabled || EnvironmentOpenMP.isEnabled)
    {
      omp_set_num_threads(MaxNumThreads);
      omp_sched_t OpenMPStrategy =
        ScheduleStrategyOpenMP[ScheduleStrategyNames.toEnum(ScheduleStrategy, ScheduleStrategy::Static)];
      omp_sched_t OpenMPMonotonicity =
        MonotonicOpenMP[MonotonicNames.toEnum(Monotonic, Monotonic::nonmonotonic)];

      omp_set_schedule(omp_sched_t(OpenMPStrategy | OpenMPMonotonicity), ChunkSize);
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
  if (maxNumThreads > EnvironmentOpenMP.MaxNumThreads)
    return false;

  *mpMaxNumThreads = maxNumThreads == 0 ? EnvironmentOpenMP.MaxNumThreads : maxNumThreads;

#ifdef USE_OMP
  omp_set_num_threads((int) *mpMaxNumThreads);
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
  InitFromEnvironment();

  mpIsEnabled = assertParameter("Enabled", CCopasiParameter::Type::BOOL, EnvironmentOpenMP.isEnabled);
  C_UINT32 DefaultMaxNumThreads = EnvironmentOpenMP.isEnabled ? EnvironmentOpenMP.MaxNumThreads : ceil(EnvironmentOpenMP.MaxNumThreads / 2.0);
  mpMaxNumThreads = assertParameter("Max Number Threads", CCopasiParameter::Type::UINT, DefaultMaxNumThreads);
  mpScheduleStrategy = assertParameter("Schedule Strategy", CCopasiParameter::Type::STRING, ScheduleStrategyNames[EnvironmentOpenMP.scheduleStrategy != ScheduleStrategy::__SIZE ? EnvironmentOpenMP.scheduleStrategy : ScheduleStrategy::Static]);
  mpMonotonic = assertParameter("Monotonicity", CCopasiParameter::Type::STRING, MonotonicNames[EnvironmentOpenMP.monotonicity != Monotonic::__SIZE ? EnvironmentOpenMP.monotonicity : Monotonic::nonmonotonic]);
  mpChunkSize = assertParameter("Chunk Size", CCopasiParameter::Type::UINT, EnvironmentOpenMP.chunkSize == (C_UINT32) -1 ? 0 : EnvironmentOpenMP.chunkSize);

  CCopasiParameter * pMaxNumThreadsParameter = getParameter("Max Number Threads");
  pMaxNumThreadsParameter->setValidValues(std::vector< std::pair< C_UINT32, C_UINT32 > >({{0, EnvironmentOpenMP.MaxNumThreads}}));

  CCopasiParameter * pScheduleStrategyParameter = getParameter("Schedule Strategy");
  pScheduleStrategyParameter->setValidValues(ScheduleStrategyNames);

  CCopasiParameter * pMonotonicParameter = getParameter("Monotonicity");
  pMonotonicParameter->setValidValues(MonotonicNames);
}

std::string COpenMPConfig::Info()
{
  std::ostringstream Info;

#ifdef USE_OMP
  Info << "OpenMP " << COPASI_OMP_VERSION << " (threads: " << omp_get_max_threads() << ", schedule: ";
  omp_sched_t Schedule;
  int Chunk;
  omp_get_schedule(&Schedule, &Chunk);

  // Schedule may have the monotonic modifier, we masked it.
  if (Schedule & omp_sched_monotonic)
    {
      Schedule = (omp_sched_t) (Schedule & ~omp_sched_monotonic);
      Info << "monotonic:";
    }

  Info << ScheduleStrategyNames[ScheduleStrategyOpenMP.toEnum(Schedule)];
  Info << ", chunk size: " << Chunk << ")";
#endif // USE_OMP

  return Info.str();
}
