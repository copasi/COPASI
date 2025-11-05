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
  connect(mpProcess, &QProcess::errorOccurred, this, &CQPLProcessWorker::handleProcessError);

  // connect differently for qt 5 and qt 6
  #if QT_VERSION_MAJOR == 5
  connect(mpProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(handleProcessFinished(int, QProcess::ExitStatus))); 
  #else
  connect(mpProcess, &QProcess::finished, this, &CQPLProcessWorker::handleProcessFinished);
  #endif

  connect(mpProcess, &QProcess::readyReadStandardOutput, this, &CQPLProcessWorker::handleStandardOutput);
  connect(mpProcess, &QProcess::readyReadStandardError, this, &CQPLProcessWorker::handleStandardError);
  mCancelled = false;
}

CQPLProcessWorker::~CQPLProcessWorker()
{
  mpProcess->deleteLater();
}

void CQPLProcessWorker::setCopasiSE(const QString & copasiSE)
{
  mCopasiSE = copasiSE;
}

void CQPLProcessWorker::start(const QString& cpsFile, const QString& label)
{
  mCurrentFile = cpsFile;
  mLabel = label;
  mCancelled = false;
  mStartTime = std::chrono::high_resolution_clock::now();
  mpProcess->start(mCopasiSE, QStringList() << "--nologo" << cpsFile);
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

bool CQPLProcessWorker::wasCancelled() const
{
  return mCancelled;
}

void CQPLProcessWorker::kill()
{
  mpProcess->kill();
}

void CQPLProcessWorker::handleProcessError(QProcess::ProcessError)
{
  emit errorOccurred(this, formatMessage(mLabel, QString("Process error: %1").arg(mpProcess->errorString())));
}

void CQPLProcessWorker::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  auto endTime = std::chrono::high_resolution_clock::now();
  mRuntime = std::chrono::duration< double >(endTime - mStartTime).count();
  mOutput += mpProcess->readAllStandardOutput();
  mError += mpProcess->readAllStandardError();
  emit finished(this);
}

QString CQPLProcessWorker::formatMessage(const QString & prefix, const QByteArray & message)
{
  return formatMessage(prefix, QString::fromUtf8(message));
}

QString CQPLProcessWorker::formatMessage(const QString & prefix, const QString & message)
{
  QStringList lines = message.split('\n');
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
  emit output(this, formatMessage(mLabel, newOutput));
}

void CQPLProcessWorker::handleStandardError()
{
  auto newError = mpProcess->readAllStandardError();
  mError += newError;
  emit output(this, formatMessage(mLabel, newError));
}

CQPLProcessWidget::CQPLProcessWidget(QWidget * parent)
  : QWidget(parent)
  , mpSettings(nullptr)
{
  setupUi(this);

  // not implemented yet
  mpScrollArea->setVisible(false);
  mpProcessBar->setValue(0);
}

CQPLProcessWidget::~CQPLProcessWidget()
{
  // clean up workers
  for (auto* pWorker : mWorkers)
  {
    pWorker->deleteLater();
  }
  for (auto* pWorker : mAvailableWorkers)
  {
    pWorker->deleteLater();
  }

  mWorkers.clear();
  mAvailableWorkers.clear();
}

void CQPLProcessWidget::loadSettings(const CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  mpSettings = const_cast<CProfileSettings*>(pSettings);

  mpTxtDirectory->setText(FROM_UTF8(pSettings->getDirectory()));
  mpTxtPrefix->setText(FROM_UTF8((*pSettings)["Prefix"].get< std::string >()));
  mpTxtCopasiSE->setText(FROM_UTF8(pSettings->getCopasiSE()));
  mpSpnNumProcesses->setValue((*pSettings)["Num Processes"]);
}

void CQPLProcessWidget::saveSettings(CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  (*pSettings)["Directory"] = TO_UTF8(mpTxtDirectory->text());
  (*pSettings)["Prefix"] = TO_UTF8(mpTxtPrefix->text());
  (*pSettings)["Num Processes"] = mpSpnNumProcesses->value();
  (*pSettings)["CopasiSE"] = TO_UTF8(mpTxtCopasiSE->text());

  pSettings->save();
}

void CQPLProcessWidget::browseCopasiSE()
{
  QString file = QFileDialog::getOpenFileName(this, "Select CopasiSE", mpTxtCopasiSE->text(), "CopasiSE (*.exe CopasiSE);;All files (*.*)");
  if (file.isEmpty())
    return;
  mpTxtCopasiSE->setText(file);
}

void CQPLProcessWidget::browseDirectory()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", mpTxtDirectory->text(), QFileDialog::ShowDirsOnly);
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
  mFiles = globFiles(mpTxtDirectory->text(), mpTxtPrefix->text() + "*profile_*.cps");
  mpTxtOutput->setPlainText(QString("Found %1 files").arg(mFiles.count()));

  if (mFiles.isEmpty())
  {
    mpCmdRun->setEnabled(true);
    return;
  }

  // set up process bar
  mpProcessBar->setRange(0, (int)mFiles.size());
  mpProcessBar->setValue(0);

  // update CopasiSE
  for (int i = 0; i < (int)mAvailableWorkers.count(); ++i)
    {
    mAvailableWorkers[i]->setCopasiSE(mpTxtCopasiSE->text());
    }

  // allocate as many workers as we have specified in num processes
  for (int i = (int)mAvailableWorkers.count(); i < (int)mpSpnNumProcesses->value(); ++i)
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

void CQPLProcessWidget::startNextWorker(CQPLProcessWorker* pCurrentWorker)
{
  if (pCurrentWorker)
    {
      if (!mFiles.isEmpty())
        {
          QString first = mFiles.takeFirst();
          mpTxtOutput->append("start file: " + first);
          pCurrentWorker->start(mpTxtDirectory->text() + "/" + first, first);
        }
      else
        {
          mWorkers.removeAll(pCurrentWorker);
          mAvailableWorkers.push_back(pCurrentWorker);
        }
    }

  if (mFiles.isEmpty() && !mpCmdRun->isEnabled() && mWorkers.isEmpty())
    {
      mpTxtOutput->append("all done");
      mpCmdRun->setEnabled(true);
    }
}

void CQPLProcessWidget::workerFinished(CQPLProcessWorker* pWorker)
{
  if (pWorker)
    mpTxtOutput->append(QString("finished %1 in %2 seconds").arg(pWorker->currentLabel()).arg(pWorker->getRuntime()));

  // increment the process bar
  mpProcessBar->setValue(mpProcessBar->value() + 1);

  // if there are more files process the next one
  startNextWorker(pWorker);
}

void CQPLProcessWidget::workerError(CQPLProcessWorker* pWorker, const QString& error)
{
  // add error to the log
  if (pWorker && !pWorker->wasCancelled())
    mpTxtOutput->append(error);

  startNextWorker(pWorker);
}

void CQPLProcessWidget::workerOutput(CQPLProcessWorker* pWorker, const QString& output)
{
  // add output to the log
  mpTxtOutput->append(output);
}
