// Copyright (C) 2011 - 2012 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#ifdef _WIN32
# define _USE_MATH_DEFINES // without the following define, M_PI will not be declared under windows
#endif // _WIN32

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <limits>
#include <cmath>
#include <sstream>
#include <stdlib.h> // for strtod

#define USE_LAYOUT 1
#define USE_RENDER 1

// SBML classes
#include <sbml/Compartment.h>
#include <sbml/Model.h>
#include <sbml/SBase.h>
#include <sbml/SBMLDocument.h>
#include <sbml/Species.h>
#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLNamespaces.h>
#include <sbml/xml/XMLAttributes.h>
// layout classes
#include <sbml/packages/layout/sbml/CompartmentGlyph.h>
#include <sbml/packages/layout/sbml/CubicBezier.h>
#include <sbml/packages/layout/sbml/Curve.h>
#include <sbml/packages/layout/sbml/GraphicalObject.h>
#include <sbml/packages/layout/sbml/Layout.h>
#include <sbml/packages/layout/sbml/LineSegment.h>
#include <sbml/packages/layout/sbml/ReactionGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesReferenceGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesReferenceRole.h>
#include <sbml/packages/layout/sbml/TextGlyph.h>

#include <sbml/packages/layout/extension/LayoutModelPlugin.h>

// render classes
#include <sbml/packages/render/sbml/ColorDefinition.h>
#include <sbml/packages/render/sbml/Ellipse.h>
#include <sbml/packages/render/sbml/RenderGroup.h>
#include <sbml/packages/render/sbml/LocalRenderInformation.h>
#include <sbml/packages/render/sbml/LocalStyle.h>
#include <sbml/packages/render/sbml/Polygon.h>
#include <sbml/packages/render/sbml/Rectangle.h>
#include <sbml/packages/render/sbml/RelAbsVector.h>
#include <sbml/packages/render/sbml/RenderCurve.h>
#include <sbml/packages/render/sbml/RenderPoint.h>

#include <sbml/packages/render/extension/RenderLayoutPlugin.h>

#include "CCellDesignerImporter.h"

#include "SBMLUtils.h"

// TODO modifications are not imported yet

// TODO set the role on species reference glyphs where possible, this is done on substrates and products already

// TODO modifiers are missing

// TODO deal with missing linkAnchor in a nicer way, e.g. find the closest
// TODO connection point

// TODO import render information, e.g. start with color and font size
// TODO since these should be easy

// TODO label positions on compartments are not handled

/**
 * Constructor that takes a pointer to an
 * SBMLDocument.
 * The SBMLDocument will not be copied and it will not be
 * owned by the importer.
 * If the pointer is not NULL, the class will try
 * to directly convert the CellDesigner layout if there is one.
 */
CCellDesignerImporter::CCellDesignerImporter(SBMLDocument* pDocument):
    mpDocument(pDocument),
    mpLayout(NULL),
    mpLocalRenderInfo(NULL)
{
  if (this->mpDocument != NULL &&
      this->mpDocument->getModel() != NULL &&
      this->mpDocument->getModel()->getAnnotation() != NULL)
    {
      const XMLNode* pAnnotation = this->findCellDesignerAnnotation(this->mpDocument, this->mpDocument->getModel()->getAnnotation());

      if (pAnnotation != NULL)
        {
          this->convertCellDesignerLayout(pAnnotation);
        }
    }
}

/**
 * Method to set the SBMLDocument.
 * If the pointer is not NULL, the class will try
 * to directly convert the CellDesigner layout if there is one.
 */
void CCellDesignerImporter::setSBMLDocument(SBMLDocument* pDocument)
{
  if (pDocument != this->mpDocument)
    {
      this->mpDocument = pDocument;

      if (this->mpDocument != NULL &&
          this->mpDocument->getModel() != NULL &&
          this->mpDocument->getModel()->getAnnotation() != NULL)
        {
          const XMLNode* pAnnotation = this->findCellDesignerAnnotation(this->mpDocument, this->mpDocument->getModel()->getAnnotation());

          if (pAnnotation != NULL)
            {
              this->convertCellDesignerLayout(pAnnotation);
            }
        }
      else
        {
          if (this->mpLayout != NULL)
            {
              if (this->mpDocument && this->mpDocument->getModel())
                {

                  LayoutModelPlugin* lmPlugin = (LayoutModelPlugin*)this->mpDocument->getModel()->getPlugin("layout");

                  if (lmPlugin != NULL)
                    {

                      unsigned int i, iMax = lmPlugin->getListOfLayouts()->size();

                      for (i = 0; i < iMax; ++i)
                        {
                          if (lmPlugin->getLayout(i) == this->mpLayout)
                            {
                              lmPlugin->removeLayout(i);
                              break;
                            }
                        }
                    }
                }

              delete this->mpLayout;
              this->mpLayout = NULL;
            }
        }
    }
}

/**
 * Method to return a const poiner to the SBMLDocument.
 */
const SBMLDocument* CCellDesignerImporter::getSBMLDocument() const
{
  return this->mpDocument;
}

/**
 * Method to return the layout object.
 * Since the laoyut object is owned by the importer,
 * the caller should make a copy of the layout.
 */
const Layout* CCellDesignerImporter::getLayout() const
{
  return this->mpLayout;
}

/**
 * Goes through the SBMLDocument and tries to find a CellDesigner
 * annotation.
 * If one is found, a const pointer to the corresponding XMLNode
 * is returned.
 * If the current SBMLDocument is NULL or if no CellDesigner annotation
 * is found, ULL is returned.
 */
const XMLNode* CCellDesignerImporter::findCellDesignerAnnotation(SBMLDocument* pDocument, const XMLNode* pAnnotation)
{
  const XMLNode* pNode = NULL;

  if (pDocument != NULL && pAnnotation != NULL)
    {
      const Model* pModel = pDocument->getModel();
      std::pair<bool, std::string> celldesigner_ns_found = CCellDesignerImporter::findCellDesignerNamespace(pDocument);

      if (celldesigner_ns_found.first == true && pModel != NULL)
        {
          const XMLNamespaces* pNamespaces = NULL;
          const std::string uri("http://www.sbml.org/2001/ns/celldesigner");
          const XMLNode* pAnnoChild = NULL;

          if (pAnnotation != NULL)
            {
              unsigned int i, iMax = pAnnotation->getNumChildren();

              // we only search until we found the first element that fits
              std::string ns_prefix;

              if (pAnnotation->getNamespaces().hasURI(uri))
                {
                  ns_prefix = pAnnotation->getNamespaces().getPrefix(uri);
                }
              else if (pDocument->getNamespaces()->hasURI(uri))
                {
                  ns_prefix = pDocument->getNamespaces()->getPrefix(uri);
                }

              for (i = 0; i < iMax && pNode == NULL; ++i)
                {
                  pAnnoChild = &pAnnotation->getChild(i);

                  // check if the child has the celldesigner namespace
                  // or if the child has the celldesigner prefix
                  if (pAnnoChild != NULL)
                    {
                      // if the prefix is redefined here, it should take precedence
                      pNamespaces = &pAnnoChild->getNamespaces();

                      if (pNamespaces->hasURI(uri))
                        {
                          ns_prefix = pNamespaces->getPrefix(uri);
                        }

                      if (!ns_prefix.empty() && ns_prefix == pAnnoChild->getPrefix() && pAnnoChild->getName() == "extension")
                        {
                          // we have found the first cell designer annotation
                          // element
                          // check if it really is the top level cell designer anotation
                          pNode = pAnnoChild;
                        }
                    }
                }
            }
        }
    }

  return pNode;
}

/**
 * This method searches for the CellDesigner namespace in the annotation to the model
 * as well as the annotation to the document.
 * The method returns a pair of bool and string. The bool determines if the namespace was
 * found and the string specifies the prefix for the namespace.
 */
std::pair<bool, std::string> CCellDesignerImporter::findCellDesignerNamespace(const SBMLDocument* pDocument)
{
  std::pair<bool, std::string> result(false, "");

  if (pDocument != NULL)
    {
      // first we look for the CellDesigner namespace in the SBMLDocument
      // and in the model and in all children of the models annotation
      const XMLNamespaces* pNamespaces = pDocument->getNamespaces();
      const std::string uri("http://www.sbml.org/2001/ns/celldesigner");
      const Model* pModel = pDocument->getModel();

      if (pNamespaces && pNamespaces->hasURI(uri))
        {
          result.first = true;
          result.second = pNamespaces->getPrefix(uri);
        }
      else
        {
          if (pModel != NULL)
            {
              pNamespaces = pModel->getNamespaces();

              if (pNamespaces != NULL && pNamespaces->hasURI(uri))
                {
                  result.first = true;
                  result.second = pNamespaces->getPrefix(uri);
                }
              else
                {
                  // check the annotation and all its top level children
                  const XMLNode* pAnnotation = const_cast<Model*>(pModel)->getAnnotation();

                  if (pAnnotation != NULL)
                    {
                      pNamespaces = &pAnnotation->getNamespaces();

                      if (pNamespaces != NULL && pNamespaces->hasURI(uri))
                        {
                          result.first = true;
                          result.second = pNamespaces->getPrefix(uri);
                        }
                      else
                        {
                          unsigned int i, iMax = pAnnotation->getNumChildren();
                          const XMLNode* pChild = NULL;

                          for (i = 0; i < iMax; ++i)
                            {
                              pChild = &pAnnotation->getChild(i);
                              assert(pChild != NULL);

                              if (pChild != NULL)
                                {
                                  pNamespaces = &pChild->getNamespaces();

                                  if (pNamespaces != NULL && pNamespaces->hasURI(uri))
                                    {
                                      result.first = true;
                                      result.second = pNamespaces->getPrefix(uri);
                                      break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

  return result;
}

/**
 * This method tries to convert the CellDesigner annotation to an SBML Layout.
 * On success the method will return true and false otherwise.
 */
bool CCellDesignerImporter::convertCellDesignerLayout(const XMLNode* pCellDesignerAnnotation)
{
  bool result = true;

  // before we start, we make sure that all data structures
  // are cleared
  this->mCompartmentAliasMap.clear();
  this->mSpeciesAliasMap.clear();
  this->mColorStringMap.clear();
  this->mIdMap.clear();
  this->mCDIdToLayoutElement.clear();
  this->mCDBounds.clear();
  this->mSpeciesAnnotationMap.clear();
  this->mCompartmentAnnotationMap.clear();
  this->mSpeciesAliases.clear();
  // actually we need to delete all nodes in the list
  std::list<CCopasiNode<std::string>*>::iterator nit = this->mComplexDependencies.begin(), nendit = this->mComplexDependencies.end();

  while (nit != nendit)
    {
      delete *nit;
      ++nit;
    }

  this->mComplexDependencies.clear();
  this->mModelIdToLayoutElement.clear();
  this->mCompartmentNamePointMap.clear();
  this->mProteinInformationMap.clear();
  //this->mGeneNameMap.clear();
  //this->mRNANameMap.clear();
  //this->mASRNANameMap.clear();

  // check if we are in the top level cell designer element
  if (pCellDesignerAnnotation != NULL &&
      pCellDesignerAnnotation->getName() == "extension" &&
      this->mpDocument != NULL &&
      this->mpDocument->getModel() != NULL)
    {
      // we don't need the meta ids
      std::map<std::string, const SBase*> metaids;
      // delete all existing ids
      SBMLUtils::collectIds(this->mpDocument->getModel(), this->mIdMap, metaids);

      LayoutModelPlugin* lmPlugin = (LayoutModelPlugin*)this->mpDocument->getModel()->getPlugin("layout");
      assert(lmPlugin != NULL);
      // create the layout
      this->mpLayout = lmPlugin->createLayout();

      if (this->mpLayout != NULL)
        {
          // we need to find a unique id for the layout
          std::string id = this->createUniqueId("Layout");
          this->mpLayout->setId(id);
          this->mpLayout->setName(id);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(id, this->mpLayout));

          // create the LocalRenderInformation
          RenderLayoutPlugin* rlPlugin = (RenderLayoutPlugin*) this->mpLayout->getPlugin("render");
          this->mpLocalRenderInfo = rlPlugin->createLocalRenderInformation();

          if (this->mpLocalRenderInfo != NULL)
            {
              // set the id of the render information
              // set a name
              // set a program name
              // set the background color to white
              this->mpLocalRenderInfo->setBackgroundColor("#FFFFFFFF");
              this->mpLocalRenderInfo->setName("render info from celldesigner");
              this->mpLocalRenderInfo->setProgramName("CellDesignerImporter");
              this->mpLocalRenderInfo->setProgramVersion("0.0.1");
              std::string render_id = this->createUniqueId("RenderInformation");
              this->mpLocalRenderInfo->setId(id);
              this->mIdMap.insert(std::pair<std::string, const SBase*>(render_id, this->mpLocalRenderInfo));
              // since we use black for the edge of all objects, we create a color definition for that
              std::string color_id = this->createUniqueId("black");
              ColorDefinition* pBlack = this->mpLocalRenderInfo->createColorDefinition();

              if (pBlack != NULL)
                {
                  pBlack->setId(color_id);
                  this->mIdMap.insert(std::pair<std::string, const SBase*>(color_id, pBlack));
                  pBlack->setRGBA(0, 0, 0, 255);
                  this->mColorStringMap.insert(std::pair<std::string, std::string>("#000000FF", color_id));
                }
              else
                {
                  result = false;
                }

              if (result == true)
                {
                  // ReactionGlyphs and SpeciesReferenceGlyphs
                  result = this->createDefaultStyles();
                }
            }

          const XMLNode* pChild = NULL;

          double version = CCellDesignerImporter::determineVersion(pCellDesignerAnnotation);

          if (version < 4.0)
            {
              result = false;
            }


          if (result == true)
            {
              // handle the modelDisplay element
              pChild = CCellDesignerImporter::findChildNode(pCellDesignerAnnotation, pCellDesignerAnnotation->getPrefix(), "modelDisplay", false);
              result = (pChild != NULL && CCellDesignerImporter::parseModelDisplay(pChild, *this->mpLayout->getDimensions()));
            }

          if (result == true)
            {
              pChild = CCellDesignerImporter::findChildNode(pCellDesignerAnnotation, pCellDesignerAnnotation->getPrefix(), "listOfIncludedSpecies", false);

              if (pChild != NULL)
                {
                  result = this->handleIncludedSpecies(pChild);
                }
            }

          if (result == true)
            {
              pChild = CCellDesignerImporter::findChildNode(pCellDesignerAnnotation, pCellDesignerAnnotation->getPrefix(), "listOfCompartmentAliases", false);

              if (pChild != NULL)
                {
                  result = this->createCompartmentGlyphs(pChild);
                }
            }

          if (result == true)
            {
              pChild = CCellDesignerImporter::findChildNode(pCellDesignerAnnotation, pCellDesignerAnnotation->getPrefix(), "listOfSpeciesAliases", false);

              if (pChild != NULL)
                {
                  result = this->createSpeciesGlyphs(pChild);
                }
            }

          if (result == true)
            {
              pChild = CCellDesignerImporter::findChildNode(pCellDesignerAnnotation, pCellDesignerAnnotation->getPrefix(), "listOfComplexSpeciesAliases", false);

              if (pChild != NULL)
                {
                  result = this->createSpeciesGlyphs(pChild);
                }
            }

          /*
          if(result == true)
          {
              pChild=CCellDesignerImporter::findChildNode(pCellDesignerAnnotation,pCellDesignerAnnotation->getPrefix(),"listOfGenes",false);
              result = (pChild!=NULL && this->parseGeneNames(pChild));
          }
          if(result == true)
          {
              pChild=CCellDesignerImporter::findChildNode(pCellDesignerAnnotation,pCellDesignerAnnotation->getPrefix(),"listOfRNAs",false);
              result = (pChild!=NULL && this->parseRNANames(pChild));
          }
          if(result == true)
          {
              pChild=CCellDesignerImporter::findChildNode(pCellDesignerAnnotation,pCellDesignerAnnotation->getPrefix(),"listOfAntisenseRNAs",false);
              result = (pChild!=NULL && this->parseASRNANames(pChild));
          }
          */

          // go through the models reactions and find the cell designer annotations there
          // so that we can create the edges of the graph
          if (result)
            {
              result = this->convertReactionAnnotations();
            }

          // go through the compartment annotations and create the text glyph for the names
          if (result)
            {
              result = this->convertCompartmentAnnotations();
            }

          // go through the species annotations and create the text glyph for the names
          if (result)
            {
              result = this->convertSpeciesAnnotations();
            }

          // now we need to find the correct way of drawing protein nodes
          // for this we need the type on the protein elements
          // this information is used when we create the styles for the species glyphs
          // TODO the code below will only work if we know the mapping from protein reference id
          // TODO to the corresponding species or CellDesigner species id
          // TODO this information is stored in a proteinReference element of either the annotation
          // TODO of the species or directly with the CellDesignerSpecies
          if (result == true)
            {
              pChild = CCellDesignerImporter::findChildNode(pCellDesignerAnnotation, pCellDesignerAnnotation->getPrefix(), "listOfProteins", false);
              result = (pChild != NULL && this->parseProteins(pChild));

              //   // now we go through the protein map and set the correct type
              //   // on the SpeciesAlias for the corresponding species
              //   std::map<std::string,Protein>::const_iterator it=this->mProteinInformationMap.begin(),endit=this->mProteinInformationMap.end();
              //   std::map<std::string,SpeciesAnnotation>::iterator annoIt;
              //   std::cout << "num protein types:" << this->mProteinInformationMap.size() << std::endl;
              //   while(it != endit)
              //   {
              //       std::cout << "looking for annotation to " << it->first << std::endl;
              //       annoIt=this->mSpeciesAnnotationMap.find(it->first);
              //       if(annoIt != this->mSpeciesAnnotationMap.end())
              //       {
              //           annoIt->second.mIdentity.mSpeciesClass=it->second;
              //       }
              //       else
              //       {
              //           result=false;
              //       }
              //       ++it;
              //   }
            }

          // go through all species glyphs and create a style for each one
          if (result)
            {
              result = this->createSpeciesStyles();
            }

        }

      // clean up
      if (!result && this->mpLayout != NULL)
        {
          if (this->mpDocument && this->mpDocument->getModel())
            {
              LayoutModelPlugin* lmPlugin = (LayoutModelPlugin*)this->mpDocument->getModel()->getPlugin("layout");

              if (lmPlugin != NULL)
                {
                  unsigned int i, iMax = lmPlugin->getListOfLayouts()->size();

                  for (i = 0; i < iMax; ++i)
                    {
                      if (lmPlugin->getLayout(i) == this->mpLayout)
                        {
                          lmPlugin->removeLayout(i);
                          break;
                        }
                    }
                }
            }

          delete this->mpLayout;
          this->mpLayout = NULL;
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Creates the compartment glyphs from the given node
 * that represents the listOfCompartmentAliases.
 */
bool CCellDesignerImporter::createCompartmentGlyphs(const XMLNode* pLoCA)
{
  bool result = true;

  if (pLoCA != NULL && pLoCA->getName() == "listOfCompartmentAliases")
    {
      std::string prefix = pLoCA->getPrefix();
      const XMLNode* pChild = NULL;
      unsigned int i, iMax = pLoCA->getNumChildren();

      for (i = 0; i < iMax && result == true; ++i)
        {
          pChild = &pLoCA->getChild(i);

          if (pChild != NULL && pChild->getPrefix() == prefix && pChild->getName() == "compartmentAlias")
            {
              CompartmentAlias ca;
              result = CCellDesignerImporter::parseCompartmentAlias(pChild, ca, *this->mpLayout->getDimensions());

              if (result == true)
                {
                  result = this->createCompartmentGlyph(ca);
                }
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Creates the species glyphs from the given node
 * that represents the listOfSpeciesAliases.
 */
bool CCellDesignerImporter::createSpeciesGlyphs(const XMLNode* pLoSA)
{
  bool result = true;

  if (pLoSA != NULL && (pLoSA->getName() == "listOfSpeciesAliases" || pLoSA->getName() == "listOfComplexSpeciesAliases"))
    {
      std::string prefix = pLoSA->getPrefix();
      const XMLNode* pChild = NULL;
      unsigned int i, iMax = pLoSA->getNumChildren();

      for (i = 0; i < iMax && result == true; ++i)
        {
          pChild = &pLoSA->getChild(i);

          if (pChild != NULL &&
              pChild->getPrefix() == prefix &&
              (pChild->getName() == "speciesAlias" || pChild->getName() == "complexSpeciesAlias"))
            {
              SpeciesAlias sa;
              result = CCellDesignerImporter::parseSpeciesAlias(pChild, sa);

              if (result == true)
                {
                  result = this->createSpeciesGlyph(sa);
                }
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Creates the compartment glyph from the given
 * compartmentAliase structure.
 */
bool CCellDesignerImporter::createCompartmentGlyph(const CompartmentAlias& ca)
{
  bool result = true;

  if (!ca.mId.empty())
    {
      CompartmentGlyph* pCGlyph = this->mpLayout->createCompartmentGlyph();

      if (pCGlyph != NULL)
        {
          this->mCDIdToLayoutElement.insert(std::pair<std::string, GraphicalObject*>(ca.mId, pCGlyph));
          // create a unique id
          std::string id = this->createUniqueId("CompartmentGlyph");
          pCGlyph->setId(id);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pCGlyph));

          // set the corresponding compartment
          // check if a compartment with that id actually exists before making the link
          if (!ca.mCompartment.empty() &&
              this->mpDocument != NULL &&
              this->mpDocument->getModel() != NULL &&
              this->mpDocument->getModel()->getCompartment(ca.mCompartment) != NULL)
            {
              pCGlyph->setCompartmentId(ca.mCompartment);
              this->mModelIdToLayoutElement.insert(std::pair<std::string, GraphicalObject*>(ca.mCompartment, pCGlyph));
              assert(pCGlyph->getBoundingBox() != NULL);
              pCGlyph->setBoundingBox(&ca.mBounds);
              this->mCompartmentNamePointMap.insert(std::pair<const CompartmentGlyph*, Point>(pCGlyph, ca.mNamePoint));
            }

          // create a style for the compartment glyph
          result = this->createCompartmentStyle(ca, pCGlyph);

          if (result == true)
            {
              // store the compartment alias
              this->mCompartmentAliasMap.insert(std::pair<const CompartmentGlyph*, CompartmentAlias>(pCGlyph, ca));
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Creates the species glyph from the given
 * SpeciesAliases structure.
 */
bool CCellDesignerImporter::createSpeciesGlyph(const SpeciesAlias& sa)
{
  bool result = true;
  // the speciesAlias node should
  // have a bounds element with x,y,w and h
  // attributes
  SpeciesGlyph* pSGlyph = NULL;

  if (!sa.mId.empty())
    {
      if (sa.mComplexSpeciesAlias.empty())
        {
          pSGlyph = this->mpLayout->createSpeciesGlyph();

          if (pSGlyph != NULL)
            {
              // create unique id
              std::string id = this->createUniqueId("SpeciesGlyph");
              pSGlyph->setId(id);
              this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSGlyph));
              // set the bounds on the species glyph
              pSGlyph->setBoundingBox(&sa.mBounds);
              this->mCDIdToLayoutElement.insert(std::pair<std::string, GraphicalObject*>(sa.mId, pSGlyph));
              // add the data to mCDBounds
              this->mCDBounds.insert(std::pair<std::string, BoundingBox>(sa.mId, *pSGlyph->getBoundingBox()));

              // check if a compartment with that id actually exists before making the link
              if (!sa.mSpecies.empty() &&
                  this->mpDocument != NULL &&
                  this->mpDocument->getModel() != NULL &&
                  this->mpDocument->getModel()->getSpecies(sa.mSpecies) != NULL)
                {
                  pSGlyph->setSpeciesId(sa.mSpecies);
                  this->mModelIdToLayoutElement.insert(std::pair<std::string, GraphicalObject*>(sa.mSpecies, pSGlyph));
                }

              if (result == true)
                {
                  // store the species alias
                  this->mSpeciesAliasMap.insert(std::pair<const SpeciesGlyph*, SpeciesAlias>(pSGlyph, sa));
                  this->mSpeciesAliases.insert(std::pair<std::string, SpeciesAlias>(sa.mId, sa));
                }

              // create a style for the object
              //result=this->createSpeciesStyle(sa,pSGlyph->getId());
            }
          else
            {
              result = false;
            }
        }
      else
        {
          this->addDependency(sa.mComplexSpeciesAlias, sa.mId);
          // we need to parse the bounding box and store the information for it in
          // mCDBounds
          this->mCDBounds.insert(std::pair<std::string, BoundingBox>(sa.mId, sa.mBounds));
          this->mSpeciesAliases.insert(std::pair<std::string, SpeciesAlias>(sa.mId, sa));
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Creates styles for all species glyphs.
 */
bool CCellDesignerImporter::createSpeciesStyles()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      // we go through the top level species which we can get from the dependency tree
      // for each glyph we create a primitive depending on the class of the alias
      // for the first implementation, all classes will be represented as boxes
      // then we will recurse into the dependency tree and create primitives for the
      // children
      std::map<const SpeciesGlyph*, SpeciesAlias>::const_iterator glyphs_it = this->mSpeciesAliasMap.begin(), glyphs_endit = this->mSpeciesAliasMap.end();
      std::list<CCopasiNode<std::string>*>::const_iterator dependency_it, dependency_endit;

      while (glyphs_it != glyphs_endit)
        {
          std::map<std::string, SpeciesAnnotation>::const_iterator anno_pos = this->mSpeciesAnnotationMap.find(glyphs_it->second.mSpecies);

          if (anno_pos != this->mSpeciesAnnotationMap.end() && glyphs_it->first != NULL && glyphs_it->second.mComplexSpeciesAlias.empty())
            {
              // find the alias in the dependency map.
              dependency_it = this->mComplexDependencies.begin();
              dependency_endit = this->mComplexDependencies.end();

              while (dependency_it != dependency_endit)
                {
                  if ((*dependency_it)->getData() == glyphs_it->second.mId)
                    {
                      break;
                    }

                  ++dependency_it;
                }

              if (dependency_it != dependency_endit)
                {
                  // If we find it, we create a primitive and a text glyph
                  // and we create a style that contains all the children
                  const CCopasiNode<std::string>* pCurrent = *dependency_it;
                  assert(pCurrent != NULL);
                  std::string alias;
                  std::map<std::string, SpeciesAlias>::const_iterator alias_pos;
                  // create a style
                  std::string style_id = this->createUniqueId("ComplexSpeciesGlyphStyle");
                  LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

                  if (pStyle != NULL)
                    {
                      pStyle->setId(style_id);
                      this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
                      // apply the style to the glyph
                      pStyle->addId(glyphs_it->first->getId());
                      RenderGroup* pGroup = pStyle->getGroup();
                      assert(pGroup != NULL);
                      // since children of aliases should stay within the bounds of their
                      // parents, we add all children to the same group and assume
                      // that no overlap will occur
                      // this also allows us to traverse the tree depth first
                      // instead of level for level

                      // all primitives we create should be relative to the glyphs bounding box
                      // sine the CellDesigner annotation contains absolute values for
                      // all coordinates, we need to subtract the species glyphs position
                      Point offset(new LayoutPkgNamespaces(), -glyphs_it->first->getBoundingBox()->getPosition()->x(), -glyphs_it->first->getBoundingBox()->getPosition()->y());

                      while (pCurrent != NULL)
                        {
                          alias = pCurrent->getData();
                          assert(!alias.empty());
                          // find the corresponding SpeciesAlias entry
                          alias_pos = this->mSpeciesAliases.find(alias);
                          assert(alias_pos != this->mSpeciesAliases.end());
                          bool is_included = false;
                          std::map<std::string, std::pair<std::string, SpeciesIdentity> >::const_iterator nameMapPos;

                          if (alias_pos != this->mSpeciesAliases.end())
                            {
                              SpeciesAlias sa = alias_pos->second;

                              // find the corresponding SpeciesAnnotation
                              if (!sa.mSpecies.empty())
                                {
                                  // create the primitive
                                  std::string color_id;
                                  result = this->findOrCreateColorDefinition(sa.mUView.mPaint.mColor, color_id);
                                  // if we are not on the root node, we need to add a text
                                  // element as well
                                  std::string text;

                                  if (result == true && pCurrent != *dependency_it)
                                    {
                                      // find and add text
                                      const Species* pSpecies = this->mpDocument->getModel()->getSpecies(sa.mSpecies);

                                      if (pSpecies == NULL)
                                        {
                                          // it is a CellDesignerSpecies
                                          nameMapPos = this->mIncludedSpeciesNameMap.find(sa.mSpecies);
                                          assert(nameMapPos != this->mIncludedSpeciesNameMap.end());

                                          if (nameMapPos != this->mIncludedSpeciesNameMap.end())
                                            {
                                              text = nameMapPos->second.first;
                                              is_included = true;
                                            }
                                        }
                                      else
                                        {
                                          text = pSpecies->getName();
                                        }
                                    }

                                  if (result == true)
                                    {
                                      if (is_included)
                                        {
                                          // the identity should be stored in the mIncludedSpeciesNameMap
                                          result = CCellDesignerImporter::createPrimitive(pGroup, nameMapPos->second.second, alias_pos->second.mBounds, offset, 1.0, "#000000", color_id, text);
                                        }
                                      else
                                        {
                                          // the identity should be stored in the SpeciesAnnotationMap
                                          // The mSpeciesAnnotationMap uses the id of an SBML species as the key
                                          anno_pos = this->mSpeciesAnnotationMap.find(sa.mSpecies);
                                          assert(anno_pos != this->mSpeciesAnnotationMap.end());

                                          if (anno_pos != this->mSpeciesAnnotationMap.end())
                                            {
                                              result = CCellDesignerImporter::createPrimitive(pGroup, anno_pos->second.mIdentity, alias_pos->second.mBounds, offset, 1.0, "#000000", color_id, text);
                                            }
                                          else
                                            {
                                              result = false;
                                            }
                                        }
                                    }

                                  // TODO gradients are currently not considered

                                }
                              else
                                {
                                  result = false;
                                }
                            }
                          else
                            {
                              result = false;
                            }

                          pCurrent = pCurrent->getNext();
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  // if it is not a root element in there, and if it
                  // does not have the mComplexSpeciesSpeciesAlias attribute set
                  // we assume it is a top level species and create a primitive
                  std::string style_id = this->createUniqueId("SpeciesGlyphStyle");
                  LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);
                  assert(pStyle != NULL);

                  if (pStyle != NULL)
                    {
                      pStyle->setId(style_id);
                      // apply it to the glyph
                      pStyle->addId(glyphs_it->first->getId());
                      this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));

                      // find the identity for the species alias
                      if (!glyphs_it->second.mSpecies.empty())
                        {
                          std::map<std::string, SpeciesAnnotation>::const_iterator anno_pos = this->mSpeciesAnnotationMap.find(glyphs_it->second.mSpecies);

                          if (anno_pos != this->mSpeciesAnnotationMap.end())
                            {
                              assert(pStyle->getGroup() != NULL);

                              if (pStyle->getGroup() != NULL)
                                {
                                  // all positions within the style should be relative
                                  // to the glyphs bounding box, so we need to subtract
                                  // the position of the glyphs bounding box from
                                  // all coordinates in the style
                                  std::string color_id;
                                  result = this->findOrCreateColorDefinition(glyphs_it->second.mUView.mPaint.mColor, color_id);

                                  if (result == true)
                                    {
                                      result = CCellDesignerImporter::createPrimitive(pStyle->getGroup(), anno_pos->second.mIdentity, glyphs_it->second.mBounds, Point(new LayoutPkgNamespaces(), -glyphs_it->first->getBoundingBox()->getPosition()->x(), -glyphs_it->first->getBoundingBox()->getPosition()->y()), 1.0, "#000000", color_id);
                                    }

                                  // TODO gradients are currently not considered
                                }
                              else
                                {
                                  result = false;
                                }
                            }
                          else
                            {
                              result = false;
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
            }

          ++glyphs_it;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Create a primitive that corresponds to the given class
 * The promitive is created in the given group object.
 * The complete primitive is translated by the given offset.
 *
 * If creation of the primitive fails, false is returned.
 *
 */
bool CCellDesignerImporter::createPrimitive(RenderGroup* pGroup,
    const SpeciesIdentity& si,
    const BoundingBox& bounds,
    const Point& offset,
    double stroke_width,
    const std::string& stroke_color,
    const std::string& fill_color,
    const std::string& text
                                           )
{
  bool result = true;

  // maybe we should rule out all the SQUARE classes and the OVAL class
  // since they are probably only used for compartments
  // On the other hand, maybe we can use this method to create the primitives
  // for the compartments as well
  if (pGroup != NULL &&
      si.mSpeciesClass != UNDEFINED_CLASS
     )
    {
      // if it is a protein, find the specific type
      SPECIES_CLASS cl = UNDEFINED_CLASS;

      if (si.mSpeciesClass == PROTEIN_CLASS && !si.mNameOrReference.empty())
        {
          std::map<std::string, Protein>::const_iterator pos = this->mProteinInformationMap.find(si.mNameOrReference);

          if (pos != this->mProteinInformationMap.end())
            {
              cl = pos->second.mType;
            }
        }
      else
        {
          cl = si.mSpeciesClass;
        }

      switch (cl)
        {
          case ION_CLASS:
          {
            double width = bounds.getDimensions()->getWidth();
            double height = bounds.getDimensions()->getHeight();
            double shortside = (width < height) ? width : height;
            Ellipse* pEllipse = pGroup->createEllipse();
            assert(pEllipse != NULL);

            if (pEllipse != NULL)
              {
                pEllipse->setCX(RelAbsVector(offset.x() + bounds.getPosition()->x() + width*0.5, 0.0));
                pEllipse->setCY(RelAbsVector(offset.y() + bounds.getPosition()->y() + height*0.5, 0.0));
                pEllipse->setRX(RelAbsVector(shortside*0.5, 0.0));
                pEllipse->setRY(RelAbsVector(shortside*0.5, 0.0));
                pEllipse->setStrokeWidth(stroke_width);
                pEllipse->setStroke(stroke_color);
                pEllipse->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }
          }
          break;
          case UNKNOWN_CLASS:
            // unknown has no edge
          {
            Ellipse* pEllipse = pGroup->createEllipse();
            assert(pEllipse != NULL);

            if (pEllipse != NULL)
              {
                double width = bounds.getDimensions()->getWidth();
                double height = bounds.getDimensions()->getHeight();
                pEllipse->setCX(RelAbsVector(offset.x() + bounds.getPosition()->x() + width*0.5, 0.0));
                pEllipse->setCY(RelAbsVector(offset.y() + bounds.getPosition()->y() + height*0.5, 0.0));
                pEllipse->setRX(RelAbsVector(bounds.getDimensions()->getWidth()*0.5, 0.0));
                pEllipse->setRY(RelAbsVector(bounds.getDimensions()->getHeight()*0.5, 0.0));
                pEllipse->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }
          }
          break;
        case DRUG_CLASS:
            // actually drug is a rectangle with rounded sides
          {
            // create two circles with radius height/2 at 10%,50% and 90%,50%
            // both have a fill and a black edge with stroke width 1
            double width = bounds.getDimensions()->getWidth();
            double height = bounds.getDimensions()->getHeight();

            // outer rectangle
            Rectangle* pRectangle = pGroup->createRectangle();
            assert(pRectangle != NULL);

            if (pRectangle != NULL)
              {
                pRectangle->setX(RelAbsVector(offset.x() + bounds.getPosition()->x(), 0.0));
                pRectangle->setY(RelAbsVector(offset.y() + bounds.getPosition()->y(), 0.0));
                pRectangle->setRadiusX(RelAbsVector(height*0.5, 0.0));
                pRectangle->setRadiusY(RelAbsVector(height*0.5, 0.0));
                pRectangle->setWidth(RelAbsVector(width, 0.0));
                pRectangle->setHeight(RelAbsVector(height, 0.0));

                pRectangle->setStrokeWidth(stroke_width);
                pRectangle->setStroke(stroke_color);
                pRectangle->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }

            // inner rectangle
            pRectangle = pGroup->createRectangle();
            assert(pRectangle != NULL);

            if (pRectangle != NULL)
              {
                pRectangle->setX(RelAbsVector(offset.x() + bounds.getPosition()->x() + 5, 0.0));
                pRectangle->setY(RelAbsVector(offset.y() + bounds.getPosition()->y() + 5, 0.0));
                pRectangle->setRadiusX(RelAbsVector(height*0.5 - 5, 0.0));
                pRectangle->setRadiusY(RelAbsVector(height*0.5 - 5, 0.0));
                pRectangle->setWidth(RelAbsVector(width - 10, 0.0));
                pRectangle->setHeight(RelAbsVector(height - 10, 0.0));

                pRectangle->setStrokeWidth(stroke_width);
                pRectangle->setStroke(stroke_color);
                pRectangle->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }
          }
          break;
        case SIMPLE_MOLECULE_CLASS:
          {
            Ellipse* pEllipse = pGroup->createEllipse();
            assert(pEllipse != NULL);

            if (pEllipse != NULL)
              {
                double width = bounds.getDimensions()->getWidth();
                double height = bounds.getDimensions()->getHeight();
                pEllipse->setCX(RelAbsVector(offset.x() + bounds.getPosition()->x() + width*0.5, 0.0));
                pEllipse->setCY(RelAbsVector(offset.y() + bounds.getPosition()->y() + height*0.5, 0.0));
                pEllipse->setRX(RelAbsVector(bounds.getDimensions()->getWidth()*0.5, 0.0));
                pEllipse->setRY(RelAbsVector(bounds.getDimensions()->getHeight()*0.5, 0.0));
                pEllipse->setStrokeWidth(stroke_width);
                pEllipse->setStroke(stroke_color);
                pEllipse->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }
          }
          break;
        case DEGRADED_CLASS:
          {
            Ellipse* pEllipse = pGroup->createEllipse();
            assert(pEllipse != NULL);

            if (pEllipse != NULL)
              {
                double width = bounds.getDimensions()->getWidth();
                double height = bounds.getDimensions()->getHeight();
                pEllipse->setCX(RelAbsVector(offset.x() + bounds.getPosition()->x() + width*0.5, 0.0));
                pEllipse->setCY(RelAbsVector(offset.y() + bounds.getPosition()->y() + height*0.5, 0.0));
                double short_side = (width > height) ? height : width;
                pEllipse->setRX(RelAbsVector(short_side*0.35, 0.0));
                pEllipse->setRY(RelAbsVector(short_side*0.35, 0.0));
                pEllipse->setStrokeWidth(stroke_width);
                pEllipse->setStroke(stroke_color);
                pEllipse->setFillColor(fill_color);
                RenderCurve* pCurve = pGroup->createCurve();
                assert(pCurve != NULL);

                if (pCurve != NULL)
                  {
                    pCurve->setStrokeWidth(2.0);
                    pCurve->setStroke("#000000FF");
                    RenderPoint* pP = pCurve->createPoint();
                    assert(pP != NULL);

                    if (pP != NULL)
                      {
                        pP->setX((short_side - width)*0.5);
                        pP->setY((short_side - height)*0.5 + short_side);
                        pP = pCurve->createPoint();
                        assert(pP != NULL);

                        if (pP != NULL)
                          {
                            pP->setX((short_side - width)*0.5 + short_side);
                            pP->setY((short_side - height)*0.5);
                          }
                        else
                          {
                            result = false;
                          }
                      }
                    else
                      {
                        result = false;
                      }
                  }
                else
                  {
                    result = false;
                  }
              }
            else
              {
                result = false;
              }
          }
          break;
        case TRUNCATED_CLASS:
          {
            // TODO the left corners should be rounded, but for now this is close enough
            double width = bounds.getDimensions()->getWidth();
            double height = bounds.getDimensions()->getHeight();
            // we take a fixed radius for the rounded corners
            double radius = 10.0;
            Polygon* pPoly = pGroup->createPolygon();
            assert(pPoly != NULL);

            if (pPoly != NULL)
              {
                pPoly->setStrokeWidth(stroke_width);
                pPoly->setStroke(stroke_color);
                pPoly->setFillColor(fill_color);
                RenderPoint* pP = pPoly->createPoint();
                RenderCubicBezier* pCB = NULL;

                if (pP != NULL)
                  {
                    pP->setX(RelAbsVector(radius, 0.0));
                    pP->setY(RelAbsVector(0.0, 0.0));
                  }
                else
                  {
                    result = false;
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(width, 0.0));
                        pP->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(width, 0.0));
                        pP->setY(RelAbsVector(0.8*height, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.8*width, 0.0));
                        pP->setY(RelAbsVector(0.5*height, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.8*width, 0.0));
                        pP->setY(RelAbsVector(height, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(radius, 0.0));
                        pP->setY(RelAbsVector(height, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pCB = pPoly->createCubicBezier();

                    if (pCB != NULL)
                      {
                        pCB->setBasePoint1_X(RelAbsVector(0.0, 0.0));
                        pCB->setBasePoint1_Y(RelAbsVector(height, 0.0));
                        pCB->setBasePoint2_X(RelAbsVector(0.0, 0.0));
                        pCB->setBasePoint2_Y(RelAbsVector(height, 0.0));
                        pCB->setX(RelAbsVector(0.0, 0.0));
                        pCB->setY(RelAbsVector(height - radius, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 0.0));
                        pP->setY(RelAbsVector(radius, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pCB = pPoly->createCubicBezier();

                    if (pCB != NULL)
                      {
                        pCB->setBasePoint1_X(RelAbsVector(0.0, 0.0));
                        pCB->setBasePoint1_Y(RelAbsVector(0.0, 0.0));
                        pCB->setBasePoint2_X(RelAbsVector(0.0, 0.0));
                        pCB->setBasePoint2_Y(RelAbsVector(0.0, 0.0));
                        pCB->setX(RelAbsVector(radius, 0.0));
                        pCB->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }
              }
            else
              {
                result = false;
              }
          }
          break;
        case PROTEIN_CLASS:
            // make a rectangle with rounded edges
          {
            Rectangle* pRect = pGroup->createRectangle();
            assert(pRect != NULL);

            if (pRect != NULL)
              {
                pRect->setX(RelAbsVector(offset.x() + bounds.getPosition()->x(), 0.0));
                pRect->setY(RelAbsVector(offset.y() + bounds.getPosition()->y(), 0.0));
                pRect->setRadiusX(RelAbsVector(0.0, 10.0));
                pRect->setRadiusY(RelAbsVector(0.0, 10.0));
                pRect->setWidth(RelAbsVector(bounds.getDimensions()->getWidth(), 0.0));
                pRect->setHeight(RelAbsVector(bounds.getDimensions()->getHeight(), 0.0));
                pRect->setStrokeWidth(stroke_width);
                pRect->setStroke(stroke_color);
                pRect->setFillColor(fill_color);
              }

            else
              {
                result = false;
              }
            if(result == true)
              {
                // handle modifications
                std::vector<SpeciesModification>::const_iterator it=si.mState.mModifications.begin(),endit=si.mState.mModifications.end();
                while(it != endit)
                {
                    result=this->createProteinModification(pGroup,*it,bounds,stroke_color);
                    assert(result==true);
                    ++it;
                }
              }
          }
          break;
        case PHENOTYPE_CLASS:
          {
            // we assume the width is larger
            Polygon* pPoly = pGroup->createPolygon();
            assert(pPoly != NULL);

            if (pPoly != NULL)
              {
                pPoly->setStrokeWidth(stroke_width);
                pPoly->setStroke(stroke_color);
                pPoly->setFillColor(fill_color);
                RenderPoint* pP = pPoly->createPoint();

                if (pP != NULL)
                  {
                    pP->setY(RelAbsVector(0.0, 0.0));
                    pP->setY(RelAbsVector(0.0, 50.0));
                  }
                else
                  {
                    result = false;
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 15.0));
                        pP->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 85.0));
                        pP->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0));
                        pP->setY(RelAbsVector(0.0, 50.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 85.0));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 15.0));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }
              }
            else
              {
                result = false;
              }
          }
          break;
        case RNA_CLASS:
            // make a trapezoid
          {
            // we assume the width is larger
            Polygon* pPoly = pGroup->createPolygon();
            assert(pPoly != NULL);

            if (pPoly != NULL)
              {
                pPoly->setStrokeWidth(stroke_width);
                pPoly->setStroke(stroke_color);
                pPoly->setFillColor(fill_color);
                RenderPoint* pP = pPoly->createPoint();

                if (pP != NULL)
                  {
                    pP->setX(RelAbsVector(0.0, 20.0));
                    pP->setY(RelAbsVector(0.0, 0.0));
                  }
                else
                  {
                    result = false;
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0));
                        pP->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 80.0));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 0.0));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }
              }
            else
              {
                result = false;
              }
          }
          break;
        case ANTISENSE_RNA_CLASS:
            // make a trapzoid
          {
            // we assume the width is larger
            Polygon* pPoly = pGroup->createPolygon();
            assert(pPoly != NULL);

            if (pPoly != NULL)
              {
                pPoly->setStrokeWidth(stroke_width);
                pPoly->setStroke(stroke_color);
                pPoly->setFillColor(fill_color);
                RenderPoint* pP = pPoly->createPoint();

                if (pP != NULL)
                  {
                    pP->setY(RelAbsVector(0.0, 0.0));
                    pP->setY(RelAbsVector(0.0, 0.0));
                  }
                else
                  {
                    result = false;
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 80.0));
                        pP->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 20.0));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }
              }
            else
              {
                result = false;
              }
          }
          break;
        case COMPLEX_CLASS:
            // rectangle with cut edges
          {
            double width = bounds.getDimensions()->getWidth();
            double height = bounds.getDimensions()->getHeight();
            // we assume the width is larger
            double ratio = height / width;
            Polygon* pPoly = pGroup->createPolygon();
            assert(pPoly != NULL);

            if (pPoly != NULL)
              {
                pPoly->setStrokeWidth(stroke_width);
                pPoly->setStroke(stroke_color);
                pPoly->setFillColor(fill_color);
                RenderPoint* pP = pPoly->createPoint();

                if (pP != NULL)
                  {
                    pP->setX(RelAbsVector(0.0, 10.0*ratio));
                    pP->setY(RelAbsVector(0.0, 0.0));
                  }
                else
                  {
                    result = false;
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0 - 10.0*ratio));
                        pP->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0));
                        pP->setY(RelAbsVector(0.0, 10.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0));
                        pP->setY(RelAbsVector(0.0, 90.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0 - 10.0*ratio));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 10.0*ratio));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 0.0));
                        pP->setY(RelAbsVector(0.0, 90.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 0.0));
                        pP->setY(RelAbsVector(0.0, 10.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }
              }
            else
              {
                result = false;
              }
          }
          break;
        case RECEPTOR_CLASS:
          {
            // we assume the width is larger
            Polygon* pPoly = pGroup->createPolygon();
            assert(pPoly != NULL);

            if (pPoly != NULL)
              {
                pPoly->setStrokeWidth(stroke_width);
                pPoly->setStroke(stroke_color);
                pPoly->setFillColor(fill_color);
                RenderPoint* pP = pPoly->createPoint();

                if (pP != NULL)
                  {
                    pP->setY(RelAbsVector(0.0, 0.0));
                    pP->setY(RelAbsVector(0.0, 0.0));
                  }
                else
                  {
                    result = false;
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 50.0));
                        pP->setY(RelAbsVector(0.0, 15.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0));
                        pP->setY(RelAbsVector(0.0, 0.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 100.0));
                        pP->setY(RelAbsVector(0.0, 85.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 50.0));
                        pP->setY(RelAbsVector(0.0, 100.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }

                if (result == true)
                  {
                    pP = pPoly->createPoint();

                    if (pP != NULL)
                      {
                        pP->setX(RelAbsVector(0.0, 0.0));
                        pP->setY(RelAbsVector(0.0, 85.0));
                      }
                    else
                      {
                        result = false;
                      }
                  }
              }
            else
              {
                result = false;
              }
          }
          break;
        case CHANNEL_CLASS:
            // make two rectangles with rounded corners
          {
            double width = bounds.getDimensions()->getWidth();
            double height = bounds.getDimensions()->getHeight();
            Rectangle* pRect = pGroup->createRectangle();
            assert(pRect != NULL);

            if (pRect != NULL)
              {
                pRect->setX(RelAbsVector(offset.x() + bounds.getPosition()->x(), 0.0));
                pRect->setY(RelAbsVector(offset.y() + bounds.getPosition()->y(), 0.0));
                pRect->setRadiusX(RelAbsVector(6.0, 0.0));
                pRect->setRadiusY(RelAbsVector(6.0, 0.0));
                pRect->setWidth(RelAbsVector(width*0.75, 0.0));
                pRect->setHeight(RelAbsVector(height, 0.0));
                pRect->setStrokeWidth(stroke_width);
                pRect->setStroke(stroke_color);
                pRect->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }

            pRect = pGroup->createRectangle();
            assert(pRect != NULL);

            if (pRect != NULL)
              {
                pRect->setX(RelAbsVector(offset.x() + bounds.getPosition()->x() + width * 0.75, 0.0));
                pRect->setY(RelAbsVector(offset.y() + bounds.getPosition()->y(), 0.0));
                pRect->setWidth(RelAbsVector(width*0.25, 0.0));
                pRect->setHeight(RelAbsVector(height, 0.0));
                pRect->setRadiusX(RelAbsVector(6.0, 0.0));
                pRect->setRadiusY(RelAbsVector(6.0, 0.0));
                pRect->setStrokeWidth(stroke_width);
                pRect->setStroke(stroke_color);
                pRect->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }
          }
          break;
        case GENE_CLASS:
          {
            Rectangle* pRect = pGroup->createRectangle();
            assert(pRect != NULL);

            if (pRect != NULL)
              {
                pRect->setX(RelAbsVector(offset.x() + bounds.getPosition()->x(), 0.0));
                pRect->setY(RelAbsVector(offset.y() + bounds.getPosition()->y(), 0.0));
                pRect->setWidth(RelAbsVector(bounds.getDimensions()->getWidth(), 0.0));
                pRect->setHeight(RelAbsVector(bounds.getDimensions()->getHeight(), 0.0));
                pRect->setStrokeWidth(stroke_width);
                pRect->setStroke(stroke_color);
                pRect->setFillColor(fill_color);
              }
            else
              {
                result = false;
              }
          }
          break;
        default:
            result = false;
            break;
        }

      // create the text element
      if (result == true && !text.empty())
        {
          // place a text element in the box
          // specified by bounds
          Text* pText = pGroup->createText();
          assert(pText != NULL);

          if (pText != NULL)
            {
              pText->setTextAnchor(Text::ANCHOR_MIDDLE);
              pText->setVTextAnchor(Text::ANCHOR_MIDDLE);
              // middle of the box
              pText->setX(RelAbsVector(bounds.getPosition()->x() + offset.x() + 0.5*bounds.getDimensions()->getWidth(), 0.0));
              // middle of the box
              pText->setY(RelAbsVector(bounds.getPosition()->y() + offset.y() + 0.5*bounds.getDimensions()->getHeight(), 0.0));
              pText->setText(text);
              // TODO we need the font size and the font family
              // TODO for now we use a default
              pText->setFontFamily("serif");
              pText->setFontSize(RelAbsVector(10.0, 0.0));
              pText->setStroke("#000000");
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Takes a protein modification description and creates the corresponding primitive.
 */
bool CCellDesignerImporter::createProteinModification(RenderGroup* pGroup,
                                                     const SpeciesModification& smod,
                                                     const BoundingBox& bounds,
                                                     const std::string& stroke_color
                                                    )
{
   // TODO this method will place all modification in exactly the same spot, so 
   // TODO if a protein has several modifications, they will sit on top of each other
   // TODO One would have to play around with CellDesigner to see how it is done there
   // TODO because there does not seem to be any stored information on where the
   // TODO modification symbol is supposed to be placed 
   bool result=true;
   // this is a filled circle
   // the fill color is white
   Ellipse* pEllipse=pGroup->createEllipse();
   assert(pEllipse != NULL);
   if(pEllipse != NULL)
   {
       pEllipse->setCX(RelAbsVector(0.0, 0.0));
       pEllipse->setCY(RelAbsVector(0.0, 0.0));
       pEllipse->setRX(RelAbsVector(7.0, 0.0));
       pEllipse->setRY(RelAbsVector(7.0, 0.0));
       pEllipse->setStrokeWidth(1.0);
       pEllipse->setStroke(stroke_color);
       pEllipse->setFillColor("#FFFFFFFF");
       // depending on the type of modification, the string displayed in the circle varies
       std::string mod_string("");
       switch(smod.mType)
       {
           case PHOSPHORYLATED_MOD_TYPE:
               mod_string="P";
               break;
           case ACETYLATED_MOD_TYPE:
               mod_string="Ac";
               break;
           case UBIQUITINATED_MOD_TYPE:
               mod_string="Ub";
               break;
           case METHYLATED_MOD_TYPE:
               mod_string="Me";
               break;
           case HYDROXYLATED_MOD_TYPE:
               mod_string="OH";
               break;
           case DONTCARE_MOD_TYPE:
               mod_string="*";
               break;
           case UNKNOWN_MOD_TYPE:
               mod_string="?";
               break;
           case GLYCOSYLATED_MOD_TYPE:
               mod_string="G";
               break;
           case MYRISTOYLATED_MOD_TYPE:
               mod_string="My";
               break;
           case PALMYTOYLATED_MOD_TYPE:
               mod_string="Pa";
               break;
           case PRENYLATED_MOD_TYPE:
               mod_string="Pr";
               break;
           case PROTONATED_MOD_TYPE:
               mod_string="H";
               break;
           case SUFLATED_MOD_TYPE:
               mod_string="S";
               break;
           default:
               break;
       }
       Text* pText=pGroup->createText();
       pText->setTextAnchor(Text::ANCHOR_MIDDLE);
       pText->setVTextAnchor(Text::ANCHOR_MIDDLE);
       pText->setX(RelAbsVector(0.0,0.0));
       pText->setY(RelAbsVector(0.0,0.0));
       pText->setText(mod_string);
       pText->setFontFamily("serif");
       pText->setFontSize(RelAbsVector(8.0, 0.0));
       pText->setStroke("#000000FF");
   }
   else
   {
     result=false;
   }
   return result;
}

 

/**
 * Creates a unique id with the given prefix.
 */
std::string CCellDesignerImporter::createUniqueId(const std::string& prefix)
{
  static std::ostringstream os;
  unsigned int index = 1;
  std::string id = prefix;

  while (this->mIdMap.find(id) != this->mIdMap.end())
    {
      os.str("");
      os << prefix;
      os << "_";
      os << index;
      id = os.str();
      ++index;
    }

  return id;
}

/**
 * Traverses the reactions of the model and looks for CellDesigner annotations.
 * These are used to create reaction glyphs.
 */
bool CCellDesignerImporter::convertReactionAnnotations()
{
  bool result = true;

  if (this->mpDocument != NULL)
    {
      Model* pModel = this->mpDocument->getModel();

      if (pModel != NULL)
        {
          unsigned int i, iMax = pModel->getNumReactions();

          for (i = 0; i < iMax && result == true; ++i)
            {
              result = this->convertReactionAnnotation(pModel->getReaction(i), pModel);
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Looks for CellDesigner annotation in the given reaction and ries to convert
 * the information in that annotation into a ReactionGlyph.
 */
bool CCellDesignerImporter::convertReactionAnnotation(Reaction* pReaction, const Model* pModel)
{
  bool result = true;

  if (pReaction != NULL && pModel != NULL && pReaction->getAnnotation() != NULL)
    {
      const XMLNode* pAnnotation = this->findCellDesignerAnnotation(this->mpDocument, pReaction->getAnnotation());

      if (pAnnotation != NULL && pAnnotation->getName() == "extension" && this->mpLayout != NULL)
        {
          // create a reaction glyph
          ReactionAnnotation ranno;
          result = this->parseReactionAnnotation(pAnnotation, ranno);

          if (result == true)
            {
              ReactionGlyph* pRGlyph = this->mpLayout->createReactionGlyph();

              if (pRGlyph != NULL)
                {
                  std::string id = this->createUniqueId("ReactionGlyph");
                  pRGlyph->setId(id);
                  pRGlyph->setReactionId(pReaction->getId());
                  this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pRGlyph));
                  // the reactionType element has a text element
                  // that defines the type of reaction

                  // the following reaction types have one reactant and one product
                  // STATE_TRANSITION, KNOWN_TRANSITION_OMITTED, UNKNOWN_TRANSITION,
                  // TRANSCRIPTION, TRANSLATION, TRANSPORT
                  // I also have an example where an INHIBITION reaction has one substrate
                  // and one product, so maybe we add some more like CATALYSIS, UNKNOWN_INHIBITION
                  // UNKNOWN_CATALYSIS, TRANSCRITPTIONAL_INHIBITION, TRANSLATIONAL_INHIBITION,
                  // TRANSLATIONAL_ACTIVATION, TRANSCRIPTIONAL_ACTIVATION
                  // the following reactions have two reactants and one product
                  // HETERODIMNER_ASSOCIATION
                  // the following reactions have one substrate and two products:
                  // DISSOCIATION, TRUNCATION
                  switch (ranno.mType)
                    {
                      case STATE_TRANSITION_RTYPE:
                      case KNOWN_TRANSITION_OMITTED_RTYPE:
                      case UNKNOWN_TRANSITION_RTYPE:
                      case TRANSCRIPTION_RTYPE:
                      case TRANSLATION_RTYPE:
                      case TRANSPORT_RTYPE:
                      case CATALYSIS_RTYPE:
                      case UNKNOWN_CATALYSIS_RTYPE:
                      case INHIBITION_RTYPE:
                      case UNKNOWN_INHIBITION_RTYPE:
                      case TRANSCRIPTIONAL_ACTIVATION_RTYPE:
                      case TRANSCRIPTIONAL_INHIBITION_RTYPE:
                      case TRANSLATIONAL_ACTIVATION_RTYPE:
                      case TRANSLATIONAL_INHIBITION_RTYPE:
                      {
                        assert(ranno.mBaseReactants.size() == 1);
                        assert(ranno.mBaseProducts.size() == 1);
                        // check if both elements have a link anchor
                        this->checkLinkAnchors(ranno.mBaseReactants[0], ranno.mBaseProducts[0]);

                        if (ranno.mBaseReactants[0].mPosition != POSITION_UNDEFINED &&
                            ranno.mBaseProducts[0].mPosition != POSITION_UNDEFINED &&
                            !ranno.mBaseReactants[0].mAlias.empty() &&
                            !ranno.mBaseProducts[0].mAlias.empty()
                           )
                          {
                            // we should have a start and an end point now
                            // and the reaction box lies in the middle between these two points
                            std::map<std::string, BoundingBox>::const_iterator box_pos1 = this->mCDBounds.find(ranno.mBaseReactants[0].mAlias);
                            std::map<std::string, BoundingBox>::const_iterator box_pos2 = this->mCDBounds.find(ranno.mBaseProducts[0].mAlias);
                            assert(box_pos1 != this->mCDBounds.end());
                            assert(box_pos2 != this->mCDBounds.end());

                            if (box_pos1 != this->mCDBounds.end() && box_pos2 != this->mCDBounds.end())
                              {
                                // calculate the absolute values of all points
                                // and put them in a vector
                                // then we go through the vector and create
                                // the line segments
                                // add all edit points
                                //
                                // p1 stores the coordinates of the anchor point at the reactant
                                Point p1 = CCellDesignerImporter::getPositionPoint(box_pos1->second, ranno.mBaseReactants[0].mPosition);
                                // p2 stores the coordinates of the anchor point at the product
                                Point p2 = CCellDesignerImporter::getPositionPoint(box_pos2->second, ranno.mBaseProducts[0].mPosition);
                                Point v1(new LayoutPkgNamespaces(), p2.x() - p1.x(), p2.y() - p1.y());
                                Point v2(new LayoutPkgNamespaces());
                                result = CCellDesignerImporter::createOrthogonal(v1, v2);

                                Point p3(new LayoutPkgNamespaces(), p1.x() + v2.x(), p1.y() + v2.y());
                                std::vector<Point>::const_iterator pointIt = ranno.mEditPoints.mPoints.begin(), pointsEnd = ranno.mEditPoints.mPoints.end();
                                Point p(new LayoutPkgNamespaces());
                                std::vector<Point> points;
                                // we add p1 and p2 to the points vector
                                // then the values would be save and we could use the entries from the vector below
                                // which would be save even if p1 and p2 got new values
                                points.push_back(p1);

                                while (pointIt != pointsEnd)
                                  {
                                    // create the absolute point
                                    p = CCellDesignerImporter::calculateAbsoluteValue(*pointIt, p1, p2, p3);
                                    points.push_back(p);
                                    ++pointIt;
                                  }

                                points.push_back(p2);

                                std::vector<Point> reactantPoints;
                                pointIt = points.begin(), pointsEnd = points.end();
                                reactantPoints.push_back(*pointIt);
                                ++pointIt;
                                std::vector<Point> productPoints;
                                int index = 0;
                                int rectangleIndex = ranno.mConnectScheme.mRectangleIndex;

                                // rectangle index marks the segment that contains the "process symbol", i.e. the reaction glyph
                                while (index < rectangleIndex)
                                  {
                                    reactantPoints.push_back(*pointIt);
                                    ++index;
                                    ++pointIt;
                                  }

                                assert(pointIt != pointsEnd);

                                if (pointIt != pointsEnd)
                                  {
                                    p2 = *pointIt;
                                  }

                                // p2 now points to the end of the section that contains the reaction glyph
                                // now we assing p3 to be the start of the segment that contains the reaction glyph
                                // which is the last point we added to the reactants
                                p3 = reactantPoints.back();

                                double distance = CCellDesignerImporter::distance(p3, p2);
                                Point v(new LayoutPkgNamespaces(), (p2.x() - p3.x()) / distance, (p2.y() - p3.y()) / distance);
                                // create the curve for the reaction glyph
                                // right now, the reaction glyph consists of a short
                                // line segment
                                // the curve should not be longer than 1/3 the distance
                                distance /= 6.0;

                                if (distance >= 7.5)
                                  {
                                    distance = 7.5;
                                  }

                                Curve* pCurve = pRGlyph->getCurve();
                                assert(pCurve != NULL);
                                LineSegment* pLS = pCurve->createLineSegment();
                                Point center(new LayoutPkgNamespaces(), (p3.x() + p2.x())*0.5, (p3.y() + p2.y())*0.5);
                                pLS->setStart(center.x() - distance*v.x(), center.y() - distance*v.y());
                                pLS->setEnd(center.x() + distance*v.x(), center.y() + distance*v.y());
                                // add a new substrate point
                                // the substrate points are in reverse order
                                reactantPoints.push_back(*pLS->getStart());
                                // add a new product point
                                productPoints.push_back(*pLS->getEnd());

                                if (pointIt == pointsEnd)
                                  {
                                    productPoints.push_back(p2);
                                  }

                                while (pointIt != pointsEnd)
                                  {
                                    productPoints.push_back(*pointIt);
                                    ++pointIt;
                                  }

                                // create the speciesReferenceGlyphs
                                SpeciesReferenceGlyph* pSRefGlyph1 = pRGlyph->createSpeciesReferenceGlyph();
                                SpeciesReferenceGlyph* pSRefGlyph2 = pRGlyph->createSpeciesReferenceGlyph();
                                assert(pSRefGlyph1 != NULL);
                                assert(pSRefGlyph2 != NULL);

                                if (pSRefGlyph1 != NULL && pSRefGlyph2 != NULL)
                                  {
                                    // set the ids
                                    std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                    pSRefGlyph1->setId(id);
                                    this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph1));
                                    id = this->createUniqueId("SpeciesReferenceGlyph");
                                    pSRefGlyph2->setId(id);
                                    this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph2));
                                    // set the role
                                    pSRefGlyph1->setRole(SPECIES_ROLE_SUBSTRATE);
                                    pSRefGlyph2->setRole(SPECIES_ROLE_PRODUCT);
                                    // set the curve
                                    pCurve = pSRefGlyph1->getCurve();
                                    assert(pCurve != NULL);

                                    if (pCurve != NULL && result == true)
                                      {
                                        assert(reactantPoints.size() > 1);
                                        result = CCellDesignerImporter::createLineSegments(pCurve, reactantPoints.rbegin(), reactantPoints.rend());
                                      }
                                    else
                                      {
                                        result = false;
                                      }

                                    pCurve = pSRefGlyph2->getCurve();
                                    assert(pCurve != NULL);

                                    if (pCurve != NULL && result == true)
                                      {
                                        assert(productPoints.size() > 1);
                                        result = CCellDesignerImporter::createLineSegments(pCurve, productPoints.begin(), productPoints.end());
                                      }

                                    // make sure the role is set because setSpeciesReferenceId relies on it
                                    this->setSpeciesGlyphId(pSRefGlyph1, ranno.mBaseReactants[0]);
                                    this->setSpeciesReferenceId(pSRefGlyph1, ranno.mBaseReactants[0], pRGlyph->getReactionId());
                                    this->setSpeciesGlyphId(pSRefGlyph2, ranno.mBaseProducts[0]);
                                    this->setSpeciesReferenceId(pSRefGlyph2, ranno.mBaseProducts[0], pRGlyph->getReactionId());
                                  }
                                else
                                  {
                                    result = false;
                                  }
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }
                      }
                      break;
                      case DISSOCIATION_RTYPE:
                      case TRUNCATION_RTYPE:
                      {
                        assert(ranno.mBaseReactants.size() == 1);
                        assert(ranno.mBaseProducts.size() == 2);
                        // there must be some edit points
                        assert(!ranno.mEditPoints.mPoints.empty());
                        // there should be a tShapeIndex or an omittedShapeIndex element
                        // that tells us, which of the points is the connection point
                        // center_product1 - center_substrate_1)
                        // if no tShapeIndex or omittedSHapeIndex is given, we assume it is 0
                        Point connectionPoint(new LayoutPkgNamespaces());

                        if (ranno.mEditPoints.mTShapeIndex < (int)ranno.mEditPoints.mPoints.size())
                          {
                            connectionPoint = ranno.mEditPoints.mPoints[ranno.mEditPoints.mTShapeIndex];
                          }
                        else if (ranno.mEditPoints.mOmittedShapeIndex < (int)ranno.mEditPoints.mPoints.size())
                          {
                            connectionPoint = ranno.mEditPoints.mPoints[ranno.mEditPoints.mOmittedShapeIndex];
                          }
                        else
                          {
                            connectionPoint = ranno.mEditPoints.mPoints[0];
                          }

                        // calculate the absolute position
                        // the position for the relative points coordinates is calculated as
                        // center_substrate1 + x*(center_substrate_2 - center_substrate_1)+y*(
                        std::string alias1 = ranno.mBaseReactants[0].mAlias;
                        assert(!alias1.empty());
                        std::string alias2 = ranno.mBaseProducts[0].mAlias;
                        assert(!alias2.empty());
                        std::string alias3 = ranno.mBaseProducts[1].mAlias;
                        assert(!alias3.empty());
                        std::map<std::string, BoundingBox>::const_iterator pos1, pos2, pos3;
                        pos1 = this->mCDBounds.find(alias1);
                        assert(pos1 != this->mCDBounds.end());
                        pos2 = this->mCDBounds.find(alias2);
                        assert(pos2 != this->mCDBounds.end());
                        pos3 = this->mCDBounds.find(alias3);
                        assert(pos3 != this->mCDBounds.end());

                        if (!alias1.empty() &&
                            !alias3.empty() &&
                            !alias3.empty() &&
                            pos1 != this->mCDBounds.end() &&
                            pos2 != this->mCDBounds.end() &&
                            pos3 != this->mCDBounds.end())
                          {
                            Point p1(new LayoutPkgNamespaces(), pos1->second.getPosition()->x() + pos1->second.getDimensions()->getWidth()*0.5, pos1->second.getPosition()->y() + pos1->second.getDimensions()->getHeight()*0.5);
                            Point p2(new LayoutPkgNamespaces(), pos2->second.getPosition()->x() + pos2->second.getDimensions()->getWidth()*0.5, pos2->second.getPosition()->y() + pos2->second.getDimensions()->getHeight()*0.5);
                            Point p3(new LayoutPkgNamespaces(), pos3->second.getPosition()->x() + pos3->second.getDimensions()->getWidth()*0.5, pos3->second.getPosition()->y() + pos3->second.getDimensions()->getHeight()*0.5);
                            Point v1(new LayoutPkgNamespaces(), p2.x() - p1.x(), p2.y() - p1.y());
                            Point v2(new LayoutPkgNamespaces(), p3.x() - p1.x(), p3.y() - p1.y());
                            Point p(new LayoutPkgNamespaces(), p1.x() + connectionPoint.x()*v1.x() + connectionPoint.y()*v2.x(), p1.y() + connectionPoint.x()*v1.y() + connectionPoint.y()*v2.y());
                            // p is the start point of the reaction glyph
                            // i.e. the point where the substrates connect
                            // create the curve for the reaction glyph
                            // the end point is a short distance further along the
                            // path the the only product

                            // first we have to check if we have linkAnchors for all
                            // elements
                            // if not, we create them based on the shortest distance to the
                            // connection point

                            CCellDesignerImporter::checkLinkAnchor(ranno.mBaseReactants[0], p);
                            CCellDesignerImporter::checkLinkAnchor(ranno.mBaseProducts[0], p);
                            CCellDesignerImporter::checkLinkAnchor(ranno.mBaseProducts[1], p);
                            assert(ranno.mBaseReactants[0].mPosition != POSITION_UNDEFINED);
                            assert(ranno.mBaseProducts[0].mPosition != POSITION_UNDEFINED);
                            assert(ranno.mBaseProducts[1].mPosition != POSITION_UNDEFINED);

                            if (ranno.mBaseReactants[0].mPosition != POSITION_UNDEFINED &&
                                ranno.mBaseProducts[0].mPosition != POSITION_UNDEFINED &&
                                ranno.mBaseProducts[1].mPosition != POSITION_UNDEFINED)
                              {
                                // p is the end point of the reaction glyph
                                // i.e. the point where the products connect
                                // the start point is a short distance further along the
                                // path the to the only substrate
                                Curve* pCurve = pRGlyph->getCurve();
                                assert(pCurve != NULL);

                                if (pCurve != NULL)
                                  {
                                    LineSegment* pLS = pCurve->createLineSegment();
                                    assert(pLS != NULL);

                                    if (pLS != NULL)
                                      {
                                        pLS->setEnd(p.x(), p.y());

                                        Point p1 = CCellDesignerImporter::getPositionPoint(pos1->second, ranno.mBaseReactants[0].mPosition);
                                        double dist = CCellDesignerImporter::distance(p1, p);
                                        assert(dist != 0.0);
                                        Point v(new LayoutPkgNamespaces(), (p1.x() - p.x()) / dist, (p1.y() - p.y()) / dist);
                                        dist /= 3.0;

                                        if (dist > 15.0)
                                          {
                                            dist = 15.0;
                                          }

                                        pLS->setStart(p.x() + dist*v.x(), p.y() + dist*v.y());

                                        // create the species reference glyphs
                                        // since we already know the endpoint for the substrate, we start
                                        // with that
                                        SpeciesReferenceGlyph* pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                                        assert(pSRefGlyph != NULL);

                                        if (pSRefGlyph != NULL)
                                          {
                                            // set the curve
                                            pCurve = pSRefGlyph->getCurve();

                                            if (pCurve != NULL)
                                              {
                                                LineSegment* pLS2 = pCurve->createLineSegment();
                                                assert(pLS2 != NULL);

                                                if (pLS2 != NULL)
                                                  {
                                                    pLS2->setStart(pLS->getStart()->x(), pLS->getStart()->y());
                                                    pLS2->setEnd(p1.x(), p1.y());
                                                  }
                                                else
                                                  {
                                                    result = false;
                                                  }
                                              }
                                            else
                                              {
                                                result = false;
                                              }

                                            // set an id
                                            std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                            pSRefGlyph->setId(id);
                                            this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));
                                            // set the role
                                            pSRefGlyph->setRole(SPECIES_ROLE_SUBSTRATE);
                                            // set the species glyph id
                                            this->setSpeciesGlyphId(pSRefGlyph, ranno.mBaseReactants[0]);
                                            // set the species reference id
                                            this->setSpeciesReferenceId(pSRefGlyph, ranno.mBaseReactants[0], pRGlyph->getReactionId());
                                          }
                                        else
                                          {
                                            result = false;
                                          }

                                        // first product
                                        if (result == true)
                                          {
                                            p1 = CCellDesignerImporter::getPositionPoint(pos2->second, ranno.mBaseProducts[0].mPosition);
                                            pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                                            assert(pSRefGlyph != NULL);

                                            if (pSRefGlyph != NULL)
                                              {
                                                // set the curve
                                                pCurve = pSRefGlyph->getCurve();

                                                if (pCurve != NULL)
                                                  {
                                                    LineSegment* pLS2 = pCurve->createLineSegment();
                                                    assert(pLS2 != NULL);

                                                    if (pLS2 != NULL)
                                                      {
                                                        pLS2->setStart(pLS->getEnd()->x(), pLS->getEnd()->y());
                                                        pLS2->setEnd(p1.x(), p1.y());
                                                      }
                                                    else
                                                      {
                                                        result = false;
                                                      }
                                                  }
                                                else
                                                  {
                                                    result = false;
                                                  }

                                                // set an id
                                                std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                                pSRefGlyph->setId(id);
                                                this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));
                                                // set the role
                                                pSRefGlyph->setRole(SPECIES_ROLE_PRODUCT);
                                                // set the species glyph id
                                                this->setSpeciesGlyphId(pSRefGlyph, ranno.mBaseProducts[0]);
                                                // set the species reference id
                                                this->setSpeciesReferenceId(pSRefGlyph, ranno.mBaseProducts[0], pRGlyph->getReactionId());
                                              }
                                            else
                                              {
                                                result = false;
                                              }
                                          }

                                        // second product
                                        if (result == true)
                                          {
                                            p1 = CCellDesignerImporter::getPositionPoint(pos3->second, ranno.mBaseProducts[1].mPosition);
                                            pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                                            assert(pSRefGlyph != NULL);

                                            if (pSRefGlyph != NULL)
                                              {
                                                // set the curve
                                                pCurve = pSRefGlyph->getCurve();

                                                if (pCurve != NULL)
                                                  {
                                                    LineSegment* pLS2 = pCurve->createLineSegment();
                                                    assert(pLS2 != NULL);

                                                    if (pLS2 != NULL)
                                                      {
                                                        pLS2->setStart(pLS->getEnd()->x(), pLS->getEnd()->y());
                                                        pLS2->setEnd(p1.x(), p1.y());
                                                      }
                                                    else
                                                      {
                                                        result = false;
                                                      }
                                                  }
                                                else
                                                  {
                                                    result = false;
                                                  }

                                                // set an id
                                                std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                                pSRefGlyph->setId(id);
                                                this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));
                                                // set the role
                                                pSRefGlyph->setRole(SPECIES_ROLE_PRODUCT);
                                                // set the species glyph id
                                                this->setSpeciesGlyphId(pSRefGlyph, ranno.mBaseProducts[1]);
                                                // set the species reference id
                                                this->setSpeciesReferenceId(pSRefGlyph, ranno.mBaseProducts[1], pRGlyph->getReactionId());
                                              }
                                            else
                                              {
                                                result = false;
                                              }
                                          }

                                      }
                                    else
                                      {
                                        result = false;
                                      }
                                  }
                                else
                                  {
                                    result = false;
                                  }
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }
                      }
                      break;
                      case HETERODIMER_ASSOCIATION_RTYPE:
                      {
                        assert(ranno.mBaseReactants.size() == 2);
                        assert(ranno.mBaseProducts.size() == 1);
                        // assert that all elements have a link anchor
                        assert(!ranno.mEditPoints.mPoints.empty());
                        // there should be a tShapeIndex or an omittedShapeIndex element
                        // that tells us, which of the points is the connection point
                        Point connectionPoint(new LayoutPkgNamespaces());

                        if (ranno.mEditPoints.mTShapeIndex < (int)ranno.mEditPoints.mPoints.size())
                          {
                            connectionPoint = ranno.mEditPoints.mPoints[ranno.mEditPoints.mTShapeIndex];
                          }
                        else if (ranno.mEditPoints.mOmittedShapeIndex < (int)ranno.mEditPoints.mPoints.size())
                          {
                            connectionPoint = ranno.mEditPoints.mPoints[ranno.mEditPoints.mOmittedShapeIndex];
                          }
                        else
                          {
                            connectionPoint = ranno.mEditPoints.mPoints[0];
                          }

                        // calculate the absolute position
                        // the position for the relative points coordinates is calculated as
                        // center_substrat1 + x*(center_product1 - center_substrate_1)+y*(
                        // center_product2 - center_substrate_1)
                        // if no tShapeIndex or omittedShapeIndex is given, we assume it is 0
                        std::string alias1 = ranno.mBaseReactants[0].mAlias;
                        assert(!alias1.empty());
                        std::string alias2 = ranno.mBaseReactants[1].mAlias;
                        assert(!alias2.empty());
                        std::string alias3 = ranno.mBaseProducts[0].mAlias;
                        assert(!alias3.empty());
                        std::map<std::string, BoundingBox>::const_iterator pos1, pos2, pos3;
                        pos1 = this->mCDBounds.find(alias1);
                        assert(pos1 != this->mCDBounds.end());
                        pos2 = this->mCDBounds.find(alias2);
                        assert(pos2 != this->mCDBounds.end());
                        pos3 = this->mCDBounds.find(alias3);
                        assert(pos3 != this->mCDBounds.end());

                        if (!alias1.empty() &&
                            !alias3.empty() &&
                            !alias3.empty() &&
                            pos1 != this->mCDBounds.end() &&
                            pos2 != this->mCDBounds.end() &&
                            pos3 != this->mCDBounds.end())
                          {
                            Point p1(new LayoutPkgNamespaces(), pos1->second.getPosition()->x() + pos1->second.getDimensions()->getWidth()*0.5, pos1->second.getPosition()->y() + pos1->second.getDimensions()->getHeight()*0.5);
                            Point p2(new LayoutPkgNamespaces(), pos2->second.getPosition()->x() + pos2->second.getDimensions()->getWidth()*0.5, pos2->second.getPosition()->y() + pos2->second.getDimensions()->getHeight()*0.5);
                            Point p3(new LayoutPkgNamespaces(), pos3->second.getPosition()->x() + pos3->second.getDimensions()->getWidth()*0.5, pos3->second.getPosition()->y() + pos3->second.getDimensions()->getHeight()*0.5);

                            Point p = CCellDesignerImporter::calculateAbsoluteValue(connectionPoint, p1, p2, p3);

                            // first we have to check if we have linkAnchors for all
                            // elements
                            // if not, we create them based on the shortest distance to the
                            // connection point
                            CCellDesignerImporter::checkLinkAnchor(ranno.mBaseReactants[0], p);
                            CCellDesignerImporter::checkLinkAnchor(ranno.mBaseReactants[1], p);
                            CCellDesignerImporter::checkLinkAnchor(ranno.mBaseProducts[0], p);
                            assert(ranno.mBaseReactants[0].mPosition != POSITION_UNDEFINED);
                            assert(ranno.mBaseReactants[1].mPosition != POSITION_UNDEFINED);
                            assert(ranno.mBaseProducts[0].mPosition != POSITION_UNDEFINED);

                            if (ranno.mBaseReactants[0].mPosition != POSITION_UNDEFINED &&
                                ranno.mBaseReactants[1].mPosition != POSITION_UNDEFINED &&
                                ranno.mBaseProducts[0].mPosition != POSITION_UNDEFINED)
                              {
                                // p is the start point of the reaction glyph
                                // i.e. the point where the substrates connect
                                // create the curve for the reaction glyph
                                // the end point is a short distance further along the
                                // path the to the only product
                                Curve* pCurve = pRGlyph->getCurve();
                                assert(pCurve != NULL);

                                if (pCurve != NULL)
                                  {
                                    LineSegment* pLS = pCurve->createLineSegment();
                                    assert(pLS != NULL);

                                    if (pLS != NULL)
                                      {
                                        pLS->setStart(p.x(), p.y());

                                        Point p3 = CCellDesignerImporter::getPositionPoint(pos3->second, ranno.mBaseProducts[0].mPosition);
                                        double dist = CCellDesignerImporter::distance(p3, p);
                                        assert(dist != 0.0);
                                        Point v(new LayoutPkgNamespaces(), (p3.x() - p.x()) / dist, (p3.y() - p.y()) / dist);
                                        dist /= 3.0;

                                        if (dist > 15.0)
                                          {
                                            dist = 15.0;
                                          }

                                        pLS->setEnd(p.x() + dist*v.x(), p.y() + dist*v.y());

                                        // create the species reference glyphs
                                        // since we already know the endpoint for the product, we start
                                        // with that
                                        SpeciesReferenceGlyph* pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                                        assert(pSRefGlyph != NULL);

                                        if (pSRefGlyph != NULL)
                                          {
                                            // set the curve
                                            pCurve = pSRefGlyph->getCurve();

                                            if (pCurve != NULL)
                                              {
                                                LineSegment* pLS2 = pCurve->createLineSegment();
                                                assert(pLS2 != NULL);

                                                if (pLS2 != NULL)
                                                  {
                                                    pLS2->setStart(p.x(), p.y());
                                                    pLS2->setEnd(p3.x(), p3.y());
                                                  }
                                                else
                                                  {
                                                    result = false;
                                                  }
                                              }
                                            else
                                              {
                                                result = false;
                                              }

                                            // set an id
                                            std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                            pSRefGlyph->setId(id);
                                            this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));
                                            // set the role
                                            pSRefGlyph->setRole(SPECIES_ROLE_PRODUCT);
                                            // set the species glyph id
                                            this->setSpeciesGlyphId(pSRefGlyph, ranno.mBaseProducts[0]);
                                            // set the species reference id
                                            this->setSpeciesReferenceId(pSRefGlyph, ranno.mBaseProducts[0], pRGlyph->getReactionId());
                                          }
                                        else
                                          {
                                            result = false;
                                          }

                                        // first substrate
                                        if (result == true)
                                          {
                                            p3 = CCellDesignerImporter::getPositionPoint(pos1->second, ranno.mBaseReactants[0].mPosition);
                                            pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                                            assert(pSRefGlyph != NULL);

                                            if (pSRefGlyph != NULL)
                                              {
                                                // set the curve
                                                pCurve = pSRefGlyph->getCurve();

                                                if (pCurve != NULL)
                                                  {
                                                    LineSegment* pLS2 = pCurve->createLineSegment();
                                                    assert(pLS2 != NULL);

                                                    if (pLS2 != NULL)
                                                      {
                                                        pLS2->setStart(pLS->getStart()->x(), pLS->getStart()->y());
                                                        pLS2->setEnd(p3.x(), p3.y());
                                                      }
                                                    else
                                                      {
                                                        result = false;
                                                      }
                                                  }
                                                else
                                                  {
                                                    result = false;
                                                  }

                                                // set an id
                                                std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                                pSRefGlyph->setId(id);
                                                this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));
                                                // set the role
                                                pSRefGlyph->setRole(SPECIES_ROLE_SUBSTRATE);
                                                // set the species glyph id
                                                this->setSpeciesGlyphId(pSRefGlyph, ranno.mBaseReactants[0]);
                                                // set the species reference id
                                                this->setSpeciesReferenceId(pSRefGlyph, ranno.mBaseReactants[0], pRGlyph->getReactionId());
                                              }
                                            else
                                              {
                                                result = false;
                                              }
                                          }

                                        // second substrate
                                        if (result == true)
                                          {
                                            p3 = CCellDesignerImporter::getPositionPoint(pos2->second, ranno.mBaseReactants[1].mPosition);
                                            pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                                            assert(pSRefGlyph != NULL);

                                            if (pSRefGlyph != NULL)
                                              {
                                                // set the curve
                                                pCurve = pSRefGlyph->getCurve();

                                                if (pCurve != NULL)
                                                  {
                                                    LineSegment* pLS2 = pCurve->createLineSegment();
                                                    assert(pLS2 != NULL);

                                                    if (pLS2 != NULL)
                                                      {
                                                        pLS2->setStart(pLS->getStart()->x(), pLS->getStart()->y());
                                                        pLS2->setEnd(p3.x(), p3.y());
                                                      }
                                                    else
                                                      {
                                                        result = false;
                                                      }
                                                  }
                                                else
                                                  {
                                                    result = false;
                                                  }

                                                // set an id
                                                std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                                pSRefGlyph->setId(id);
                                                this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));
                                                // set the role
                                                pSRefGlyph->setRole(SPECIES_ROLE_SUBSTRATE);
                                                // set the species glyph id
                                                this->setSpeciesGlyphId(pSRefGlyph, ranno.mBaseReactants[1]);
                                                // set the species reference id
                                                this->setSpeciesReferenceId(pSRefGlyph, ranno.mBaseReactants[1], pRGlyph->getReactionId());
                                              }
                                            else
                                              {
                                                result = false;
                                              }
                                          }

                                      }
                                    else
                                      {
                                        result = false;
                                      }
                                  }
                                else
                                  {
                                    result = false;
                                  }
                              }
                            else
                              {
                                result = false;
                              }

                          }
                        else
                          {
                            result = false;
                          }
                      }
                      break;
                      default:
                        result = false;
                        break;
                    }

                  // there might be additional substrates and reactants
                  // in the listOfReactantLinks and the listOfProductLinks
                  if (result == true)
                    {
                      result = this->handleExtraReactionElements(pRGlyph, ranno, true);
                    }

                  if (result == true)
                    {
                      result = this->handleExtraReactionElements(pRGlyph, ranno, false);
                    }

                  // now that the species reference glyphs are handled,
                  // we should handle the modifiers
                  if (result == true)
                    {
                      result = this->handleModificationLinks(pRGlyph, ranno);
                    }
                }
              else
                {
                  result = false;
                }
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Takes a node that contains a number of baseReactants or baseProducts
 * and creates species reference glyphs for each one.
 */
bool CCellDesignerImporter::createSpeciesReferenceGlyphs(ReactionGlyph* pRGlyph, const std::vector<LinkTarget>& links, std::map<SpeciesReferenceGlyph*, Point>& startsMap, bool reactants)
{
  bool result = true;
  startsMap.clear();

  if (pRGlyph != NULL)
    {
      unsigned int i, iMax = links.size();
      const LinkTarget*  pLink = NULL;

      for (i = 0; i < iMax && result == true; ++i)
        {
          pLink = &links[i];

          // a baseProduct or baseReactant node has an alias attribute
          if (!pLink->mAlias.empty())
            {
              // if the alias points to an element within a complexSpeciesReference,
              // we don't get a valid position here because we never created elements for this
              // aliases.
              // we need to store them and their size in another map so that we can determine where
              // the arrow is supposed to go
              std::map<std::string, BoundingBox>::const_iterator pos = this->mCDBounds.find(pLink->mAlias);

              if (pos != this->mCDBounds.end())
                {
                  // now we have to find the layout element that corresponds to this alias
                  // there are two posibilities
                  // a) the alias belongs directly to the layout element
                  // b) the alias is part of a complex and the complex root
                  //    represents the layout element
                  std::map<std::string, GraphicalObject*>::const_iterator go_pos = this->mCDIdToLayoutElement.find(pLink->mAlias);

                  if (go_pos == this->mCDIdToLayoutElement.end())
                    {
                      std::string alias = this->findRootElementId(pLink->mAlias);
                      // make sure we found the dependency
                      assert(!alias.empty());

                      // nit should now point to the root of the tree
                      // and the data of that root should correspond to the CD Id
                      // of a layout object
                      if (!alias.empty())
                        {
                          go_pos = this->mCDIdToLayoutElement.find(alias);
                          assert(go_pos != this->mCDIdToLayoutElement.end());

                          if (go_pos == this->mCDIdToLayoutElement.end())
                            {
                              result = false;
                            }
                        }
                    }

                  if (result == true)
                    {
                      SpeciesReferenceGlyph* pSRG = pRGlyph->createSpeciesReferenceGlyph();

                      if (pSRG != NULL)
                        {
                          std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                          pSRG->setId(id);
                          this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRG));
                          assert(go_pos->second != NULL);
                          pSRG->setSpeciesGlyphId(go_pos->second->getId());

                          // and a species attribute. The species attribute can be used to
                          // determine the species reference the glyph belongs to
                          if (!pLink->mSpecies.empty() &&
                              !pRGlyph->getReactionId().empty() &&
                              this->mpDocument != NULL &&
                              this->mpDocument->getModel() != NULL)
                            {
                              Reaction* pReaction = this->mpDocument->getModel()->getReaction(pRGlyph->getReactionId());

                              if (pReaction != NULL)
                                {
                                  // check if we have a substrate or a product
                                  if (reactants == true)
                                    {
                                      pSRG->setRole("SUBSTRATE");
                                      // look for the species reference in the listOfReactants of the reaction
                                      id = pLink->mSpecies;
                                      // the id we get here can be the id of a cell designer species
                                      // in that case we can't associate the species reference glyph
                                      // with an SBML species reference
                                      unsigned int i, iMax = pReaction->getNumReactants();

                                      for (i = 0; i < iMax; ++i)
                                        {
                                          if (pReaction->getReactant(i)->getSpecies() == id)
                                            {
                                              break;
                                            }
                                        }

                                      if (i != iMax)
                                        {
                                          // check if the species reference has an id, if not, we create one
                                          if (!pReaction->getReactant(i)->isSetId())
                                            {
                                              id = this->createUniqueId("SpeciesReference");
                                              pReaction->getReactant(i)->setId(id);
                                              this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pReaction->getReactant(i)));
                                            }

                                          id = pReaction->getReactant(i)->getId();
                                          pSRG->setSpeciesReferenceId(id);
                                        }
                                    }
                                  else
                                    {
                                      pSRG->setRole("PRODUCT");
                                      // look for the species reference in the listOfReactants of the reaction
                                      id = pLink->mSpecies;
                                      // the id we get here can be the id of a cell designer species
                                      // in that case we can't associate the species reference glyph
                                      // with an SBML species reference
                                      unsigned int i, iMax = pReaction->getNumProducts();

                                      for (i = 0; i < iMax; ++i)
                                        {
                                          if (pReaction->getProduct(i)->getSpecies() == id)
                                            {
                                              break;
                                            }
                                        }

                                      if (i != iMax)
                                        {
                                          // check if the species reference has an id, if not, we create one
                                          if (!pReaction->getProduct(i)->isSetId())
                                            {
                                              id = this->createUniqueId("SpeciesReference");
                                              pReaction->getProduct(i)->setId(id);
                                              this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pReaction->getProduct(i)));
                                            }

                                          id = pReaction->getProduct(i)->getId();
                                          pSRG->setSpeciesReferenceId(id);
                                        }
                                    }
                                }
                              else
                                {
                                  result = false;
                                }
                            }

                          // the node has a child called linkAnchor with a position attribute
                          // The attribute is an enum that can be converted to an angle or
                          // a position on the bounding box of the associated species glyph
                          if (result == true)
                            {
                              if (pLink->mPosition != POSITION_UNDEFINED)
                                {
                                  // get the point on the boundingbox of the species glyph
                                  // that corresponds to position
                                  Point p = this->getPositionPoint(pos->second, pLink->mPosition);
                                  startsMap.insert(std::pair<SpeciesReferenceGlyph*, Point>(pSRG, p));
                                }
                              else
                                {
                                  // there are actually elements that do not have the linkAnchor
                                  // since I currently don't know what to do with these, I just add the
                                  // origin as position
                                  startsMap.insert(std::pair<SpeciesReferenceGlyph*, Point>(pSRG, Point(new LayoutPkgNamespaces(), 0.0, 0.0)));
                                }
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Takes a bounding box and a position string and retirns the position on the bounding box that corresponds
 * to the given position.
 */
Point CCellDesignerImporter::getPositionPoint(const BoundingBox& box, POSITION position)
{
  double x = std::numeric_limits<double>::quiet_NaN(), y = std::numeric_limits<double>::quiet_NaN();
  double bx = box.getPosition()->x();
  double by = box.getPosition()->y();
  double bw = box.getDimensions()->getWidth();
  double bh = box.getDimensions()->getHeight();

  switch (position)
    {
      case POSITION_N:
        // top
        x = bx + bw * 0.5;
        y = by;
        break;
      case POSITION_NNE:
        x = bx + bw * 0.75;
        y = by;
        break;
      case POSITION_NE:
        // top right
        x = bx + bw;
        y = by;
        break;
      case POSITION_ENE:
        x = bx + bw;
        y = by + 0.25 * bh;
        break;
      case POSITION_E:
        // right middle
        x = bx + bw;
        y = by + bh * 0.5;
        break;
      case POSITION_ESE:
        x = bx + bw;
        y = by + 0.75 * bh;
        break;
      case POSITION_SE:
        // right bottom
        x = bx + bw;
        y = by + bh;
        break;
      case POSITION_SSE:
        x = bx + 0.75 * bw;
        y = by + bh;
        break;
      case POSITION_S:
        // bottom
        x = bx + bw * 0.5;
        y = by + bh;
        break;
      case POSITION_SSW:
        x = bx + 0.25 * bw;
        y = by + bh;
        break;
      case POSITION_SW:
        // bottom left
        x = bx;
        y = by + bh;
        break;
      case POSITION_WSW:
        x = bx;
        y = by + 0.75 * bh;
        break;
      case POSITION_W:
        // left
        x = bx;
        y = by + bh * 0.5;
        break;
      case POSITION_WNW:
        x = bx;
        y = by + 0.25 * bh;
        break;
      case POSITION_NW:
        // top left
        x = bx;
        y = by;
        break;
      case POSITION_NNW:
        x = bx + 0.25 * bw;
        y = by;
        break;
      default:
        break;
    }

  return Point(new LayoutPkgNamespaces(), x, y);
}

/**
 * Traverses the compartments of the model and looks for CellDesigner annotations.
 * These are used to create text glyphs associated with compartments.
 */
bool CCellDesignerImporter::convertCompartmentAnnotations()
{
  bool result = true;

  if (this->mpDocument && this->mpDocument->getModel() && this->mpLayout)
    {
      Model* pModel = this->mpDocument->getModel();
      unsigned int i, iMax = pModel->getNumCompartments();
      Compartment* pCompartment = NULL;
      const XMLNode* pAnnotation = NULL;

      for (i = 0; i < iMax && result == true; ++i)
        {
          pCompartment = pModel->getCompartment(i);

          if (pCompartment->getAnnotation() != NULL)
            {
              pAnnotation = CCellDesignerImporter::findCellDesignerAnnotation(this->mpDocument, pCompartment->getAnnotation());

              // there should be a name element in there somewhere
              if (pAnnotation != NULL)
                {
                  CompartmentAnnotation canno;
                  result = CCellDesignerImporter::parseCompartmentAnnotation(pAnnotation, canno);

                  if (result)
                    {
                      this->mCompartmentAnnotationMap.insert(std::pair<std::string, CompartmentAnnotation>(pCompartment->getId(), canno));
                      // create the text glyph if there is a CompartmentGlyph
                      std::multimap<std::string, GraphicalObject*>::const_iterator pos = this->mModelIdToLayoutElement.find(pCompartment->getId());

                      if (pos != this->mModelIdToLayoutElement.end() && pos->second != NULL)
                        {
                          do
                            {
                              TextGlyph* pTGlyph = this->mpLayout->createTextGlyph();
                              std::string id = this->createUniqueId("TextGlyph");
                              pTGlyph->setId(id);
                              this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pTGlyph));
                              // set the text and the associated layout element
                              pTGlyph->setText(canno.mName);
                              pTGlyph->setGraphicalObjectId(pos->second->getId());
                              // set the position of the text relative to the layout element
                              // from the mCompartmentNamePointMap
                              const CompartmentGlyph* pCGlyph = dynamic_cast<const CompartmentGlyph*>(pos->second);
                              assert(pCGlyph != NULL);
                              std::map<const CompartmentGlyph*, Point>::const_iterator pos2 = this->mCompartmentNamePointMap.find(pCGlyph);
                              Point p(new LayoutPkgNamespaces(), 0.0, 0.0);

                              if (pos2 != this->mCompartmentNamePointMap.end())
                                {
                                  p = pos2->second;
                                }

                              // set the position and dimensions of the text
                              Point position = *pCGlyph->getBoundingBox()->getPosition();
                              // add the name position to the position of the compartment
                              position.setX(position.x() + p.x());
                              position.setY(position.y() + p.y());
                              Dimensions dim = *pCGlyph->getBoundingBox()->getDimensions();
                              // subtract the name position from the dimensions of the compartment
                              dim.setWidth(dim.getWidth() - p.x());
                              dim.setHeight(dim.getHeight() - p.y());
                              BoundingBox bb;
                              bb.setPosition(&position);
                              bb.setDimensions(&dim);
                              pTGlyph->setBoundingBox(&bb);
                              // create an appropriate style
                              // first we need the style information for the CompartmentGlyph
                              std::map<const CompartmentGlyph*, CompartmentAlias>::const_iterator compAliasPos = this->mCompartmentAliasMap.find(pCGlyph);
                              assert(compAliasPos != this->mCompartmentAliasMap.end());

                              if (compAliasPos != this->mCompartmentAliasMap.end())
                                {
                                  this->createTextGlyphStyle(compAliasPos->second.mFontSize, Text::ANCHOR_START, Text::ANCHOR_BOTTOM, pTGlyph->getId());
                                }

                              ++pos;
                            }
                          while (pos != this->mModelIdToLayoutElement.end() && pos->first == pCompartment->getId());

                        }
                      else
                        {
                          // TODO this is OK as long as we only import compartments with bounds
                          //result=false;
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Traverses the species of the model and looks for CellDesigner annotations.
 * These are used to create text glyphs associated with species.
 */
bool CCellDesignerImporter::convertSpeciesAnnotations()
{
  bool result = true;

  if (this->mpDocument && this->mpDocument->getModel() && this->mpLayout)
    {
      Model* pModel = this->mpDocument->getModel();
      unsigned int i, iMax = pModel->getNumSpecies();
      Species* pSpecies = NULL;
      const XMLNode* pAnnotation = NULL;

      for (i = 0; i < iMax && result == true; ++i)
        {
          pSpecies = pModel->getSpecies(i);

          if (pSpecies->getAnnotation() != NULL)
            {
              pAnnotation = CCellDesignerImporter::findCellDesignerAnnotation(this->mpDocument, pSpecies->getAnnotation());

              // there should be a name element in there somewhere
              if (pAnnotation != NULL)
                {

                  SpeciesAnnotation sanno;
                  result = CCellDesignerImporter::parseSpeciesAnnotation(pAnnotation, sanno);

                  if (result == true)
                    {
                      this->mSpeciesAnnotationMap.insert(std::pair<std::string, SpeciesAnnotation>(pSpecies->getId(), sanno));
                      std::string name = pSpecies->getName();

                      //result=this->findNameForSpeciesIdentity(sanno.mIdentity,name);
                      if (result && !name.empty() && sanno.mIdentity.mSpeciesClass != DEGRADED_CLASS)
                        {
                          // create the text glyph if there is a SpeciesGlyph
                          std::multimap<std::string, GraphicalObject*>::const_iterator pos = this->mModelIdToLayoutElement.find(pSpecies->getId());
                          assert(pos != this->mModelIdToLayoutElement.end());
                          assert(pos->second != NULL);

                          if (pos != this->mModelIdToLayoutElement.end() && pos->second != NULL)
                            {
                              do
                                {
                                  const SpeciesGlyph* pSGlyph = dynamic_cast<const SpeciesGlyph*>(pos->second);
                                  assert(pSGlyph != NULL);

                                  if (pSGlyph != NULL)
                                    {
                                      TextGlyph* pTGlyph = this->mpLayout->createTextGlyph();
                                      std::string id = this->createUniqueId("TextGlyph");
                                      pTGlyph->setId(id);
                                      this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pTGlyph));
                                      // set the text and the associated layout element
                                      pTGlyph->setText(name);
                                      pTGlyph->setGraphicalObjectId(pSGlyph->getId());
                                      // set the position and dimensions of the text
                                      Point position = *pSGlyph->getBoundingBox()->getPosition();
                                      Dimensions dim = *pSGlyph->getBoundingBox()->getDimensions();
                                      BoundingBox bb;
                                      bb.setPosition(&position);
                                      bb.setDimensions(&dim);
                                      pTGlyph->setBoundingBox(&bb);
                                      // create an appropriate style
                                      // first we need the style information for the CompartmentGlyph
                                      std::map<const SpeciesGlyph*, SpeciesAlias>::const_iterator speciesAliasPos = this->mSpeciesAliasMap.find(pSGlyph);
                                      assert(speciesAliasPos != this->mSpeciesAliasMap.end());

                                      if (speciesAliasPos != this->mSpeciesAliasMap.end())
                                        {
                                          Text::TEXT_ANCHOR vAnchor = Text::ANCHOR_MIDDLE;

                                          if (speciesAliasPos->second.mComplex)
                                            {
                                              vAnchor = Text::ANCHOR_BOTTOM;
                                            }

                                          this->createTextGlyphStyle(speciesAliasPos->second.mFontSize, Text::ANCHOR_MIDDLE, vAnchor, pTGlyph->getId());
                                        }
                                    }
                                  else
                                    {
                                      result = false;
                                    }

                                  ++pos;
                                }
                              while (result == true && pos != this->mModelIdToLayoutElement.end() && pos->first == pSpecies->getId());
                            }
                          else
                            {
                              result = false;
                            }
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Adds a new entry to the dependency tree for complex species aliases.
 */
void CCellDesignerImporter::addDependency(const std::string& parent, const std::string& child)
{
  // check if the parent is already part of one of the trees
  CCopasiNode<std::string>* pChildNode = new CCopasiNode<std::string>(child);
  std::list<CCopasiNode<std::string>* >::iterator it = this->mComplexDependencies.begin(), endit = this->mComplexDependencies.end(), tree;
  CCopasiNode<std::string>* pCurrent;

  while (it != endit)
    {
      // iterate over the nodes in the tree
      // and try to find the parent
      pCurrent = *it;

      while (pCurrent != NULL)
        {
          if (pCurrent->getData() == parent)
            {
              pCurrent->addChild(pChildNode);
              break;
            }

          pCurrent = pCurrent->getNext();
        }

      if (pCurrent != NULL)
        {
          break;
        }

      ++it;
    }

  // if so add the child to that tree node
  // else create a new tree with parent as the root and child as the only child
  if (it == endit)
    {
      CCopasiNode<std::string>* pRoot = new CCopasiNode<std::string>;
      pRoot->setData(parent);
      pRoot->addChild(pChildNode);
      this->mComplexDependencies.push_back(pRoot);
      // update the iterator to the end
      endit = this->mComplexDependencies.end();
    }

  tree = this->mComplexDependencies.begin();

  // check if the child is already root to another tree, if so, we combine the two trees
  while (tree != endit)
    {
      // check if the root node is child
      if (tree != it && (*tree)->getData() == child)
        {
          // combine tree and it by adding all children from tree to it
          CCopasiNode<std::string>* pChild = (*tree)->getChild(), *pSibling = NULL;

          while (pChild != NULL)
            {
              // store the next node before we change the tree
              pSibling = pChild->getSibling();
              (*tree)->removeChild(pChild);
              pChildNode->addChild(pChild);
              pChild = pSibling;
            }

          // there can be only one I think, so we can stop here
          break;
        }

      ++tree;
    }
}

/**
 * Goes through the children of the given node which represents a list of protein definitions
 * and collects the names for them.
 * These names are converted to text glyphs for the proteins.
bool CCellDesignerImporter::parseGeneNames(const XMLNode* pNode)
{
    bool result=true;
    if(pNode != NULL && pNode->getName() == "listOfGenes")
    {
        std::string prefix=pNode->getPrefix();
        unsigned int i,iMax=pNode->getNumChildren();
        const XMLNode* pChild=NULL;
        for(i=0;i<iMax;++i)
        {
            pChild=&pNode->getChild(i);
            if(pChild != NULL &&
               pChild->getPrefix() == prefix &&
               pChild->getName() == "gene" &&
               pChild->getAttributes().hasAttribute("id") &&
               pChild->getAttributes().hasAttribute("name"))
            {
                std::string id=pChild->getAttributes().getValue("id");
                assert(!id.empty());
                std::string name=pChild->getAttributes().getValue("name");
                assert(!name.empty());
                this->mGeneNameMap.insert(std::pair<std::string,std::string>(id,name));
            }
        }
    }
    return result;
}
 */

/**
 * Goes through the children of the given node which represents a list of protein definitions
 * and collects the names for them.
 * These names are converted to text glyphs for the proteins.
bool CCellDesignerImporter::parseRNANames(const XMLNode* pNode)
{
    bool result=true;
    if(pNode != NULL && pNode->getName() == "listOfRNAs")
    {
        std::string prefix=pNode->getPrefix();
        unsigned int i,iMax=pNode->getNumChildren();
        const XMLNode* pChild=NULL;
        for(i=0;i<iMax;++i)
        {
            pChild=&pNode->getChild(i);
            if(pChild != NULL &&
               pChild->getPrefix() == prefix &&
               pChild->getName() == "RNA" &&
               pChild->getAttributes().hasAttribute("id") &&
               pChild->getAttributes().hasAttribute("name"))
            {
                std::string id=pChild->getAttributes().getValue("id");
                assert(!id.empty());
                std::string name=pChild->getAttributes().getValue("name");
                assert(!name.empty());
                this->mRNANameMap.insert(std::pair<std::string,std::string>(id,name));
            }
        }
    }
    return result;
}
 */

/**
 * Goes through the children of the given node which represents a list of protein definitions
 * and collects the names for them.
 * These names are converted to text glyphs for the proteins.
bool CCellDesignerImporter::parseASRNANames(const XMLNode* pNode)
{
    bool result=true;
    if(pNode != NULL && pNode->getName() == "listOfAntisenseRNAs")
    {
        std::string prefix=pNode->getPrefix();
        unsigned int i,iMax=pNode->getNumChildren();
        const XMLNode* pChild=NULL;
        for(i=0;i<iMax;++i)
        {
            pChild=&pNode->getChild(i);
            if(pChild != NULL &&
               pChild->getPrefix() == prefix &&
               pChild->getName() == "AntisenseRNA" &&
               pChild->getAttributes().hasAttribute("id") &&
               pChild->getAttributes().hasAttribute("name"))
            {
                std::string id=pChild->getAttributes().getValue("id");
                assert(!id.empty());
                std::string name=pChild->getAttributes().getValue("name");
                assert(!name.empty());
                this->mASRNANameMap.insert(std::pair<std::string,std::string>(id,name));
            }
        }
    }
    return result;
}
 */

/**
 * Goes through the children of the given node which represents a list of
 * protein definitions and check the types.
 * If the type is RECEPTOR, ION_CHANNEL or TRUNCATED, store that information.
 */
bool CCellDesignerImporter::parseProteins(const XMLNode* pNode)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "listOfProteins")
    {
      std::string prefix = pNode->getPrefix();
      unsigned int i, iMax = pNode->getNumChildren();
      const XMLNode* pChild = NULL;

      for (i = 0; i < iMax; ++i)
        {
          pChild = &pNode->getChild(i);

          if (pChild != NULL &&
              pChild->getPrefix() == prefix &&
              pChild->getName() == "protein" &&
              pChild->getAttributes().hasAttribute("id") &&
              pChild->getAttributes().hasAttribute("name"))
            {
              Protein prot;
              // we are only interested in the id and the type
              prot.mId = pChild->getAttributes().getValue("id");
              assert(!prot.mId.empty());
              prot.mName = pChild->getAttributes().getValue("name");
              assert(!prot.mName.empty());

              if (pChild->getAttributes().hasAttribute("type"))
                {
                  std::string type = pChild->getAttributes().getValue("type");
                  assert(!type.empty());
                  std::transform(type.begin(), type.end(), type.begin(), toupper);

                  if (type != "GENERIC")
                    {
                      SPECIES_CLASS cl = CCellDesignerImporter::classToEnum(type);

                      if (cl != UNDEFINED_CLASS)
                        {
                          prot.mType = cl;
                        }
                      else
                        {
                          result = false;
                        }
                    }
                }

              // parse the modifications
              const XMLNode* pModifications = CCellDesignerImporter::findChildNode(pChild, pChild->getPrefix(), "listOfModificationResidues", false);

              if (pModifications != NULL)
                {
                  unsigned int j = 0, jMax = pModifications->getNumChildren();
                  const XMLNode* pChild2 = NULL;

                  while (j < jMax && result == true)
                    {
                      pChild2 = &pModifications->getChild(j);
                      assert(pChild2 != NULL);

                      if (pChild2 != NULL &&
                          pChild2->getPrefix() == pModifications->getPrefix() &&
                          pChild2->getName() == "modificationResidue")
                        {
                          ProteinModification mod;
                          result = CCellDesignerImporter::parseProteinModification(pChild2, mod);

                          if (result == true)
                            {
                              prot.mModifications.push_back(mod);
                            }
                        }
                      else
                        {
                          result = false;
                        }

                      ++j;
                    }
                }

              if (result == true)
                {
                  this->mProteinInformationMap.insert(std::pair<std::string, Protein>(prot.mId, prot));
                }
            }
        }
    }

  return result;
}

/**
 * Tries to parse the protein modification in the given node and stores the data in the given
 * ProteinModification structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseProteinModification(const XMLNode* pNode, ProteinModification& mod)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getName() == "modificationResidue")
    {
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("id"))
        {
          // has an id
          mod.mId = attr.getValue("id");

          // optional: name and angle
          if (attr.hasAttribute("name"))
            {
              mod.mName = attr.getValue("name");
            }
          else
            {
              mod.mName = "";
            }

          if (attr.hasAttribute("angle"))
            {
              char** err = NULL;
              double v;
              std::string s = attr.getValue("angle");
              assert(!s.empty());
              v = strtod(s.c_str(), err);

              if (err == NULL || *err != s.c_str())
                {
                  mod.mAngle = v;
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              mod.mAngle = 0.0;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Tries to parse the compartment annotation in the given node and stores the data in the given
 * CompartmentAnnotation structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseCompartmentAnnotation(const XMLNode* pNode, CompartmentAnnotation& anno)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "extension")
    {
      // as far as I can tell from the spec, there should only
      // be a name node
      const XMLNode* pNameNode = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "name", false);

      if (pNameNode != NULL && pNameNode->getNumChildren() == 1 && pNameNode->getChild(0).isText())
        {
          anno.mName = pNameNode->getChild(0).getCharacters();
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}
/**
 * Tries to parse the species annotation in the given node and stores the data in the given
 * SpeciesAnnotation structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseSpeciesAnnotation(const XMLNode* pNode, SpeciesAnnotation& anno)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "extension")
    {
      // the annotation should contain
      // either a positionToCompartment element
      // or a complexSpecies element
      // additionally it should contain a speciesIdentity element
      // and a listOfCatalyzedReactions element
      // TODO we currently don't use the last one or the first choice
      // we are only interested in the information stored in the identity
      const XMLNode* pIdentityNode = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "speciesIdentity", false);

      if (pIdentityNode != NULL)
        {
          result = CCellDesignerImporter::parseSpeciesIdentity(pIdentityNode, anno.mIdentity);
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the node which represents a speciesIdentity node and fills the given SpeciesIdentity
 * structure with the data.
 * If the parsinf fails, false is returned.
 */
bool CCellDesignerImporter::parseSpeciesIdentity(const XMLNode* pNode, SpeciesIdentity& identity)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "speciesIdentity")
    {
      // find the class element
      // this decides which futher element we expect
      const XMLNode* pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "class", false);

      if (pChild != NULL &&
          pChild->getNumChildren() == 1 &&
          pChild->getChild(0).isText())
        {
          std::string cl = pChild->getChild(0).getCharacters();
          assert(!cl.empty());
          identity.mSpeciesClass = CCellDesignerImporter::classToEnum(cl);

          switch (identity.mSpeciesClass)
            {
              case ION_CLASS:
              case SIMPLE_MOLECULE_CLASS:
              case COMPLEX_CLASS:
                // we expect a name
              {
                const XMLNode* pNameNode = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "name", false);

                if (pNameNode != NULL && pNameNode->getNumChildren() == 1 && pNameNode->getChild(0).isText())
                  {
                    identity.mNameOrReference = pNameNode->getChild(0).getCharacters();
                  }
                else
                  {
                    result = false;
                  }
              }
              break;
              case PROTEIN_CLASS:
                // we expect a protein reference
              {
                const XMLNode* pNameNode = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "proteinReference", false);

                if (pNameNode != NULL && pNameNode->getNumChildren() == 1 && pNameNode->getChild(0).isText())
                  {
                    identity.mNameOrReference = pNameNode->getChild(0).getCharacters();
                  }
                else
                  {
                    result = false;
                  }
              }
              break;
              default:
                // we don't handle all other cases
                // for now
                identity.mNameOrReference = "";
                break;
            }
        }
      else
        {
          result = false;
        }

      // handle state
      pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "state", false);

      if (pChild != NULL)
        {
          result = CCellDesignerImporter::parseSpeciesState(pChild, identity.mState);
        }

    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the node which represents the state in a speciesIdentity node and fills the given SpeciesState
 * structure with the data.
 * If the parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseSpeciesState(const XMLNode* pNode, SpeciesState& state)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "state")
    {
      // find the listOfModifications element
      const XMLNode* pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "listOfModifications", false);

      if (pChild != NULL)
        {
          unsigned int i = 0, iMax = pChild->getNumChildren();
          const XMLNode* pChild2 = NULL;

          while (i < iMax && result == true)
            {
              pChild2 = &pChild->getChild(i);
              assert(pChild2 != NULL);

              if (pChild2 != NULL)
                {
                  SpeciesModification mod;
                  result = CCellDesignerImporter::parseSpeciesModification(pChild2, mod);

                  if (result == true)
                    {
                      state.mModifications.push_back(mod);
                    }
                }
              else
                {
                  result = false;
                }

              ++i;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the node which represents a modification ion a species node and fills the given SpeciesModification
 * structure with the data.
 * If the parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseSpeciesModification(const XMLNode* pNode, SpeciesModification& mod)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getName() == "modification")
    {
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("residue") &&
          attr.hasAttribute("state"))
        {
          mod.mResidue = attr.getValue("residue");
          assert(!mod.mResidue.empty());
          std::string s = attr.getValue("state");
          assert(!s.empty());
          mod.mType = CCellDesignerImporter::speciesModificationTypeToEnum(s);
          assert(mod.mType != UNDEFINED_MOD_TYPE);
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Searches for a child with a certain name and a certain prefix
 * in the tree based on pNode.
 * The first child that fits the name and the prefix or NULL is returned.
 * If recursive is true, the tree is searched recursively.
 */
const XMLNode* CCellDesignerImporter::findChildNode(const XMLNode* pNode, const std::string& prefix, const std::string& name, bool recursive)
{
  const XMLNode* pResult = NULL;

  if (pNode != NULL && !name.empty())
    {
      const XMLNode* pChild = NULL;
      unsigned int i, iMax = pNode->getNumChildren();

      for (i = 0; i < iMax && pResult == NULL; ++i)
        {
          pChild = &pNode->getChild(i);

          if (pChild != NULL && pChild->getPrefix() == prefix &&
              pChild->getName() == name)
            {
              pResult = pChild;
              break;
            }

          if (recursive && pChild != NULL && pChild->getNumChildren() > 0)
            {
              pResult = CCellDesignerImporter::findChildNode(pChild, prefix, name, recursive);
            }
        }
    }

  return pResult;
}

/**
 * Tries to parse the reaction annotation in the given node and stores the data in the given
 * ReactionAnnotation structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseReactionAnnotation(const XMLNode* pNode, ReactionAnnotation& ranno)
{
  bool result = true;

  if (pNode != NULL)
    {
      const XMLNode* pChild = NULL;

      // now come the mandatory elements
      // type element
      pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "reactionType");

      if (pChild != NULL)
        {
          if (pChild->getNumChildren() == 1 && pChild->getChild(0).isText())
            {
              std::string s = pChild->getChild(0).getCharacters();
              ranno.mType = CCellDesignerImporter::reactionTypeToEnum(s);

              // baseReactants
              pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "baseReactants");

              if (pChild != NULL)
                {
                  result = CCellDesignerImporter::parseReactionElements(pChild, ranno.mBaseReactants);

                  if (result == true)
                    {
                      // baseProducts
                      pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "baseProducts");

                      if (pChild != NULL)
                        {
                          result = CCellDesignerImporter::parseReactionElements(pChild, ranno.mBaseProducts);

                          if (result == true)
                            {
                              // connectScheme
                              pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "connectScheme");

                              if (pChild != NULL)
                                {
                                  result = CCellDesignerImporter::parseConnectScheme(pChild, ranno.mConnectScheme);

                                  if (result == true)
                                    {
                                      // line
                                      pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "line");

                                      if (pChild != NULL)
                                        {
                                          result = CCellDesignerImporter::parseLine(pChild, ranno.mLine);

                                          if (result == true)
                                            {
                                              // now we read the optional elements
                                              // name element (optional)
                                              pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "name");

                                              if (pChild != NULL)
                                                {
                                                  if (pChild->getNumChildren() == 1 && pChild->getChild(0).isText())
                                                    {
                                                      ranno.mName = pChild->getChild(0).getCharacters();
                                                    }
                                                }

                                              if (result == true)
                                                {
                                                  // listOfReactantLinks (optional)
                                                  pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "listOfReactantLinks");

                                                  if (pChild != NULL)
                                                    {
                                                      result = CCellDesignerImporter::parseExtraLinks(pChild, ranno.mReactantLinks);
                                                    }

                                                  if (result == true)
                                                    {
                                                      // listOfProductLinks (optional)
                                                      pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "listOfProductLinks");

                                                      if (pChild != NULL)
                                                        {
                                                          result = CCellDesignerImporter::parseExtraLinks(pChild, ranno.mProductLinks);
                                                        }

                                                      if (result == true)
                                                        {
                                                          // offset (optional)
                                                          pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "offset");

                                                          if (pChild != NULL)
                                                            {
                                                              // read the x and the y attribute
                                                              if (pChild->getAttributes().hasAttribute("x") && pChild->getAttributes().hasAttribute("y"))
                                                                {
                                                                  s = pChild->getAttributes().getValue("x");
                                                                  char** err = NULL;
                                                                  double v;
                                                                  v = strtod(s.c_str(), err);

                                                                  if (err == NULL || *err != s.c_str())
                                                                    {
                                                                      ranno.mOffset.setX(v);
                                                                      err = NULL;
                                                                      v = strtod(s.c_str(), err);

                                                                      if (err == NULL || *err != s.c_str())
                                                                        {
                                                                          ranno.mOffset.setY(v);
                                                                        }
                                                                      else
                                                                        {
                                                                          result = false;
                                                                        }
                                                                    }
                                                                  else
                                                                    {
                                                                      result = false;
                                                                    }
                                                                }
                                                            }

                                                          if (result == true)
                                                            {
                                                              // editPoints (optional)
                                                              pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "editPoints");

                                                              if (pChild != NULL)
                                                                {
                                                                  result = CCellDesignerImporter::parseEditPoints(pChild, ranno.mEditPoints);
                                                                }

                                                              if (result == true)
                                                                {
                                                                  // listOfModifications (optional)
                                                                  pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "listOfModification");

                                                                  if (pChild != NULL)
                                                                    {
                                                                      result = CCellDesignerImporter::parseReactionModifications(pChild, ranno.mModifications);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                      else
                                        {
                                          result = false;
                                        }
                                    }
                                }
                              else
                                {
                                  result = false;
                                }
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Converts the given reaction type string to the corresponding enum.
 * If there is no enum that corresponds to the string, UNDEFINED_RTYPE is returned.
 */
REACTION_TYPE CCellDesignerImporter::reactionTypeToEnum(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
  REACTION_TYPE result = UNDEFINED_RTYPE;

  if (s == "STATE_TRANSITION")
    {
      result = STATE_TRANSITION_RTYPE;
    }
  else if (s == "KNOWN_TRANSITION_OMITTED")
    {
      result = KNOWN_TRANSITION_OMITTED_RTYPE;
    }
  else if (s == "UNKNOWN_TRANSITION")
    {
      result = UNKNOWN_TRANSITION_RTYPE;
    }
  else if (s == "CATALYSIS")
    {
      result = CATALYSIS_RTYPE;
    }
  else if (s == "UNKNOWN_CATALYSIS")
    {
      result = UNKNOWN_CATALYSIS_RTYPE;
    }
  else if (s == "INHIBITION")
    {
      result = INHIBITION_RTYPE;
    }
  else if (s == "UNKNOWN_INHIBITION")
    {
      result = UNKNOWN_INHIBITION_RTYPE;
    }
  else if (s == "TRANSPORT")
    {
      result = TRANSPORT_RTYPE;
    }
  else if (s == "HETERODIMER_ASSOCIATION")
    {
      result = HETERODIMER_ASSOCIATION_RTYPE;
    }
  else if (s == "DISSOCIATION")
    {
      result = DISSOCIATION_RTYPE;
    }
  else if (s == "TRUNCATION")
    {
      result = TRUNCATION_RTYPE;
    }
  else if (s == "TRANSCRIPTIONAL_ACTIVATION")
    {
      result = TRANSCRIPTIONAL_ACTIVATION_RTYPE;
    }
  else if (s == "TRANSCRIPTIONAL_INHIBITION")
    {
      result = TRANSCRIPTIONAL_INHIBITION_RTYPE;
    }
  else if (s == "TRANSLATIONAL_ACTIVATION")
    {
      result = TRANSLATIONAL_ACTIVATION_RTYPE;
    }
  else if (s == "TRANSLATIONAL_INHIBITION")
    {
      result = TRANSLATIONAL_INHIBITION_RTYPE;
    }
  else if (s == "TRANSCRIPTION")
    {
      result = TRANSCRIPTION_RTYPE;
    }
  else if (s == "TRANSLATION")
    {
      result = TRANSLATION_RTYPE;
    }

  return result;
}


/**
 * Converts the given modification link type string to the corresponding enum.
 * If there is no enum that corresponds to the string, UNDEFINED_ML_TYPE is returned.
 */
MODIFICATION_LINK_TYPE CCellDesignerImporter::modificationLinkTypeToEnum(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
  MODIFICATION_LINK_TYPE result = UNDEFINED_ML_TYPE;

  if (s == "CATALYSIS")
    {
      result = CATALYSIS_ML_TYPE;
    }
  else if (s == "UNKNOWN_CATALYSIS")
    {
      result = UNKNOWN_CATALYSIS_ML_TYPE;
    }
  else if (s == "INHIBITION")
    {
      result = INHIBITION_ML_TYPE;
    }
  else if (s == "UNKNOWN_INHIBITION")
    {
      result = UNKNOWN_INHIBITION_ML_TYPE;
    }
  else if (s == "TRANSPORT")
    {
      result = TRANSPORT_ML_TYPE;
    }
  else if (s == "HETERODIMER_ASSOCIATION")
    {
      result = HETERODIMER_ASSOCIATION_ML_TYPE;
    }
  else if (s == "TRANSCRIPTIONAL_ACTIVATION")
    {
      result = TRANSCRIPTIONAL_ACTIVATION_ML_TYPE;
    }
  else if (s == "TRANSCRIPTIONAL_INHIBITION")
    {
      result = TRANSCRIPTIONAL_INHIBITION_ML_TYPE;
    }
  else if (s == "TRANSLATIONAL_ACTIVATION")
    {
      result = TRANSLATIONAL_ACTIVATION_ML_TYPE;
    }
  else if (s == "TRANSLATIONAL_INHIBITION")
    {
      result = TRANSLATIONAL_INHIBITION_ML_TYPE;
    }
  else if (s == "PHYSICAL_STIMULATION")
    {
      result = PHYSICAL_STIMULATION_ML_TYPE;
    }
  else if (s == "MODULATION")
    {
      result = MODULATION_ML_TYPE;
    }
  else if (s == "TRIGGER")
    {
      result = TRIGGER_ML_TYPE;
    }
  else if (s == "BOOLEAN_LOGIC_GATE_AND")
    {
      result = BOOLEAN_LOGIC_GATE_AND_ML_TYPE;
    }
  else if (s == "BOOLEAN_LOGIC_GATE_OR")
    {
      result = BOOLEAN_LOGIC_GATE_OR_ML_TYPE;
    }
  else if (s == "BOOLEAN_LOGIC_GATE_NOT")
    {
      result = BOOLEAN_LOGIC_GATE_NOT_ML_TYPE;
    }
  else if (s == "BOOLEAN_LOGIC_GATE_UNKNOWN")
    {
      result = BOOLEAN_LOGIC_GATE_UNKNOWN_ML_TYPE;
    }

  return result;
}

/**
 * Converts the given modification type string to the corresponding enum.
 * If there is no enum that corresponds to the string, UNDEFINED_MTYPE is returned.
 */
MODIFICATION_TYPE CCellDesignerImporter::modificationTypeToEnum(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
  MODIFICATION_TYPE result = UNDEFINED_MTYPE;

  if (s == "CATALYSIS")
    {
      result = CATALYSIS_MTYPE;
    }
  else if (s == "UNKNOWN_CATALYSIS")
    {
      result = UNKNOWN_CATALYSIS_MTYPE;
    }
  else if (s == "INHIBITION")
    {
      result = INHIBITION_MTYPE;
    }
  else if (s == "UNKNOWN_INHIBITION")
    {
      result = UNKNOWN_INHIBITION_MTYPE;
    }
  else if (s == "TRANSPORT")
    {
      result = TRANSPORT_MTYPE;
    }
  else if (s == "HETERODIMER_ASSOCIATION")
    {
      result = HETERODIMER_ASSOCIATION_MTYPE;
    }
  else if (s == "TRANSCRIPTIONAL_ACTIVATION")
    {
      result = TRANSCRIPTIONAL_ACTIVATION_MTYPE;
    }
  else if (s == "TRANSCRIPTIONAL_INHIBITION")
    {
      result = TRANSCRIPTIONAL_INHIBITION_MTYPE;
    }
  else if (s == "TRANSLATIONAL_ACTIVATION")
    {
      result = TRANSLATIONAL_ACTIVATION_MTYPE;
    }
  else if (s == "TRANSLATIONAL_INHIBITION")
    {
      result = TRANSLATIONAL_INHIBITION_MTYPE;
    }
  else if (s == "PHYSICAL_STIMULATION")
    {
      result = PHYSICAL_STIMULATION_MTYPE;
    }
  else if (s == "MODULATION")
    {
      result = MODULATION_MTYPE;
    }

  return result;
}

/**
 * Converts the given position to compartment string to the corresponding enum.
 * If there is no enum that corresponds to the string, UNDEFINED_POSITION is returned.
 */
POSITION_TO_COMPARTMENT CCellDesignerImporter::positionToCompartmentToEnum(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
  POSITION_TO_COMPARTMENT result = UNDEFINED_POSITION;

  if (s == "OUTER_SURFACE")
    {
      result = OUTER_SURFACE;
    }
  else if (s == "TRANSMEMBRANE")
    {
      result = TRANSMEMBRANE;
    }
  else if (s == "INNER_SURFACE")
    {
      result = INNER_SURFACE;
    }
  else if (s == "INSIDE")
    {
      result = INSIDE;
    }
  else if (s == "INSIDE_MEMBRANE")
    {
      result = INSIDE_MEMBRANE;
    }

  return result;
}

/**
 * Converts the given connection policy string to the corresponding enum.
 * If there is no enum that corresponds to the string, POLICY_UNDEFINED is returned.
 */
CONNECTION_POLICY CCellDesignerImporter::connectionPolicyToEnum(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
  CONNECTION_POLICY result = POLICY_UNDEFINED;

  if (s == "DIRECT")
    {
      result = POLICY_DIRECT;
    }
  else if (s == "SQUARE")
    {
      result = POLICY_SQUARE;
    }

  return result;
}

/**
 * Converts the given direction string to the corresponding enum.
 * If there is no enum that corresponds to the string, DIRECTION_UNDEFINED is returned.
 */
DIRECTION_VALUE CCellDesignerImporter::directionToEnum(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
  DIRECTION_VALUE result = DIRECTION_UNDEFINED;

  if (s == "UNKNOWN")
    {
      result = DIRECTION_UNKNOWN;
    }
  else if (s == "HORIZONTAL")
    {
      result = DIRECTION_HORIZONTAL;
    }
  else if (s == "VERTICAL")
    {
      result = DIRECTION_VERTICAL;
    }

  return result;
}

/**
 * Converts the given position string to an enum.
 */
POSITION CCellDesignerImporter::positionToEnum(std::string pos)
{
  std::transform(pos.begin(), pos.end(), pos.begin(), toupper);
  POSITION position = POSITION_UNDEFINED;

  if (pos == "N")
    {
      position = POSITION_N;
    }
  else if (pos == "NNE")
    {
      position = POSITION_NNE;
    }
  else if (pos == "NE")
    {
      position = POSITION_NE;
    }
  else if (pos == "ENE")
    {
      position = POSITION_ENE;
    }
  else if (pos == "E")
    {
      position = POSITION_E;
    }
  else if (pos == "ESE")
    {
      position = POSITION_ESE;
    }
  else if (pos == "SE")
    {
      position = POSITION_SE;
    }
  else if (pos == "SSE")
    {
      position = POSITION_SSE;
    }
  else if (pos == "S")
    {
      position = POSITION_S;
    }
  else if (pos == "SSW")
    {
      position = POSITION_SSW;
    }
  else if (pos == "SW")
    {
      position = POSITION_SW;
    }
  else if (pos == "WSW")
    {
      position = POSITION_WSW;
    }
  else if (pos == "W")
    {
      position = POSITION_W;
    }
  else if (pos == "WNW")
    {
      position = POSITION_WNW;
    }
  else if (pos == "NW")
    {
      position = POSITION_NW;
    }
  else if (pos == "NNW")
    {
      position = POSITION_NNW;
    }

  return position;
}

/**
 * Converts the given paint scheme string to the correspnding PAINT_SCHEME enum value.
 * If no enum is found, PAINT_UNDEFINED is returned.
 */
PAINT_SCHEME CCellDesignerImporter::paintSchemeToEnum(std::string s)
{
  PAINT_SCHEME result = PAINT_UNDEFINED;
  std::transform(s.begin(), s.end(), s.begin(), toupper);

  if (s == "COLOR")
    {
      result = PAINT_COLOR;
    }
  else if (s == "GRADIENT")
    {
      result = PAINT_GRADIENT;
    }

  return result;
}



/**
 * Converts the given class string to the correspnding SPECIES_CLASS enum value.
 * If no enum is found, UNDEFINED is returned.
 */
SPECIES_CLASS CCellDesignerImporter::classToEnum(std::string cl)
{
  std::transform(cl.begin(), cl.end(), cl.begin(), toupper);
  SPECIES_CLASS result = UNDEFINED_CLASS;

  if (cl == "ION")
    {
      result = ION_CLASS;
    }
  else if (cl == "SIMPLE_MOLECULE")
    {
      result = SIMPLE_MOLECULE_CLASS;
    }
  else if (cl == "PROTEIN")
    {
      result = PROTEIN_CLASS;
    }
  else if (cl == "GENE")
    {
      result = GENE_CLASS;
    }
  else if (cl == "RNA")
    {
      result = RNA_CLASS;
    }
  else if (cl == "ANTISENSE_RNA")
    {
      result = ANTISENSE_RNA_CLASS;
    }
  else if (cl == "PHENOTYPE")
    {
      result = PHENOTYPE_CLASS;
    }
  else if (cl == "DRUG")
    {
      result = DRUG_CLASS;
    }
  else if (cl == "UNKNOWN")
    {
      result = UNKNOWN_CLASS;
    }
  else if (cl == "COMPLEX")
    {
      result = COMPLEX_CLASS;
    }
  else if (cl == "SQUARE")
    {
      result = SQUARE_CLASS;
    }
  else if (cl == "OVAL")
    {
      result = OVAL_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_NORTHWEST")
    {
      result = SQUARE_NW_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_NORTHEAST")
    {
      result = SQUARE_NE_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_SOUTHWEST")
    {
      result = SQUARE_SW_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_SOUTHEAST")
    {
      result = SQUARE_SE_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_NORTH")
    {
      result = SQUARE_N_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_EAST")
    {
      result = SQUARE_E_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_WEST")
    {
      result = SQUARE_W_CLASS;
    }
  else if (cl == "SQUARE_CLOSEUP_SOUTH")
    {
      result = SQUARE_S_CLASS;
    }
  else if (cl == "DEGRADED")
    {
      result = DEGRADED_CLASS;
    }
  else if (cl == "RECEPTOR")
    {
      result = RECEPTOR_CLASS;
    }
  else if (cl == "TRUNCATED")
    {
      result = TRUNCATED_CLASS;
    }
  else if (cl == "ION_CHANNEL")
    {
      result = CHANNEL_CLASS;
    }

  return result;
}

/**
 * Tries to parse the reaction elements (baseReactants or baseProducts) in the given
 * node and stores the data in the given ReactionAnnotation structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseReactionElements(const XMLNode* pNode, std::vector<LinkTarget>& elements)
{
  bool result = true;

  if (pNode != NULL &&
      (pNode->getName() == "baseReactants" ||
       pNode->getName() == "baseProducts")
     )
    {
      // elements of either baseReactant or baseProduct
      // each element has the attributes alias and species
      // as well as a linkAnchor element (which sometimes is missing)
      unsigned int i, iMax = pNode->getNumChildren();
      const XMLNode* pChild = NULL;
      elements.clear();

      for (i = 0; i < iMax && result == true; ++i)
        {
          pChild = &pNode->getChild(i);

          if (pChild != NULL &&
              pChild->getPrefix() == pNode->getPrefix() &&
              (pChild->getName() == "baseReactant" ||
               pChild->getName() == "baseProduct")
             )
            {
              LinkTarget l;
              result = CCellDesignerImporter::parseLinkTarget(pChild, l);
              elements.push_back(l);
            }
        }

    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the connection scheme in the given node and stores the data in the given
 * ConnectionScheme structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseConnectScheme(const XMLNode* pNode, ConnectScheme& scheme)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "connectScheme")
    {
      // attributes
      // policy
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("connectPolicy"))
        {
          std::string s = attr.getValue("connectPolicy");
          scheme.mPolicy = CCellDesignerImporter::connectionPolicyToEnum(s);

          if (scheme.mPolicy != POLICY_UNDEFINED)
            {
              // reactangleIndex (optional)
              if (attr.hasAttribute("rectangleIndex"))
                {
                  s = attr.getValue("rectangleIndex");
                  char** err = NULL;
                  long val = strtol(s.c_str(), err, 10);

                  if (!err || *err != s.c_str())
                    {
                      scheme.mRectangleIndex = val;
                    }
                  else
                    {
                      result = false;
                    }
                }

              // children
              const XMLNode* pDirections = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "listOfLineDirection");

              if (pDirections != NULL)
                {
                  // list of lineDirectionElements
                  unsigned int i, iMax = pDirections->getNumChildren();
                  const XMLNode* pChild = NULL;

                  for (i = 0; i < iMax && result == true; ++i)
                    {
                      pChild = &pDirections->getChild(i);

                      if (pChild != NULL &&
                          pChild->getPrefix() == pDirections->getPrefix() &&
                          pChild->getName() == "lineDirection")
                        {
                          LineDirection l;
                          result = CCellDesignerImporter::parseLineDirection(pChild, l);
                          scheme.mLineDirections.push_back(l);
                        }
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the line data in the given node and stores the data in the given
 * Line structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseLine(const XMLNode* pNode, Line& line)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "line")
    {
      // the line element has two attributes
      // color and width
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("color") && attr.hasAttribute("width"))
        {
          std::string s = attr.getValue("color");
          line.mColor = s;
          s = attr.getValue("width");
          char** err = NULL;
          double dbl = strtod(s.c_str(), err);

          if (!err || *err != s.c_str())
            {
              line.mWidth = dbl;
            }
          else
            {
              result = false;
            }

          // the lines with reactant and productLinks
          // might also have a type
          if (attr.hasAttribute("type"))
            {
              s = attr.getValue("type");
              std::transform(s.begin(), s.end(), s.begin(), toupper);

              if (s == "CURVE")
                {
                  line.mCurve = true;
                }
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the extra reactant links in the given node and stores the data in the given
 * vector of ReactantLinks structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseExtraLinks(const XMLNode* pNode, std::vector<ReactantLink>& rlinks)
{
  bool result = true;

  if (pNode != NULL &&
      (pNode->getName() == "listOfReactantLinks" ||
       pNode->getName() == "listOfProductLinks")
     )
    {
      // each child is either a reactantLink or a productLink
      // which have the same structure
      unsigned int i, iMax = pNode->getNumChildren();
      const XMLNode* pChild = NULL;
      rlinks.clear();

      for (i = 0; i < iMax && result == true; ++i)
        {
          pChild = &pNode->getChild(i);

          if (pChild != NULL &&
              pChild->getPrefix() == pNode->getPrefix() &&
              (pChild->getName() == "reactantLink" ||
               pChild->getName() == "productLink")
             )
            {
              ReactantLink l;
              result = CCellDesignerImporter::parseExtraLink(pChild, l);
              rlinks.push_back(l);
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the edit points in the given node and stores the data in the given
 * vector of Points.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseEditPoints(const XMLNode* pNode, EditPoints& editpoints)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "editPoints")
    {
      // there can be attributes num0, num1 and num2
      // as well as tShapeIndex and omittedShapeIndex
      // all of these are optional
      if (pNode->getNumChildren() == 1 && pNode->getChild(0).isText())
        {
          std::string s = pNode->getChild(0).getCharacters();
          // the rest is a text child element that contains the string with the points
          result = CCellDesignerImporter::parsePointsString(s, editpoints.mPoints);
          char** err = NULL;
          const XMLAttributes& attr = pNode->getAttributes();
          long val = 0;

          if (result && attr.hasAttribute("num0"))
            {
              s = attr.getValue("num0");
              err = NULL;
              val = strtol(s.c_str(), err, 10);

              if (!err || *err != s.c_str())
                {
                  editpoints.mNum0 = val;
                }
              else
                {
                  result = false;
                }
            }

          if (result && attr.hasAttribute("num1"))
            {
              s = attr.getValue("num1");
              err = NULL;
              val = strtol(s.c_str(), err, 10);

              if (!err || *err != s.c_str())
                {
                  editpoints.mNum1 = val;
                }
              else
                {
                  result = false;
                }
            }

          if (result && attr.hasAttribute("num2"))
            {
              s = attr.getValue("num2");
              err = NULL;
              val = strtol(s.c_str(), err, 10);

              if (!err || *err != s.c_str())
                {
                  editpoints.mNum2 = val;
                }
              else
                {
                  result = false;
                }
            }

          if (result && attr.hasAttribute("tShapeIndex"))
            {
              s = attr.getValue("tShapeIndex");
              err = NULL;
              val = strtol(s.c_str(), err, 10);

              if (!err || *err != s.c_str())
                {
                  editpoints.mTShapeIndex = val;
                }
              else
                {
                  result = false;
                }
            }

          if (result && attr.hasAttribute("omittedShapeIndex"))
            {
              s = attr.getValue("omittedShapeIndex");
              err = NULL;
              val = strtol(s.c_str(), err, 10);

              if (!err || *err != s.c_str())
                {
                  editpoints.mOmittedShapeIndex = val;
                }
              else
                {
                  result = false;
                }
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the reaction modifications in the given node and stores the data in the given
 * vector of ReactionModifications.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseReactionModifications(const XMLNode* pNode, std::vector<ReactionModification>& rmods)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "listOfModification")
    {
      unsigned int i, iMax = pNode->getNumChildren();
      const XMLNode* pChild = NULL;

      for (i = 0; i < iMax && result == true; ++i)
        {
          pChild = &pNode->getChild(i);

          if (pChild != NULL &&
              pChild->getPrefix() == pNode->getPrefix() &&
              pChild->getName() == "modification")
            {
              ReactionModification rmod;
              result = CCellDesignerImporter::parseReactionModification(pChild, rmod);
              rmods.push_back(rmod);
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the link target in the given node and stores the data in the given
 * vector of LinkTarget structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseLinkTarget(const XMLNode* pNode, LinkTarget& l)
{
  bool result = true;

  if (pNode != NULL &&
      (pNode->getName() == "baseReactant" ||
       pNode->getName() == "baseProduct" ||
       pNode->getName() == "linkTarget")
     )
    {
      // alias and species attributes are mandatory
      // a linkAnchor child seems to be optional
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("alias") && attr.hasAttribute("species"))
        {
          std::string s = attr.getValue("alias");
          l.mAlias = s;
          s = attr.getValue("species");
          l.mSpecies = s;
          const XMLNode* pAnchor = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "linkAnchor", false);

          if (pAnchor != NULL)
            {
              if (pAnchor->getAttributes().hasAttribute("position"))
                {
                  s = pAnchor->getAttributes().getValue("position");
                  l.mPosition = CCellDesignerImporter::positionToEnum(s);

                  if (l.mPosition == POSITION_UNDEFINED)
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the line direction in the given node and stores the data in the given
 * vector of LineDirection structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseLineDirection(const XMLNode* pNode, LineDirection& d)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getName() == "lineDirection")
    {
      // attributesd index and value are mandatory
      // attribute arm is optional
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("index") && attr.hasAttribute("value"))
        {
          std::string s = attr.getValue("index");
          char** err = NULL;
          long val = strtol(s.c_str(), err, 10);

          if (!err || *err != s.c_str())
            {
              d.mIndex = val;
              err = NULL;
              s = attr.getValue("value");
              d.mValue = CCellDesignerImporter::directionToEnum(s);

              if (d.mValue != DIRECTION_UNDEFINED)
                {
                  if (attr.hasAttribute("arm"))
                    {
                      s = attr.getValue("arm");
                      err = NULL;
                      val = strtol(s.c_str(), err, 10);

                      if (!err || *err != s.c_str())
                        {
                          d.mArm = val;
                        }
                      else
                        {
                          result = false;
                        }
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }

  return result;
}

/**
 * Tries to parse the wreactant link in the given node and stores the data in the given
 * vector of ReactionLink structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseExtraLink(const XMLNode* pNode, ReactantLink& l)
{
  bool result = true;

  if (pNode != NULL &&
      (pNode->getName() == "productLink" ||
       pNode->getName() == "reactantLink")
     )
    {
      // attributes alias , reactant and targetLineIndex are mandatory
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("alias") &&
          (attr.hasAttribute("reactant") ||
           attr.hasAttribute("product")) &&
          attr.hasAttribute("targetLineIndex"))
        {
          std::string s = attr.getValue("alias");
          l.mAlias = s;

          if (attr.hasAttribute("reactant"))
            {
              s = attr.getValue("reactant");
            }
          else
            {
              s = attr.getValue("product");
            }

          l.mReactant = s;
          s = attr.getValue("targetLineIndex");
          std::vector<std::string> parts;
          // targetLineIndex has two number split by a ','
          result = CCellDesignerImporter::splitString(s, parts, ",");

          if (result && parts.size() == 2)
            {
              char** err = NULL;
              // we are only interested in the second value because for CellDesigner 4.0
              // and higher, the first value is always -1
              long val = strtol(parts[1].c_str(), err, 10);

              if (!err || *err != s.c_str())
                {
                  l.mTargetLineIndex = val;
                  // child element line is mandatory
                  const XMLNode* pLineNode = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "line", false);

                  if (pLineNode != NULL)
                    {
                      result = CCellDesignerImporter::parseLine(pLineNode, l.mLine);

                      // child element linkAnchor is optional
                      if (result == true)
                        {
                          pLineNode = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "linkAnchor", false);

                          if (pLineNode != NULL && pLineNode->getAttributes().hasAttribute("position"))
                            {
                              l.mPosition = CCellDesignerImporter::positionToEnum(pLineNode->getAttributes().getValue("position"));

                              if (l.mPosition == POSITION_UNDEFINED)
                                {
                                  result = false;
                                }
                            }
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the reaction modification in the given node and stores the data in the given
 * ReactionModification structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseReactionModification(const XMLNode* pNode, ReactionModification& mod)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getName() == "modification")
    {
      // mandatory attributes: alias, modifiers, type, targetLineIndex
      // optional attributes: editPoints, num0, num1, num2, modificationType
      //                      offsetX,offsetY
      // optional children: connectScheme, linkTarget and line

      // first we handle the mandatory attributes
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("aliases") &&
          attr.hasAttribute("modifiers") &&
          attr.hasAttribute("type") &&
          attr.hasAttribute("targetLineIndex"))
        {
          std::string s = attr.getValue("aliases");
          result = CCellDesignerImporter::splitString(s, mod.mAliases, ",");

          if (result == true)
            {
              s = attr.getValue("modifiers");
              result = CCellDesignerImporter::splitString(s, mod.mModifiers, ",");

              if (result == true)
                {
                  s = attr.getValue("type");
                  mod.mType = CCellDesignerImporter::modificationLinkTypeToEnum(s);

                  if (mod.mType != UNDEFINED_ML_TYPE)
                    {
                      s = attr.getValue("targetLineIndex");
                      // the targetLineIndex attribute is a comma
                      // separated list of two int values
                      // for CellDesigner 4.0 and above the first
                      // value is always -1, so we ignore it
                      std::vector<std::string> tmp;
                      result = CCellDesignerImporter::splitString(s, tmp, ",");

                      if (result == true && tmp.size() == 2)
                        {
                          char** err = NULL;
                          long val = strtol(tmp[1].c_str(), err, 10);

                          if (!err || *err != tmp[1].c_str())
                            {
                              mod.mTargetLineIndex = val;
                            }
                          else
                            {
                              result = false;
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
            }

          if (result == true)
            {
              // optional attributes: editPoints, num0, num1, num2, modificationType
              //                      offsetX,offsetY
              char** err = NULL;
              long val;
              double dval;

              if (attr.hasAttribute("editPoints"))
                {
                  s = attr.getValue("editPoints");
                  result = CCellDesignerImporter::parsePointsString(s, mod.mEditPoints.mPoints);
                }

              if (result == true && attr.hasAttribute("num0"))
                {
                  s = attr.getValue("num0");
                  err = NULL;
                  val = strtol(s.c_str(), err, 10);

                  if (!err || *err != s.c_str())
                    {
                      mod.mNum0 = val;
                    }
                  else
                    {
                      result = false;
                    }
                }

              if (result == true && attr.hasAttribute("num1"))
                {
                  s = attr.getValue("num1");
                  err = NULL;
                  val = strtol(s.c_str(), err, 10);

                  if (!err || *err != s.c_str())
                    {
                      mod.mNum1 = val;
                    }
                  else
                    {
                      result = false;
                    }
                }

              if (result == true && attr.hasAttribute("num2"))
                {
                  s = attr.getValue("num2");
                  err = NULL;
                  val = strtol(s.c_str(), err, 10);

                  if (!err || *err != s.c_str())
                    {
                      mod.mNum2 = val;
                    }
                  else
                    {
                      result = false;
                    }
                }

              if (result == true && attr.hasAttribute("modificationType"))
                {
                  s = attr.getValue("modificationType");
                  mod.mModType = CCellDesignerImporter::modificationTypeToEnum(s);

                  if (mod.mModType == UNDEFINED_MTYPE)
                    {
                      result = false;
                    }
                }

              if (result == true && attr.hasAttribute("offsetX"))
                {
                  s = attr.getValue("offsetX");
                  err = NULL;
                  dval = strtod(s.c_str(), err);

                  if (!err || *err != s.c_str())
                    {
                      mod.mOffset.setX(dval);
                    }
                  else
                    {
                      result = false;
                    }
                }

              if (result == true && attr.hasAttribute("offsetY"))
                {
                  s = attr.getValue("offsetY");
                  err = NULL;
                  dval = strtod(s.c_str(), err);

                  if (!err || *err != s.c_str())
                    {
                      mod.mOffset.setY(dval);
                    }
                  else
                    {
                      result = false;
                    }
                }
            }

          if (result == true)
            {
              // optional children: connectScheme, linkTarget and line
              const XMLNode* pNode2 = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "line", false);

              if (pNode2 != NULL)
                {
                  result = CCellDesignerImporter::parseLine(pNode2, mod.mLine);
                }

              if (result == true)
                {
                  pNode2 = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "connectScheme", false);

                  if (pNode2 != NULL)
                    {
                      result = CCellDesignerImporter::parseConnectScheme(pNode2, mod.mConnectScheme);
                    }
                }

              if (result == true)
                {
                  // there can be several linkTarget elements
                  unsigned int i, iMax = pNode->getNumChildren();
                  mod.mLinkTargets.clear();

                  for (i = 0; i < iMax && result == true; ++i)
                    {
                      pNode2 = &pNode->getChild(i);

                      if (pNode2 != NULL &&
                          pNode2->getPrefix() == pNode->getPrefix() &&
                          pNode2->getName() == "linkTarget")
                        {
                          LinkTarget l;
                          result = CCellDesignerImporter::parseLinkTarget(pNode2, l);
                          mod.mLinkTargets.push_back(l);
                        }
                    }
                }

            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Tries to parse the 2D points in the given string and stores the data in the given
 * vector of Points.
 * The points vector is cleared by the method.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parsePointsString(const std::string& s, std::vector<Point>& points)
{
  bool result = true;
  // first we need to split the string at the whitespaces
  std::string splitChars = " \n\t\r";
  std::vector<std::string> parts;
  result = CCellDesignerImporter::splitString(s, parts, splitChars);

  if (result == true)
    {
      points.clear();
      std::vector<std::string>::const_iterator it = parts.begin(), endit = parts.end();
      std::vector<std::string> tmp;
      std::string splitter(",");
      char** err;
      double dbl;
      Point p(new LayoutPkgNamespaces());

      while (it != endit && result == true)
        {
          // now we have to split the string at the komma
          tmp.clear();
          result = CCellDesignerImporter::splitString(*it, tmp, splitter);

          if (result == true)
            {
              if (tmp.size() == 2)
                {
                  err = NULL;
                  dbl = strtod(tmp[0].c_str(), err);

                  if (!err || *err != tmp[0].c_str())
                    {
                      p.setX(dbl);
                      err = NULL;
                      dbl = strtod(tmp[1].c_str(), err);

                      if (!err || *err != tmp[0].c_str())
                        {
                          p.setY(dbl);
                          points.push_back(p);
                        }
                      else
                        {
                          result = false;
                        }

                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }

          ++it;
        }
    }

  return result;
}


/**
 * Splits the given string at each character occurs in splitChars.
 * The parts generated are stored in the given vector.
 * The vector is cleared by the method.
 * If something goes wrong false is returned.
 */
bool CCellDesignerImporter::splitString(const std::string& s, std::vector<std::string>& parts, const std::string& splitChars)
{
  bool result = true;
  parts.clear();

  if (splitChars.empty())
    {
      parts.push_back(s);
    }
  else
    {
      size_t pos = 0;
      size_t next = s.find_first_of(splitChars, pos);

      while (next != std::string::npos)
        {
          // add the substring to parts
          parts.push_back(s.substr(pos, next - pos));
          pos = next;

          // step after the found character
          while (splitChars.find(s[pos]) != std::string::npos)
            {
              ++pos;
            }

          if (pos < s.size())
            {
              next = s.find_first_of(splitChars, pos);
            }
          else
            {
              next = std::string::npos;
            }
        }

      next = s.find_last_of(splitChars);

      if (next < pos || next == std::string::npos)
        {
          parts.push_back(s.substr(pos, s.size() - pos));
        }
    }

  return result;
}

/**
 * Parses the data in the given node which represents a compartment alias
 * and stores it in the given CompartmentAlias structure.
 * The last argument is the dimensions of the layout.
 * This is needed to calculate the bounds for compartments that only specify a point
 * and a class.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseCompartmentAlias(const XMLNode* pNode, CompartmentAlias& ca, const Dimensions& ld)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "compartmentAlias")
    {
      // attributes are id, compartment
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("id") && attr.hasAttribute("compartment"))
        {
          ca.mId = attr.getValue("id");
          ca.mCompartment = attr.getValue("compartment");
        }
      else
        {
          result = false;
        }

      if (result == true)
        {
          const XMLNode* pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "class", false);

          // we have the class element
          if (pChild != NULL && pChild->getNumChildren() == 1 && pChild->getChild(0).isText())
            {
              ca.mClass = CCellDesignerImporter::classToEnum(pChild->getChild(0).getCharacters());

              if (ca.mClass != UNDEFINED_CLASS)
                {
                  // the bounds element or the point element
                  pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "bounds", false);

                  if (pChild != NULL)
                    {
                      result = CCellDesignerImporter::parseBounds(pChild, ca.mBounds);
                    }
                  else
                    {
                      pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "point", false);

                      if (pChild != NULL)
                        {
                          if (pChild->getAttributes().hasAttribute("x") && pChild->getAttributes().hasAttribute("y"))
                            {
                              Point tmp(new LayoutPkgNamespaces());
                              result = CCellDesignerImporter::parsePoint(pChild, tmp);

                              if (result == true)
                                {
                                  // we have to check the class of the compartment alias to calculate the correct bounds
                                  // we should actually do this when we parse the element
                                  switch (ca.mClass)
                                    {
                                      case SQUARE_NW_CLASS:
                                        // the point determines the north western point of the compartment
                                        // so the compartment fills the space from that point to the lower right
                                        // corner of the layout
                                        ca.mBounds.setX(tmp.x());
                                        ca.mBounds.setY(tmp.y());
                                        ca.mBounds.setWidth(ld.getWidth() - tmp.x());
                                        ca.mBounds.setHeight(ld.getHeight() - tmp.y());
                                        break;
                                      case SQUARE_NE_CLASS:
                                        // the point determines the north eastern point of the compartment
                                        // so the compartment fills the space from that point to the lower left
                                        // corner of the layout
                                        ca.mBounds.setX(0.0);
                                        ca.mBounds.setY(tmp.y());
                                        ca.mBounds.setWidth(tmp.x());
                                        ca.mBounds.setHeight(ld.getHeight() - tmp.y());
                                        break;
                                      case SQUARE_SW_CLASS:
                                        // the point determines the south western point of the compartment
                                        // so the compartment fills the space from that point to the upper right
                                        // corner of the layout
                                        ca.mBounds.setX(tmp.x());
                                        ca.mBounds.setY(0.0);
                                        ca.mBounds.setWidth(ld.getWidth() - tmp.x());
                                        ca.mBounds.setHeight(tmp.y());
                                        break;
                                      case SQUARE_SE_CLASS:
                                        // the point determines the southern eastern point of the compartment
                                        // so the compartment fills the space from that point to the upper left
                                        // corner of the layout
                                        ca.mBounds.setX(0.0);
                                        ca.mBounds.setY(0.0);
                                        ca.mBounds.setWidth(tmp.x());
                                        ca.mBounds.setHeight(tmp.y());
                                        break;
                                      case SQUARE_N_CLASS:
                                        // the compartment fills the lower part of the layout up to the
                                        // y value in the given point
                                        ca.mBounds.setX(0.0);
                                        ca.mBounds.setY(tmp.y());
                                        ca.mBounds.setWidth(ld.getWidth());
                                        ca.mBounds.setHeight(ld.getHeight() - tmp.y());
                                        break;
                                      case SQUARE_E_CLASS:
                                        // the compartment fills the left part of the layout up to the
                                        // y value in the given point
                                        ca.mBounds.setX(0.0);
                                        ca.mBounds.setY(0.0);
                                        ca.mBounds.setWidth(tmp.x());
                                        ca.mBounds.setHeight(ld.getHeight());
                                        break;
                                      case SQUARE_W_CLASS:
                                        // the compartment fills the right part of the layout up to the
                                        // y value in the given point
                                        ca.mBounds.setX(tmp.x());
                                        ca.mBounds.setY(0.0);
                                        ca.mBounds.setWidth(ld.getWidth() - tmp.x());
                                        ca.mBounds.setHeight(ld.getHeight());
                                        break;
                                      case SQUARE_S_CLASS:
                                        // the compartment fills the upper part of the layout up to the
                                        // y value in the given point
                                        ca.mBounds.setX(0.0);
                                        ca.mBounds.setY(0.0);
                                        ca.mBounds.setWidth(ld.getWidth());
                                        ca.mBounds.setHeight(tmp.y());
                                        break;
                                      default:
                                        result = false;
                                        break;
                                    }
                                }
                            }
                          else
                            {
                              result = false;
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }

                  if (result == true)
                    {
                      // we have the namePoint
                      pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "namePoint", false);

                      if (pChild != NULL)
                        {
                          result = CCellDesignerImporter::parsePoint(pChild, ca.mNamePoint);
                        }
                      else
                        {
                          result = false;
                        }

                      if (result == true)
                        {
                          // we have the double line
                          pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "doubleLine", false);

                          if (pChild != NULL && CCellDesignerImporter::parseDoubleLine(pChild, ca.mDoubleLine) == true)
                            {
                              // we have the paint
                              pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "paint", false);

                              if (pChild != NULL && CCellDesignerImporter::parsePaint(pChild, ca.mPaint) == true)
                                {
                                  // and we might have a font element with a size attribute that is not describes in the spec
                                  pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "font", false);

                                  if (pChild != NULL && pChild->getAttributes().hasAttribute("size"))
                                    {
                                      std::string s = pChild->getAttributes().getValue("size");
                                      char** err = NULL;
                                      double dbl = strtod(s.c_str(), err);

                                      if (!err || *err != s.c_str())
                                        {
                                          ca.mFontSize = dbl;
                                        }
                                      else
                                        {
                                          result = false;
                                        }
                                    }
                                }
                              else
                                {
                                  result = false;
                                }
                            }
                          else
                            {
                              result = false;
                            }
                        }
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the data in the given node which represents a species
 * (or ComplexSpecies) alias
 * and stores it in the given SpeciesAlias structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseSpeciesAlias(const XMLNode* pNode, SpeciesAlias& sa)
{
  bool result = true;

  if (pNode != NULL &&
      (pNode->getName() == "speciesAlias" ||
       pNode->getName() == "complexSpeciesAlias")
     )
    {
      if (pNode->getName() == "complexSpeciesAlias")
        {
          sa.mComplex = true;
        }

      // attributes: id, species compartmentAlias or complesSpeciesAlias
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("id") && attr.hasAttribute("species"))
        {
          sa.mId = attr.getValue("id");
          sa.mSpecies = attr.getValue("species");

          // complexSpeciesAlias and compartmentAlias attributes are optional
          if (attr.hasAttribute("complexSpeciesAlias"))
            {
              sa.mComplexSpeciesAlias = attr.getValue("complexSpeciesAlias");
            }
          else if (attr.hasAttribute("compartmentAlias"))
            {
              sa.mCompartmentAlias = attr.getValue("compartmentAlias");
            }

          // elements: font (optional), bounds, usualView
          const XMLNode* pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "font", false);

          if (pChild != NULL)
            {
              std::string s = pChild->getAttributes().getValue("size");
              char** err = NULL;
              double dbl = strtod(s.c_str(), err);

              if (!err || *err != s.c_str())
                {
                  sa.mFontSize = dbl;
                }
              else
                {
                  result = false;
                }
            }

          if (result == true)
            {
              pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "bounds", false);

              if (pChild != NULL && CCellDesignerImporter::parseBounds(pChild, sa.mBounds) == true)
                {
                  pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "usualView", false);

                  if (pChild != NULL)
                    {
                      result = CCellDesignerImporter::parseUsualView(pChild, sa.mUView);
                    }
                }
              else
                {
                  result = false;
                }
            }

        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parse the data in the given node assuming that this is a node that represents a point
 * and therefore contains an "x" and a "y" attribute.
 * The data is stored in the given point object.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parsePoint(const XMLNode* pNode, Point& p)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getAttributes().hasAttribute("x") &&
      pNode->getAttributes().hasAttribute("y"))
    {
      std::string s = pNode->getAttributes().getValue("x");
      char** err = NULL;
      double val = strtod(s.c_str(), err);

      if (!err || *err != s.c_str())
        {
          p.setX(val);
          s = pNode->getAttributes().getValue("y");
          err = NULL;
          val = strtod(s.c_str(), err);

          if (!err || *err != s.c_str())
            {
              p.setY(val);
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Parse the data in the given node assuming that this is a node that represents a point
 * and therefore contains an "x" and a "y" attribute.
 * The data is stored in the given point object.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseBounds(const XMLNode* pNode, BoundingBox& box)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getAttributes().hasAttribute("x") &&
      pNode->getAttributes().hasAttribute("y") &&
      pNode->getAttributes().hasAttribute("w") &&
      pNode->getAttributes().hasAttribute("h"))
    {
      result = CCellDesignerImporter::parsePoint(pNode, *box.getPosition());

      if (result == true)
        {
          std::string s = pNode->getAttributes().getValue("w");
          char** err = NULL;
          double val = strtod(s.c_str(), err);

          if (!err || *err != s.c_str())
            {
              box.getDimensions()->setWidth(val);
              s = pNode->getAttributes().getValue("h");
              err = NULL;
              val = strtod(s.c_str(), err);

              if (!err || *err != s.c_str())
                {
                  box.getDimensions()->setHeight(val);
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the data in the given node which represents a UsualView object and stores
 * the parsed data in the given UsualView structure.
 * If parsinf fails, false is returned.
 */
bool CCellDesignerImporter::parseUsualView(const XMLNode* pNode, UsualView& view)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "usualView")
    {
      // elements: innerPosition (optional)
      //           boxSize
      //           singleLine
      //           paint
      const XMLNode* pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "innerPosition", false);

      if (pChild != NULL)
        {
          result = CCellDesignerImporter::parsePoint(pChild, view.mInnerPosition);
        }

      if (result == true)
        {
          pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "boxSize", false);

          if (pChild != NULL && CCellDesignerImporter::parseBoxSize(pChild, view.mBoxSize) == true)
            {
              pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "paint", false);

              if (pChild != NULL && CCellDesignerImporter::parsePaint(pChild, view.mPaint) == true)
                {
                  pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "singleLine", false);

                  if (pChild != NULL && pChild->getAttributes().hasAttribute("width"))
                    {
                      std::string s = pChild->getAttributes().getValue("width");
                      char** err = NULL;
                      double dbl = strtod(s.c_str(), err);

                      if (!err || *err != s.c_str())
                        {
                          view.mLineWidth = dbl;
                        }
                      else
                        {
                          result = false;
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the given node and stored the information iín the width and height attribute
 * in the given dimensions object.
 * If parsinf fails, false is returned.
 */
bool CCellDesignerImporter::parseModelDisplay(const XMLNode* pNode, Dimensions& d)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getName() == "modelDisplay" &&
      pNode->getAttributes().hasAttribute("sizeX") &&
      pNode->getAttributes().hasAttribute("sizeY"))
    {
      std::string s = pNode->getAttributes().getValue("sizeX");
      char** err = NULL;
      double val = strtod(s.c_str(), err);

      if (!err || *err != s.c_str())
        {
          d.setWidth(val);
          s = pNode->getAttributes().getValue("sizeY");
          err = NULL;
          val = strtod(s.c_str(), err);

          if (!err || *err != s.c_str())
            {
              d.setHeight(val);
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the given node and stored the information iín the width and height attribute
 * in the given dimensions object.
 * If parsinf fails, false is returned.
 */
bool CCellDesignerImporter::parseBoxSize(const XMLNode* pNode, Dimensions& d)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getAttributes().hasAttribute("width") &&
      pNode->getAttributes().hasAttribute("height"))
    {
      std::string s = pNode->getAttributes().getValue("width");
      char** err = NULL;
      double val = strtod(s.c_str(), err);

      if (!err || *err != s.c_str())
        {
          d.setWidth(val);
          s = pNode->getAttributes().getValue("height");
          err = NULL;
          val = strtod(s.c_str(), err);

          if (!err || *err != s.c_str())
            {
              d.setHeight(val);
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Parses the given XMLNode which represents a double line element.
 * The parsed data is stored in the given DoubleLine structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parseDoubleLine(const XMLNode* pNode, DoubleLine& dl)
{
  bool result = true;

  if (pNode != NULL &&
      pNode->getName() == "doubleLine")
    {
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("innerWidth") &&
          attr.hasAttribute("outerWidth") &&
          attr.hasAttribute("thickness"))
        {
          std::string s = attr.getValue("innerWidth");
          char** err = NULL;
          double val = strtod(s.c_str(), err);

          if (!err || *err != s.c_str())
            {
              dl.mInnerWidth = val;
              s = attr.getValue("outerWidth");
              err = NULL;
              val = strtod(s.c_str(), err);

              if (!err || *err != s.c_str())
                {
                  dl.mOuterWidth = val;
                  s = attr.getValue("thickness");
                  err = NULL;
                  val = strtod(s.c_str(), err);

                  if (!err || *err != s.c_str())
                    {
                      dl.mThickness = val;
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Parses the paint data in the given XMLNode and stores the result in the
 * given Paint structure.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::parsePaint(const XMLNode* pNode, Paint& p)
{
  bool result = true;

  if (pNode != NULL && pNode->getName() == "paint")
    {
      const XMLAttributes& attr = pNode->getAttributes();

      if (attr.hasAttribute("color") &&
          attr.hasAttribute("scheme"))
        {
          p.mColor = attr.getValue("color");
          // we convert the string to upper
          // and add the # in front and we
          // convert the aRGB to RGBa
          std::transform(p.mColor.begin(), p.mColor.end(), p.mColor.begin(), toupper);
          p.mColor = "#" + p.mColor.substr(2) + p.mColor.substr(0, 2);
          p.mScheme = CCellDesignerImporter::paintSchemeToEnum(attr.getValue("scheme"));

          if (p.mScheme == PAINT_UNDEFINED)
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * This method creates a new local style based on the passed in CompartmentAlias object.
 * The style is associated with the object via the given id.
 * If Creating the style fails, false is returned.
 */
bool CCellDesignerImporter::createCompartmentStyle(const CompartmentAlias& ca, const CompartmentGlyph* pCGlyph)
{
  // TODO the GRADIENT flag is currently ignored
  bool result = true;

  if (this->mpLocalRenderInfo != NULL &&
      !ca.mPaint.mColor.empty() &&
      pCGlyph != NULL &&
      !pCGlyph->getId().empty())
    {
      std::string color_id;
      result = this->findOrCreateColorDefinition(ca.mPaint.mColor, color_id);
      // CellDesigner seems to use the paint color for the two edges
      // of the compartment representation
      // The inner area (between the two edges seems to be filled with the same color, but
      // with a opacity value of about 35 (23 hex).
      std::string inner_color_id, inner_color_string = ca.mPaint.mColor;

      if (inner_color_string.length() == 7)
        {
          inner_color_string += "23";
          result = this->findOrCreateColorDefinition(inner_color_string, inner_color_id);
        }
      else if (inner_color_string.length() == 9)
        {
          inner_color_string[7] = '2';
          inner_color_string[8] = '3';
          result = this->findOrCreateColorDefinition(inner_color_string, inner_color_id);
        }
      else
        {
          result = false;
        }

      if (result == true)
        {
          // create a new style for the object
          std::string style_id = this->createUniqueId("Style");
          LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

          if (pStyle != NULL)
            {
              this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
              RenderGroup* pGroup = pStyle->getGroup();
              assert(pGroup != NULL);

              if (pGroup != NULL)
                {
                  // set the font size
                  pGroup->setFontSize(ca.mFontSize);
                  double d = ca.mDoubleLine.mThickness;
                  double width = pCGlyph->getBoundingBox()->getDimensions()->getWidth();
                  double height = pCGlyph->getBoundingBox()->getDimensions()->getHeight();

                  switch (ca.mClass)
                    {
                      case SQUARE_CLASS:
                      {
                        // three rectangles the first is the thick one with the transparent color
                        double small_side = (width < height) ? width : height;
                        Rectangle* pRect = pGroup->createRectangle();
                        assert(pRect != NULL);

                        if (pRect != NULL)
                          {
                            pRect->setStroke(inner_color_id);
                            pRect->setStrokeWidth(d);
                            pRect->setCoordinates(RelAbsVector(0.0, 0.0), RelAbsVector(0.0, 0.0), RelAbsVector(0.0, 0.0));
                            pRect->setSize(RelAbsVector(width, 0.0), RelAbsVector(height, 0.0));
                            pRect->setRadiusX(RelAbsVector(small_side*0.1, 0.0));
                            pRect->setRadiusY(RelAbsVector(small_side*0.1, 0.0));
                          }
                        else
                          {
                            result = false;
                          }

                        // the second has a width of 2 and is non-transparent
                        pRect = pGroup->createRectangle();
                        assert(pRect != NULL);

                        if (pRect != NULL)
                          {
                            pRect->setStroke(color_id);
                            pRect->setStrokeWidth(2.0);
                            pRect->setCoordinates(RelAbsVector(-0.5*d, 0.0), RelAbsVector(-0.5*d, 0.0), RelAbsVector(0.0, 0.0));
                            pRect->setSize(RelAbsVector(width + d, 0.0), RelAbsVector(height + d, 0.0));
                            pRect->setRadiusX(RelAbsVector((small_side + d)*0.1, 0.0));
                            pRect->setRadiusY(RelAbsVector((small_side + d)*0.1, 0.0));
                          }
                        else
                          {
                            result = false;
                          }

                        // the third has a width of 1 and is non-transparent
                        pRect = pGroup->createRectangle();
                        assert(pRect != NULL);

                        if (pRect != NULL)
                          {
                            pRect->setStroke(color_id);
                            pRect->setStrokeWidth(1.0);
                            pRect->setCoordinates(RelAbsVector(0.5*d, 0.0), RelAbsVector(0.5*d, 0.0), RelAbsVector(0.0, 0.0));
                            pRect->setSize(RelAbsVector(width - d, 0.0), RelAbsVector(height - d, 0.0));
                            pRect->setRadiusX(RelAbsVector((small_side - d)*0.1, 0.0));
                            pRect->setRadiusY(RelAbsVector((small_side - d)*0.1, 0.0));
                          }
                        else
                          {
                            result = false;
                          }

                      }
                      break;
                      case OVAL_CLASS:
                      {
                        // we need three ellipses
                        // the bottom one is the one with the transparent color
                        // and the full width
                        Ellipse* pEllipse = pGroup->createEllipse();
                        pEllipse->setCX(RelAbsVector(width*0.5, 0.0));
                        pEllipse->setCY(RelAbsVector(height*0.5, 0.0));
                        pEllipse->setRX(RelAbsVector(width*0.5, 0.0));
                        pEllipse->setRY(RelAbsVector(height*0.5, 0.0));
                        pEllipse->setStrokeWidth(d);
                        pEllipse->setStroke(inner_color_id);
                        // the outer one has a width of 2 and has the non-transparent color
                        pEllipse = pGroup->createEllipse();
                        pEllipse->setCX(RelAbsVector(width*0.5, 0.0));
                        pEllipse->setCY(RelAbsVector(height*0.5, 0.0));
                        pEllipse->setRX(RelAbsVector(width*0.5 + d*0.5, 0.0));
                        pEllipse->setRY(RelAbsVector(height*0.5 + d*0.5, 0.0));
                        pEllipse->setStrokeWidth(2.0);
                        pEllipse->setStroke(color_id);
                        // the inner one has a width of 1 and has the non-transparent color
                        pEllipse = pGroup->createEllipse();
                        pEllipse->setCX(RelAbsVector(width*0.5, 0.0));
                        pEllipse->setCY(RelAbsVector(height*0.5, 0.0));
                        pEllipse->setRX(RelAbsVector(width*0.5 - d*0.5, 0.0));
                        pEllipse->setRY(RelAbsVector(height*0.5 - d*0.5, 0.0));
                        pEllipse->setStrokeWidth(1.0);
                        pEllipse->setStroke(color_id);
                      }
                      break;
                      case SQUARE_NW_CLASS:
                        // thick line with thicker edge to the northwest
                      {
                        // three curves, the first is thick and transparent
                        double radius = 20.0;
                        RenderPoint* pP = NULL;
                        RenderCubicBezier* pCB = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(radius);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(0.0);
                                pCB->setBasePoint1_Y(0.0);
                                pCB->setBasePoint2_X(0.0);
                                pCB->setBasePoint2_Y(0.0);
                                pCB->setX(radius);
                                pCB->setY(0.0);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(0.0);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // second curve for the outer edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(-d*0.5);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(-d*0.5);
                                pP->setY(radius);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(-d*0.5);
                                pCB->setBasePoint1_Y(-d*0.5);
                                pCB->setBasePoint2_X(-d*0.5);
                                pCB->setBasePoint2_Y(-d*0.5);
                                pCB->setX(radius);
                                pCB->setY(-d*0.5);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(-d*0.5);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // third curve for the inner edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(d*0.5);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(d*0.5);
                                pP->setY(radius);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(d*0.5);
                                pCB->setBasePoint1_Y(d*0.5);
                                pCB->setBasePoint2_X(d*0.5);
                                pCB->setBasePoint2_Y(d*0.5);
                                pCB->setX(radius);
                                pCB->setY(d*0.5);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(d*0.5);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                      }
                      break;
                      case SQUARE_NE_CLASS:
                        // thick line with thicker edge to the northeast
                      {
                        // three curves, the first is thick and transparent
                        double radius = 20.0;
                        RenderPoint* pP = NULL;
                        RenderCubicBezier* pCB = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - radius);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(width);
                                pCB->setBasePoint1_Y(0.0);
                                pCB->setBasePoint2_X(width);
                                pCB->setBasePoint2_Y(0.0);
                                pCB->setX(width);
                                pCB->setY(radius);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // second curve for the outer edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(-d*0.5);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - radius);
                                pP->setY(-d*0.5);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(width + 0.5*d);
                                pCB->setBasePoint1_Y(-0.5*d);
                                pCB->setBasePoint2_X(width + 0.5*d);
                                pCB->setBasePoint2_Y(-0.5*d);
                                pCB->setX(width + 0.5*d);
                                pCB->setY(radius);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width + 0.5*d);
                                pP->setY(height);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // third curve for the inner edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - radius);
                                pP->setY(0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(width - 0.5*d);
                                pCB->setBasePoint1_Y(0.5*d);
                                pCB->setBasePoint2_X(width - 0.5*d);
                                pCB->setBasePoint2_Y(0.5*d);
                                pCB->setX(width - 0.5*d);
                                pCB->setY(radius);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - 0.5*d);
                                pP->setY(height);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                      }
                      break;
                      case SQUARE_SW_CLASS:
                        // thick line with thicker edge to the southwest
                      {
                        // three curves, the first is thick and transparent
                        double radius = 20.0;
                        RenderPoint* pP = NULL;
                        RenderCubicBezier* pCB = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height - radius);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(0.0);
                                pCB->setBasePoint1_Y(height);
                                pCB->setBasePoint2_X(0.0);
                                pCB->setBasePoint2_Y(height);
                                pCB->setX(radius);
                                pCB->setY(height);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // second curve for the outer edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(-0.5*d);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(-d*0.5);
                                pP->setY(height - radius);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(-d*0.5);
                                pCB->setBasePoint1_Y(height + d*0.5);
                                pCB->setBasePoint2_X(-d*0.5);
                                pCB->setBasePoint2_Y(height + d*0.5);
                                pCB->setX(radius);
                                pCB->setY(height + d*0.5);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height + d*0.5);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // third curve for the inner edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(d*0.5);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(d*0.5);
                                pP->setY(height - radius);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(d*0.5);
                                pCB->setBasePoint1_Y(height - d*0.5);
                                pCB->setBasePoint2_X(d*0.5);
                                pCB->setBasePoint2_Y(height - d*0.5);
                                pCB->setX(radius);
                                pCB->setY(height - d*0.5);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height - d*0.5);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                      }
                      break;
                      case SQUARE_SE_CLASS:
                        // thick line with thicker edge to the southeast
                      {
                        // three curves, the first is thick and transparent
                        double radius = 20.0;
                        RenderPoint* pP = NULL;
                        RenderCubicBezier* pCB = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - radius);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(width);
                                pCB->setBasePoint1_Y(height);
                                pCB->setBasePoint2_X(width);
                                pCB->setBasePoint2_Y(height);
                                pCB->setX(width);
                                pCB->setY(height - radius);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(0.0);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // second curve for the outer edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height + 0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - radius);
                                pP->setY(height + 0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(width + d*0.5);
                                pCB->setBasePoint1_Y(height + 0.5*d);
                                pCB->setBasePoint2_X(width + d*0.5);
                                pCB->setBasePoint2_Y(height + d*0.5);
                                pCB->setX(width + 0.5*d);
                                pCB->setY(height - radius);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width + 0.5*d);
                                pP->setY(0.0);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // third curve for the inner edge
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height - 0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - radius);
                                pP->setY(height - 0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pCB = pCurve->createCubicBezier();
                            assert(pCB != NULL);

                            if (pCB != NULL)
                              {
                                pCB->setBasePoint1_X(width - d*0.5);
                                pCB->setBasePoint1_Y(height - d*0.5);
                                pCB->setBasePoint2_X(width - d*0.5);
                                pCB->setBasePoint2_Y(height - d*0.5);
                                pCB->setX(width - 0.5*d);
                                pCB->setY(height - radius);
                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - 0.5*d);
                                pP->setY(0.0);
                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                      }
                      break;
                      case SQUARE_N_CLASS:
                        // thick line with thicker edge to the north
                      {
                        // three curves, the first is thick and transparent
                        RenderPoint* pP = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the second has width 2 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(-0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(-0.5*d);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the third has width 1 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(0.5*d);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(0.5*d);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }


                      }
                      break;
                      case SQUARE_E_CLASS:
                        // thick line with thicker edge to the east
                      {
                        // three curves, the first is thick and transparent
                        RenderPoint* pP = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the second has width 2 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width + 0.5*d);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width + 0.5*d);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the third has width 1 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - 0.5*d);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width - 0.5*d);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }


                      }
                      break;
                      case SQUARE_W_CLASS:
                        // thick line with thicker edge to the west
                      {
                        // three curves, the first is thick and transparent
                        RenderPoint* pP = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the second has width 2 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(-0.5*d);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(-0.5*d);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the third has width 1 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.5*d);
                                pP->setY(0.0);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.5*d);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }


                      }
                      break;
                      case SQUARE_S_CLASS:
                        // thick line with thicker edge to the south
                      {
                        // three curves, the first is thick and transparent
                        RenderPoint* pP = NULL;
                        RenderCurve* pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(d);
                            pCurve->setStroke(inner_color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the second has width 2 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(2.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height + d*0.5);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height + d*0.5);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }

                        // the third has width 1 and is non-transparent
                        pCurve = pGroup->createCurve();
                        assert(pCurve != NULL);

                        if (pCurve != NULL)
                          {
                            pCurve->setStrokeWidth(1.0);
                            pCurve->setStroke(color_id);
                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(0.0);
                                pP->setY(height - d*0.5);

                              }
                            else
                              {
                                result = false;
                              }

                            pP = pCurve->createPoint();
                            assert(pP != NULL);

                            if (pP != NULL)
                              {
                                pP->setX(width);
                                pP->setY(height - d*0.5);

                              }
                            else
                              {
                                result = false;
                              }
                          }
                        else
                          {
                            result = false;
                          }


                      }
                      break;
                      default:
                        result = false;
                        break;
                    }

                }

              // don't forget to associate the style and the layout object via the id
              pStyle->addId(pCGlyph->getId());
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * This method creates a new local style based on the passed in SpeciesAlias object.
 * The style is associated with the object via the given id.
 * If Creating the style fails, false is returned.
bool CCellDesignerImporter::createSpeciesStyle(const SpeciesAlias& sa,const std::string& objectReference)
{
    // TODO for now this style has a black, single
    // TODO line edge and a background color as specified
    // TODO in the paint element
    // TODO the GRADIENT flag is currently ignored
    bool result=true;
    if(this->mpLocalRenderInfo != NULL &&
       !sa.mUView.mPaint.mColor.empty() &&
       !objectReference.empty())
    {
        std::map<std::string,std::string>::const_iterator pos=this->mColorStringMap.find(sa.mUView.mPaint.mColor);
        std::string color_id;
        if(pos == this->mColorStringMap.end())
        {
            // we need to create a new ColorDefinition for this object first
            ColorDefinition* pDef=this->mpLocalRenderInfo->createColorDefinition();
            if(pDef != NULL)
            {
                // the color definition needs an id and we need to set the color values
                color_id=this->createUniqueId("ColorDefinition");
                pDef->setId(color_id);
                this->mIdMap.insert(std::pair<std::string,const SBase*>(color_id,pDef));
                result=pDef->setColorValue(sa.mUView.mPaint.mColor);
                this->mColorStringMap.insert(std::pair<std::string,std::string>(sa.mUView.mPaint.mColor,color_id));
            }
        }
        else
        {
            color_id=pos->second;
        }
        if(result == true)
        {
            // create a new style for the object
            std::string style_id=this->createUniqueId("Style");
            LocalStyle* pStyle=this->mpLocalRenderInfo->createStyle(style_id);
            if(pStyle != NULL)
            {
                this->mIdMap.insert(std::pair<std::string,const SBase*>(style_id,pStyle));
                Group* pGroup=pStyle->getGroup();
                assert(pGroup != NULL);
                if(pGroup != NULL)
                {
                    // set the font size
                    pGroup->setFontSize(sa.mFontSize);
                    // well as the edge color, and edge width
                    pos=this->mColorStringMap.find("#000000FF");
                    assert(pos != this->mColorStringMap.end());
                    if(pos != this->mColorStringMap.end())
                    {
                        pGroup->setStroke("black");
                    }
                    else
                    {
                        pGroup->setStroke("#000000FF");
                    }
                    // set the lien width
                    pGroup->setStrokeWidth(sa.mUView.mLineWidth);
                    // set the background color on the top level group as
                    pGroup->setFillColor(color_id);

                    // TODO create render objects depending on the class of the
                    // TODO object
                    // TODO for now we use a rectangle
                    Rectangle* pRect=pGroup->createRectangle();
                    assert(pRect != NULL);
                    if(pRect != NULL)
                    {
                      pRect->setCoordinates(RelAbsVector(0.0,0.0),RelAbsVector(0.0,0.0),RelAbsVector(0.0,0.0));
                      pRect->setSize(RelAbsVector(0.0,100.0),RelAbsVector(0.0,100.0));
                    }
                    else
                    {
                        result=false;
                    }

                }
                // don't forget to associate the style and the layout object via the id
                pStyle->addId(objectReference);
            }
        }
    }
    else
    {
        result=false;
    }
    return result;
}
*/

/**
 * Creates a local style for a certain text glyph.
 * The style is associated with the text glyph via the id
 * of the text glyph.
 */
bool CCellDesignerImporter::createTextGlyphStyle(double size, Text::TEXT_ANCHOR hAlign, Text::TEXT_ANCHOR vAlign, const std::string& objectReference)
{
  // the color is alway black
  // the size is passed in
  // the vertical and horizontal alignments are passed in
  bool result = true;

  if (this->mpLocalRenderInfo != NULL &&
      !objectReference.empty())
    {
      // create a new style for the object
      std::string style_id = this->createUniqueId("Style");
      LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

      if (pStyle != NULL)
        {
          this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
          RenderGroup* pGroup = pStyle->getGroup();
          assert(pGroup != NULL);

          if (pGroup != NULL)
            {
              // set the font size
              pGroup->setFontSize(size);
              pGroup->setFontFamily("serif");
              // well as the edge color, and edge width
              std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");
              assert(pos != this->mColorStringMap.end());

              if (pos != this->mColorStringMap.end())
                {
                  pGroup->setStroke("black");
                }
              else
                {
                  pGroup->setStroke("#000000FF");
                }

              pGroup->setStrokeWidth(1.0);
              // set the alignment
              pGroup->setTextAnchor(hAlign);
              pGroup->setVTextAnchor(vAlign);
            }

          // don't forget to associate the style and the layout object via the id
          pStyle->addId(objectReference);
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * TODO right now, we use default styles for species reference glyphs
 * TODO and reaction glyphs.
 * TODO These are created here.
 * TODO later we have to create individual styles based on the type of reaction
 * TODO and the color set in the CellDesigner annotation.
 */
bool CCellDesignerImporter::createDefaultStyles()
{
  bool result = true;
  this->mModificationLinkStyleMap.clear();

  if (this->mpLocalRenderInfo != NULL)
    {
      result = this->createDefaultReactionGlyphStyle();
      result = (result && this->createDefaultModifierStyle());
      result = (result && this->createDefaultInhibitorStyle());
      result = (result && this->createDefaultActivatorStyle());
      result = (result && this->createCatalysisStyles());
      result = (result && this->createDefaultProductStyle());
      result = (result && this->createDefaultSubstrateStyle());
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Create default style for reaction glyphs.
 */
bool CCellDesignerImporter::createDefaultReactionGlyphStyle()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      std::string style_id = this->createUniqueId("ReactionGlyphStyle");
      LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

      if (pStyle != NULL)
        {
          this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
          assert(pStyle->getGroup() != NULL);

          if (pStyle->getGroup() != NULL)
            {
              std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

              if (pos != this->mColorStringMap.end())
                {
                  pStyle->getGroup()->setStroke(pos->second);
                }
              else
                {
                  pStyle->getGroup()->setStroke("#000000FF");
                }

              pStyle->getGroup()->setStrokeWidth(1.0);
              // we also use this as fallback to species reference glyphs that don't
              // specify a role
              pStyle->addType("SPECIESREFERENCEGLYPH");
              pStyle->addType("REACTIONGLYPH");
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Create default style for modifiers.
 */
bool CCellDesignerImporter::createDefaultModifierStyle()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      // we need a head for modifiers
      LineEnding* pLE = this->mpLocalRenderInfo->createLineEnding();
      std::string headId;

      if (pLE != NULL)
        {
          pLE->setEnableRotationalMapping(true);
          // set the id
          headId = this->createUniqueId("modifier_arrow");
          pLE->setId(headId);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(headId, pLE));
          Point pos(new LayoutPkgNamespaces(), -5.0, -5.0);
          Dimensions dim = Dimensions(new LayoutPkgNamespaces(), 10.0, 10.0);
          BoundingBox box;
          box.setPosition(&pos);
          box.setDimensions(&dim);
          pLE->setBoundingBox(&box);
          RenderGroup* pGroup = pLE->getGroup();
          assert(pGroup != NULL);

          if (pGroup != NULL)
            {
              Polygon* pPolygon = pGroup->createPolygon();
              assert(pPolygon != NULL);

              if (pPolygon != NULL)
                {
                  pPolygon->setFillColor("#000000");
                  pPolygon->setStroke("#000000");
                  RenderPoint* pP = pPolygon->createPoint();
                  assert(pP != NULL);

                  if (pP != NULL)
                    {
                      pP->setX(RelAbsVector(0.0, 0.0));
                      pP->setY(RelAbsVector(0.0, 50.0));
                      pP = pPolygon->createPoint();
                      assert(pP != NULL);

                      if (pP != NULL)
                        {
                          pP->setX(RelAbsVector(0.0, 50.0));
                          pP->setY(RelAbsVector(0.0, 100.0));
                          pP = pPolygon->createPoint();
                          assert(pP != NULL);

                          if (pP != NULL)
                            {
                              pP->setX(RelAbsVector(0.0, 100.0));
                              pP->setY(RelAbsVector(0.0, 50.0));
                              pP = pPolygon->createPoint();
                              assert(pP != NULL);

                              if (pP != NULL)
                                {
                                  pP->setX(RelAbsVector(0.0, 50.0));
                                  pP->setY(RelAbsVector(0.0, 0.0));
                                }
                              else
                                {
                                  result = false;
                                }
                            }
                          else
                            {
                              result = false;
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }

      if (result == true)
        {
          std::string style_id = this->createUniqueId("ModifierStyle");
          LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

          if (pStyle != NULL)
            {
              this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
              assert(pStyle->getGroup() != NULL);

              if (pStyle->getGroup() != NULL)
                {
                  std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

                  if (pos != this->mColorStringMap.end())
                    {
                      pStyle->getGroup()->setStroke(pos->second);
                    }
                  else
                    {
                      pStyle->getGroup()->setStroke("#000000FF");
                    }

                  pStyle->getGroup()->setStrokeWidth(1.0);
                  pStyle->getGroup()->setEndHead(headId);
                  pStyle->addRole("modifier");
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Create default style for inhibitors.
 */
bool CCellDesignerImporter::createDefaultInhibitorStyle()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      LineEnding* pLE = this->mpLocalRenderInfo->createLineEnding();
      assert(pLE != NULL);
      BoundingBox box;
      Point pos(new LayoutPkgNamespaces());
      Dimensions dim(new LayoutPkgNamespaces());
      RenderGroup* pGroup = NULL;
      std::string headId;

      if (pLE != NULL)
        {
          pLE->setEnableRotationalMapping(true);
          headId = this->createUniqueId("inhibitor_arrow");
          pLE->setId(headId);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(headId, pLE));
          pos = Point(new LayoutPkgNamespaces(), 0.0, -5.0);
          dim = Dimensions(new LayoutPkgNamespaces(), 3.0, 10.0);
          box.setPosition(&pos);
          box.setDimensions(&dim);
          pLE->setBoundingBox(&box);
          pGroup = pLE->getGroup();
          assert(pGroup != NULL);

          if (pGroup != NULL)
            {
              Rectangle* pRect = pGroup->createRectangle();
              assert(pRect != NULL);

              if (pRect != NULL)
                {
                  pRect->setFillColor("#000000");
                  pRect->setStrokeWidth(1.0);
                  pRect->setCoordinates(RelAbsVector(0.0, 0.0), RelAbsVector(0.0, 0.0), RelAbsVector(0.0, 0.0));
                  pRect->setSize(RelAbsVector(0.0, 100.0), RelAbsVector(0.0, 100.0));
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }

      if (result == true)
        {
          std::string style_id = this->createUniqueId("InhibitorStyle");
          LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

          if (pStyle != NULL)
            {
              this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
              assert(pStyle->getGroup() != NULL);

              if (pStyle->getGroup() != NULL)
                {
                  std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

                  if (pos != this->mColorStringMap.end())
                    {
                      pStyle->getGroup()->setStroke(pos->second);
                    }
                  else
                    {
                      pStyle->getGroup()->setStroke("#000000FF");
                    }

                  pStyle->getGroup()->setStrokeWidth(1.0);
                  pStyle->getGroup()->setEndHead(headId);
                  pStyle->addRole("inhibitor");
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Create default style for activators.
 */
bool CCellDesignerImporter::createDefaultActivatorStyle()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      // we need a head for products
      LineEnding* pLE = this->mpLocalRenderInfo->createLineEnding();
      assert(pLE != NULL);
      BoundingBox box;
      Point pos(new LayoutPkgNamespaces());
      Dimensions dim(new LayoutPkgNamespaces());
      RenderGroup* pGroup = NULL;
      std::string headId;

      if (pLE != NULL)
        {
          pLE->setEnableRotationalMapping(true);
          headId = this->createUniqueId("activator_arrow");
          pLE->setId(headId);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(headId, pLE));
          pos = Point(new LayoutPkgNamespaces(), -5.0, -5.0);
          dim = Dimensions(new LayoutPkgNamespaces(), 10.0, 10.0);
          box.setPosition(&pos);
          box.setDimensions(&dim);
          pLE->setBoundingBox(&box);
          pGroup = pLE->getGroup();
          assert(pGroup != NULL);

          if (pGroup != NULL)
            {
              Polygon* pPolygon = pGroup->createPolygon();
              assert(pPolygon != NULL);

              if (pPolygon != NULL)
                {
                  RenderPoint* pP = pPolygon->createPoint();
                  assert(pP != NULL);

                  if (pP != NULL)
                    {
                      pP->setX(RelAbsVector(0.0, 0.0));
                      pP->setY(RelAbsVector(0.0, 0.0));
                      pP = pPolygon->createPoint();
                      assert(pP != NULL);

                      if (pP != NULL)
                        {
                          pP->setX(RelAbsVector(0.0, 0.0));
                          pP->setY(RelAbsVector(0.0, 100.0));
                          pP = pPolygon->createPoint();
                          assert(pP != NULL);

                          if (pP != NULL)
                            {
                              pP->setX(RelAbsVector(0.0, 100.0));
                              pP->setY(RelAbsVector(0.0, 50.0));
                            }
                          else
                            {
                              result = false;
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }

      if (result == true)
        {
          std::string style_id = this->createUniqueId("AvtivatorStyle");
          LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

          if (pStyle != NULL)
            {
              this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
              assert(pStyle->getGroup() != NULL);

              if (pStyle->getGroup() != NULL)
                {
                  std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

                  if (pos != this->mColorStringMap.end())
                    {
                      pStyle->getGroup()->setStroke(pos->second);
                    }
                  else
                    {
                      pStyle->getGroup()->setStroke("#000000FF");
                    }

                  pStyle->getGroup()->setStrokeWidth(1.0);
                  pStyle->getGroup()->setEndHead(headId);
                  pStyle->addRole("activator");
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Create style for catalysis.
 */
bool CCellDesignerImporter::createCatalysisStyles()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      // we need a head for products
      LineEnding* pLE = this->mpLocalRenderInfo->createLineEnding();
      assert(pLE != NULL);
      BoundingBox box;
      Point pos(new LayoutPkgNamespaces());
      Dimensions dim(new LayoutPkgNamespaces());
      RenderGroup* pGroup = NULL;
      std::string headId;

      if (pLE != NULL)
        {
          pLE->setEnableRotationalMapping(true);
          headId = this->createUniqueId("catalysis_arrow");
          pLE->setId(headId);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(headId, pLE));
          pos = Point(new LayoutPkgNamespaces(), -5.0, -5.0);
          dim = Dimensions(new LayoutPkgNamespaces(), 10.0, 10.0);
          box.setPosition(&pos);
          box.setDimensions(&dim);
          pLE->setBoundingBox(&box);
          pGroup = pLE->getGroup();
          assert(pGroup != NULL);

          if (pGroup != NULL)
            {
                Ellipse* pEllipse = pGroup->createEllipse();
                assert(pEllipse != NULL);

                if (pEllipse != NULL)
                {
                    pEllipse->setCX(RelAbsVector(5.0, 0.0));
                    pEllipse->setCY(RelAbsVector(5.0, 0.0));
                    pEllipse->setRX(RelAbsVector(5.0, 0.0));
                    pEllipse->setRY(RelAbsVector(5.0, 0.0));
                    pEllipse->setStrokeWidth(1.0);
                    pEllipse->setStroke("#000000");
                    pEllipse->setFillColor("none");
                }
                else
                {
                    result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }

      if (result == true)
        {
          std::string style_id = this->createUniqueId("CatalysisStyle");
          LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

          if (pStyle != NULL)
            {
              this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
              assert(pStyle->getGroup() != NULL);

              if (pStyle->getGroup() != NULL)
                {
                  std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

                  if (pos != this->mColorStringMap.end())
                    {
                      pStyle->getGroup()->setStroke(pos->second);
                    }
                  else
                    {
                      pStyle->getGroup()->setStroke("#000000FF");
                    }

                  pStyle->getGroup()->setStrokeWidth(1.0);
                  pStyle->getGroup()->setEndHead(headId);
                  this->mModificationLinkStyleMap.insert(std::pair<MODIFICATION_LINK_TYPE,LocalStyle*>(CATALYSIS_ML_TYPE,pStyle));
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      if (result == true)
        {
          std::string style_id = this->createUniqueId("UnknownCatalysisStyle");
          LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

          if (pStyle != NULL)
            {
              this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
              assert(pStyle->getGroup() != NULL);

              if (pStyle->getGroup() != NULL)
                {
                  std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

                  if (pos != this->mColorStringMap.end())
                    {
                      pStyle->getGroup()->setStroke(pos->second);
                    }
                  else
                    {
                      pStyle->getGroup()->setStroke("#000000FF");
                    }

                  pStyle->getGroup()->setStrokeWidth(1.0);
                  std::vector<unsigned int> dashes;
                  dashes.push_back(5);
                  dashes.push_back(5);
                  pStyle->getGroup()->setDashArray(dashes);
                  // Unknown Catalysis has a dashed stroke pattern
                  pStyle->getGroup()->setEndHead(headId);
                  this->mModificationLinkStyleMap.insert(std::pair<MODIFICATION_LINK_TYPE,LocalStyle*>(UNKNOWN_CATALYSIS_ML_TYPE,pStyle));

                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Create default style for products.
 */
bool CCellDesignerImporter::createDefaultProductStyle()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      // we need a head for products
      LineEnding* pLE = this->mpLocalRenderInfo->createLineEnding();
      assert(pLE != NULL);
      BoundingBox box;
      Point pos(new LayoutPkgNamespaces());
      Dimensions dim(new LayoutPkgNamespaces());
      RenderGroup* pGroup = NULL;
      std::string headId;

      if (pLE != NULL)
        {
          pLE->setEnableRotationalMapping(true);
          headId = this->createUniqueId("product_arrow");
          pLE->setId(headId);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(headId, pLE));
          pos = Point(new LayoutPkgNamespaces(), -5.0, -5.0);
          dim = Dimensions(new LayoutPkgNamespaces(), 10.0, 10.0);
          box.setPosition(&pos);
          box.setDimensions(&dim);
          pLE->setBoundingBox(&box);
          pGroup = pLE->getGroup();
          assert(pGroup != NULL);

          if (pGroup != NULL)
            {
              Polygon* pPolygon = pGroup->createPolygon();
              assert(pPolygon != NULL);

              if (pPolygon != NULL)
                {
                  pPolygon->setFillColor("#000000");
                  RenderPoint* pP = pPolygon->createPoint();
                  assert(pP != NULL);

                  if (pP != NULL)
                    {
                      pP->setX(RelAbsVector(0.0, 0.0));
                      pP->setY(RelAbsVector(0.0, 0.0));
                      pP = pPolygon->createPoint();
                      assert(pP != NULL);

                      if (pP != NULL)
                        {
                          pP->setX(RelAbsVector(0.0, 0.0));
                          pP->setY(RelAbsVector(0.0, 100.0));
                          pP = pPolygon->createPoint();
                          assert(pP != NULL);

                          if (pP != NULL)
                            {
                              pP->setX(RelAbsVector(0.0, 100.0));
                              pP->setY(RelAbsVector(0.0, 50.0));
                            }
                          else
                            {
                              result = false;
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                  else
                    {
                      result = false;
                    }
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }

      if (result == true)
        {
          std::string style_id = this->createUniqueId("ProductStyle");
          LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

          if (pStyle != NULL)
            {
              this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
              assert(pStyle->getGroup() != NULL);

              if (pStyle->getGroup() != NULL)
                {
                  std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

                  if (pos != this->mColorStringMap.end())
                    {
                      pStyle->getGroup()->setStroke(pos->second);
                    }
                  else
                    {
                      pStyle->getGroup()->setStroke("#000000FF");
                    }

                  pStyle->getGroup()->setStrokeWidth(1.0);
                  pStyle->getGroup()->setEndHead(headId);
                  pStyle->addRole("product");
                  pStyle->addRole("sideproduct");
                }
              else
                {
                  result = false;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Create default style for substrates.
 */
bool CCellDesignerImporter::createDefaultSubstrateStyle()
{
  bool result = true;

  if (this->mpLocalRenderInfo != NULL)
    {
      std::string style_id = this->createUniqueId("SubstrateStyle");
      LocalStyle* pStyle = this->mpLocalRenderInfo->createStyle(style_id);

      if (pStyle != NULL)
        {
          this->mIdMap.insert(std::pair<std::string, const SBase*>(style_id, pStyle));
          assert(pStyle->getGroup() != NULL);

          if (pStyle->getGroup() != NULL)
            {
              std::map<std::string, std::string>::const_iterator pos = this->mColorStringMap.find("#000000FF");

              if (pos != this->mColorStringMap.end())
                {
                  pStyle->getGroup()->setStroke(pos->second);
                }
              else
                {
                  pStyle->getGroup()->setStroke("#000000FF");
                }

              pStyle->getGroup()->setStrokeWidth(1.0);
              pStyle->addRole("substrate");
              pStyle->addRole("sidesubstrate");
            }
          else
            {
              result = false;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }    return result;
}



/**
 * Adds all possible POSITION enums to the given vector.
 * The vector is cleared first.
 */
void CCellDesignerImporter::addAllPositions(std::vector<POSITION>& v)
{
  // we make the assumption that POSITION_N
  // is the first valid element and that
  // POSITION_NNW the last
  POSITION pos = POSITION_N;

  while (pos <= POSITION_NNW)
    {
      v.push_back(pos);
      pos = (POSITION)((int)pos + 1);
    }
}


/**
 * Finds the shortest connection between two objects given the potential
 * connection positions for each object and the bounding boxes for each object.
 * The result is returned in the original vectors as position values.
 * If the method fails, e.g. because one of the vectors is empty or the bounding box contains
 * values we can't use for calculations (ing,NAN), false is returned.
 */
bool CCellDesignerImporter::findShortestConnection(std::vector<POSITION>& pos1, std::vector<POSITION>& pos2, const BoundingBox& box1, const BoundingBox& box2)
{
  bool result = true;
  double x1 = box1.getPosition()->x();
  double y1 = box1.getPosition()->y();
  double width1 = box1.getDimensions()->getWidth();
  double height1 = box1.getDimensions()->getHeight();
  double x2 = box2.getPosition()->x();
  double y2 = box2.getPosition()->y();
  double width2 = box2.getDimensions()->getWidth();
  double height2 = box2.getDimensions()->getHeight();

  if (!pos1.empty() &&
      !pos2.empty() &&
      x1 == x1 &&
      y1 == y1 &&
      width1 == width1 &&
      height1 == height1 &&
      x2 == x2 &&
      y2 == y2 &&
      width2 == width2 &&
      height2 == height2 &&
      width1 > 0.0 &&
      height1 > 0.0 &&
      width2 > 0.0 &&
      height2 > 0.0)
    {
      if (std::numeric_limits<double>::has_infinity)
        {
          double inf = std::numeric_limits<double>::infinity();

          if (x1 == inf ||
              y1 == inf ||
              width1 == inf ||
              height1 == inf ||
              x2 == inf ||
              y2 == inf ||
              width2 == inf ||
              height2 == inf ||
              x1 == -inf ||
              y1 == -inf ||
              width1 == -inf ||
              height1 == -inf ||
              x2 == -inf ||
              y2 == -inf ||
              width2 == -inf ||
              height2 == -inf)
            {
              result = false;
              pos1.clear();
              pos2.clear();
            }
        }

      if (result == true)
        {
          double minDist = std::numeric_limits<double>::max();
          double dist;
          Point p1(new LayoutPkgNamespaces()), p2(new LayoutPkgNamespaces());
          std::pair<POSITION, POSITION> bestPair;
          std::vector<POSITION>::const_iterator it = pos1.begin(), endit = pos1.end();
          POSITION best;

          while (it != endit)
            {
              p1 = CCellDesignerImporter::getPositionPoint(box1, *it);
              best = CCellDesignerImporter::findShortestConnection(p1, pos2, box2);

              if (best != POSITION_UNDEFINED)
                {
                  p2 = CCellDesignerImporter::getPositionPoint(box2, best);
                  dist = CCellDesignerImporter::distance(p1, p2);

                  if (dist < minDist)
                    {
                      minDist = dist;
                      bestPair.first = *it;
                      bestPair.second = best;
                    }
                }
              else
                {
                  result = false;
                  break;
                }

              ++it;
            }

          pos1.clear();
          pos2.clear();
          pos1.push_back(bestPair.first);
          pos2.push_back(bestPair.second);
        }
    }
  else
    {
      result = false;
      pos1.clear();
      pos2.clear();
    }

  return result;
}

/**
 * Finds the shortest connection between the given point and the object which is
 * defined by its connection positions and its bounding box.
 * If the method fails, e.g. because one of the vectors is empty or the bounding box contains
 * values we can't use for calculations (ing,NAN), POSITION_UNDEFINED
 */
POSITION CCellDesignerImporter::findShortestConnection(const Point& p, std::vector<POSITION>& pos, const BoundingBox& box)
{
  POSITION result = POSITION_UNDEFINED;
  double x = box.getPosition()->x();
  double y = box.getPosition()->y();
  double width = box.getDimensions()->getWidth();
  double height = box.getDimensions()->getHeight();
  double dist;
  double minDist = std::numeric_limits<double>::max();

  if (!pos.empty() &&
      x == x &&
      y == y &&
      width == width &&
      height == height &&
      width > 0.0 &&
      height > 0.0)
    {
      if (std::numeric_limits<double>::has_infinity)
        {
          double inf = std::numeric_limits<double>::infinity();

          if (x == inf ||
              y == inf ||
              width == inf ||
              height == inf ||
              x == -inf ||
              y == -inf ||
              width == -inf ||
              height == -inf)
            {
              return result;
            }
        }

      std::vector<POSITION>::const_iterator it = pos.begin(), endit = pos.end();
      Point p2(new LayoutPkgNamespaces());

      while (it != endit)
        {
          p2 = CCellDesignerImporter::getPositionPoint(box, *it);
          dist = CCellDesignerImporter::distance(p, p2);

          if (dist < minDist)
            {
              minDist = dist;
              result = *it;
            }

          ++it;
        }
    }

  return result;
}


/**
 * Calculate the distance between the two points.
 */
double CCellDesignerImporter::distance(const Point& p1, const Point& p2)
{
  return std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2));
}

/**
 * Calculates the absolute position for point p
 * based on the three other points (p1,p2,p3) given.
 * The formula for that is:
 * p1 + p.x * (p2 - p1) + p.y * (p3 - p1)
 */
Point CCellDesignerImporter::calculateAbsoluteValue(const Point& p, const Point& p1, const Point& p2, const Point& p3)
{
  Point v1(new LayoutPkgNamespaces(), p2.x() - p1.x(), p2.y() - p1.y());
  Point v2(new LayoutPkgNamespaces(), p3.x() - p1.x(), p3.y() - p1.y());
  Point result(new LayoutPkgNamespaces(), p1.x() + p.x()*v1.x() + p.y()*v2.x(), p1.y() + p.x()*v1.y() + p.y()*v2.y());
  return result;
}

/**
 * Checks if the given ReactantLink object has a valid linkAnchor
 * If not, we try to determine the best anchor be finding the one that is closest
 * to the given point.
 */
void CCellDesignerImporter::checkLinkAnchor(LinkTarget& link, const Point& p)
{
  if (link.mPosition == POSITION_UNDEFINED)
    {
      // find the bounding box for the alias
      if (!link.mAlias.empty())
        {
          std::map<std::string, BoundingBox>::const_iterator pos = this->mCDBounds.find(link.mAlias);
          assert(pos != this->mCDBounds.end());

          if (pos != this->mCDBounds.end())
            {
              std::vector<POSITION> tmp;
              CCellDesignerImporter::addAllPositions(tmp);
              link.mPosition = CCellDesignerImporter::findShortestConnection(p, tmp, pos->second);
            }
        }
    }
}

/**
 * Checks if the given ReactantLink objects have valid linkAnchors
 * If not, we try to determine the best anchor be finding the ones that
 * give the shortest connection between the two objects
 */
void CCellDesignerImporter::checkLinkAnchors(LinkTarget& substrate, LinkTarget& product)
{
  if (substrate.mPosition == POSITION_UNDEFINED ||
      product.mPosition == POSITION_UNDEFINED)
    {
      // find the bounding box for the alias
      if (!substrate.mAlias.empty() && !product.mAlias.empty())
        {
          std::map<std::string, BoundingBox>::const_iterator pos1 = this->mCDBounds.find(substrate.mAlias);
          std::map<std::string, BoundingBox>::const_iterator pos2 = this->mCDBounds.find(product.mAlias);
          assert(pos1 != this->mCDBounds.end());
          assert(pos2 != this->mCDBounds.end());

          if (pos1 != this->mCDBounds.end() && pos2 != this->mCDBounds.end())
            {
              std::vector<POSITION> tmp1;
              std::vector<POSITION> tmp2;

              if (substrate.mPosition == POSITION_UNDEFINED)
                {
                  CCellDesignerImporter::addAllPositions(tmp1);
                }
              else
                {
                  tmp1.push_back(substrate.mPosition);
                }

              if (product.mPosition == POSITION_UNDEFINED)
                {
                  CCellDesignerImporter::addAllPositions(tmp2);
                }
              else
                {
                  tmp2.push_back(product.mPosition);
                }

              if (CCellDesignerImporter::findShortestConnection(tmp1, tmp2, pos1->second, pos2->second) == true)
                {
                  assert(tmp1.size() == 1);
                  assert(tmp2.size() == 1);
                  substrate.mPosition = tmp1[0];
                  product.mPosition = tmp2[0];
                }
            }
        }
    }
}

/**
 * Tries to set the species glyph id in the given species reference glyph.
 */
bool CCellDesignerImporter::setSpeciesGlyphId(SpeciesReferenceGlyph* pGlyph, const LinkTarget& link)
{
  bool result = false;

  // set the SpeciesGlyph
  if (pGlyph != NULL && !link.mAlias.empty())
    {
      // find the glyph
      std::map<std::string, GraphicalObject*>::const_iterator it = this->mCDIdToLayoutElement.find(link.mAlias);

      if (it != this->mCDIdToLayoutElement.end() && it->second != NULL)
        {
          pGlyph->setSpeciesGlyphId(it->second->getId());
          result = true;
        }
      else
        {
          // we have to search the dependency tree
          std::string root_id = this->findRootElementId(link.mAlias);
          assert(!root_id.empty());

          if (!root_id.empty())
            {
              it = this->mCDIdToLayoutElement.find(root_id);

              if (it != this->mCDIdToLayoutElement.end())
                {
                  pGlyph->setSpeciesGlyphId(it->second->getId());
                  result = true;
                }
            }
        }
    }

  return result;
}

/**
 * Tries to set the species reference id on the given SPeciesReferenceGlyph.
 */
bool CCellDesignerImporter::setSpeciesReferenceId(SpeciesReferenceGlyph* pGlyph, const LinkTarget& link, const std::string& reactionId)
{
  bool result = false;

  // set the species reference
  if (pGlyph != NULL && !link.mSpecies.empty() && !reactionId.empty())
    {
      // for pSRefGlyph1 we check if we find
      // a species reference that is pointing
      // to this id
      if (this->mpDocument != NULL && this->mpDocument->getModel() != NULL)
        {
          Reaction* pReaction = this->mpDocument->getModel()->getReaction(reactionId);
          assert(pReaction != NULL);

          if (pReaction != NULL)
            {
              ListOfSpeciesReferences* pList = NULL;

              switch (pGlyph->getRole())
                {
                  case SPECIES_ROLE_SUBSTRATE:
                  case SPECIES_ROLE_SIDESUBSTRATE:
                    pList = pReaction->getListOfReactants();
                    break;
                  case SPECIES_ROLE_PRODUCT:
                  case SPECIES_ROLE_SIDEPRODUCT:
                    pList = pReaction->getListOfProducts();
                    break;
                  default:
                    pList = pReaction->getListOfModifiers();
                    break;
                }

              if (pList != NULL)
                {
                  unsigned int i, iMax = pList->size();
                  SimpleSpeciesReference* pSRef = NULL;

                  for (i = 0; i < iMax; ++i)
                    {
                      pSRef = pList->get(i);

                      if (pSRef != NULL && pSRef->getSpecies() == link.mSpecies)
                        {
                          if (!pSRef->isSetId())
                            {
                              std::string id = this->createUniqueId("SpeciesReference");
                              pSRef->setId(id);
                              this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRef));
                            }

                          pGlyph->setSpeciesReferenceId(pSRef->getId());
                          result = true;
                          break;
                        }
                    }
                }
            }
        }
    }

  return result;
}


/**
 * Creates the structures for the modification links
 * in a reaction.
 * If processing fails, false is returned;
 */
bool CCellDesignerImporter::handleModificationLinks(ReactionGlyph* pRGlyph, ReactionAnnotation& ranno)
{
  bool result = true;

  if (pRGlyph != NULL)
    {
      unsigned int i, iMax = ranno.mModifications.size();

      if (iMax > 0)
        {
          if (pRGlyph->getCurve() != NULL &&
              pRGlyph->getCurve()->getNumCurveSegments() > 0
             )
            {
              for (i = 0; i < iMax && result == true; ++i)
                {
                  // TODO
                  // we only support CellDesigner 4 and upwards
                  // so the targetLineIndex is actually a pair of numbers where the first number
                  // is always -1 and we throw it away.
                  // the second number is the connection point index on the reaction glyph
                  // and we will need this once we have specific glyphs
                  // right now, we can use this value to determine the endpoint of the modification link
                  // as well

                  // since CellDesigner does not support branch type modifications,
                  // we will only take the first alias and we also ignore num0, num1 and num2

                  // modificationType is only useful for boolean modificiations and we don't do those
                  ReactionModification mod = ranno.mModifications[i];

                  if (mod.mType != BOOLEAN_LOGIC_GATE_AND_ML_TYPE &&
                      mod.mType != BOOLEAN_LOGIC_GATE_OR_ML_TYPE &&
                      mod.mType != BOOLEAN_LOGIC_GATE_NOT_ML_TYPE &&
                      mod.mType != BOOLEAN_LOGIC_GATE_UNKNOWN_ML_TYPE &&
                      !mod.mAliases.empty()
                     )
                    {
                      // TODO right now, I don't exactly know wht the offset means since I have not seen an example
                      // TODO But it seems to be used to calculte positions from edit points and since we currently
                      // TODO ignore edit points it should be save to ignore the offset as well

                      // find the best connection between the reaction glyph and the alias
                      // for this, we convert the targetLineIndex to a position and treat the reaction glyph
                      // as a box of a certain size to calculate the corresponding position

                      // the indices can be 4 (NW),2 (N),5 (NE), 6 (SW), 3 (S), 7 (SE) indices 0 and 1 are reserved for the connection of substrates
                      // and products respectively
                      // TODO actually the calculation is not that easy since the reaction glyphs in CellDesigner can be rotated
                      // TODO but for a first implementation, we can assume that 2 means up
                      POSITION r_pos = POSITION_UNDEFINED;

                      switch (mod.mTargetLineIndex)
                        {
                          case 4:
                            r_pos = POSITION_NW;
                            break;
                          case 2:
                            r_pos = POSITION_N;
                            break;
                          case 5:
                            r_pos = POSITION_NE;
                            break;
                          case 6:
                            r_pos = POSITION_SW;
                            break;
                          case 3:
                            r_pos = POSITION_S;
                            break;
                          case 7:
                            r_pos = POSITION_SE;
                            break;
                          default:
                            r_pos = POSITION_N;
                            break;
                        }

                      // we treat the reaction as a box
                      LineSegment* pLS = pRGlyph->getCurve()->getCurveSegment(0);
                      assert(pLS != NULL);

                      if (pLS != NULL)
                        {
                          double x1, x2, y1, y2;
                          x1 = pLS->getStart()->x();
                          y1 = pLS->getStart()->y();
                          x2 = pLS->getEnd()->x();
                          y2 = pLS->getEnd()->y();
                          Point tmpP(new LayoutPkgNamespaces(), x2 - x1, y2 - y1);
                          double tmp;
                          tmp = x1;
                          x1 = (x1 < x2) ? x1 : x2;
                          x2 = (x2 >= tmp) ? x2 : tmp;
                          tmp = y1;
                          y1 = (y1 < y2) ? y1 : y2;
                          y2 = (y2 >= tmp) ? y2 : tmp;
                          double width = x2 - x1;
                          double height = y2 - y1;
                          x1 = (x1 + x2) * 0.5;
                          y1 = (y1 + y2) * 0.5;
                          width = (width < 10.0) ? 10.0 : width;
                          height = (height < 10.0) ? 10.0 : height;
                          BoundingBox r_box;
                          Point position(new LayoutPkgNamespaces(), x1 - width*0.5, y1 - height*0.5);
                          Dimensions dim(new LayoutPkgNamespaces(), width, height);
                          r_box.setPosition(&position);
                          r_box.setDimensions(&dim);
                          Point connectionPoint = CCellDesignerImporter::getPositionPoint(r_box, r_pos);
                          // calculate the angle and rotate the connectPoint around
                          // that angle to get the real points
                          double angle = CCellDesignerImporter::angle(tmpP);
                          assert(angle == angle);

                          if (angle == angle)
                            {
                              // transfer box center to the origin before rotation
                              connectionPoint.setX(connectionPoint.x() - (x1 + x2)*0.5);
                              connectionPoint.setY(connectionPoint.y() - (y1 + y2)*0.5);
                              CCellDesignerImporter::rotate(connectionPoint, angle, tmpP);
                              connectionPoint = tmpP;
                              // transform result back to the original place
                              connectionPoint.setX(connectionPoint.x() + (x1 + x2)*0.5);
                              connectionPoint.setY(connectionPoint.y() + (y1 + y2)*0.5);
                            }

                          std::string alias = mod.mAliases[0];
                          // check if we have a target link to that alias
                          unsigned int j, jMax = mod.mLinkTargets.size();
                          POSITION targetPosition = POSITION_UNDEFINED;
                          LinkTarget linkTarget;

                          for (j = 0; j < jMax; ++j)
                            {
                              if (mod.mLinkTargets[j].mAlias == alias)
                                {
                                  linkTarget = mod.mLinkTargets[j];
                                  targetPosition = mod.mLinkTargets[j].mPosition;
                                }
                            }

                          std::map<std::string, BoundingBox>::const_iterator pos = this->mCDBounds.find(alias);
                          assert(pos != this->mCDBounds.end());

                          if (targetPosition == POSITION_UNDEFINED && pos != this->mCDBounds.end())
                            {
                              // with this position, we can calculate the closest anchor point on the alias
                              // if there is a linkTarget for the first alias, we might find a linkAnchor as well
                              // and save us the effort for the calculation
                              std::vector<POSITION> tmp;
                              CCellDesignerImporter::addAllPositions(tmp);
                              targetPosition = CCellDesignerImporter::findShortestConnection(connectionPoint, tmp, pos->second);
                            }

                          if (targetPosition != POSITION_UNDEFINED)
                            {
                              Point targetPoint = CCellDesignerImporter::getPositionPoint(pos->second, targetPosition);
                              // create the species glyph
                              SpeciesReferenceGlyph* pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                              assert(pSRefGlyph != NULL);

                              if (pSRefGlyph != NULL)
                                {
                                  // set the id
                                  std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                  pSRefGlyph->setId(id);
                                  this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));

                                  // set the role
                                  switch (mod.mType)
                                    {
                                      case INHIBITION_ML_TYPE:
                                      case UNKNOWN_INHIBITION_ML_TYPE:
                                      case TRANSCRIPTIONAL_INHIBITION_ML_TYPE:
                                      case TRANSLATIONAL_INHIBITION_ML_TYPE:
                                        pSRefGlyph->setRole(SPECIES_ROLE_INHIBITOR);
                                        break;
                                      case CATALYSIS_ML_TYPE:
                                        // find the stye that belongs to CATALYSIS
                                        // add the id of the species reference glyph to it
                                        {
                                            std::map<MODIFICATION_LINK_TYPE,LocalStyle*>::iterator pos=this->mModificationLinkStyleMap.find(CATALYSIS_ML_TYPE);
                                            assert(pos != this->mModificationLinkStyleMap.end());
                                            if(pos != this->mModificationLinkStyleMap.end())
                                            {
                                                assert(pos->second != NULL);
                                                if(pos->second != NULL)
                                                {
                                                  pos->second->addId(pSRefGlyph->getId());
                                                }
                                            }
                                        }
                                        break;
                                      case UNKNOWN_CATALYSIS_ML_TYPE:
                                        // find the stye that belongs to UNKNOWN_CATALYSIS
                                        // add the id of the species reference glyph to it
                                        {
                                            std::map<MODIFICATION_LINK_TYPE,LocalStyle*>::iterator pos=this->mModificationLinkStyleMap.find(UNKNOWN_CATALYSIS_ML_TYPE);
                                            assert(pos != this->mModificationLinkStyleMap.end());
                                            if(pos != this->mModificationLinkStyleMap.end())
                                            {
                                                assert(pos->second != NULL);
                                                if(pos->second != NULL)
                                                {
                                                  pos->second->addId(pSRefGlyph->getId());
                                                }
                                            }
                                        }
                                        break;
                                      case TRANSCRIPTIONAL_ACTIVATION_ML_TYPE:
                                      case TRANSLATIONAL_ACTIVATION_ML_TYPE:
                                        pSRefGlyph->setRole(SPECIES_ROLE_ACTIVATOR);
                                        break;
                                      default:
                                        pSRefGlyph->setRole(SPECIES_ROLE_MODIFIER);
                                        break;
                                    }

                                  // now we can create the connection from targetpoint to connectionPoint
                                  // the first vector for the coordinate system of the edit points is the vector
                                  // from connection point to target point

                                  Point v1(new LayoutPkgNamespaces(), connectionPoint.x() - targetPoint.x(), connectionPoint.y() - targetPoint.y());
                                  // the second vector is the vector with the same length that is orthogonal
                                  // to this vector
                                  Point v2(new LayoutPkgNamespaces());
                                  result = CCellDesignerImporter::createOrthogonal(v1, v2);

                                  if (result == true)
                                    {
                                      Point p3(new LayoutPkgNamespaces(), targetPoint.x() + v2.x(), targetPoint.y() + v2.y());
                                      Curve* pCurve = pSRefGlyph->getCurve();
                                      assert(pCurve != NULL);

                                      if (pCurve != NULL)
                                        {
                                          // calculate the absolute values of all points
                                          // and put them in a vector
                                          // then we go through the vector and create
                                          // the line segments
                                          // add all edit points
                                          std::vector<Point>::const_iterator pointIt = mod.mEditPoints.mPoints.begin(), pointsEnd = mod.mEditPoints.mPoints.end();
                                          Point p(new LayoutPkgNamespaces());
                                          std::vector<Point> points;

                                          while (pointIt != pointsEnd)
                                            {
                                              // create the absolute point
                                              p = CCellDesignerImporter::calculateAbsoluteValue(*pointIt, targetPoint, connectionPoint, p3);
                                              points.push_back(p);
                                              ++pointIt;
                                            }

                                          pLS = pCurve->createLineSegment();
                                          assert(pLS != NULL);

                                          if (pLS != NULL)
                                            {
                                              pLS->setStart(targetPoint.x(), targetPoint.y());
                                              pointIt = points.begin();
                                              pointsEnd = points.end();

                                              while (pointIt != pointsEnd && pLS != NULL)
                                                {
                                                  // set the current point as the end point
                                                  // of the current line segment
                                                  pLS->setEnd(pointIt->x(), pointIt->y());

                                                  // create a new line segment and set the current
                                                  // point as the start point
                                                  pLS = pCurve->createLineSegment();

                                                  if (pLS != NULL)
                                                    {
                                                      pLS->setStart(pointIt->x(), pointIt->y());
                                                    }

                                                  ++pointIt;
                                                }
                                            }

                                          if (pLS != NULL && result)
                                            {
                                              pLS->setEnd(connectionPoint.x(), connectionPoint.y());

                                              // set the species glyph id
                                              if (!linkTarget.mAlias.empty())
                                                {
                                                  this->setSpeciesGlyphId(pSRefGlyph, linkTarget);
                                                }

                                              // set the species reference id
                                              if (!linkTarget.mSpecies.empty())
                                                {
                                                  this->setSpeciesReferenceId(pSRefGlyph, linkTarget, pRGlyph->getReactionId());
                                                }
                                            }
                                        }
                                    }
                                  else
                                    {
                                      result = false;
                                    }
                                }
                            }
                          else
                            {
                              result = false;
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Creates the structures for the extra product links.
 * If processing fails, false is returned;
 */
bool CCellDesignerImporter::handleExtraReactionElements(ReactionGlyph* pRGlyph, ReactionAnnotation& ranno, bool substrate)
{
  bool result = true;

  if (pRGlyph != NULL)
    {
      std::vector<ReactantLink>::iterator it, endit;

      if (substrate)
        {
          it = ranno.mReactantLinks.begin();
          endit = ranno.mReactantLinks.end();
        }
      else
        {
          it = ranno.mProductLinks.begin();
          endit = ranno.mProductLinks.end();
        }

      if (it != endit)
        {
          if (pRGlyph->getCurve() != NULL &&
              pRGlyph->getCurve()->getNumCurveSegments() > 0
             )
            {
              while (it != endit && result == true)
                {
                  // has an alias that points to the GraphicalObject
                  if (!(*it).mAlias.empty())
                    {
                      std::map<std::string, BoundingBox>::const_iterator box_pos = this->mCDBounds.find((*it).mAlias);
                      assert(box_pos != this->mCDBounds.end());

                      if (box_pos != this->mCDBounds.end())
                        {
                          // has a position that defined where the alias is connected
                          // has a mTargetLineIndex which defines the line it is connected to
                          // for CellDesigner 4.0 and above the targetLineIndex is always -1,0
                          // because all products and all reactants are always connected to the
                          // same point
                          const LineSegment* pLS = NULL;
                          assert(pRGlyph->getCurve()->getNumCurveSegments() > 0);

                          if (substrate)
                            {
                              pLS = pRGlyph->getCurve()->getCurveSegment(0);
                            }
                          else
                            {
                              pLS = pRGlyph->getCurve()->getCurveSegment(pRGlyph->getCurve()->getNumCurveSegments() - 1);
                            }

                          assert(pLS != NULL);

                          if (pLS != NULL)
                            {
                              if ((*it).mPosition == POSITION_UNDEFINED)
                                {
                                  // get the position that is closest to the end point of the
                                  // reaction glyphs curve
                                  std::vector<POSITION> tmp;
                                  CCellDesignerImporter::addAllPositions(tmp);

                                  if (substrate)
                                    {
                                      (*it).mPosition = CCellDesignerImporter::findShortestConnection(*pLS->getStart(), tmp, box_pos->second);
                                    }
                                  else
                                    {
                                      (*it).mPosition = CCellDesignerImporter::findShortestConnection(*pLS->getEnd(), tmp, box_pos->second);
                                    }
                                }
                            }
                          else
                            {
                              result = false;
                            }

                          if (result && (*it).mPosition != POSITION_UNDEFINED)
                            {
                              SpeciesReferenceGlyph* pSRefGlyph = pRGlyph->createSpeciesReferenceGlyph();
                              assert(pSRefGlyph != NULL);

                              if (pSRefGlyph != NULL)
                                {
                                  // set an id
                                  std::string id = this->createUniqueId("SpeciesReferenceGlyph");
                                  pSRefGlyph->setId(id);
                                  this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pSRefGlyph));

                                  // set the role
                                  if (substrate)
                                    {
                                      pSRefGlyph->setRole(SPECIES_ROLE_SIDESUBSTRATE);
                                    }
                                  else
                                    {
                                      pSRefGlyph->setRole(SPECIES_ROLE_SIDEPRODUCT);
                                    }

                                  // set the curve
                                  Curve* pCurve = pSRefGlyph->getCurve();
                                  assert(pCurve != NULL);

                                  if (pCurve != NULL)
                                    {
                                      LineSegment* pLS2 = pCurve->createLineSegment();
                                      assert(pLS2 != NULL);

                                      if (pLS2 != NULL)
                                        {
                                          if (substrate)
                                            {
                                              pLS2->setEnd(pLS->getStart()->x(), pLS->getStart()->y());
                                            }
                                          else
                                            {
                                              pLS2->setEnd(pLS->getEnd()->x(), pLS->getEnd()->y());
                                            }

                                          Point p = CCellDesignerImporter::getPositionPoint(box_pos->second, (*it).mPosition);
                                          pLS2->setStart(p.x(), p.y());
                                        }
                                      else
                                        {
                                          result = false;
                                        }
                                    }
                                  else
                                    {
                                      result = false;
                                    }

                                  if (result == true)
                                    {
                                      // set the species glyph id
                                      LinkTarget lt;
                                      lt.mAlias = (*it).mAlias;
                                      result = this->setSpeciesGlyphId(pSRefGlyph, lt);

                                      if (result == true)
                                        {
                                          // has a mReactant which points to the model element
                                          // set the species reference id
                                          lt.mSpecies = (*it).mReactant;
                                          result = this->setSpeciesReferenceId(pSRefGlyph, lt, pRGlyph->getReactionId());
                                        }
                                    }
                                }

                              // TODO the mLine attribute species the color and the width, as well as
                              // TODO whether is is a straight line or a curve
                              // TODO Currently we assume that it is a straight line.
                            }
                        }
                      else
                        {
                          result = false;
                        }
                    }
                  else
                    {
                      result = false;
                    }

                  ++it;
                }
            }
          else
            {
              result = false;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Check if a color with the given color string already exists.
 * If so, the id of the color is set on the given id string.
 * If the color does not exist yet, a color definition for it is
 * created and the id of the newly created color is returned in
 * the id string.
 * If color creation fails, false is returned by the method.
 */
bool CCellDesignerImporter::findOrCreateColorDefinition(const std::string& color_string, std::string& id)
{
  bool result = true;
  std::map<std::string, std::string>::const_iterator color_pos = this->mColorStringMap.find(color_string);

  if (color_pos == this->mColorStringMap.end())
    {
      // we need to create a new ColorDefinition for this object first
      ColorDefinition* pDef = this->mpLocalRenderInfo->createColorDefinition();

      if (pDef != NULL)
        {
          // the color definition needs an id and we need to set the color values
          id = this->createUniqueId("ColorDefinition");
          pDef->setId(id);
          this->mIdMap.insert(std::pair<std::string, const SBase*>(id, pDef));
          result = pDef->setColorValue(color_string);

          if (result == true)
            {
              this->mColorStringMap.insert(std::pair<std::string, std::string>(color_string, id));
            }
          else
            {
              id = "";
            }
        }
    }
  else
    {
      id = color_pos->second;
    }

  return result;
}

/**
 * Tries to find the name for the given species identity.
 * If the name was found, it is returned in the name argument.
 * If something goes wrong, false is returend.
bool CCellDesignerImporter::findNameForSpeciesIdentity(const SpeciesIdentity& identity,std::string& name)
{
   bool result=true;
   switch(identity.mSpeciesClass)
   {
      case ION_CLASS:
      case SIMPLE_MOLECULE_CLASS:
      case COMPLEX_CLASS:
      case DRUG_CLASS:
      case UNKNOWN_CLASS:
      case PHENOTYPE_CLASS:
        name=identity.mNameOrReference;
        break;
      case PROTEIN_CLASS:
        {
            std::map<std::string,std::string>::const_iterator pos=this->mProteinNameMap.find(identity.mNameOrReference);
            assert(pos != this->mProteinNameMap.end());
            if(pos != this->mProteinNameMap.end())
            {
                name=pos->second;
            }
            else
            {
                result=false;
            }
        }
        break;
      case GENE_CLASS:
        {
            std::map<std::string,std::string>::const_iterator pos=this->mProteinNameMap.find(identity.mNameOrReference);
            assert(pos != this->mGeneNameMap.end());
            if(pos != this->mGeneNameMap.end())
            {
                name=pos->second;
            }
            else
            {
                result=false;
            }
        }
        break;
      case RNA_CLASS:
        {
            std::map<std::string,std::string>::const_iterator pos=this->mProteinNameMap.find(identity.mNameOrReference);
            assert(pos != this->mRNANameMap.end());
            if(pos != this->mRNANameMap.end())
            {
                name=pos->second;
            }
            else
            {
                result=false;
            }
        }
        break;
      case ANTISENSE_RNA_CLASS:
        {
            std::map<std::string,std::string>::const_iterator pos=this->mProteinNameMap.find(identity.mNameOrReference);
            assert(pos != this->mASRNANameMap.end());
            if(pos != this->mASRNANameMap.end())
            {
                name=pos->second;
            }
            else
            {
                result=false;
            }
        }
        break;
      case UNDEFINED_CLASS:
        result=false;
      default:
        break;
   }
   return result;
}
 */


/**
 * Goes through the dependency graph
 * and tries to find the root element for the given species alias id.
 */
std::string CCellDesignerImporter::findRootElementId(const std::string& id) const
{
  std::list<CCopasiNode<std::string>*>::const_iterator nit = this->mComplexDependencies.begin(), nendit = this->mComplexDependencies.end();
  const CCopasiNode<std::string>* pCurrent = NULL;

  while (nit != nendit)
    {
      pCurrent = *nit;

      while (pCurrent != NULL)
        {
          if (pCurrent->getData() == id)
            {
              break;
            }

          pCurrent = pCurrent->getNext();
        }

      if (pCurrent != NULL)
        {
          break;
        }

      ++nit;
    }

  std::string result;

  if (pCurrent != NULL)
    {
      result = pCurrent->getData();
    }

  return result;
}

/**
 * Tries to parse the CellDesigner species in the listOfIncludedSpecies.
 * If parsing fails, false is returned.
 */
bool CCellDesignerImporter::handleIncludedSpecies(const XMLNode* pNode)
{
  bool result = true;
  this->mIncludedSpeciesNameMap.clear();

  if (pNode != NULL && pNode->getName() == "listOfIncludedSpecies")
    {
      unsigned int i, iMax = pNode->getNumChildren();
      const XMLNode* pChild = NULL;

      for (i = 0; i < iMax; ++i)
        {
          pChild = &pNode->getChild(i);

          if (pChild != NULL &&
              pChild->getPrefix() == pNode->getPrefix() &&
              pChild->getName() == "species")
            {
              const XMLAttributes& attr = pChild->getAttributes();

              if (attr.hasAttribute("id") &&
                  attr.hasAttribute("name"))
                {
                  std::string id = attr.getValue("id");
                  std::string name = attr.getValue("name");
                  std::pair<std::string, SpeciesIdentity> pair;
                  pair.first = name;
                  assert(!id.empty());
                  assert(!name.empty());
                  // we need to check if there is an annotation child and parse it
                  // this annotation includes information about the identity
                  unsigned j = 0, jMax = pChild->getNumChildren();
                  const XMLNode* pAnnotation = NULL;

                  while (j != jMax)
                    {
                      if (pChild->getChild(j).getName() == "annotation")
                        {
                          pAnnotation = &pChild->getChild(j);
                          break;
                        }

                      ++j;
                    }

                  // there should be a name element in there somewhere
                  if (pAnnotation != NULL)
                    {
                      // now look for an identity node
                      const XMLNode* pIdent = NULL;
                      j = 0;
                      jMax = pAnnotation->getNumChildren();

                      while (j != jMax)
                        {
                          if (pAnnotation->getChild(j).getName() == "speciesIdentity")
                            {
                              pIdent = &pAnnotation->getChild(j);
                              break;
                            }

                          ++j;
                        }

                      if (pIdent != NULL)
                        {
                          SpeciesIdentity sident;
                          result = CCellDesignerImporter::parseSpeciesIdentity(pIdent, sident);
                          assert(result == true);

                          if (result == true)
                            {
                              // set the species identity
                              pair.second = sident;
                            }
                        }

                    }

                  this->mIncludedSpeciesNameMap.insert(std::pair<std::string, std::pair<std::string, SpeciesIdentity> >(id, pair));
                }
              else
                {
                  result = false;
                }
            }

        }
    }

  return result;
}

/**
 * Creates a vector that is orthogonal to the given first vector.
 * If there is a problem, false is returned.
 */
bool CCellDesignerImporter::createOrthogonal(const Point& v1, Point& v2)
{
  bool result = true;

  if (v1.x() == v1.x() &&
      v1.y() == v1.y() &&
      !(fabs(v1.x()) < 1e-20 &&
        fabs(v1.y()) < 1e-20)
     )
    {
      if (std::numeric_limits<double>::has_infinity)
        {
          double inf = std::numeric_limits<double>::infinity();

          if (v1.x() == inf ||
              v1.y() == inf ||
              v1.x() == -inf ||
              v1.y() == -inf)
            {
              result = false;
            }
          else
            {
              /*
              if(fabs(v1.x()) < 1e-20)
              {
                  // create horizontal line
                  v2.setX(-v1.y());
                  v2.setY(0.0);
              }
              else if(fabs(v1.y()) < 1e-20)
              {
                  // create vertical line
                  v2.setX(0.0);
                  v2.setY(v1.x());
              }
              else
              */
              {
                v2.setX(-v1.y());
                v2.setY(v1.x());
              }
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}


/**
 * Calculates the angle between the given vector and the positive x axis.
 * The result is returned in radians.
 */
double CCellDesignerImporter::angle(const Point& v)
{
  double result = std::numeric_limits<double>::quiet_NaN();

  if (!(v.x() == 0.0 && v.y() == 0.0))
    {
      result = acos(v.x() / sqrt(v.x() * v.x() + v.y() * v.y()));

      if (v.y() < 0.0)
        {
          result = 2.0 * M_PI - result;
        }
      else if (v.y() == 0.0 && v.x() < 0.0)
        {
          result = M_PI;
        }
    }

  return result;
}


/**
 * Calculates the position of point p after rotation by angle a
 * around the origin.
 * The angle is given in radians.
 * The result is returned in r.
 */
void CCellDesignerImporter::rotate(const Point& p, double a, Point& r)
{
  r.setX(p.x()*cos(a) - p.y()*sin(a));
  r.setY(p.x()*sin(a) + p.y()*cos(a));
}

/**
 * Tries to find the version number of CellDesigner that was used to write
 * this annotation.
 * The node should be the CellDesigner annotation of the model.
 * If the version number is not found or could not be parsed, we
 * return -1.
 */
double CCellDesignerImporter::determineVersion(const XMLNode* pNode)
{
  double version = -1.0;

  // first we check if we have CellDesigner 4.0 or higher
  if (pNode != NULL)
    {
      const XMLNode* pChild = CCellDesignerImporter::findChildNode(pNode, pNode->getPrefix(), "modelVersion", false);

      if (pChild != NULL)
        {
          // the version can probably be parsed as a double value
          if (pChild->getNumChildren() == 1 && pChild->getChild(0).isText())
            {
              std::string s = pChild->getChild(0).getCharacters();
              char** err = NULL;
              version = strtod(s.c_str(), err);

              if (!(err == NULL || *err != s.c_str() || version >= 4.0))
                {
                  version = -1.0;
                }
            }
        }
    }

  return version;
}

/**
 * Converts the given modification string to the correspnding MODIFICATION_TYPE enum value.
 * If no enum is found, UNDEFINED_MOD_TYPE is returned.
 */
SPECIES_MODIFICATION_TYPE CCellDesignerImporter::speciesModificationTypeToEnum(std::string cl)
{
  std::transform(cl.begin(), cl.end(), cl.begin(), toupper);
  SPECIES_MODIFICATION_TYPE result = UNDEFINED_MOD_TYPE;

  if (cl == "PHOSPHORYLATED")
    {
      result = PHOSPHORYLATED_MOD_TYPE;
    }
  else if (cl == "ACETYLATED")
    {
      result = ACETYLATED_MOD_TYPE;
    }
  else if (cl == "UBIQUITINATED")
    {
      result = UBIQUITINATED_MOD_TYPE;
    }
  else if (cl == "METHYLATED")
    {
      result = METHYLATED_MOD_TYPE;
    }
  else if (cl == "HYDROXYLATED")
    {
      result = HYDROXYLATED_MOD_TYPE;
    }
  else if (cl == "DON'T CARE")
    {
      result = DONTCARE_MOD_TYPE;
    }
  else if (cl == "EMPTY") // "empty" is not mentioned in the specification, but it seems to occur in SBML files written by CellDesigner
    {
      // actually as far as I can see from the rendering in CellDesigner, "empty" means "draw the circle, but leave it unfilled"  
      result = EMPTY_MOD_TYPE;
    }
  else if (cl == "UNKNOWN")
    {
      result = UNKNOWN_MOD_TYPE;
    }
  else if (cl == "GLYCOSYLATED")
    {
      result = GLYCOSYLATED_MOD_TYPE;
    }
  else if (cl == "MYRISTOYLATED")
    {
      result = MYRISTOYLATED_MOD_TYPE;
    }
  else if (cl == "PALMYTOYLATED")
    {
      result = PALMYTOYLATED_MOD_TYPE;
    }
  else if (cl == "PRENYLATED")
    {
      result = PRENYLATED_MOD_TYPE;
    }
  else if (cl == "PROTONATED")
    {
      result = PROTONATED_MOD_TYPE;
    }
  else if (cl == "SUFLATED")
    {
      result = SUFLATED_MOD_TYPE;
    }

  return result;
}

/**
 * Returns the color string for the given color id
 * or an empty string if the color id was not found.
 */
std::string CCellDesignerImporter::getColorString(const std::string& color_id) const
{
  std::string result;
  std::map<std::string, std::string>::const_iterator it = this->mColorStringMap.begin(), endit = this->mColorStringMap.end();

  while (it != endit)
    {
      if (it->second == color_id)
        {
          result = it->first;
          break;
        }

      ++it;
    }

  return result;
}

ReactionModification::ReactionModification() :
    mAliases()
    , mModifiers()
    , mType(UNDEFINED_ML_TYPE)
    , mTargetLineIndex(std::numeric_limits<int>::max())
    , mEditPoints()
    , mNum0(std::numeric_limits<int>::max())
    , mNum1(std::numeric_limits<int>::max())
    , mNum2(std::numeric_limits<int>::max())
    , mModType(UNDEFINED_MTYPE)
    , mOffset(Point(new LayoutPkgNamespaces(), 0.0, 0.0))
{}

ReactionAnnotation::ReactionAnnotation() :
    mName("")
    , mType(UNDEFINED_RTYPE)
    , mBaseReactants()
    , mBaseProducts()
    , mReactantLinks()
    , mProductLinks()
    , mConnectScheme()
    , mOffset(Point(new LayoutPkgNamespaces(), 0.0, 0.0))
    , mEditPoints()
    , mLine(Line())
    , mModifications()
{}

CompartmentAlias::CompartmentAlias() :
    mId("")
    , mCompartment("")
    , mClass(UNDEFINED_CLASS)
    , mNamePoint(Point(new LayoutPkgNamespaces(), 0.0, 0.0))
    , mDoubleLine()
    , mPaint()
    , mBounds()
    , mFontSize(12.0)
{}

UsualView::UsualView() :
    mInnerPosition(Point(new LayoutPkgNamespaces(), 0.0, 0.0))
    , mBoxSize(Dimensions(new LayoutPkgNamespaces(), 0.0, 0.0))
    , mLineWidth(0.0)
    , mPaint()
{}

LinkTarget::LinkTarget() :
    mAlias(""),
    mSpecies(""),
    mPosition(POSITION_UNDEFINED)
{}

SpeciesModification::SpeciesModification() :
    mResidue("")
    , mType(UNDEFINED_MOD_TYPE)
{}

SpeciesState::SpeciesState():
    mModifications()
{}

SpeciesIdentity::SpeciesIdentity():
    mSpeciesClass(UNDEFINED_CLASS),
    mNameOrReference("")
{}

SpeciesAnnotation::SpeciesAnnotation():
    mPosition(UNDEFINED_POSITION),
    mParentComplex(""),
    mIdentity(SpeciesIdentity())
{}

CompartmentAnnotation::CompartmentAnnotation():
    mName("")
{}

Line::Line():
    mColor("#FF000000"),
    mWidth(0.0),
    mCurve(false)
{}

LineDirection::LineDirection() :
    mIndex(std::numeric_limits<int>::max())
    , mArm(std::numeric_limits<int>::max())
    , mValue(DIRECTION_UNDEFINED)
{}

ConnectScheme::ConnectScheme() :
    mPolicy(POLICY_UNDEFINED)
    , mRectangleIndex(0)
    , mLineDirections()
{}

EditPoints::EditPoints() :
    mNum0(std::numeric_limits<int>::max())
    , mNum1(std::numeric_limits<int>::max())
    , mNum2(std::numeric_limits<int>::max())
    , mOmittedShapeIndex(std::numeric_limits<int>::max())
    , mTShapeIndex(std::numeric_limits<int>::max())
    , mPoints()
{}

ReactantLink::ReactantLink() :
    mAlias("")
    , mReactant("")
    , mTargetLineIndex(std::numeric_limits<int>::max())
    , mPosition(POSITION_UNDEFINED)
    , mLine()
{}

CellDesignerSpecies::CellDesignerSpecies() :
    mId("")
    , mName("")
    , mCompartment("")
    , mAnnotation()
{}

Paint::Paint() :
    mColor("#FF000000")
    , mScheme(PAINT_UNDEFINED)
{}

DoubleLine::DoubleLine() :
    mInnerWidth(0.0)
    , mOuterWidth(0.0)
    , mThickness(0.0)
{}

SpeciesAlias::SpeciesAlias() :
    mId("")
    , mSpecies("")
    , mComplexSpeciesAlias("")
    , mCompartmentAlias("")
    , mFontSize(12.0)
    , mComplex(false)
    , mBounds()
    , mUView()
{}

ProteinModification::ProteinModification() :
    mId(""),
    mName(""),
    mAngle(0.0)
{}

Protein::Protein():
    mId(""),
    mName(""),
    mType(PROTEIN_CLASS)
{}








