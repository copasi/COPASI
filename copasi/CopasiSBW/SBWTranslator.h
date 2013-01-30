// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_SBW_TRANSLATOR_H
#define COPASI_SBW_TRANSLATOR_H

#include <string>

#include <SBW/MethodTable.h>
#include <SBW/DataBlockWriter.h>
#include <SBW/DataBlockReader.h>
#include <SBW/Module.h>

class Copasi2SBMLTranslator
{
public:
  Copasi2SBMLTranslator();
  virtual ~Copasi2SBMLTranslator();

  static void registerMethods(SystemsBiologyWorkbench::MethodTable<Copasi2SBMLTranslator> &table);

  static std::string translateToSBML(const std::string &copasiString);
  static std::string translate(const std::string &sbmlString);
  static std::string translateFileToSBML(const std::string &fileName);

protected:

  SystemsBiologyWorkbench::DataBlockWriter getName(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter getVersion(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter getAuthor(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter getDescription(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter getCopyright(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter getURL(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter getFileExtension(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter getFileType(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter translate(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter translateToSBML(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);
  SystemsBiologyWorkbench::DataBlockWriter translateFileToSBML(SystemsBiologyWorkbench::Module from, SystemsBiologyWorkbench::DataBlockReader reader);

private:

  static int mLevel;
  static int mVersion;
};

#endif //COPASI_SBW_TRANSLATOR_H
