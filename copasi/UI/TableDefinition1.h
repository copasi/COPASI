/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TableDefinition1.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/28 15:24:57 $
   End CVS Header */

/****************************************************************************
 ** 
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: Liang Xu
($Id: TableDefinition1.h,v 1.10 2004/06/28 15:24:57 ssahle Exp $)
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
    //virtual void nameTextChanged(const QString&);
    virtual void commentTextChanged(const QString&);
    virtual void separatorTextChanged(const QString&);
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

  private:
    CModel *mModel;
    inline void setModel(CModel* pNewModel)
    {mModel = pNewModel;}

    CReport *mReport;

    std::string reportKey;
    inline void setKey(const std::string pNewKey)
    {reportKey = pNewKey;}

    QListBox* itemsTable;

    void loadTableDefinition1();

  public:
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  private:
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
    QLineEdit* separatorEdit;
    QLabel* separatorLabel;
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
