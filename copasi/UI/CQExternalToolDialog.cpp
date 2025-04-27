// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQExternalToolDialog.h"

#include "CQExternalTools.h"

#include <QMenu>
#include <QFile>
#include <QFileDialog>

CQExternalToolDialog::CQExternalToolDialog(QWidget * parent, const char * name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
  , mTools()
  , mCurrentTool()
  , mCurrentIndex(-1)
{
  setupUi(this);
}

CQExternalToolDialog::~CQExternalToolDialog()
{
}

void CQExternalToolDialog::init(CQExternalTools * tools)
{
  if (tools == nullptr)
    return;

  bool block = blockSignals(true);

  // clear the textboxes
  txtTitle->clear();
  txtCommand->clear();
  txtArguments->clear();
  txtInitialDirectory->clear();
  chkPromptForArguments->setChecked(false);

  // disable them
  txtTitle->setEnabled(false);
  txtCommand->setEnabled(false);
  txtArguments->setEnabled(false);
  txtInitialDirectory->setEnabled(false);
  chkPromptForArguments->setEnabled(false);

  // create a copy of the tools
  mTools.clear();
  lstExternalTools->clear();
  for (auto * tool : tools->getTools())
    {
      mTools.append(CQExternalTool(*tool));
      lstExternalTools->addItem(tool->getName());
    }

  // select the first tool
  if (!mTools.isEmpty())
    {
      lstExternalTools->setCurrentRow(0);
    }

  blockSignals(block);
}

void CQExternalToolDialog::saveTools(bool deleteExisting)
{
  if (deleteExisting)
    {
      auto exitingFiles = CQExternalTools::getToolFiles();
      for (auto & file : exitingFiles)
        {
          QFile::remove(file);
        }
    }

    for (auto & tool : mTools)
        {
            tool.ensureIniFile();
            tool.save();
        }
}

void CQExternalToolDialog::slotAddTool()
{
  // add a new tool
  CQExternalTool tool;
  tool.setName(QString("[Tool %1]").arg(mTools.size() + 1));
  mTools.append(tool);
  lstExternalTools->addItem(tool.getName());
}

void CQExternalToolDialog::slotDeleteTool()
{
  // get the selected tool
  auto index = lstExternalTools->currentRow();
  if (index < 0 || index >= mTools.size())
    return;

  // remove it
  mTools.removeAt(index);
  delete lstExternalTools->takeItem(index);
}

void CQExternalToolDialog::slotMoveUp()
{
    // get the selected tool
    auto index = lstExternalTools->currentRow();
    if (index <= 1 || index >= mTools.size())
        return;

    // move it up
    mTools.move(index, index - 1);
    lstExternalTools->insertItem(index - 1, lstExternalTools->takeItem(index));
}

void CQExternalToolDialog::slotMoveDown()
{
    // get the selected tool
    auto index = lstExternalTools->currentRow();
    if (index < 0 || index >= mTools.size() - 1)
        return;

    // move it down
    mTools.move(index, index + 1);
    lstExternalTools->insertItem(index + 1, lstExternalTools->takeItem(index));
}

void CQExternalToolDialog::slotBrowseCommand()
{
    // open a file dialog to select the command
    auto command = QFileDialog::getOpenFileName(this, tr("Select Command"), QString(), tr("All Files (*)"));
    if (!command.isEmpty())
        txtCommand->setText(command);
}

void CQExternalToolDialog::slotShowArgs()
{
    // show a contect menu with default arguments: $cpsFile, $sbmlFile, $omexFile, $copasiExecutable
    QMenu menu(this);
    menu.addAction("$cpsFile");
    menu.addAction("$sbmlFile");
    menu.addAction("$omexFile");
    menu.addAction("$copasiExecutable");

    auto action = menu.exec(QCursor::pos());
    if (action)
      {
        txtArguments->setText(txtArguments->text() + action->text());
      }
}

void CQExternalToolDialog::slotBrowseInitialDir()
{
    // open a file dialog to select the initial directory
    auto dir = QFileDialog::getExistingDirectory(this, tr("Select Initial Directory"));
    if (!dir.isEmpty())
        txtInitialDirectory->setText(dir);
}

void CQExternalToolDialog::slotItemChanged()
{

  // get the selected tool
  auto index = lstExternalTools->currentRow();
  if (index < 0 || index >= mTools.size())
    {
      bool block = blockSignals(true);

      // clear the textboxes
      txtTitle->clear();
      txtCommand->clear();
      txtArguments->clear();
      txtInitialDirectory->clear();
      txtIniFile->clear();
      chkPromptForArguments->setChecked(false);

      // disable them
      txtTitle->setEnabled(false);
      txtCommand->setEnabled(false);
      txtArguments->setEnabled(false);
      txtInitialDirectory->setEnabled(false);
      chkPromptForArguments->setEnabled(false);

      blockSignals(block);

      return;
    }

  // if current index is different from the selected index, save the current tool
  if (mCurrentIndex != index && mCurrentIndex >= 0 && mCurrentIndex < mTools.size())
    {
      mCurrentTool.setName(txtTitle->text());
      mCurrentTool.setCommand(txtCommand->text());
      mCurrentTool.setArguments(txtArguments->text());
      mCurrentTool.setWorkingDirectory(txtInitialDirectory->text());
      mCurrentTool.setPromptForArguments(chkPromptForArguments->isChecked());
      mCurrentTool.setIniFile(txtIniFile->text());

      mTools[mCurrentIndex] = mCurrentTool;
      // update the name in the list
      lstExternalTools->item(mCurrentIndex)->setText(mCurrentTool.getName());
    }

  mCurrentIndex = index;
  mCurrentTool = mTools[index];

  bool block = blockSignals(true);

  // set the textboxes
  txtTitle->setText(mCurrentTool.getName());
  txtCommand->setText(mCurrentTool.getCommand());
  txtArguments->setText(mCurrentTool.getArguments());
  txtInitialDirectory->setText(mCurrentTool.getWorkingDirectory());
  txtIniFile->setText(mCurrentTool.getIniFile());
  chkPromptForArguments->setChecked(mCurrentTool.promptForArguments());

  // enable them
  txtTitle->setEnabled(true);
  txtCommand->setEnabled(true);
  txtArguments->setEnabled(true);
  txtInitialDirectory->setEnabled(true);
  chkPromptForArguments->setEnabled(true);

  blockSignals(block);
}

void CQExternalToolDialog::slotUpdateSelected()
{
    if (mCurrentIndex < 0 || mCurrentIndex >= mTools.size())
        return;

    if (signalsBlocked())
      return;

    mCurrentTool.setName(txtTitle->text());
    mCurrentTool.setCommand(txtCommand->text());
    mCurrentTool.setArguments(txtArguments->text());
    mCurrentTool.setWorkingDirectory(txtInitialDirectory->text());
    mCurrentTool.setPromptForArguments(chkPromptForArguments->isChecked());
    mCurrentTool.setIniFile(txtIniFile->text());

    mTools[mCurrentIndex] = mCurrentTool;
    lstExternalTools->item(mCurrentIndex)->setText(mCurrentTool.getName());
}
