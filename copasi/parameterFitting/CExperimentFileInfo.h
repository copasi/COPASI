/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentFileInfo.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/25 18:17:41 $
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
    bool setFilename(const std::string & filename);

    /**
     *
     */
    bool sync();

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
    std::string mFilename;

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
    unsigned C_INT32 mUnusedEnd;
  };

#endif // COPASI_CExperimentFileInfo
