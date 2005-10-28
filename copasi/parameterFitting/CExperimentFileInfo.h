/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentFileInfo.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/28 15:42:03 $
   End CVS Header */

#ifndef COPASI_CExperimentFileInfo
 #define COPASI_CExperimentFileInfo

#include <string>
 #include <vector>

class CExperimentSet;
class CExperiment;

/**
 *
 */
class CExperimentFileInfo
  {
  private:
    /**
     *
     */
    class CExperimentInfo
      {
        // Operations
      private:
        /**
         *
         */
        CExperimentInfo();

      public:
        /**
         *
         */
        CExperimentInfo(CExperiment & Experiment);

        /**
         *
         */
        ~CExperimentInfo();

        // Attributes
      public:
        /**
         *
         */
        CExperiment * pExperiment;

        /**
         *
         */
        unsigned C_INT32 First;

        /**
         *
         */
        unsigned C_INT32 Last;
      };

    // Operations
  private:
    /**
     *
     */
    CExperimentFileInfo();

  public:
    /**
     *
     */
    CExperimentFileInfo(CExperimentSet & set);

    /**
     *
     */
    ~CExperimentFileInfo();

    /**
     *
     */
    bool setFileName(const std::string & fileName);

    /**
     *
     */
    const std::string & getFileName() const;

    /**
     *
     */
    bool sync();

    /**
     *
     */
    bool validate() const;

    /**
     *
     */
    bool validateFirst(const unsigned C_INT32 & index,
                       const unsigned C_INT32 & value);

    /**
     *
     */
    bool validateLast(const unsigned C_INT32 & index,
                      const unsigned C_INT32 & value);

    /**
     *
     */
    bool validateHeader(const unsigned C_INT32 & index,
                        const unsigned C_INT32 & value);

    /**
     *
     */
    std::vector< std::string > getExperimentNames() const;

    /**
     *
     */
    CExperiment * getExperiment(const std::string & name);

    /**
     *
     */
    bool getFirstUnusedSection(unsigned C_INT32 & First,
                               unsigned C_INT32 & Last);

    /**
     *
     */
    bool getNextUnusedSection(unsigned C_INT32 & First,
                              unsigned C_INT32 & Last);

    // Attributes
  private:
    /**
     *
     */
    CExperimentSet * mpSet;

    /**
     *
     */
    std::string mFileName;

    /**
     *
     */
    std::vector< CExperimentInfo * > mList;

    /**
     *
     */
    unsigned C_INT32 mLines;

    /**
     *
     */
    unsigned C_INT32 mUsedEnd;
  };

#endif // COPASI_CExperimentFileInfo
