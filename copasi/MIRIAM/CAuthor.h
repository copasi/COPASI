// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CAuthor.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/08 22:26:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CAuthors: Stores author name, email and other (vCard) details.
 *
 *
 */

#ifndef COPASI_CAUTHOR
#define COPASI_CAUTHOR

#include <string>

#include "report/CCopasiContainer.h"

class CAuthor : public CCopasiContainer
  {
    // Attributes
  private:

    std::string mKey;
    /**
    * The Family Name of the author - (only Required field,
    * everything else is optional).
    */
    std::string mFamilyName;
    /** The first name.
    */
    std::string mGivenName;

    /**
        * The email address of the author.
        */
    std::string mEmail;

    /**
        * The email address of the author.
        */
    std::string mURL;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & familyName
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CAuthor(const std::string & familyName,
            const CCopasiContainer * pParent = NULL,
            const std::string & givenName = "NoGivenName");

    /**
     * Copy constructor
     * @param "const CAuthor &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CAuthor(const CAuthor & src,
            const CCopasiContainer * pParent = NULL);

    ~CAuthor();
    void initObjects();

    /** Add the given name to Last name to get the full Name.
         *
         */
    std::string getFullName() const;

    const std::string & getFamilyName() const;

    const std::string & getGivenName() const;

    const std::string & getEmail() const;

    const std::string & getURL() const;

    void setFamilyName(const std::string familyName);

    void setGivenName(const std::string givenName);

    void setEmail(const std::string Email);

    void setURL(const std::string URL);

    /**
        *  Returns a string with the name of this Author.
        *  @return std::string key
        */
    virtual const std::string & getKey() const;
  };

#endif //COPASI_CAUTHOR
