// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRootContainer
#define COPASI_CRootContainer

#include "copasi/core/CDataContainer.h"
#include "copasi/report/CKeyFactory.h"

class CMIRIAMResource;
class CFunction;
class CFunctionDB;
class CConfigurationFile;
class CDataModel;
class CUnitDefinitionDB;
class CUnitDefinition;
template < class CType > class CDataVector;

/**
 * This is the new root container class.
 * It will hold some attributes that are used by all datamodels,
 * e.g.the global function database and the configuration,
 * and it will hold a list of datamodels.
 * Currently all methods to create new instances of CRootContainer
 * are declared private. This ensures that there can be only one root container
 * which is initialized by the init method.
 * If this is necessary or not needs to be discussed.
 */
class CRootContainer : public CDataContainer
{
private:
  /**
   * The default constructor should be private so that nobody can create
   * new instances of the root container.
   * The only way to create a root container is through the static init
   * method.
   * Maybe this restriction is not necessary. We have to discuss this
   * later.
   */
  CRootContainer(const bool & withGUI = false);

  /**
   * The copy constructor is private as well to make sure that there is only
   * one root container that can be initialized through the init call.
   * @param const CRootContainer & src
   */
  CRootContainer(const CRootContainer & src);

  /**
   * The assignment operator is private as well to make sure that there is only
   * one root container that can be initialized through the init call.
   * @param const CRootContainer & src
   * @return CRootContainer &
   */
  CRootContainer& operator=(const CRootContainer& src);

  /**
   * This method needs to be called after a new root container is
   * constructed.
   * Since many of the children of the root container need to access the key
   * factory through the global Root instance, the global root instance need to be created before the children can be initialized.
   * Calling this Method initializes the children. This method must be
   * protected since it can only be called once by the global init method.
   */
  void initializeChildren();

protected:
  CKeyFactory mKeyFactory;
  CMIRIAMResource *mpUnknownResource;
  CFunctionDB* mpFunctionList;
  CConfigurationFile* mpConfiguration;
  CDataVector< CDataModel > * mpDataModelList;
  CUnitDefinitionDB * mpUnitDefinitionList;
  // flag to store if we are running a GUI or not
  bool mWithGUI;

  CFunction * mpUndefined;

public:
  // Destructor
  virtual ~CRootContainer();

  /**
   * This method creates the only root container.
   */
  static void init(int argc, char *argv[], const bool & withGui = false);

  static void destroy();

  /**
   * Retrieve the root container
   */
  static const CDataContainer * getRoot();

  /**
   * Returns the a pointer to the configuration.
   */
  static CConfigurationFile * getConfiguration();

  /**
   * Returns a pointer to the global function database.
   */
  static CFunctionDB * getFunctionList();

  /**
   * Returns a pointer to the list of data models.
   */
  static CDataVector< CDataModel > * getDatamodelList();

  /**
   * Returns a pointer to the list of units.
   */
  static CUnitDefinitionDB *getUnitList();

  /**
   * Retrieve the unit for the given symbol
   */
  static const CUnitDefinition * getUnitDefFromSymbol(const std::string symbol);

  /**
   * Quote the given symbol if needed
   * @param const std::string & symbol
   * @return std::string quotedSymbol
   */
  static std::string quoteUnitDefSymbol(const std::string & symbol);

  /**
   * Replace all old symbols with new symbols in the unit definition DB
   * and in all models
   * @param const std::string & oldSymbol
   * @param const std::string & newSymbol
   */
  static void replaceSymbol(const std::string & oldSymbol,
                            const std::string & newSymbol);

  /**
   * Creates a new datamodel instance and adds it to the list.
   * The new instance is returned by the method.
   */
  static CDataModel * addDatamodel();

  /**
   * Retrieve the pointer for the function used for importing
   * kinetics without a kinetic law
   * @return CFunction * pUnsupportedDelay
   */
  static CFunction * getUndefinedFunction();

  static void functionDefinitionChanged(const CFunction * pFunction);

  /**
   * Returns a pointer to the KeyFactory.
   */
  static CKeyFactory* getKeyFactory();

  static const CMIRIAMResource & getUnknownMiriamResource();

  static bool removeDatamodel(const CDataModel * pDatamodel);

  static bool removeDatamodel(const unsigned C_INT32 index);

  static const char * getLicenseTxt();

  static const char * getLicenseHTML();
};

#endif /* COPASI_CRootContainer */
