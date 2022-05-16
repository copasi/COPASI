// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQSEDMLFileDialog.cpp
 *
 *  Created on: 31 Jul 2013
 *      Author: dada
 */

#include <QRegExp>

#include "copasi/copasi.h"

#include "CQSEDMLFileDialog.h"
#include "CopasiFileDialog.h"

// static
std::pair< QString, std::pair< unsigned C_INT32, unsigned C_INT32 > > CQSEDMLFileDialog::getSaveFileName(QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & caption,
    unsigned int sedmlLevel,
    unsigned int sedmlVersion)
{
  std::pair< QString, std::pair< unsigned C_INT32, unsigned C_INT32 > > NameAndVersion;

  QString Filter = "Level 1 Version 4 (*.sedml);;"
                   "Level 1 Version 3 (*.sedml);;"
                   "Level 1 Version 2 (*.sedml);;"
                   "Level 1 Version 1 (*.sedml)";

  QString SelectedFilter =
    QString("Level %1 Version %2 (*.sedml)").arg(QString::number(sedmlLevel)).arg(QString::number(sedmlVersion));;

  // The default export is L1V4
  if (Filter.indexOf(SelectedFilter) == -1)
    {
      SelectedFilter = "Level 1 Version 4 (*.sedml)";
    }

  // We need to avoid the KDE dialog at least under Qt 4.7 and KDE 4.5
  // See: Bug 1651
  QFileDialog::Options DontUseNativeDialog = QFileDialog::Options();

#ifdef Linux
  DontUseNativeDialog = QFileDialog::DontUseNativeDialog;
#endif // Linux

  NameAndVersion.first =
    CopasiFileDialog::getSaveFileName(parent, name, startWith, Filter, caption, &SelectedFilter, DontUseNativeDialog);

  QRegExp Pattern("Level (\\d) Version (\\d) \\(\\*\\.sedml\\)");

  if (Pattern.exactMatch(SelectedFilter))
    {
      NameAndVersion.second.first = Pattern.cap(1).toInt();
      NameAndVersion.second.second = Pattern.cap(2).toInt();
    }
  else
    {
      NameAndVersion.second.first = 1;
      NameAndVersion.second.second = 4;
    }

  return NameAndVersion;
}
