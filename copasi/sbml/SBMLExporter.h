/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/09/30 15:26:26 $
   End CVS Header */

#ifndef SBMLExpoter_H__
#define SBMLExpoter_H__

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "function/CKinFunction.h"

#include "sbml/SBMLDocument.hpp"
#include "sbml/Model.hpp"
#include "sbml/Compartment.hpp"
#include "sbml/Species.hpp"
#include "sbml/Reaction.hpp"
#include "sbml/KineticLaw.hpp"
#include "sbml/ASTNode.hpp"
#include "sbml/Parameter.hpp"
#include "sbml/StdException.h"

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

    /**
     **  This method takes a copasi CModel object and generates a SBMLDocument
     ** object from it.
     ** Optionally the method takes two integers that specify the level and the
     ** version number of the SBMLDocument that will be generated.
     */
    SBMLDocument* createSBMLDocumentFromCModel(const CModel* copasiModel, int sbmlLevel = 2, int sbmlVersion = 1);

    /**
     ** This method taked a copasi CModel and generates a SBML Model object
     **  which is returned. On failure NULL is returned.
     */
    Model* createSBMLModelFromCModel(const CModel* copasiModel);

    /**
     ** This method takes a pointer to a copasi CCompartment object and creates
     ** a SBML Compartment. The pointer to the SBML Comprtment is returned.
     */
    Compartment* createSBMLCompartmentFromCCompartment(const CCompartment* copasiCompartment);

    /**
     ** This method takes a pointer to a copasi CMetab object and creates a SBML 
     ** Species object. The pointer to the species object is returned.
     */
    Species* createSBMLSpeciesFromCMetab(const CMetab* copasiMetabolite);

    /**
     ** This method takes a pointer to a copasi CReaction object and creates an
     ** SBML Reaction object. The pointer to the created reaction object is
     ** returned.
     */
    Reaction* createSBMLReactionFromCReaction(const CReaction* reaction);

    /**
     ** This method takes a pointer to a copasi CReation object and creates a
     ** SBML KineticLaw object from the kintik function of the copasi reaction
     ** object. The pointer to the created KineticLaw is returned.
     */
    KineticLaw* createSBMLKineticLawFromCReaction(const CReaction* copasiReaction);

    /**
     ** This method takes a string that specifies the time unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition* createSBMLTimeUnitDefinitionFromCopasiTimeUnit(const std::string u);

    /**
     ** This method takes a string that specifies the substance unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition* createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(const std::string u);

    /**
     ** This method takes a string that specifies the volume unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition* createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(const std::string u);

    /**
     ** This method creates an ASTNode tree where all the species specified in
     ** the given vector are multiplied. This is used to create the mass action
     ** kinetic law.
     */
    ASTNode* createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos = 0);

    /**
     ** This method takes the left side of the topmost CNodeK object tree in a
     ** copasi CKinFunction object. This CNodeK object corresponds to the
     ** function tree of the kinetic function. Additionally the kintic function
     ** object and the parameter mapping vector are given as argumtns to the
     ** function.
     ** The method returns the corresponding ASTNode tree for use in the SBML
     ** KineticLaw object.
     */
    ASTNode* createASTNodeFromCNodeK(const CNodeK& cNodeK, const CKinFunction& kinFunction, const std::vector< std::vector < std::string > >& vect);

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
    bool exportSBML(const CModel* copasiModel, std::string sbmlFilename, int sbmlLevel = 2, int sbmlVersion = 1) throw (StdException);

    /**
    ** This method tests if a string only consists of whitespace characters
    */
    bool isEmptyString(const std::string str);
  };

#endif
