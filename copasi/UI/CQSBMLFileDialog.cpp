// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLFileDialog.cpp,v $
//   $Revision: 1.10.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/19 22:28:07 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
    const QString & caption,
    unsigned int sbmlLevel,
    unsigned int sbmlVersion)
{
  std::pair< QString, std::pair< unsigned C_INT32, unsigned C_INT32 > > NameAndVersion;

  QString Filter = "Level 1 Version 2 (*.xml);;"
                   "Level 2 Version 1 (*.xml);;"
                   "Level 2 Version 2 (*.xml);;"
                   "Level 2 Version 3 (*.xml);;"
                   "Level 2 Version 4 (*.xml)";

  QString SelectedFilter = "Level 2 Version 4 (*.xml)";

  switch (sbmlLevel)
    {
      case 1:

        switch (sbmlVersion)
          {
            case 2:
              SelectedFilter = "Level 1 Version 2 (*.xml)";
              break;
            default:
              break;
          }

        break;
      case 2:

        switch (sbmlVersion)
          {
            case 1:
              SelectedFilter = "Level 2 Version 1 (*.xml)";
              break;
            case 2:
              SelectedFilter = "Level 2 Version 2 (*.xml)";
              break;
            case 3:
              SelectedFilter = "Level 2 Version 3 (*.xml)";
              break;
            case 4:
              SelectedFilter = "Level 2 Version 4 (*.xml)";
              break;
            default:
              break;
          }

        break;
    }

  QFileDialog::Options NativeDialog;

  // We need to avoid the KDE dialog.
#ifdef Linux
  NativeDialog = QFileDialog::DontUseNativeDialog;
#endif // Linux

  NameAndVersion.first =
    CopasiFileDialog::getSaveFileName(parent, name, startWith, Filter, caption, &SelectedFilter, NativeDialog);

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
  else if (SelectedFilter == "Level 2 Version 4 (*.xml)")
    {
      NameAndVersion.second.first = 2;
      NameAndVersion.second.second = 4;
    }

  return NameAndVersion;
}
