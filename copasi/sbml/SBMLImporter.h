/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/11 08:43:28 $
   End CVS Header */

#ifndef SBMLIMPORTER_HPP
#define SBMLIMPORTER_HPP

#include <string>
#include <map>
#include "sbml/ASTNode.hpp"

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

/**
 * Simple exception class that implements the what() function of std::exception
 * to specify an error message.
 */
class StdException: public std::exception
  {
  public:
    /**
     * Constructor that sets the error message object to "Error."
     */
    StdException() throw();

    /**
     * Constructor that sets the error message object to the string given.
     */
    explicit StdException(const std::string what) throw();

    /**
     * Destructor that does nothing.
     */
    virtual ~StdException() throw();

    /**
     * Returns the error message object as a character array.
     */
    virtual const char* what() const throw();

  protected:
    std::string message;
  };

class SBMLImporter
  {
  protected:
    std::map<std::string, CMetab*> speciesMap;
    //std::map<std::string,CCompartment*> compartmentMap;

    /**
     * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
     */
    CModel* createCModelFromSBMLDocument(SBMLDocument* doc) throw(StdException);

    /**
     * Creates and returns a Copasi CCompartment from the SBML Compartment
     * given as argument.
     */
    CCompartment* createCCompartmentFromCompartment(const Compartment* sbmlComp, CModel* copasiModel);

    /**
     * Creates and returns a Copasi CMetab from the given SBML Species object.
     */
    CMetab* createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment);

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
    void replaceSubstanceNames(ConverterASTNode* node, std::map<std::string, std::string> substances);

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

  public:
    SBMLImporter();
    ~SBMLImporter();
    CModel* readSBML(std::string filename);
  };

#endif
