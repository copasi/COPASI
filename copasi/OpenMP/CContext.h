// Copyright (C) 2020 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CCONTEXT
#define COPASI_CCONTEXT

#include <string>
#include "copasi/config.h"

#ifdef USE_MPI
#include <mpi.h>
#else
typedef int MPI_Status;
typedef int MPI_Comm;
typedef int MPI_Win;
# define MPI_COMM_WORLD 1
# define MPI_SUCCESS 0
# define MPI_ERR_UNKNOWN 2
# define MPI_ERR_LASTCODE 100
# define MPI_Comm_rank(comm, rank) (*rank = 0)
# define MPI_Comm_size(comm, processes) (*processes = 1)
#endif

#ifdef USE_OMP
# include <omp.h>
# ifndef OMP_HAVE_MONOTONIC
const omp_sched_t omp_sched_monotonic = (omp_sched_t) 0x80000000;
# endif // OMP_HAVE_MONOTONIC
#else
# define omp_get_max_threads() (1)
# define omp_get_num_threads() (1)
# define omp_get_thread_num() (0)
#endif // USE_OMP

struct omp_info
{
  std::string operator()();
};

template < class Data > class CContext
{
public:
  CContext(const bool & parallel = true);
  CContext(const CContext & src);
  ~CContext();
  CContext & operator = (const CContext & rhs);
  bool operator == (const CContext & rhs) const;

  void init();
  void release();
  Data & master();
  Data & active();
  const Data & master() const;
  const Data & active() const;
  Data * beginThread();
  Data * endThread();
  const Data * beginThread() const;
  const Data * endThread() const;
  bool isMaster(const Data * data) const;
  bool isThread(const Data * data) const;
  int localIndex(const Data * data) const;
  int globalIndex(const Data * data) const;
  const size_t & size() const;

private:
  Data * mMasterData;
  Data * mThreadData;
  bool mParallel;
  size_t mSize;
};

template < class Data > CContext< Data >::CContext(const bool & parallel)
  : mMasterData(NULL)
  , mThreadData(NULL)
  , mParallel(parallel)
  , mSize(0)
{}

template < class Data > CContext< Data >::CContext(const CContext & src)
  : mMasterData(NULL)
  , mThreadData(NULL)
  , mParallel(src.mParallel)
  , mSize(0)
{
  init();

  *mMasterData = *src.mMasterData;

  Data * pIt = mThreadData;
  Data * pEnd = mThreadData + mSize;
  const Data * pSrc = src.mThreadData;

  for (; pIt != pEnd; ++pIt, ++pSrc)
    if (isThread(pIt))
      *pIt = *pSrc;
}

template < class Data > CContext< Data >::~CContext()
{
  release();
}

template < class Data > CContext< Data > & CContext< Data >::operator = (const CContext< Data > & rhs)
{
  if (this != &rhs)
    {
      init();

      *mMasterData = *rhs.mMasterData;

      Data * pIt = mThreadData;
      Data * pEnd = mThreadData + mSize;
      const Data * pRhs = rhs.mThreadData;

      for (; pIt != pEnd; ++pIt, ++pRhs)
        if (isThread(pIt))
          *pIt = *pRhs;
    }

  return *this;
}

template < class Data > bool CContext< Data >::operator == (const CContext< Data > & rhs) const
{
  if (mSize != rhs.mSize)
    return false;

  if (memcmp(mMasterData, rhs.mMasterData, sizeof(Data)))
    return false;

  const Data * pIt = mThreadData;
  const Data * pEnd = mThreadData + mSize;
  const Data * pRhs = rhs.mThreadData;

  for (; pIt != pEnd; ++pIt, ++pRhs)
    if (isThread(pIt)
        && memcmp(pIt, pRhs, sizeof(Data)))
      return false;

  return true;
}

template < class Data > void CContext< Data >::init()
{
  if (mSize != 0)
    return;

  mMasterData = new Data();
  mSize = mParallel ? omp_get_max_threads() : 1;

  if (mSize > 1)
    {
      mThreadData = new Data[mSize];
    }
  else
    {
      mThreadData = mMasterData;
    }
}

template < class Data > void CContext< Data >::release()
{
  if (mMasterData != NULL)
    {
      delete mMasterData;
      mMasterData = NULL;

      if (mSize == 1)
        mThreadData = NULL;
    }

  if (mThreadData != NULL)
    {
      delete [] mThreadData;
      mThreadData = NULL;
    }

  mSize = 0;
}

template < class Data > Data & CContext< Data >::master()
{
  return *mMasterData;
}

template < class Data > Data & CContext< Data >::active()
{
  switch (omp_get_num_threads())
    {
      case 1:
        return *mMasterData;
        break;

      default:
        return mThreadData[omp_get_thread_num()];
        break;
    }

  return *mMasterData;
}

template < class Data > const Data & CContext< Data >::master() const
{
  return *mMasterData;
}

template < class Data > const Data & CContext< Data >::active() const
{
  switch (omp_get_num_threads())
    {
      case 1:
        return *mMasterData;
        break;

      default:
        return mThreadData[omp_get_thread_num()];
        break;
    }

  return *mMasterData;
}

template < class Data > Data * CContext< Data >::beginThread()
{
  return mThreadData;
}

template < class Data > Data * CContext< Data >::endThread()
{
  return mThreadData + mSize;
}

template < class Data > const Data * CContext< Data >::beginThread() const
{
  return mThreadData;
}

template < class Data > const Data * CContext< Data >::endThread() const
{
  return mThreadData + mSize;
}

template < class Data > bool CContext< Data >::isMaster(const Data * data) const
{
  return mMasterData == data;
}

template < class Data > bool CContext< Data >::isThread(const Data * data) const
{
  return mMasterData != data;
}

template < class Data > int CContext< Data >::localIndex(const Data * data) const
{
  if (mThreadData <= data && data < mThreadData + mSize)
    return data - mThreadData;

  return -1;
}

template < class Data > int CContext< Data >::globalIndex(const Data * data) const
{
  int GlobalIndex = isMaster(data) ? 0 : localIndex(data);

  if (GlobalIndex != -1)
    {
      int MPIRank;
      MPI_Comm_rank(MPI_COMM_WORLD, &MPIRank);
      GlobalIndex += MPIRank * mSize;
    }

  return GlobalIndex;
}

template < class Data > const size_t & CContext< Data >::size() const
{
  return mSize;
}

#endif // COPASI_CCONTEXT
