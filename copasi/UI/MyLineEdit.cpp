#include <qmessagebox.h>
#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget * parent, const char * name)
    : QLineEdit(parent, name)
{
  //deleteConfirmation = TRUE;
}

MyLineEdit::MyLineEdit(const QString & contents, QWidget * parent, const char * name)
    : QLineEdit(contents, parent, name)
{
  //deleteConfirmation = TRUE;
}

void MyLineEdit::focusOutEvent(QFocusEvent *fe)
{
  //QMessageBox::information(this, "got it", "yipeee ");
  emit edited();
}

/*void MyLineEdit::slotLineEditChanged()
{
  //const QString & chemreactn
 /* const QString & chemreactn = LineEdit2->text();
  const string & changed_chemical_reaction = chemreactn.latin1();
  CCopasiVectorNS < CReaction > & reactions1 = mModel->getReactions();
  CReaction *reactn1;
  reactn1 = reactions1[(string)name];
  CChemEq * chemEq1;
  chemEq1 = & reactn1->getChemEq();
  bool status;
  status = chemEq1->setChemicalEquation(changed_chemical_reaction);
  reactn1->setChemEq(changed_chemical_reaction);
   if (reactn1->isReversible() == TRUE)
    {
      checkBox->setChecked(TRUE);
    }
  else
    {
      checkBox->setChecked(FALSE);
    }
  slotCheckBoxClicked();
}*/
