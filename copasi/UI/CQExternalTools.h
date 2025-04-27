// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQ_EXTERNAL_TOOLS_H
#define CQ_EXTERNAL_TOOLS_H

class QAction;
class QMenu;

#include <QObject>
#include <QSettings>
#include <QString>

#include <map>

class CQExternalTool : public QObject
{
  Q_OBJECT

public:
  CQExternalTool();
  CQExternalTool(const QString & iniFile);
  CQExternalTool(const CQExternalTool & other);
  ~CQExternalTool();

  CQExternalTool & operator=(const CQExternalTool & other);

  bool isValid() const
  {
    return mIsValid;
  }

  QString getName() const
  {
    return name;
  }
  void setName(const QString & value)
  {
    name = value;
  }

  QString getToolTip() const
  {
    return toolTip;
  }
  void setToolTip(const QString & value)
  {
    toolTip = value;
  }

  QString getCommand() const
  {
    return command;
  }
  void setCommand(const QString & value)
  {
    command = value;
  }

  QString getArguments() const
  {
    return arguments;
  }
  void setArguments(const QString & value)
  {
    arguments = value;
  }

  QString getWorkingDirectory() const
  {
    return workingDirectory;
  }
  void setWorkingDirectory(const QString & value)
  {
    workingDirectory = value;
  }

  bool promptForArguments() const
  {
    return mPromptForArguments;
  }
  void setPromptForArguments(bool value)
  {
    mPromptForArguments = value;
  }

  QString getIniFile() const
  {
    return mIniFile;
  }
  void setIniFile(const QString & value)
  {
    mIniFile = value;
  }

  void ensureIniFile();

public slots:
  void execute();
  void save();

private:
  QString mIniFile;

  QString name;
  QString toolTip;
  QString command;
  QString arguments;
  QString workingDirectory;

  bool mPromptForArguments;
  bool mIsValid;
};

class CQExternalTools
{

public:
  CQExternalTools();
  CQExternalTools(const CQExternalTools & other);
  ~CQExternalTools();

  void init(QMenu * pMenu, QAction * pAction);

  void removeActionsFromMenu();
  void addActionsToMenu();

  static QStringList getToolFiles();
  QStringList getToolNames() const;
  QList< CQExternalTool * > getTools() const;

private:
  QAction * mpAction;
  QMenu * mpMenu;

  std::map< QAction *, CQExternalTool * > mActionToTool;
};

#endif // CQ_EXTERNAL_TOOLS_H
