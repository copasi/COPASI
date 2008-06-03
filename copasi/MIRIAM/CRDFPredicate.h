// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFPredicate.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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
      bqbiol_hasVersion,
      bqbiol_is,
      bqbiol_isDescribedBy,
      bqbiol_isEncodedBy,
      bqbiol_isHomologTo,
      bqbiol_isPartOf,
      bqbiol_isVersionOf,
      bqbiol_occursIn,
      bqmodel_is,
      bqmodel_isDescribedBy,
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
        unsigned C_INT32 MaxOccurance;
        bool ReadOnly;
        CRDFObject::eObjectType Type;
        Path Location;
      };

    typedef std::vector< sAllowedLocation > AllowedLocationList;

  private:
    static const std::string PredicateURI[];

    static std::map< std::string, ePredicateType > URI2Predicate;

    static const std::string PredicateDisplayName[];

    static std::map< std::string, ePredicateType > DisplayName2Predicate;

    static std::vector< AllowedLocationList > Predicate2AllowedLocationsRelative;

    static std::vector< AllowedLocationList > Predicate2AllowedLocationsAbsolute;

    static CRDFPredicate Factory;

    CRDFPredicate();

    ~CRDFPredicate();

    void createURI2Predicate();

    void createDisplayName2Predicate();

    void createAllowedLocationsRelative();

    void createAllowedLocationsAbsolute();

    void createAllowedLocationsAbsolute(const ePredicateType & predicate);

  public:
    static const AllowedLocationList & getAllowedLocationList(const ePredicateType & predicate);

    static const std::string & getURI(const ePredicateType & predicate);

    static ePredicateType getPredicateFromURI(const std::string & URI);

    static const std::string & getDisplayName(const ePredicateType & predicate);

    static ePredicateType getPredicateFromDisplayName(const std::string & URI);

    static unsigned C_INT32 getSubPathIndex(const Path & fullPath, const Path & currentPath);

    static bool isReadOnly(const Path & currentPath);
  };

std::ostream & operator << (std::ostream & os, const CRDFPredicate::Path & path);
std::ostream & operator << (std::ostream & os, const CRDFPredicate::sAllowedLocation & location);

#endif // COPASI_CRDFPredicate
