// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(WIN32) && !defined(__MINGW32__) && !defined(__MINGW64__)
# include <io.h>
# include <direct.h>
typedef struct _stat STAT;
# define stat _wstat
# define S_IFREG _S_IFREG
# define S_IFDIR _S_IFDIR
# define access _waccess
# define rename _wrename
# define mkdir _wmkdir
# define rmdir _wrmdir
#else
typedef struct stat STAT;
# include <dirent.h>
# include <unistd.h>
#endif // WIN32

#include "copasi/copasi.h"

#include "CDirEntry.h"
#include "utility.h"
#include "CCopasiMessage.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/commandline/CLocaleString.h"

#ifdef WIN32
# include "copasi/commandline/COptions.h"
const std::string CDirEntry::Separator = "\\";
#else
const std::string CDirEntry::Separator = "/";
#endif

bool CDirEntry::isFile(const std::string & path)
{
  STAT st;

  if (stat(CLocaleString::fromUtf8(path).c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFREG) == S_IFREG);
#else
  return S_ISREG(st.st_mode);
#endif
}

bool CDirEntry::isDir(const std::string & path)
{
  STAT st;

  if (stat(CLocaleString::fromUtf8(path).c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFDIR) == S_IFDIR);
#else
  return S_ISDIR(st.st_mode);
#endif
}

bool CDirEntry::exist(const std::string & path)
{
  STAT st;

  if (stat(CLocaleString::fromUtf8(path).c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFREG) == S_IFREG ||
          (st.st_mode & S_IFDIR) == S_IFDIR);
#else
  return (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode));
#endif
}

bool CDirEntry::isReadable(const std::string & path)
{return (access(CLocaleString::fromUtf8(path).c_str(), 0x4) == 0);}

bool CDirEntry::isWritable(const std::string & path)
{return (access(CLocaleString::fromUtf8(path).c_str(), 0x2) == 0);}

std::string CDirEntry::baseName(const std::string & path)
{
  std::string::size_type start = path.find_last_of(Separator);
#ifdef WIN32 // WIN32 also understands '/' as the separator.

  if (start == std::string::npos)
    start = path.find_last_of("/");

#endif

  if (start == std::string::npos) start = 0;
  else start++; // We do not want the separator.

  std::string::size_type end = path.find_last_of(".");

  if (end == std::string::npos || end < start)
    end = path.length();

  return path.substr(start, end - start);
}

std::string CDirEntry::fileName(const std::string & path)
{
  std::string::size_type start = path.find_last_of(Separator);
#ifdef WIN32 // WIN32 also understands '/' as the separator.

  if (start == std::string::npos)
    start = path.find_last_of("/");

#endif

  if (start == std::string::npos) start = 0;
  else start++; // We do not want the separator.

  return path.substr(start);
}

std::string CDirEntry::dirName(const std::string & path)
{
  if (path == "") return path;

#ifdef WIN32 // WIN32 also understands '/' as the separator.
  std::string::size_type end = path.find_last_of(Separator + "/");
#else
  std::string::size_type end = path.find_last_of(Separator);
#endif

  if (end == path.length() - 1)
    {
#ifdef WIN32 // WIN32 also understands '/' as the separator.
      end = path.find_last_of(Separator + "/", end);
#else
      end = path.find_last_of(Separator, end);
#endif
    }

  if (end == std::string::npos) return "";

  return path.substr(0, end);
}

std::string CDirEntry::suffix(const std::string & path)
{
  std::string::size_type start = path.find_last_of(Separator);
#ifdef WIN32 // WIN32 also understands '/' as the separator.

  if (start == std::string::npos)
    start = path.find_last_of("/");

#endif

  if (start == std::string::npos) start = 0;
  else start++; // We do not want the separator.

  std::string::size_type end = path.find_last_of(".");

  if (end == std::string::npos || end < start)
    return "";
  else
    return path.substr(end);
}

bool CDirEntry::createDir(const std::string & dir,
                          const std::string & parent)
{
  std::string Dir;

  if (!parent.empty()) Dir = parent + Separator;

  Dir += dir;

  // Check whether the directory already exists and is writable.
  if (isDir(Dir) && isWritable(Dir)) return true;

  // Check whether the parent directory exists and is writable.
  if (!parent.empty() && (!isDir(parent) || !isWritable(parent)))
    return false;

#ifdef WIN32
  return (mkdir(CLocaleString::fromUtf8(Dir).c_str()) == 0);
#else
  return (mkdir(CLocaleString::fromUtf8(Dir).c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == 0);
#endif
}

std::string CDirEntry::createTmpName(const std::string & dir,
                                     const std::string & suffix)
{
  if (!isDir(dir) || !isWritable(dir))
    {
      return "";
    }

  CRandom * pRandom = CRandom::createGenerator();

  CLocaleString Path = CLocaleString::fromUtf8(dir);
  std::string TmpName;
  int FD = 0;

  do
    {
      TmpName = Path.toUtf8() + Separator;

      unsigned C_INT32 Char;

      for (size_t i = 0; i < 8; i++)
        {
          Char = pRandom->getRandomU(35);

          if (Char < 10)
            TmpName += '0' + Char;
          else
            TmpName += 'a' - 10 + Char;
        }

      TmpName += suffix;
    }

#if defined(WIN32) && !defined(__MINGW32__) && !defined(__MINGW64__)

  while ((FD = _wcreat(CLocaleString::fromUtf8(TmpName).c_str(), _S_IREAD | _S_IWRITE)) == 0);

  if (FD != -1) // _close will terminate on bad file descriptor
    _close(FD);

#else

  while ((FD = creat(CLocaleString::fromUtf8(TmpName).c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == 0);

  close(FD);
#endif

  pdelete(pRandom);

  return TmpName;
}

bool CDirEntry::copy(const std::string & from,
                     const std::string & to)
{
  if (!isFile(from)) return false;

  std::string To = to;

  // Check whether To is a directory and append the
  // filename of from
  if (isDir(To))
    To += Separator + fileName(from);

  if (isDir(To)) return false;

  std::ifstream in(CLocaleString::fromUtf8(from).c_str());
  std::ofstream out(CLocaleString::fromUtf8(To).c_str());

  out << in.rdbuf();

  return out.good();
}

bool CDirEntry::move(const std::string & from,
                     const std::string & to)
{
  if (!isFile(from)) return false;

  std::string To = to;

  // Check whether To is a directory and append the
  // filename of from
  if (isDir(To))
    To += Separator + fileName(from);

  if (isDir(To)) return false;

#if defined(WIN32)

  // The target must not exist under WIN32 for rename to succeed.
  if (exist(To) && !remove(To))
    return false;

#endif // WIN32

  bool success =
    (rename(CLocaleString::fromUtf8(from).c_str(), CLocaleString::fromUtf8(To).c_str()) == 0);

  if (!success)
    {
      {
        std::ifstream in(CLocaleString::fromUtf8(from).c_str());
        std::ofstream out(CLocaleString::fromUtf8(To).c_str());

        out << in.rdbuf();

        success = out.good();
      }

      remove(from);
    }

  return success;
}

bool CDirEntry::remove(const std::string & path)
{
  if (isDir(path))
    return (rmdir(CLocaleString::fromUtf8(path).c_str()) == 0);
  else if (isFile(path))
#if defined(WIN32) && !defined(__MINGW32__) && !defined(__MINGW64__)
    return (_wremove(CLocaleString::fromUtf8(path).c_str()) == 0);

#else
    return (::remove(CLocaleString::fromUtf8(path).c_str()) == 0);
#endif

  return false;
}

bool CDirEntry::removeFiles(const std::string & pattern,
                            const std::string & path)
{
  bool success = true;
  std::vector< std::string > PatternList;

  PatternList = compilePattern(pattern);

#if defined(WIN32) && !defined(__MINGW32__) && !defined(__MINGW64__)

  // We want the same pattern matching behavior for all platforms.
  // Therefore, we do not use the MS provided one and list all files instead.
  std::string FilePattern = path + "\\*";

  // Open directory stream and try read info about first entry
  struct _wfinddata_t Entry;
  intptr_t hList = _wfindfirst(CLocaleString::fromUtf8(FilePattern).c_str(), &Entry);

  if (hList == -1) return success;

  do
    {
      std::string Utf8 = CLocaleString(Entry.name).toUtf8();

      if (match(Utf8, PatternList))
        {
          success &= remove(path + Separator + Utf8);
        }
    }
  while (_wfindnext(hList, &Entry) == 0);

  _findclose(hList);

#else

  DIR * pDir = opendir(CLocaleString::fromUtf8(path).c_str());

  if (!pDir) return false;

  struct dirent * pEntry;

  while ((pEntry = readdir(pDir)) != NULL)
    {
      std::string Utf8 = CLocaleString(pEntry->d_name).toUtf8();

      if (match(Utf8, PatternList))
        {
          success &= remove(path + Separator + Utf8);
        }
    }

  closedir(pDir);

#endif // WIN32

  return success;
}

std::vector< std::string > CDirEntry::compilePattern(const std::string & pattern)
{
  std::string::size_type pos = 0;
  std::string::size_type start = 0;
  std::string::size_type end = 0;
  std::vector< std::string > PatternList;

  while (pos < pattern.length())
    {
      start = pos;
      pos = pattern.find_first_of("*?", pos);

      end = std::min(pos, pattern.length());

      if (start != end)
        PatternList.push_back(pattern.substr(start, end - start));
      else
        {
          PatternList.push_back(pattern.substr(start, 1));
          pos++;
        }
    };

  return PatternList;
}

bool CDirEntry::match(const std::string & name,
                      const std::vector< std::string > & patternList)
{
  // We ignore . and ..
  if (name == "." || name == "..") return false;

  std::vector< std::string >::const_iterator it = patternList.begin();
  std::vector< std::string >::const_iterator end = patternList.end();
  std::string::size_type at = 0;
  std::string::size_type after = 0;

  bool Match = true;

  while (it != end && Match)
    Match = matchInternal(name, *it++, at, after);

  return Match;
}

bool CDirEntry::isRelativePath(const std::string & path)
{
#ifdef WIN32
  std::string Path = normalize(path);

  if (Path.length() < 2)
    return true;

  if (Path[1] == ':')
    return false;

  if (Path[0] == '/' && Path[1] == '/')
    return false;

  return true;
#else
  return (path.length() < 1 || path[0] != '/');
#endif
}

bool CDirEntry::makePathRelative(std::string & absolutePath,
                                 const std::string & relativeTo)
{
  if (isRelativePath(absolutePath) ||
      isRelativePath(relativeTo)) return false; // Nothing can be done.

  std:: string RelativeTo = normalize(relativeTo);

  if (isFile(RelativeTo)) RelativeTo = dirName(RelativeTo);

  if (!isDir(RelativeTo)) return false;

  absolutePath = normalize(absolutePath);

  size_t i, imax = std::min(absolutePath.length(), RelativeTo.length());

  for (i = 0; i < imax; i++)
    if (absolutePath[i] != RelativeTo[i]) break;

  // We need to retract to the beginning of the current directory.
  if (i != imax)
    i = absolutePath.find_last_of('/', i) + 1;

#ifdef WIN32

  if (i == 0) return false; // A different drive letter we cannot do anything

#endif

  RelativeTo = RelativeTo.substr(i);

  std::string relativePath;

  while (RelativeTo != "")
    {
      relativePath += "../";
      RelativeTo = dirName(RelativeTo);
    }

  if (relativePath != "")
    absolutePath = relativePath + absolutePath.substr(i);
  else
    absolutePath = absolutePath.substr(i + 1);

  return true;
}

bool CDirEntry::makePathAbsolute(std::string & relativePath,
                                 const std::string & absoluteTo)
{
  if (!isRelativePath(relativePath) ||
      isRelativePath(absoluteTo)) return false; // Nothing can be done.

  std:: string AbsoluteTo = normalize(absoluteTo);

  if (isFile(AbsoluteTo)) AbsoluteTo = dirName(AbsoluteTo);

  if (!isDir(AbsoluteTo)) return false;

  relativePath = normalize(relativePath);

  while (!relativePath.compare(0, 3, "../"))
    {
      AbsoluteTo = dirName(AbsoluteTo);
      relativePath = relativePath.substr(3);
    }

  relativePath = AbsoluteTo + "/" + relativePath;

  return true;
}

bool CDirEntry::matchInternal(const std::string & name,
                              const std::string pattern,
                              std::string::size_type & at,
                              std::string::size_type & after)
{
  bool Match = true;

  switch (pattern[0])
    {
      case '*':

        if (at != std::string::npos)
          {
            after = at;
            at = std::string::npos;
          }

        break;

      case '?':

        if (at != std::string::npos)
          {
            ++at;
            Match = (name.length() >= at);
          }
        else
          {
            ++after;
            Match = (name.length() >= after);
          }

        break;

      default:

        if (at != std::string::npos)
          {
            Match = (name.compare(at, pattern.length(), pattern) == 0);
            at += pattern.length();
          }
        else
          {
            at = name.find(pattern, after);
            Match = (at != std::string::npos);
            at += pattern.length();
          }

        break;
    }

  return Match;
}

std::string CDirEntry::normalize(const std::string & path)
{
  std::string Normalized = path;

#ifdef WIN32
  // converts all '\' to '/' (only on WIN32)
  size_t i, imax;

  for (i = 0, imax = Normalized.length(); i < imax; i++)
    if (Normalized[i] == '\\') Normalized[i] = '/';

  // if the path starts with /[^/] we prepend the current drive letter
  if (Normalized.length() > 0 && Normalized[0] == '/')
    {
      if ((Normalized.length() > 1 && Normalized[1] != '/') ||
          Normalized.length() == 1)
        {
          std::string PWD;
          COptions::getValue("PWD", PWD);

          Normalized = PWD.substr(0, 2) + Normalized;
        }
    }

#endif

  // Remove leading './'
  while (!Normalized.compare(0, 2, "./"))
    Normalized = Normalized.substr(2);

  // Collapse '//' to '/'
  std::string::size_type pos = 1;

  while (true)
    {
      pos = Normalized.find("//", pos);

      if (pos == std::string::npos) break;

      Normalized.erase(pos, 1);
    }

  // Collapse '/./' to '/'
  pos = 0;

  while (true)
    {
      pos = Normalized.find("/./", pos);

      if (pos == std::string::npos) break;

      Normalized.erase(pos, 2);
    }

  // Collapse '[^/]+/../' to '/'
  std::string::size_type start = Normalized.length();

  while (true)
    {
      pos = Normalized.rfind("/../", start);

      if (pos == std::string::npos) break;

      start = Normalized.rfind('/', pos - 1);

      if (start == std::string::npos) break;

      if (!Normalized.compare(start, 4, "/../")) continue;

      Normalized.erase(start, pos - start + 3);
      start = Normalized.length();
    }

  return Normalized;
}
