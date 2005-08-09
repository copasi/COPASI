/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/08/09 14:28:25 $
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

    std::list<const CEvaluationTree*> mUsedFunctions;

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
     ** This method takes a pointer to a copasi CEvaluationTree object and creates
     ** a SBML FunctionDefinition. The pointer to the SBML FunctionDefinition is returned.
     */
    FunctionDefinition* createSBMLFunctionDefinitionFromCEvaluationTree(const CEvaluationTree* tree, const std::map<std::string, std::string>& replacementMap);

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

    /**
     * Checks if a given tree is multiplied by a compartment identifier.
     * If so, a copy of the tree is returned in which the multiplication has been removed.
     */
    ASTNode* isDividedByVolume(const ASTNode* node, const std::string& compartmentSBMLId);

    /**
     * Create the function definitions for all functions used in the model.
     */
    void createFunctionDefinitions();

    /**
     * Recursively go through a function tree and find all functions that are used.
     * This also covers function called by function call etc.
     * If a loop is encountered this throws an exception.
     */
    void findUsedFunctions(CEvaluationNode* pNode, std::list<const CEvaluationTree*>& usedFunctionList);

    /**
     * Check if some CEvaluationTree is already in a list.
     */
    bool existsInList(CEvaluationTree* tree, const std::list<const CEvaluationTree*>& list);

    /**
     * Go through a tree of ASTNodes and replace the names of all function calls
     * with the one given in the replacementMap.
     */
    void replaceFunctionNames(ASTNode* pNode, const std::map<std::string, std::string> replacementMap);

    /**
     * Checks if the given string is a valid SBMLId.
     */
    bool isValidSId(const std::string& id);

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

    /**
     * Create a unique id for an SBML object.
     * I can't just take the Copasi key of the object since this might conflict
     * with an already existing sbml id which came from the sbmlid attribute in a
     * copasi file or directly by importing an SBML file.
     */
    static std::string createUniqueId(const std::set<std::string>* pIdSet, const std::string& prefix);

    std::set<std::string>* createIdSet(const Model* pSBMLModel);

    SBMLDocument* getSBMLDocument() const;
  };

#endif
