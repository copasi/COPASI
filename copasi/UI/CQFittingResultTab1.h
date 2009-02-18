// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:46:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQFITTINGRESULTTAB1_H
#define CQFITTINGRESULTTAB1_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3VBoxLayout>
#include <QLabel>

class CFitProblem;

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>

class Ui_CQFittingResultTab1
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3GridLayout *gridLayout;
    QLineEdit *mpEditRMS;
    QLineEdit *mpEditStdDeviation;
    QLabel *mpLblRMS;
    QLineEdit *mpEditEvaluations;
    QLabel *mpLblCPUTime;
    QLabel *mpLblCVObjectiveValue;
    QLabel *mpLblCVStdDeviation;
    QLabel *mpLblStdDeviation;
    QLabel *mpLblCVRMS;
    QLabel *mpLblEvaluations;
    QLineEdit *mpEditSpeed;
    QLineEdit *mpEditCPUTime;
    QLineEdit *mpEditCVObjectiveValue;
    QLabel *mpLblObjectiveValue;
    QLineEdit *mpEditCVRMS;
    QLineEdit *mpEditCVStdDeviation;
    QLineEdit *mpEditObjectiveValue;
    QLabel *mpLblSpeed;
    QSpacerItem *mpSpacer;

    void setupUi(QWidget *CQFittingResultTab1)
    {
      if (CQFittingResultTab1->objectName().isEmpty())
        CQFittingResultTab1->setObjectName(QString::fromUtf8("CQFittingResultTab1"));
      CQFittingResultTab1->resize(362, 264);
      vboxLayout = new Q3VBoxLayout(CQFittingResultTab1);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      gridLayout = new Q3GridLayout(1, 1);
      gridLayout->setSpacing(6);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpEditRMS = new QLineEdit(CQFittingResultTab1);
      mpEditRMS->setObjectName(QString::fromUtf8("mpEditRMS"));
      mpEditRMS->setReadOnly(true);

      gridLayout->addWidget(mpEditRMS, 1, 1, 1, 1);

      mpEditStdDeviation = new QLineEdit(CQFittingResultTab1);
      mpEditStdDeviation->setObjectName(QString::fromUtf8("mpEditStdDeviation"));
      mpEditStdDeviation->setReadOnly(true);

      gridLayout->addWidget(mpEditStdDeviation, 1, 2, 1, 1);

      mpLblRMS = new QLabel(CQFittingResultTab1);
      mpLblRMS->setObjectName(QString::fromUtf8("mpLblRMS"));
      mpLblRMS->setWordWrap(false);

      gridLayout->addWidget(mpLblRMS, 0, 1, 1, 1);

      mpEditEvaluations = new QLineEdit(CQFittingResultTab1);
      mpEditEvaluations->setObjectName(QString::fromUtf8("mpEditEvaluations"));
      mpEditEvaluations->setReadOnly(true);

      gridLayout->addWidget(mpEditEvaluations, 5, 0, 1, 1);

      mpLblCPUTime = new QLabel(CQFittingResultTab1);
      mpLblCPUTime->setObjectName(QString::fromUtf8("mpLblCPUTime"));
      mpLblCPUTime->setWordWrap(false);

      gridLayout->addWidget(mpLblCPUTime, 4, 1, 1, 1);

      mpLblCVObjectiveValue = new QLabel(CQFittingResultTab1);
      mpLblCVObjectiveValue->setObjectName(QString::fromUtf8("mpLblCVObjectiveValue"));
      mpLblCVObjectiveValue->setWordWrap(false);

      gridLayout->addWidget(mpLblCVObjectiveValue, 2, 0, 1, 1);

      mpLblCVStdDeviation = new QLabel(CQFittingResultTab1);
      mpLblCVStdDeviation->setObjectName(QString::fromUtf8("mpLblCVStdDeviation"));
      mpLblCVStdDeviation->setWordWrap(false);

      gridLayout->addWidget(mpLblCVStdDeviation, 2, 2, 1, 1);

      mpLblStdDeviation = new QLabel(CQFittingResultTab1);
      mpLblStdDeviation->setObjectName(QString::fromUtf8("mpLblStdDeviation"));
      mpLblStdDeviation->setWordWrap(false);

      gridLayout->addWidget(mpLblStdDeviation, 0, 2, 1, 1);

      mpLblCVRMS = new QLabel(CQFittingResultTab1);
      mpLblCVRMS->setObjectName(QString::fromUtf8("mpLblCVRMS"));
      mpLblCVRMS->setWordWrap(false);

      gridLayout->addWidget(mpLblCVRMS, 2, 1, 1, 1);

      mpLblEvaluations = new QLabel(CQFittingResultTab1);
      mpLblEvaluations->setObjectName(QString::fromUtf8("mpLblEvaluations"));
      mpLblEvaluations->setWordWrap(false);

      gridLayout->addWidget(mpLblEvaluations, 4, 0, 1, 1);

      mpEditSpeed = new QLineEdit(CQFittingResultTab1);
      mpEditSpeed->setObjectName(QString::fromUtf8("mpEditSpeed"));
      mpEditSpeed->setReadOnly(true);

      gridLayout->addWidget(mpEditSpeed, 5, 2, 1, 1);

      mpEditCPUTime = new QLineEdit(CQFittingResultTab1);
      mpEditCPUTime->setObjectName(QString::fromUtf8("mpEditCPUTime"));
      mpEditCPUTime->setReadOnly(true);

      gridLayout->addWidget(mpEditCPUTime, 5, 1, 1, 1);

      mpEditCVObjectiveValue = new QLineEdit(CQFittingResultTab1);
      mpEditCVObjectiveValue->setObjectName(QString::fromUtf8("mpEditCVObjectiveValue"));
      mpEditCVObjectiveValue->setReadOnly(true);

      gridLayout->addWidget(mpEditCVObjectiveValue, 3, 0, 1, 1);

      mpLblObjectiveValue = new QLabel(CQFittingResultTab1);
      mpLblObjectiveValue->setObjectName(QString::fromUtf8("mpLblObjectiveValue"));
      mpLblObjectiveValue->setWordWrap(false);

      gridLayout->addWidget(mpLblObjectiveValue, 0, 0, 1, 1);

      mpEditCVRMS = new QLineEdit(CQFittingResultTab1);
      mpEditCVRMS->setObjectName(QString::fromUtf8("mpEditCVRMS"));
      mpEditCVRMS->setReadOnly(true);

      gridLayout->addWidget(mpEditCVRMS, 3, 1, 1, 1);

      mpEditCVStdDeviation = new QLineEdit(CQFittingResultTab1);
      mpEditCVStdDeviation->setObjectName(QString::fromUtf8("mpEditCVStdDeviation"));
      mpEditCVStdDeviation->setReadOnly(true);

      gridLayout->addWidget(mpEditCVStdDeviation, 3, 2, 1, 1);

      mpEditObjectiveValue = new QLineEdit(CQFittingResultTab1);
      mpEditObjectiveValue->setObjectName(QString::fromUtf8("mpEditObjectiveValue"));
      mpEditObjectiveValue->setReadOnly(true);

      gridLayout->addWidget(mpEditObjectiveValue, 1, 0, 1, 1);

      mpLblSpeed = new QLabel(CQFittingResultTab1);
      mpLblSpeed->setObjectName(QString::fromUtf8("mpLblSpeed"));
      mpLblSpeed->setWordWrap(false);

      gridLayout->addWidget(mpLblSpeed, 4, 2, 1, 1);

      vboxLayout->addLayout(gridLayout);

      mpSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout->addItem(mpSpacer);

      retranslateUi(CQFittingResultTab1);

      QMetaObject::connectSlotsByName(CQFittingResultTab1);
    } // setupUi

    void retranslateUi(QWidget *CQFittingResultTab1)
    {
      CQFittingResultTab1->setWindowTitle(QApplication::translate("CQFittingResultTab1", "CQFittingResultTab1", 0, QApplication::UnicodeUTF8));
      mpLblRMS->setText(QApplication::translate("CQFittingResultTab1", "Root Mean Square", 0, QApplication::UnicodeUTF8));
      mpLblCPUTime->setText(QApplication::translate("CQFittingResultTab1", "CPU Time [s]", 0, QApplication::UnicodeUTF8));
      mpLblCVObjectiveValue->setText(QApplication::translate("CQFittingResultTab1", "CV Objective Value", 0, QApplication::UnicodeUTF8));
      mpLblCVStdDeviation->setText(QApplication::translate("CQFittingResultTab1", "CV Standard Deviation", 0, QApplication::UnicodeUTF8));
      mpLblStdDeviation->setText(QApplication::translate("CQFittingResultTab1", "Standard Deviation", 0, QApplication::UnicodeUTF8));
      mpLblCVRMS->setText(QApplication::translate("CQFittingResultTab1", "CV Root Mean Square", 0, QApplication::UnicodeUTF8));
      mpLblEvaluations->setText(QApplication::translate("CQFittingResultTab1", "Function Evaluations", 0, QApplication::UnicodeUTF8));
      mpLblObjectiveValue->setText(QApplication::translate("CQFittingResultTab1", "Objective Value", 0, QApplication::UnicodeUTF8));
      mpLblSpeed->setText(QApplication::translate("CQFittingResultTab1", "Evaluations/second [1/s]", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQFittingResultTab1);
    } // retranslateUi
  };

namespace Ui
  {
  class CQFittingResultTab1: public Ui_CQFittingResultTab1 {};
} // namespace Ui

class CQFittingResultTab1 : public QWidget, public Ui::CQFittingResultTab1
  {
    Q_OBJECT

  public:
    CQFittingResultTab1(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CQFittingResultTab1();

    void load(const CFitProblem * pProblem);

  protected slots:
    virtual void languageChange();

  private:
    void init();
  };

#endif // CQFITTINGRESULTTAB1_H
