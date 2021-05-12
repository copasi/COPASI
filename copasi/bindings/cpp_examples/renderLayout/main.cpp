// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This examples demonstrates how to rad in a copasi file, change its parameters and run a parameter scan
 * while changing the report filename
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <QFileInfo>

#define COPASI_MAIN

#include "copasi/CopasiTypes.h"
#include "copasi/UI/CopasiGuiTypes.h"
#include <copasi/layout/CListOfLayouts.h>
#include <copasi/qlayout/CQLayoutScene.h>

using namespace std;

void renderCurrentLayout(CLayout* pLayout, CDataModel* pDataModel, const std::string& outputFilename, const std::string& format = "pdf")
{
  CQLayoutScene scene(pLayout, pDataModel);
  scene.recreate();
  auto bounds = pLayout->calculateBoundingBox();
  auto dims = bounds.getDimensions();
  scene.setSceneRect(0, 0, dims.getWidth(), dims.getHeight());
  scene.saveToFile(outputFilename, format);
}

int main(int argc, char** argv)
{
  // initialize the backend library
  CRootContainer::init(0, NULL);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of an SBML file and an output file
  if (argc < 3)
    {
      std::cerr << "Usage: renderLayout <copasi file | sbml file> <output file>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string outputFilename = argv[2];
  QFileInfo outputInfo(FROM_UTF8(outputFilename));
  std::string path = TO_UTF8(outputInfo.absolutePath());
  std::string baseName = TO_UTF8(outputInfo.completeBaseName());
  std::string format = TO_UTF8(outputInfo.suffix());

  try
    {

      if (filename.find(".cps") != std::string::npos || filename.find(".gps") != std::string::npos)
        {
          if (!pDataModel->loadFromFile(filename))
            throw "model couldn't be loaded";
        }
      else
        {
          if (!pDataModel->importSBML(filename, NULL))
            throw "model couldn't be imported";
        }

      auto layouts = pDataModel->getListOfLayouts();
      auto numLayouts = layouts->size();

      if (layouts->empty())
        {
          std::cout << "no layouts in file." << std::endl;
          return 1;
        }

      QApplication app(argc, argv);

      auto it = layouts->begin();

      for (; it != layouts->end(); ++it)
        {
          auto& current = *it;
          std::cout << "Exporting: " << current.getObjectName() << std::endl;
          std::string currentName =  numLayouts == 1 ? outputFilename :
                                     path + std::string("/") + baseName + std::string("_") + current.getObjectName() + std::string(".") + format;
          renderCurrentLayout(&current, pDataModel, currentName, format);
        }
    }
  catch (...)
    {
      std::cout << "Exception occurred: " << std::endl
                << CCopasiMessage::getAllMessageText() << std::endl;
    }

  // clean up the library
  CRootContainer::destroy();
}
