/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/SimpleSelectionDialog.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:50 $
   End CVS Header */

#ifndef SimpleSelectionDialog_H__
#define SimpleSelectionDialog_H__

#include "qdialog.h"
#include <vector>

class QPushButton;
class SimpleSelectionWidget;
class QHBox;
class QVBoxLayout;
class QHBoxLayout;
class CCopasiObject;
class CModel;
class ObjectBrowserWidget;

class SimpleSelectionDialog: public QDialog
  {
    Q_OBJECT

  protected:
    QPushButton* okButton;
    QPushButton* cancelButton;
    QPushButton* modeButton;
    QHBoxLayout* buttonBox;
    QWidget* mainWidget;
    SimpleSelectionWidget* simpleSelectionWidget;
    ObjectBrowserWidget* objectBrowserWidget;
    QVBoxLayout* mainLayout;
    std::vector<CCopasiObject*>* tmpVector;
    std::vector<CCopasiObject*>* outputVector;
    bool expertMode;

  protected slots:
    void okButton_clicked();
    void cancelButton_clicked();
    void modeButton_clicked();

  public:
    SimpleSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = FALSE);
    virtual ~SimpleSelectionDialog();
    void setOutputVector(std::vector<CCopasiObject*>* outputVector);
    void setModel(CModel* model);
  };

#endif /* SimpleSelectionDialog_H__ */
