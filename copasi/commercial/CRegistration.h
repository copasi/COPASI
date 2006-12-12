/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/CRegistration.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/12 21:22:08 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRegistration
#define COPASI_CRegistration

#include "utilities/CCopasiParameterGroup.h"

class CRegistration : public CCopasiParameterGroup
  {
    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: Registration)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CRegistration(const std::string & name = "Registration",
                  const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CRegistration & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CRegistration(const CRegistration & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CRegistration(const CCopasiParameterGroup & group,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CRegistration();

    /**
     * Set the registered user
     * @param const std::string & registeredUser
     */
    void setRegisteredUser(const std::string & registeredUser);

    /**
     * Retrieve the registered user
     * @return const std::string & registeredUser
     */
    const std::string & getRegisteredUser() const;

    /**
     * Set the registration code
     * @param const std::string & registrationCode
     */
    void setRegistrationCode(const std::string & registrationCode);

    /**
     * Retrieve the registration code
     * @return const std::string & registrationCode
     */
    const std::string & getRegistrationCode() const;

    /**
     * Check whether the registration is valid;
     * @return bool isValid
     */
    bool isValid() const;

  private:
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();

    // Attributes
  private:
    /**
     * Registered User
     */
    std::string *mpRegisteredUser;

    /**
     * Registration Code
     */
    std::string *mpRegistrationCode;

    /**
     * The Signature
     */
    std::string *mpSignature;
  };

#endif // COPASI_CRegistration
