// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationResult.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/07 14:12:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQOPTIMIZATIONRESULT_H
#define CQOPTIMIZATIONRESULT_H

#include <qvariant.h>

class COptTask;
class COptProblem;

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "copasiWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CQOptimizationResult
{
public:
  QVBoxLayout *vboxLayout;
  QHBoxLayout *hboxLayout;
  QLabel *mpLblResult;
  QPushButton *mpBtnUpdateModel;
  QPushButton *mpBtnSave;
  QGridLayout *gridLayout;
  QLineEdit *mpEditCPUTime;
  QLineEdit *mpEditEvaluations;
  QLineEdit *mpEditSpeed;
  QLabel *mpLblSpeed;
  QLabel *mpLblEvaluations;
  QLabel *mpLblCPUTime;
  QLabel *mpLblObjectiveValue;
  QLineEdit *mpEditObjectiveValue;
  Q3Table *mpParameters;
  QSpacerItem *mpSpacer;

  void setupUi(CopasiWidget *CQOptimizationResult)
  {
    if (CQOptimizationResult->objectName().isEmpty())
      CQOptimizationResult->setObjectName(QString::fromUtf8("CQOptimizationResult"));

    CQOptimizationResult->resize(568, 306);
    vboxLayout = new QVBoxLayout(CQOptimizationResult);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    mpLblResult = new QLabel(CQOptimizationResult);
    mpLblResult->setObjectName(QString::fromUtf8("mpLblResult"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(5));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mpLblResult->sizePolicy().hasHeightForWidth());
    mpLblResult->setSizePolicy(sizePolicy);
    mpLblResult->setWordWrap(false);

    hboxLayout->addWidget(mpLblResult);

    mpBtnUpdateModel = new QPushButton(CQOptimizationResult);
    mpBtnUpdateModel->setObjectName(QString::fromUtf8("mpBtnUpdateModel"));

    hboxLayout->addWidget(mpBtnUpdateModel);

    mpBtnSave = new QPushButton(CQOptimizationResult);
    mpBtnSave->setObjectName(QString::fromUtf8("mpBtnSave"));

    hboxLayout->addWidget(mpBtnSave);

    vboxLayout->addLayout(hboxLayout);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    mpEditCPUTime = new QLineEdit(CQOptimizationResult);
    mpEditCPUTime->setObjectName(QString::fromUtf8("mpEditCPUTime"));
    mpEditCPUTime->setReadOnly(true);

    gridLayout->addWidget(mpEditCPUTime, 3, 1, 1, 1);

    mpEditEvaluations = new QLineEdit(CQOptimizationResult);
    mpEditEvaluations->setObjectName(QString::fromUtf8("mpEditEvaluations"));
    mpEditEvaluations->setReadOnly(true);

    gridLayout->addWidget(mpEditEvaluations, 3, 0, 1, 1);

    mpEditSpeed = new QLineEdit(CQOptimizationResult);
    mpEditSpeed->setObjectName(QString::fromUtf8("mpEditSpeed"));
    mpEditSpeed->setReadOnly(true);

    gridLayout->addWidget(mpEditSpeed, 3, 2, 1, 1);

    mpLblSpeed = new QLabel(CQOptimizationResult);
    mpLblSpeed->setObjectName(QString::fromUtf8("mpLblSpeed"));
    mpLblSpeed->setWordWrap(false);

    gridLayout->addWidget(mpLblSpeed, 2, 2, 1, 1);

    mpLblEvaluations = new QLabel(CQOptimizationResult);
    mpLblEvaluations->setObjectName(QString::fromUtf8("mpLblEvaluations"));
    mpLblEvaluations->setWordWrap(false);

    gridLayout->addWidget(mpLblEvaluations, 2, 0, 1, 1);

    mpLblCPUTime = new QLabel(CQOptimizationResult);
    mpLblCPUTime->setObjectName(QString::fromUtf8("mpLblCPUTime"));
    mpLblCPUTime->setWordWrap(false);

    gridLayout->addWidget(mpLblCPUTime, 2, 1, 1, 1);

    mpLblObjectiveValue = new QLabel(CQOptimizationResult);
    mpLblObjectiveValue->setObjectName(QString::fromUtf8("mpLblObjectiveValue"));
    mpLblObjectiveValue->setWordWrap(false);

    gridLayout->addWidget(mpLblObjectiveValue, 0, 0, 1, 1);

    mpEditObjectiveValue = new QLineEdit(CQOptimizationResult);
    mpEditObjectiveValue->setObjectName(QString::fromUtf8("mpEditObjectiveValue"));
    mpEditObjectiveValue->setReadOnly(true);

    gridLayout->addWidget(mpEditObjectiveValue, 1, 0, 1, 1);

    vboxLayout->addLayout(gridLayout);

    mpParameters = new Q3Table(CQOptimizationResult);
    mpParameters->setObjectName(QString::fromUtf8("mpParameters"));
    mpParameters->setNumRows(0);
    mpParameters->setNumCols(0);

    vboxLayout->addWidget(mpParameters);

    mpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(mpSpacer);

    retranslateUi(CQOptimizationResult);
    QObject::connect(mpBtnSave, SIGNAL(clicked()), CQOptimizationResult, SLOT(slotSave()));
    QObject::connect(mpBtnUpdateModel, SIGNAL(clicked()), CQOptimizationResult, SLOT(slotUpdateModel()));

    QMetaObject::connectSlotsByName(CQOptimizationResult);
  } // setupUi

  void retranslateUi(CopasiWidget *CQOptimizationResult)
  {
    CQOptimizationResult->setCaption(QApplication::translate("CQOptimizationResult", "Fitting Result", 0, QApplication::UnicodeUTF8));
    mpLblResult->setText(QApplication::translate("CQOptimizationResult", "<h2>Optimization Result</h2>", 0, QApplication::UnicodeUTF8));
    mpBtnUpdateModel->setText(QApplication::translate("CQOptimizationResult", "Update Model", 0, QApplication::UnicodeUTF8));
    mpBtnSave->setText(QApplication::translate("CQOptimizationResult", "save data", 0, QApplication::UnicodeUTF8));
    mpLblSpeed->setText(QApplication::translate("CQOptimizationResult", "Evaluations/second [1/s]", 0, QApplication::UnicodeUTF8));
    mpLblEvaluations->setText(QApplication::translate("CQOptimizationResult", "Function Evaluations", 0, QApplication::UnicodeUTF8));
    mpLblCPUTime->setText(QApplication::translate("CQOptimizationResult", "CPU Time [s]", 0, QApplication::UnicodeUTF8));
    mpLblObjectiveValue->setText(QApplication::translate("CQOptimizationResult", "Objective Value", 0, QApplication::UnicodeUTF8));
    mpParameters->horizontalHeader()->setLabel(0, QApplication::translate("CQOptimizationResult", "Parameter", 0, QApplication::UnicodeUTF8));
    mpParameters->horizontalHeader()->setLabel(1, QApplication::translate("CQOptimizationResult", "Value", 0, QApplication::UnicodeUTF8));
    mpParameters->horizontalHeader()->setLabel(2, QApplication::translate("CQOptimizationResult", "Gradient", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CQOptimizationResult);
  } // retranslateUi
};

namespace Ui
{
class CQOptimizationResult: public Ui_CQOptimizationResult {};
} // namespace Ui

QT_END_NAMESPACE

class CQOptimizationResult : public CopasiWidget, public Ui::CQOptimizationResult
{
  Q_OBJECT

public:
  CQOptimizationResult(QWidget* parent = 0, const char* name = 0);
  ~CQOptimizationResult();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

private:
  const COptProblem * mpProblem;
  const COptTask * mpTask;

  void init();

private slots:
  void slotSave(void);
  void slotUpdateModel();
};

#endif // CQOPTIMIZATIONRESULT_H
