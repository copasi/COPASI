/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiFileDialog.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qdir.h>
#include <qpushbutton.h>

#include "CQFileDialogBtnGrp.h"

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
