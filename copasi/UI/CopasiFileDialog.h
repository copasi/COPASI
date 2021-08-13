// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <QFileDialog>
#include <QtCore/QString>
#include <QtCore/QDir>

class CopasiFileDialog
{
public:
  static void openExampleDir(QWidget * parent = 0);

  static QString getOpenFileName(QWidget * parent = 0,
                                 const char * name = 0,
                                 const QString & startWith = QString(),
                                 const QString & filter = QString(),
                                 const QString & caption = QString(),
                                 QString * pSelectedFilter = NULL,
                                 QFileDialog::Options options = QFileDialog::Options());

  static QString getSaveFileName(QWidget * parent = 0,
                                 const char * name = 0,
                                 const QString & startWith = QString(),
                                 const QString & filter = QString(),
                                 const QString & caption = QString(),
                                 QString * pSelectedFilter = NULL,
                                 QFileDialog::Options options = QFileDialog::Options());

  static QString getDefaultFileName(const QString & suffix);

private:
  static QString StartWith(const QString & startWith);
};

#endif
