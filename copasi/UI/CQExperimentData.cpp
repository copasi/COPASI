// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentData.cpp,v $
//   $Revision: 1.15.2.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:49 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQExperimentData.h"

#include <qvariant.h>
#include <algorithm>
#include <limits>
#include <math.h>
#include <qsignalmapper.h>
#include <qcombobox.h>

#include "copasi.h"

#include "UI/CCopasiSelectionDialog.h"
#include "UI/CopasiFileDialog.h"
#include "UI/CQValidator.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"
#include "UI/CQIcons.h"

#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentFileInfo.h"
#include "parameterFitting/CExperimentObjectMap.h"

#include "report/CKeyFactory.h"
#include "utilities/CDirEntry.h"
#include "utilities/utility.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "commandline/CLocaleString.h"

#define COL_NAME 0
#define COL_TYPE 1
#define COL_TYPE_HIDDEN 2
#define COL_BTN 3
#define COL_OBJECT 4
#define COL_OBJECT_HIDDEN 5
#define COL_WEIGHT 6

#define InvalidIndex std::numeric_limits< unsigned C_INT32 >::max()

/*
 *  Constructs a CQExperimentData as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQExperimentData::CQExperimentData(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQExperimentData::~CQExperimentData()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

class CQExperimentDataValidator: public CQValidatorNotEmpty
{
public:
  enum Type
  {
    Name = 0,
    FirstRow,
    LastRow,
    HeaderRow
  };

  // Operations
public:
  CQExperimentDataValidator(QLineEdit * parent,
                            const char * name,
                            CQExperimentData * pContext,
                            const Type & type):
      CQValidatorNotEmpty(parent, name),
      mpIntValidator(new QIntValidator(1, std::numeric_limits< int >::max(), parent)),
      mpContext(pContext),
      mType(type)
  {}

  virtual State validate(QString & input, int & pos) const
  {
    if (mpContext->mShown == (unsigned int) - 1) return Acceptable;

    if (mType == Name)
      {
        if (input == "All")
          {
            setColor(Invalid);
            return Intermediate;
          }

        if (mLastAccepted != input &&
            mpContext->mpExperimentSetCopy->getParameter(TO_UTF8(input)))
          {
            setColor(Invalid);
            return Intermediate;
          }
      }
    else
      {
        if (mpIntValidator->validate(input, pos) != Acceptable)
          {
            setColor(Invalid);
            return Intermediate;
          }

        size_t First, Last;

        switch (mType)
          {
            case FirstRow:

              if (!mpContext->mpFileInfo->validateFirst(mpContext->mShown, input.toULong()))
                {
                  size_t NewFirst = input.toULong();

                  mpContext->mpFileInfo->getFirstUnusedSection(First, Last);

                  while (NewFirst > Last)
                    mpContext->mpFileInfo->getNextUnusedSection(First, Last);

                  if (First <= NewFirst && NewFirst <= Last)
                    {
                      if (First > mpContext->mpExperiment->getLastRow())
                        {
                          mpContext->mpExperiment->setLastRow((unsigned C_INT32) Last);
                          mpContext->mpExperiment->setFirstRow((unsigned C_INT32) First);
                        }
                      else
                        {
                          mpContext->mpExperiment->setFirstRow((unsigned C_INT32) First);
                          mpContext->mpExperiment->setLastRow((unsigned C_INT32) Last);
                        }

                      mpContext->syncExperiments();

                      mpContext->mpEditFirst->setText(QString::number(First));
                      mpContext->mpEditLast->setText(QString::number(Last));
                      mpContext->mpValidatorLast->revalidate();

                      return validate(input, pos);
                    }

                  setColor(Invalid);
                  return Intermediate;
                }

              mpContext->mpExperiment->setFirstRow(input.toULong());
              mpContext->mpFileInfo->sync();
              mpContext->mpBtnExperimentAdd->setEnabled(mpContext->mpFileInfo->getFirstUnusedSection(First, Last));
              break;

            case LastRow:

              if (!mpContext->mpFileInfo->validateLast(mpContext->mShown, input.toULong()))
                {
                  setColor(Invalid);
                  return Intermediate;
                }

              mpContext->mpExperiment->setLastRow(input.toULong());
              mpContext->mpFileInfo->sync();
              mpContext->mpBtnExperimentAdd->setEnabled(mpContext->mpFileInfo->getFirstUnusedSection(First, Last));
              break;

            case HeaderRow:

              if (!mpContext->mpFileInfo->validateHeader(mpContext->mShown, input.toULong()))
                {
                  setColor(Invalid);
                  return Intermediate;
                }

              mpContext->mpExperiment->setHeaderRow(input.toULong());
              break;

            default:
              break;
          }
      }

    return CQValidatorNotEmpty::validate(input, pos);
  }

  // virtual State revalidate();

  // virtual void forceAcceptance(const QString & input) const;

  // virtual void saved() const;

  // Attributes
private:
  QIntValidator * mpIntValidator;

  CQExperimentData * mpContext;

  Type mType;
};

void CQExperimentData::slotRevert()
{
  load(mpExperimentSet, mpDataModel);
}

void CQExperimentData::slotFirst()
{
  qWarning("CQExperimentData::slotFirst(): Not implemented yet");

  size_t Row = C_INVALID_INDEX;

  if (mpEditFirst->text() != "")
    Row = mpEditFirst->text().toULong();

  if (Row == C_INVALID_INDEX)
    {
      //  Row = find first non used row in file
    }

  // display dialog with table showing file section of First row

  // if accept
  //  set mpEditFirst
}

void CQExperimentData::slotLast()
{
  size_t Row = C_INVALID_INDEX;

  if (mpEditLast->text() != "")
    Row = mpEditLast->text().toULong();

  if (Row == C_INVALID_INDEX && mpEditFirst->text() != "")
    Row = mpEditFirst->text().toULong();

  // display dialog with table showing file section of First row

  // if accept
  //  set mpEditFirst
  // if last row
  //  display table showing file section of last row inexperiment
  // else if  first
  //  display table showing file section of  first row in file
  // else
  //  display table showing file section of last non used row in file

  // if accept
  //  set mpEditLast
}

void CQExperimentData::slotHeader()
{
  qWarning("CQExperimentData::slotHeader(): Not implemented yet");

  // if header row
  //  display table showing file section of header row inexperiment
  // if first row
  //  display table showing file section of first row inexperiment
  // else if last row
  //  display table showing file section of last row inexperiment
  // else
  //  display table showing file section of  first non used row in file

  // if accept
  //  set mpEditHeader
  //  check mpCheckHeader
  // else
  // uncheck mpCheckHeader
}

void CQExperimentData::slotExprimentType(bool isSteadyState)
{
  if (!mpExperiment) return;

  if (isSteadyState)
    {
      mpBtnSteadystate->setFocus();
      mpExperiment->setExperimentType(CCopasiTask::steadyState);
    }
  else
    {
      mpBtnTimeCourse->setFocus();
      mpExperiment->setExperimentType(CCopasiTask::timeCourse);
    }

  saveTable(mpExperiment);

  // Undo the changes so that copy from and to work.
  if (isSteadyState)
    {
      mpExperiment->setExperimentType(CCopasiTask::timeCourse);
    }
  else
    {
      mpExperiment->setExperimentType(CCopasiTask::steadyState);
    }

  size_t i, imax = mpTable->numRows();

  if (isSteadyState)
    for (i = 0; i < imax; i++)
      {
        CExperiment::Type Type =
          static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget((int) i, COL_TYPE))->currentItem());

        if (Type == CExperiment::time)
          mpExperiment->getObjectMap().setRole(i, CExperiment::ignore);
      };

  loadTable(mpExperiment, true);
  return;
}

void CQExperimentData::slotCheckTab(bool checked)
{
  mpEditSeparator->setEnabled(!checked);

  if (checked)
    mpCheckTab->setFocus();
  else
    mpEditSeparator->setFocus();

  if (mpEditSeparator->isEnabled() &&
      mpEditSeparator->text().isEmpty())
    mpEditSeparator->setText(",");
  else
    slotSeparator();
}

void CQExperimentData::slotCheckHeader(bool checked)
{
  mpEditHeader->setEnabled(checked);

  if (!checked)
    {
      this->mpEditHeader->setText("");
    }
}

void CQExperimentData::slotExperimentAdd()
{
  mShowError = false;

  CExperiment Experiment(mpDataModel);
  CExperiment * pExperiment = mpExperimentSetCopy->addExperiment(Experiment);

  size_t First, Last;
  mpFileInfo->getFirstUnusedSection(First, Last);
  pExperiment->setFirstRow((unsigned C_INT32) First);
  pExperiment->setLastRow((unsigned C_INT32) Last);
  pExperiment->setHeaderRow((unsigned C_INT32) First);
  pExperiment->setFileName(mpFileInfo->getFileName());

  pExperiment->setNumColumns((unsigned C_INT32) pExperiment->guessColumnNumber());
  mpFileInfo->sync();

  mpBoxExperiment->insertItem(FROM_UTF8(pExperiment->getObjectName()));
  mpBoxExperiment->setSelected(mpBoxExperiment->count() - 1, true);

  syncExperiments();
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  mShowError = true;
}

void CQExperimentData::slotExperimentChanged(Q3ListBoxItem * pItem)
{
  std::string Name;

  if (pItem != NULL)
    Name = TO_UTF8(pItem->text());

  CCopasiMessage::clearDeque();

  bool success = true;

  saveExperiment(mpExperiment, true);

  if (pItem != NULL)
    {
      mpExperiment = mpFileInfo->getExperiment(Name);
      mShown = mpBoxExperiment->currentItem();

      std::ifstream File;
      File.open(CLocaleString::fromUtf8(mpExperiment->getFileName()).c_str());

      size_t CurrentLine = 1;
      success &= mpExperiment->read(File, CurrentLine);

      if (success)
        success &= mpExperiment->compile();
    }
  else
    {
      mpExperiment = NULL;
      mShown = (unsigned int) - 1;
    }

  loadExperiment(mpExperiment);

  if (!success && CCopasiMessage::size() > 0 && mShowError)
    {
      CQMessageBox::information(this, "Specification Error", FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }

  enableEdit(!mpCheckFrom->isChecked());
}

void CQExperimentData::slotExperimentDelete()
{
  // Get info from current selection
  size_t index = mpBoxExperiment->currentItem();

  if (index == C_INVALID_INDEX) return;

  std::string key =
    mpFileInfo->getExperiment(TO_UTF8(mpBoxExperiment->item((int) index)->text()))->CCopasiParameter::getKey();

  // change selection
  if (mpBoxExperiment->count() > 1)
    {
      if (mpBoxExperiment->count() > index + 1)
        mpBoxExperiment->setSelected((int)(index + 1), true);
      else
        mpBoxExperiment->setSelected((int)(index - 1), true);
    }
  else
    slotExperimentChanged(NULL);

  // remove experiment
  mpExperimentSetCopy->removeExperiment(mpExperimentSetCopy->keyToIndex(key));
  syncExperiments();

  size_t First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  // We need to correct mpCheckFrom and mpCheckTo since the removal of the experiment
  // may have changed their status.
  disconnect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));
  disconnect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));

  mpCheckFrom->setChecked(isLikePreviousExperiment(mpExperiment));
  enableEdit(!mpCheckFrom->isChecked());

  if (mpExperiment)
    {
      size_t Next =
        mpExperimentSetCopy->keyToIndex(mpExperiment->CCopasiParameter::getKey()) + 1;


      if (Next < mpExperimentSetCopy->size())
        mpCheckTo->setChecked(isLikePreviousExperiment(mpExperimentSetCopy->getExperiment(Next)));
      else
        mpCheckTo->setChecked(false);
    }

  connect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  connect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));
}

void CQExperimentData::slotFileAdd()
{
  QString File =
    CopasiFileDialog::getOpenFileName(this,
                                      "Open File Dialog",
                                      "",
                                      "Data Files (*.txt *.csv);;All Files (*)",
                                      "Open Data Files");

  if (File.isNull()) return;

  std::map<std::string, std::string>::const_iterator it = mFileMap.begin();
  std::map<std::string, std::string>::const_iterator end = mFileMap.end();
  size_t i;

  for (; it != end; ++it)
    if (it->second == TO_UTF8(File))
      {
        for (i = 0; i < mpBoxFile->count(); i++)
          if (it->first == TO_UTF8(mpBoxFile->item((int) i)->text()))
            {
              mpBoxFile->setSelected((int) i, true);
              break;
            }

        return;
      }

  std::string FileName = CDirEntry::fileName(TO_UTF8(File));

  i = 0;

  while (mFileMap.find(FileName) != mFileMap.end())
    FileName = StringPrint("%s_%d", CDirEntry::fileName(TO_UTF8(File)).c_str(), i++);

  mFileMap[FileName] = TO_UTF8(File);
  mpBoxFile->insertItem(FROM_UTF8(FileName));

  mpBoxFile->setSelected(mpBoxFile->count() - 1, true);

  size_t First, Last;

  if (mpFileInfo->getFirstUnusedSection(First, Last))
    {
      do
        {
          slotExperimentAdd();
        }
      while (mpBtnExperimentAdd->isEnabled());

      mpBoxExperiment->setSelected(0, true);
    }
}

void CQExperimentData::slotFileChanged(Q3ListBoxItem * pItem)
{
  if (pItem)
    {
      slotExperimentChanged(NULL); // Assure that changes are saved.
      mpBoxExperiment->clear();

      if (mpFileInfo->setFileName(mFileMap[TO_UTF8(pItem->text())]))
        {
          // fill experiment list box

          std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
          std::vector< std::string >::const_iterator it = ExperimentNames.begin();
          std::vector< std::string >::const_iterator end = ExperimentNames.end();

          for (; it != end; ++it)
            mpBoxExperiment->insertItem(FROM_UTF8((*it)));
        }

      if (mpBoxExperiment->count())
        mpBoxExperiment->setSelected(0, true);
      else
        slotExperimentChanged(NULL);
    }
  else
    {
      mpBoxExperiment->clear();
      slotExperimentChanged(NULL);
    }

  size_t First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));
}

void CQExperimentData::slotFileDelete()
{
  // Get info from current selection
  size_t index = mpBoxFile->currentItem();

  if (index == C_INVALID_INDEX) return;

  std::string FileName = mFileMap[TO_UTF8(mpBoxFile->item((int) index)->text())];

  // change selection
  if (mpBoxFile->count() > 1)
    {
      if (mpBoxFile->count() > index + 1)
        mpBoxFile->setSelected((int)(index + 1), true);
      else
        mpBoxFile->setSelected((int)(index - 1), true);
    }
  else
    slotFileChanged(NULL);

  // remove file
  mFileMap.erase(TO_UTF8(mpBoxFile->item((int) index)->text()));
  mpBoxFile->removeItem((int) index);

  // delete all experiments in current file.
  size_t i = mpExperimentSetCopy->getExperimentCount() - 1;

  for (; i != C_INVALID_INDEX; i--)
    if (mpExperimentSetCopy->getExperiment(i)->getFileName() == FileName)
      mpExperimentSetCopy->removeExperiment(i);
}

void CQExperimentData::slotCancel()
{
  pdelete(mpExperimentSetCopy);
  reject();
}

void CQExperimentData::slotOK()
{
  // Force the save all current changes.
  slotExperimentChanged(NULL);

  CExperiment * pExperiment;

  size_t i = mpExperimentSet->getExperimentCount() - 1;

  for (; i != C_INVALID_INDEX; i--)
    {
      pExperiment =
        dynamic_cast<CExperiment *>(CCopasiRootContainer::getKeyFactory()->get(mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()]));

      if (pExperiment)
        {
          *mpExperimentSet->getExperiment(i) = *pExperiment;
          mpExperimentSetCopy->removeParameter(pExperiment->getObjectName());
        }
      else
        mpExperimentSet->removeExperiment(i);
    }

  emit experimentChanged();

  for (i = 0; i < mpExperimentSetCopy->getExperimentCount(); i++)
    mpExperimentSet->addExperiment(*mpExperimentSetCopy->getExperiment(i));

#ifdef COPASI_CROSSVALIDATION

  if (mCrossValidation)
    {
      CCrossValidationSet * pSet = static_cast< CCrossValidationSet * >(mpExperimentSet);

      if (QString::number(pSet->getWeight()) != mpEditWeight->text())
        {
          pSet->setWeight(mpEditWeight->text().toDouble());
        }

      if (QString::number(pSet->getThreshold()) != mpEditThreshold->text())
        {
          pSet->setThreshold(mpEditThreshold->text().toUInt());
        }
    }

#endif // COPASI_CROSSVALIDATION

  pdelete(mpExperimentSetCopy);
  accept();
}

bool CQExperimentData::load(CExperimentSet * pExperimentSet, CCopasiDataModel * pDataModel)
{
  mpDataModel = pDataModel;

#ifdef COPASI_CROSSVALIDATION
  mCrossValidation = (dynamic_cast< CCrossValidationSet * >(pExperimentSet) != NULL);
#endif // COPASI_CROSSVALIDATION

  if (mCrossValidation)
    {
      setCaption("Cross Validation Data");
      mpLblWeight->show();
      mpEditWeight->show();
      mpLblThreshold->show();
      mpEditThreshold->show();
      mpLineCrossValidation->show();

#ifdef COPASI_CROSSVALIDATION
      mpEditWeight->setText(QString::number(static_cast< CCrossValidationSet * >(pExperimentSet)->getWeight()));
      mpEditThreshold->setText(QString::number(static_cast< CCrossValidationSet * >(pExperimentSet)->getThreshold()));
#endif // COPASI_CROSSVALIDATION
    }
  else
    {
      mpLblWeight->hide();
      mpEditWeight->hide();
      mpLblThreshold->hide();
      mpEditThreshold->hide();
      mpLineCrossValidation->hide();
    }

  if (!pExperimentSet) return false;

  mpExperiment = NULL;
  mShown = (unsigned int) - 1;

  mpExperimentSet = pExperimentSet;

  pdelete(mpExperimentSetCopy);

  mpExperimentSetCopy = new CExperimentSet(*pExperimentSet);

#ifdef COPASI_CROSSVALIDATION

  if (mCrossValidation)
    mpExperimentSetCopy = elevate< CCrossValidationSet, CExperimentSet >(mpExperimentSetCopy);

#endif // COPASI_CROSSVALIDATION

  pdelete(mpFileInfo);
  mpFileInfo = new CExperimentFileInfo(*mpExperimentSetCopy);

  // Build the key map so that we are able to update the correct experiments
  // on OK.
  mKeyMap.clear();
  size_t i, imax = mpExperimentSet->getExperimentCount();

  for (i = 0; i < imax; i++)
    mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()] =
      mpExperimentSetCopy->getExperiment(i)->CCopasiParameter::getKey();

  // fill file list box
  mpBoxFile->clear();

  std::vector< std::string > FileNames = mpExperimentSetCopy->getFileNames();
  std::vector< std::string >::const_iterator it = FileNames.begin();
  std::vector< std::string >::const_iterator end = FileNames.end();

  std::string FileName;
  i = 0;

  mFileMap.clear();

  for (; it != end; ++it)
    {
      FileName = CDirEntry::fileName(*it);

      while (mFileMap.find(FileName) != mFileMap.end())
        FileName = StringPrint("%s_%d", CDirEntry::fileName(*it).c_str(), i++);

      mFileMap[FileName] = *it;
      mpBoxFile->insertItem(FROM_UTF8(FileName));
    }

  if (mpBoxFile->count())
    mpBoxFile->setSelected(0, true); // This tiggers the rest of the update :)
  else
    slotFileChanged(NULL);

  return true;
}

void CQExperimentData::init()
{
  mpBtnFileAdd->setIcon(CQIcons::getIcon(CQIcons::Add));
  mpBtnFileDelete->setIcon(CQIcons::getIcon(CQIcons::Delete));
  mpBtnExperimentAdd->setIcon(CQIcons::getIcon(CQIcons::Add));
  mpBtnExperimentDelete->setIcon(CQIcons::getIcon(CQIcons::Delete));

  mCopasi = CQIcons::getIcon(CQIcons::SelectObject);

  mpComboMap = NULL;
  mpBtnMap = NULL;

  mpTable->setColumnReadOnly(COL_NAME, true);
  mpTable->hideColumn(COL_TYPE_HIDDEN);
  mpTable->setColumnWidth(COL_BTN, 20);
  mpTable->horizontalHeader()->setLabel(COL_BTN, " ");
  mpTable->setColumnStretchable(COL_OBJECT, true);
  mpTable->setColumnReadOnly(COL_OBJECT, true);
  mpTable->hideColumn(COL_OBJECT_HIDDEN);

  const std::string * pWeightMethod = CExperiment::WeightMethodName;

  while (*pWeightMethod != "")
    mpBoxWeightMethod->insertItem(FROM_UTF8(*pWeightMethod++));

  mpExperimentSetCopy = NULL;
  mpFileInfo = NULL;
  mpExperiment = NULL;

  mpValidatorName = new CQExperimentDataValidator(mpEditName, 0, this, CQExperimentDataValidator::Name);
  mpEditName->setValidator(mpValidatorName);
  mpValidatorFirst = new CQExperimentDataValidator(mpEditFirst, 0, this, CQExperimentDataValidator::FirstRow);
  mpEditFirst->setValidator(mpValidatorFirst);
  mpValidatorLast = new CQExperimentDataValidator(mpEditLast, 0, this, CQExperimentDataValidator::LastRow);
  mpEditLast->setValidator(mpValidatorLast);
  mpValidatorHeader = new CQExperimentDataValidator(mpEditHeader, 0, this, CQExperimentDataValidator::HeaderRow);
  mpEditHeader->setValidator(mpValidatorHeader);

  mShown = (unsigned int) - 1;
  mCrossValidation = false;
  mShowError = true;

  mpDataModel = NULL;
}

void CQExperimentData::destroy()
{
  pdelete(mpComboMap);
  pdelete(mpBtnMap);

  pdelete(mpExperimentSetCopy);
  pdelete(mpFileInfo);
}

bool CQExperimentData::loadExperiment(CExperiment * pExperiment)
{

  // Temporarily disconnect signals
  disconnect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));
  disconnect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  disconnect(mpBtnSteadystate, SIGNAL(toggled(bool)), this, SLOT(slotExprimentType(bool)));
  disconnect(mpEditSeparator, SIGNAL(textChanged(QString)), this, SLOT(slotSeparator()));
  disconnect(mpCheckTab, SIGNAL(toggled(bool)), this, SLOT(slotCheckTab(bool)));

  if (!pExperiment)
    {
      mpEditName->setText("");
      mpEditSeparator->setText("");
      mpCheckTab->setChecked(true);
      mpEditFirst->setText("");
      mpEditLast->setText("");
      mpEditHeader->setText("");
      mpCheckHeader->setChecked(false);
      mpBtnTimeCourse->setChecked(true);
      mpCheckFrom->setChecked(false);
      mpCheckTo->setChecked(false);
      mpBoxWeightMethod->setCurrentItem(CExperiment::SD);
    }
  else
    {
      mpEditName->setText(FROM_UTF8(pExperiment->getObjectName()));

      if (pExperiment->getSeparator() == "\t")
        {
          mpEditSeparator->setText("");
          mpCheckTab->setChecked(true);
        }
      else
        {
          mpEditSeparator->setText(FROM_UTF8(pExperiment->getSeparator()));
          mpCheckTab->setChecked(false);
        }

      QString Row = (pExperiment->getFirstRow() == InvalidIndex) ?
                    "" : QString::number(pExperiment->getFirstRow());
      mpEditFirst->setText(Row);
      Row = (pExperiment->getLastRow() == InvalidIndex) ?
            "" : QString::number(pExperiment->getLastRow());
      mpEditLast->setText(Row);

      if (pExperiment->getHeaderRow() == InvalidIndex)
        {
          mpEditHeader->setText("");
          mpCheckHeader->setChecked(false);
        }
      else
        {
          mpEditHeader->setText(QString::number(pExperiment->getHeaderRow()));
          mpCheckHeader->setChecked(true);
        }

      if (pExperiment->getExperimentType() == CCopasiTask::timeCourse)
        mpBtnTimeCourse->setChecked(true);
      else
        mpBtnSteadystate->setChecked(true);

      mOldWeightMethod = pExperiment->getWeightMethod();
      mpBoxWeightMethod->setCurrentItem(mOldWeightMethod);

      size_t Next =
        mpExperimentSetCopy->keyToIndex(pExperiment->CCopasiParameter::getKey()) + 1;

      mpCheckFrom->setChecked(isLikePreviousExperiment(pExperiment));

      if (Next < mpExperimentSetCopy->getExperimentCount())
        mpCheckTo->setChecked(isLikePreviousExperiment(mpExperimentSetCopy->getExperiment(Next)));
      else
        mpCheckTo->setChecked(false);
    }

  mpValidatorName->saved();
  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();

  loadTable(pExperiment, false);

  // Reconnect signals
  connect(mpBtnSteadystate, SIGNAL(toggled(bool)), this, SLOT(slotExprimentType(bool)));
  connect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  connect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));
  connect(mpEditSeparator, SIGNAL(textChanged(QString)), this, SLOT(slotSeparator()));
  connect(mpCheckTab, SIGNAL(toggled(bool)), this, SLOT(slotCheckTab(bool)));

  return true;
}

bool CQExperimentData::saveExperiment(CExperiment * pExperiment, const bool & full)
{
  if (!pExperiment) return false;

  bool success = true;

  size_t Next =
    mpExperimentSetCopy->keyToIndex(pExperiment->CCopasiParameter::getKey()) + 1;

  if (Next < mpExperimentSetCopy->getExperimentCount() && mpCheckTo->isChecked())
    {
      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);

      if (isLikePreviousExperiment(pNext))
        success &= saveExperiment(pNext, false);
    }

  QString value = mpEditName->text();
  int pos = value.length();

  if (full &&
      pExperiment->getObjectName() != (const char *) value &&
      mpValidatorName->validate(value, pos) == QValidator::Acceptable)
    {
      int current = mpBoxExperiment->currentItem();
      disconnect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
                 this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
      mpBoxExperiment->changeItem(value, (int) mShown);
      mpBoxExperiment->setSelected(current, true);
      connect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
              this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
      pExperiment->setObjectName((const char *) value);
    }

  if (mpCheckTab->isChecked())
    pExperiment->setSeparator("\t");
  else
    pExperiment->setSeparator(TO_UTF8(mpEditSeparator->text()));

  value = mpEditFirst->text();
  pos = value.length();

  if (full &&
      mpValidatorFirst->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setFirstRow(value.toULong());

  value = mpEditLast->text();
  pos = value.length();

  if (full &&
      mpValidatorLast->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setLastRow(value.toULong());

  value = mpEditHeader->text();
  pos = value.length();

  if (mpCheckHeader->isChecked() &&
      mpValidatorHeader->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setHeaderRow(value.toULong());
  else
    {
      pExperiment->setHeaderRow(InvalidIndex);
      mpCheckHeader->setChecked(false);
    }

  if (mpBtnTimeCourse->isChecked())
    pExperiment->setExperimentType(CCopasiTask::timeCourse);
  else
    pExperiment->setExperimentType(CCopasiTask::steadyState);

  pExperiment->setWeightMethod((CExperiment::WeightMethod) mpBoxWeightMethod->currentItem());

  mpFileInfo->sync();

  size_t First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  mpValidatorName->saved();
  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();

  saveTable(pExperiment);

  return success;
}

void CQExperimentData::syncExperiments()
{
  std::string Current = TO_UTF8(mpBoxExperiment->currentText());
  std::string Shown;

  if (mShown != C_INVALID_INDEX)
    Shown = TO_UTF8(mpBoxExperiment->item((int) mShown)->text());

  mpFileInfo->sync();

  mpBoxExperiment->clear();

  std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
  std::vector< std::string >::const_iterator it = ExperimentNames.begin();
  std::vector< std::string >::const_iterator end = ExperimentNames.end();

  size_t i;

  for (i = 0; it != end; ++it, i++)
    {
      mpBoxExperiment->insertItem(FROM_UTF8((*it)));

      if (*it == Current)
        {
          disconnect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
                     this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
          mpBoxExperiment->setSelected(mpBoxExperiment->count() - 1, true);
          connect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
                  this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
        }

      if (*it == Shown) mShown = i;
    }

  return;
}

void CQExperimentData::slotUpdateTable()
{loadTable(mpExperiment, true);}

void CQExperimentData::slotModelObject(int row)
{
  // :TODO: Implement object browser and update of column 'Model Object'.

  CQSimpleSelectionTree::ObjectClasses Classes;
  CExperiment::Type Type =
    static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(row, COL_TYPE))->currentItem());

  if (Type == CExperiment::independent)
    Classes =
      CQSimpleSelectionTree::InitialTime |
      CQSimpleSelectionTree::Parameters;
  else
    Classes =
      CQSimpleSelectionTree::Variables |
      CQSimpleSelectionTree::ObservedValues |
      CQSimpleSelectionTree::ObservedConstants;

  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject)
    {
      mpTable->setText(row, COL_OBJECT, FROM_UTF8(pObject->getObjectDisplayName()));
      mpTable->setText(row, COL_OBJECT_HIDDEN, FROM_UTF8(pObject->getCN()));
    }
}

void CQExperimentData::loadTable(CExperiment * pExperiment, const bool & guess)
{
  if (!pExperiment)
    {
      mpTable->setNumRows(0);
      mpTable->setNumRows(3);

      pdelete(mpComboMap);
      pdelete(mpBtnMap);

      return;
    }

  size_t TimeRow = C_INVALID_INDEX;

  pdelete(mpComboMap);
  mpComboMap = new QSignalMapper(this);
  connect(mpComboMap, SIGNAL(mapped(int)), this, SLOT(slotTypeChanged(int)));

  pdelete(mpBtnMap);
  mpBtnMap = new QSignalMapper(this);
  connect(mpBtnMap, SIGNAL(mapped(int)), this, SLOT(slotModelObject(int)));

  pExperiment->readColumnNames();
  const std::vector<std::string> & ColumnNames = pExperiment->getColumnNames();

  QStringList ColumnTypes;
  const std::string * pTmp = CExperiment::TypeName;

  while (*pTmp != "")
    {
      ColumnTypes.push_back(FROM_UTF8(*pTmp));
      pTmp++;
    }

  // This assumes that time is always the last type.
  if (mpBtnSteadystate->isChecked())
    ColumnTypes.pop_back();

  size_t i, imax = ColumnNames.size();
  mpTable->setNumRows((int) imax);

  CExperimentObjectMap & ObjectMap = pExperiment->getObjectMap();

  QComboBox * pComboBox;
  QToolButton* pBtn;
  const CCopasiObject * pObject;
  CExperiment::Type Type;

  for (i = 0; i < imax; i++)
    {
      // COL_NAME
      mpTable->setText((int) i, COL_NAME, FROM_UTF8(ColumnNames[i]));

      // COL_TYPE
      pComboBox = new QComboBox(mpTable);
      pComboBox->insertStringList(ColumnTypes);
      pComboBox->setEditable(false);

      if (guess && TimeRow == C_INVALID_INDEX &&
          mpBtnTimeCourse->isChecked() &&
          mpTable->text((int) i, COL_NAME).contains("time", false))
        ObjectMap.setRole(i, CExperiment::time);

      Type = ObjectMap.getRole(i);

      if (Type == CExperiment::time) TimeRow = i;

      pComboBox->setCurrentItem(Type);

      mpComboMap->setMapping(pComboBox, (int) i);
      connect(pComboBox, SIGNAL(activated(int)), mpComboMap, SLOT(map()));

      mpTable->setCellWidget((int) i, COL_TYPE, pComboBox);

      // COL_TYPE_HIDDEN
      mpTable->setText((int) i, COL_TYPE_HIDDEN, QString::number(pComboBox->currentItem()));

      // COL_BTN
      pBtn = new QToolButton(mpTable);
      pBtn->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pBtn->sizePolicy().hasHeightForWidth()));
      pBtn->setMaximumSize(QSize(20, 20));
      pBtn->setIconSet(QIcon(mCopasi));

      if (Type == CExperiment::ignore || Type == CExperiment::time)
        pBtn->setEnabled(false);

      mpBtnMap->setMapping(pBtn, (int) i);
      connect(pBtn, SIGNAL(clicked()), mpBtnMap, SLOT(map()));

      mpTable->setCellWidget((int) i, COL_BTN, pBtn);

      // COL_OBJECT and COL_OBJECT_HIDDEN
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);

      if (ObjectMap.getObjectCN(i) != "")
        {
          pObject = pDataModel->getObject(ObjectMap.getObjectCN(i));

          if (pObject)
            mpTable->setText((int) i, COL_OBJECT, FROM_UTF8(pObject->getObjectDisplayName()));
          else
            mpTable->setText((int) i, COL_OBJECT, "not found");

          mpTable->setText((int) i, COL_OBJECT_HIDDEN, FROM_UTF8(ObjectMap.getObjectCN(i)));
        }
      else
        {
          mpTable->setText((int) i, COL_OBJECT, "");
          mpTable->setText((int) i, COL_OBJECT_HIDDEN, "");
        }

      if (Type != CExperiment::dependent)
        mpTable->setText((int) i, COL_WEIGHT, "");
      else
        {
          C_FLOAT64 DefaultWeight = ObjectMap.getDefaultWeight(i);
          C_FLOAT64 Weight = ObjectMap.getWeight(i);

          QString WeightText;

          if ((isnan(DefaultWeight) &&
               isnan(Weight)) ||
              DefaultWeight == Weight)
            WeightText = "(" + QString::number(DefaultWeight) + ")";
          else
            WeightText = QString::number(Weight);

          mpTable->setText((int) i, COL_WEIGHT, WeightText);
        }
    }

  if (TimeRow != C_INVALID_INDEX)
    for (i = 0; i < imax; i++)
      if (i != TimeRow)
        static_cast<QComboBox *>(mpTable->cellWidget((int) i, COL_TYPE))->removeItem(CExperiment::time);
}

void CQExperimentData::slotTypeChanged(int row)
{
  CExperiment::Type NewType =
    static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(row, COL_TYPE))->currentItem());
  CExperiment::Type OldType =
    static_cast<CExperiment::Type>(mpTable->text(row, COL_TYPE_HIDDEN).toLong());

  if (OldType == NewType) return;

  bool BtnEnabled = true;
  C_INT32 i, imax = mpTable->numRows();

  CCopasiObjectName CN = CCopasiObjectName(TO_UTF8(mpTable->text(row, COL_OBJECT_HIDDEN)));
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  switch (NewType)
    {
      case CExperiment::ignore:
        BtnEnabled = false;
        break;

      case CExperiment::independent:

        if (!CQSimpleSelectionTree::filter(CQSimpleSelectionTree::InitialTime |
                                           CQSimpleSelectionTree::Parameters,
                                           pDataModel->getObject(CN)))
          slotModelObject(row);

        BtnEnabled = true;
        break;

      case CExperiment::dependent:

        if (!CQSimpleSelectionTree::filter(CQSimpleSelectionTree::Variables |
                                           CQSimpleSelectionTree::ObservedValues,
                                           pDataModel->getObject(CN)))
          slotModelObject(row);

        BtnEnabled = true;
        break;

      case CExperiment::time:
        BtnEnabled = false;

        // Remove Time from combo items
        for (i = 0; i < imax; i++)
          if (i != row)
            static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->removeItem(CExperiment::time);

        break;
    }

  static_cast<QToolButton *>(mpTable->cellWidget(row, COL_BTN))->setEnabled(BtnEnabled);

  switch (OldType)
    {
      case CExperiment::ignore:
      case CExperiment::independent:
      case CExperiment::dependent:
        break;

      case CExperiment::time:

        // Add time to combo items
        for (i = 0; i < imax; i++)
          if (i != row)
            static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->insertItem(FROM_UTF8(CExperiment::TypeName[CExperiment::time]));

        break;
    }

  mpTable->setText(row, COL_TYPE_HIDDEN, QString::number(NewType));

  // The default weights need to be recalculated and the table updated if the type change
  // involves dependent values.
  if (OldType == CExperiment::dependent ||
      NewType == CExperiment::dependent)
    {
      saveExperiment(mpExperiment, true);

      // Since the iterpretation of the data has changed we need read the file again
      std::ifstream File;
      File.open(CLocaleString::fromUtf8(mpExperiment->getFileName()).c_str());

      size_t CurrentLine = 1;
      mpExperiment->read(File, CurrentLine);
      mpExperiment->compile();

      // We can not simply use loadTable as this would destroy the two signal maps
      // for the buttons and comboboxes leading to crashes in Qt.
      CExperimentObjectMap & ObjectMap = mpExperiment->getObjectMap();

      for (i = 0; i < imax; i++)
        {
          // COL_WEIGHT
          if (ObjectMap.getRole(i) != CExperiment::dependent)
            mpTable->setText(i, COL_WEIGHT, "");
          else
            {
              QString WeightText = mpTable->text(i, COL_WEIGHT);

              // Keep non default values
              if (WeightText == "" || WeightText[0] == '(')
                {

                  C_FLOAT64 DefaultWeight = ObjectMap.getDefaultWeight(i);
                  WeightText = "(" + QString::number(DefaultWeight) + ")";

                  mpTable->setText(i, COL_WEIGHT, WeightText);
                }
            }
        }
    }

  return;
}

void CQExperimentData::slotSeparator()
{
  if (!mpExperiment) return;

  //  saveTable(mpExperiment);

  if (mpCheckTab->isChecked())
    mpExperiment->setSeparator("\t");
  else
    mpExperiment->setSeparator(TO_UTF8(mpEditSeparator->text()));

  mpExperiment->setNumColumns((unsigned C_INT32) mpExperiment->guessColumnNumber());
  mpExperiment->readColumnNames();

  loadTable(mpExperiment, true);
}

bool CQExperimentData::saveTable(CExperiment * pExperiment)
{
  CExperimentObjectMap & ObjectMap = pExperiment->getObjectMap();
  CExperimentObjectMap & MasterObjectMap = mpExperiment->getObjectMap();
  size_t i, imax = mpTable->numRows();
  bool FoundTime = false;
  bool Changed = false;

  ObjectMap.setNumCols(imax);

  for (i = 0; i < imax; i++)
    {
      CExperiment::Type Type =
        static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget((int) i, COL_TYPE))->currentItem());

      if (Type == CExperiment::time)
        FoundTime = true;

      if (ObjectMap.getRole(i) != Type)
        {
          ObjectMap.setRole(i, Type);
          Changed = true;
        }

      if (ObjectMap.getObjectCN(i) != TO_UTF8(mpTable->text((int) i, COL_OBJECT_HIDDEN)))
        {
          ObjectMap.setObjectCN(i, TO_UTF8(mpTable->text((int) i, COL_OBJECT_HIDDEN)));
          Changed = true;
        }

      QString WeightText = mpTable->text((int) i, COL_WEIGHT);

      // Empty fields are treated as default.
      if (WeightText == "")
        WeightText = QString::number(std::numeric_limits<C_FLOAT64>::quiet_NaN());

      if (Type == CExperiment::dependent &&
          WeightText[0] != '(' &&
          QString::number(MasterObjectMap.getWeight(i)) != WeightText)
        {
          ObjectMap.setWeight(i, WeightText.toDouble());
          Changed = true;
        }
    }

  pExperiment->updateFittedPoints();

  if (!FoundTime &&
      pExperiment->getExperimentType() == CCopasiTask::timeCourse &&
      pExperiment == mpExperiment)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 3, mpExperiment->getObjectName().c_str());

      CQMessageBox::information(this, "Specification Error", FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }

  return Changed;
}

void CQExperimentData::slotCheckFrom(bool checked)
{
  mpCheckFrom->setFocus();

  size_t Current = this->mpBoxExperiment->currentItem();

  if (checked && Current && Current != C_INVALID_INDEX)
    {
      // Load the information from the previous experiment
      CExperiment * pPrevious =
        mpFileInfo->getExperiment(TO_UTF8(mpBoxExperiment->text((int)(Current - 1))));

      unsigned C_INT32 OldWeightMethod = mOldWeightMethod;
      loadExperiment(pPrevious);
      mOldWeightMethod = OldWeightMethod;

      // Load the experiment individual information.
      mpEditName->setText(FROM_UTF8(mpExperiment->getObjectName()));
      QString Row = (mpExperiment->getFirstRow() == InvalidIndex) ?
                    "" : QString::number(mpExperiment->getFirstRow());
      mpEditFirst->setText(Row);
      Row = (mpExperiment->getLastRow() == InvalidIndex) ?
            "" : QString::number(mpExperiment->getLastRow());
      mpEditLast->setText(Row);

      mpValidatorName->saved();
      mpValidatorFirst->saved();
      mpValidatorLast->saved();
    }
  else
    {
      loadExperiment(mpExperiment);
    }

  // loadExperiment determines the status of mpCheckFrom and may have overwritten
  // the desired setting. We correct that here.
  disconnect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  mpCheckFrom->setChecked(checked);
  connect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));

  enableEdit(!checked);
}

bool CQExperimentData::isLikePreviousExperiment(CExperiment * pExperiment)
{
  if (!pExperiment) return false;

  size_t Previous =
    mpExperimentSetCopy->keyToIndex(pExperiment->CCopasiParameter::getKey()) - 1;

  if (Previous == C_INVALID_INDEX) return false;

  CExperiment * pPrevious = mpExperimentSetCopy->getExperiment(Previous);

  if (pExperiment->getSeparator() != pPrevious->getSeparator()) return false;

  if (pExperiment->getHeaderRow() != pPrevious->getHeaderRow()) return false;

  if (pExperiment->getExperimentType() != pPrevious->getExperimentType()) return false;

  if (mpExperiment != pExperiment)
    {
      if (pExperiment->getWeightMethod() != (CExperiment::WeightMethod) mOldWeightMethod) return false;
    }
  else
    {
      if ((CExperiment::WeightMethod) mOldWeightMethod != pPrevious->getWeightMethod()) return false;
    }

  if (!(pExperiment->getObjectMap() == pPrevious->getObjectMap())) return false;

  return true;
}

void CQExperimentData::slotCheckTo(bool checked)
{
  mpCheckTo->setFocus();

  if (!checked || !mpExperiment) return;

  size_t Next =
    mpExperimentSetCopy->keyToIndex(mpExperiment->CCopasiParameter::getKey()) + 1;

  if (Next < mpExperimentSetCopy->getExperimentCount())
    {
      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);
      unsigned C_INT32 OldWeightMethod = mOldWeightMethod;
      mOldWeightMethod = pNext->getWeightMethod();
      saveExperiment(mpExperimentSetCopy->getExperiment(Next), false);
      mOldWeightMethod = OldWeightMethod;
    }
}

void CQExperimentData::enableEdit(const bool & enable)
{
  if (enable)
    {
      mpBtnSteadystate->setEnabled(true);
      mpBtnTimeCourse->setEnabled(true);

      if (mpCheckHeader->isChecked()) mpEditHeader->setEnabled(true);

      mpCheckHeader->setEnabled(true);

      if (!mpCheckTab->isChecked()) mpEditSeparator->setEnabled(true);

      mpCheckTab->setEnabled(true);
      mpTable->setEnabled(true);
      mpBoxWeightMethod->setEnabled(true);

      // We need to enable all items in COL_TYPE and some in COL_BTN
      // Disable is inheritted but enable not.
      if (mpExperiment)
        {
          size_t i, imax = mpTable->numRows();

          for (i = 0; i < imax; i++)
            {
              mpTable->cellWidget((int) i, COL_TYPE)->setEnabled(true);

              CExperiment::Type Type =
                static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget((int) i, COL_TYPE))->currentItem());

              if (Type == CExperiment::ignore || Type == CExperiment::time) continue;

              mpTable->cellWidget((int) i, COL_BTN)->setEnabled(true);
            }
        }
    }
  else
    {
      mpBtnSteadystate->setEnabled(false);
      mpBtnTimeCourse->setEnabled(false);
      mpEditHeader->setEnabled(false);
      mpCheckHeader->setEnabled(false);
      mpEditSeparator->setEnabled(false);
      mpCheckTab->setEnabled(false);
      mpTable->setEnabled(false);
      mpBoxWeightMethod->setEnabled(false);
    }
}

void CQExperimentData::slotWeightMethod(int weightMethod)
{
  if (mpExperiment == NULL) return;

  if ((CExperiment::WeightMethod) weightMethod ==
      mpExperiment->getWeightMethod()) return;

  size_t Current =
    mpExperimentSetCopy->keyToIndex(mpExperiment->CCopasiParameter::getKey());
  size_t Next = Current + 1;

  // Find all experiments which are like this.
  while (Next < mpExperimentSetCopy->getExperimentCount() && mpCheckTo->isChecked())
    {
      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);

      if (!isLikePreviousExperiment(pNext)) break;

      Next++;
    }

  // Update each of them.
  while (true)
    {
      Next--;

      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);

      bool Changed = saveTable(pNext);

      if (Changed)
        {
          std::ifstream File;
          File.open(CLocaleString::fromUtf8(pNext->getFileName()).c_str());

          size_t CurrentLine = 1;
          pNext->read(File, CurrentLine);
          pNext->compile();
        }

      pNext->setWeightMethod((CExperiment::WeightMethod) weightMethod);
      pNext->calculateWeights();

      if (Next == Current) break;
    }

  loadTable(mpExperiment, false);
}
