// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef STRESS_TEST_H__
#define STRESS_TEST_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#ifdef WIN32
#include <time.h>
#include <windows.h>
#include <sys/timeb.h>
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
#else
#include <sys/time.h>
#endif

class CNormalFraction;
class Model;
class CDataModel;
class ASTNode;
class Reaction;

// This test reads all models from the biomodels database and normalizes all
// mathematical expressions it finds in there.
// Later on, it will do the same for the functions in COPASIs function database
// and compare the expressions from the model to those in the function database
// in order to find out if they are the same.
class stress_test
{
#ifdef WIN32
  struct timeval
  {
    time_t  tv_sec;         /* seconds */
    long tv_usec;    /* and microseconds */
  };

  struct timezone
  {
    int  tz_minuteswest; /* minutes W of Greenwich */
    int  tz_dsttime;     /* type of dst correction */
  };

  int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if (NULL != tv)
      {
        GetSystemTimeAsFileTime(&ft);

        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

        /*converting file time to unix epoch*/
        tmpres -= DELTA_EPOCH_IN_MICROSECS;
        tmpres /= 10;  /*convert into microseconds*/
        tv->tv_sec = (long)(tmpres / 1000000UL);
        tv->tv_usec = (long)(tmpres % 1000000UL);
      }

    if (NULL != tz)
      {
        if (!tzflag)
          {
            _tzset();
            tzflag++;
          }

        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
      }

    return 0;
  }
#endif
public:
  /**
   * Constructor.
   */
  stress_test();

  /**
   * Destructor.
   */
  virtual ~stress_test();

  /**
   * Goes through the list of files, loads each file and normalizes the
   * mathematical expressions in the contained model.
   */
  void run(const std::vector<std::string>& filenames);

protected:
  /**
   * Loads an sbml model from the given file and
   * normalized all mathematical expressions in the SBML model.
   */
  void normalizeMath(const std::string& filename);

  /**
   * Normalizes all expressions but the function definitions in the given
   * model.
  void normalizeExpressions(const Model* pModel);
   */

  /**
   * Normalizes the function definitions in the given model.
  void normalizeFunctionDefinitions(const Model* pModel);
   */

  /**
   * Normalizes all expressions but the function definitions in the given
   * model.
   */
  void normalizeAndSimplifyExpressions(const Model* pModel);

  /**
   * Normalizes the function definitions in the given model.
   */
  void normalizeAndSimplifyFunctionDefinitions(const Model* pModel);

  /**
   * Normalizes COPASIs function database.
   */
  void normalizeFunctionDB();

  static bool normalize_names(ASTNode* pNode, const Reaction* pReaction, const Model* pModel);

protected:
  unsigned int mNumFunctionDefinitions;
  unsigned int mNumExceededFunctions;
  unsigned int mNumFailedFunctions;
  unsigned int mNumExpressions;
  unsigned int mNumExceeded;
  unsigned int mNumFailed;
  unsigned int mNumCOPASIFunctions;
  unsigned int mNumExceededCOPASIFunctions;
  unsigned int mNumFailedCOPASIFunctions;
  unsigned int mNumFiles;
  unsigned int mNumKineticFunctions;
  unsigned int mNumMassActionsKinetics;
  unsigned int mNumConstantFluxKinetics;
  unsigned int mNumMappedKineticExpressions;
  unsigned int mNumUnmappedKineticExpressions;
  std::vector<CNormalFraction*> mNormalizedExpressions;
  std::vector<std::pair<std::string, CNormalFraction*> > mNormalizedFunctionDefinitions;
  std::multimap<std::string, CNormalFraction*> mNormalizedCOPASIFunctionDefinitions;
  std::vector<std::string> mUnreadableFiles;
  std::map<std::string, unsigned int> mExpressionMappings;
  std::map<int, std::vector<CNormalFraction*> > mSBOMap;
  std::map<CNormalFraction*, int> mUnknownCategories;
  unsigned int mDifferentNormalform;
  unsigned int mNumSBO;
  CDataModel* mpDataModel;
  struct timeval mTV1;
  struct timezone mTZ1;
  struct timeval mTV2;
  struct timezone mTZ2;
  std::set<double> mProcessTimes;
};

#endif // STRESS_TEST_H__
