// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLFileDialog.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/30 13:50:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CQSBMLFileDialog.h"

#include "CopasiFileDialog.h"

// static
std::pair< QString, std::pair< unsigned C_INT32, unsigned C_INT32 > > CQSBMLFileDialog::getSaveFileName(QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & caption)
{
  std::pair< QString, std::pair< unsigned C_INT32, unsigned C_INT32 > > NameAndVersion;

  QString Filter = "Level 1 Version 2 (*.xml);;"
                   "Level 2 Version 1 (*.xml);;"
                   "Level 2 Version 2 (*.xml);;"
                   "Level 2 Version 3 (*.xml)";

  QString SelectedFilter = "Level 2 Version 3 (*.xml)";

  NameAndVersion.first =
    CopasiFileDialog::getSaveFileName(parent, name, startWith, Filter, caption, &SelectedFilter);

  if (SelectedFilter == "Level 1 Version 2 (*.xml)")
    {
      NameAndVersion.second.first = 1;
      NameAndVersion.second.second = 2;
    }
  else if (SelectedFilter == "Level 2 Version 1 (*.xml)")
    {
      NameAndVersion.second.first = 2;
      NameAndVersion.second.second = 1;
    }
  else if (SelectedFilter == "Level 2 Version 2 (*.xml)")
    {
      NameAndVersion.second.first = 2;
      NameAndVersion.second.second = 2;
    }
  else if (SelectedFilter == "Level 2 Version 3 (*.xml)")
    {
      NameAndVersion.second.first = 2;
      NameAndVersion.second.second = 3;
    }

  return NameAndVersion;
}
