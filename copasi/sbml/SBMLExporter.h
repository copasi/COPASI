/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/11 16:26:03 $
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

class SBMLExporter
  {
  protected:
    static const char* HTML_HEADER = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n<title>Comments</title>\n</head><body>";

    static const char* HTML_FOOTER = "</body>\n</html>";

    SBMLDocument_t* sbmlDocument;

    SBMLDocument_t* createSBMLDocumentFromCModel(const CModel* copasiModel, int sbmlVersion, int sbmlLevel);
    Model_t* createSBMLModelFromCModel(const CModel* copasiModel);
    Compartment_t* createSBMLCompartmentFromCCompartment(const CCompartment* copasiCompartment);
    Species_t* createSBMLSpeciesFromCMetab(const CMetab* copasiMetabolite);
    Reaction_t* createSBMLReactionFromCReaction(const CReaction* reaction);
    KineticLaw_t* createSBMLKineticLawFromCKinFunction(const CKinFunction* cKinFunction);

    UnitDefinition_t* createSBMLTimeUnitDefinitionFromCopasiTimeUnit(CModel::TimeUnit u);
    UnitDefinition_t* createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(CModel::QuantityUnit u);
    UnitDefinition_t* createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(CModel::VolumeUnit u);

  public:
    SBMLExporter();
    virtual ~SBMLExporter();
    bool exportSBML(const CModel* copasiModel, std::string sbmlFilename) throw (StdException);
  };

#endif
