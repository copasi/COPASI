/****************************************************************************
 ** 
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: Liang Xu
($Id: TableDefinition1.h,v 1.1 2003/08/13 15:02:00 lixu1 Exp $)
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
    virtual void tabButtonClicked();
    virtual void titleButtonClicked();
    virtual void appendButtonClicked();

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
    QFrame* frame4;
    QCheckBox* tabChecked;
    QLineEdit* seperatorEdit;
    QLabel* seperatorLabel;
    QComboBox* comboTask;
    QFrame* line4;
    QLabel* taskLabel;
    QFrame* frame5;
    QLabel* targetLabel;
    QLineEdit* targetEdit;
    QCheckBox* titleChecked;
    QCheckBox* appendChecked;

  protected:
    QGridLayout* TableDefinition1Layout;
    QHBoxLayout* layout14;
    QHBoxLayout* layout7;
    QVBoxLayout* layout6;
    QGridLayout* layout5;
    QGridLayout* frame4Layout;
    QGridLayout* frame5Layout;
    QHBoxLayout* layout5_2;

    QWidget* pParent;
    std::vector<CCopasiObject*> selectedList;
  };

#endif // TableDefinition1_H
