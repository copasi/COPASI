/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDirEntry.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/12 19:04:36 $
   End CVS Header */

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <direct.h>

#ifdef WIN32
# define stat _stat
# define S_IFREG _S_IFREG
# define S_IFDIR _S_IFDIR
# define access _access
# define mkdir _mkdir
# define rmdir _rmdir
#else
#endif

#include "copasi.h"

#include "CDirEntry.h"

bool CDirEntry::isFile(const std::string & path)
{
  struct stat st;
  if (stat(path.c_str(), & st) == -1) return false;

  return ((st.st_mode | S_IFREG) != 0);
}

bool CDirEntry::isDir(const std::string & path)
{
  struct stat st;
  if (stat(path.c_str(), & st) == -1) return false;

  return ((st.st_mode | S_IFDIR) != 0);
}

bool CDirEntry::exist(const std::string & path)
{
  struct stat st;
  if (stat(path.c_str(), & st) == -1) return false;

  return ((st.st_mode | S_IFREG) || (st.st_mode | S_IFDIR));
}

bool CDirEntry::isReadable(const std::string & path)
{return (access(path.c_str(), 0x4) == 0);}

bool CDirEntry::isWritable(const std::string & path)
{return (access(path.c_str(), 0x2) == 0);}

bool CDirEntry::createDir(const std::string & dir,
                          const std::string & parent)
{
  std::string Separator;
#ifdef WIN32
  Separator = "\\";
#else
  Separator = "/";
#endif

  std::string Dir;
  if (parent != "") Dir = parent + Separator;
  Dir += dir;

  // Check whether the directory already exists and is writable.
  if (isDir(Dir) && isWritable(Dir)) return true;

  // Check whether the parent directory exists and is writable.
  if (!isDir(parent) || !isWritable(parent)) return false;

  return (mkdir(Dir.c_str()) == 0);
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
  // :TODO:
#ifdef XXXX
#ifdef WIN32

  // Append to the "path" mask for all files in directory
  string pattern = path_base + string("*");

  bool skip_recursive_entry;

  // Open directory stream and try read info about first entry
  struct _finddata_t entry;
  long desc = _findfirst(pattern.c_str(), &entry);
  if (desc != -1)
    {
      skip_recursive_entry = (mode == eIgnoreRecursive) &&
                             ((::strcmp(entry.name, ".") == 0) ||
                              (::strcmp(entry.name, "..") == 0));
      // check all masks
      if (!skip_recursive_entry)
        {
          ITERATE(vector<string>, it, masks)
          {
            const string& mask = *it;
            if (mask.empty() ||
                 MatchesMask(entry.name, mask.c_str(), use_case))
              {
                s_AddDirEntry(contents, path_base + entry.name);
                break;
              }
          } // ITERATE
        }

      while (_findnext(desc, &entry) != -1)
        {
          if ((mode == eIgnoreRecursive) &&
               ((::strcmp(entry.name, ".") == 0) ||
                (::strcmp(entry.name, "..") == 0)))
            {
              continue;
            }
          ITERATE(vector<string>, it, masks)
          {
            const string& mask = *it;
            if (mask.empty() ||
                 MatchesMask(entry.name, mask.c_str(), use_case))
              {
                s_AddDirEntry(contents, path_base + entry.name);
                break;
              }
          } // ITERATE
        }
      _findclose(desc);
    }

#else
  DIR* dir = opendir(GetPath().c_str());
  if (dir)
    {
      while (struct dirent* entry = readdir(dir))
        {
          if ((mode == eIgnoreRecursive) &&
               ((::strcmp(entry->d_name, ".") == 0) ||
                (::strcmp(entry->d_name, "..") == 0)))
            {
              continue;
            }
          ITERATE(vector<string>, it, masks)
          {
            const string& mask = *it;
            if (mask.empty() ||
                 MatchesMask(entry->d_name, mask.c_str(), use_case))
              {
                s_AddDirEntry(contents, path_base + entry->d_name);
                break;
              }
          } // ITERATE
        } // while
      closedir(dir);
    }
#endif // WIN32
#endif // XXXX
  return false;
}
