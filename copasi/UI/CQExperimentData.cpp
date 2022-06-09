// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQExperimentData.h"

#include <QtCore/QVariant>
#include <QtCore/QTimer>

#include <algorithm>
#include <limits>
#include <cmath>
#include <QtCore/QSignalMapper>
#include <QComboBox>

#include "copasi/copasi.h"

#include "CCopasiSelectionDialog.h"
#include "CopasiFileDialog.h"
#include "CQValidator.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "copasi/resourcesUI/CQIconResource.h"
#include "CQPushButtonDelegate.h"
#include "CQComboDelegate.h"

#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/parameterFitting/CExperiment.h"
#include "copasi/parameterFitting/CExperimentFileInfo.h"
#include "copasi/parameterFitting/CExperimentObjectMap.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/model/CModel.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#define COL_NAME 0
#define COL_TYPE 1
#define COL_TYPE_HIDDEN 2
#define COL_BTN 3
#define COL_OBJECT 4
#define COL_OBJECT_HIDDEN 5
#define COL_SCALE 6

#define InvalidIndex std::numeric_limits< unsigned C_INT32 >::max()

/*
 *  Constructs a CQExperimentData as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQExperimentData::CQExperimentData(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl):
  QDialog(parent, fl),
  mOldWeightMethod(),
  mpValidatorHeader(NULL),
  mpValidatorLast(NULL),
  mpExperiment(NULL),
  mpFileInfo(NULL),
  mpExperimentSet(NULL),
  mpExperimentSetCopy(NULL),
  mKeyMap(),
  mFileMap(),
  mpValidatorFirst(),
  mShown(-1),
  mpValidatorName(NULL),
  mCrossValidation(false),
  mShowError(true),
  mpDataModel(NULL),
  mpComboDelegate(NULL),
  mTypeItems(),
  mTypeWithoutTimeItems(),
  mModelObjectRow(-1)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
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
    if (mpContext->mShown == -1) return Acceptable;

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
      mpExperiment->setExperimentType(CTaskEnum::Task::steadyState);
    }
  else
    {
      mpBtnTimeCourse->setFocus();
      mpExperiment->setExperimentType(CTaskEnum::Task::timeCourse);
    }

  saveTable(mpExperiment);

  // Undo the changes so that copy from and to work.
  if (isSteadyState)
    {
      mpExperiment->setExperimentType(CTaskEnum::Task::timeCourse);
    }
  else
    {
      mpExperiment->setExperimentType(CTaskEnum::Task::steadyState);
    }

  size_t i, imax = mpTable->rowCount();

  if (isSteadyState)
    for (i = 0; i < imax; i++)
      {
        CExperiment::Type Type = static_cast< CExperiment::Type >(mpTable->item((int) i, COL_TYPE_HIDDEN)->data(Qt::DisplayRole).toInt());

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

  pExperiment->setNormalizeWeightsPerExperiment(CRootContainer::getConfiguration()->normalizePerExperiment());

  pExperiment->setNumColumns((unsigned C_INT32) pExperiment->guessColumnNumber());
  mpFileInfo->sync();

  mpBoxExperiment->addItem(FROM_UTF8(pExperiment->getObjectName()));
  mpBoxExperiment->setCurrentRow(mpBoxExperiment->count() - 1);

  syncExperiments();
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  mShowError = true;
}

void CQExperimentData::slotExperimentChanged(QListWidgetItem * pCurrentItem, QListWidgetItem * /* pPreviousItem */)
{
  std::string Name;

  if (pCurrentItem != NULL)
    Name = TO_UTF8(pCurrentItem->text());

  CCopasiMessage::clearDeque();

  bool success = true;

  saveExperiment(mpExperiment, true);

  if (pCurrentItem != NULL)
    {
      mpExperiment = mpFileInfo->getExperiment(Name);
      mShown = mpBoxExperiment->currentRow();

      std::ifstream File;
      File.open(CLocaleString::fromUtf8(mpExperiment->getFileName()).c_str());

      size_t CurrentLine = 1;
      success &= mpExperiment->read(File, CurrentLine);

      if (success)
        success &= mpExperiment->compile(&mpDataModel->getModel()->getMathContainer());
    }
  else
    {
      mpExperiment = NULL;
      mShown =  -1;
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
  size_t index = mpBoxExperiment->currentRow();

  if (index == C_INVALID_INDEX) return;

  std::string key =
    mpFileInfo->getExperiment(TO_UTF8(mpBoxExperiment->item((int) index)->text()))->CCopasiParameter::getKey();

  // change selection
  if (mpBoxExperiment->count() > 1)
    {
      if (mpBoxExperiment->count() > (int)index + 1)
        mpBoxExperiment->setCurrentRow((int)(index + 1));
      else
        mpBoxExperiment->setCurrentRow((int)(index - 1));
    }
  else
    slotExperimentChanged(NULL, NULL);

  // remove experiment
  mpExperimentSetCopy->removeExperiment(mpExperimentSetCopy->keyToIndex(key));
  syncExperiments();

  size_t First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  // We need to correct mpCheckFrom and mpCheckTo since the removal of the experiment
  // may have changed their status.
  disconnect(mpCheckToAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckToAll(bool)));
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
  connect(mpCheckToAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckToAll(bool)));
}

void CQExperimentData::slotFileAdd()
{
  QString File =
    CopasiFileDialog::getOpenFileName(this,
                                      "Open File Dialog",
                                      "",
                                      "Data Files (*.txt *.csv *.tsv);;All Files (*)",
                                      "Open Data Files");

  if (File.isNull()) return;

  std::map<std::string, std::string>::const_iterator it = mFileMap.begin();
  std::map<std::string, std::string>::const_iterator end = mFileMap.end();
  int i;

  for (; it != end; ++it)
    if (it->second == TO_UTF8(File))
      {
        for (i = 0; i < mpBoxFile->count(); i++)
          if (it->first == TO_UTF8(mpBoxFile->item(i)->text()))
            {
              mpBoxFile->setCurrentRow(i);
              break;
            }

        return;
      }

  std::string FileName = CDirEntry::fileName(TO_UTF8(File));

  i = 0;

  while (mFileMap.find(FileName) != mFileMap.end())
    FileName = StringPrint("%s_%d", CDirEntry::fileName(TO_UTF8(File)).c_str(), i++);

  mFileMap[FileName] = TO_UTF8(File);
  mpBoxFile->addItem(FROM_UTF8(FileName));

  mpBoxFile->setCurrentRow(mpBoxFile->count() - 1);

  size_t First, Last;

  if (mpFileInfo->getFirstUnusedSection(First, Last))
    {
      do
        {
          slotExperimentAdd();
        }
      while (mpBtnExperimentAdd->isEnabled());

      mpBoxExperiment->setCurrentRow(0);
    }
}

void CQExperimentData::slotFileChanged(QListWidgetItem * pCurrentItem, QListWidgetItem * /* pPreviousItem */)
{
  if (pCurrentItem)
    {
      slotExperimentChanged(NULL, NULL); // Assure that changes are saved.
      mpBoxExperiment->clear();

      if (mpFileInfo->setFileName(mFileMap[TO_UTF8(pCurrentItem->text())]))
        {
          // fill experiment list box

          std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
          std::vector< std::string >::const_iterator it = ExperimentNames.begin();
          std::vector< std::string >::const_iterator end = ExperimentNames.end();

          for (; it != end; ++it)
            mpBoxExperiment->addItem(FROM_UTF8((*it)));
        }

      if (mpBoxExperiment->count())
        mpBoxExperiment->setCurrentRow(0);
      else
        slotExperimentChanged(NULL, NULL);
    }
  else
    {
      mpBoxExperiment->clear();
    }

  size_t First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));
}

void CQExperimentData::slotFileEdit()
{
  // Get info from current selection
  size_t index = mpBoxFile->currentRow();

  if (index == C_INVALID_INDEX) return;

  std::string oldFileName = mFileMap[TO_UTF8(mpBoxFile->item((int)index)->text())];

  QString newFile =
    CopasiFileDialog::getOpenFileName(this,
                                      "Replace File Dialog",
                                      FROM_UTF8(oldFileName),
                                      "Data Files (*.txt *.csv *.tsv);;All Files (*)",
                                      "Replace Data File");

  if (newFile.isNull()) return;

  size_t i = mpExperimentSetCopy->getExperimentCount() - 1;
  bool changedExperimentSets = false;

  for (size_t i = 0; i < mpExperimentSetCopy->getExperimentCount(); ++i)
    {
      CExperiment * experiment = mpExperimentSetCopy->getExperiment(i);

      if (experiment->getFileName() != oldFileName)
        continue;

      experiment->setFileName(TO_UTF8(newFile));
      changedExperimentSets = true;
    }

  if (!changedExperimentSets) return;

  // try and set the filename
  if (!mpFileInfo->setFileName(TO_UTF8(newFile)))
    {
      // the new file is not valid, lets assume that the file is
      // just truncated
      mpFileInfo->removeInvalidExperiments();
    }

  // in case there are additional experiments in the file add them
  // without mapping
  size_t First, Last;

  if (mpFileInfo->getFirstUnusedSection(First, Last))
    {
      do
        {
          slotExperimentAdd();
        }
      while (mpBtnExperimentAdd->isEnabled());

      mpBoxExperiment->setCurrentRow(0);
    }

  // then display the changes
  loadFromCopy();
}

void CQExperimentData::slotFileDelete()
{
  // Get info from current selection
  size_t index = mpBoxFile->currentRow();

  if (index == C_INVALID_INDEX) return;

  std::string FileName = mFileMap[TO_UTF8(mpBoxFile->item((int) index)->text())];

  // change selection
  if (mpBoxFile->count() > 1)
    {
      if (mpBoxFile->count() > (int)index + 1)
        mpBoxFile->setCurrentRow((int)(index + 1));
      else
        mpBoxFile->setCurrentRow((int)(index - 1));
    }
  else
    slotFileChanged(NULL, NULL);

  // remove file
  mFileMap.erase(TO_UTF8(mpBoxFile->item((int) index)->text()));

  QListWidgetItem * pItem = mpBoxFile->takeItem((int) index);
  pdelete(pItem);

  // delete all experiments in current file.
  size_t i = mpExperimentSetCopy->getExperimentCount() - 1;

  for (; i != C_INVALID_INDEX; i--)
    if (mpExperimentSetCopy->getExperiment(i)->getFileName() == FileName)
      mpExperimentSetCopy->removeExperiment(i);
}

void CQExperimentData::slotCancel()
{
  reject();
}

void CQExperimentData::slotOK()
{
  mpBtnOK->setFocus();

  // Force the save all current changes.
  slotExperimentChanged(NULL, NULL);

  CExperiment * pExperiment;

  size_t i = mpExperimentSet->getExperimentCount() - 1;

  for (; i != C_INVALID_INDEX; i--)
    {
      pExperiment =
        dynamic_cast<CExperiment *>(CRootContainer::getKeyFactory()->get(mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()]));

      if (pExperiment)
        {
          *mpExperimentSet->getExperiment(i) = *pExperiment;
          mpExperimentSetCopy->removeParameter(pExperiment->getObjectName());
        }
      else
        mpExperimentSet->removeExperiment(i);
    }

  emit experimentChanged();

  for (i = 0; i < mpExperimentSetCopy->getExperimentCount(); ++i)
    {
      mpExperimentSet->addExperiment(*mpExperimentSetCopy->getExperiment(i));
    }

  if (mCrossValidation)
    {
      CCrossValidationSet * pSet = static_cast< CCrossValidationSet * >(mpExperimentSet);

      if (convertToQString(pSet->getWeight()) != mpEditWeight->text())
        {
          pSet->setWeight(mpEditWeight->text().toDouble());
        }

      if (convertToQString(pSet->getThreshold()) != mpEditThreshold->text())
        {
          pSet->setThreshold(mpEditThreshold->text().toUInt());
        }
    }

  pdelete(mpExperimentSetCopy);
  accept();
}

bool CQExperimentData::load(CExperimentSet * pExperimentSet, CDataModel * pDataModel)
{
  mpDataModel = pDataModel;

  mCrossValidation = (dynamic_cast< CCrossValidationSet * >(pExperimentSet) != NULL);

  if (mCrossValidation)
    {
      setWindowTitle("Validation Data");
      mpLblWeight->show();
      mpEditWeight->show();
      mpLblThreshold->show();
      mpEditThreshold->show();
      mpLineCrossValidation->show();

      mpEditWeight->setText(convertToQString(static_cast< CCrossValidationSet * >(pExperimentSet)->getWeight()));
      mpEditThreshold->setText(convertToQString(static_cast< CCrossValidationSet * >(pExperimentSet)->getThreshold()));
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

  mpExperimentSet = pExperimentSet;

  pdelete(mpExperimentSetCopy);

  mpExperimentSetCopy = new CExperimentSet(*pExperimentSet, NO_PARENT);

  if (mCrossValidation)
    mpExperimentSetCopy = elevate< CCrossValidationSet, CExperimentSet >(mpExperimentSetCopy);

  pdelete(mpFileInfo);
  mpFileInfo = new CExperimentFileInfo(*mpExperimentSetCopy);

  // Build the key map so that we are able to update the correct experiments
  // on OK.
  mKeyMap.clear();
  size_t i, imax = mpExperimentSet->getExperimentCount();

  for (i = 0; i < imax; ++i)
    {
      mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()] =
        mpExperimentSetCopy->getExperiment(i)->CCopasiParameter::getKey();
    }

  loadFromCopy();

  return true;
}

void CQExperimentData::loadFromCopy()
{
  mpExperiment = NULL;
  mShown = -1;

  bool wasBlocked = mpBoxFile->blockSignals(true);
  // fill file list box
  mpBoxFile->clear();

  std::vector< std::string > FileNames = mpExperimentSetCopy->getFileNames();
  std::vector< std::string >::const_iterator it = FileNames.begin();
  std::vector< std::string >::const_iterator end = FileNames.end();

  std::string FileName;
  size_t i = 0;

  mFileMap.clear();

  for (; it != end; ++it)
    {
      FileName = CDirEntry::fileName(*it);

      while (mFileMap.find(FileName) != mFileMap.end())
        FileName = StringPrint("%s_%d", CDirEntry::fileName(*it).c_str(), ++i);

      mFileMap[FileName] = *it;
      mpBoxFile->addItem(FROM_UTF8(FileName));
    }

  mpBoxFile->blockSignals(wasBlocked);

  if (mpBoxFile->count())
    mpBoxFile->setCurrentRow(0); // This triggers the rest of the update :)
  else
    slotFileChanged(NULL, NULL);
}

void CQExperimentData::init()
{
  mpBtnFileAdd->setIcon(CQIconResource::icon(CQIconResource::editAdd));
  mpBtnFileDelete->setIcon(CQIconResource::icon(CQIconResource::editDelete));
  mpBtnExperimentAdd->setIcon(CQIconResource::icon(CQIconResource::editAdd));
  mpBtnExperimentDelete->setIcon(CQIconResource::icon(CQIconResource::editDelete));

  mpTable->hideColumn(COL_TYPE_HIDDEN);
  mpTable->hideColumn(COL_OBJECT_HIDDEN);

  mpComboDelegate = new CQComboDelegate(this);
  mpTable->setItemDelegateForColumn(COL_TYPE, mpComboDelegate);
  connect(mpComboDelegate, SIGNAL(currentIndexChanged(int, int)), this, SLOT(slotTypeChanged(int, int)));

  CQPushButtonDelegate * pButtonDelegate = new CQPushButtonDelegate(CQIconResource::icon(CQIconResource::copasi), QString(),
      CQPushButtonDelegate::ToolButton, this);
  mpTable->setItemDelegateForColumn(COL_BTN, pButtonDelegate);
  connect(pButtonDelegate, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotModelObject(const QModelIndex &)));

  const std::string * pWeightMethod = CExperiment::WeightMethodName;

  while (*pWeightMethod != "")
    mpBoxWeightMethod->insertItem(mpBoxWeightMethod->count(), FROM_UTF8(*pWeightMethod++));

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

  mCrossValidation = false;
  mShowError = true;

  mpDataModel = NULL;

  // Set the combo box items
  const std::string * pTmp = CExperiment::TypeName;

  while (*pTmp != "")
    {
      mTypeItems.push_back(FROM_UTF8(*pTmp));

      if (*pTmp != "Time")
        mTypeWithoutTimeItems.push_back(FROM_UTF8(*pTmp));

      pTmp++;
    }
}

void CQExperimentData::destroy()
{
  pdelete(mpExperimentSetCopy);
  pdelete(mpFileInfo);
}

void CQExperimentData::setTypeItems(const int & timeRow)
{
  int i, imax = mpTable->rowCount();

  for (i = 0; i < imax; i++)
    {
      if ((timeRow != -1 && timeRow != i) ||
          mpBtnSteadystate->isChecked())
        {
          mpComboDelegate->setItems(i, mTypeWithoutTimeItems);
        }
      else
        {
          mpComboDelegate->setItems(i, mTypeItems);
        }
    }
}

bool CQExperimentData::loadExperiment(CExperiment * pExperiment)
{

  // Temporarily disconnect signals
  mpCheckToAll->blockSignals(true);
  mpCheckTo->blockSignals(true);
  mpCheckFrom->blockSignals(true);
  mpBtnSteadystate->blockSignals(true);
  mpEditSeparator->blockSignals(true);
  mpCheckTab->blockSignals(true);
  mpCheckNormalizeWeightsPerExperiment->blockSignals(true);

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
      mpCheckNormalizeWeightsPerExperiment->setChecked(true);
      mpCheckFrom->setChecked(false);
      mpCheckTo->setChecked(false);
      mpCheckToAll->setChecked(false);
      mpBoxWeightMethod->setCurrentIndex(CExperiment::SD);
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

      if (pExperiment->getExperimentType() == CTaskEnum::Task::timeCourse)
        mpBtnTimeCourse->setChecked(true);
      else
        mpBtnSteadystate->setChecked(true);

      mOldWeightMethod = pExperiment->getWeightMethod();
      mpBoxWeightMethod->setCurrentIndex(mOldWeightMethod);

      switch ((CExperiment::WeightMethod) mOldWeightMethod)
        {
          case CExperiment::VALUE_SCALING:
            mpTable->horizontalHeaderItem(COL_SCALE)->setText("Epsilon");
            break;

          default:
            mpTable->horizontalHeaderItem(COL_SCALE)->setText("Weight");
            break;
        }

      mpCheckNormalizeWeightsPerExperiment->setChecked(pExperiment->getNormalizeWeightsPerExperiment());

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

  // Reconnect signals
  mpCheckToAll->blockSignals(false);
  mpCheckTo->blockSignals(false);
  mpCheckFrom->blockSignals(false);
  mpBtnSteadystate->blockSignals(false);
  mpEditSeparator->blockSignals(false);
  mpCheckTab->blockSignals(false);
  mpCheckNormalizeWeightsPerExperiment->blockSignals(false);

  loadTable(pExperiment, false);

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
      pExperiment->getObjectName() != TO_UTF8(value) &&
      mpValidatorName->validate(value, pos) == QValidator::Acceptable)
    {
      int current = mpBoxExperiment->currentRow();
      mpBoxExperiment->blockSignals(true);
      mpBoxExperiment->item(mShown)->setText(value);
      mpBoxExperiment->setCurrentRow(current);
      mpBoxExperiment->blockSignals(false);
      pExperiment->setObjectName(TO_UTF8(value));
    }

  if (mpCheckTab->isChecked())
    pExperiment->setSeparator("\t");
  else
    pExperiment->setSeparator(TO_UTF8_UNTRIMMED(mpEditSeparator->text()));

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
    pExperiment->setExperimentType(CTaskEnum::Task::timeCourse);
  else
    pExperiment->setExperimentType(CTaskEnum::Task::steadyState);

  pExperiment->setWeightMethod((CExperiment::WeightMethod) mpBoxWeightMethod->currentIndex());

  pExperiment->setNormalizeWeightsPerExperiment(mpCheckNormalizeWeightsPerExperiment->isChecked());

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
  std::string Current = TO_UTF8(mpBoxExperiment->currentItem()->text());
  std::string Shown;

  if (mShown != -1)
    Shown = TO_UTF8(mpBoxExperiment->item(mShown)->text());

  mpFileInfo->sync();

  mpBoxExperiment->blockSignals(true);
  mpBoxExperiment->clear();

  std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
  std::vector< std::string >::const_iterator it = ExperimentNames.begin();
  std::vector< std::string >::const_iterator end = ExperimentNames.end();

  int i;

  for (i = 0; it != end; ++it, i++)
    {
      mpBoxExperiment->addItem(FROM_UTF8((*it)));

      if (*it == Current)
        {
          mpBoxExperiment->setCurrentRow(mpBoxExperiment->count() - 1);
        }

      if (*it == Shown) mShown = i;
    }

  mpBoxExperiment->blockSignals(false);

  return;
}

void CQExperimentData::slotUpdateTable()
{loadTable(mpExperiment, true);}

void CQExperimentData::slotModelObject(const QModelIndex & index)
{
  selectModelObject(index.row());
}

void CQExperimentData::selectModelObject(const int & row)
{
  CQSimpleSelectionTree::ObjectClasses Classes;
  CExperiment::Type Type = static_cast< CExperiment::Type >(mpTable->item(row, COL_TYPE_HIDDEN)->data(Qt::DisplayRole).toInt());

  if (Type == CExperiment::independent)
    Classes =
      CQSimpleSelectionTree::InitialTime |
      CQSimpleSelectionTree::Parameters;
  else
    Classes =
      CQSimpleSelectionTree::Variables |
      CQSimpleSelectionTree::ObservedValues;

  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject)
    {
      mpTable->item(row, COL_OBJECT)->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpTable->item(row, COL_OBJECT_HIDDEN)->setText(FROM_UTF8(pObject->getCN()));
    }

  updateScales();
}

void CQExperimentData::slotModelObjectDelayed()
{
  if (mModelObjectRow != -1)
    {
      selectModelObject(mModelObjectRow);
    }

  mModelObjectRow = -1;
}

void CQExperimentData::loadTable(CExperiment * pExperiment, const bool & guess)
{
  if (!pExperiment)
    {
      mpTable->clearContents();
      mpTable->setRowCount(0);

      return;
    }

  size_t TimeRow = C_INVALID_INDEX;

  pExperiment->readColumnNames();
  const std::vector<std::string> & ColumnNames = pExperiment->getColumnNames();

  size_t OldRowCount = mpTable->rowCount();
  size_t i, imax = ColumnNames.size();
  mpTable->setRowCount((int)(imax));

  CExperimentObjectMap & ObjectMap = pExperiment->getObjectMap();
  const CDataObject *pObject;
  CExperiment::Type Type;
  QTableWidgetItem *pItem = NULL;

  for (i = 0; i < imax; i++)
    {
      // Check whether we need to allocate table items.
      if (OldRowCount <= i)
        {
          // COL_NAME
          pItem = new QTableWidgetItem();
          pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
          mpTable->setItem((int) i, COL_NAME, pItem);

          // COL_TYPE
          pItem = new QTableWidgetItem();
          mpTable->setItem((int) i, COL_TYPE, pItem);

          // COL_TYPE_HIDDEN
          pItem = new QTableWidgetItem();
          pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
          mpTable->setItem((int) i, COL_TYPE_HIDDEN, pItem);

          // COL_BTN
          pItem = new QTableWidgetItem();
          mpTable->setItem(i, COL_BTN, pItem);

          // COL_OBJECT
          pItem = new QTableWidgetItem();
          pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
          mpTable->setItem((int) i, COL_OBJECT, pItem);

          // COL_OBJECT_HIDDEN
          pItem = new QTableWidgetItem();
          pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
          mpTable->setItem((int) i, COL_OBJECT_HIDDEN, pItem);

          // COL_SCALE
          pItem = new QTableWidgetItem("");
          mpTable->setItem((int) i, COL_SCALE, pItem);
        }

      // COL_NAME
      mpTable->item((int) i, COL_NAME)->setText(FROM_UTF8(ColumnNames[i]));

      // COL_TYPE
      if (guess && TimeRow == C_INVALID_INDEX &&
          mpBtnTimeCourse->isChecked() &&
          mpTable->item((int) i, COL_NAME)->text().contains("time", Qt::CaseInsensitive))
        {
          ObjectMap.setRole(i, CExperiment::time);
        }

      Type = ObjectMap.getRole(i);

      if (Type == CExperiment::time) TimeRow = i;

      mpTable->item((int) i, COL_TYPE)->setText(FROM_UTF8(CExperiment::TypeName[Type]));

      // COL_TYPE_HIDDEN
      mpTable->item((int) i, COL_TYPE_HIDDEN)->setText(QString::number(Type));

      // COL_BTN
      pItem = mpTable->item(i, COL_BTN);

      // Show the Button
      if (Type == CExperiment::ignore || Type == CExperiment::time)
        {
          pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled);
          mpTable->closePersistentEditor(pItem);
        }
      else
        {
          pItem->setFlags(pItem->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled);
          mpTable->openPersistentEditor(pItem);
        }

      // COL_OBJECT and COL_OBJECT_HIDDEN
      QTableWidgetItem * pItem;

      if (ObjectMap.getObjectCN(i) != "")
        {
          assert(mpDataModel != NULL);
          pObject = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(ObjectMap.getObjectCN(i)));

          if (pObject)
            {
              mpTable->item((int)i, COL_OBJECT)->setText(FROM_UTF8(pObject->getObjectDisplayName()));
              mpTable->item((int)i, COL_OBJECT_HIDDEN)->setText(FROM_UTF8(ObjectMap.getObjectCN(i)));
            }
          else
            {
              mpTable->item((int)i, COL_OBJECT)->setText("");
              mpTable->item((int)i, COL_OBJECT_HIDDEN)->setText("");
            }
        }
      else
        {
          mpTable->item((int) i, COL_OBJECT)->setText("");
          mpTable->item((int) i, COL_OBJECT_HIDDEN)->setText("");
        }

      // COL_SCALE
      pItem = mpTable->item((int) i, COL_SCALE);

      if (Type != CExperiment::dependent)
        {
          pItem->setText("");
          pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
        }
      else
        {
          C_FLOAT64 DefaultScale = ObjectMap.getDefaultScale(i);
          C_FLOAT64 Scale = ObjectMap.getScale(i);

          QString ScaleText;
          Qt::ItemFlags FlagMask = Qt::NoItemFlags;

          if ((std::isnan(DefaultScale) && std::isnan(Scale)) ||
              DefaultScale == Scale)
            ScaleText = "(" + convertToQString(DefaultScale) + ")";
          else
            ScaleText = convertToQString(Scale);

          pItem->setText(ScaleText);
          pItem->setFlags(pItem->flags() & ~FlagMask);

          // ensure item is editable
          pItem->setFlags(pItem->flags() | Qt::ItemIsEditable);

        }
    }

  setTypeItems(TimeRow);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTable->resizeColumnsToContents();
      mpTable->resizeRowsToContents();
    }
}

void CQExperimentData::slotTypeChanged(int row, int index)
{
  CExperiment::Type NewType = static_cast<CExperiment::Type>(index);
  CExperiment::Type OldType = static_cast<CExperiment::Type>(mpTable->item(row, COL_TYPE_HIDDEN)->data(Qt::DisplayRole).toInt());

  if (OldType == NewType) return;

  bool BtnEnabled = true;
  //C_INT32 i, imax = mpTable->rowCount();

  mpTable->item(row, COL_TYPE)->setText(QString(FROM_UTF8(CExperiment::TypeName[NewType])));
  mpTable->item(row, COL_TYPE_HIDDEN)->setText(QString::number(NewType));

  CCommonName CN = CCommonName(TO_UTF8(mpTable->item(row, COL_OBJECT_HIDDEN)->text()));

  switch (NewType)
    {
      case CExperiment::ignore:
        BtnEnabled = false;
        break;

      case CExperiment::independent:
        assert(mpDataModel != NULL);

        if (!CQSimpleSelectionTree::filter(CQSimpleSelectionTree::InitialTime |
                                           CQSimpleSelectionTree::Parameters,
                                           CObjectInterface::DataObject(mpDataModel->getObjectFromCN(CN))))
          {
            mModelObjectRow = row;
            // slotModelObject(row);
            QTimer::singleShot(10, this, SLOT(slotModelObjectDelayed()));
          }

        BtnEnabled = true;
        break;

      case CExperiment::dependent:

        if (!CQSimpleSelectionTree::filter(CQSimpleSelectionTree::Variables |
                                           CQSimpleSelectionTree::ObservedValues,
                                           CObjectInterface::DataObject(mpDataModel->getObjectFromCN(CN))))
          {
            mModelObjectRow = row;
            // slotModelObject(row);
            QTimer::singleShot(10, this, SLOT(slotModelObjectDelayed()));
          }

        BtnEnabled = true;
        break;

      case CExperiment::time:
        BtnEnabled = false;
        setTypeItems(row);

        break;
    }

  QTableWidgetItem * pItem = mpTable->item(row, COL_BTN);

  if (BtnEnabled)
    {
      pItem->setFlags(pItem->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled);
      mpTable->openPersistentEditor(pItem);
    }
  else
    {
      pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled);
      mpTable->closePersistentEditor(pItem);
    }

  switch (OldType)
    {
      case CExperiment::ignore:
      case CExperiment::independent:
      case CExperiment::dependent:
        break;

      case CExperiment::time:
        setTypeItems(-1);
        break;
    }

  // The default weights need to be recalculated and the table updated if the type change
  // involves dependent values.
  if (OldType == CExperiment::dependent ||
      NewType == CExperiment::dependent)
    {
      updateScales();
    }

  return;
}

void CQExperimentData::updateScales()
{
  saveExperiment(mpExperiment, true);

  // Since the interpretation of the data has changed we need read the file again
  std::ifstream File;
  File.open(CLocaleString::fromUtf8(mpExperiment->getFileName()).c_str());

  size_t CurrentLine = 1;
  mpExperiment->read(File, CurrentLine);
  mpExperiment->compile(&mpDataModel->getModel()->getMathContainer());

  // We can not simply use loadTable as this would destroy the two signal maps
  // for the buttons and comboboxes leading to crashes in Qt.
  CExperimentObjectMap & ObjectMap = mpExperiment->getObjectMap();

  C_INT32 i, imax = mpTable->rowCount();

  for (i = 0; i < imax; i++)
    {
      QTableWidgetItem * pItem = mpTable->item(i, COL_SCALE);

      // COL_SCALE
      if (ObjectMap.getRole(i) != CExperiment::dependent)
        {
          pItem->setText("");
          pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
        }
      else
        {
          QString ScaleText = pItem->text();

          // Keep non default values
          if (ScaleText == "" || ScaleText[0] == '(')
            {

              C_FLOAT64 DefaultWeight = ObjectMap.getDefaultScale(i);

              ScaleText = "(" + convertToQString(DefaultWeight) + ")";
              pItem->setText(ScaleText);
            }

          pItem->setFlags(pItem->flags() | Qt::ItemIsEditable);
        }
    }
}

void CQExperimentData::slotSeparator()
{
  if (!mpExperiment) return;

  //  saveTable(mpExperiment);

  if (mpCheckTab->isChecked())
    mpExperiment->setSeparator("\t");
  else
    mpExperiment->setSeparator(TO_UTF8_UNTRIMMED(mpEditSeparator->text()));

  mpExperiment->setNumColumns((unsigned C_INT32) mpExperiment->guessColumnNumber());
  mpExperiment->readColumnNames();

  loadTable(mpExperiment, true);
}

bool CQExperimentData::saveTable(CExperiment * pExperiment)
{
  CExperimentObjectMap & ObjectMap = pExperiment->getObjectMap();
  size_t i, imax = mpTable->rowCount();
  bool FoundTime = false;
  bool Changed = false;

  ObjectMap.setNumCols(imax);

  for (i = 0; i < imax; i++)
    {
      CExperiment::Type Type = toEnum(TO_UTF8(mpTable->item((int) i, COL_TYPE)->text()),
                                      CExperiment::TypeName, CExperiment::ignore);

      if (Type == CExperiment::time)
        FoundTime = true;

      if (ObjectMap.getRole(i) != Type)
        {
          ObjectMap.setRole(i, Type);
          Changed = true;
        }

      if (ObjectMap.getObjectCN(i) != TO_UTF8(mpTable->item((int) i, COL_OBJECT_HIDDEN)->text()))
        {
          ObjectMap.setObjectCN(i, TO_UTF8(mpTable->item((int) i, COL_OBJECT_HIDDEN)->text()));
          Changed = true;
        }

      QString ScaleText = mpTable->item((int) i, COL_SCALE)->text();

      // Empty fields are treated as default.
      if (ScaleText == "")
        ScaleText = convertToQString(std::numeric_limits<C_FLOAT64>::quiet_NaN());

      if (Type == CExperiment::dependent &&
          ScaleText[0] != '(' &&
          convertToQString(ObjectMap.getScale(i)) != ScaleText)
        {
          ObjectMap.setScale(i, ScaleText.toDouble());
          Changed = true;
        }
    }

  pExperiment->updateFittedPoints();

  return Changed;
}

void CQExperimentData::slotCheckFrom(bool checked)
{
  mpCheckFrom->setFocus();

  size_t Current = this->mpBoxExperiment->currentRow();

  if (checked && Current && Current != C_INVALID_INDEX)
    {
      // Load the information from the previous experiment
      CExperiment * pPrevious =
        mpFileInfo->getExperiment(TO_UTF8(mpBoxExperiment->item((int)(Current - 1))->text()));

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
  else if (checked && Current != C_INVALID_INDEX && mpExperimentSetCopy->getExperimentCount() > 0)
    {
      if (mpBoxFile->currentRow() > 0)
        {
          std::string prevFile = mFileMap[TO_UTF8(mpBoxFile->item(mpBoxFile->currentRow() - 1)->text())];
          std::string currentFile = mFileMap[TO_UTF8(mpBoxFile->currentItem()->text())];

          CExperiment* pLast = NULL;

          for (int i = (int)mpExperimentSetCopy->getExperimentCount() - 1; i >= 0; --i)
            {
              pLast = mpExperimentSetCopy->getExperiment(i);

              if (pLast->getFileName() == prevFile)
                break;

              pLast = NULL;
            }

          if (pLast != NULL)
            {
              unsigned C_INT32 OldWeightMethod = mOldWeightMethod;
              loadExperiment(pLast);
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
        }
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

      if (pExperiment->getNormalizeWeightsPerExperiment() != pPrevious->getNormalizeWeightsPerExperiment()) return false;
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

void CQExperimentData::slotCheckToAll(bool checked)
{
  mpCheckToAll->setFocus();

  if (!checked || !mpExperiment) return;

  size_t Next =
    mpExperimentSetCopy->keyToIndex(mpExperiment->CCopasiParameter::getKey()) + 1;

  while (Next < mpExperimentSetCopy->getExperimentCount())
    {
      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);
      unsigned C_INT32 OldWeightMethod = mOldWeightMethod;
      mOldWeightMethod = pNext->getWeightMethod();
      saveExperiment(mpExperimentSetCopy->getExperiment(Next), false);
      mOldWeightMethod = OldWeightMethod;
      Next++;
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

      mpCheckNormalizeWeightsPerExperiment->setEnabled(true);

      // We need to enable all items in COL_TYPE and some in COL_BTN
      // Disable is inheritted but enable not.
      /*
      if (mpExperiment)
        {
          size_t i, imax = mpTable->rowCount();

          for (i = 0; i < imax; i++)
            {
              CExperiment::Type Type = static_cast< CExperiment::Type >(mpTable->item((int) i, COL_TYPE_HIDDEN)->data(Qt::DisplayRole).toInt());

              QTableWidgetItem * pItem = mpTable->item((int) i, COL_BTN);

              if (Type == CExperiment::ignore || Type == CExperiment::time)
                {
                  pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled);
                  mpTable->closePersistentEditor(pItem);
                }
              else
                {
                  pItem->setFlags(pItem->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled);
                  mpTable->openPersistentEditor(pItem);
                }
            }
        }
        */
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
      mpCheckNormalizeWeightsPerExperiment->setEnabled(false);
    }
}

void CQExperimentData::slotCheckNormalizeWeightsPerExperiment(bool flag)
{
  if (!mpExperiment) return;

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
          pNext->compile(&mpDataModel->getModel()->getMathContainer());
        }

      pNext->setNormalizeWeightsPerExperiment(flag);
      pNext->calculateWeights();

      if (Next == Current) break;
    }

  loadTable(mpExperiment, false);
}

void CQExperimentData::slotWeightMethod(int weightMethod)
{
  if (mpExperiment == NULL) return;

  if ((CExperiment::WeightMethod) weightMethod ==
      mpExperiment->getWeightMethod()) return;

  switch ((CExperiment::WeightMethod) weightMethod)
    {
      case CExperiment::VALUE_SCALING:
        mpTable->horizontalHeaderItem(COL_SCALE)->setText("Epsilon");
        break;

      default:
        mpTable->horizontalHeaderItem(COL_SCALE)->setText("Weight");
        break;
    }

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
          pNext->compile(&mpDataModel->getModel()->getMathContainer());
        }

      pNext->setWeightMethod((CExperiment::WeightMethod) weightMethod);
      pNext->calculateWeights();

      if (Next == Current) break;
    }

  loadTable(mpExperiment, false);
}
