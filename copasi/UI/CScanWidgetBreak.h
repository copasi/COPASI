// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetBreak.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:48:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CSCANWIDGETBREAK_H
#define CSCANWIDGETBREAK_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class CCopasiParameterGroup;
class CScanProblem;

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QComboBox>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>

class Ui_CScanWidgetBreak
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3Frame *frame;
    Q3GridLayout *gridLayout;
    QComboBox *comboBoxReport;
    QLabel *textLabelReport;
    QComboBox *comboBoxPlot;
    QLabel *labelTitle;
    QLabel *textLabelPlot;
    QSpacerItem *spacer1;

    void setupUi(QWidget *CScanWidgetBreak)
    {
      if (CScanWidgetBreak->objectName().isEmpty())
        CScanWidgetBreak->setObjectName(QString::fromUtf8("CScanWidgetBreak"));
      CScanWidgetBreak->resize(420, 74);
      vboxLayout = new Q3VBoxLayout(CScanWidgetBreak);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(5);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      frame = new Q3Frame(CScanWidgetBreak);
      frame->setObjectName(QString::fromUtf8("frame"));
      frame->setFrameShape(Q3Frame::StyledPanel);
      frame->setFrameShadow(Q3Frame::Raised);
      gridLayout = new Q3GridLayout(frame);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(6);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      comboBoxReport = new QComboBox(frame);
      comboBoxReport->setObjectName(QString::fromUtf8("comboBoxReport"));
      comboBoxReport->setEnabled(false);
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(comboBoxReport->sizePolicy().hasHeightForWidth());
      comboBoxReport->setSizePolicy(sizePolicy);

      gridLayout->addWidget(comboBoxReport, 0, 3, 1, 1);

      textLabelReport = new QLabel(frame);
      textLabelReport->setObjectName(QString::fromUtf8("textLabelReport"));
      textLabelReport->setEnabled(false);
      textLabelReport->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      textLabelReport->setWordWrap(false);

      gridLayout->addWidget(textLabelReport, 0, 2, 1, 1);

      comboBoxPlot = new QComboBox(frame);
      comboBoxPlot->setObjectName(QString::fromUtf8("comboBoxPlot"));
      comboBoxPlot->setEnabled(false);
      sizePolicy.setHeightForWidth(comboBoxPlot->sizePolicy().hasHeightForWidth());
      comboBoxPlot->setSizePolicy(sizePolicy);

      gridLayout->addWidget(comboBoxPlot, 1, 3, 1, 1);

      labelTitle = new QLabel(frame);
      labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
      labelTitle->setWordWrap(false);

      gridLayout->addWidget(labelTitle, 0, 0, 2, 1);

      textLabelPlot = new QLabel(frame);
      textLabelPlot->setObjectName(QString::fromUtf8("textLabelPlot"));
      textLabelPlot->setEnabled(false);
      textLabelPlot->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      textLabelPlot->setWordWrap(false);

      gridLayout->addWidget(textLabelPlot, 1, 2, 1, 1);

      spacer1 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

      gridLayout->addItem(spacer1, 0, 1, 2, 1);

      vboxLayout->addWidget(frame);

      retranslateUi(CScanWidgetBreak);

      QMetaObject::connectSlotsByName(CScanWidgetBreak);
    } // setupUi

    void retranslateUi(QWidget *CScanWidgetBreak)
    {
      CScanWidgetBreak->setWindowTitle(QApplication::translate("CScanWidgetBreak", "Form1", 0, QApplication::UnicodeUTF8));
      comboBoxReport->clear();
      comboBoxReport->insertItems(0, QStringList()
                                  << QApplication::translate("CScanWidgetBreak", "empty line", 0, QApplication::UnicodeUTF8)
                                  << QApplication::translate("CScanWidgetBreak", "page break", 0, QApplication::UnicodeUTF8)
                                  << QApplication::translate("CScanWidgetBreak", "new file", 0, QApplication::UnicodeUTF8)
                                  << QApplication::translate("CScanWidgetBreak", "no break", 0, QApplication::UnicodeUTF8)
);
      textLabelReport->setText(QApplication::translate("CScanWidgetBreak", "for reports:", 0, QApplication::UnicodeUTF8));
      comboBoxPlot->clear();
      comboBoxPlot->insertItems(0, QStringList()
                                << QApplication::translate("CScanWidgetBreak", "new curve", 0, QApplication::UnicodeUTF8)
                                << QApplication::translate("CScanWidgetBreak", "new plot window", 0, QApplication::UnicodeUTF8)
                                << QApplication::translate("CScanWidgetBreak", "no break", 0, QApplication::UnicodeUTF8)
);
      labelTitle->setText(QApplication::translate("CScanWidgetBreak", "<h2>Output separator</h2>", 0, QApplication::UnicodeUTF8));
      textLabelPlot->setText(QApplication::translate("CScanWidgetBreak", "for plots:", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CScanWidgetBreak);
    } // retranslateUi
  };

namespace Ui
  {
  class CScanWidgetBreak: public Ui_CScanWidgetBreak {};
} // namespace Ui

class CScanWidgetBreak : public QWidget, public Ui::CScanWidgetBreak
  {
    Q_OBJECT

  public:
    CScanWidgetBreak(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CScanWidgetBreak();

    virtual bool initFromScanItem(CCopasiParameterGroup * pg);
    virtual bool saveToScanItem(CScanProblem * pg) const;

  protected slots:
    virtual void languageChange();

  private:
    void init();
  };

#endif // CSCANWIDGETBREAK_H
