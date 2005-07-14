/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/MMASCIIExporter.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: nsimus $ 
   $Date: 2005/07/14 10:52:03 $
   End CVS Header */

#include <math.h>
#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "MMASCIIExporter.h"

#include "model/CModel.h"
#include "model/CMetab.h"
#include "utilities/CCopasiVector.h"
#include "model/CReaction.h"

#include <iostream>
#include <fstream>

/**
 ** Constructor for the exporter.
 */
MMASCIIExporter::MMASCIIExporter()
{}

/**
 ** Destructor for the exporter.
 */
MMASCIIExporter::~MMASCIIExporter()
{}

/**
 ** This method takes some of the copasi objects : such as CMetab,...
 ** and writes them to an ASCII output file. The filename is given as the second
 ** argument to the function. The function return "true" on success and
 ** "false" on failure.
 */

bool MMASCIIExporter::exportMathModel(const CModel* copasiModel, std::string mmasciiFilename, bool overwriteFile)
{
  /* check if the file already exisits.
          If yes, write if overwrite is true, 
          else create an appropriate  CCopasiMessage. */

  std::ifstream testInfile(mmasciiFilename.c_str(), std::ios::in);

  if (testInfile && !overwriteFile)
    {
      // create a CCopasiMessage with the appropriate error
      CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, mmasciiFilename.c_str());
      return false;
    }

  std::ofstream outFile(mmasciiFilename.c_str(), std::ios::out);

  outFile << "//Metabolites:" << std::endl;

  unsigned int i, imax;
  CMetab* metab;

  imax = copasiModel->getMetabolites().size();
  for (i = 0; i < imax; i++)
    {
      metab = copasiModel->getMetabolites()[i];

      outFile << "x[" << i << "]="
      << metab->getInitialConcentration() << ";"
      << '\t' << "//" << metab->getObjectName().c_str() << ","
      << '\t' << CModelEntity::StatusName[metab->getStatus()]
      << std::endl;
    }

  outFile << "//Moiety:" << std::endl;

  outFile << "//Kinetic Parameters:" << std::endl;

  unsigned j, jmax;
  const CCopasiVector< CReaction > & reacs = copasiModel->getReactions();
  CReaction* reac;

  imax = reacs.size();

  for (i = 0; i < imax; ++i)
    {
      reac = reacs[i];

      outFile << "// in reaction:" << reac->getObjectName().c_str() << std::endl;

      jmax = reac->getParameters().size();

      for (j = 0; j < jmax; ++j)
        {
          outFile << "k[" << j << "]="
          << *reac->getParameters().getParameter(j)->getValue().pDOUBLE << ";"
          << '\t' << "//" << reac->getParameters().getParameter(j)->getObjectName().c_str()
          << std::endl;
        }
    }

  return true;
}
