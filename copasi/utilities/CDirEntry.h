/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDirEntry.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/16 20:45:09 $
   End CVS Header */

#ifndef COPASI_CDirEntry
#define COPASI_CDirEntry

#include <string>
#include <vector>

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

    static std::vector< std::string > compilePattern(const std::string & pattern);

    static bool match(const std::string & name,
                      const std::vector< std::string > & pattern);

  private:
    static bool check(const std::string & name,
                      const std::string pattern,
                      std::string::size_type & at,
                      std::string::size_type & after);
  };

#endif // COPASI_CDirEntry
