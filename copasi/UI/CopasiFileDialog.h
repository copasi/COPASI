// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/16 19:55:37 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <qfiledialog.h>
#include <qdir.h>
#include <qpushbutton.h>

#include "UI/CQFileDialogBtnGrp.h"

class CopasiFileDialog : public QFileDialog
  {
    Q_OBJECT
  private:
    CQFileDialogBtnGrp * mpGrp;
    static QDir mLastDir;

  public:
    CopasiFileDialog(QWidget * parent , const char * name , bool modal);

    ~CopasiFileDialog();

    QString getOpenFileName(const QString & startWith = QString::null,
                            const QString & filter = QString::null,
                            const QString & caption = QString::null,
                            QString selectedFilter = QString::null);

    QString getSaveFileName(const QString & startWith = QString::null,
                            const QString & filter = QString::null,
                            const QString & caption = QString::null,
                            QString selectedFilter = QString::null);

    static QString getOpenFileName(QWidget * parent = 0,
                                   const char * name = 0,
                                   const QString & startWith = QString::null,
                                   const QString & filter = QString::null,
                                   const QString & caption = QString::null,
                                   QString selectedFilter = QString::null);

    static QString getSaveFileName(QWidget * parent = 0,
                                   const char * name = 0,
                                   const QString & startWith = QString::null,
                                   const QString & filter = QString::null,
                                   const QString & caption = QString::null,
                                   QString selectedFilter = QString::null);

    static QString getSaveFileNameAndFilter(QString & newFilter,
                                            QWidget * parent = 0,
                                            const char * name = 0,
                                            const QString & startWith = QString::null,
                                            const QString & filter = QString::null,
                                            const QString & caption = QString::null,
                                            QString selectedFilter = QString::null);

  public slots:
    virtual void slotExampleDir();
    virtual void slotHomeDir();
  };

#endif
