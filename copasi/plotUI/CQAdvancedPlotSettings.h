// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQADVANCEDPLOTSETTINGS_H
#define CQADVANCEDPLOTSETTINGS_H

#include <QWidget>

namespace Ui
{
class CQAdvancedPlotSettings;
}

class CPlotSpecification;

class CQAdvancedPlotSettings : public QWidget
{
  Q_OBJECT

public:
  explicit CQAdvancedPlotSettings(QWidget *parent = nullptr);
  ~CQAdvancedPlotSettings();

  void loadFromPlotSpec(const CPlotSpecification * pspec);
  void saveToPlotSpec(CPlotSpecification * pspec);

private:
  Ui::CQAdvancedPlotSettings *ui;
};

#endif // CQADVANCEDPLOTSETTINGS_H
