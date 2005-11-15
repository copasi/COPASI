/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQExperimentData.ui.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/15 23:15:44 $
   End CVS Header */

#include <algorithm>

#include <qsignalmapper.h>
#include <qcombobox.h>

#include "copasi.h"

#include "CCopasiSelectionDialog.h"
#include "CopasiFileDialog.h"
#include "CQValidator.h"
#include "qtUtilities.h"

#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentFileInfo.h"
#include "parameterFitting/CExperimentObjectMap.h"

#include "report/CKeyFactory.h"
#include "utilities/CDirEntry.h"
#include "utilities/utility.h"

#define COL_NAME 0
#define COL_TYPE 1
#define COL_TYPE_HIDDEN 2
#define COL_BTN 3
#define COL_OBJECT 4
#define COL_OBJECT_HIDDEN 5

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
        mpIntValidator(new QIntValidator(1, LONG_MAX, parent)),
        mpContext(pContext),
        mType(type)
    {}

    virtual State validate(QString & input, int & pos) const
      {
        if (mpContext->mShown == C_INVALID_INDEX) return Acceptable;

        if (mType == Name)
          {
            if (input == "All")
              {
                setColor(Invalid);
                return Intermediate;
              }
            if (mpContext->mpExperimentSetCopy->getParameter((const char *) input.utf8()))
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

            unsigned C_INT32 First, Last;

            switch (mType)
              {
              case FirstRow:
                if (!mpContext->mpFileInfo->validateFirst(mpContext->mShown, input.toULong()))
                  {
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

void CQExperimentData::slotExprimentType(bool isSteadyState)
{
  if (!mpExperiment) return;

  saveTable();

  unsigned C_INT32 i, imax = mpTable->numRows();
  if (isSteadyState)
    for (i = 0; i < imax; i++)
      {
        CExperiment::Type Type =
          static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->currentItem());

        if (Type == CExperiment::time)
          mpExperiment->removeColumnType(i);
      };

  loadTable(true);
  return;
}

void CQExperimentData::slotCheckTab(bool checked)
{
  mpEditSeparator->setEnabled(!checked);

  if (mpEditSeparator->isEnabled() &&
      mpEditSeparator->text().isEmpty())
    mpEditSeparator->setText(",");
  else
    slotSeparator();
}

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
  pExperiment->setHeaderRow(First);
  pExperiment->setFileName(mpFileInfo->getFileName());

  pExperiment->setNumColumns(pExperiment->guessColumnNumber());
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
  mpExperimentSetCopy->removeParameter(mpExperimentSetCopy->keyToIndex(key));
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

  for (; it != end; ++it)
    if (it->second == (const char *) File.utf8())
      {
        for (i = 0; i < mpBoxFile->count(); i++)
          if (it->first == (const char *) mpBoxFile->item(i)->text().utf8())
            {
              mpBoxFile->setSelected(i, true);
              break;
            }
        return;
      }

  std::string baseName = CDirEntry::baseName((const char *) File.utf8());

  i = 0;
  while (mFileMap.find(baseName) != mFileMap.end())
    baseName = StringPrint("%s_%d", CDirEntry::baseName((const char *) File.utf8()).c_str(), i++);

  mFileMap[baseName] = (const char *) File.utf8();
  mpBoxFile->insertItem(FROM_UTF8(baseName));

  mpBoxFile->setSelected(mpBoxFile->count() - 1, true);

  unsigned C_INT32 First, Last;
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
      mpExperimentSetCopy->removeParameter(i);
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
  unsigned C_INT32 i = mpExperimentSet->size() - 1;
  for (; i < C_INVALID_INDEX; i--)
    {
      pExperiment =
        dynamic_cast<CExperiment *>(GlobalKeys.get(mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()]));
      if (pExperiment)
        {
          *mpExperimentSet->getExperiment(i) = *pExperiment;
          mpExperimentSetCopy->removeParameter(pExperiment->getObjectName());
        }
      else
        mpExperimentSet->removeParameter(i);
    }

  for (i = 0; i < mpExperimentSetCopy->size(); i++)
    mpExperimentSet->addExperiment(*mpExperimentSetCopy->getExperiment(i));

  pdelete(mpExperimentSetCopy);
  accept();
}

bool CQExperimentData::load(CExperimentSet *& pExperimentSet)
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
    mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()] =
      mpExperimentSetCopy->getExperiment(i)->CCopasiParameter::getKey();

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
    mpBoxFile->setSelected(0, true); // This tiggers the rest of the update :)
  else
    slotFileChanged(NULL);

  return true;
}

void CQExperimentData::init()
{
  mpComboMap = NULL;
  mpBtnMap = NULL;

  mpTable->setColumnReadOnly(COL_NAME, true);
  mpTable->hideColumn(COL_TYPE_HIDDEN);
  mpTable->setColumnWidth(COL_BTN, 20);
  mpTable->horizontalHeader()->setLabel(COL_BTN, " ");
  mpTable->setColumnStretchable(COL_OBJECT, true);
  mpTable->setColumnReadOnly(COL_OBJECT, true);
  mpTable->hideColumn(COL_OBJECT_HIDDEN);

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

  mShown = C_INVALID_INDEX;
}

void CQExperimentData::destroy()
{
  pdelete(mpComboMap);
  pdelete(mpBtnMap);

  pdelete(mpExperimentSetCopy);
  pdelete(mpFileInfo);
}

bool CQExperimentData::loadExperiment(const CExperiment * pExperiment)
{
  disconnect(mpBtnSteadystate, SIGNAL(toggled(bool)), this, SLOT(slotExprimentType(bool)));
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

  mpValidatorName->saved();
  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();

  loadTable(false);

  connect(mpBtnSteadystate, SIGNAL(toggled(bool)), this, SLOT(slotExprimentType(bool)));
  return true;
}

bool CQExperimentData::saveExperiment(CExperiment * pExperiment)
{
  if (!pExperiment) return false;

  QString value = mpEditName->text();
  int pos = value.length();

  if (pExperiment->getObjectName() != (const char *) value &&
      mpValidatorName->validate(value, pos) == QValidator::Acceptable)
    {
      int current = mpBoxExperiment->currentItem();
      disconnect(mpBoxExperiment, SIGNAL(currentChanged(QListBoxItem*)),
                 this, SLOT(slotExperimentChanged(QListBoxItem*)));
      mpBoxExperiment->changeItem(value, mShown);
      mpBoxExperiment->setSelected(current, true);
      connect(mpBoxExperiment, SIGNAL(currentChanged(QListBoxItem*)),
              this, SLOT(slotExperimentChanged(QListBoxItem*)));
      pExperiment->setObjectName((const char *) value);
    }

  if (mpCheckTab->isChecked())
    pExperiment->setSeparator("\t");
  else
    pExperiment->setSeparator((const char *) mpEditSeparator->text().utf8());

  value = mpEditFirst->text();
  pos = value.length();
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

  mpValidatorName->saved();
  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();

  saveTable();

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

void CQExperimentData::slotUpdateTable()
{loadTable(true);}

void CQExperimentData::slotModelObject(int row)
{
  // :TODO: Implement object browser and update of column 'Model Object'.
  CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this);

  if (pObject)
    {
      mpTable->setText(row, COL_OBJECT, FROM_UTF8(pObject->getObjectDisplayName()));
      mpTable->setText(row, COL_OBJECT_HIDDEN, FROM_UTF8(pObject->getCN()));
    }
}

void CQExperimentData::loadTable(const bool & guess)
{
  if (!mpExperiment)
    {
      mpTable->setNumRows(0);
      mpTable->setNumRows(3);

      pdelete(mpComboMap);
      pdelete(mpBtnMap);

      return;
    }

  unsigned C_INT32 TimeRow = C_INVALID_INDEX;

  pdelete(mpComboMap);
  mpComboMap = new QSignalMapper(this);
  connect(mpComboMap, SIGNAL(mapped(int)), this, SLOT(slotTypeChanged(int)));

  pdelete(mpBtnMap);
  mpBtnMap = new QSignalMapper(this);
  connect(mpBtnMap, SIGNAL(mapped(int)), this, SLOT(slotModelObject(int)));

  mpExperiment->readColumnNames();
  const std::vector<std::string> & ColumnNames = mpExperiment->getColumnNames();

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

  unsigned C_INT32 i, imax = ColumnNames.size();
  mpTable->setNumRows(imax);

  CExperimentObjectMap & ObjectMap = mpExperiment->getObjectMap();

  QComboBox * pComboBox;
  QToolButton* pBtn;
  CCopasiObject * pObject;
  CExperiment::Type Type;

  for (i = 0; i < imax; i++)
    {
      // COL_NAME
      mpTable->setText(i, COL_NAME, FROM_UTF8(ColumnNames[i]));

      // COL_TYPE
      pComboBox = new QComboBox(mpTable);
      pComboBox->insertStringList(ColumnTypes);
      pComboBox->setEditable(false);
      if (guess && TimeRow == C_INVALID_INDEX &&
          mpBtnTimeCourse->isChecked() &&
          mpTable->text(i, COL_NAME).contains("time", false))
        mpExperiment->setColumnType(i, CExperiment::time);

      Type = mpExperiment->getColumnType(i);
      if (Type == CExperiment::time) TimeRow = i;
      pComboBox->setCurrentItem(Type);

      mpComboMap->setMapping(pComboBox, i);
      connect(pComboBox, SIGNAL(activated(int)), mpComboMap, SLOT(map()));

      mpTable->setCellWidget(i, COL_TYPE, pComboBox);

      // COL_TYPE_HIDDEN
      mpTable->setText(i, COL_TYPE_HIDDEN, QString::number(pComboBox->currentItem()));

      // COL_BTN
      pBtn = new QToolButton(mpTable);
      pBtn->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pBtn->sizePolicy().hasHeightForWidth()));
      pBtn->setMaximumSize(QSize(20, 20));
      pBtn->setIconSet(QIconSet(image2));

      if (Type == CExperiment::ignore || Type == CExperiment::time)
        pBtn->setEnabled(false);

      mpBtnMap->setMapping(pBtn, i);
      connect(pBtn, SIGNAL(clicked()), mpBtnMap, SLOT(map()));

      mpTable->setCellWidget(i, COL_BTN, pBtn);

      // COL_OBJECT and COL_OBJECT_HIDDEN
      if (ObjectMap.getObjectCN(i) != "")
        {
          pObject = CCopasiContainer::ObjectFromName(ObjectMap.getObjectCN(i));
          if (pObject)
            mpTable->setText(i, COL_OBJECT, FROM_UTF8(pObject->getObjectDisplayName()));
          else
            mpTable->setText(i, COL_OBJECT, "not found");

          mpTable->setText(i, COL_OBJECT_HIDDEN, FROM_UTF8(ObjectMap.getObjectCN(i)));
        }
      else
        {
          mpTable->setText(i, COL_OBJECT, "");
          mpTable->setText(i, COL_OBJECT_HIDDEN, "");
        }
    }

  if (TimeRow != C_INVALID_INDEX)
    for (i = 0; i < imax; i++)
      if (i != TimeRow)
        static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->removeItem(CExperiment::time);
}

void CQExperimentData::slotTypeChanged(int row)
{
  CExperiment::Type NewType =
    static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(row, COL_TYPE))->currentItem());
  CExperiment::Type OldType =
    static_cast<CExperiment::Type>(mpTable->text(row, COL_TYPE_HIDDEN).toLong());

  if (OldType == NewType) return;

  bool BtnEnabled = true;
  unsigned C_INT32 i, imax = mpTable->numRows();

  switch (NewType)
    {
    case CExperiment::ignore:
      BtnEnabled = false;
      break;

    case CExperiment::independent:
    case CExperiment::dependent:
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

  return;
}

void CQExperimentData::slotSeparator()
{
  if (!mpExperiment) return;

  saveTable();

  if (mpCheckTab->isChecked())
    mpExperiment->setSeparator("\t");
  else
    mpExperiment->setSeparator((const char *) mpEditSeparator->text().utf8());

  mpExperiment->setNumColumns(mpExperiment->guessColumnNumber());
  mpExperiment->readColumnNames();

  loadTable(true);
}

bool CQExperimentData::saveTable()
{
  CExperimentObjectMap & ObjectMap = mpExperiment->getObjectMap();
  unsigned C_INT32 i, imax = mpTable->numRows();
  for (i = 0; i < imax; i++)
    {
      CExperiment::Type Type =
        static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->currentItem());
      if (mpExperiment->getColumnType(i) != Type)
        mpExperiment->setColumnType(i, Type);

      if (ObjectMap.getObjectCN(i) != (const char *) mpTable->text(i, COL_OBJECT_HIDDEN).utf8())
        ObjectMap.setObjectCN(i, (const char *) mpTable->text(i, COL_OBJECT_HIDDEN).utf8());
    }

  return true;
}
