// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CConstants.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/10 15:49:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CConstants.h"

std::map<std::string, std::string> CConstants::referencePredicates;
std::map<std::string, std::string> CConstants::prefix2URI;
std::map<std::string, std::string> CConstants::relationships;
std::map<std::string, std::string> CConstants::resources;

CConstants c;
CConstants::CConstants()
{
  referencePredicates["Pubmed"] = "http://www.pubmed.gov/#";
  referencePredicates["DOI"] = "http://dx.doi.org/";

  prefix2URI["rdf"] = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
  prefix2URI["dc"] = "http://purl.org/dc/elements/1.1/";
  prefix2URI["dcterms"] = "http://purl.org/dc/terms/";
  prefix2URI["vCard"] = "http://www.w3.org/2001/vcard-rdf/3.0#";
  prefix2URI["bqbiol"] = "http://biomodels.net/biology-qualifiers/";
  prefix2URI["bqmodel"] = "http://biomodels.net/model-qualifiers/";

  relationships["bqbiol:encodes"] = "encodes";
  relationships["bqbiol:hasPart"] = "has part";
  relationships["bqbiol:hasVersion"] = "has version";
  relationships["bqbiol:is"] = "is";
  relationships["bqbiol:isEncodedBy"] = "is encoded by";
  relationships["bqbiol:isHomologTo"] = "is homolog to";
  relationships["bqbiol:isPartOf"] = "is part of";
  relationships["bqbiol:isVersionOf"] = "is version of";

  resources["ArrayExpress"] = "http://arrayexpress.org/";
  resources["arXiv"] = "http://arxiv.org/";
  resources["BIND"] = "http://www.bind.ca/";
  resources["BioModels Database"] = "http://www.ebi.ac.uk/biomodels/";
  resources["ChEBI"] = "http://www.ebi.ac.uk/chebi/";
  resources["CluSTr"] = "http://www.ebi.ac.uk/clustr/";
  resources["DOI"] = "http://www.doi.org/";
  resources["Ensembl"] = "http://www.ensembl.org/";
  resources["Enzyme Nomenclature"] = "http://www.ec-code.org/";
  resources["FlyBase"] = "http://www.flybase.org/";
  resources["Gene Ontology"] = "http://www.geneontology.org/";
  resources["ICD"] = "http://www.who.int/classifications/icd/";
  resources["IntAct"] = "http://www.ebi.ac.uk/intact/";
  resources["InterPro"] = "http://www.ebi.ac.uk/interpro/";
  resources["KEGG Compound"] = "http://www.genome.jp/kegg/compound/";
  resources["KEGG Drug"] = "http://www.genome.jp/kegg/drug/";
  resources["KEGG Glycan"] = "http://www.genome.jp/kegg/glycan/";
  resources["KEGG Pathway"] = "http://www.genome.jp/kegg/pathway/";
  resources["KEGG Reaction"] = "http://www.genome.jp/kegg/reaction/";
  resources["MIRIAM Resources"] = "http://biomodels.net/MIRIAM/";
  resources["Mouse Genome Database"] = "http://mousegenome.org/";
  resources["Nucleotide Sequence Database"] = "http://www.insdc.org/";
  resources["OMIM"] = "http://www.ncbi.nlm.nih.gov/OMIM/";
  resources["Pfam"] = "http://pfam.org/";
  resources["PIRSF"] = "http://pir.georgetown.edu/pirsf/";
  resources["PROSITE"] = "http://www.prosite.org/";
  resources["Protein Data Bank"] = "http://www.pdb.org/";
  resources["PubChem-compound"] = "http://www.pubchem.gov/compound/";
  resources["PubChem-substance"] = "http://www.pubchem.gov/substance/";
  resources["PubMed"] = "http://www.pubmed.gov/";
  resources["Reactome"] = "http://www.reactome.org/";
  resources["SABIO-RK Reaction"] = "http://sabio.villa-bosch.de/reaction/";
  resources["Saccharomyces genome database"] = "http://www.yeastgenome.org/";
  resources["Systems Biology Ontology"] = "http://biomodels.net/SBO/";
  resources["Taxonomy"] = "http://www.taxonomy.org/";
  resources["UniProt"] = "urn:lsid:uniprot.org:uniprot";
  resources["WormBase"] = "http://www.wormbase.org/";
  resources["Wormpep"] = "http://www.wormpep.org/";
}

std::map<std::string, std::string> CConstants::getReferencePredicates()
{return referencePredicates;}

std::map<std::string, std::string> CConstants::getPrefix2URI()
{return prefix2URI;}

std::map<std::string, std::string> CConstants::getRelationships()
{return relationships;}

std::map<std::string, std::string> CConstants::getResources()
{return resources;}

std::string CConstants::getKey(const std::map<std::string, std::string>& map, const std::string& value)
{
  std::map<std::string, std::string>::const_iterator it = map.begin();
  std::map<std::string, std::string>::const_iterator end = map.end();
  for (; it != end; it++)
    {
      if (it->second == value)
      {return it->first;}
    }
  return "";
}
