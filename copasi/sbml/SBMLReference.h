// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
