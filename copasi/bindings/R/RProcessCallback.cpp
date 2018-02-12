#include "RProcessCallback.h"
#include <R_ext/Utils.h>

bool 
RProcessCallback::proceed()
{
  R_CheckUserInterrupt();
  return CProcessReport::proceed();
}

RProcessCallback::RProcessCallback(const unsigned int & maxTime)
: CProcessReport(maxTime)
{
}

RProcessCallback::~RProcessCallback()
{
}

bool 
RProcessCallback::progress()
{
  R_CheckUserInterrupt();
  return CProcessReport::proceed();
}

bool 
RProcessCallback::progressItem(const size_t &handle)
{
  R_CheckUserInterrupt();
  return CProcessReport::progressItem(handle);
}

bool 
RProcessCallback::reset()
{
  R_CheckUserInterrupt();
  return CProcessReport::reset();
}

bool 
RProcessCallback::finish()
{
  R_CheckUserInterrupt();
  return CProcessReport::finish();
}

