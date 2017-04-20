// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000098.h"

#include <sstream>
#include <fstream>
#include "utilities.hpp"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/xml/XMLNode.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CEvent.h"

void test000098::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  pDataModel = CRootContainer::addDatamodel();
}

void test000098::tearDown()
{
  CRootContainer::destroy();
}

// tests whether we are importing notes on all elemnts
void test000098::test_import_notes()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // import the file and check if we find all the notes
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(SBML_MODEL_1));
  // check if all the elements have notes
  const CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  std::string notes = pModel->getNotes();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on model") != std::string::npos);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 1);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  // compartment
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  notes = pCompartment->getNotes();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on compartment") != std::string::npos);
  // species
  const CMetab* pMetab = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pMetab != NULL);
  notes = pMetab->getNotes();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on species") != std::string::npos);
  // reaction
  const CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);
  notes = pReaction->getNotes();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on reaction") != std::string::npos);
  // parameter
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  notes = pModelValue->getNotes();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on parameter") != std::string::npos);
  // event
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  notes = pEvent->getNotes();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on event") != std::string::npos);
}

// tests whether we are importing global render information
void test000098::test_export_notes()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  std::istringstream iss(test000098::CPS_MODEL_1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!s.empty());
  SBMLReader reader;
  SBMLDocument* pSBMLDocument = NULL;

  try
    {
      pSBMLDocument = reader.readSBMLFromString(s);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(pSBMLDocument != NULL);
  Model* pModel = pSBMLDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->isSetNotes() == true);
  std::string notes = pModel->getNotesString();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on model") != std::string::npos);

  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pModel->getNumEvents() == 1);
  // compartment
  SBase* pObject = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isSetNotes() == true);
  notes = pObject->getNotesString();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on compartment") != std::string::npos);
  // species
  pObject = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isSetNotes() == true);
  notes = pObject->getNotesString();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on species") != std::string::npos);
  // parameter
  pObject = pModel->getParameter(0);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isSetNotes() == true);
  notes = pObject->getNotesString();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on parameter") != std::string::npos);
  // reaction
  pObject = pModel->getReaction(0);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isSetNotes() == true);
  notes = pObject->getNotesString();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on reaction") != std::string::npos);
  // event
  pObject = pModel->getEvent(0);
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isSetNotes() == true);
  notes = pObject->getNotesString();
  CPPUNIT_ASSERT(!notes.empty());
  CPPUNIT_ASSERT(notes.find("Simple note on event") != std::string::npos);
}

// SBML model with local render information
const char* test000098::SBML_MODEL_1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- Created by COPASI version 4.6.34 (Debug) on 2011-05-12 15:45 with libSBML version 4.2.0. -->\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">Simple note on model</body>\n"
  "    </notes>\n"
  "    <listOfFunctionDefinitions>\n"
  "      <functionDefinition id=\"function_1\" name=\"Constant flux (irreversible)\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> v </ci>\n"
  "            </bvar>\n"
  "            <ci> v </ci>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "    </listOfFunctionDefinitions>\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\" name=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\" name=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment metaid=\"COPASI2\" id=\"compartment_1\" name=\"compartment_1\" size=\"1\">\n"
  "        <notes>\n"
  "          <body xmlns=\"http://www.w3.org/1999/xhtml\">Simple note on compartment</body>\n"
  "        </notes>\n"
  "      </compartment>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species metaid=\"COPASI3\" id=\"species_1\" name=\"species_1\" compartment=\"compartment_1\" initialConcentration=\"1\">\n"
  "        <notes>\n"
  "          <body xmlns=\"http://www.w3.org/1999/xhtml\">Simple note on species</body>\n"
  "        </notes>\n"
  "      </species>\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter metaid=\"COPASI4\" id=\"parameter_1\" name=\"quantity_1\" value=\"0\" constant=\"false\">\n"
  "        <notes>\n"
  "          <body xmlns=\"http://www.w3.org/1999/xhtml\">Simple note on parameter</body>\n"
  "        </notes>\n"
  "      </parameter>\n"
  "    </listOfParameters>\n"
  "    <listOfReactions>\n"
  "      <reaction metaid=\"COPASI6\" id=\"reaction_1\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <notes>\n"
  "          <body xmlns=\"http://www.w3.org/1999/xhtml\">Simple note on reaction</body>\n"
  "        </notes>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfProducts>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>\n"
  "              <apply>\n"
  "                <ci> function_1 </ci>\n"
  "                <ci> v </ci>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </math>\n"
  "          <listOfParameters>\n"
  "            <parameter id=\"v\" name=\"v\" value=\"0.1\"/>\n"
  "          </listOfParameters>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "    <listOfEvents>\n"
  "      <event metaid=\"COPASI5\" id=\"event_1\" name=\"event_1\">\n"
  "        <notes>\n"
  "          <body xmlns=\"http://www.w3.org/1999/xhtml\">Simple note on event</body>\n"
  "        </notes>\n"
  "        <trigger>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <gt/>\n"
  "              <csymbol encoding=\"text\" definitionURL=\"http://www.sbml.org/sbml/symbols/time\"> time </csymbol>\n"
  "              <cn> 3 </cn>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </trigger>\n"
  "        <listOfEventAssignments>\n"
  "          <eventAssignment variable=\"parameter_1\">\n"
  "            <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "              <cn> 3 </cn>\n"
  "            </math>\n"
  "          </eventAssignment>\n"
  "        </listOfEventAssignments>\n"
  "      </event>\n"
  "    </listOfEvents>\n"
  "  </model>\n"
  "</sbml>\n"
  ;

// COPASI model with local render information
const char* test000098::CPS_MODEL_1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.6.34 (Debug) (http://www.copasi.org) at 2011-05-12 13:45:33 UTC -->\n"
  "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
  "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"34\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_6\" name=\"Constant flux (irreversible)\" type=\"PreDefined\" reversible=\"false\">\n"
  "      <Expression>\n"
  "        v\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_49\" name=\"v\" order=\"0\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\" avogadroConstant=\"6.02214179e+23\">\n"
  "    <Comment>\n"
  "      Simple note on model\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment_1\" simulationType=\"fixed\" dimensionality=\"3\">\n"
  "        <Comment>\n"
  "          Simple note on compartment\n"
  "        </Comment>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"species_1\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "        <Comment>\n"
  "          Simple note on species\n"
  "        </Comment>\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"quantity_1\" simulationType=\"fixed\">\n"
  "        <Comment>\n"
  "          Simple note on parameter\n"
  "        </Comment>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <Comment>\n"
  "          Simple note on reaction\n"
  "        </Comment>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_74\" name=\"v\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_6\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_49\">\n"
  "              <SourceParameter reference=\"Parameter_74\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <ListOfEvents>\n"
  "      <Event key=\"Event_0\" name=\"event_1\" order=\"1\">\n"
  "        <Comment>\n"
  "          Simple note on event\n"
  "        </Comment>\n"
  "        <TriggerExpression>\n"
  "          &lt;CN=Root,Model=New Model,Reference=Time&gt; gt 3.0\n"
  "        </TriggerExpression>\n"
  "        <ListOfAssignments>\n"
  "          <Assignment targetKey=\"ModelValue_0\">\n"
  "            <Expression>\n"
  "              3.0\n"
  "            </Expression>\n"
  "          </Assignment>\n"
  "        </ListOfAssignments>\n"
  "      </Event>\n"
  "    </ListOfEvents>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.022141790000001e+20 0 1 \n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
