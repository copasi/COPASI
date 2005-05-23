/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDirEntry.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/23 17:20:25 $
   End CVS Header */

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
# include <io.h>
# include <direct.h>
# define stat _stat
# define S_IFREG _S_IFREG
# define S_IFDIR _S_IFDIR
# define access _access
# define mkdir _mkdir
# define rmdir _rmdir
#else
# include <dirent.h>
# include <unistd.h>
#endif // WIN32

#include "copasi.h"

#include "CDirEntry.h"

#ifdef WIN32
const std::string CDirEntry::Separator = "\\";
#else
const std::string CDirEntry::Separator = "/";
#endif

bool CDirEntry::isFile(const std::string & path)
{
  struct stat st;
  if (stat(path.c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFREG) == S_IFREG);
#else
  return S_ISREG(st.st_mode);
#endif
}

bool CDirEntry::isDir(const std::string & path)
{
  struct stat st;
  if (stat(path.c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFDIR) == S_IFDIR);
#else
  return S_ISDIR(st.st_mode);
#endif
}

bool CDirEntry::exist(const std::string & path)
{
  struct stat st;
  if (stat(path.c_str(), & st) == -1) return false;

#ifdef WIN32
  return ((st.st_mode & S_IFREG) == S_IFREG ||
          (st.st_mode & S_IFDIR) == S_IFDIR);
#else
  return (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode));
#endif
}

bool CDirEntry::isReadable(const std::string & path)
{return (access(path.c_str(), 0x4) == 0);}

bool CDirEntry::isWritable(const std::string & path)
{return (access(path.c_str(), 0x2) == 0);}

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

std::string CDirEntry::dirName(const std::string & path)
{
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
  if (parent != "") Dir = parent + Separator;
  Dir += dir;

  // Check whether the directory already exists and is writable.
  if (isDir(Dir) && isWritable(Dir)) return true;

  // Check whether the parent directory exists and is writable.
  if (!isDir(parent) || !isWritable(parent)) return false;

#ifdef WIN32
  return (mkdir(Dir.c_str()) == 0);
#else
  return (mkdir(Dir.c_str(), 0) == 0);
#endif
}

bool CDirEntry::remove(const std::string & path)
{
  if (isDir(path))
    return (rmdir(path.c_str()) == 0);
  else if (isFile(path))
    return (::remove(path.c_str()) == 0);

  return false;
}

bool CDirEntry::removeFiles(const std::string & pattern,
                            const std::string & path)
{
  bool success = true;
  std::vector< std::string > PatternList;

  PatternList = compilePattern(pattern);

#ifdef WIN32

  // We want the same pattern matching behaviour for all platforms.
  // Therefore, we do not use the MS provided one and list all files instead.
  std::string FilePattern = path + "\\*";

  // Open directory stream and try read info about first entry
  struct _finddata_t Entry;
  C_INT32 hList = _findfirst(FilePattern.c_str(), &Entry);

  if (hList == -1) return success;

  do
    {
      if (match(Entry.name, PatternList))
        {
          if (Entry.attrib | _A_NORMAL)
            {
              if (::remove((path + Separator + Entry.name).c_str()) != 0) success = false;
            }
          else
            {
              if (rmdir((path + Separator + Entry.name).c_str()) != 0) success = false;
            }
        }
    }
  while (_findnext(hList, &Entry) == 0);

  _findclose(hList);

#else

  DIR * pDir = opendir(path.c_str());
  if (!pDir) return false;

  struct dirent * pEntry;

  while ((pEntry = readdir(pDir)) != NULL)
    {
      if (match(pEntry->d_name, PatternList))
        {
          if (isDir(pEntry->d_name))
            {
              if (rmdir((path + Separator + pEntry->d_name).c_str()) != 0)
                success = false;
            }
          else
            {
              if (::remove((path + Separator + pEntry->d_name).c_str()) != 0)
                success = false;
            }
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

  while (pos != std::string::npos)
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
  std::vector< std::string >::const_iterator it = patternList.begin();
  std::vector< std::string >::const_iterator end = patternList.end();
  std::string::size_type at = 0;
  std::string::size_type after = 0;

  bool Match = true;
  while (it != end && Match)
    Match = matchInternal(name, *it++, at, after);

  return Match;
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
