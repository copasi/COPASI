// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiRootContainer.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/12 15:54:45 $
// End CVS Header

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
 * are declard private. This ensures that there can be only one root container
 * which is initialized by the init method.
 * If this is necessary or not needs to be discussed.
 */
class CCopasiRootContainer : public CCopasiContainer
  {
  private:
    /**
     * The default contructor should be private so that nobody can create
     * new instances of the root container.
     * The only way to create a root container is through the static init
     * method.
     * Maybe this restriction is not necessary. We have to discuss this
     * later.
     */
    CCopasiRootContainer();

    /**
     * The copy constructor is private as well to make sure that there is only
     * one root container that can be initialized through the init call.
     */
    // Can't implement this yet since some of the copy constructors
    // further down the line don't work.
    //CCopasiRootContainer(const CCopasiRootContainer & src);

    /**
     * The assignment operator is private as well to make sure that there is only
     * one root container that can be initialized through the init call.
     */
    // Can't implement this yet since some of the copy constructors
    // further down the line don't work.
    //CCopasiRootContainer& operator=(const CCopasiRootContainer& src);

    /**
     * This Method creates a new root container.
     * Currently it is only used in the init call and it is made private so
     * that we can be sure that there is only one root container.
     */
    static CCopasiRootContainer* createNewRoot();

  protected:
    CKeyFactory mKeyFactory;
    CFunctionDB* mpFunctionList;
    CConfigurationFile* mpConfiguration;
    CCopasiVector<CCopasiDataModel>* mpDataModelList;
    // flag to store if we are running a GUI or not
    bool mWithGUI;

  public:
    /**
     * The pointer to the root container that holds all models.
     */
    static CCopasiRootContainer * Root;

    // Destructor
    virtual ~CCopasiRootContainer();

    /**
     * This method creates the only root container.
     */
    static void init();

    /**
     * Returns the a pointer to the configuration.
     */
    CConfigurationFile * getConfiguration();

    /**
     * Returns the a pointer to the configuration.
     */
    const CConfigurationFile * getConfiguration() const;

    /**
     * Returns a pointer to the global function database.
     */
    CFunctionDB * getFunctionList();

    /**
     * Returns a pointer to the global function database.
     */
    const CFunctionDB * getFunctionList() const;

    /**
     * Returns a pointer to the list of data models.
     */
    CCopasiVector< CCopasiDataModel > * getDatamodelList();

    /**
     * Returns a const pointer to the list of data models.
     */
    const CCopasiVector< CCopasiDataModel > * getDatamodelList() const;

    /**
     * Creates a new datamodel instance and adds it to the list.
     * The new instance is returned by the method.
     */
    CCopasiDataModel * addDatamodel();
  };

#define RootContainer (*CCopasiContainer::Root)

#endif /* COPASI_CCopasiRootContainer */
