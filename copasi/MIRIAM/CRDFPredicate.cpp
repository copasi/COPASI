// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CRDFPredicate.h"

// static
const std::string CRDFPredicate::PredicateURI[] =
{
  /* These are proposed to replace:
   * http://biomodels.net/biology-qualifiers/...
   * http://biomodels.net/model-qualifiers/...
   */
  "http://www.copasi.org/RDF/MiriamTerms#encodes", // copasi_encodes
  "http://www.copasi.org/RDF/MiriamTerms#hasPart", // copasi_hasPart
  "http://www.copasi.org/RDF/MiriamTerms#hasVersion", // copasi_hasVersion
  "http://www.copasi.org/RDF/MiriamTerms#is", // copasi_is
  "http://www.copasi.org/RDF/MiriamTerms#isDescribedBy", // copasi_isDescribedBy
  "http://www.copasi.org/RDF/MiriamTerms#isEncodedBy", // copasi_isEncodedBy
  "http://www.copasi.org/RDF/MiriamTerms#isHomologTo", // copasi_isHomologTo
  "http://www.copasi.org/RDF/MiriamTerms#isPartOf", // copasi_isPartOf
  "http://www.copasi.org/RDF/MiriamTerms#isVersionOf", // copasi_isVersionOf
  "http://www.copasi.org/RDF/MiriamTerms#occursIn", // copasi_occursIn
  // "http://www.copasi.org/RDF/MiriamTerms#modification", // copasi_modification
  "http://biomodels.net/biology-qualifiers/encodes", // bqbiol_encodes
  "http://biomodels.net/biology-qualifiers/hasPart", // bqbiol_hasPart
  "http://biomodels.net/biology-qualifiers/hasProperty", // bqbiol_hasProperty
  "http://biomodels.net/biology-qualifiers/hasVersion", // bqbiol_hasVersion
  "http://biomodels.net/biology-qualifiers/is", // bqbiol_is
  "http://biomodels.net/biology-qualifiers/isDescribedBy", // bqbiol_isDescribedBy
  "http://biomodels.net/biology-qualifiers/isEncodedBy", // bqbiol_isEncodedBy
  "http://biomodels.net/biology-qualifiers/isHomologTo", // bqbiol_isHomologTo
  "http://biomodels.net/biology-qualifiers/isPartOf", // bqbiol_isPartOf
  "http://biomodels.net/biology-qualifiers/isPropertyOf", // bqbiol_isPropertyOf
  "http://biomodels.net/biology-qualifiers/isVersionOf", // bqbiol_isVersionOf
  "http://biomodels.net/biology-qualifiers/occursIn", // copasi_occursIn
  "http://biomodels.net/biology-qualifiers/hasTaxon", // copasi_hasTaxon
  "http://biomodels.net/model-qualifiers/is", // bqmodel_is
  "http://biomodels.net/model-qualifiers/isDerivedFrom", // bqmodel_isDerivedFrom
  "http://biomodels.net/model-qualifiers/isDescribedBy", // bqmodel_isDescribedBy
  "http://biomodels.net/model-qualifiers/isInstanceOf", // bqmodel_isInstanceOf
  "http://biomodels.net/model-qualifiers/isDescribedBy", // bqmodel_hasInstance
  "http://purl.org/dc/elements/1.1/creator", // dc_creator
  "http://purl.org/dc/terms/creator", // dcterms_creator
  "http://purl.org/dc/terms/bibliographicCitation", // dcterms_bibliographicCitation
  // "http://purl.org/dc/terms/contributor", // dcterms_contributor
  "http://purl.org/dc/terms/created", // dcterms_created
  "http://purl.org/dc/terms/description", // dcterms_description,
  // "http://purl.org/dc/terms/license", // dcterms_license
  "http://purl.org/dc/terms/modified", // dcterms_modified
  // "http://purl.org/dc/terms/rights", // dcterms_rights
  // "http://purl.org/dc/terms/rightsHolder", // dcterms_rightsHolder
  "http://purl.org/dc/terms/W3CDTF", // dcterms_W3CDTF
  "http://www.w3.org/2001/vcard-rdf/3.0#EMAIL", // vcard_EMAIL
  "http://www.w3.org/2001/vcard-rdf/3.0#Family", // vcard_Family
  "http://www.w3.org/2001/vcard-rdf/3.0#Given", // vcard_Given
  "http://www.w3.org/2001/vcard-rdf/3.0#N", // vcard_N
  "http://www.w3.org/2001/vcard-rdf/3.0#ORG", // vcard_ORG
  "http://www.w3.org/2001/vcard-rdf/3.0#Orgname", // vcard_Orgname
  "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", // rdf_type,
  "http://www.w3.org/1999/02/22-rdf-syntax-ns#li", // rdf_li
  "http://www.w3.org/1999/02/22-rdf-syntax-ns#_", // rdf__n
  "http://www.w3.org/1999/02/22-rdf-syntax-ns#subject", //rdf_subject
  "http://www.w3.org/1999/02/22-rdf-syntax-ns#predicate", //rdf_predicate
  "http://www.w3.org/1999/02/22-rdf-syntax-ns#object", //rdf_object
  "http://www.copasi.org/RDF/MiriamTerms#unknown", // unknown
  // For internal use
  "about", // about
  "any", // any
  "end" // end
};

// static
std::map< std::string, CRDFPredicate::ePredicateType > CRDFPredicate::URI2Predicate;

// static
void CRDFPredicate::createURI2Predicate()
{
  int Predicate = 0;

  for (; PredicateURI[Predicate] != "end"; Predicate++)
    URI2Predicate[PredicateURI[Predicate]] = (ePredicateType) Predicate;

  URI2Predicate[PredicateURI[Predicate]] = (ePredicateType) Predicate;

  // Now we now the number of supported predicates.
  Predicate2AllowedLocationsRelative.resize(URI2Predicate.size());
  Predicate2AllowedLocationsAbsolute.resize(URI2Predicate.size());
}

// static
const std::string CRDFPredicate::PredicateDisplayName[] =
{
  /* These are proposed to replace:
   * http://biomodels.net/biology-qualifiers/...
   * http://biomodels.net/model-qualifiers/...
   */
  "encodes", // copasi_encodes
  "has part", // copasi_hasPart
  "has version", // copasi_hasVersion
  "is", // copasi_is
  "is described by", // copasi_isDescribedBy
  "is encoded by", // copasi_isEncodedBy
  "is homolog to", // copasi_isHomologTo
  "is part of", // copasi_isPartOf
  "is version of", // copasi_isVersionOf
  "occurs in", // copasi_occursIn
  // "modification", // copasi_modification
  "encodes", // bqbiol_encodes
  "has part", // bqbiol_hasPart
  "has property", // bqbiol_hasProperty
  "has version", // bqbiol_hasVersion
  "is", // bqbiol_is
  "is described by", // bqbiol_isDescribedBy
  "is encoded by", // bqbiol_isEncodedBy
  "is homolog to", // bqbiol_isHomologTo
  "is part of", // bqbiol_isPartOf
  "is property of", // bqbiol_isPropertyOf
  "is version of", // bqbiol_isVersionOf
  "occurs in", // bqbiol_occursIn
  "has taxon", // bqbiol_hasTaxon
  "is", // bqmodel_is
  "is derived from", // bqmodel_isDerivedFrom
  "is described by", // bqmodel_isDescribedBy
  "is instance of", // bqmodel_isInstanceOf
  "has instance", // bqmodel_hasInstance
  "creator", // dc_creator
  "creator", // dcterms_creator
  "bibliographic citation", // dcterms_bibliographicCitation
  // "contributor", // dcterms_contributor
  "created at", // dcterms_created
  "description", // dcterms_description
  // "license", // dcterms_license
  "modified at", // dcterms_modified
  // "rights", // dcterms_rights
  // "rights holder", // dcterms_rightsHolder
  "date", // dcterms_W3CDTF
  "EMAIL", // vcard_EMAIL
  "family name", // vcard_Family
  "given name", // vcard_Given
  "name", // vcard_N
  "organization", // vcard_ORG
  "name", // vcard_Orgname
  "type", // rdf_type,
  "*", // rdf_li
  "*", // rdf__n
  "subject", // rdf_subject,
  "predicate", // rdf_predicate,
  "object", // rdf_object
  "-- select --", // unknown
  // For internal use
  "about", // about
  "any", // any
  "end" // end
};

// static
std::map< std::string, CRDFPredicate::ePredicateType > CRDFPredicate::DisplayName2Predicate;

// static
void CRDFPredicate::createDisplayName2Predicate()
{
  int Predicate = 0;

  for (; PredicateDisplayName[Predicate] != "end"; Predicate++)
    DisplayName2Predicate.insert(std::map< std::string, ePredicateType >::value_type(PredicateDisplayName[Predicate], (ePredicateType) Predicate));

  DisplayName2Predicate.insert(std::map< std::string, ePredicateType >::value_type(PredicateDisplayName[Predicate], (ePredicateType) Predicate));
}

// static
std::vector< CRDFPredicate::AllowedLocationList > CRDFPredicate::Predicate2AllowedLocationsRelative;

// static
void CRDFPredicate::createAllowedLocationsRelative()
{
  AllowedLocationList AboutUnboundedResource;
  AboutUnboundedResource.resize(1);
  AboutUnboundedResource[0].MaxOccurance = C_INVALID_INDEX;
  AboutUnboundedResource[0].ReadOnly = false;
  AboutUnboundedResource[0].Type = CRDFObject::RESOURCE;
  AboutUnboundedResource[0].Location.resize(1);
  AboutUnboundedResource[0].Location[0] = about;

  AllowedLocationList AboutOneLiteral;
  AboutOneLiteral.resize(1);
  AboutOneLiteral[0].MaxOccurance = 1;
  AboutOneLiteral[0].ReadOnly = false;
  AboutOneLiteral[0].Type = CRDFObject::LITERAL;
  AboutOneLiteral[0].Location.resize(1);
  AboutOneLiteral[0].Location[0] = about;

  /* These are proposed to replace:
   * http://biomodels.net/biology-qualifiers/...
   * http://biomodels.net/model-qualifiers/...
   */
  // copasi_encodes:
  Predicate2AllowedLocationsRelative[copasi_encodes] = AboutUnboundedResource;

  // copasi_hasPart:
  Predicate2AllowedLocationsRelative[copasi_hasPart] = AboutUnboundedResource;

  // copasi_hasVersion:
  Predicate2AllowedLocationsRelative[copasi_hasVersion] = AboutUnboundedResource;

  // copasi_is:
  Predicate2AllowedLocationsRelative[copasi_is] = AboutUnboundedResource;

  // copasi_isDescribedBy:
  Predicate2AllowedLocationsRelative[copasi_isDescribedBy].resize(1);
  //  *.dcterms_bibliographicCitation, *
  Predicate2AllowedLocationsRelative[copasi_isDescribedBy][0].MaxOccurance = C_INVALID_INDEX;
  Predicate2AllowedLocationsRelative[copasi_isDescribedBy][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[copasi_isDescribedBy][0].Type = CRDFObject::RESOURCE;
  Predicate2AllowedLocationsRelative[copasi_isDescribedBy][0].Location.resize(2);
  Predicate2AllowedLocationsRelative[copasi_isDescribedBy][0].Location[0] = any;
  Predicate2AllowedLocationsRelative[copasi_isDescribedBy][0].Location[1] = dcterms_bibliographicCitation;

  // copasi_isEncodedBy:
  Predicate2AllowedLocationsRelative[copasi_isEncodedBy] = AboutUnboundedResource;

  // copasi_isHomologTo:
  Predicate2AllowedLocationsRelative[copasi_isHomologTo] = AboutUnboundedResource;

  // copasi_isPartOf:
  Predicate2AllowedLocationsRelative[copasi_isPartOf] = AboutUnboundedResource;

  // copasi_isVersionOf:
  Predicate2AllowedLocationsRelative[copasi_isVersionOf] = AboutUnboundedResource;

  // copasi_occursIn:
  Predicate2AllowedLocationsRelative[copasi_occursIn] = AboutUnboundedResource;

  /*
  copasi_modification:
    about, *
   */

  // bq* is read only
  AboutUnboundedResource[0].ReadOnly = true;

  // bqbiol_encodes:
  Predicate2AllowedLocationsRelative[bqbiol_encodes] = AboutUnboundedResource;

  // bqbiol_hasPart:
  Predicate2AllowedLocationsRelative[bqbiol_hasPart] = AboutUnboundedResource;

  // bqbiol_hasProperty:
  Predicate2AllowedLocationsRelative[bqbiol_hasProperty] = AboutUnboundedResource;

  // bqbiol_hasVersion:
  Predicate2AllowedLocationsRelative[bqbiol_hasVersion] = AboutUnboundedResource;

  // bqbiol_is:
  Predicate2AllowedLocationsRelative[bqbiol_is] = AboutUnboundedResource;

  // bqbiol_isDescribedBy:
  Predicate2AllowedLocationsRelative[bqbiol_isDescribedBy] = AboutUnboundedResource;

  // bqbiol_isEncodedBy:
  Predicate2AllowedLocationsRelative[bqbiol_isEncodedBy] = AboutUnboundedResource;

  // bqbiol_isHomologTo:
  Predicate2AllowedLocationsRelative[bqbiol_isHomologTo] = AboutUnboundedResource;

  // bqbiol_isPropertyOf:
  Predicate2AllowedLocationsRelative[bqbiol_isPropertyOf] = AboutUnboundedResource;

  // bqbiol_isPartOf:
  Predicate2AllowedLocationsRelative[bqbiol_isPartOf] = AboutUnboundedResource;

  // bqbiol_isVersionOf:
  Predicate2AllowedLocationsRelative[bqbiol_isVersionOf] = AboutUnboundedResource;

  // bqbiol_hasTaxon:
  Predicate2AllowedLocationsRelative[bqbiol_hasTaxon] = AboutUnboundedResource;

  // bqbiol_occursIn:
  Predicate2AllowedLocationsRelative[bqbiol_occursIn] = AboutUnboundedResource;

  // bqmodel_is:
  Predicate2AllowedLocationsRelative[bqmodel_is] = AboutUnboundedResource;

  // bqmodel_isDerivedFrom:
  Predicate2AllowedLocationsRelative[bqmodel_isDerivedFrom] = AboutUnboundedResource;

  // bqmodel_isDescribedBy:
  Predicate2AllowedLocationsRelative[bqmodel_isDescribedBy] = AboutUnboundedResource;

  // bqmodel_isInstanceOf:
  Predicate2AllowedLocationsRelative[bqmodel_isInstanceOf] = AboutUnboundedResource;

  // bqmodel_hasInstance:
  Predicate2AllowedLocationsRelative[bqmodel_hasInstance] = AboutUnboundedResource;

  // dc_creator:
  Predicate2AllowedLocationsRelative[dc_creator] = AboutUnboundedResource;
  Predicate2AllowedLocationsRelative[dc_creator][0].Type = CRDFObject::BLANK_NODE;

  // change back to writable
  AboutUnboundedResource[0].ReadOnly = false;

  // dcterms_creator:
  Predicate2AllowedLocationsRelative[dcterms_creator] = AboutUnboundedResource;
  Predicate2AllowedLocationsRelative[dcterms_creator][0].Type = CRDFObject::BLANK_NODE;

  // dcterms_bibliographicCitation:
  Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation].resize(1);
  // about, *
  Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][0].MaxOccurance = C_INVALID_INDEX;
  Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][0].Type = CRDFObject::BLANK_NODE;
  Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][0].Location.resize(1);
  Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][0].Location[0] = about;
  // *.copasi_modification, *
  // Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][1].MaxOccurance = C_INVALID_INDEX;
  // Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][1].ReadOnly = false;
  // Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][1].Type = CRDFObject::BLANK_NODE;
  // Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][1].Location.resize(2);
  // Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][1].Location[0] = any;
  // Predicate2AllowedLocationsRelative[dcterms_bibliographicCitation][1].Location[1] = copasi_modification;

  // dcterms_contributor:
  // Predicate2AllowedLocationsRelative[dcterms_modified].resize(1);
  // *.copasi_modification, *
  // Predicate2AllowedLocationsRelative[dcterms_modified][0].MaxOccurance = C_INVALID_INDEX;
  // Predicate2AllowedLocationsRelative[dcterms_modified][0].ReadOnly = false;
  // Predicate2AllowedLocationsRelative[dcterms_modified][0].Type = CRDFObject::BLANK_NODE;
  // Predicate2AllowedLocationsRelative[dcterms_modified][0].Location.resize(2);
  // Predicate2AllowedLocationsRelative[dcterms_modified][0].Location[0] = any;
  // Predicate2AllowedLocationsRelative[dcterms_modified][0].Location[1] = copasi_modification;

  // dcterms_created:
  Predicate2AllowedLocationsRelative[dcterms_created].resize(1);
  // about, 1
  Predicate2AllowedLocationsRelative[dcterms_created][0].MaxOccurance = 1;
  Predicate2AllowedLocationsRelative[dcterms_created][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[dcterms_created][0].Type = CRDFObject::BLANK_NODE;
  Predicate2AllowedLocationsRelative[dcterms_created][0].Location.resize(1);
  Predicate2AllowedLocationsRelative[dcterms_created][0].Location[0] = about;

  // dcterms_description
  Predicate2AllowedLocationsRelative[dcterms_description].resize(1);
  // bibliographicCitation, 1
  Predicate2AllowedLocationsRelative[dcterms_description][0].MaxOccurance = 1;
  Predicate2AllowedLocationsRelative[dcterms_description][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[dcterms_description][0].Type = CRDFObject::LITERAL;
  Predicate2AllowedLocationsRelative[dcterms_description][0].Location.resize(2);
  Predicate2AllowedLocationsRelative[dcterms_description][0].Location[0] = any;
  Predicate2AllowedLocationsRelative[dcterms_description][0].Location[1] = dcterms_bibliographicCitation;

  // dcterms_license:
  // Predicate2AllowedLocationsRelative[dcterms_license] = AboutOneLiteral;

  // dcterms_modified:
  Predicate2AllowedLocationsRelative[dcterms_modified].resize(1);
  // about, *
  Predicate2AllowedLocationsRelative[dcterms_modified][0].MaxOccurance = C_INVALID_INDEX;
  Predicate2AllowedLocationsRelative[dcterms_modified][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[dcterms_modified][0].Type = CRDFObject::BLANK_NODE;
  Predicate2AllowedLocationsRelative[dcterms_modified][0].Location.resize(1);
  Predicate2AllowedLocationsRelative[dcterms_modified][0].Location[0] = about;

  // *.copasi_modification, *
  // Predicate2AllowedLocationsRelative[dcterms_modified][1].MaxOccurance = C_INVALID_INDEX;
  // Predicate2AllowedLocationsRelative[dcterms_modified][1].ReadOnly = false;
  // Predicate2AllowedLocationsRelative[dcterms_modified][1].Type = CRDFObject::BLANK_NODE;
  // Predicate2AllowedLocationsRelative[dcterms_modified][1].Location.resize(2);
  // Predicate2AllowedLocationsRelative[dcterms_modified][1].Location[0] = any;
  // Predicate2AllowedLocationsRelative[dcterms_modified][1].Location[1] = copasi_modification;

  // dcterms_rights:
  // Predicate2AllowedLocationsRelative[dcterms_rights] = AboutOneLiteral;

  // dcterms_rightsHolder:
  // Predicate2AllowedLocationsRelative[dcterms_rights] = AboutOneLiteral;

  // dcterms_W3CDTF:
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF].resize(2);
  // *.dcterms_created, 1
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][0].MaxOccurance = 1;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][0].Type = CRDFObject::LITERAL;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][0].Location.resize(2);
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][0].Location[0] = any;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][0].Location[1] = dcterms_created;
  // *.dcterms_modified, 1
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][1].MaxOccurance = 1;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][1].ReadOnly = false;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][1].Type = CRDFObject::LITERAL;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][1].Location.resize(2);
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][1].Location[0] = any;
  Predicate2AllowedLocationsRelative[dcterms_W3CDTF][1].Location[1] = dcterms_modified;

  AllowedLocationList VCardOneBlankNode;
  VCardOneBlankNode.resize(2);
  // *.dcterms_creator, 1
  VCardOneBlankNode[0].MaxOccurance = 1;
  VCardOneBlankNode[0].ReadOnly = false;
  VCardOneBlankNode[0].Type = CRDFObject::BLANK_NODE;
  VCardOneBlankNode[0].Location.resize(2);
  VCardOneBlankNode[0].Location[0] = any;
  VCardOneBlankNode[0].Location[1] = dcterms_creator;
  // *.dc_creator, 1
  VCardOneBlankNode[1].MaxOccurance = 1;
  VCardOneBlankNode[1].ReadOnly = true;
  VCardOneBlankNode[1].Type = CRDFObject::BLANK_NODE;
  VCardOneBlankNode[1].Location.resize(2);
  VCardOneBlankNode[1].Location[0] = any;
  VCardOneBlankNode[1].Location[1] = dc_creator;
  // *.dcterms_contributor, 1
  // VCardOneBlankNode[1].MaxOccurance = 1;
  // VCardOneBlankNode[1].ReadOnly = false;
  // VCardOneBlankNode[1].Type = CRDFObject::BLANK_NODE;
  // VCardOneBlankNode[1].Location.resize(2);
  // VCardOneBlankNode[1].Location[0] = any;
  // VCardOneBlankNode[1].Location[1] = dcterms_contributor;

  // vcard_EMAIL:
  Predicate2AllowedLocationsRelative[vcard_EMAIL] = VCardOneBlankNode;
  // Override the default for vcard which is literal = true;
  Predicate2AllowedLocationsRelative[vcard_EMAIL][0].Type = CRDFObject::LITERAL;
  Predicate2AllowedLocationsRelative[vcard_EMAIL][1].Type = CRDFObject::LITERAL;

  // vcard_Family:
  Predicate2AllowedLocationsRelative[vcard_Family].resize(1);
  // *.vcard_N, 1
  Predicate2AllowedLocationsRelative[vcard_Family][0].MaxOccurance = 1;
  Predicate2AllowedLocationsRelative[vcard_Family][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[vcard_Family][0].Type = CRDFObject::LITERAL;
  Predicate2AllowedLocationsRelative[vcard_Family][0].Location.resize(2);
  Predicate2AllowedLocationsRelative[vcard_Family][0].Location[0] = any;
  Predicate2AllowedLocationsRelative[vcard_Family][0].Location[1] = vcard_N;

  // vcard_Given:
  Predicate2AllowedLocationsRelative[vcard_Given].resize(1);
  // *.vcard_N, 1
  Predicate2AllowedLocationsRelative[vcard_Given][0].MaxOccurance = 1;
  Predicate2AllowedLocationsRelative[vcard_Given][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[vcard_Given][0].Type = CRDFObject::LITERAL;
  Predicate2AllowedLocationsRelative[vcard_Given][0].Location.resize(2);
  Predicate2AllowedLocationsRelative[vcard_Given][0].Location[0] = any;
  Predicate2AllowedLocationsRelative[vcard_Given][0].Location[1] = vcard_N;

  // vcard_N:
  Predicate2AllowedLocationsRelative[vcard_N] = VCardOneBlankNode;

  // vcard_ORG:
  Predicate2AllowedLocationsRelative[vcard_ORG] = VCardOneBlankNode;

  // vcard_Orgname:
  Predicate2AllowedLocationsRelative[vcard_Orgname].resize(1);
  // *.vcard_ORG, 1
  Predicate2AllowedLocationsRelative[vcard_Orgname][0].MaxOccurance = 1;
  Predicate2AllowedLocationsRelative[vcard_Orgname][0].ReadOnly = false;
  Predicate2AllowedLocationsRelative[vcard_Orgname][0].Type = CRDFObject::LITERAL;
  Predicate2AllowedLocationsRelative[vcard_Orgname][0].Location.resize(2);
  Predicate2AllowedLocationsRelative[vcard_Orgname][0].Location[0] = any;
  Predicate2AllowedLocationsRelative[vcard_Orgname][0].Location[1] = vcard_ORG;
}

// static
std::vector< CRDFPredicate::AllowedLocationList > CRDFPredicate::Predicate2AllowedLocationsAbsolute;

// static
void CRDFPredicate::createAllowedLocationsAbsolute()
{
  size_t Predicate, PredicateMax = Predicate2AllowedLocationsRelative.size();

  for (Predicate = 0; Predicate < PredicateMax; Predicate++)
    createAllowedLocationsAbsolute((ePredicateType) Predicate);
}

// static
void CRDFPredicate::createAllowedLocationsAbsolute(const CRDFPredicate::ePredicateType & predicate)
{
  AllowedLocationList & RelativeList = Predicate2AllowedLocationsRelative[predicate];
  AllowedLocationList & AbsoluteList = Predicate2AllowedLocationsAbsolute[predicate];

  // Since we are called recursively the absolute locations might already have been build.
  if (AbsoluteList.size() > 0) return;

  sAllowedLocation Relative;

  size_t i, imax = RelativeList.size();

  for (i = 0; i < imax; i++)
    {
      sAllowedLocation & Relative = RelativeList[i];

      sAllowedLocation Absolute;
      Absolute.MaxOccurance = Relative.MaxOccurance;
      Absolute.Type = Relative.Type;

      // Debugging
      assert(Relative.Location.size() > 0);

      ePredicateType Parent = Relative.Location[0];
      size_t StartIndex = 0;

      // about is the root, i.e., the path is absolute
      if (Parent == about)
        {
          Absolute.ReadOnly = Relative.ReadOnly;
          Absolute.Location = Relative.Location;

          // Add the predicate itself.
          Absolute.Location.push_back(predicate);
          AbsoluteList.push_back(Absolute);

          continue;
        }

      if (Parent == any)
        {
          // Debugging
          assert(Relative.Location.size() > 1);
          Parent = Relative.Location[1];
          StartIndex = 1;
        }

      // Make sure that the absolute path of the parent is known
      createAllowedLocationsAbsolute(Parent);
      AllowedLocationList & ParentList = Predicate2AllowedLocationsAbsolute[Parent];

      // For each parent path append the relative path
      size_t j, jmax = ParentList.size();

      for (j = 0; j < jmax; j++)
        {
          Absolute.ReadOnly = ParentList[j].ReadOnly || Relative.ReadOnly;
          Absolute.Location = ParentList[j].Location;

          size_t k, kmax = Relative.Location.size();

          for (k = StartIndex + 1; k < kmax; k++)
            Absolute.Location.push_back(Relative.Location[k]);

          // Add the predicate itself.
          Absolute.Location.push_back(predicate);
          AbsoluteList.push_back(Absolute);
        }
    }
}

void CRDFPredicate::initialize()
{
  static bool Initialized = false;

  if (Initialized)
    return;

  Initialized = true;

  // Fill URI2Predicate
  createURI2Predicate();

  // Fill DisplayName2Predicate
  createDisplayName2Predicate();

  // Fill relative allowed locations
  createAllowedLocationsRelative();

  // Fill relative allowed locations
  createAllowedLocationsAbsolute();
}

// Methods
CRDFPredicate::CRDFPredicate(const ePredicateType & type):
  mType(type),
  mURI()
{
  initialize();
  mURI = CRDFPredicate::PredicateURI[mType];
}

CRDFPredicate::CRDFPredicate(const std::string & uri):
  mType(),
  mURI(uri)
{
  initialize();
  mType = CRDFPredicate::getPredicateFromURI(mURI);

  if (mType == rdf_li)
    mURI = CRDFPredicate::PredicateURI[mType];
}

CRDFPredicate::CRDFPredicate(const CRDFPredicate & src):
  mType(src.mType),
  mURI(src.mURI)
{}

CRDFPredicate::~CRDFPredicate()
{}

CRDFPredicate CRDFPredicate::operator = (const ePredicateType & type)
{return CRDFPredicate(type);}

const CRDFPredicate::ePredicateType & CRDFPredicate::getType() const
{return mType;}

void CRDFPredicate::setURI(const std::string & uri)
{
  mType = getPredicateFromURI(uri);

  if (mType == rdf_li)
    mURI = CRDFPredicate::PredicateURI[mType];
  else
    mURI = uri;
}

const std::string & CRDFPredicate::getURI() const
{return mURI;}

bool CRDFPredicate::operator == (const CRDFPredicate & rhs) const
{return mURI == rhs.mURI;}

bool CRDFPredicate::operator != (const CRDFPredicate & rhs) const
{return mURI != rhs.mURI;}

bool CRDFPredicate::operator < (const CRDFPredicate & rhs) const
{return mURI < rhs.mURI;}

// friend
std::ostream & operator << (std::ostream & os, const CRDFPredicate & p)
{
  os << p.mType;
  return os;
}

// static
const CRDFPredicate::AllowedLocationList & CRDFPredicate::getAllowedLocationList(const ePredicateType & predicate)
{
  return Predicate2AllowedLocationsAbsolute[predicate];
}

// static
const std::string & CRDFPredicate::getURI(const CRDFPredicate & predicate)
{
  return PredicateURI[predicate.mType];
}

// static
CRDFPredicate::ePredicateType CRDFPredicate::getPredicateFromURI(const std::string & URI)
{
  std::map< std::string, ePredicateType >::iterator it = URI2Predicate.find(URI);

  if (it != URI2Predicate.end())
    return it->second;
  // Handle rdf:_n and map it to rdf:li
  else if (URI.compare(0, PredicateURI[rdf__n].length(), PredicateURI[rdf__n]) == 0)
    return rdf_li;
  else
    return unknown;
}

// static
const std::string & CRDFPredicate::getDisplayName(const CRDFPredicate & predicate)
{
  return PredicateDisplayName[predicate.mType];
}

// static
CRDFPredicate::ePredicateType CRDFPredicate::getPredicateFromDisplayName(const std::string & displayName)
{
  std::map< std::string, ePredicateType >::iterator it = DisplayName2Predicate.find(displayName);

  if (it != DisplayName2Predicate.end())
    return it->second;
  else
    return unknown;
}

// static
size_t CRDFPredicate::getSubPathIndex(const CRDFPredicate::Path & fullPath,
                                      const CRDFPredicate::Path & currentPath)
{
  // If the current path is longer than the full path we fail
  if (currentPath.size() > fullPath.size())
    return C_INVALID_INDEX;

  // Check whether the current path is part of the full path;
  Path::const_iterator itCurrent = currentPath.begin();
  Path::const_iterator endCurrent = currentPath.end();
  Path::const_iterator itFull = fullPath.begin();

  for (; itCurrent != endCurrent; ++itCurrent, ++itFull)
    if (*itCurrent != *itFull)
      return C_INVALID_INDEX;

  return currentPath.size();
}

// static
bool CRDFPredicate::isReadOnly(const Path & currentPath)
{
  // Iterate over each predicate
  std::vector< AllowedLocationList >::const_iterator itPredicate = Predicate2AllowedLocationsAbsolute.begin();
  std::vector< AllowedLocationList >::const_iterator endPredicate = Predicate2AllowedLocationsAbsolute.end();

  for (; itPredicate != endPredicate; ++itPredicate)
    {
      // Iterate over each location
      AllowedLocationList::const_iterator itLocation = itPredicate->begin();
      AllowedLocationList::const_iterator endLocation = itPredicate->end();

      for (; itLocation != endLocation; ++itLocation)
        if (itLocation->ReadOnly &&
            currentPath.size() == itLocation->Location.size())
          {
            // Compare the path.
            Path::const_iterator itCurrent = currentPath.begin();
            Path::const_iterator endCurrent = currentPath.end();
            Path::const_iterator itAbsolute = itLocation->Location.begin();

            for (; itCurrent != endCurrent; ++itCurrent, ++itAbsolute)
              if (*itCurrent != *itAbsolute)
                break;

            if (itCurrent == endCurrent)
              return true;
          }
    }

  return false;
}

std::ostream & operator << (std::ostream & os, const CRDFPredicate::Path & path)
{
  os << "Path: ";
  std::vector< CRDFPredicate::ePredicateType >::const_iterator it = path.begin();
  std::vector< CRDFPredicate::ePredicateType >::const_iterator end = path.end();

  for (; it != end; ++it)
    os << *it << " ";

  return os << std::endl;
}

std::ostream & operator << (std::ostream & os, const CRDFPredicate::sAllowedLocation & location)
{
  os << "MaxOccurance: " << location.MaxOccurance << std::endl;
  os << "ReadOnly: " << location.ReadOnly << std::endl;
  os << "Type: " << location.Type << std::endl;
  os << location.Location << std::endl;

  return os;
}
