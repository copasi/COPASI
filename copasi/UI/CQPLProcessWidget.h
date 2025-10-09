#ifndef CQPLProcessWidget_H__
#define CQPLProcessWidget_H__

#include <QWidget>
#include <QObject>
#include <QProcess>

#include "copasi/UI/ui_CQPLProcessWidget.h"
#include <copasi/UI/CQProfileWidget.h>

class QAction;
class QPushButton;
class CProfileSettings;

class CQPLProcessWorker : public QObject
{
  Q_OBJECT

public:
  CQPLProcessWorker(const QString& program);
  virtual ~CQPLProcessWorker();

  void start(const QString& copasiFile);
  void cancel();
  void kill();

  const QString& currentFile() const;
  
signals:
  void finished(CQPLProcessWorker* pWorker);
  void errorOccurred(CQPLProcessWorker* pWorker, const QString& error);
  void output(CQPLProcessWorker* pWorker, const QString& output);

private slots:
  void handleProcessError(QProcess::ProcessError error);
  void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
  void handleStandardOutput();
  void handleStandardError();

private:
  QProcess* mpProcess;
  QString mCopasiSE;
  QString mCurrentFile;
  bool mCancelled;
};


class CQPLProcessWidget : public QWidget
  , public Ui::CQPLProcessWidget, public CQProfileWidget
{

  Q_OBJECT

  QList<CQPLProcessWorker*> mWorkers;
  QList<CQPLProcessWorker*> mAvailableWorkers;
  QStringList mFiles;

public:
  CQPLProcessWidget(QWidget * parent = 0);

  virtual void loadSettings(const CProfileSettings * pSettings);
  virtual void saveSettings(CProfileSettings * pSettings);

  QStringList globFiles(const QString& directory, const QString& pattern);

public slots:
  /**
   * browses for a directory to process files in
   */
  virtual void browseDirectory();

  /**
   * processes all files in the selected directory
   */
  virtual void processDirectory();

  /**
   * browses for the copasiSE executable
   */
  virtual void browseCopasiSE();

  /**
   * Cancels all running processes
   */
  virtual void cancelRun();

  /**
   * @brief handles the finished signal from a worker
   * 
   * @param pWorker 
   */
  void workerFinished(CQPLProcessWorker* pWorker);

  /**
   * @brief handles the error signal from a worker
   * 
   * @param pWorker 
   * @param error 
   */
  void workerError(CQPLProcessWorker* pWorker, const QString& error);

  /**
   * @brief handles the output signal from a worker
   * 
   * @param pWorker 
   * @param output 
   */
  void workerOutput(CQPLProcessWorker* pWorker, const QString& output);

};

#endif // CQPLProcessWidget_H__
