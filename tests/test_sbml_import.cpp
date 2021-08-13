// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>
#include <sbml/SBMLTypes.h>


TEST_CASE("1: importing sbml files", "[copasi,sbml]")
{

  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  SECTION("unit import")
  {
    std::string test_file = getTestFile("test-data/unit_test.xml");
    auto* sbml_doc = readSBMLFromFile(test_file.c_str());
    REQUIRE(sbml_doc != NULL);
    auto* sbml_mod = sbml_doc->getModel();
    REQUIRE(sbml_mod != NULL);

    auto * unit = sbml_mod->getUnitDefinition("unit_1");
    REQUIRE(unit != NULL);

    SBMLImporter importer;

    std::string expression = importer.createUnitExpressionFor(unit);

    REQUIRE(expression == "l/(nmol*s)");

    unit = sbml_mod->getUnitDefinition("unit_2");
    REQUIRE(unit != NULL);
    expression = importer.createUnitExpressionFor(unit);
    REQUIRE(expression == "d");

    unit = sbml_mod->getUnitDefinition("unit_3");
    REQUIRE(unit != NULL);
    expression = importer.createUnitExpressionFor(unit);
    REQUIRE((expression == "1/(#*d)" || expression == "1/(d*#)"));


    delete sbml_doc;

  }


  SECTION("volume units")
  {
    std::string test_file = getTestFile("test-data/volume_units.xml");
    auto * sbml_doc = readSBMLFromFile(test_file.c_str());
    REQUIRE(sbml_doc != NULL);
    auto * sbml_mod = sbml_doc->getModel();
    REQUIRE(sbml_mod != NULL);

    auto * unit = sbml_mod->getUnitDefinition("um3");
    REQUIRE(unit != NULL);

    SBMLImporter importer;

    std::string expression = importer.createUnitExpressionFor(unit);
    delete sbml_doc;

    REQUIRE(!expression.empty());

    auto* dm = CRootContainer::addDatamodel();
    REQUIRE(dm->importSBML(test_file) == true);
    const auto* model = dm->getModel();
    std::string model_units = model->getVolumeUnit();
    REQUIRE(model_units == expression);

    // now export
    auto sbml_text = dm->exportSBMLToString(NULL, 3, 1);

    sbml_doc = readSBMLFromString(sbml_text.c_str());
    sbml_mod = sbml_doc->getModel();
    unit = sbml_mod->getUnitDefinition("volume");
    REQUIRE(unit != NULL);

    expression = importer.createUnitExpressionFor(unit);
    REQUIRE(model_units == expression);
    delete sbml_doc;
  }

  SECTION("unit export")
  {
    REQUIRE(dm->newModel(NULL, true) == true);

    auto * mod = dm->getModel();
    REQUIRE(mod != NULL);
    auto * p = mod->createModelValue("p1");
    REQUIRE(p != NULL);
    p->setValue(1);
    p->setUnitExpression("d");

    p = mod->createModelValue("p2");
    REQUIRE(p != NULL);
    p->setValue(1);
    p->setUnitExpression("1/(#*d)");

    CSBMLExporter exp;
    auto sbml = exp.exportModelToString(*dm, 2, 4);

    auto * doc = readSBMLFromString(sbml.c_str());
    REQUIRE(doc != NULL);
    auto * sbml_mod = doc->getModel();
    REQUIRE(sbml_mod != NULL);

    auto * unitdef = sbml_mod->getUnitDefinition("unit_0");
    REQUIRE(unitdef != NULL);
    REQUIRE(unitdef->getNumUnits() == 1);
    auto * unit = unitdef->getUnit(0);
    REQUIRE(unit != NULL);
    REQUIRE(unit->getScale() == 0);
    REQUIRE(unit->getMultiplier() == 86400);
    REQUIRE(unit->getExponent() == 1);
    REQUIRE(unit->getKind() == UNIT_KIND_SECOND);

    unitdef = sbml_mod->getUnitDefinition("unit_1");
    REQUIRE(unitdef != NULL);
    REQUIRE(unitdef->getNumUnits() == 2);
    unit = unitdef->getUnit(0);
    REQUIRE(unit != NULL);
    REQUIRE(unit->getScale() == 0);
    REQUIRE(unit->getMultiplier() == 86400);
    REQUIRE(unit->getExponent() == -1);
    REQUIRE(unit->getKind() == UNIT_KIND_SECOND);

    unit = unitdef->getUnit(1);
    REQUIRE(unit != NULL);
    REQUIRE(unit->getScale() == 0);
    REQUIRE(unit->getMultiplier() == 1);
    REQUIRE(unit->getExponent() == -1);
    REQUIRE(unit->getKind() == UNIT_KIND_ITEM);

  }

  CRootContainer::removeDatamodel(dm);
}



#include <copasi/report/CDataHandler.h>

TEST_CASE("3: creating a new model testing avogadro", "[copasi,sbml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  dm->newModel(NULL, true);

  auto * model = dm->getModel();
  double avo_num = 6e23;
  model->setAvogadro(avo_num, CCore::Framework::Concentration);
  auto * mv = model->createModelValue("avo");

  std::stringstream str;

  str << "<"
      << CObjectInterface::DataObject(model->getObject(CCommonName("Reference=Avogadro Constant")))->getValueObject()->getCN()
      << ">";

  mv->setInitialExpression(str.str());

  mv->setStatus(CModelEntity::Status::ASSIGNMENT);
  mv->setExpression(str.str());

  model->compileIfNecessary(NULL);

  // simulate
  auto & task = (*dm->getTaskList())["Time-Course"];
  CTrajectoryProblem * pProblem = static_cast< CTrajectoryProblem * >(task.getProblem());
  pProblem->setStepNumber(2);

  {
    auto dh = CDataHandler();
    dh.addDuringName(model->getModelValues()[0].getValueReference()->getCN());
    task.initialize(CCopasiTask::OUTPUT_UI, &dh, NULL);
    task.process(true);
    task.restore();

    REQUIRE(dh.getDuringData()[0][0] == avo_num);
  }


  {
    avo_num = 7e23;
    model->setAvogadro(avo_num, CCore::Framework::Concentration);
    auto dh = CDataHandler();
    dh.addDuringName(model->getModelValues()[0].getValueReference()->getCN());
    task.initialize(CCopasiTask::OUTPUT_UI, &dh, NULL);
    task.process(true);
    task.restore();

    REQUIRE(dh.getDuringData()[0][0] == avo_num);
  }


  CRootContainer::removeDatamodel(dm);
}



TEST_CASE("2: importing an sbml file and saving as COPASI file", "[copasi,sbml]")
{

  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  std::string test_file = getTestFile("test-data/01776-sbml-l3v1.xml");

  REQUIRE(dm->importSBML(test_file) == true);

  // create model values for amounts:
  auto * model = dm->getModel();

for (auto & metab : model->getMetabolites())
    {
      std::stringstream str;
      str << metab.getObjectName() << "_amount";
      auto * mv = model->createModelValue(str.str());
      REQUIRE(mv != NULL);
      str.str("");
      str
          << "<"
          << metab.getConcentrationReference()->getCN()
          << "> * <"
          << metab.getCompartment()->getValueReference()->getCN()
          << ">";
      mv->setStatus(CModelEntity::Status::ASSIGNMENT);
      REQUIRE(mv->setExpression(str.str()).isSuccess());
      REQUIRE(mv->compile().isSuccess());
    }

  // simulate
  auto &task = (*dm->getTaskList())["Time-Course"];

  auto dh = CDataHandler();
  dh.addDuringName(model->getModelValues()[0].getValueReference()->getCN());

  task.initialize(CCopasiTask::OUTPUT_UI, &dh, NULL);
  task.process(true);
  task.restore();

  double val = dh.getDuringData()[0][0];

  std::string copasi_model = dm->saveModelToString();

  std::string sbml_model = dm->exportSBMLToString(NULL, 3, 1);

  CRootContainer::removeDatamodel(dm);
}


TEST_CASE("importing an SBML file multiple times", "[copasi,sbml]")
{

  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  std::string test_file = getTestFile("test-data/BIOMD0000000027_url.xml");

  REQUIRE(dm->importSBML(test_file) == true);
  REQUIRE(dm->importSBML(test_file) == true);
  REQUIRE(dm->importSBML(test_file) == true);


  std::string copasi_model = dm->saveModelToString();

  std::string sbml_model = dm->exportSBMLToString(NULL, 3, 1);

  CRootContainer::removeDatamodel(dm);
}


TEST_CASE("importing an SBML file and delete used function definition", "[copasi,sbml]")
{

  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  std::string test_file = getTestFile("test-data/BIOMD0000000055_urn.xml");

  REQUIRE(dm->importSBML(test_file) == true);

  auto * pFunDB = CRootContainer::getFunctionList();

  for (int i = ((int)pFunDB->loadedFunctions().size()) - 1; i >= 0; --i)
    {
      auto & pFun = pFunDB->loadedFunctions()[i];

      if (!pFun.isReadOnly())
        {
          pFunDB->removeFunction(i);
        }
    }

  std::string copasi_model = dm->saveModelToString();

  std::string sbml_model = dm->exportSBMLToString(NULL, 3, 1);

  CRootContainer::removeDatamodel(dm);
}



//#include <filesystem>
//#include <copasi/utilities/CCopasiException.h>
//
//namespace fs = std::filesystem;
//
//#include <copasi/math/CJitCompiler.h>
//
//TEST_CASE("2: importing biomodel files", "[copasi,sbml]")
//{
//  auto * dm = CRootContainer::addDatamodel();
//  REQUIRE(dm != NULL);
//
//  CJitCompiler::SetJitBufferSize(128000);
//
//  bool skip = true;
//
//  for (auto itEntry = fs::recursive_directory_iterator("/Development/temp-biomodels/original/");
//       itEntry != fs::recursive_directory_iterator();
//       ++itEntry)
//    {
//      const auto currentPath = itEntry->path();
//      const auto filenameStr = currentPath.filename().string();
//      if (filenameStr.find(".xml") == std::string::npos)
//        continue;
//
//      if (filenameStr.find("SED") != std::string::npos)
//        continue;
//
//      //if (skip && filenameStr.find("385") == std::string::npos)
//      //  continue;
//
//      skip = false;
//
//
//      try
//        {
//          bool result = dm->importSBML(currentPath.string(), NULL);
//          std::cout << std::setw(itEntry.depth() * 3) << "";
//          std::cout << "sbml:  " << filenameStr << ": " << result << '\n';
//        }
//      catch (CCopasiException & ex)
//        {
//          std::cerr << "exception: " << ex.getMessage().getText() << '\n';
//        }
//      catch (...)
//        {
//          std::cerr << "unknown exception!\n";
//        }
//
//      // remove unused functions
//      dm->newModel(NULL, true);
//
//      auto & functions = CRootContainer::getFunctionList()->loadedFunctions();
//      for (int Index = functions.size() - 1; Index >= 0 ; --Index)
//      {
//          if (!functions[Index].isReadOnly())
//          CRootContainer::getFunctionList()->removeFunction(functions[Index].getKey());
//      }
//
//    }
//
//}
