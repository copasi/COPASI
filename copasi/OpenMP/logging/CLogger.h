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

#ifndef UTILITIES_CLOGGER_H
#define UTILITIES_CLOGGER_H

#include <stack>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

#include "copasi/OpenMP/CContext.h"

class CLogger
{
private:
  template < int LEVEL >
  class CStream
  {
  public:
    CStream() = delete;
    template< class ... Arguments >
    CStream(const std::string & format, Arguments ... arguments);
    virtual ~CStream();
  };

public :
  typedef spdlog::level::level_enum LogLevel;

  struct LoggerData
  {
    std::shared_ptr< spdlog::logger > pLogger;
    std::shared_ptr< spdlog::sinks::sink > pConsole;
    std::shared_ptr< spdlog::sinks::sink > pFile;
    std::string task;
    std::stack< spdlog::level::level_enum > levels;
  };

  static void init();

  static void finalize();

  static void setLevel(LogLevel level);

  static void pushLevel(LogLevel level);

  static void popLevel();

  static LogLevel level();

  static void setTask();

  static void setLogDir(const std::string dir);

  static std::string sanitize(std::string dirty);

  static bool hasErrors();

  static void setSingle(bool single);

  typedef CStream< spdlog::level::trace > trace;
  typedef CStream< spdlog::level::debug > debug;
  typedef CStream< spdlog::level::info > info;
  typedef CStream< spdlog::level::warn > warn;
  typedef CStream< spdlog::level::err > error;
  typedef CStream< spdlog::level::critical > critical;
  typedef CStream< spdlog::level::off > off;

private:
  static void initData(LoggerData & loggerData);
  static void releaseData(LoggerData & loggerData);
  static void setLevel();
  static bool haveErrors;
  static int single;
  static CContext< LoggerData > Context;
};

template < int LEVEL >
template< class ... Arguments >
  CLogger::CStream< LEVEL >::CStream(const std::string & format, Arguments ... arguments)
{
  if (Context.active().levels.top() > static_cast< LogLevel >(LEVEL))
    return;

  size_t iStart, iEnd;

  if (Context.singleThreadedExecution()
      || single == Context.localThreadIndex())
    {
      iStart = 0;
      iEnd = Context.size();
    }
  else
    {
      iStart = Context.localThreadIndex();
      iEnd = iStart + 1;
    }

#pragma omp parallel for
  for (size_t i = iStart; i < iEnd; ++i)
    {
      switch (static_cast< LogLevel >(LEVEL))
        {
        case spdlog::level::trace:
          Context.threadData()[i].pLogger->trace(Context.threadData()[i].task + " " + format, arguments...);
          break;
        case spdlog::level::debug:
          Context.threadData()[i].pLogger->debug(Context.threadData()[i].task + " " + format, arguments...);
          break;
        case spdlog::level::info:
          Context.threadData()[i].pLogger->info(Context.threadData()[i].task + " " + format, arguments...);
          break;
        case spdlog::level::warn:
          Context.threadData()[i].pLogger->warn(Context.threadData()[i].task + " " + format, arguments...);
          break;
        case spdlog::level::err:
#pragma omp atomic
          haveErrors |= true;
          Context.threadData()[i].pLogger->error(Context.threadData()[i].task + " " + format, arguments...);
          break;
        case spdlog::level::critical:
#pragma omp atomic
          haveErrors |= true;
          Context.threadData()[i].pLogger->critical(Context.threadData()[i].task + " " + format, arguments...);
          break;
        case spdlog::level::off:
          break;
        }

      Context.threadData()[i].pLogger->flush();
    }
}

// virtual
template < int LEVEL >
CLogger::CStream< LEVEL >::~CStream()
{}

#endif // UTILITIES_CLOGGER_H
