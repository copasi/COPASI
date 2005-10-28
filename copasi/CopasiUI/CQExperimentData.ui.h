/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQExperimentData.ui.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/28 16:12:27 $
   End CVS Header */

#include <algorithm>

#include "copasi.h"

#include "CopasiFileDialog.h"
#include "CQValidator.h"
#include "qtUtilities.h"

#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentFileInfo.h"

#include "utilities/CDirEntry.h"
#include "utilities/utility.h"

class CQExperimentDataValidator: public CQValidator
  {
  public:
    enum Type
    {
      FirstRow = 0,
      LastRow,
      HeaderRow
    };

    // Operations
  public:
    CQExperimentDataValidator(QLineEdit * parent,
                              const char * name,
                              CQExperimentData * pContext,
                              const Type & type):
        CQValidator(parent, name),
        mpIntValidator(new QIntValidator(1, LONG_MAX, this)),
        mpContext(pContext),
        mType(type)
    {}

    virtual State validate(QString & input, int & pos) const
      {
        if (mpContext->mShown == C_INVALID_INDEX) return Acceptable;

        if (mpIntValidator->validate(input, pos) != Acceptable)
          {
            setColor(Invalid);
            return Intermediate;
          }

        switch (mType)
          {
          case FirstRow:
            if (!mpContext->mpFileInfo->validateFirst(mpContext->mShown, input.toULong()))
              {
                setColor(Invalid);
                return Intermediate;
              }

            mpContext->mpExperiment->setFirstRow(input.toULong());
            break;

          case LastRow:
            if (!mpContext->mpFileInfo->validateLast(mpContext->mShown, input.toULong()))
              {
                setColor(Invalid);
                return Intermediate;
              }

            mpContext->mpExperiment->setLastRow(input.toULong());
            break;

          case HeaderRow:
            if (!mpContext->mpFileInfo->validateHeader(mpContext->mShown, input.toULong()))
              {
                setColor(Invalid);
                return Intermediate;
              }

            mpContext->mpExperiment->setHeaderRow(input.toULong());
            break;
          }

        CQValidator::validate(input, pos);
        mpContext->syncExperiments();

        unsigned C_INT32 First, Last;
        mpContext->mpBtnExperimentAdd->setEnabled(mpContext->mpFileInfo->getFirstUnusedSection(First, Last));

        return Acceptable;
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
  load(mpExperimentSet);
}

void CQExperimentData::slotFirst()
{
  qWarning("CQExperimentData::slotFirst(): Not implemented yet");

  unsigned C_INT32 Row = C_INVALID_INDEX;

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
  qWarning("CQExperimentData::slotLast(): Not implemented yet");

  unsigned C_INT32 Row = C_INVALID_INDEX;

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

void CQExperimentData::slotExprimentType(bool)
{
  qWarning("CQExperimentData::slotExprimentType(bool): Not implemented yet");
}

void CQExperimentData::slotCheckTab(bool checked)
{mpEditSeparator->setEnabled(!checked);}

void CQExperimentData::slotCheckHeader(bool checked)
{mpEditHeader->setEnabled(checked);}

void CQExperimentData::slotExperimentAdd()
{
  CExperiment Experiment;
  CExperiment * pExperiment = mpExperimentSetCopy->addExperiment(Experiment);

  unsigned C_INT32 First, Last;
  mpFileInfo->getFirstUnusedSection(First, Last);
  pExperiment->setFirstRow(First);
  pExperiment->setLastRow(Last);
  pExperiment->setFileName(mpFileInfo->getFileName());

  mpFileInfo->sync();

  mpBoxExperiment->insertItem(FROM_UTF8(pExperiment->getObjectName()));
  mpBoxExperiment->setSelected(mpBoxExperiment->count() - 1, true);

  syncExperiments();
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));
}

void CQExperimentData::slotExperimentChanged(QListBoxItem * pItem)
{
  std::string Name;
  if (pItem)
    Name = (const char *) pItem->text().utf8();

  saveExperiment(mpExperiment);

  if (pItem)
    {
      mpExperiment = mpFileInfo->getExperiment(Name);
      mShown = mpBoxExperiment->currentItem();
    }
  else
    {
      mpExperiment = NULL;
      mShown = C_INVALID_INDEX;
    }

  loadExperiment(mpExperiment);
}

void CQExperimentData::slotExperimentDelete()
{
  // Get info from current selection
  unsigned C_INT32 index = mpBoxExperiment->currentItem();
  if (index == C_INVALID_INDEX) return;

  std::string key =
    mpFileInfo->getExperiment((const char *) mpBoxExperiment->item(index)->text().utf8())->CCopasiParameter::getKey();

  // change selection
  if (mpBoxExperiment->count() > 1)
    {
      if (mpBoxExperiment->count() > index + 1)
        mpBoxExperiment->setSelected(index + 1, true);
      else
        mpBoxExperiment->setSelected(index - 1, true);
    }
  else
    slotExperimentChanged(NULL);

  // remove experiment
  mpExperimentSetCopy->removeExperiment(mpExperimentSetCopy->keyToIndex(key));
  syncExperiments();

  unsigned C_INT32 First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));
}

void CQExperimentData::slotFileAdd()
{
  QString File =
    CopasiFileDialog::getOpenFileName(this,
                                      "Open File Dialog",
                                      "",
                                      "Data Files (*.txt *.csv);;All Files (*.*);;",
                                      "Open Data Files");

  if (!File) return;

  std::map<std::string, std::string>::const_iterator it = mFileMap.begin();
  std::map<std::string, std::string>::const_iterator end = mFileMap.end();
  unsigned C_INT32 i;

  for (i = 0; it != end; ++it, i++)
    if (it->second == (const char *) File.utf8())
      {
        mpBoxFile->setSelected(i, true);
        return;
      }

  std::string baseName = CDirEntry::baseName((const char *) File.utf8());

  i = 0;
  while (mFileMap.find(baseName) != mFileMap.end())
    baseName = StringPrint("%s_%d", CDirEntry::baseName((const char *) File.utf8()).c_str(), i++);

  mFileMap[baseName] = (const char *) File.utf8();
  mpBoxFile->insertItem(FROM_UTF8(baseName));

  mpBoxFile->setSelected(mpBoxFile->count() - 1, true);
}

void CQExperimentData::slotFileChanged(QListBoxItem * pItem)
{
  if (pItem)
    {
      slotExperimentChanged(NULL); // Assure that changes are saved.
      mpFileInfo->setFileName(mFileMap[(const char *) pItem->text().utf8()]);

      // fill experiment list box
      mpBoxExperiment->clear();

      std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
      std::vector< std::string >::const_iterator it = ExperimentNames.begin();
      std::vector< std::string >::const_iterator end = ExperimentNames.end();

      for (; it != end; ++it)
        mpBoxExperiment->insertItem(FROM_UTF8((*it)));

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

  unsigned C_INT32 First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));
}

void CQExperimentData::slotFileDelete()
{
  // Get info from current selection
  unsigned C_INT32 index = mpBoxFile->currentItem();
  if (index == C_INVALID_INDEX) return;

  std::string FileName = mFileMap[(const char *) mpBoxFile->item(index)->text().utf8()];

  // change selection
  if (mpBoxFile->count() > 1)
    {
      if (mpBoxFile->count() > index + 1)
        mpBoxFile->setSelected(index + 1, true);
      else
        mpBoxFile->setSelected(index - 1, true);
    }
  else
    slotFileChanged(NULL);

  // remove file
  mFileMap.erase((const char *) mpBoxFile->item(index)->text().utf8());
  mpBoxFile->removeItem(index);

  // delete all experiments in current file.
  unsigned C_INT32 i = mpExperimentSetCopy->size() - 1;
  for (; i < C_INVALID_INDEX; i--)
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
  slotExperimentChanged(NULL);

  // :TODO: reflect changes in the dialog in the data.
  // i.e., copy information from mpExperimentSetCopy to mpExperimentSet

  pdelete(mpExperimentSetCopy);
  accept();
}

bool CQExperimentData::load(CExperimentSet * pExperimentSet)
{
  if (!pExperimentSet) return false;

  mpExperiment = NULL;
  mShown = C_INVALID_INDEX;

  mpExperimentSet = pExperimentSet;

  pdelete(mpExperimentSetCopy);
  mpExperimentSetCopy = new CExperimentSet(*pExperimentSet);

  pdelete(mpFileInfo);
  mpFileInfo = new CExperimentFileInfo(*mpExperimentSetCopy);

  // Build the key map so that we are able to update the correct experiments
  // on OK.
  mKeyMap.clear();
  unsigned C_INT32 i, imax = mpExperimentSet->size();

  for (i = 0; i < imax; i++)
    mKeyMap[mpExperimentSetCopy->getExperiment(i)->CCopasiParameter::getKey()] =
      mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey();

  // :TODO: Display the data in the dialog.

  // fill file list box
  mpBoxFile->clear();

  std::vector< std::string > FileNames = mpExperimentSetCopy->getFileNames();
  std::vector< std::string >::const_iterator it = FileNames.begin();
  std::vector< std::string >::const_iterator end = FileNames.end();

  std::string baseName;
  i = 0;

  mFileMap.clear();
  for (; it != end; ++it)
    {
      baseName = CDirEntry::baseName(*it);

      while (mFileMap.find(baseName) != mFileMap.end())
        baseName = StringPrint("%s_%d", CDirEntry::baseName(*it).c_str(), i++);

      mFileMap[baseName] = *it;
      mpBoxFile->insertItem(FROM_UTF8(baseName));
    }

  if (mpBoxFile->count())
    mpBoxFile->setSelected(0, true);
  else
    slotFileChanged(NULL);

  return true;
}

void CQExperimentData::init()
{
  mpExperimentSetCopy = NULL;
  mpFileInfo = NULL;
  mpExperiment = NULL;

  mpValidatorFirst = new CQExperimentDataValidator(mpEditFirst, 0, this, CQExperimentDataValidator::FirstRow);
  mpEditFirst->setValidator(mpValidatorFirst);
  mpValidatorLast = new CQExperimentDataValidator(mpEditLast, 0, this, CQExperimentDataValidator::LastRow);
  mpEditLast->setValidator(mpValidatorLast);
  mpValidatorHeader = new CQExperimentDataValidator(mpEditHeader, 0, this, CQExperimentDataValidator::HeaderRow);
  mpEditHeader->setValidator(mpValidatorHeader);

  mShown = C_INVALID_INDEX;
}

void CQExperimentData::destroy()
{
  pdelete(mpExperimentSetCopy);
  pdelete(mpFileInfo);
}

bool CQExperimentData::loadExperiment(const CExperiment * pExperiment)
{
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

      QString Row = (pExperiment->getFirstRow() == C_INVALID_INDEX) ?
                    "" : QString::number(pExperiment->getFirstRow());
      mpEditFirst->setText(Row);
      Row = (pExperiment->getLastRow() == C_INVALID_INDEX) ?
            "" : QString::number(pExperiment->getLastRow());
      mpEditLast->setText(Row);

      if (pExperiment->getHeaderRow() == C_INVALID_INDEX)
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
    }

  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();
  return true;
}

bool CQExperimentData::saveExperiment(CExperiment * pExperiment)
{
  if (!pExperiment) return false;

  if (pExperiment->getObjectName() != (const char *) mpEditName->text() &&
      !mpExperimentSetCopy->getExperiment((const char *) mpEditName->text()))
    pExperiment->setObjectName((const char *) mpEditName->text());

  if (mpCheckTab->isChecked())
    pExperiment->setSeparator("\t");
  else
    pExperiment->setSeparator((const char *) mpEditSeparator->text().utf8());

  QString value = mpEditFirst->text();
  int pos = value.length();
  if (mpValidatorFirst->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setFirstRow(value.toULong());

  value = mpEditLast->text();
  pos = value.length();
  if (mpValidatorLast->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setLastRow(value.toULong());

  value = mpEditHeader->text();
  pos = value.length();
  if (mpCheckHeader->isChecked() &&
      mpValidatorHeader->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setHeaderRow(value.toULong());
  else
    {
      pExperiment->setHeaderRow(C_INVALID_INDEX);
      mpCheckHeader->setChecked(false);
    }

  if (mpBtnTimeCourse->isChecked())
    pExperiment->setExperimentType(CCopasiTask::timeCourse);
  else
    pExperiment->setExperimentType(CCopasiTask::steadyState);

  mpFileInfo->sync();

  unsigned C_INT32 First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();
  return true;
}

void CQExperimentData::syncExperiments()
{
  std::string Current = (const char *) mpBoxExperiment->currentText().utf8();
  std::string Shown;
  if (mShown != C_INVALID_INDEX)
    Shown = (const char *) mpBoxExperiment->item(mShown)->text().utf8();

  mpFileInfo->sync();

  mpBoxExperiment->clear();

  std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
  std::vector< std::string >::const_iterator it = ExperimentNames.begin();
  std::vector< std::string >::const_iterator end = ExperimentNames.end();

  unsigned C_INT32 i;
  for (i = 0; it != end; ++it, i++)
    {
      mpBoxExperiment->insertItem(FROM_UTF8((*it)));
      if (*it == Current)
        {
          disconnect(mpBoxExperiment, SIGNAL(currentChanged(QListBoxItem*)),
                     this, SLOT(slotExperimentChanged(QListBoxItem*)));
          mpBoxExperiment->setSelected(mpBoxExperiment->count() - 1, true);
          connect(mpBoxExperiment, SIGNAL(currentChanged(QListBoxItem*)),
                  this, SLOT(slotExperimentChanged(QListBoxItem*)));
        }
      if (*it == Shown) mShown = i;
    }

  return;
}
