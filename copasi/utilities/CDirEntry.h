/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDirEntry.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/16 21:19:04 $
   End CVS Header */

#ifndef COPASI_CDirEntry
#define COPASI_CDirEntry

#include <string>
#include <vector>

/**
 * This class provides an OS independent interface to directory entries
 * such as files and directories.
 */
class CDirEntry
  {
  public:
    /**
     * Check whether the directory entry specified by 'path' is
     * a file.
     * @param const std::string & path
     * @return bool isFile
     */
    static bool isFile(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' is
     * is a directory.
     * @param const std::string & path
     * @return bool isDir
     */
    static bool isDir(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' exists.
     * @param const std::string & path
     * @return bool exist
     */
    static bool exist(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' is
     * is readable.
     * @param const std::string & path
     * @return bool isReadable
     */
    static bool isReadable(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' is
     * writable.
     * @param const std::string & path
     * @return bool isWritable
     */
    static bool isWritable(const std::string & path);

    /**
     * Create the directory 'dir' in the parent directory 'parent'.
     * @param const std::string & dir
     * @param const std::string & parent (Default: current working directory)
     * @return bool success
     */
    static bool createDir(const std::string & dir,
                          const std::string & parent = "");

    /**
     * Removes a file or directory specified by path.
     * @param const std::string & path
     * @return bool success
     */
    static bool remove(const std::string & path);

    /**
     * Remove files or directories matching the pattern in directory dir.
     * @param const std::string & pattern
     * @param const std::string & dir
     * @return bool success
     */
    static bool removeFiles(const std::string & pattern,
                            const std::string & dir);

    /**
     * Compiles the pattern to a patternList. Valid wildcards in the pattern are:
     * '*' matches any number of characters and '?' matches exactly one character. 
     * @param const std::string & pattern
     * @return std::vector< std::string > patternList 
     */
    static std::vector< std::string > compilePattern(const std::string & pattern);

    /**
     * Compare the name against the pattern list and returns whether the 
     * name matches. The patternList can be created from a pattern by the 
     * compilePattern method. 
     * @param const std::string & name
     * @param const std::vector< std::string > & patternList
     * @return bool match
     */
    static bool match(const std::string & name,
                      const std::vector< std::string > & patternList);

  private:
    /**
     * This private methods checks whether the active section matches the
     * secified patter. The section is automatically advanced to allow 
     * repeated calls. On the first call 'at' must be 0. The parameters 
     * 'at' and 'after' must not be changed outside this method.
     * @param const std::string & name
     * @param const std::string pattern
     * @param std::string::size_type & at
     * @param std::string::size_type & after
     * @return bool match
     */
    static bool check(const std::string & name,
                      const std::string pattern,
                      std::string::size_type & at,
                      std::string::size_type & after);
  };

#endif // COPASI_CDirEntry
