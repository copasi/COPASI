/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/12 16:30:48 $
   End CVS Header */

#ifndef SBMLExpoter_H__
#define SBMLExpoter_H__

#include <set>
#include <string>

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "function/CKinFunction.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Reaction.h"
#include "sbml/KineticLaw.h"
#include "sbml/math/ASTNode.h"
#include "sbml/Parameter.h"

class SBMLExporter
  {
  protected:
    /* HTML header that will be prepended to the comments of CModel to generate
    ** a valid SBML note. 
    */
    static const char* HTML_HEADER;

    /* HTML header that will be appended to the comments of CModel to generate
    ** a valid SBML note. 
    */
    static const char* HTML_FOOTER;

    /* the sbml document that is being generated. */
    SBMLDocument* sbmlDocument;

    /* A vector that holds the objects that have been handled during export.
     * This is needed to be able to delete objects that are no longer there 
     * from the sbml model.
     */
    std::vector<SBase*> mHandledSBMLObjects;

    std::set<std::string>* mpIdSet;

    CModel* mpCopasiModel;

    /**
     **  This method takes a copasi CModel object and generates a SBMLDocument
     ** object from it.
     ** Optionally the method takes two integers that specify the level and the
     ** version number of the SBMLDocument that will be generated.
     */
    SBMLDocument* createSBMLDocumentFromCModel(CModel* copasiModel, int sbmlLevel = 2, int sbmlVersion = 1);

    /**
     ** This method taked a copasi CModel and generates a SBML Model object
     **  which is returned. On failure NULL is returned.
     */
    Model* createSBMLModelFromCModel(CModel* copasiModel);

    /**
     ** This method takes a pointer to a copasi CCompartment object and creates
     ** a SBML Compartment. The pointer to the SBML Comprtment is returned.
     */
    Compartment* createSBMLCompartmentFromCCompartment(CCompartment* copasiCompartment);

    /**
     ** This method takes a pointer to a copasi CMetab object and creates a SBML 
     ** Species object. The pointer to the species object is returned.
     */
    Species* createSBMLSpeciesFromCMetab(CMetab* copasiMetabolite);

    /**
     ** This method takes a pointer to a copasi CModelValue object and creates a SBML 
     ** Parameter object. The pointer to the parameter object is returned.
     */
    Parameter* createSBMLParameterFromCModelValue(CModelValue* pModelValue);

    /**
     ** This method takes a pointer to a copasi CReaction object and creates an
     ** SBML Reaction object. The pointer to the created reaction object is
     ** returned.
     */
    Reaction* createSBMLReactionFromCReaction(CReaction* reaction);

    /**
     ** This method takes a pointer to a copasi CReation object and creates a
     ** SBML KineticLaw object from the kintik function of the copasi reaction
     ** object. The pointer to the created KineticLaw is returned.
     */
    KineticLaw* createSBMLKineticLawFromCReaction(CReaction* copasiReaction);

    /**
     ** This method takes a string that specifies the time unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition* createSBMLTimeUnitDefinitionFromCopasiTimeUnit(const std::string& u);

    /**
     ** This method takes a string that specifies the substance unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition* createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(const std::string& u);

    /**
     ** This method takes a string that specifies the volume unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition* createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(const std::string& u);

    /**
     ** This method creates an ASTNode tree where all the species specified in
     ** the given vector are multiplied. This is used to create the mass action
     ** kinetic law.
     */
    ASTNode* createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos = 0);

    /**
     * Replaces the name on all nodes with oldName with newName.
     */
    void replaceNodeName(ASTNode* pNode, const std::string& oldName, const std::string& newName);

    /**
     * Remove all compartments, species, parameters and reactions
     * that did not end up in mHandledSBMLObjects during an export.
     * Additionally remove all function definitions and all unit
     * definitions that have not been used in the file.   
     */
    void removeUnusedObjects();

    /**
     * Removes all UnitDefinition objects that have not been used.
     */
    void removeUnusedFunctionDefinitions();

    /**
     * Removes all FunctionDefinition objects that have not been used.
     */
    void removeUnusedUnitDefinitions();

  public:

    /**
     ** Constructor for the exporter.
     */
    SBMLExporter();

    /**
     ** Destructor for the exporter.
     */
    virtual ~SBMLExporter();

    /**
     ** This method takes a copasi CModel object, crerates an SBMLDocument from
     ** it and writes it to a file. The filename is given as the second
     ** argument to the function. The function return "true" on success and
     ** "false" on failure.
     */
    bool exportSBML(CModel* copasiModel, std::string sbmlFilename, bool overwriteFile = false, int sbmlLevel = 2, int sbmlVersion = 1);

    /**
    ** This method tests if a string only consists of whitespace characters
    */
    bool isEmptyString(const std::string& str);

    static std::string createUniqueId(const std::set<std::string>* pIdSet, const std::string& prefix);

    std::set<std::string>* createIdSet(const Model* pSBMLModel);
  };

#endif
