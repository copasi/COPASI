// Copyright (C) 2020 - 2025 by Pedro Mendes, Rector and Visitors of the
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
  bool singleThreadedExecution();
  bool multiThreaded();
  int localThreadIndex();

  CContext(const bool & parallel = true);
  CContext(const CContext & src);
  ~CContext();
  CContext & operator = (const CContext & rhs);
  bool operator == (const CContext & rhs) const;

  void init();
  void release();
  Data & master();
  Data & active();
  Data * threadData();
  const Data & master() const;
  const Data & active() const;
  Data const * threadData() const;

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
  Data * mpMasterData;
  Data * mThreadData;
  bool mParallel;
  size_t mSize;
};

template < class Data > bool CContext< Data >::singleThreadedExecution()
{
  return omp_get_num_threads() == 1;
}

template < class Data > bool CContext< Data >::multiThreaded()
{
  return mSize > 1;
}

template < class Data > int CContext< Data >::localThreadIndex()
{
  return omp_get_thread_num();
}

template < class Data > CContext< Data >::CContext(const bool & parallel)
  : mpMasterData(NULL)
  , mThreadData(NULL)
  , mParallel(parallel)
  , mSize(0)
{}

template < class Data > CContext< Data >::CContext(const CContext & src)
  : mpMasterData(NULL)
  , mThreadData(NULL)
  , mParallel(src.mParallel)
  , mSize(0)
{
  init();

  *mpMasterData = *src.mpMasterData;

  if (mSize > 1)
#pragma omp parallel for
    for (size_t i = 0; i < mSize; ++i)
      mThreadData[i] = src.mThreadData[i];
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

      *mpMasterData = *rhs.mpMasterData;

      if (mSize > 1)
#pragma omp parallel for
        for (size_t i = 0; i < mSize; ++i)
          mThreadData[i] = rhs.mThreadData[i];
    }

  return *this;
}

template < class Data > bool CContext< Data >::operator == (const CContext< Data > & rhs) const
{
  if (mSize != rhs.mSize)
    return false;

  if (!(mpMasterData == rhs.mpMasterData))
    return false;

  bool equal = true;

  if (mSize > 1)
#pragma omp parallel for reduction(& : equal)
    for (size_t i = 0; i < mSize; ++i)
      equal = mThreadData[i] == rhs.mThreadData[i];

  return equal;
}

template < class Data > void CContext< Data >::init()
{
  if (mSize != 0)
    return;

  mpMasterData = new Data();
  mSize = mParallel ? omp_get_max_threads() : 1;

  if (mSize > 1)
    {
      mThreadData = new Data[mSize];
    }
  else
    {
      mThreadData = mpMasterData;
    }
}

template < class Data > void CContext< Data >::release()
{
  if (mpMasterData != NULL)
    {
      delete mpMasterData;
      mpMasterData = NULL;

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
  return *mpMasterData;
}

template < class Data > Data & CContext< Data >::active()
{
  switch (omp_get_num_threads())
    {
      case 1:
        return *mpMasterData;
        break;

      default:
        return mThreadData[omp_get_thread_num()];
        break;
    }

  return *mpMasterData;
}

template < class Data > Data * CContext< Data >::threadData()
{
  return mThreadData;
}

template < class Data > const Data & CContext< Data >::master() const
{
  return *mpMasterData;
}

template < class Data > const Data & CContext< Data >::active() const
{
  switch (omp_get_num_threads())
    {
      case 1:
        return *mpMasterData;
        break;

      default:
        return mThreadData[omp_get_thread_num()];
        break;
    }

  return *mpMasterData;
}

template < class Data > Data const * CContext< Data >::threadData() const
{
  return mThreadData;
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
  return mpMasterData == data;
}

template < class Data > bool CContext< Data >::isThread(const Data * data) const
{
  return mpMasterData != data;
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
