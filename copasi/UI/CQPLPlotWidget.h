#ifndef CQPLPlotWidget_H__
#define CQPLPlotWidget_H__
#include <QWidget>
#include <QString>
#include <QMap>
#include <tuple>

#include "copasi/UI/ui_CQPLPlotWidget.h"
#include <copasi/UI/CQProfileWidget.h>

class QAction;
class QPushButton;
class CProfileSettings;

typedef QMap<QString, std::pair<QString, QString>> QResultMap;

class CQPLPlotWidget : public QWidget
  , public Ui::CQPLPlotWidget, public CQProfileWidget
{

  Q_OBJECT

  QStringList mFiles;
  QResultMap mMap;
  CProfileSettings * mpSettings;

public:
  CQPLPlotWidget(QWidget * parent = 0);

  virtual void loadSettings(const CProfileSettings * pSettings);
  virtual void saveSettings(CProfileSettings * pSettings);

  QResultMap globFiles(const QString& directory, const QString& pattern);

public slots:
  /**
   * browses for a directory with reports to generate plots for
   */
  virtual void browseDirectory();

  /**
   * displays a selection dialog, to add a threshold to display in plots
   */
  virtual void addThreshold();

  /**
   * generates plots for all reports in the selected directory
   */
  virtual void generatePlots();

  /**
   * saves plots as PDF files
   */
  virtual void savePlots();
};

#endif // CQPLPlotWidget_H__
