// Copyright (C) 2024 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQExternalToolDialog.h"

#include "CQExternalTools.h"

#include <QMenu>
#include <QFile>
#include <QFileDialog>

#include <copasi/resourcesUI/CQIconResource.h>

CQExternalToolDialog::CQExternalToolDialog(QWidget * parent, const char * name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
  , mTools()
  , mCurrentTool()
  , mCurrentIndex(-1)
{
#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin
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

  blockSignals(block);

  // select the first item
  selectItem(0);
}

void CQExternalToolDialog::selectItem(int index)
{
  if (signalsBlocked())
    return;
  lstExternalTools->setCurrentRow(index);
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

void CQExternalToolDialog::loadTool(CQExternalTool & tool)
{
  bool block = blockSignals(true);

  // set the textboxes
  txtTitle->setText(tool.getName());
  txtCommand->setText(tool.getCommand());
  txtArguments->setText(tool.getArguments());
  txtInitialDirectory->setText(tool.getWorkingDirectory());
  txtIniFile->setText(tool.getIniFile());
  chkPromptForArguments->setChecked(tool.promptForArguments());

  // enable them
  txtTitle->setEnabled(true);
  txtCommand->setEnabled(true);
  txtArguments->setEnabled(true);
  txtInitialDirectory->setEnabled(true);
  chkPromptForArguments->setEnabled(true);

  blockSignals(block);
}

void CQExternalToolDialog::slotAddTool()
{
  // add a new tool
  CQExternalTool tool;
  tool.setName(QString("[Tool %1]").arg(mTools.size() + 1));
  mTools.append(tool);
  lstExternalTools->addItem(tool.getName());

  selectItem(mTools.size() - 1);
}

void CQExternalToolDialog::saveTool(CQExternalTool & tool)
{
  bool block = blockSignals(true);
  tool.setName(txtTitle->text());
  tool.setCommand(txtCommand->text());
  tool.setArguments(txtArguments->text());
  tool.setWorkingDirectory(txtInitialDirectory->text());
  tool.setPromptForArguments(chkPromptForArguments->isChecked());
  tool.setIniFile(txtIniFile->text());
  blockSignals(block);
}

void CQExternalToolDialog::saveCurrent()
{
  saveTool(mCurrentTool);

  mTools[mCurrentIndex] = mCurrentTool;
  // update the name in the list
  lstExternalTools->item((int) mCurrentIndex)->setText(mCurrentTool.getName());
}

void CQExternalToolDialog::loadCurrent(int index)
{
  if (index < 0 || index >= mTools.size())
    {
      clear();
      return;
    }

  mCurrentIndex = index;
  mCurrentTool = mTools[index];
  loadTool(mCurrentTool);
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

  lstExternalTools->setCurrentRow(index);
}

void CQExternalToolDialog::clear()
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
}

void CQExternalToolDialog::slotMoveUp()
{
    // get the selected tool
    auto index = lstExternalTools->currentRow();
    if (index < 1 || index >= mTools.size())
        return;

    bool block = blockSignals(true);
    // save current settings
    saveCurrent();
    clear();

    auto & first = mTools[index];
    auto & second = mTools[index - 1];

    QString firstIni = first.getIniFile();
    QString otherIni = second.getIniFile();

    // move it up
    mTools.swapItemsAt(index, index - 1);
    lstExternalTools->insertItem(index - 1, lstExternalTools->takeItem(index));

    // swap ini files to keep the correct association
    first.setIniFile(firstIni);
    second.setIniFile(otherIni);

    loadCurrent(index-1);

    lstExternalTools->setCurrentRow(index - 1);

    blockSignals(block);
}

void CQExternalToolDialog::slotMoveDown()
{
    // get the selected tool
    auto index = lstExternalTools->currentRow();
    if (index < 0 || index >= mTools.size() - 1)
        return;

    bool block = blockSignals(true);

    // save current settings
    saveCurrent();
    clear();

    auto & first = mTools[index];
    auto & second = mTools[index + 1];

    QString firstIni = first.getIniFile();
    QString otherIni = second.getIniFile();

    // move it up
    mTools.swapItemsAt(index, index + 1);
    lstExternalTools->insertItem(index + 1, lstExternalTools->takeItem(index));

    // swap ini files to keep the correct association
    first.setIniFile(firstIni);
    second.setIniFile(otherIni);

    loadCurrent(index + 1);

    lstExternalTools->setCurrentRow(index + 1);
    blockSignals(block);
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
    // show a context menu with default arguments: $cpsFile, $sbmlFile, $omexFile, $copasiExecutable
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
  if (signalsBlocked())
    return;

  // get the selected tool
  auto index = lstExternalTools->currentRow();
  if (index < 0 || index >= mTools.size())
    {
      clear();
      return;
    }

  // if current index is different from the selected index, save the current tool
  if (mCurrentIndex != index && mCurrentIndex >= 0 && mCurrentIndex < (size_t)mTools.size())
    {
      saveCurrent();
    }

  loadCurrent(index);
}

void CQExternalToolDialog::slotUpdateSelected()
{
    if (mCurrentIndex < 0 || mCurrentIndex >= (size_t)mTools.size())
        return;

    if (signalsBlocked())
      return;

    saveTool(mCurrentTool);

    mTools[mCurrentIndex] = mCurrentTool;
    lstExternalTools->item((int)mCurrentIndex)->setText(mCurrentTool.getName());
}
