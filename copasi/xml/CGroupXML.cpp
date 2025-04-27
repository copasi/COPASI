// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/xml/CGroupXML.h"
#include "copasi/xml/parser/CXMLParser.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/utility.h"

/*
  mConfiguration.assertGroup("Recent Files");
  mConfiguration.assertGroup("Recent SBML Files");
  mConfiguration.assertGroup("MIRIAM Resources");
  mConfiguration.assertGroup("Recent SEDML Files");
 */

CGroupXML::CGroupXML(CCopasiParameterGroup & group)
  : CCopasiXMLInterface()
  , mGroup(group)
{}

CGroupXML::~CGroupXML()
{}

bool CGroupXML::save(std::ostream & os,
                                    const std::string & relativeTo)
{
  mPWD = relativeTo;

  os.imbue(std::locale::classic());
  os.precision(std::numeric_limits<double>::digits10 + 2);

  mpOstream = &os;

  *mpOstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
             << "\n";

  *mpOstream << "<!-- generated with COPASI "
             << CVersion::VERSION.getVersion()
             << " (http://www.copasi.org) at "
             << UTCTimeStamp()
             << " -->"
             << "\n";

  saveParameter(mGroup);

  return true;
}

bool CGroupXML::load(std::istream & is,
                     const std::string & relativeTo)
{
  mPWD = relativeTo;

  is.imbue(std::locale::classic());
  is.precision(std::numeric_limits<double>::digits10 + 2);

  mpIstream = &is;
  bool success = true;
  bool done = false;

  CVersion Version;
  CXMLParser Parser(Version);

#define BUFFER_SIZE 0xfffe
  char * pBuffer = new char[BUFFER_SIZE + 1];

  while (!done)
    {
      mpIstream->get(pBuffer, BUFFER_SIZE, 0);

      if (mpIstream->eof()) done = true;

      if (mpIstream->fail() && !done)
        {
          CCopasiMessage Message(CCopasiMessage::WARNING, MCConfiguration + 2, mFileName.c_str());

          done = true;
          success = false;
        }

      if (!Parser.parse(pBuffer, -1, done))
        {
          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 2,
                                 Parser.getCurrentLineNumber(),
                                 Parser.getCurrentColumnNumber(),
                                 Parser.getErrorString());
          done = true;
          success = false;
        }
    }

  delete [] pBuffer;
#undef BUFFER_SIZE

  if (success
      && Parser.getCurrentGroup() != NULL
      && mGroup.getObjectName() == Parser.getCurrentGroup()->getObjectName())
    {
      mGroup = *Parser.getCurrentGroup();
      delete Parser.getCurrentGroup();
    }
  else
    mGroup.clear();

  return success;
}
