// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQExternalTools.h"

#include <QAction>
#include <QMenu>
#include <QString>
#include <QDir>
#include <QInputDialog>
#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>

#include <copasi/copasi.h>
#include <copasi/core/CCore.h>
#include <copasi/commandline/COptions.h>
#include <copasi/UI/qtUtilities.h>
#include <copasi/UI/DataModelGUI.h>
#include <copasi/CopasiDataModel/CDataModel.h>

CQExternalTools::CQExternalTools()
  : mpAction(nullptr)
  , mpMenu(nullptr)
  , mActionToTool()
{
}

CQExternalTools::CQExternalTools(const CQExternalTools & other)
    : mpAction(other.mpAction)
    , mpMenu(other.mpMenu)
    , mActionToTool(other.mActionToTool)
{
}

CQExternalTools::~CQExternalTools()
{
}

void CQExternalTools::init(QMenu * pMenu, QAction * pAction)
{
  mpMenu = pMenu;
  mpAction = pAction;

  removeActionsFromMenu();

  mActionToTool.clear();

  auto files = getToolFiles();
  QString copasiDir = QString(COptions::getConfigDir().c_str());

  for (auto & file : files)
    {
      auto tool = new CQExternalTool(file);
      if (!tool->isValid())
        {
          delete tool;
          continue;
        }

      auto action = new QAction(tool->getName(), mpMenu);
      QObject::connect(action, &QAction::triggered, tool, &CQExternalTool::execute);

      mActionToTool[action] = tool;
    }

  addActionsToMenu();
}

void CQExternalTools::removeActionsFromMenu()
{
  if (!mpMenu || !mpAction)
    return;

  for (auto & action : mActionToTool)
    {
      mpMenu->removeAction(action.first);
      delete action.first;
      delete action.second;
    }
}

void CQExternalTools::addActionsToMenu()
{
  if (!mpMenu || !mpAction)
    return;

  for (auto & action : mActionToTool)
    {
      mpMenu->insertAction(mpAction, action.first);
    }
}

QStringList CQExternalTools::getToolFiles()
{
  // find all setting files for external tools
  // they will be in the configDir as tools*.ini
  auto copasiDir = QString(COptions::getConfigDir().c_str());

  // use the QDir class to find all files that match the pattern
  QDir dir(copasiDir);
  QStringList filters;
  filters << "tools*.ini";
  dir.setNameFilters(filters);

  QStringList files = dir.entryList();
  // now prepend the directory to the file names
  for (auto & file : files)
    {
      file = copasiDir + QString("/") + file;
    }

  return files;
}

QStringList CQExternalTools::getToolNames() const
{
    QStringList names;

    for (auto & action : mActionToTool)
        {
        names << action.second->getName();
        }

    return names;
}

QList< CQExternalTool * > CQExternalTools::getTools() const
{
    QList< CQExternalTool * > tools;

    for (auto & action : mActionToTool)
        {
        tools << action.second;
        }

    return tools;
}

CQExternalTool::CQExternalTool()
  : mIniFile()
  , name()
  , toolTip()
  , command()
  , arguments()
  , workingDirectory()
  , mPromptForArguments(false)
  , mIsValid(false)
{
}

CQExternalTool::CQExternalTool(const QString & iniFile)
  : mIniFile(iniFile)
{
  QSettings settings(iniFile, QSettings::IniFormat);

  settings.beginGroup("ExternalTool");

  name = settings.value("name").toString();
  toolTip = settings.value("toolTip").toString();
  command = settings.value("command").toString();
  arguments = settings.value("arguments").toString();
  workingDirectory = settings.value("workingDirectory").toString();

  mPromptForArguments = settings.value("promptForArguments").toBool();

  mIsValid = !name.isEmpty();
}

CQExternalTool::CQExternalTool(const CQExternalTool & other)
    : mIniFile(other.mIniFile)
    , name(other.name)
    , toolTip(other.toolTip)
    , command(other.command)
    , arguments(other.arguments)
    , workingDirectory(other.workingDirectory)
    , mPromptForArguments(other.mPromptForArguments)
    , mIsValid(other.mIsValid)
{
}

CQExternalTool::~CQExternalTool()
{
}

CQExternalTool & CQExternalTool::operator=(const CQExternalTool & other)
{
  if (this != &other)
    {
      mIniFile = other.mIniFile;
      name = other.name;
      toolTip = other.toolTip;
      command = other.command;
      arguments = other.arguments;
      workingDirectory = other.workingDirectory;
      mPromptForArguments = other.mPromptForArguments;
      mIsValid = other.mIsValid;
    }

  return *this;
}

void CQExternalTool::save()
{
  QSettings settings(mIniFile, QSettings::IniFormat);

  settings.beginGroup("ExternalTool");

  settings.setValue("name", name);
  settings.setValue("toolTip", toolTip);
  settings.setValue("command", command);
  settings.setValue("arguments", arguments);
  settings.setValue("workingDirectory", workingDirectory);

  settings.setValue("promptForArguments", mPromptForArguments);

  settings.endGroup();
}

void CQExternalTool::ensureIniFile()
{
  // if the ini file is not set, create a new one
  if (mIniFile.isEmpty())
    {
      auto files = CQExternalTools::getToolFiles();
      QString copasiDir = QString(COptions::getConfigDir().c_str());
      QString iniFile = copasiDir + "/tools1.ini";
      int i = 1;
      while (files.contains(iniFile))
        {
          iniFile = copasiDir + QString("/tools%1.ini").arg(++i);
        }
      mIniFile = iniFile;
    }
}

void CQExternalTool::execute()
{
  auto args = arguments;
  // if prompt for arguments is set, show a dialog to enter the arguments
  if (mPromptForArguments)
    {
      // show a dialog to enter the arguments
      args = QInputDialog::getText(nullptr, "Arguments", "Enter the arguments for the tool", QLineEdit::Normal, arguments);
      if (args.isEmpty())
        return;
    }

  auto *dm_gui = getDataModel();
  if (!dm_gui)
    return;

  auto * dm = dm_gui->getDataModel();
  if (!dm)
    return;

  // split the arguments into a list
  QStringList argList;
    QString arg;
    bool inQuote = false;
    for (auto & c : args)
    {
        if (c == '\"')
        {
            inQuote = !inQuote;
            continue;
        }

        if (c == ' ' && !inQuote)
        {
            argList << arg;
            arg.clear();
            continue;
        }

        arg += c;
    }

    if (!arg.isEmpty())
    {
        argList << arg;
    }

  // handle special arguments: $cpsFile, $sbmlFile, $omexFile, $copasiExecutable
  auto saveDir = QString(COptions::getTemp().c_str());

  // loop over the arguments and replace the special arguments
  for (auto & arg : argList)
  {
    if (arg == "$copasiExecutable")
    {
      // determine the path to the currently running copasi
      auto copasiExecutable = QCoreApplication::applicationFilePath();
      arg = copasiExecutable;
    }

    if (arg == "$cpsFile")
    {
      auto cpsFile = saveDir + "/temp.cps";
      auto cps = dm->saveModelToString(NULL);

      QFile file(cpsFile);
      if (file.open(QIODevice::WriteOnly))
      {
        QTextStream stream(&file);
        stream << FROM_UTF8(cps);
      }
      file.close();

      arg = cpsFile;
    }

    if (arg.startsWith("$sbmlFile"))
    {
      int sbmlLevel = 3;
      int sbmlVersion = 2;
      if (arg.at(arg.length() - 4) == 'L' && arg.at(arg.length() - 2) == 'V')
      {
          sbmlLevel = QString(arg.at(arg.length() - 3)).toInt();
        sbmlVersion = QString(arg.at(arg.length() - 1)).toInt();
        }

      auto sbmlFile = saveDir + "/temp.sbml";
      auto sbml = dm->exportSBMLToString(NULL, sbmlLevel, sbmlVersion);

      QFile file(sbmlFile);
      if (file.open(QIODevice::WriteOnly))
      {
        QTextStream stream(&file);
        stream << FROM_UTF8(sbml);
      }
      file.close();

      arg = sbmlFile;
    }

    if (arg == "$omexFile")
    {
      auto omexFile = saveDir + "/temp.omex";
      auto omex = dm->exportCombineArchive(TO_UTF8(omexFile), true, true, true, true, true);
      arg = omexFile;
    }
  }

  // execute the command using QProcess
  QProcess process;
  process.setWorkingDirectory(workingDirectory);
  process.setProgram(command);
  process.setWorkingDirectory(workingDirectory);
  process.startDetached(command, argList);
}
