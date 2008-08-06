// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CConstants.cpp,v $
//   $Revision: 1.6.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/08/06 17:49:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CConstants.h"
#include "CRDFGraph.h"

// static
CMIRIAMResource::sResource CMIRIAMResource::Resources[] =
  {
    {
      "MIR:00000036",
      "ArrayExpress",
      "http://www.ebi.ac.uk/arrayexpress/",
      "urn:miriam:arrayexpress",
      {
        "http://arrayexpress.org/",
        ""
      },
      "^[AEP]-\\w{4}-\\d+$",
      false
    },
    {
      "MIR:00000035",
      "arXiv",
      "http://arxiv.org/",
      "urn:miriam:arxiv",
      {
        "http://arxiv.org/",
        "urn:oai:arXiv.org:",
        ""
      },
      "^(\\w+(\\-\\w+)?(\\.\\w+)?/)?\\d{4,7}(\\.\\d{4}(v\\d+)?)?$",
      false
    },
    {
      "MIR:00000001",
      "BIND",
      "http://www.bind.ca/",
      "urn:miriam:bind",
      {
        "http://www.bind.ca/",
        ""
      },
      "^\\d+$",
      false
    },
    {
      "MIR:00000007",
      "BioModels Database",
      "http://www.ebi.ac.uk/biomodels/",
      "urn:miriam:biomodels.db",
      {
        "http://www.ebi.ac.uk/biomodels/",
        ""
      },
      "^BIOMD\\d{10}$",
      false
    },
    {
      "MIR:00000002",
      "ChEBI",
      "http://www.ebi.ac.uk/chebi/",
      "urn:miriam:obo.chebi",
      {
        "http://www.ebi.ac.uk/chebi/",
        ""
      },
      "^CHEBI:\\d+$",
      false
    },
    {
      "MIR:00000021",
      "CluSTr",
      "http://www.ebi.ac.uk/clustr/",
      "urn:miriam:clustr",
      {
        "http://www.ebi.ac.uk/clustr/",
        ""
      },
      "^[0-9A-Za-z]+:\\d+:\\d{1,5}(\\.\\d)?$",
      false
    },
    {
      "MIR:00000044",
      "Database of Interacting Proteins",
      "http://dip.doe-mbi.ucla.edu/",
      "urn:miriam:dip",
      {
        ""
      },
      "^DIP\\:\\d{3}[EN]$",
      true
    },
    {
      "MIR:00000019",
      "DOI",
      "http://www.doi.org/",
      "urn:miriam:doi",
      {
        "http://www.doi.org/",
        ""
      },
      "^\\d{2}\\.\\d{4}/.*$",
      true
    },
    {
      "MIR:00000003",
      "Ensembl",
      "http://www.ensembl.org/",
      "urn:miriam:ensembl",
      {
        "http://www.ensembl.org/",
        ""
      },
      "^ENS(\\w{3})*[FPTG]\\d{11}$",
      false
    },
    {
      "MIR:00000004",
      "Enzyme Nomenclature",
      "http://www.ebi.ac.uk/intenz/",
      "urn:miriam:ec-code",
      {
        "http://www.ec-code.org/",
        "http://www.ebi.ac.uk/IntEnz/",
        "urn:lsid:ec-code.org",
        ""
      },
      "^\\d+|\\d+\\.(-|\\d+)|\\d+\\.\\d+\\.(-|\\d+)|\\d+\\.\\d+\\.\\d+\\.(-|\\d+)$",
      false
    },
    {
      "MIR:00000030",
      "FlyBase",
      "http://www.flybase.org/",
      "urn:miriam:flybase",
      {
        "http://www.flybase.org/",
        ""
      },
      "^FB\\w{2}\\d{7}$",
      false
    },
    {
      "MIR:00000022",
      "Gene Ontology",
      "http://www.ebi.ac.uk/ego/",
      "urn:miriam:obo.go",
      {
        "http://www.geneontology.org/",
        ""
      },
      "^GO:\\d{7}$",
      false
    },
    {
      "MIR:00000051",
      "HMDB",
      "http://www.hmdb.ca/",
      "urn:miriam:hmdb",
      {
        ""
      },
      "^HMDB\\d{5}$",
      false
    },
    {
      "MIR:00000009",
      "ICD",
      "http://www3.who.int/icd/currentversion/fr-icd.htm",
      "urn:miriam:icd",
      {
        "http://www.who.int/classifications/icd/",
        ""
      },
      "^[A-Z]\\d+(\\.[-\\d+])?$",
      false
    },
    {
      "MIR:00000010",
      "IntAct",
      "http://www.ebi.ac.uk/intact/",
      "urn:miriam:intact",
      {
        "http://www.ebi.ac.uk/intact/",
        ""
      },
      "^EBI\\-[0-9]+$",
      false
    },
    {
      "MIR:00000011",
      "InterPro",
      "http://www.ebi.ac.uk/interpro/",
      "urn:miriam:interpro",
      {
        "http://www.ebi.ac.uk/interpro/",
        ""
      },
      "IPR\\d{6}$",
      false
    },
    {
      "MIR:00000043",
      "IPI",
      "http://www.ebi.ac.uk/IPI",
      "urn:miriam:ipi",
      {
        ""
      },
      "^IPI\\d{8}$",
      false
    },
    {
      "MIR:00000013",
      "KEGG Compound",
      "http://www.genome.jp/kegg/ligand.html",
      "urn:miriam:kegg.compound",
      {
        "http://www.genome.jp/kegg/compound/",
        ""
      },
      "^C\\d+$",
      false
    },
    {
      "MIR:00000025",
      "KEGG Drug",
      "http://www.genome.jp/kegg/drug/",
      "urn:miriam:kegg.drug",
      {
        "http://www.genome.jp/kegg/drug/",
        ""
      },
      "^D\\d+$",
      false
    },
    {
      "MIR:00000026",
      "KEGG Glycan",
      "http://www.genome.jp/kegg/glycan/",
      "urn:miriam:kegg.glycan",
      {
        "http://www.genome.jp/kegg/glycan/",
        ""
      },
      "^G\\d+$",
      false
    },
    {
      "MIR:00000012",
      "KEGG Pathway",
      "http://www.genome.jp/kegg/pathway.html",
      "urn:miriam:kegg.pathway",
      {
        "http://www.genome.jp/kegg/pathway/",
        ""
      },
      "^\\w{2,3}\\d{5}$",
      false
    },
    {
      "MIR:00000014",
      "KEGG Reaction",
      "http://www.genome.jp/kegg/ligand.html",
      "urn:miriam:kegg.reaction",
      {
        "http://www.genome.jp/kegg/reaction/",
        ""
      },
      "^R\\d+$",
      false
    },
    {
      "MIR:00000052",
      "LIPID MAPS",
      "http://www.lipidmaps.org",
      "urn:miriam:lipidmaps",
      {
        ""
      },
      "^LM(FA|GL|GP|SP|ST|PR|SL|PK)[0-9]{6}[0-9a-zA-Z]{4}$",
      false
    },
    {
      "MIR:00000042",
      "MINT",
      "http://mint.bio.uniroma2.it/mint/",
      "urn:miriam:mint",
      {
        ""
      },
      "^MINT\\-\\d{1,5}$",
      false
    },
    {
      "MIR:00000008",
      "MIRIAM Resources",
      "http://www.ebi.ac.uk/compneur-srv/miriam/",
      "urn:miriam:miriam",
      {
        "http://biomodels.net/MIRIAM/",
        "http://www.biomodels.net/MIRIAM/",
        ""
      },
      "^MIR:\\d{8}$",
      false
    },
    {
      "MIR:00000037",
      "Mouse Genome Database",
      "http://www.informatics.jax.org/",
      "urn:miriam:mgd",
      {
        "http://mousegenome.org/",
        ""
      },
      "^MGI:\\d+$",
      false
    },
    {
      "MIR:00000029",
      "Nucleotide Sequence Database",
      "http://www.ncbi.nlm.nih.gov/Genbank/",
      "urn:miriam:insdc",
      {
        "http://www.insdc.org/",
        ""
      },
      "^[a..zA..Z]+(\\_)?\\d+(\\.\\d+)?$",
      false
    },
    {
      "MIR:00000016",
      "OMIM",
      "http://www.ncbi.nlm.nih.gov/entrez/query.fcgi?db=OMIM",
      "urn:miriam:omim",
      {
        "http://www.ncbi.nlm.nih.gov/OMIM/",
        ""
      },
      "^[*#+%^]?\\d{6}$",
      false
    },
    {
      "MIR:00000028",
      "Pfam",
      "http://pfam.sanger.ac.uk/",
      "urn:miriam:pfam",
      {
        "http://pfam.org/",
        ""
      },
      "^PF\\d{5}$",
      false
    },
    {
      "MIR:00000017",
      "PIRSF",
      "http://pir.georgetown.edu/pirsf/",
      "urn:miriam:pirsf",
      {
        "http://pir.georgetown.edu/pirsf/",
        ""
      },
      "^PIRSF\\d{6}$",
      false
    },
    {
      "MIR:00000032",
      "PROSITE",
      "http://www.expasy.org/prosite/",
      "urn:miriam:prosite",
      {
        "http://www.prosite.org/",
        ""
      },
      "^PS\\d{5}$",
      false
    },
    {
      "MIR:00000020",
      "Protein Data Bank",
      "http://www.pdb.org/",
      "urn:miriam:pdb",
      {
        "http://www.pdb.org/",
        ""
      },
      "^\\d[0..9a..zA..Z]{3}$",
      false
    },
    {
      "MIR:00000034",
      "PubChem-compound",
      "http://pubchem.ncbi.nlm.nih.gov/",
      "urn:miriam:pubchem.compound",
      {
        "http://www.pubchem.gov/compound/",
        ""
      },
      "^\\d+$",
      false
    },
    {
      "MIR:00000033",
      "PubChem-substance",
      "http://pubchem.ncbi.nlm.nih.gov/",
      "urn:miriam:pubchem.substance",
      {
        "http://www.pubchem.gov/substance/",
        ""
      },
      "^\\d+$",
      false
    },
    {
      "MIR:00000015",
      "PubMed",
      "http://www.ncbi.nlm.nih.gov/PubMed/",
      "urn:miriam:pubmed",
      {
        "http://www.pubmed.gov/",
        "http://www.ncbi.nlm.nih.gov/PubMed/",
        ""
      },
      "^\\d+$",
      true
    },
    {
      "MIR:00000047",
      "Rat Genome Database",
      "http://rgd.mcw.edu/genes/",
      "urn:miriam:rgd",
      {
        ""
      },
      "^\\d{4,7}$",
      false
    },
    {
      "MIR:00000018",
      "Reactome",
      "http://www.reactome.org/",
      "urn:miriam:reactome",
      {
        "http://www.reactome.org/",
        ""
      },
      "^REACT_\\d+(\\.\\d+)?$",
      false
    },
    {
      "MIR:00000039",
      "RefSeq",
      "http://www.ncbi.nlm.nih.gov/projects/RefSeq/",
      "urn:miriam:refseq",
      {
        ""
      },
      "^[NC|AC|NG|NT|NW|NZ|NM|NR|XM|XR|NP|AP|XP|ZP]_\\d+$",
      false
    },
    {
      "MIR:00000046",
      "RESID",
      "http://www.ebi.ac.uk/RESID/",
      "urn:miriam:resid",
      {
        ""
      },
      "^AA\\d{4}$",
      false
    },
    {
      "MIR:00000038",
      "SABIO-RK Reaction",
      "http://sabio.bioquant.uni-heidelberg.de/SABIORK/",
      "urn:miriam:sabiork.reaction",
      {
        "http://sabio.villa-bosch.de/reaction/",
        ""
      },
      "^\\d+$",
      false
    },
    {
      "MIR:00000023",
      "Saccharomyces genome database",
      "http://www.yeastgenome.org/",
      "urn:miriam:sgd",
      {
        "http://www.yeastgenome.org/",
        ""
      },
      "^S\\d+$",
      false
    },
    {
      "MIR:00000045",
      "Signaling Gateway",
      "http://www.signaling-gateway.org/",
      "urn:miriam:signaling-gateway",
      {
        ""
      },
      "^A0/d+$",
      false
    },
    {
      "MIR:00000024",
      "Systems Biology Ontology",
      "http://biomodels.net/SBO/",
      "urn:miriam:obo.sbo",
      {
        "http://biomodels.net/SBO/",
        "http://www.biomodels.net/SBO/",
        ""
      },
      "^SBO:\\d{7}$",
      false
    },
    {
      "MIR:00000049",
      "TAIR Gene",
      "http://arabidopsis.org/index.jsp",
      "urn:miriam:tair.gene",
      {
        ""
      },
      "^Gene\\:\\d{7}$",
      false
    },
    {
      "MIR:000000050",
      "TAIR Locus",
      "http://arabidopsis.org/index.jsp",
      "urn:miriam:tair.locus",
      {
        ""
      },
      "^AT\\d[1-5]G\\d{5}$",
      false
    },
    {
      "MIR:00000048",
      "TAIR Protein",
      "http://arabidopsis.org/index.jsp",
      "urn:miriam:tair.protein",
      {
        ""
      },
      "^AASequence\\:\\d{10}$",
      false
    },
    {
      "MIR:00000006",
      "Taxonomy",
      "http://www.ncbi.nlm.nih.gov/Taxonomy/",
      "urn:miriam:taxonomy",
      {
        "http://www.taxonomy.org/",
        "http://www.ncbi.nlm.nih.gov/Taxonomy/",
        ""
      },
      "^\\d+$",
      false
    },
    {
      "MIR:00000040",
      "Transport Classification Database",
      "http://www.tcdb.org/index.php",
      "urn:miriam:tcdb",
      {
        ""
      },
      "^\\d+\\.[A-Z]\\.\\d+\\.\\d+\\.\\d+$",
      false
    },
    {
      "MIR:00000041",
      "UniParc",
      "http://www.ebi.ac.uk/uniparc/",
      "urn:miriam:uniparc",
      {
        ""
      },
      "^UPI[A-F0-9]{10}$",
      false
    },
    {
      "MIR:00000005",
      "UniProt",
      "http://www.ebi.uniprot.org/",
      "urn:miriam:uniprot",
      {
        "urn:lsid:uniprot.org",
        "urn:lsid:uniprot.org:uniprot",
        "http://www.uniprot.org/",
        ""
      },
      "^([AOPQ][0-9][A-Z0-9][A-Z0-9][A-Z0-9][0-9](_[\\dA-Z]{1,5})?)$",
      false
    },
    {
      "MIR:00000027",
      "WormBase",
      "http://www.wormbase.org/",
      "urn:miriam:wormbase",
      {
        "http://www.wormbase.org/",
        ""
      },
      "^WBGene\\d{8}$",
      false
    },
    {
      "MIR:00000031",
      "Wormpep",
      "http://www.wormbase.org/db/seq/protein",
      "urn:miriam:wormpep",
      {
        "http://www.wormpep.org/",
        ""
      },
      "^CE\\d{5}$",
      false
    },
    // This must always be the last line
    {"", "unknown", "", "", {""}, ".*", false}
  };

// static
bool CMIRIAMResource::Initialized = false;

// static
std::map< std::string, unsigned C_INT32 > CMIRIAMResource::DisplayName2Resource;

// static
void CMIRIAMResource::createDisplayNameMap()
{
  unsigned C_INT32 Index;

  for (Index = 0; Resources[Index].MiriamId != ""; ++Index)
    DisplayName2Resource[Resources[Index].DisplayName] = Index;
}

// static
std::map< std::string, unsigned C_INT32 > CMIRIAMResource::URI2Resource;

// static
void CMIRIAMResource::createURIMap()
{
  unsigned C_INT32 Index;

  for (Index = 0; Resources[Index].MiriamId != ""; ++Index)
    {
      URI2Resource[Resources[Index].URI] = Index;

      std::string * pDeprecated = & Resources[Index].Deprecated[0];
      while (*pDeprecated != "")
        URI2Resource[*pDeprecated++] = Index;
    }
}

// static
unsigned C_INT32 CMIRIAMResource::getResource(const std::string & URI)
{
  // Since the URI contains always an id this will always point past the actual element.
  std::map< std::string , unsigned C_INT32 >::const_iterator it = URI2Resource.upper_bound(URI);

  // we have an unknown URI
  if (it == URI2Resource.begin())
    return C_INVALID_INDEX;

  // it-- is defined for end as long as x exist with x++ = end, i.e., the map is not empty.
  it--;

  const sResource & Resource = Resources[it->second];

  // Check whether the URI base of the candidate matches.
  if (URI.substr(0, Resource.URI.length()) == Resource.URI)
    return it->second;

  // We need to check for deprecated URIs
  const std::string * pDeprecated = &Resource.Deprecated[0];
  for (; *pDeprecated != ""; ++pDeprecated)
    if (URI.substr(0, pDeprecated->length()) == *pDeprecated)
      return it->second;

  return C_INVALID_INDEX;
}

// static
const CMIRIAMResource::sResource * CMIRIAMResource::getResourceList()
{return Resources;}

CMIRIAMResource::CMIRIAMResource(CRDFNode * pNode):
    mResource(C_INVALID_INDEX),
    mId(),
    mpNode(pNode)
{
  if (!Initialized)
    {
      Initialized = true;
      createDisplayNameMap();
      createURIMap();
    }

  if (mpNode != NULL)
    setURI(mpNode->getObject().getResource());
}

CMIRIAMResource::CMIRIAMResource(const std::string & displayName, const std::string & id):
    mResource(C_INVALID_INDEX),
    mId(),
    mpNode(NULL)
{
  if (!Initialized)
    {
      Initialized = true;
      createDisplayNameMap();
      createURIMap();
    }

  setDisplayName(displayName);
  mId = id;
}

CMIRIAMResource::CMIRIAMResource(const CMIRIAMResource & src):
    mResource(src.mResource),
    mId(src.mId)
{}

bool CMIRIAMResource::setId(const std::string & id)
{
  mId = id;
  return isValid();
}

const std::string & CMIRIAMResource::getId() const
  {
    return mId;
  }

bool CMIRIAMResource::setURI(const std::string & URI)
{
  mResource = getResource(URI);
  extractId(URI);

  return isValid();
}

std::string CMIRIAMResource::getURI() const
  {
    // Check whether the resource is known.
    if (!isValid())
      return "";

    return Resources[mResource].URI + ":" + mId;
  }

bool CMIRIAMResource::setNode(CRDFNode * pNode)
{
  mpNode = pNode;

  if (mpNode != NULL)
    return setURI(mpNode->getObject().getResource());

  return true;
}

CRDFNode * CMIRIAMResource::getNode() const
{return mpNode;}

bool CMIRIAMResource::setDisplayName(const std::string & displayName)
{
  // Check if the display name is a know resource
  std::map< std::string, unsigned C_INT32>::const_iterator it =
    DisplayName2Resource.find(displayName.c_str());

  // If we did not find the resource we set it to unknown
  if (it == DisplayName2Resource.end())
    {
      // unknown is indicated by an invalid index.
      mResource = C_INVALID_INDEX;
      return false;
    }

  mResource = it->second;
  return isValid();
}

std::string CMIRIAMResource::getDisplayName() const
  {
    // Check whether the resource is known.
    if (mResource == C_INVALID_INDEX)
      return "";

    return Resources[mResource].DisplayName;
  }

bool CMIRIAMResource::isValid() const
  {
    // Check whether the resource is known.
    if (mResource == C_INVALID_INDEX)
      return false;

    // Empty IDs are not allowed.
    if (mId == "")
      return false;

    // TODO Check whether the Id matches the regular expression.
    return true;
  }

bool CMIRIAMResource::isValid(const std::string & URI) const
  {
    if (getResource(URI) != mResource ||
        mResource == C_INVALID_INDEX)
      return false;

    return true;
  }

void CMIRIAMResource::extractId(const std::string & URI)
{
  mId = "";

  // Check whether the resource is known.
  if (mResource == C_INVALID_INDEX)
    return;

  if (URI.substr(0, Resources[mResource].URI.length()) == Resources[mResource].URI)
    mId = URI.substr(Resources[mResource].URI.length() + 1);

  // We need to check for deprecated URIs
  std::string * pDeprecated = &Resources[mResource].Deprecated[0];
  for (; *pDeprecated != ""; ++pDeprecated)
    if (URI.substr(0, pDeprecated->length()) == *pDeprecated)
      {
        mId = URI.substr(pDeprecated->length() + 1);
        break;
      }

  return;
}
