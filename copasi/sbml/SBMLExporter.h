/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/15 08:15:01 $
   End CVS Header */

#ifndef SBMLExpoter_H__
#define SBMLExpoter_H__

#include "SBMLImporter.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CKinFunction.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Reaction.h"
#include "sbml/KineticLaw.h"
#include "sbml/ASTNode.h"
#include "sbml/Parameter.h"

class SBMLExporter
  {
  protected:
    /* HTML header that will be prepended to the comments of CModel to generate
    ** a valid SBML note. 
    */
    static const char* HTML_HEADER; // "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n<title>Comments</title>\n</head><body>";

    /* HTML header that will be appended to the comments of CModel to generate
    ** a valid SBML note. 
    */
    static const char* HTML_FOOTER; // "</body>\n</html>";

    /* the sbml document that is being generated. */
    SBMLDocument_t* sbmlDocument;

    /**
     **  This method takes a copasi CModel object and generates a SBMLDocument
     ** object from it.
     ** Optionally the method takes two integers that specify the level and the
     ** version number of the SBMLDocument that will be generated.
     */
    SBMLDocument_t* createSBMLDocumentFromCModel(const CModel* copasiModel, int sbmlLevel = 2, int sbmlVersion = 1);

    /**
     ** This method taked a copasi CModel and generates a SBML Model object
     **  which is returned. On failure NULL is returned.
     */
    Model_t* createSBMLModelFromCModel(const CModel* copasiModel);

    /**
     ** This method takes a pointer to a copasi CCompartment object and creates
     ** a SBML Compartment. The pointer to the SBML Comprtment is returned.
     */
    Compartment_t* createSBMLCompartmentFromCCompartment(const CCompartment* copasiCompartment);

    /**
     ** This method takes a pointer to a copasi CMetab object and creates a SBML 
     ** Species object. The pointer to the species object is returned.
     */
    Species_t* createSBMLSpeciesFromCMetab(const CMetab* copasiMetabolite);

    /**
     ** This method takes a pointer to a copasi CReaction object and creates an
     ** SBML Reaction object. The pointer to the created reaction object is
     ** returned.
     */
    Reaction_t* createSBMLReactionFromCReaction(const CReaction* reaction);

    /**
     ** This method takes a pointer to a copasi CReation object and creates a
     ** SBML KineticLaw object from the kintik function of the copasi reaction
     ** object. The pointer to the created KineticLaw is returned.
     */
    KineticLaw_t* createSBMLKineticLawFromCReaction(const CReaction* copasiReaction);

    /**
     ** This method takes a string that specifies the time unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition_t* createSBMLTimeUnitDefinitionFromCopasiTimeUnit(const std::string u);

    /**
     ** This method takes a string that specifies the substance unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition_t* createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(const std::string u);

    /**
     ** This method takes a string that specifies the volume unit used in the
     ** copasi model and returns a pointer to the corresponding SBML
     ** UnitDefinition object.
     */
    UnitDefinition_t* createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(const std::string u);

    /**
     ** This method creates an ASTNode tree where all the species specified in
     ** the given vector are multiplied. This is used to create the mass action
     ** kinetic law.
     */
    ASTNode_t* createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos = 0);

    /**
     ** This method takes the left side of the topmost CNodeK object tree in a
     ** copasi CKinFunction object. This CNodeK object corresponds to the
     ** function tree of the kinetic function. Additionally the kintic function
     ** object and the parameter mapping vector are given as argumtns to the
     ** function.
     ** The method returns the corresponding ASTNode tree for use in the SBML
     ** KineticLaw object.
     */
    ASTNode_t* createASTNodeFromCNodeK(const CNodeK& cNodeK, const CKinFunction& kinFunction, const std::vector< std::vector < std::string > >& vect);

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
  };

#endif
