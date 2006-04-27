/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLReference.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:31:21 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_SBMLReference
#define COPASI_SBMLReference

#include <string>
#include <map>

class SBMLReference
  {
  public:
    typedef std::map<std::string, std::string>::const_iterator const_iterator;

    // Operations
    /**
     * Default constructor
     */
    SBMLReference();

    /**
     * copy constructor
     */
    SBMLReference(const SBMLReference & src);

    /**
     * Default constructor
     */
    ~SBMLReference();

    /**
     * Set URL of the refernced SBML file.
     * @param const std::string & id
     * @return bool success
     */
    bool setURL(const std::string & url);

    /**
     * Retrieve the URL of the referenced SBML file
     * @return const std::string & url
     */
    const std::string & getURL() const;

    /**
     * Retrieve the SBML Id which is mapped to the given COPASI key.
     * @param const std::string & key
     * @return const std::string & id ("" if no map is found)
     */
    const std::string & getSBMLid(const std::string & key) const;

    /**
     * Retrieve the COPASI key which is mapped to the given SBML Id.
     * @param const std::string & id
     * @return const std::string & key ("" if no map is found)
     */
    const std::string & getCOPASIkey(const std::string & id) const;

    /**
     * Add an associated SBMLid, COPASIkey pair to the references.
     * @param const std::string & id
     * @param const std::string & key
     * @return bool success
     */
    bool add(const std::string & id, const std::string & key);

    /**
     * Remove the reference of the given id
     * @param const std::string & id
     * @return bool success
     */
    bool removeSBMLid(const std::string & id);

    /**
     * Remove the reference of the given key
     * @param const std::string & key
     * @return bool success
     */
    bool removeCOPASIkey(const std::string & key);

    /**
     *
     */
    const_iterator beginCOPASIkey() const;

    /**
     *
     */
    const_iterator endCOPASIkey() const;

    /**
     *
     */
    const_iterator beginSBMLid() const;

    /**
     *
     */
    const_iterator endSBMLid() const;

  private:
    // Attributes

    /**
     *
     */
    std::string mURL;

    /**
     *
     */
    std::map<std::string, std::string> mIdToKey;

    /**
     *
     */
    std::map<std::string, std::string> mKeyToId;

    static std::string NotFound;
  };

#endif // COPASI_SBMLReference
