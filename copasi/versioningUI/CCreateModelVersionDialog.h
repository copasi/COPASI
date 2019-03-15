// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CCreateModelVersionDialog.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#ifndef CCreateModelVersionDialog_H
#define CCreateModelVersionDialog_H

#include <QDialog>

#include "copasi/versioningUI/ui_CCreateModelVersionDialog.h"

namespace Ui
{
class CCreateModelVersionDialog;
}

class CCreateModelVersionDialog : public QDialog
{
  Q_OBJECT

public:

  /**
   * Default constructor
   * Fetch author information from COPASI configuration
   */
  explicit CCreateModelVersionDialog(QWidget *parent = 0);
  /**
   * Destructor
   */
  ~CCreateModelVersionDialog();

  /**
   * Retrieve the version name of the created version
   */
  QString getVersion() const;

  /**
   * Retrieve the comments of the created version
   */
  QString getComments() const;

  /**
  * Return true if the newly version name is captured from dialog
  */
  bool isDataCaptured() const;

  /**
   * Retrieve the Given Name of the author of version
   */
  QString getGivenName() const;

  /**
   * Retrieve the Family Name of the author of version
   */
  QString getFamilyName() const;

  /**
   * Retrieve the organization of the author of version
   */
  QString getOrganization() const;

  /**
   * Retrieve the email of the author of version
   */
  QString getEmail() const;

private slots:

  /**
   * Retrieve the version name and comment from the dialog on 'OK' button clicked
   */
  void on_OkButton_clicked();

  void on_lineEdit_2_textEdited(const QString &arg1);

private:
  Ui::CCreateModelVersionDialog *ui;

  /**
   * Version name of the created version
   */
  QString  mVersion;

  /**
   * Comments of the created version
   */
  QString  mComments;

  /**
   * Author's name who creates version
   */
  QString  mGivenName;

  /**
   * Author's familyname who creates version
   */
  QString  mFamilyName;

  /**
   * Author's organization who creates version
   */
  QString  mOrganization;

  /**
   * Author's email who creates version
   */
  QString  mEmail;

  /**
   * Checks whether version information has captured from the table
   */
  bool  mDataCaptured;
};

#endif // CCreateModelVersionDialog_H
