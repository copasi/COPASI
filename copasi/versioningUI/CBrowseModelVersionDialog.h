// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CBrowseModelVersionDialog.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#ifndef CBrowseModelVersionDialog_H
#define CBrowseModelVersionDialog_H

#include <QDialog>
#include "copasi/versioning/CModelVersionHierarchy.h"
#include "copasi/versioningUI/CQModelVersionHierarchyDM.h"

class CDataModel;
class DataModelGUI;

namespace Ui
{
class CBrowseModelVersionDialog;
}

class CBrowseModelVersionDialog : public QDialog
{

  Q_OBJECT

public:

  /**
   * Default constructor
   * Fetch Version Hierarchy Model data and show it in a table
   */
  explicit CBrowseModelVersionDialog(QWidget *parent,
                                     DataModelGUI * pDataModelGUI,
                                     CDataModel * pDataModel
#ifdef COPASI_Provenance
//                                     , QString PathProvenance = QString(""),  QString ProvenanceParentOfCurrentModel = QString("")
                                     ,  QString ProvenanceParentOfCurrentModel = QString("")
#endif
                                    );

  /**
   * Destructor
   */
  ~CBrowseModelVersionDialog();

  /**
   * Returns the last saved Parent of Current Model
   * In delete case if the last saved Parrent of Current Model changes
   * It is subtitued with its parrent
   */
  //QString getLastSavedParentOfCurrentModel();

#ifdef COPASI_Provenance
  /**
   * Returns the Provenance Parent of Current Model
   */
  //QString getProvenanceParentOfCurrentModel();
#endif

private:

  Ui::CBrowseModelVersionDialog *ui;

  /**
   * A pointer to Version Hierarchy Model data
   */
  CModelVersionHierarchy * mpModelVersion;

  /**
   * A pointer to Version Hierarchy Model data
   */
  CQModelVersionHierarchyDM * mpModelVersionDM;

  /**
   * A pointer to Data Model GUI
   * It is used to load a .cps file
   */
  DataModelGUI * mpDataModelGUI;

  CDataModel * mpDataModel;

  /**
   * The last created/resotored version at the last saving occasion
   */
  //QString mLastSavedParentOfCurrentModel;

#ifdef COPASI_Provenance
  QString           mPathProvenance;
  //QString mProvenanceParentOfCurrentModel;
#endif

private slots:

  /**
  * When Restore button clicked, restore the selected version
  */
  void slotRestoreButtonClicked();

  /**
  * When Delete button clicked, delete the selected version
  */
  void slotDeleteButtonClicked();

  /**
  * When a row selected, make Restore and Delete buttons available
  */
  void slotRowSelected(QModelIndex index);
};

#endif // CBrowseModelVersionDialog_H
