/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDirEntry.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/12 19:04:36 $
   End CVS Header */

#ifndef COPASI_CDirEntry
#define COPASI_CDirEntry

#include <string>

class CDirEntry
  {
  public:
    static bool isFile(const std::string & path);
    static bool isDir(const std::string & path);
    static bool exist(const std::string & path);
    static bool isReadable(const std::string & path);
    static bool isWritable(const std::string & path);
    static bool createDir(const std::string & dir,
                          const std::string & parent = "");
    static bool remove(const std::string & path);
    static bool removeFiles(const std::string & pattern,
                            const std::string & path);
  };

#endif // COPASI_CDirEntry
