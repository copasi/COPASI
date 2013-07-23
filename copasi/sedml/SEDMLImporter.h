/**
 * SEDMLImporter.h
 * $Rev:               $:  Revision of last commit
 * $Author:            $:  Author of last commit
 * $Date:              $:  Date of last commit
 * $HeadURL:			 $
 * $Id::				 $
 */

#ifndef SEDMLIMPORTER_H_
#define SEDMLIMPORTER_H_

#include <string>
#include <map>
#include <set>
#include <utility>

#include "copasi/function/CFunctionDB.h"
//#include "copasi/sbml/StdException.h"
#include "copasi/model/CModel.h"

class SedDocument;
class SedUniformTimeCourse;
class SedSimulation;
class CTrajectoryTask;
class CCompartment;
class CMetab;
class Model;
class SedParameter;
class SedBase;
class CProcessReport;
class CPlotSpecification;


class SEDMLImporter {

protected:
  static
  C_FLOAT64 round(const C_FLOAT64 & x);

  static
  bool areApproximatelyEqual(const double & x, const double & y, const double & t = 1e-9);

protected:
  std::string mArchiveFileName;
  std::set<unsigned int> mIgnoredSEDMLMessages;
  std::map<std::string, CMetab*> speciesMap;
  CFunctionDB* functionDB;
  bool mIncompleteModel;
  unsigned int mLevel;
  unsigned int mOriginalLevel;
  unsigned int mVersion;
  std::map<CFunction*, std::string> sedmlIdMap;
  std::set<std::string> mUsedFunctions;
  CCopasiDataModel * mpDataModel;
  CModel* mpCopasiModel;
  std::map<std::string, std::string> mFunctionNameMapping;
  std::set<std::string> mDivisionByCompartmentReactions;
  CProcessReport* mpImportHandler;
  unsigned C_INT32 mImportStep;
  size_t mhImportStep;
  unsigned C_INT32 mTotalSteps;
  std::set<std::string> mExplicitelyTimeDependentFunctionDefinitions;
  std::map<const ASTNode*, CChemEqElement* > mStoichiometricExpressionMap;
  bool mDelayFound;
  std::set<const Parameter*> mPotentialAvogadroNumbers;
  bool mAvogadroCreated;

  std::set<std::string> mUsedSEDMLIds;
  bool mUsedSEDMLIdsPopulated;
  std::map<std::string, std::string> mKnownCustomUserDefinedFunctions;
  std::map<std::string, std::string> mKnownInitalValues;
public:
	SEDMLImporter();
	~SEDMLImporter();


	const std::string getArchiveFileName();

	void readListOfPlotsFromSedMLOutput(
			COutputDefinitionVector *pPlotList, CModel* pModel,
			SedDocument *pSedDocument,
			std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap);

	std::string getDataGeneratorModelItemRefrenceId(SedDocument *pSEDMLDocument, std::string dataReference, std::string SBMLType);
	std::string translateTargetXpathInSBMLId(const std::string &xpath, std::string &SBMLType);

	/**
	 *  This is a hack at the moment better solution for processing XPath string may be developed in the future
	 */
	std::string splitXpath(const std::string &xpath, std::string & SBMLType, char delim, bool isTypeRequred = false);

	/**
	 * Creates and returns a COPASI CTrajectoryTask from the SEDML simulation
	 * given as argument.
	 */
	CTrajectoryTask* createCTrajectoryTaskFromSimulation(SedSimulation* sedmlsim,
			std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap);

	CModel* readSEDML(std::string filename, CProcessReport* pImportHandler, CFunctionDB* funDB,
			SBMLDocument *& pSBMLDocument, SedDocument*& pSedDocument,
			std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap,
			std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
			CListOfLayouts *& prLol,
			CTrajectoryTask *& trajTask,
			COutputDefinitionVector * & plotList,
			CCopasiDataModel* pDataModel);

	CModel* parseSEDML(const std::string& sedmlDocumentText, CProcessReport* pImportHandler, CFunctionDB* funDB,
			SBMLDocument *& pSBMLDocument, SedDocument *& pSEDMLDocument,
			std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap,
			std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
			CListOfLayouts *& prLol,
			CTrajectoryTask *& trajTask,
			COutputDefinitionVector *& plotList,
			CCopasiDataModel* pDataModel);

	/**
	 * This call deletes an existing COPASI model.
	 * The method can e.g. be called to clean up if an import fails.
	 */
	void deleteCopasiModel();

	void setImportHandler(CProcessReport* pHandler);

	CProcessReport* getImportHandlerAddr();

	void restoreFunctionDB();


};



#endif /* SEDMLIMPORTER_H_ */
