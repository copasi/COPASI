/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/21 09:49:29 $
   End CVS Header */

#ifndef SBMLIMPORTER_H__
#define SBMLIMPORTER_H__

#include <string>
#include <map>
#include "sbml/ASTNode.hpp"

#include "function/CFunctionDB.h"
#include "sbml/StdException.h"

class SBMLDocument;
class CModel;
class CCompartment;
class CMetab;
class CReaction;
class Reaction;
class Species;
class Model;
class Compartment;
class SBMLDocument;
class ConverterASTNode;
class FunctionDefinition;

class SBMLImporter
  {
  protected:
    std::map<std::string, CMetab*> speciesMap;
    CFunctionDB* functionDB;

    /**
     * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
     */
    CModel* createCModelFromSBMLDocument(SBMLDocument* doc) throw(StdException);

    /**
     * Creates and returns a Copasi CCompartment from the SBML Compartment
     * given as argument.
     */
    CCompartment* createCCompartmentFromCompartment(const Compartment* sbmlComp, CModel* copasiModel) throw(StdException);

    /**
     * Creates and returns a Copasi CMetab from the given SBML Species object.
     */
    CMetab* createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment) throw(StdException);

    /**
     * Creates and returns a Copasi CReaction object from the given SBML
     * Reaction object.
     */
    CReaction* createCReactionFromReaction(const Reaction* sbmlReaction, const Model* sbmlModel, CModel* cmodel) throw(StdException);

    /**
     * Traverses the brach of the given AST node recursively and prefixes all substrate
     * parameters with "substrate_", all product parameters with "product_" and all modifier parameters with "modifier_".
     */
    void replaceSubstanceNames(ConverterASTNode* node, const Reaction* reaction);

    /**
     * Recursively replaces all parameter names in the branch of the given AST node
     * with the ones give in the map.
     */
    void replaceSubstanceNames(ConverterASTNode* node, std::map< std::string, std::map <std::string, std::string > > substMap, bool reversible);

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

  public:
    SBMLImporter();
    ~SBMLImporter();
    CModel* readSBML(std::string filename, CFunctionDB* funDB) throw(StdException);
  };

#endif
