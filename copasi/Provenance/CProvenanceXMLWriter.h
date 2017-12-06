// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CProvenanceXMLWriter_H
#define CProvenanceXMLWriter_H

#include <QtCore/QModelIndex>
#include <QtCore/QMap>

class CUndoStack;

class CProvenanceXMLWriter

{
  //Q_OBJECT

public:
  explicit CProvenanceXMLWriter(QWidget *parent = 0 ,
                                CUndoStack * undoStack = NULL,
                                QString PathFile = "",
                                QString ProvenanceOrigionFiletype = "",
                                QString ProvenanceOrigionTime = "",
                                QList<QString> VersionsPathToCurrentModel = QList<QString> ());

  ~CProvenanceXMLWriter();

  /**
   * Update Current Session Provenance on saving occasion
   */
  void updateCurrentSessionProvenance();

  /**
   * Update Main Body Provenance when session ends
   */
  void updateMainBodyProvenace();

  /**
   * Update Origion of file: Create/Open/Import
   */
  void updateOrigionOfProvenance(QString OrigionalFile);

  /**
   * Update Provenance and store it as the newly created Version Provenance
   */
  void updateVersionProvenanceXMLFile(QString VersionName);

  /**
   * Delete Provenance of a deleted version
   */
  void deleteVersionProvenance(QString VersionName);

  /**
   * Add the Provenance of Parent Version to the Version Provenance
   */
  void combineVersionProvenance(QString ParentVersionName, QString VersionName);

  /**
   * If the Parent of Current Version deleted, Update the Current Verison main body provenance
   */
  void deleteParentofCurrentVersionProvenance(QString VersionName);

private:

  /**
   * Merge two provenance files into a target file. Source file1 is older provenance in saving time thand Source file 2
   */
  void mergeProvenanceFiles(QString SourceFile1, QString SourceFile2, QString TargetFile);

  /**
   * Map of all entities and their ID
   */
  QHash<QString, QString> reconstructProvenanceEntityNameMap();

  /**
   * Path to the versioning data file
   */
  QString mPathFile;

  int    mProvenanceTotalEntityNumber;
  int    mProvenanceTotalActionNumber;
  int    mProvenanceTotalAgentNumber;

  /**
   * Provenance Orgional file type : Create/Open/Import
   */
  QString mProvenanceOrigionFileType;

  /**
   * Time of Create/Open/Import action (first action)
   */
  QString mProvenanceOrigionTime;

  /**
   * The last Provenance parent of current model version
   * File save and ending a session will take care of by COMBINE Archive
   */
  //QString mProvenanceParentOfCurrentModel;

  /**
   * The parent of current model version
   * Last Created/Restored Version
   */
  //QString mVersioningParentOfCurrentModel;

  /**
   * A map between Author provenance ID and their names
   * Name = 'Givenanem + FamilyName'
   */
  QMap<QString, QString> mProvenanceAuthorNameMap;

  /**
   * A point to Undo Stack
   */
  CUndoStack * mpUndoStack;

  /**
  *  A list of Versions from the root to the Parent of Current Model
  */
  QList<QString> mVersionsPathToCurrentModel;
};
#endif //CProvenanceXMLWriter_H
