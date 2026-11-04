// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <time.h>
#ifdef WIN32
# ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES 1
# endif // _USE_MATH_DEFINES
# ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
# endif // WIN32_LEAN_AND_MEAN
# include <windows.h>
# ifdef min
#  undef min
# endif // min
# ifdef max
#  undef max
# endif // max
#else
# include <unistd.h>
# include <sys/syscall.h>
#endif // WIN32

#include "copasi/core/CEnumValue.h"
#include "copasi/randomGenerator/CConfigurableRNG.h"
#include "copasi/utilities/CopasiTime.h"

CConfigurableRNG::CConfigurableRNG(CConfigurableRNG::Type engineType, CConfigurableRNG::result_type initialSeed)
  : mEngine(false)
  , mType(engineType)
  , mSeed(initialSeed)
{}

CConfigurableRNG::CConfigurableRNG(const CConfigurableRNG & src)
  : mEngine(false)
  , mType(src.mType)
  , mSeed(src.mSeed)
{}

CConfigurableRNG * CConfigurableRNG::copy()
{
  return new CConfigurableRNG(*this);
}

void CConfigurableRNG::seed(CConfigurableRNG::result_type newSeed)
{
  if (mEngine.index() != 0)
    {
      mSeed = (newSeed != 0) ? newSeed : getSystemSeed();
      std::visit([this](auto & eng) {
        using EngineType = std::decay_t< decltype(eng) >;

        if constexpr (!std::is_same_v< EngineType, bool >)
          eng.seed(mSeed);
      },
                 mEngine);
    }
  else
    mSeed = newSeed;
}

CConfigurableRNG::result_type CConfigurableRNG::operator()()
{
  if (mEngine.index() == 0)
    initialize();

  return std::visit([](auto & eng) -> result_type {
    using EngineType = std::decay_t< decltype(eng) >;

    if constexpr (std::is_same_v < EngineType, bool >)
      return 0;
    else
      return static_cast< result_type >(eng());
  },
                    mEngine);
}

void CConfigurableRNG::discard(result_type z)
{
  if (mEngine.index() == 0)
    initialize();

  std::visit([z](auto & eng) {
    using EngineType = std::decay_t< decltype(eng) >;

    if constexpr (!std::is_same_v< EngineType, bool >)
      eng.discard(z);
  },
             mEngine);
}

CConfigurableRNG::Type CConfigurableRNG::getType() const
{
  return mType;
}

void CConfigurableRNG::setType(Type engineType, result_type initialSeed)
{
  mEngine = false;
  mType = engineType;
  mSeed = initialSeed;
}

void CConfigurableRNG::initialize()
{
  if (mSeed == 0)
    mSeed = getSystemSeed();

  switch (mType)
    {
    case Type::R250:
      mEngine = std::independent_bits_engine< CR250, 64, result_type >{mSeed};
      break;
    case Type::MersenneTwister:
      mEngine = std::independent_bits_engine< std::mt19937, 64, result_type >{mSeed};
      break;
    case Type::MersenneTwister64:
      mEngine = std::mt19937_64{mSeed};
      break;
    case Type::SobolSequence:
      mEngine = std::independent_bits_engine< CSobolSequence, 64, result_type >{mSeed};
      break;
    }
}

// static
CConfigurableRNG::result_type CConfigurableRNG::getSystemSeed()
{
  result_type ThreadId = 0;

#ifdef WIN32
  ThreadId = (result_type)(GetCurrentThreadId() & 0xffffffffUL);
#elif defined(SYS_thread_selfid)
  ThreadId = (result_type)(::syscall(SYS_thread_selfid) & 0xffffffffUL);
#elif defined(SYS_gettid)
  ThreadId = (result_type)(::syscall(SYS_gettid) & 0xffffffffUL);
#elif defined(SYS_getthrid)
  ThreadId = (result_type)(syscall(SYS_getthrid) & 0xffffffffUL);
#endif

  // Invert Byte order so that we do not have accidental cancellations since both time and thread id are incremented.
  ThreadId = (ThreadId & 0x000000ffUL) << 24 | (ThreadId & 0x0000ff00UL) << 8 |
             (ThreadId & 0x00ff0000UL) >> 8 | (ThreadId & 0xff000000UL) >> 24;

  result_type Time = (result_type)(CCopasiTimeVariable::getCurrentWallTime().getMicroSeconds() & 0xffffffffUL);

  // We use XOR so that we do not favor set or unset bits.
  result_type Seed = ThreadId ^ Time;

  return Seed;
}
