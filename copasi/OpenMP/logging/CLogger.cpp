// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// BEGIN: Copyright
// MIT License
//
// Copyright (C) 2020 - 2024 Rector and Visitors of the University of Virginia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE
// END: Copyright

#include <iomanip>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <sstream>

#include "copasi/OpenMP/CLogger.h"

// static
bool CLogger::haveErrors = false;

// static
int CLogger::single = -1;

// static
CContext< CLogger::LoggerData > CLogger::Context = CContext< CLogger::LoggerData >();

// static
void CLogger::init()
{
  Context.init();

  initData(Context.master());

  if (Context.size() > 1)
#pragma omp parallel for
    for (size_t i = 0; i < Context.size(); ++i)
      initData(Context.threadData()[i]);

  spdlog::set_default_logger(Context.beginThread()->pLogger);
  spdlog::flush_every(std::chrono::seconds(5));
}

// static
void CLogger::initData(LoggerData & loggerData)
{
  loggerData.task = "";
  loggerData.levels = std::stack< LogLevel >();
  loggerData.levels.push(spdlog::level::warn);

  loggerData.pConsole = std::make_shared< spdlog::sinks::stdout_sink_st >();
  loggerData.pConsole->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%^%l%$] %v");
  loggerData.pConsole->set_level(loggerData.levels.top());

  loggerData.pLogger = std::make_shared< spdlog::logger >("Multi Sink", loggerData.pConsole);
  loggerData.pLogger->set_level(loggerData.levels.top());

  loggerData.pFile = NULL;
}

// static
void CLogger::releaseData(LoggerData & loggerData)
{
  loggerData.pConsole = NULL;
  loggerData.pLogger = NULL;
  loggerData.pFile = NULL;
}

// static
void CLogger::finalize()
{
  spdlog::shutdown();
}

// static
void CLogger::setLevel(LogLevel level)
{
  LoggerData & Active = Context.active();
  Active.levels = std::stack< LogLevel >();

  if (Context.singleThreadedExecution()
      && Context.multiThreaded())
#pragma omp parallel for
    for (size_t i = 0; i < Context.size(); ++i)
      Context.threadData()[i].levels = std::stack< LogLevel >();

  pushLevel(level);
}

// static
void CLogger::pushLevel(LogLevel level)
{
  LoggerData & Active = Context.active();
  Active.levels.push(level);

  if (Context.singleThreadedExecution()
      && Context.multiThreaded())
#pragma omp parallel for
    for (size_t i = 0; i < Context.size(); ++i)
      Context.threadData()[i].levels.push(level);

  setLevel();
}

// static
void CLogger::popLevel()
{
  LoggerData & Active = Context.active();
  if (Active.levels.size() > 1)
     Active.levels.pop();

  if (Context.singleThreadedExecution()
      && Context.multiThreaded())
#pragma omp parallel for
    for (size_t i = 0; i < Context.size(); ++i)
      Context.threadData()[i].levels.pop();

  setLevel();
}

// static
CLogger::LogLevel CLogger::level()
{
  return Context.active().levels.top();
}

// static
void CLogger::setLevel()
{
  LoggerData & Active = Context.active();

  Active.pLogger->set_level(Active.levels.top());
  Active.pConsole->set_level(std::max(Active.levels.top(), spdlog::level::warn));

  if (Active.pFile != NULL)
    Active.pFile->set_level(Active.levels.top());

  if (Context.singleThreadedExecution()
      && Context.multiThreaded())
#pragma omp parallel for
    for (size_t i = 0; i < Context.size(); ++i)
      {
        Context.threadData()[i].pLogger->set_level(Context.threadData()[i].levels.top());
        Context.threadData()[i].pConsole->set_level(std::max(Context.threadData()[i].levels.top(), spdlog::level::warn));

        if (Context.threadData()[i].pFile != NULL)
          Context.threadData()[i].pFile->set_level(Context.threadData()[i].levels.top());
      }
}

// static
void CLogger::setLogDir(const std::string dir)
{
  if (!Context.singleThreadedExecution())
    {
      CLogger::error("CLogger::setLogDir: This function may only be called single threaded.");
      return;
    }

  LoggerData & Master = Context.master();

  if (Master.levels.top() >= spdlog::level::warn)
    return;

  if (Context.size() == 1)
    {
      Master.pFile = std::make_shared< spdlog::sinks::basic_file_sink_st >(dir + "." + Master.task + ".log", true);
      Master.pFile->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%^%l%$] %v");
      Master.pFile->set_level(Master.levels.top());
      Master.pLogger->sinks().push_back(Master.pFile);
    }
  else
    {
      LoggerData *pIt = Context.beginThread();
      LoggerData *pEnd = Context.endThread();

#pragma omp parallel for
      for (size_t i = 0; i < Context.size(); ++i)
        {
          Context.threadData()[i].pFile = std::make_shared< spdlog::sinks::basic_file_sink_st >(dir + "." + Context.threadData()[i].task + ".log", true);
          Context.threadData()[i].pFile->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%^%l%$] %v");
          Context.threadData()[i].pFile->set_level(Context.threadData()[i].levels.top());
          Context.threadData()[i].pLogger->sinks().push_back(Context.threadData()[i].pFile);
        }
    }

  setLevel();
}

// static
void CLogger::setTask()
{
  if (!Context.singleThreadedExecution())
    {
      CLogger::error("CLogger::setTask: This function may only be called single threaded.");
      return;
    }

  std::ostringstream os;

  if (Context.size() == 1)
    {
      Context.master().task = os.str();
    }
  else
    {
      std::string Task = os.str();
      int width = log10(Context.size()) + 1;

#pragma omp parallel for
      for (size_t i = 0; i < Context.size(); ++i)
        {
          std::ostringstream os;
          os << Task << "[" << Context.size() << ":" << std::setfill('0') << std::setw(width) << i << "]";
          Context.threadData()[i].task = os.str();
        }
    }
}

// static
void CLogger::setSingle(bool s)
{
  int index = s ? Context.localThreadIndex() : -1;

#pragma omp atomic write
  single = index;
}

// static
bool CLogger::hasErrors()
{
  return haveErrors;
}

// static
std::string CLogger::sanitize(std::string dirty)
{
  std::replace(dirty.begin(), dirty.end(), '\n', ' ');
  std::replace(dirty.begin(), dirty.end(), '\t', ' ');
  return dirty;
}
