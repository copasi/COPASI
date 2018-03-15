// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CProvenanceDialog_H
#define CProvenanceDialog_H

#include <QDialog>
#include <qtreewidget.h>
#include <QStandardItemModel>
#include "ui_CProvenanceDialog.h"

namespace Ui
{
class CProvenanceDialog;
}

class CProvenanceDialog : public QDialog, public Ui::CProvenanceDialog
{
  Q_OBJECT

public:
  explicit CProvenanceDialog(QWidget *parent = 0, QString PathFile = "",  QList<QString> VersionsPathToCurrentModel = QList<QString> ());

  /**
   *  Destroys the object and frees any allocated resources
   */

  ~CProvenanceDialog();

private slots:

  void on_mpTreeView_doubleClicked(const QModelIndex &index);

private:

  Ui::CProvenanceDialog *ui;

  /**
  *  Pointer to Provenance data table
  */
  QStandardItemModel *mpProvenanceTable;

  /**
  *  Pointer to Provenance browsing tree
  */
  QStandardItemModel *mpProvenanceBrowseTree;

  /**
  *  Number of Columns of Provenance data table
  */
  int mNCol;

  /**
  *  Number of Ros of Provenance data table
  */
  int mNRow;

  int mSelectedIndex;

  /**
  *  Path to Combine Archive
  */
  QString mPathFile;

  /**
  *  A list of Versions from the root to the Parent of Current Model
  */
  QList<QString> mVersionsPathToCurrentModel;

  /**
   * The last Provenance parent of current model version
   * Combine Archive will take care of File management
   */
  //QString mProvenanceParentOfCurrentModel;

  /**
   * The parent of current model version
   * Last Created/Restored Version
   */
  //QString mVersioningParentOfCurrentModel;

  /**
  *  Generate Provenance browsing tree
  */

  void generateProvenanceBrowsingTree();

  /**
  *  Generate Provenance data from Und History and append them to the provenance table
  */
  void CurrentSessionEdits2ProvenanceTable();

  /**
  *  Append data from Prov XML files to the provenance table
  */
  void ProvXMLFiles2ProvenanceTable();

  /**
   * When the last row of Provenance table is reached reallocate 10000 rows more
   */
  void reallocateProvenanceTable(int Nrow);

  /**
   * Add one row to Provenance table with the given data
   */
  void AddOneLineToTable(QString EntityType, QString Name, QString Action, QString Property, QString NewValue, QString Time, QString Author);
};

#endif // CProvenanceDialog_H
