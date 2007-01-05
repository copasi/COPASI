/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/CRegistration.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/15 21:25:34 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRegistration
#define COPASI_CRegistration

#include <time.h>

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
     * Set the registered email
     * @param const std::string & registeredEmail
     */
    void setRegisteredEmail(const std::string & registeredEmail);

    /**
     * Retrieve the registered email
     * @return const std::string & registeredEmail
     */
    const std::string & getRegisteredEmail() const;

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
     * @return bool isValidRegistration
     */
    bool isValidRegistration() const;

    /**
     * Check whether the signature is valid;
     * @return bool isValidSignature
     */
    bool isValidSignature() const;

    /**
     * Retrieve the expiration date.
     * @return std::string ExpirationDate
     */
    std::string getExpirationDate() const;

  private:
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();

    // Attributes
  private:
    /**
     * Registered Email
     */
    std::string *mpRegisteredEmail;

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

    /**
     * The expiration date
     */
    mutable time_t mExpirationDate;
  };

#endif // COPASI_CRegistration
