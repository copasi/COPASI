// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/COpenMPConfig.h"
#include "copasi/OpenMP/CContext.h"

// static
const COpenMPConfig::ScheduleStrategyName COpenMPConfig::ScheduleStrategyNames({"static",
                                                                                "dynamic",
                                                                                "guided",
                                                                                "automatic"});

// static
const CEnumAnnotation< omp_sched_t, COpenMPConfig::ScheduleStrategy > COpenMPConfig::ScheduleStrategyOpenMP({omp_sched_static,
                                                                                                             omp_sched_dynamic,
                                                                                                             omp_sched_guided,
                                                                                                             omp_sched_auto});

// static
const COpenMPConfig::MonotonicName COpenMPConfig::MonotonicNames({"nonmonotonic",
                                                                  "monotonic"});

// static
const CEnumAnnotation< omp_sched_t, COpenMPConfig::Monotonic > COpenMPConfig::MonotonicOpenMP({(omp_sched_t) 0x0, // nonmonotonic
                                                                                               omp_sched_monotonic});

// static
const int COpenMPConfig::MaxNumThreads = omp_get_max_threads();

struct _ScheduleStrategyOpenMP
{
  COpenMPConfig::ScheduleStrategy scheduleStrategy = COpenMPConfig::ScheduleStrategy::Static;
  COpenMPConfig::Monotonic monotonicity = COpenMPConfig::Monotonic::nonmonotonic;
  C_UINT32 chunkSize = 0;
};

_ScheduleStrategyOpenMP getSchedule()
{
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

  _ScheduleStrategyOpenMP ScheduleStrategyOpenMP;
  ScheduleStrategyOpenMP.scheduleStrategy = COpenMPConfig::ScheduleStrategyNames.toEnum(OMP_SCHEDULE);
  ScheduleStrategyOpenMP.monotonicity = COpenMPConfig::MonotonicNames.toEnum(Monotonic);
  ScheduleStrategyOpenMP.chunkSize = (C_UINT32) ChunkSize.empty() ? -1 : std::stoi(ChunkSize);

  return ScheduleStrategyOpenMP;
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

void COpenMPConfig::apply() const
{
  std::string OMP_NUM_THREADS = COptions::getEnvironmentVariable("OMP_NUM_THREADS");
  C_UINT32 MaxNumThreads = OMP_NUM_THREADS.empty() ? *mpMaxNumThreads : std::stoi(OMP_NUM_THREADS);

  _ScheduleStrategyOpenMP Schedule = getSchedule();
  std::string ScheduleStrategy = Schedule.scheduleStrategy == ScheduleStrategy::__SIZE ? *mpScheduleStrategy : ScheduleStrategyNames[Schedule.scheduleStrategy];
  std::string Monotonic = Schedule.monotonicity == Monotonic::__SIZE ? *mpMonotonic : MonotonicNames[Schedule.monotonicity];
  C_UINT32 ChunkSize = Schedule.chunkSize == (C_UINT32) -1 ? *mpChunkSize : Schedule.chunkSize;

  bool IsEnabled = *mpIsEnabled || !OMP_NUM_THREADS.empty() || Schedule.scheduleStrategy != ScheduleStrategy::__SIZE;

#ifdef USE_OMP
  if (IsEnabled)
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
  std::string OMP_NUM_THREADS = COptions::getEnvironmentVariable("OMP_NUM_THREADS");
  C_UINT32 MaxNumThreads = OMP_NUM_THREADS.empty() ? ceil(MaxNumThreads / 2.0) : std::stoi(OMP_NUM_THREADS);

  _ScheduleStrategyOpenMP Schedule = getSchedule();

  bool IsEnabled = false || !OMP_NUM_THREADS.empty() || Schedule.scheduleStrategy != ScheduleStrategy::__SIZE;

  mpIsEnabled = assertParameter("Enabled", CCopasiParameter::Type::BOOL, IsEnabled);
  mpMaxNumThreads = assertParameter("Max Number Threads", CCopasiParameter::Type::UINT, MaxNumThreads);
  mpScheduleStrategy = assertParameter("Schedule Strategy", CCopasiParameter::Type::STRING, ScheduleStrategyNames[Schedule.scheduleStrategy != ScheduleStrategy::__SIZE ? Schedule.scheduleStrategy : ScheduleStrategy::Static]);
  mpMonotonic = assertParameter("Monotonicity", CCopasiParameter::Type::STRING, MonotonicNames[Schedule.monotonicity != Monotonic::__SIZE ? Schedule.monotonicity : Monotonic::nonmonotonic]);
  mpChunkSize = assertParameter("Chunk Size", CCopasiParameter::Type::UINT, Schedule.chunkSize == (C_UINT32) -1 ? 0 : Schedule.chunkSize);

  CCopasiParameter * pMaxNumThreadsParameter = getParameter("Max Number Threads");
  pMaxNumThreadsParameter->setValidValues(std::vector< std::pair< C_UINT32, C_UINT32 > >({{1, MaxNumThreads}}));

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
