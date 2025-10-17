// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQPLProcessWidget.h"
#include "copasi/utilities/CProfileSettings.h"
#include "qtUtilities.h"

#include <QFileDialog>

CQPLProcessWorker::CQPLProcessWorker(const QString& program)
  : QObject()
  , mRuntime(0.0)
{
  mpProcess = new QProcess(this);
  mCopasiSE = program;
  connect(mpProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(handleProcessError(QProcess::ProcessError)));
  connect(mpProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(ProcessFinished(int, QProcess::ExitStatus)));
  connect(mpProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(handleStandardOutput()));
  connect(mpProcess, SIGNAL(readyReadStandardError()), this, SLOT(handleStandardError()));
  mCancelled = false;
}

CQPLProcessWorker::~CQPLProcessWorker()
{
  delete mpProcess;
}

void CQPLProcessWorker::start(const QString& cpsFile, const QString& label)
{
  mCurrentFile = cpsFile;
  mLabel = label;
  mpProcess->start(mCopasiSE, QStringList() << "--nologo" << cpsFile);
  mStartTime = std::chrono::high_resolution_clock::now();
}

const QString& CQPLProcessWorker::currentFile() const
{
  return mCurrentFile;
}

const QString & CQPLProcessWorker::currentLabel() const
{
  return mLabel;
}

double CQPLProcessWorker::getRuntime() const
{
  return mRuntime;
}

void CQPLProcessWorker::cancel()
{
  mCancelled = true;

  if (mpProcess->state() == QProcess::Running)
  {
    mpProcess->kill();
  }
}

void CQPLProcessWorker::kill()
{
  mpProcess->kill();
}

void CQPLProcessWorker::handleProcessError(QProcess::ProcessError)
{
  if (!mCancelled)
  emit errorOccurred(this, QString("Process error: %1").arg(mpProcess->errorString()));
}

void CQPLProcessWorker::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  auto endTime = std::chrono::high_resolution_clock::now();
  mRuntime = std::chrono::duration< double >(endTime - mStartTime).count();
  mOutput += mpProcess->readAllStandardOutput();
  mError += mpProcess->readAllStandardError();
  //if (!mOutput.isEmpty() || !mError.isEmpty())
  //{
  //    qDebug() << mOutput;
  //}
  emit finished(this);
}

QString formatArray(const QString& prefix, const QByteArray& message)
{
  QStringList lines = QString::fromUtf8(message).split('\n');
  QStringList formattedLines;
  for (const QString &line : lines)
  {
    formattedLines << (prefix + ": " + line);
  }
  return formattedLines.join('\n');
}

void CQPLProcessWorker::handleStandardOutput()
{
  auto newOutput = mpProcess->readAllStandardOutput();
  mOutput += newOutput;
  emit output(this, formatArray(mLabel, newOutput));
}

void CQPLProcessWorker::handleStandardError()
{
  auto newError = mpProcess->readAllStandardError();
  mError += newError;
  emit output(this, formatArray(mLabel, newError));
}

CQPLProcessWidget::CQPLProcessWidget(QWidget * parent)
{
  setupUi(this);
}

void CQPLProcessWidget::loadSettings(const CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  mpSettings = const_cast<CProfileSettings*>(pSettings);

  mpTxtDirectory->setText(FROM_UTF8(pSettings->getDirectory()));
  mpTxtCopasiSE->setText(FROM_UTF8(pSettings->getCopasiSE()));
  mpSpnNumProcesses->setValue((*pSettings)["Num Processes"]);
}

void CQPLProcessWidget::saveSettings(CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  (*pSettings)["Directory"] = TO_UTF8(mpTxtDirectory->text());
  (*pSettings)["Num Processes"] = mpSpnNumProcesses->value();
  (*pSettings)["CopasiSE"] = TO_UTF8(mpTxtCopasiSE->text());

  pSettings->save();
}

void CQPLProcessWidget::browseCopasiSE()
{
  QString file = QFileDialog::getOpenFileName(this, "Select CopasiSE", "", "CopasiSE (*.exe CopasiSE);;All files (*.*)");
  if (file.isEmpty())
    return;
  mpTxtCopasiSE->setText(file);
}

void CQPLProcessWidget::browseDirectory()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", "", QFileDialog::ShowDirsOnly);
  if (dir.isEmpty())
    return;

  mpTxtDirectory->setText(dir);
}

QStringList CQPLProcessWidget::globFiles(const QString& directory, const QString& pattern)
{
  QDir dir(directory, pattern, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoDotAndDotDot);
  QStringList list = dir.entryList();
  QStringList filtered;

  // remove tmp files
  for(auto & entry: list)
    if (!entry.startsWith("tmp__"))
      filtered.append(entry);

  return list;
}

void CQPLProcessWidget::processDirectory()
{
  mpCmdRun->setEnabled(false);

  saveSettings(mpSettings);

  // glob all cps files from the directory
  mFiles = globFiles(mpTxtDirectory->text(), "*profile_*.cps");
  mpTxtOutput->setPlainText(QString("Found %1 files").arg(mFiles.count()));

  if (mFiles.isEmpty())
  {
    mpCmdRun->setEnabled(true);
    return;
  }

  // set up process bar
  mpProcessBar->setRange(0, mFiles.size());
  mpProcessBar->setValue(0);

  // allocate as many workers as we have specified in num processes
  for (int i = 0; i < mpSpnNumProcesses->value(); i++)
  {
    CQPLProcessWorker* pWorker = new CQPLProcessWorker(mpTxtCopasiSE->text());
    mAvailableWorkers.append(pWorker);
    connect(pWorker, &CQPLProcessWorker::finished, this, &CQPLProcessWidget::workerFinished);
    connect(pWorker, &CQPLProcessWorker::errorOccurred, this, &CQPLProcessWidget::workerError);
    connect(pWorker, &CQPLProcessWorker::output, this, &CQPLProcessWidget::workerOutput);
  }

  // take the first mpSpnNumProcesses->value() files
  QStringList files = mFiles.mid(0, mpSpnNumProcesses->value());

  for (const auto& file : files)
  {
    auto* pWorker = mAvailableWorkers.takeFirst();
    // load the file
    mpTxtOutput->append(QString("start file: %1").arg(file));
    pWorker->start(mpTxtDirectory->text() + "/" + file, file);
    mFiles.removeAll(file);
    mWorkers.append(pWorker);
  }
}

void CQPLProcessWidget::cancelRun()
{
  // empty list of files to submit (otherwise new ones will be added)
  mpTxtOutput->append("clearing file list ...");
  mFiles.clear();

  // cancel all workers
  for (auto* pWorker : mWorkers)
  {
    pWorker->cancel();
  }

  // reset status
  mpProcessBar->setValue(0);

  // enable the run button
  mpCmdRun->setEnabled(true);
}

void CQPLProcessWidget::workerFinished(CQPLProcessWorker* pWorker)
{
  if (!pWorker)
    return;

  mpTxtOutput->append(QString("finished %1 in %2 seconds").arg(pWorker->currentLabel()).arg(pWorker->getRuntime()));

  // increment the process bar
  mpProcessBar->setValue(mpProcessBar->value() + 1);

  // if there are more files process the next one
  if (!mFiles.isEmpty())
  {
    QString first = mFiles.takeFirst();
    mpTxtOutput->append("start file: " + first);
    pWorker->start(mpTxtDirectory->text() + "/" + first, first);
  }
  else
  {
    mpTxtOutput->append("removing worker ...");
    mWorkers.removeAll(pWorker);
    delete pWorker;
  }

  if (mWorkers.isEmpty() && !mpCmdRun->isEnabled())
  {
    mpTxtOutput->append("all done");
    mpCmdRun->setEnabled(true);
  }
}

void CQPLProcessWidget::workerError(CQPLProcessWorker* pWorker, const QString& error)
{
  // add error to the log
  mpTxtOutput->append(error);
}

void CQPLProcessWidget::workerOutput(CQPLProcessWorker* pWorker, const QString& output)
{
  // add output to the log
  mpTxtOutput->append(output);
}
