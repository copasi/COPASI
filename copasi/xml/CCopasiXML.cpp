/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#include "copasi.h"
#include "CCopasiXML.h"

CCopasiXML::CCopasiXML():
    CCopasiXMLInterface()
{}

CCopasiXML::~CCopasiXML() {}

bool CCopasiXML::save(std::ostream & os)
{
  mpOstream = &os;
  bool success = true;

  if (!saveFunctionList()) success = false;
  if (!saveModel()) success = false;
  if (!saveTaskList()) success = false;
  if (!saveReportList()) success = false;

  return success;
}

bool CCopasiXML::load(std::istream & is)
{
  mpIstream = &is;

  return true;
}

bool CCopasiXML::saveModel()
{
  bool success = true;

  return success;
}

bool CCopasiXML::saveFunctionList()
{
  bool success = true;

  return success;
}

bool CCopasiXML::saveTaskList()
{
  bool success = true;

  return success;
}

bool CCopasiXML::saveReportList()
{
  bool success = true;

  return success;
}
