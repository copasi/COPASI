/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CCopasiSelectionDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/10 12:36:34 $
   End CVS Header */

#ifndef CCopasiSelectionDialog_H__
#define CCopasiSelectionDialog_H__

#include "qdialog.h"
#include <vector>

class QPushButton;
class QCheckBox;
class CCopasiSelectionWidget;
class QHBox;
class QVBoxLayout;
class QHBoxLayout;
class CCopasiObject;
class CModel;

class CCopasiSelectionDialog: public QDialog
  {
    Q_OBJECT

  protected:
    QPushButton* mpOKButton;
    QPushButton* mpCancelButton;
    QCheckBox* mpModeCheckBox;
    QHBox* mpButtonBox;
    QWidget* mpMainWidget;
    CCopasiSelectionWidget* mpSelectionWidget;
    QVBoxLayout* mpMainLayout;
    std::vector<CCopasiObject*>* mpTmpVector;
    std::vector<CCopasiObject*>* mpOutputVector;
    bool mExpertMode;

  protected slots:
    void okButton_clicked();
    void cancelButton_clicked();
    void modeButton_toggled(bool checked);

  public:
    CCopasiSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = FALSE);
    virtual ~CCopasiSelectionDialog();
    void setOutputVector(std::vector<CCopasiObject*>* outputVector);
    void setModel(CModel* model);
    void setSingleSelection(bool singleSelectionMode);
  };

#endif /* SimpleSelectionDialog_H__ */
