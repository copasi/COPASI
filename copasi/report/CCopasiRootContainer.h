// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiRootContainer.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:54:48 $
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
    CCopasiRootContainer(bool withGUI = false);

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
    static CCopasiRootContainer* createNewRoot(bool withGUI = false);

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

    /**
     * Pointer to a function created for supporting the load SBML models
     * using the delay symbol
     */
    CFunction * mpUnsupportedDelay;

    CFunction * mpUndefined;

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
    static void init(bool withGUI, int argc, char** argv);

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

    /**
     * Retrieve the pointer for the function used for importing the
     * unsupported SBML symbol delay
     * @return CFunction * pUnsupportedDelay
     */
    CFunction * getUnsupportedDelay();

    /**
     * Retrieve the const pointer for the function used for importing the
     * unsupported SBML symbol delay
     * @return CFunction * pUnsupportedDelay
     */
    const CFunction * getUnsupportedDelay() const;

    /**
     * Retrieve the pointer for the function used for importing
     * kinetics without a kinetic law
     * @return CFunction * pUnsupportedDelay
     */
    CFunction * getUndefinedFunction();

    /**
     * Retrieve the const pointer for the function used for importing
     * inetics without a kinetic law
     * @return CFunction * pUnsupportedDelay
     */
    const CFunction * getUndefinedFunction() const;

    /**
     * Returns a pointer to the KeyFactory.
     */
    CKeyFactory* getKeyFactory();

    /**
     * Returns a const pointer to the KeyFactory.
     */
    const CKeyFactory* getKeyFactory() const;
  };

#endif /* COPASI_CCopasiRootContainer */
