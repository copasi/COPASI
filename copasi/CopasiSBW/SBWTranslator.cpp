// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Main
//
// (C) Stefan Hoops 2002
//

#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

#include <SBWTranslator.h>

#include <SBW/SBW.h>

#define COPASI_MAIN

#include <copasi/CopasiTypes.h>
#include <copasi/commandline/COptions.h>
#include <copasi/utilities/CVersion.h>
#include <copasi/utilities/CDirEntry.h>

using namespace SystemsBiologyWorkbench;
using namespace std;

int Copasi2SBMLTranslator::mLevel = 3;
int Copasi2SBMLTranslator::mVersion = 1;

Copasi2SBMLTranslator::Copasi2SBMLTranslator()
{
}
Copasi2SBMLTranslator::~Copasi2SBMLTranslator()
{
}

void Copasi2SBMLTranslator::registerMethods(MethodTable<Copasi2SBMLTranslator> &table)
{
  table.addMethod(&Copasi2SBMLTranslator::getName,            "string getName()", false, "Return the name of this importer");
  table.addMethod(&Copasi2SBMLTranslator::getVersion,         "string getVersion()", false, "Return the version of this importer");
  table.addMethod(&Copasi2SBMLTranslator::getAuthor,          "string getAuthor()", false, "Return the corresponding author for this importer");
  table.addMethod(&Copasi2SBMLTranslator::getDescription,       "string getDescription()", false, "Return a description for this importer");
  table.addMethod(&Copasi2SBMLTranslator::getName,        "string getDisplayName()", false, "Return the display name for this importer.");
  table.addMethod(&Copasi2SBMLTranslator::getCopyright,       "string getCopyright()", false, "Return the copyright for this importer");
  table.addMethod(&Copasi2SBMLTranslator::getURL,           "string getURL()", false, "Return a URL for this reporter.");
  table.addMethod(&Copasi2SBMLTranslator::getFileExtension,            "string getFileExtension()", false, "Returns the file extension as a string");
  table.addMethod(&Copasi2SBMLTranslator::getFileType,                 "string getFileType()", false, "Returns a string describing the type of file");
  table.addMethod(&Copasi2SBMLTranslator::translate,          "string translate(string)", false, "Translate SBML string to COPASI.");
  table.addMethod(&Copasi2SBMLTranslator::translateToSBML,          "string translateToSBML(string)", false, "Translate COPASI string to SBML.");
  table.addMethod(&Copasi2SBMLTranslator::translateFileToSBML,          "string translateFileToSBML(string)", false, "Translate COPASI string to SBML.");
}

std::string Copasi2SBMLTranslator::translateFileToSBML(const std::string &fileName)
{
  CRootContainer::init(0, NULL);
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  pDataModel->loadModel(fileName, NULL);
  string sbml = pDataModel->exportSBMLToString(NULL, mLevel, mVersion);
  return sbml;
}

std::string Copasi2SBMLTranslator::translate(const std::string &sbmlString)
{
  CRootContainer::init(0, NULL);
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  pDataModel->importSBMLFromString(sbmlString);

  string tempDir;
  COptions::getValue("Tmp", tempDir);
  string tempFile = "tmp.cps";
  CDirEntry::makePathAbsolute(tempFile, tempDir);
  tempFile = CDirEntry::fileName(tempFile);
  pDataModel->saveModel(tempFile, NULL, true);
  std::ifstream ifs(tempFile.c_str());
  std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  ifs.close();
  CDirEntry::remove(tempFile);
  return str;
}

std::string Copasi2SBMLTranslator::translateToSBML(const std::string &copasiString)
{
  CRootContainer::init(0, NULL);
  CDataModel* pDataModel = CRootContainer::addDatamodel();

  istringstream str(copasiString);

  pDataModel->loadModel(str, COptions::getPWD(), NULL);
  string sbml = pDataModel->exportSBMLToString(NULL, mLevel, mVersion);
  return sbml;
}

DataBlockWriter Copasi2SBMLTranslator::getName(Module from, DataBlockReader reader)
{
  static string name("Copasi2SBML Translator");
  return DataBlockWriter();
}

DataBlockWriter Copasi2SBMLTranslator::getVersion(Module from, DataBlockReader reader)
{
  static string version(CVersion::VERSION.getVersion());
  return DataBlockWriter() << version;
}

DataBlockWriter Copasi2SBMLTranslator::getAuthor(Module from, DataBlockReader reader)
{
  static string author("Frank T. Bergmann");
  return DataBlockWriter() << author;
}
DataBlockWriter Copasi2SBMLTranslator::getDescription(Module from, DataBlockReader reader)
{
  static string description("This converter converts a COPASI model to an SBML file");
  return DataBlockWriter();
}
DataBlockWriter Copasi2SBMLTranslator::getCopyright(Module from, DataBlockReader reader)
{
  static string copy("(c) 2012 COPASI Team");
  return DataBlockWriter() << copy;
}
DataBlockWriter Copasi2SBMLTranslator::getURL(Module from, DataBlockReader reader)
{
  static string url("http://copasi.org");
  return DataBlockWriter() << url;
}
DataBlockWriter Copasi2SBMLTranslator::getFileExtension(Module from, DataBlockReader reader)
{
  static string extension(".cps");
  return DataBlockWriter() << extension;
}
DataBlockWriter Copasi2SBMLTranslator::getFileType(Module from, DataBlockReader reader)
{
  static string fileType("COPASI file");
  return DataBlockWriter() << fileType;
}
DataBlockWriter Copasi2SBMLTranslator::translateFileToSBML(Module from, DataBlockReader reader)
{
  std::string fileName; reader >> fileName;
  return DataBlockWriter() << translateFileToSBML(fileName);
}
DataBlockWriter Copasi2SBMLTranslator::translate(Module from, DataBlockReader reader)
{
  std::string model; reader >> model;
  return DataBlockWriter() << translate(model);
}
DataBlockWriter Copasi2SBMLTranslator::translateToSBML(Module from, DataBlockReader reader)
{
  std::string model; reader >> model;
  return DataBlockWriter() << translateToSBML(model);
}

int main(int argc, char *argv[])
{

  try
    {
      setlocale(LC_ALL, "C");
      bool doTranslate = false;
      string fileName;

      for (int i = 0; i < argc; i++)
        {
          string current(argv[i]);

          if (current == "-f" && i + 1 < argc)
            {
              doTranslate = true;
              fileName = argv[i + 1];
              i++;
            }
        }

      if (doTranslate)
        {
          cout << Copasi2SBMLTranslator::translateFileToSBML(fileName) << endl;
          exit(0);
        }

      ModuleImpl modImpl(
        "org.copasi.copasi2sbml", // module identification
        "Copasi to SBML Translator", // humanly readable name
        UniqueModule); // management scheme

      modImpl.addServiceObject(
        "translator", // service identification
        "Copasi2SBML Translator", // humanly readable name
        "plugin/sbmlTranslator/bidirectional", // category
        new Copasi2SBMLTranslator()); // service implementation

      modImpl.run(argc, argv);
    }
  catch (SBWException *e)
    {
      fprintf(stderr, "Copasi2SBMLTranslator exception: %s\n", e->getMessage().c_str());
      return -1;
    }

  return 0;
}
