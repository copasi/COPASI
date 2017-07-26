// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CRDFPredicate
#define COPASI_CRDFPredicate

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "copasi/MIRIAM/CRDFObject.h"

class CRDFPredicate
{
public:
  enum ePredicateType
  {
    /* These are proposed to unify:
     * http://biomodels.net/biology-qualifiers/...
     * http://biomodels.net/model-qualifiers/...
     */
    copasi_encodes = 0,
    copasi_hasPart,
    copasi_hasVersion,
    copasi_is,
    copasi_isDescribedBy,
    copasi_isEncodedBy,
    copasi_isHomologTo,
    copasi_isPartOf,
    copasi_isVersionOf,
    copasi_occursIn,
    // copasi_modification,
    bqbiol_encodes,
    bqbiol_hasPart,
    bqbiol_hasProperty,
    bqbiol_hasVersion,
    bqbiol_is,
    bqbiol_isDescribedBy,
    bqbiol_isEncodedBy,
    bqbiol_isHomologTo,
    bqbiol_isPartOf,
    bqbiol_isPropertyOf,
    bqbiol_isVersionOf,
    bqbiol_occursIn,
    bqbiol_hasTaxon,
    bqmodel_is,
    bqmodel_isDerivedFrom,
    bqmodel_isDescribedBy,
    bqmodel_isInstanceOf,
    bqmodel_hasInstance,
    dc_creator,
    dcterms_creator,
    dcterms_bibliographicCitation,
    // dcterms_contributor,
    dcterms_created,
    dcterms_description,
    // dcterms_license,
    dcterms_modified,
    // dcterms_rights,
    // dcterms_rightsHolder,
    dcterms_W3CDTF,
    vcard_EMAIL,
    vcard_Family,
    vcard_Given,
    vcard_N,
    vcard_ORG,
    vcard_Orgname,
    rdf_type,
    rdf_li,
    rdf__n,
    rdf_subject,
    rdf_predicate,
    rdf_object,
    unknown,
    // For internal use
    about,
    any,
    end
  };

  typedef std::vector< ePredicateType > Path;

  struct sAllowedLocation
  {
  public:
    size_t MaxOccurance;
    bool ReadOnly;
    CRDFObject::eObjectType Type;
    Path Location;
  };

  typedef std::vector< sAllowedLocation > AllowedLocationList;

public:
  // Methods
  /**
   * Default constructor
   * @param const ePredicateType & type (default CRDFPredicate::end)
   */
  CRDFPredicate(const ePredicateType & type = end);

  /**
   * Specific constructor
   * @param const std::string & uri
   */
  CRDFPredicate(const std::string & uri);

  /**
   * Copy constructor
   * @param const CRDFPredicate & src
   */
  CRDFPredicate(const CRDFPredicate & src);

  /**
   * Destructor
   */
  ~CRDFPredicate();

  /**
   * Assignment operator.
   * @param const ePredicateType & type
   * @return CRDFPredicate predicate
   */
  CRDFPredicate operator = (const ePredicateType & type);

  /**
   * Retrieve the URI.
   * @return const std::string & URI
   */
  const std::string & getURI() const;

  /**
   * Set the URI.
   * @param const std::string & URI
   */
  void setURI(const std::string & uri);

  /**
   * Comparison operator for equality.
   * @param const CRDFPredicate & rhs
   * @return bool isEqual
   */
  bool operator == (const CRDFPredicate & rhs) const;

  /**
   * Comparison operator for inequality.
   * @param const CRDFPredicate & rhs
   * @return bool isNotEqual
   */
  bool operator != (const CRDFPredicate & rhs) const;

  /**
   * Comparison operator for less.
   * @param const CRDFPredicate & rhs
   * @return bool isLess
   */
  bool operator < (const CRDFPredicate & rhs) const;

  /**
   * Retrieve the type og the predicate.
   * @return const ePredicateType & type
   */
  const ePredicateType & getType() const;

  /**
   * Retrieve the list of allowed locations in the RDF graph for the given predicate
   * @param const ePredicateType & predicate
   * @return const AllowedLocationList & listOfAllowedLocations
   */
  static const AllowedLocationList & getAllowedLocationList(const ePredicateType & predicate);

  /**
   * Retrieve the URI for the given predicate
   * @param const CRDFPredicate & predicate
   * @return const std::string & uri
   */
  static const std::string & getURI(const CRDFPredicate & predicate);

  /**
   * Retrieve the type of predicate for the given URI
   * @param const std::string & URI
   * @return ePredicateType type
   */
  static ePredicateType getPredicateFromURI(const std::string & URI);

  /**
   * Retrieve the display name for the given predicate
   * @param const CRDFPredicate & predicate
   * @return const std::string & displayName
   */
  static const std::string & getDisplayName(const CRDFPredicate & predicate);

  /**
   * Retrieve the type of predicate from the given display name
   * @param const std::string & displayName
   * @return ePredicateType type
   */
  static ePredicateType getPredicateFromDisplayName(const std::string & displayName);

  /**
   * Retrieve the index of the next path element of the full path beyond the current path.
   * If the current path is not part of the full path C_INVALID_INDEX is returned
   * @param const Path & fullPath
   * @param const Path & currentPath
   * @return size_t index
   */
  static size_t getSubPathIndex(const Path & fullPath, const Path & currentPath);

  /**
   * Checks whether the element pointed to by the current path is read-only
   * @param const Path & currentPath
   * @return bool isReadOnly
   */
  static bool isReadOnly(const Path & currentPath);

  /**
   * Friend declaration of ostream operator
   * @param std::ostream & os
   * @param const CRDFPredicate & p
   * @return std::ostream & os
   */
  friend std::ostream & operator << (std::ostream & os, const CRDFPredicate & p);

private:
  // Methods
  /**
   * Initialize the static information
   */
  static void initialize();

  /**
   * Initialize the map from URI to predicate
   */
  static void createURI2Predicate();

  /**
   * Initialize the map from display name to predicate
   */
  static void createDisplayName2Predicate();

  /**
   * Create the list of relative allowed locations for each predicate
   */
  static void createAllowedLocationsRelative();

  /**
   * Create the list of absolute allowed locations for each predicate
   */
  static void createAllowedLocationsAbsolute();

  /**
   * Create the list of absolute allowed locations for the given predicate
   * @param const ePredicateType & predicate
   */
  static void createAllowedLocationsAbsolute(const ePredicateType & predicate);

  // Attributes
  /**
   * The type of the predicate
   */
  ePredicateType mType;

  /**
   * The URI
   */
  std::string mURI;

  /**
   * Static strings for URIs
   */
  static const std::string PredicateURI[];

  /**
   * Map from URI to predicate type
   */
  static std::map< std::string, ePredicateType > URI2Predicate;

  /**
   * Static strings for display names
   */
  static const std::string PredicateDisplayName[];

  /**
   * Map from display name to predicate type
   */
  static std::map< std::string, ePredicateType > DisplayName2Predicate;

  /**
   * Vector of relative allowed locations
   */
  static std::vector< AllowedLocationList > Predicate2AllowedLocationsRelative;

  /**
   * Vector of absolute allowed locations
   */
  static std::vector< AllowedLocationList > Predicate2AllowedLocationsAbsolute;
};

std::ostream & operator << (std::ostream & os, const CRDFPredicate::Path & path);
std::ostream & operator << (std::ostream & os, const CRDFPredicate::sAllowedLocation & location);

#endif // COPASI_CRDFPredicate
