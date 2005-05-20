/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget1.cpp,v $
   $Revision: 1.120 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/20 17:18:06 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/MetaboliteWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the individual
 ** Metabolites----It is the second level of Metabolites
 ********************************************************************/
#include "mathematics.h"

#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qmessagebox.h>
#include <qvalidator.h>
#include <qtable.h>
#include <qhbox.h>
#include <qpoint.h>
#include "copasi.h"
#include "MetabolitesWidget1.h"
#include "model/CModel.h"
#include "model/CChemEqInterface.h"
#include "listviews.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "MyLineEdit.h"

/*
 *  Constructs a MetabolitesWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
MetabolitesWidget1::MetabolitesWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name) setName("MetabolitesWidget1");
  setCaption(trUtf8("MetabolitesWidget1"));

  MetabolitesWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "MetabolitesWidget1Layout");

  mLblName = new QLabel(this, "mLblName");
  mLblName->setText(trUtf8("Metabolite Name"));
  mLblName->setAlignment(int(QLabel::AlignVCenter
                             | QLabel::AlignRight));
  MetabolitesWidget1Layout->addWidget(mLblName, 0, 0);

  mEditName = new QLineEdit(this, "mEditName");
  MetabolitesWidget1Layout->addMultiCellWidget(mEditName, 0, 0, 1, 2);

  mLblCompartment = new QLabel(this, "mLblCompartment");
  mLblCompartment->setText(trUtf8("Compartment"));
  mLblCompartment->setAlignment(int(QLabel::AlignVCenter
                                    | QLabel::AlignRight));
  MetabolitesWidget1Layout->addWidget(mLblCompartment, 1, 0);

  mComboCompartment = new QComboBox(FALSE, this, "mComboCompartment");
  MetabolitesWidget1Layout->addMultiCellWidget(mComboCompartment, 1, 1, 1, 2);

  mLblInitStatus = new QLabel(this, "mLblInitStatus");
  mLblInitStatus->setText(trUtf8("Metabolite status"));
  mLblInitStatus->setAlignment(int(QLabel::AlignVCenter
                                   | QLabel::AlignRight));
  MetabolitesWidget1Layout->addWidget(mLblInitStatus, 3, 0);

  mCheckStatus = new QCheckBox(this, "mCheckStatus");
  mCheckStatus->setText("fixed");
  //mCheckStatus->setChecked(false);
  mCheckStatus->setChecked(true);
  MetabolitesWidget1Layout->addWidget(mCheckStatus, 3, 1);

  //mLblStatus = new QLabel(this, "mLblStatus");
  //mLblStatus->setText(trUtf8("Model Status"));
  //MetabolitesWidget1Layout->addWidget(mLblStatus, 3, 2);

  mEditStatus = new QLineEdit(this, "mEditStatus");
  mEditStatus->setEnabled(false);
  MetabolitesWidget1Layout->addWidget(mEditStatus, 3, 2);

  //***********************************************

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  MetabolitesWidget1Layout->addMultiCellWidget(Line2, 4, 4, 0, 2);

  mLblConcentration = new QLabel(this, "mLblConcentration");
  mLblConcentration->setText(trUtf8("Initial value"));
  MetabolitesWidget1Layout->addWidget(mLblConcentration, 5, 1);

  mLblNumber = new QLabel(this, "mLblNumber");
  mLblNumber->setText(trUtf8("Transient value"));
  MetabolitesWidget1Layout->addWidget(mLblNumber, 5, 2);

  mLblInitConcentration = new QLabel(this, "mLblInitConcentration");
  mLblInitConcentration->setText(trUtf8("Concentration\n"));
  mLblInitConcentration->setAlignment(int(QLabel::AlignVCenter
                                          | QLabel::AlignRight));
  MetabolitesWidget1Layout->addWidget(mLblInitConcentration, 6, 0);

  mEditInitConcentration = new MyLineEdit(this, "mEditInitConcentration");
  mEditInitConcentration->setValidator(new QDoubleValidator(mEditInitConcentration));
  MetabolitesWidget1Layout->addWidget(mEditInitConcentration, 6, 1);

  mEditConcentration = new QLineEdit(this, "mEditConcentration");
  mEditConcentration->setEnabled(false);
  MetabolitesWidget1Layout->addWidget(mEditConcentration, 6, 2);

  mLblInitNumber = new QLabel(this, "mLblInitNumber");
  mLblInitNumber->setText(trUtf8("Particle Number"));
  mLblInitNumber->setAlignment(int(QLabel::AlignVCenter
                                   | QLabel::AlignRight));
  MetabolitesWidget1Layout->addWidget(mLblInitNumber, 7, 0);

  mEditInitNumber = new MyLineEdit(this, "mEditInitNumber");
  mEditInitNumber->setValidator(new QDoubleValidator(mEditInitNumber));
  MetabolitesWidget1Layout->addWidget(mEditInitNumber, 7, 1);

  mEditNumber = new QLineEdit(this, "mEditNumber");
  mEditNumber->setEnabled(FALSE);
  MetabolitesWidget1Layout->addWidget(mEditNumber, 7, 2);

  //********

  mLblTransitionTime = new QLabel(this, "mLblTransitionTime");
  mLblTransitionTime->setText(trUtf8("Transition Time"));
  mLblTransitionTime->setAlignment(int(QLabel::WordBreak | QLabel::AlignVCenter
                                       | QLabel::AlignRight));
  MetabolitesWidget1Layout->addWidget(mLblTransitionTime, 8, 1);

  mEditTransitionTime = new QLineEdit(this, "mEditTransitionTime");
  mEditTransitionTime->setEnabled(FALSE);
  MetabolitesWidget1Layout->addWidget(mEditTransitionTime, 8, 2);

  mLblRate = new QLabel(this, "mLblRate");
  mLblRate->setText(trUtf8("Concentration rate"));
  mLblRate->setAlignment(int(QLabel::AlignVCenter
                             | QLabel::AlignRight));
  MetabolitesWidget1Layout->addWidget(mLblRate, 9, 1);

  mEditRate = new QLineEdit(this, "mEditRate");
  mEditRate->setEnabled(FALSE);
  MetabolitesWidget1Layout->addWidget(mEditRate, 9, 2);

  //***********************************************

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  MetabolitesWidget1Layout->addMultiCellWidget(Line1, 10, 10, 0, 2); //2

  //***************************************

  mReactionsLabel = new QLabel(this, "ReactionsLabel");
  mReactionsLabel->setText("Reactions\naffecting this\nmetabolite");
  mReactionsLabel->setAlignment(int(QLabel::AlignTop
                                    | QLabel::AlignRight));
  //mReactionsLabel->setAlignment(Qt::AlignTop);
  MetabolitesWidget1Layout->addWidget(mReactionsLabel, 11, 0);

  mReactionsTable = new QTable(this, "ReactionsTable");
  mReactionsTable->setNumCols(2);
  mReactionsTable->setNumRows(2);
  mReactionsTable->verticalHeader()->hide();
  mReactionsTable->setLeftMargin(0);
  mReactionsTable->horizontalHeader()->hide();
  mReactionsTable->setTopMargin(0);
  mReactionsTable->setShowGrid(false);
  //mReactionsTable->horizontalHeader()->setLabel(0, "Name");
  //mReactionsTable->horizontalHeader()->setLabel(1, "chemical equation");
  mReactionsTable->setReadOnly(true);
  mReactionsTable->setSizePolicy(QSizePolicy::Maximum /*Preferred*/, QSizePolicy::Maximum);
  MetabolitesWidget1Layout->addMultiCellWidget(mReactionsTable, 11, 11, 1, 2);

  QSpacerItem* spacer_3 = new QSpacerItem(470, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  MetabolitesWidget1Layout->addMultiCell(spacer_3, 12, 12, 0, 2);

  Line3 = new QFrame(this, "Line3");
  Line3->setFrameShape(QFrame::HLine);
  //Line3->setFrameShadow(QFrame::Sunken);
  //Line3->setFrameShape(QFrame::HLine);
  MetabolitesWidget1Layout->addMultiCellWidget(Line3, 13, 13, 0, 2);

  //***************************************
  Layout7 = new QHBoxLayout(0, 0, 6, "Layout7");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout7->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Revert"));
  Layout7->addWidget(cancelChanges);

  newMetaboliteBtn = new QPushButton(this, "newMetaboliteBtn");
  newMetaboliteBtn->setText(trUtf8("New"));
  Layout7->addWidget(newMetaboliteBtn);

  deleteMetaboliteBtn = new QPushButton(this, "deleteMetaboliteBtn");
  deleteMetaboliteBtn->setText(trUtf8("Delete"));
  Layout7->addWidget(deleteMetaboliteBtn);

  MetabolitesWidget1Layout->addMultiCellLayout(Layout7, 14, 14, 0, 2);

  //*******************************************

  setTabOrder(mEditName, mComboCompartment);
  setTabOrder(mComboCompartment, mCheckStatus);
  setTabOrder(mCheckStatus, mEditInitConcentration);
  setTabOrder(mEditInitConcentration, mEditInitNumber);
  setTabOrder(mEditInitNumber, commitChanges);
  setTabOrder(commitChanges, cancelChanges);
  setTabOrder(cancelChanges, newMetaboliteBtn);
  setTabOrder(newMetaboliteBtn, deleteMetaboliteBtn);

  // OK button
  connect(commitChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnOKClicked()));
  // Cancel button
  connect(cancelChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnCancelClicked()));
  connect(newMetaboliteBtn, SIGNAL(clicked()),
          this, SLOT(slotBtnNewClicked()));
  connect(deleteMetaboliteBtn, SIGNAL(clicked()),
          this, SLOT(slotBtnDeleteClicked()));

  connect(mComboCompartment, SIGNAL(activated(int)), this, SLOT(slotCompChanged()));
  connect(mEditInitConcentration, SIGNAL(edited()), this, SLOT(slotConcChanged()));
  connect(mEditInitNumber, SIGNAL(edited()), this, SLOT(slotNumberChanged()));

  connect(mReactionsTable, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(slotReactionTableCurrentChanged(int, int, int, const QPoint &)));
  //mChanged = false;

  mpMetab = NULL;
  mpCurrentCompartment = NULL;
}

/*
 *  Destroys the object and frees any allocated resources
 */
MetabolitesWidget1::~MetabolitesWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

/* This function loads the metabolites widget when its name is
   clicked in the tree   */
bool MetabolitesWidget1::loadFromMetabolite()
{
  mLblInitConcentration->setText("Concentration\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + \
                                 "/" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + ")");

  mLblTransitionTime->setText("Transition Time (" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnit()) + ")");

  mLblRate->setText("Rate of concentration change\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + \
                    "/(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + "*" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnit()) + "))");

  if (!mpMetab) return false;

  CCopasiVectorNS< CCompartment > & allcompartments = CCopasiDataModel::Global->getModel()->getCompartments();
  CCompartment *compt;
  mComboCompartment->clear();
  mEditName->setText(FROM_UTF8(mpMetab->getObjectName()));
  //Metabolite1_Name = new QString(mpMetab->getObjectName().);

  mEditInitConcentration->setText(QString::number(mpMetab->getInitialConcentration(), 'g', 10));

  mEditConcentration->setText(QString::number(mpMetab->getConcentration(), 'g', 10));
  mEditConcentration->setReadOnly(true);

  mEditNumber->setText(QString::number(mpMetab->getNumber(), 'g', 10));
  mEditNumber->setReadOnly(true);

  mEditInitNumber->setText(QString::number(mpMetab->getInitialNumber(), 'g', 10));

  mEditTransitionTime->setText(QString::number(mpMetab->getTransitionTime()));
  mEditTransitionTime->setReadOnly(true);

  mEditRate->setText(QString::number(mpMetab->getConcentrationRate()));
  mEditRate->setReadOnly(true);

  if (mpMetab->getStatus() == CMetab::METAB_FIXED)
    mCheckStatus->setChecked(true);
  else
    mCheckStatus->setChecked(false);

  mEditStatus->setText(FROM_UTF8(CMetab::StatusName[mpMetab->getStatus()]));

  mComboCompartment->setDuplicatesEnabled (false);
  unsigned C_INT32 m;
  for (m = 0; m < allcompartments.size(); m++)
    {
      compt = allcompartments[m];
      //mComboCompartment->insertStringList(compt->getObjectName().,j);
      mComboCompartment->insertItem(FROM_UTF8(compt->getObjectName()));
    }

  mpCurrentCompartment = mpMetab->getCompartment();
  mComboCompartment->setCurrentText(FROM_UTF8(mpCurrentCompartment->getObjectName()));

  loadReactionsTable();

  //mChanged = false;
  return true;
}

bool MetabolitesWidget1::saveToMetabolite()
{
  //find pointer to metab from key
  if (!mpMetab) return false;

  //name
  QString name(mEditName->text());
  if ((const char *)name.utf8() != mpMetab->getObjectName())
    {
      if (!mpMetab->setObjectName((const char *)name.utf8()))
        {
          QString msg;
          msg = "Unable to rename metabolite '" + FROM_UTF8(mpMetab->getObjectName()) + "'\n"
                + "to '" + name + "' since a metabolite with that name already exists\n"
                + "in the compartment '" + FROM_UTF8(mpMetab->getCompartment()->getObjectName()) + "'.";

          QMessageBox::warning(this,
                               "Unable to rename Metabolite",
                               msg,
                               QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          mEditName->setText(FROM_UTF8(mpMetab->getObjectName()));
        }
      else
        protectedNotify(ListViews::METABOLITE, ListViews::RENAME, objKey);
    }

  //compartment
  QString Compartment = mComboCompartment->currentText();
  if ((const char *)Compartment.utf8() != mpMetab->getCompartment()->getObjectName())
    {
      std::string CompartmentToRemove = mpMetab->getCompartment()->getObjectName();
      if (!CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()]->addMetabolite(mpMetab))
        {
          QString msg;
          msg = "Unable to move metabolite '" + FROM_UTF8(mpMetab->getObjectName()) + "'\n"
                + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + Compartment + "'\n"
                + "since a metabolite with that name already exist in the target compartment.";

          QMessageBox::warning(this,
                               "Unable to move Metabolite",
                               msg,
                               QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          mComboCompartment->setCurrentText(FROM_UTF8(CompartmentToRemove));
        }
      else
        {
          CCopasiDataModel::Global->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(mpMetab->getObjectName());
          CCopasiDataModel::Global->getModel()->setCompileFlag();
          CCopasiDataModel::Global->getModel()->initializeMetabolites();
          //protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
          protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
          protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
        }
    }

  //for Initial Concentration and Initial Number
  QString initialConcentration(mEditInitConcentration->text());
  double temp1;
  temp1 = initialConcentration.toDouble();
  if (fabs(temp1 - mpMetab->getInitialConcentration()) > 1e-40)
    {
      mpMetab->setInitialConcentration(temp1);
      //mpMetab->setConcentration(temp1);
      protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
      //CCopasiDataModel::Global->getModel()->setCompileFlag();
    }

  //fixed?
  if (mCheckStatus->isChecked() == true)
    {
      if (mpMetab->getStatus() != CMetab::METAB_FIXED)
        {
          mpMetab->setStatus(CMetab::METAB_FIXED);
          protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
          CCopasiDataModel::Global->getModel()->setCompileFlag();
        }
    }
  else
    {
      if (mpMetab->getStatus() != CMetab::METAB_VARIABLE) //TODO: should be ...==METAB_FIXED ?
        {
          mpMetab->setStatus(CMetab::METAB_VARIABLE);
          protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
          CCopasiDataModel::Global->getModel()->setCompileFlag();
        }
    }

  loadFromMetabolite();

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();

  return true; //TODO: really check
}

bool MetabolitesWidget1::loadReactionsTable()
{
  std::set<std::string> reactions = CCopasiDataModel::Global->getModel()->listReactionsDependentOnMetab(objKey);
  mReactionsTable->setNumRows(0);
  mReactionsTable->setNumRows(reactions.size() + 1);
  if (reactions.size() < 2) mReactionsTable->setNumRows(3);
  mReactionsTable->setText(0, 0, "none     ");

  std::set<std::string>::const_iterator it, itEnd = reactions.end();
  C_INT32 i;
  CReaction* pReac;
  for (it = reactions.begin(), i = 0; it != itEnd; ++it, ++i)
    {
      pReac = dynamic_cast< CReaction * >(GlobalKeys.get(*it));
      mReactionsTable->setText(i, 0, FROM_UTF8(pReac->getObjectName()) + ": ");
      mReactionsTable->setText(i, 1, FROM_UTF8(CChemEqInterface::getChemEqString(CCopasiDataModel::Global->getModel(), *pReac, false)));
    }
  mReactionsTable->adjustColumn(0);
  mReactionsTable->adjustColumn(1);

  return true;
}

void MetabolitesWidget1::slotReactionTableCurrentChanged(int C_UNUSED(mRow), int C_UNUSED(mCol),
    int C_UNUSED(mButton), const QPoint & C_UNUSED(mCur))
{
  std::set<std::string> reactions = CCopasiDataModel::Global->getModel()->listReactionsDependentOnMetab(objKey);
  CReaction* pReac;
  std::string s1, s2;
  C_INT32 i;
  std::set<std::string>::const_iterator it, itEnd = reactions.end();
  s1 = mReactionsTable->text(mReactionsTable->currentRow(), 0).utf8();
  s1 = s1.substr(0, s1.length() - 2);
  for (it = reactions.begin(), i = 0; it != itEnd; ++it, ++i)
    {
      pReac = dynamic_cast< CReaction * >(GlobalKeys.get(*it));
      s2 = pReac->getObjectName();

      if (s1 == s2)
        {
          pListView->switchToOtherWidget(0, pReac->getKey());
        }
    }
}

void MetabolitesWidget1::slotBtnCancelClicked()
{
  //let the user confirm
  enter(objKey); // reload
}

void MetabolitesWidget1::slotBtnOKClicked()
{
  //let the user confirm?
  saveToMetabolite();
}

void MetabolitesWidget1::slotBtnNewClicked()
{
  if (CCopasiDataModel::Global->getModel()->getCompartments().size() == 0)
    CCopasiDataModel::Global->getModel()->createCompartment("compartment");

  std::string name = "metabolite";
  int i = 0;
  CMetab* mpMetab;
  while (!(mpMetab = CCopasiDataModel::Global->getModel()->createMetabolite(name, "", 1.0, CMetab::METAB_VARIABLE)))
    {
      i++;
      name = "metabolite_";
      name += (const char *)QString::number(i).utf8();
    }
  enter(mpMetab->getKey());
  protectedNotify(ListViews::METABOLITE, ListViews::ADD);
}

void MetabolitesWidget1::slotBtnDeleteClicked()
{
  if (!CCopasiDataModel::Global->getModel())
    return;

  QString metabList = "Are you sure you want to delete listed METABOLITE(S) ?\n";
  QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
  int reacFound = 0;

  //unsigned C_INT32 i, imax = keys.size();
  //for (i = 0; i < imax; i++)
  //  {
  //metabList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
  metabList.append(FROM_UTF8(GlobalKeys.get(objKey)->getObjectName()));
  metabList.append(", ");

  //CMetab* metab =
  //  dynamic_cast< CMetab *>(GlobalKeys.get(keys[i]));

  std::set<std::string> effectedReacKeys = CCopasiDataModel::Global->getModel()->listReactionsDependentOnMetab(objKey);

  if (effectedReacKeys.size() > 0)
    {
      reacFound = 1;
      std::set<std::string>::const_iterator it, itEnd = effectedReacKeys.end();
      for (it = effectedReacKeys.begin(); it != itEnd; ++it)
        {
          effectedReacList.append(FROM_UTF8(GlobalKeys.get(*it)->getObjectName()));
          effectedReacList.append(", ");
        }
      effectedReacList.remove(effectedReacList.length() - 2, 2);
      effectedReacList.append("  ---> ");
      effectedReacList.append(FROM_UTF8(GlobalKeys.get(objKey)->getObjectName()));
      effectedReacList.append("\n");
    }
  //}

  metabList.remove(metabList.length() - 2, 2);

  QString msg = metabList;
  if (reacFound == 1)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  C_INT32 choice;
  if (reacFound == 1)
    choice = QMessageBox::warning(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 0, 1);
  else
    choice = 0;

  switch (choice)
    {
    case 0:                                                    // Yes or Enter
      {
        unsigned C_INT32 size = CCopasiDataModel::Global->getModel()->getMetabolites().size();
        //unsigned C_INT32 index = Copasi->pFunctionDB->loadedFunctions().getIndex(pFunction->getObjectName());
        unsigned C_INT32 index = CCopasiDataModel::Global->getModel()->getMetabolites().getIndex(GlobalKeys.get(objKey));
        /*for (i = 0; i < imax; i++)
               {
                 CCopasiDataModel::Global->getModel()->removeMetabolite(keys[i]);
               }*/
        CCopasiDataModel::Global->getModel()->removeMetabolite(objKey);
        if (size > 1)
          {
            enter(CCopasiDataModel::Global->getModel()->getMetabolites()[std::min(index, size - 2)]->getKey());
            //for (i = 0; i < imax; i++)
          }
        else
          {
            enter("");
          }
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, objKey);
        //TODO notify about reactions
        break;
      }
    case 1:                                                    // No or Escape
      break;
    }
}

void MetabolitesWidget1::slotConcChanged()
{
  if (!mpMetab) return;

  C_FLOAT64 tmp = mEditInitConcentration->text().toDouble();
  mEditInitNumber->setText(QString::number(tmp
                           * mpMetab->getCompartment()->getVolume()
                           * CCopasiDataModel::Global->getModel()->getQuantity2NumberFactor(), 'g', 10));
  //mChanged = true;
}

void MetabolitesWidget1::slotNumberChanged()
{
  if (!mpMetab) return;

  C_FLOAT64 tmp = mEditInitNumber->text().toDouble();
  mEditInitConcentration->setText(QString::number(tmp
                                  * mpMetab->getCompartment()->getVolumeInv()
                                  * CCopasiDataModel::Global->getModel()->getNumber2QuantityFactor(), 'g', 10));
}

void MetabolitesWidget1::slotCompChanged()
{
  if (!mpMetab || !mpCurrentCompartment) return;

  QString Compartment = mComboCompartment->currentText();

  C_FLOAT64 Factor = 1.0 / mpCurrentCompartment->getInitialVolume();

  mpCurrentCompartment = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()];
  Factor *= mpCurrentCompartment->getInitialVolume();

  mEditInitNumber->setText(QString::number(Factor * mEditInitNumber->text().toDouble(), 'g', 10));
  mEditNumber->setText(QString::number(Factor * mEditNumber->text().toDouble(), 'g', 10));
}

bool MetabolitesWidget1::update(ListViews::ObjectType objectType,
                                ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::STATE:
    case ListViews::MODEL:
    case ListViews::METABOLITE:
    case ListViews::COMPARTMENT:
      mpMetab = dynamic_cast< CMetab * >(GlobalKeys.get(objKey));
      return loadFromMetabolite();
      break;

    default:
      break;
    }
  return true;
}

bool MetabolitesWidget1::leave()
{
  return saveToMetabolite();
}

bool MetabolitesWidget1::enter(const std::string & key)
{
  objKey = key;
  mpMetab = dynamic_cast< CMetab * >(GlobalKeys.get(key));

  if (mpMetab) return loadFromMetabolite();
  else return false;
}
