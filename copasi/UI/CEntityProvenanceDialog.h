// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CENTITYPROVENANCEDialog_H
#define CENTITYPROVENANCEDialog_H

#include <QUndoStack>
#include <QStandardItemModel>
#include <copasiWidget.h>
#include "ui_CEntityProvenanceDialog.h"

class CEntityProvenanceDialog :  public CopasiWidget,   public Ui::CEntityProvenanceDialog
{
  Q_OBJECT

public:
  //CEntityProvenanceDialog(QWidget *parent = 0,  QUndoStack * UndoStack = NULL, QString EntityName = QString(""), QString PathFile = "",  QList<QString> VersionsPathToCurrentModel = QList<QString> (),  QString ProvenanceParentOfCurrentModel = "", QString VersioningParentOfCurrentModel = "", const char* name = 0);
  CEntityProvenanceDialog(QWidget *parent = 0,  QUndoStack * UndoStack = NULL, QString PathFile = "",  QList<QString> VersionsPathToCurrentModel = QList<QString> (),  QString ProvenanceParentOfCurrentModel = "", QString VersioningParentOfCurrentModel = "", const char* name = 0);
  ~CEntityProvenanceDialog();

  void load(QUndoStack * UndoStack, QString EntityNameQString, QString PathFile,  QList<QString> VersionsPathToCurrentModel);

private:
  Ui::CEntityProvenanceDialog *ui;

  /**
  *  Pointer to Undo Stack
  */
  QUndoStack * mpUndoStack;

  /**
  *  Pointer to Provenance data table
  */
  QStandardItemModel *mpProvenanceTable;

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
  *  Name of the Entity that Provenance table is made for
  */
  QString mEntityName;

  /**
   * The last Provenance parent of current model version
   */
// QString mProvenanceParentOfCurrentModel;

  /**
   * The parent of current model version
   * Last Created/Restored Version
   */
  //QString mVersioningParentOfCurrentModel;

  /**
  *  Generate Provenance data from Undo History and append them to the provenance table
  */
  void CurrentSessionEdits2ProvenanceTable();

  /**
  *  Append data from Prov XML files to the provenance table
  */
  void ProvXMLFiles2ProvenanceTable();

  /**
   * When the last row of Provenance table is reached reallocate 100 rows more
   */
  void reallocateProvenanceTable(int Nrow);

  /**
   * Add one row to Provenance table with the given data
   */
  void versionToTable(QString Action, QString Property, QString NewValue, QString Time, QString Author);
};

#endif // CENTITYPROVENANCEDialog_H
