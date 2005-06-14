/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/14 09:43:00 $
   End CVS Header */

#ifndef SBMLIMPORTER_H__
#define SBMLIMPORTER_H__

#include <string>
#include <map>
#include "sbml/math/ASTNode.h"

#include "function/CFunctionDB.h"
#include "sbml/StdException.h"
#include "sbml/UnitDefinition.h"
#include "model/CModel.h"

class SBMLDocument;
class CCompartment;
class CMetab;
class CReaction;
class Reaction;
class Species;
class Model;
class Compartment;
class SBMLDocument;
class ConverterASTNode;
class Parameter;
class FunctionDefinition;
class SBase;

class SBMLImporter
  {
  protected:
    std::map<std::string, CMetab*> speciesMap;
    CFunctionDB* functionDB;
    bool mIncompleteModel;
    unsigned int pLevel;

    /**
     * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
     */
    CModel* createCModelFromSBMLDocument(SBMLDocument* doc, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CCompartment from the SBML Compartment
     * given as argument.
     */
    CCompartment* createCCompartmentFromCompartment(const Compartment* sbmlComp, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CMetab from the given SBML Species object.
     */
    CMetab* createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CModelValue from the given SBML Parameter object.
     */
    CModelValue* createCModelValueFromParameter(const Parameter* sbmlParameter, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Creates and returns a Copasi CReaction object from the given SBML
     * Reaction object.
     */
    CReaction* createCReactionFromReaction(const Reaction* sbmlReaction, const Model* sbmlModel, CModel* cmodel, std::map<std::string, CCompartment*> compartmentMap, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

    /**
     * Traverses the brach of the given AST node recursively and prefixes all substrate
     * parameters with "substrate_", all product parameters with "product_" and all modifier parameters with "modifier_".
     */
    void replaceSubstanceNames(ConverterASTNode* node, const Reaction* reaction);

    /**
     * Recursively replaces all parameter names in the branch of the given AST node
     * with the ones give in the map.
     */
    void replaceSubstanceNames(ConverterASTNode* node, std::map< std::string, std::map <std::string, std::string > > substMap, const std::vector<std::string>& shadowedSubstances, bool reversible);

    /**
     * Replaces SBML user defined functions with the actual funtcion definition.
     */
    ConverterASTNode* replaceUserDefinedFunctions(ASTNode* node, const Model* model);

    /**
     * Creates a map of each parameter of the function definition and its
     * corresponding parameter in the function call.
     */
    std::map<std::string , ASTNode*> createBVarMap(const ASTNode* uDefFunction, const ASTNode* function);

    /**
     * Returns the user defined SBML function definition that belongs to the given
     * name, or NULL if none can be found.
     */
    FunctionDefinition* getFunctionDefinitionForName(const std::string name, const Model* model);

    /**
     * Replaces the variables in a function definition with the actual function
     * parameters that were used when the function was called. The function returns
     * a pointer to the ConverterAST node with the replaced variables.
     */
    ConverterASTNode* replaceBvars(const ASTNode* node, std::map<std::string, ASTNode*> bvarMap);

    /**
     * This function replaces the AST_FUNCTION_POWER ASTNodes in a ASTNode tree
     * with the AST_POWER node.
     */
    void replacePowerFunctionNodes(ASTNode* node);

    /**
     * Returns the copasi VolumeUnit corresponding to the given SBML Volume
     *  UnitDefinition.
     */
    CModel::VolumeUnit handleVolumeUnit(const UnitDefinition* uDef);

    /**
     * Returns the copasi QuantityUnit corresponding to the given SBML
     *  Substance UnitDefinition.
     */
    CModel::QuantityUnit handleSubstanceUnit(const UnitDefinition* uDef);

    /**
     * Returns the copasi TimeUnit corresponding to the given SBML Time
     *  UnitDefinition.
     */
    CModel::TimeUnit handleTimeUnit(const UnitDefinition* uDef);

    /**
     * Replaces all compartment nodes in an AST tree with the initial volume of the compartment.
     */
    void replaceCompartmentNodes(ConverterASTNode* node, std::map<std::string, CCompartment*> compartmentMap);

    /**
     * Replaces all occurences of the log function with two arguments by
     * a division of two separate calls to log.
     */
    void replaceLog(ConverterASTNode* sourceNode);

    /**
     * Replaces all occurences of the root function with two arguments by
     * a call to the power function with the inverse of the first argument.
     */
    void replaceRoot(ConverterASTNode* sourceNode);

    /**
     * Replaces all + and * nodes that have zero or one argument.
     */
    void replaceFunnyOperatorCalls(ConverterASTNode* sourceNode);

  public:
    SBMLImporter();
    ~SBMLImporter();
    CModel* readSBML(std::string filename, CFunctionDB* funDB, SBMLDocument* pSBMLDocument, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);
  };

#endif
