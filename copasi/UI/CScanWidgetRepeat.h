// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRepeat.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:48:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CSCANWIDGETREPEAT_H
#define CSCANWIDGETREPEAT_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
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
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>

class Ui_CScanWidgetRepeat
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3Frame *frame;
    Q3HBoxLayout *hboxLayout;
    QLabel *labelTitle;
    QSpacerItem *spacer1;
    QLabel *labelNumber;
    QLineEdit *lineEditNumber;

    void setupUi(QWidget *CScanWidgetRepeat)
    {
      if (CScanWidgetRepeat->objectName().isEmpty())
        CScanWidgetRepeat->setObjectName(QString::fromUtf8("CScanWidgetRepeat"));
      CScanWidgetRepeat->resize(446, 54);
      vboxLayout = new Q3VBoxLayout(CScanWidgetRepeat);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(5);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      frame = new Q3Frame(CScanWidgetRepeat);
      frame->setObjectName(QString::fromUtf8("frame"));
      frame->setFrameShape(Q3Frame::StyledPanel);
      frame->setFrameShadow(Q3Frame::Raised);
      hboxLayout = new Q3HBoxLayout(frame);
      hboxLayout->setSpacing(6);
      hboxLayout->setMargin(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      labelTitle = new QLabel(frame);
      labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
      labelTitle->setAlignment(Qt::AlignVCenter);
      labelTitle->setWordWrap(true);

      hboxLayout->addWidget(labelTitle);

      spacer1 = new QSpacerItem(20, 16, QSizePolicy::Maximum, QSizePolicy::Minimum);

      hboxLayout->addItem(spacer1);

      labelNumber = new QLabel(frame);
      labelNumber->setObjectName(QString::fromUtf8("labelNumber"));
      labelNumber->setWordWrap(false);

      hboxLayout->addWidget(labelNumber);

      lineEditNumber = new QLineEdit(frame);
      lineEditNumber->setObjectName(QString::fromUtf8("lineEditNumber"));

      hboxLayout->addWidget(lineEditNumber);

      vboxLayout->addWidget(frame);

      retranslateUi(CScanWidgetRepeat);

      QMetaObject::connectSlotsByName(CScanWidgetRepeat);
    } // setupUi

    void retranslateUi(QWidget *CScanWidgetRepeat)
    {
      CScanWidgetRepeat->setWindowTitle(QApplication::translate("CScanWidgetRepeat", "Form1", 0, QApplication::UnicodeUTF8));
      labelTitle->setText(QApplication::translate("CScanWidgetRepeat", "<h2>Repeat</h2>", 0, QApplication::UnicodeUTF8));
      labelNumber->setText(QApplication::translate("CScanWidgetRepeat", "Number of iterations", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CScanWidgetRepeat);
    } // retranslateUi
  };

namespace Ui
  {
  class CScanWidgetRepeat: public Ui_CScanWidgetRepeat {};
} // namespace Ui

class CScanWidgetRepeat : public QWidget, public Ui::CScanWidgetRepeat
  {
    Q_OBJECT

  public:
    CScanWidgetRepeat(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CScanWidgetRepeat();

    virtual bool initFromScanItem(CCopasiParameterGroup * pg);
    virtual bool saveToScanItem(CScanProblem * pg) const;

  protected slots:
    virtual void languageChange();

  private:
    void init();
  };

#endif // CSCANWIDGETREPEAT_H
