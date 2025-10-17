#include "CQPLProcessWidget.h"
#include "copasi/utilities/CProfileSettings.h"
#include "qtUtilities.h"

#include <QFileDialog>

CQPLProcessWorker::CQPLProcessWorker(const QString& program)
{
  mpProcess = new QProcess(this);
  mCopasiSE = program;
  connect(mpProcess, &QProcess::errorOccurred, this, &CQPLProcessWorker::handleProcessError);
  connect(mpProcess, &QProcess::finished, this, &CQPLProcessWorker::handleProcessFinished);
  connect(mpProcess, &QProcess::readyReadStandardOutput, this, &CQPLProcessWorker::handleStandardOutput);
  connect(mpProcess, &QProcess::readyReadStandardError, this, &CQPLProcessWorker::handleStandardError);
  mCancelled = false;
}

CQPLProcessWorker::~CQPLProcessWorker()
{
  delete mpProcess;
}

void CQPLProcessWorker::start(const QString& cpsFile)
{
  mCurrentFile = cpsFile;
  mpProcess->start(mCopasiSE, QStringList() << "--nologo" << cpsFile);
}

const QString& CQPLProcessWorker::currentFile() const
{
  return mCurrentFile;
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

void CQPLProcessWorker::handleProcessError(QProcess::ProcessError error)
{
  emit errorOccurred(this, QString("Process error: %1").arg(error));
}

void CQPLProcessWorker::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  emit finished(this);
}

void CQPLProcessWorker::handleStandardOutput()
{
  emit output(this, mpProcess->readAllStandardOutput());
}

void CQPLProcessWorker::handleStandardError()
{
  emit output(this, mpProcess->readAllStandardError());
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
  auto list = dir.entryList();
  // remove tmp files
  list.removeIf([](const QString & s) { return s.startsWith("tmp__"); });
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
    pWorker->start(mpTxtDirectory->text() + "/" + file);
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
  
  mpTxtOutput->append(QString("finished %1").arg(pWorker->currentFile()));
  
  // increment the process bar
  mpProcessBar->setValue(mpProcessBar->value() + 1);

  // if there are more files process the next one
  if (!mFiles.isEmpty())
  {
    mpTxtOutput->append("start file ...");
    pWorker->start(mpTxtDirectory->text() + "/" + mFiles.takeFirst());
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
