// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <sstream>

#include "copasi/OpenMP/CContext.h"

std::string omp_info::operator()()
{
  std::ostringstream Info;

#ifdef USE_OMP
  Info << " (OpenMP threads: " << omp_get_max_threads() << " schedule: ";
  omp_sched_t Schedule;
  int Chunk;
  omp_get_schedule(&Schedule, &Chunk);

  // Schedule may have the monotonic modifier, we masked it.
  Schedule = (omp_sched_t)(Schedule & ~omp_sched_monotonic);

  switch (Schedule)
    {
      // case (omp_sched_t) (omp_sched_static | omp_sched_monotonic):
      case omp_sched_static:
        Info << "static";
        break;

      case omp_sched_dynamic:
        Info << "dynamic";
        break;

      case omp_sched_guided:
        Info << "guided";
        break;

      case omp_sched_auto:
        Info << "automatic";
        break;

      default:
        omp_set_schedule(omp_sched_dynamic, 1);
        return operator()();
        break;
    }

  Info << "," << Chunk << ")";
#endif // USE_OMP

  return Info.str();
}
