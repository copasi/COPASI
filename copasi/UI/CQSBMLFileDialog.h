// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLFileDialog.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/11/15 21:42:24 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSBML_FILE_DIALOG
#define CQSBML_FILE_DIALOG

#include "UI/CopasiFileDialog.h"
#include <vector>
#include <utility>
#include "copasi.h"

class QComboBox;
class QLabel;

class CQSBMLFileDialog : public CopasiFileDialog
  {
    Q_OBJECT
  private:
    QComboBox* mpSBMLVersionBox;
    QLabel* mpSBMLVersionLabel;
    std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> > mSBMLVersions;

  public:
    CQSBMLFileDialog(QWidget * parent , const char * name , bool modal);

    std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> >
    getOpenFileName(const QString & startWith = QString::null,
                    const QString & filter = QString::null,
                    const QString & caption = QString::null,
                    QString selectedFilter = QString::null);
  };

#endif // CQSBML_FILE_DIALOG
