/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TableDefinition1.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:13:03 $
   End CVS Header */

/****************************************************************************
 ** 
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: Liang Xu
($Id: TableDefinition1.h,v 1.7 2003/10/16 16:13:03 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef TableDefinition1_H
#define TableDefinition1_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QCheckBox;
class QLineEdit;
class QFrame;
class QPushButton;
//class QTable;
class QRadioButton;
class QComboBox;
class QListBox;
class CModel;
class CReport;
class QString;

class TableDefinition1 : public CopasiWidget
  {
    Q_OBJECT
  protected slots:
    virtual void nameTextChanged(const QString&);
    virtual void commentTextChanged(const QString&);
    virtual void seperatorTextChanged(const QString&);
    virtual void tabButtonClicked();
    virtual void titleButtonClicked();

    virtual void languageChange();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnConfirmClicked();

    virtual void addButtonClicked();
    virtual void deleteButtonClicked();
    virtual void upButtonClicked();
    virtual void downButtonClicked();

    virtual void comboTaskChanged(const QString & string);
  public:
    TableDefinition1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TableDefinition1();
    CModel *mModel;
    inline void setModel(CModel* pNewModel)
    {mModel = pNewModel;}

    CReport *mReport;
    void setReport(CReport* pNewReport);

    std::string reportKey;
    inline void setKey(const std::string pNewKey)
    {reportKey = pNewKey;}

    QListBox* itemsTable;

    void loadTableDefinition1();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    QFrame* bodyField;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QLabel* itemsLabel;
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* deleteButton;
    QPushButton* addButton;
    //    QTable* itemsTable;
    QFrame* frame4;
    QCheckBox* tabChecked;
    QLineEdit* seperatorEdit;
    QLabel* seperatorLabel;
    QComboBox* comboTask;
    QFrame* line4;
    QLabel* taskLabel;
    QFrame* frame5;
    QLineEdit* commentEdit;
    QLabel* commentLabel;
    QLabel* targetLabel;
    QLineEdit* nameEdit;
    QCheckBox* titleChecked;

  protected:
    QGridLayout* TableDefinitionLayout;
    QHBoxLayout* layout14;
    QHBoxLayout* layout7;
    QVBoxLayout* layout6;
    QGridLayout* layout5;
    QGridLayout* frame4Layout;
    QGridLayout* frame5Layout;
    QWidget* pParent;
    bool bUpdated;
  };

#endif // TableDefinition1_H
