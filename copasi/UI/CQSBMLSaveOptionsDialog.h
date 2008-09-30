// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLSaveOptionsDialog.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/30 15:13:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQSBMLSAVEOPTIONSDIALOG_H__
#define CQSBMLSAVEOPTIONSDIALOG_H__

#include <qdialog.h>
#include <vector>
#include <utility>

#include "copasi/copasi.h"

class QButtonGroup;
class QCheckBox;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QRadioButton;
class QComboBox;

/**
 * This dialog is popped up after the user chooses an SBML file to export.
 * Here the user can choose the level and version of SBML to store to as well
 * as some other options.
 */
class CQSBMLSaveOptionsDialog : public QDialog
  {
    Q_OBJECT

  public:
    enum COMPRESSION_TYPE
    {
      NONE,
      ZIP,
      GZIP,
      BZIP2
    };

  public:
    /**
     * Constructor.
     */
    CQSBMLSaveOptionsDialog(QWidget * parent = 0, const char * name = 0);

    /**
     * Returns the selected SBML level.
     * This method just calls the corresponding method in
     * CQSBMLVersionFrame.
     */
    unsigned C_INT32 getLevel() const;

    /**
     * Returns the selected SBML versions.
     * This method just calls the corresponding method in
     * CQSBMLVersionFrame.
     */
    unsigned C_INT32 getVersion() const;

    /**
     * Returns which kind of compression should be used when saving the
     * SBML file.
     */
    COMPRESSION_TYPE getCompressionType() const;

    /**
     * Sets the compression type for the SBML file.
     * The default is to use no compression.
     */
    void setCompressionType(COMPRESSION_TYPE type = NONE);

    /**
     * Returns whether the COPASI MIRIAM annotation should be saved.
     */
    bool isSetSaveCOPASIMIRIAM() const;

    /**
     * Sets whether the COPASI MIRIAM annotation should be saved.
     * The default is to save it.
     */
    void setSaveCOPASIMIRIAM(bool save = true);

    /**
     * Set the allowed levels and version of sbml.
     * The last item in the set is automatically selected.
     */
    void setLevelsAndVersions(const std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> >& levelsAndVersions);

    /**
     * Sets the given Level and Version as the selected level and version
     * in the combobox.
     * The pair has to exists in the set of allowed levels and version
     * which has been set by setLevelsAndVersions.
     */
    void setLevelAndVersion(const std::pair<unsigned C_INT32, unsigned C_INT32>& levelAndVersion);

  protected slots:
    // slot if the compression type changes
    void compression_clicked(int type);

    // slot if saving COPASI MIRIAM is changed
    void miriam_toggled(bool checked);

    // slot if OK button is clicked
    void ok_clicked();

    // slot if cancel button is clicked
    void cancel_clicked();
  protected:
    std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> > mLevelsAndVersions;

    // holds the set compression type
    COMPRESSION_TYPE mCompressionType;

    // holds whether COPASI MIRIAM annotation should be saved
    bool mSaveCOPASIMIRIAM;

    // the layout for the dialog
    QVBoxLayout* mpLayout;

    QComboBox* mpVersionBox;

    // a checkbox to determine if the COPASI MIRIAM annotation is to be
    // saved
    QCheckBox* mpMIRIAMCheckbox;

    // a button group to determine if the SBML file should be compressed.
    QButtonGroup* mpCompressionGroup;

    // dialog OK button
    QPushButton* mpOKButton;

    // dialog Cancel button
    QPushButton* mpCancelButton;
  };

#endif //CQSBMLSAVEOPTIONSDIALOG_H__
