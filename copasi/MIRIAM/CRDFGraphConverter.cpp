// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraphConverter.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/04 14:17:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFGraphConverter.h"
#include "CRDFParser.h"
#include "CRDFWriter.h"
#include "CRDFNode.h"

// static
CRDFGraphConverter::sChange CRDFGraphConverter::SBML2CopasiChanges[] =
  {
    {
      CRDFPredicate::bqbiol_encodes,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_encodes, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_hasPart,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_hasPart, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_hasVersion,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_hasVersion, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_is,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_is, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_isDescribedBy,
      {
        CRDFPredicate::about, CRDFPredicate::dcterms_bibliographicCitation, CRDFPredicate::copasi_isDescribedBy, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_isEncodedBy,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_isEncodedBy, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_isHomologTo,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_isHomologTo, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_isPartOf,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_isPartOf, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_isVersionOf,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_isVersionOf, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqbiol_occursIn,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_occursIn, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqmodel_is,
      {
        CRDFPredicate::about, CRDFPredicate::copasi_is, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::bqmodel_isDescribedBy,
      {
        CRDFPredicate::about, CRDFPredicate::dcterms_bibliographicCitation, CRDFPredicate::copasi_isDescribedBy, CRDFPredicate::end
      }
    },
    {
      CRDFPredicate::dc_creator,
      {
        CRDFPredicate::about, CRDFPredicate::dcterms_creator, CRDFPredicate::end
      },
    },
    {
      CRDFPredicate::end,
      {
        CRDFPredicate::end
      }
    }
  };

// static
bool CRDFGraphConverter::SBML2Copasi(std::string & XML)
{
  // Create the RDF graph
  CRDFGraph * pGraph = CRDFParser::graphFromXml(XML);
  if (pGraph == NULL)
    return false;

  // Convert the graph.
  bool success = convert(pGraph, SBML2CopasiChanges);

  // Serialize the graph
  XML = CRDFWriter::xmlFromGraph(pGraph);

  return success;
}

// static
bool CRDFGraphConverter::convert(CRDFGraph * pGraph, const CRDFGraphConverter::sChange * changes)
{
  bool success = true;

  std::set< CRDFGraph::CTriplet> Triplets;
  std::set< CRDFGraph::CTriplet>::iterator it;
  std::set< CRDFGraph::CTriplet>::iterator end;

  const sChange * pChange = changes;

  // We iterate over each predicate which needs to be changed.
  for (; pChange->Source != CRDFPredicate::end; ++pChange)
    {
      Triplets = pGraph->getTripletsWithPredicate(pChange->Source);
      it = Triplets.begin();
      end = Triplets.end();

      // Apply the needed changes
      for (; it != end; ++it)
        {
          CRDFPredicate::Path NewPath;
          const CRDFPredicate::ePredicateType * pNewPath = pChange->Target;
          while (*pNewPath != CRDFPredicate::end)
            NewPath.push_back(*pNewPath++);

          success &= convert(pGraph, *it, NewPath);
        }
    }

  return false;
}

// static
bool CRDFGraphConverter::convert(CRDFGraph * pGraph,
                                 const CRDFGraph::CTriplet & triplet,
                                 const CRDFPredicate::Path & newPath)
{
  CRDFPredicate::Path CurrentPath = triplet.pObject->getPath();

  unsigned SubPathIndex = C_INVALID_INDEX;

  while (SubPathIndex == C_INVALID_INDEX && SubPathIndex > 0)
    {
      // We differ at least at the final predicate.
      CurrentPath.pop_back();
      SubPathIndex = CRDFPredicate::getSubPathIndex(newPath, CurrentPath);
    }

  if (SubPathIndex == 0)
    return false;

  CurrentPath = triplet.pObject->getPath();

  bool success = true;

  CRDFGraph::CTriplet Triplet;

  if (CurrentPath.size() < newPath.size())
    {
      // We need to create the additional node pointed to by newPath[SubPathIndex]
      // Verify that the node to be created is a blank node.
      CRDFPredicate::AllowedLocationList List =
        CRDFPredicate::getAllowedLocationList(newPath[SubPathIndex]);
      CRDFPredicate::AllowedLocationList::const_iterator it = List.begin();
      CRDFPredicate::AllowedLocationList::const_iterator end = List.end();
      for (; it != end; ++it)
        {
          if (it->Type == CRDFObject::BLANK_NODE &&
              CRDFPredicate::getSubPathIndex(newPath, it->Location))
            break;
        }

      if (it == end)
        return false;

      // We are now sure that the new predicate points to a blank node.
      CRDFObject object;
      object.setType(CRDFObject::BLANK_NODE);
      object.setBlankNodeId(pGraph->generatedBlankNodeId());

      Triplet = pGraph->addTriplet(triplet.pSubject->getSubject(),
                                   CRDFPredicate::getURI(newPath[SubPathIndex]),
                                   object);

      if (!Triplet == false)
        Triplet = pGraph->moveEdge(triplet.pSubject,
                                   Triplet.pObject,
                                   CRDFEdge(triplet.Predicate, triplet.pObject));
    }
  else if (CurrentPath.size() > newPath.size())
    {
      // TODO This needs to be implemented
      // Removing an edge will always result in loosing information!
    }
  else
    {
      // We just have to rename the predicate
      success &= triplet.pSubject->addEdgeInternal(CRDFEdge(newPath[SubPathIndex], triplet.pObject));
      success &= triplet.pSubject->removeEdgeInternal(CRDFEdge(triplet.Predicate, triplet.pObject));

      if (success)
        {
          Triplet = triplet;
          Triplet.Predicate = newPath[SubPathIndex];
        }
    }

  if (!Triplet)
    return false;

  // Check whether we are finished
  if (SubPathIndex == newPath.size() - 1)
    return success;

  return convert(pGraph, Triplet, newPath);
}
