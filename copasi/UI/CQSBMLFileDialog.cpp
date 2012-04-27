// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLFileDialog.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/27 16:33:29 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtCore/QRegExp>

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
                   "Level 2 Version 4 (*.xml);;"
                   "Level 3 Version 1 (*.xml)";

  QString SelectedFilter =
    QString("Level %1 Version %2 (*.xml)").arg(QString::number(sbmlLevel)).arg(QString::number(sbmlVersion));;

  // The default export is L2V4
  if (Filter.indexOf(SelectedFilter) == -1)
    {
      SelectedFilter = "Level 2 Version 4 (*.xml)";
    }

  // We need to avoid the KDE dialog at least under Qt 4.7 and KDE 4.5
  // See: Bug 1651
  QFileDialog::Options DontUseNativeDialog = 0;

#ifdef Linux
  DontUseNativeDialog = QFileDialog::DontUseNativeDialog;
#endif // Linux

  NameAndVersion.first =
    CopasiFileDialog::getSaveFileName(parent, name, startWith, Filter, caption, &SelectedFilter, DontUseNativeDialog);

  QRegExp Pattern("Level (\\d) Version (\\d) \\(\\*\\.xml\\)");

  if (Pattern.exactMatch(SelectedFilter))
    {
      NameAndVersion.second.first = Pattern.cap(1).toInt();
      NameAndVersion.second.second = Pattern.cap(2).toInt();
    }
  else
    {
      NameAndVersion.second.first = 2;
      NameAndVersion.second.second = 4;
    }

  return NameAndVersion;
}
