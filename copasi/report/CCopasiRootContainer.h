// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiRootContainer.h,v $
//   $Revision: 1.7.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/10/20 15:14:25 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CCopasiRootContainer
#define COPASI_CCopasiRootContainer

#include "copasi/report/CCopasiContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/utilities/CCopasiVector.h"

class CFunctionDB;
class CConfigurationFile;

/**
 * This is the new root container class.
 * It will hold some attributes that are used by all datamodels,
 * e.g.the global function database and the configuration,
 * and it will hold a list of datamodels.
 * Currently all methods to create new instances of CCopasiRootContainer
 * are declared private. This ensures that there can be only one root container
 * which is initialized by the init method.
 * If this is necessary or not needs to be discussed.
 */
class CCopasiRootContainer : public CCopasiContainer
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
  CCopasiRootContainer(const bool & withGUI = false);

  /**
   * The copy constructor is private as well to make sure that there is only
   * one root container that can be initialized through the init call.
   * @param const CCopasiRootContainer & src
   */
  CCopasiRootContainer(const CCopasiRootContainer & src);

  /**
   * The assignment operator is private as well to make sure that there is only
   * one root container that can be initialized through the init call.
   * @param const CCopasiRootContainer & src
   * @return CCopasiRootContainer &
   */
  CCopasiRootContainer& operator=(const CCopasiRootContainer& src);

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
  CFunctionDB* mpFunctionList;
  CConfigurationFile* mpConfiguration;
  CCopasiVector<CCopasiDataModel>* mpDataModelList;
  // flag to store if we are running a GUI or not
  bool mWithGUI;

  CFunction * mpUndefined;

public:
  // Destructor
  virtual ~CCopasiRootContainer();

  /**
   * This method creates the only root container.
   */
  static void init(int argc, char *argv[], const bool & withGui = false);

  static void destroy();

  /**
   * Retrieve the root container
   */
  static const CCopasiContainer * getRoot();

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
  static CCopasiVector< CCopasiDataModel > * getDatamodelList();

  /**
   * Creates a new datamodel instance and adds it to the list.
   * The new instance is returned by the method.
   */
  static CCopasiDataModel * addDatamodel();

  /**
   * Retrieve the pointer for the function used for importing
   * kinetics without a kinetic law
   * @return CFunction * pUnsupportedDelay
   */
  static CFunction * getUndefinedFunction();

  /**
   * Returns a pointer to the KeyFactory.
   */
  static CKeyFactory* getKeyFactory();

  static bool removeDatamodel(const CCopasiDataModel * pDatamodel);

  static bool removeDatamodel(const unsigned C_INT32 index);

  static const char * getLicenseTxt();

  static const char * getLicenseHTML();
};

#endif /* COPASI_CCopasiRootContainer */
