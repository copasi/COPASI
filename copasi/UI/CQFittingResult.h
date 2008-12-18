// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQFittingResult.h,v $
//   $Revision: 1.8.12.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQFITTINGRESULT_H
#define CQFITTINGRESULT_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <QLabel>

class CFitTask;
class CFitProblem;

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include "CQArrayAnnotationsWidget.h"
#include "CQFittingResultTab1.h"
#include "copasiWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CQFittingResult
  {
  public:
    Q3GridLayout *gridLayout;
    QTabWidget *mpTabWidget;
    CQFittingResultTab1 *mpMain;
    Q3Table *mpParameters;
    Q3Table *mpExperiments;
    Q3Table *mpValues;
    CQArrayAnnotationsWidget *mpCorrelations;
    CQArrayAnnotationsWidget *mpFisherInformation;
    Q3Table *mpCrossValidations;
    Q3Table *mpCrossValidationValues;
    QPushButton *mpBtnSave;
    QLabel *mpLblResult;

    void setupUi(CopasiWidget *CQFittingResult)
    {
      if (CQFittingResult->objectName().isEmpty())
        CQFittingResult->setObjectName(QString::fromUtf8("CQFittingResult"));
      CQFittingResult->resize(401, 253);
      gridLayout = new Q3GridLayout(CQFittingResult);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpTabWidget = new QTabWidget(CQFittingResult);
      mpTabWidget->setObjectName(QString::fromUtf8("mpTabWidget"));
      mpTabWidget->setGeometry(QRect(10, 50, 380, 190));
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(2), static_cast<QSizePolicy::Policy>(5));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(mpTabWidget->sizePolicy().hasHeightForWidth());
      mpTabWidget->setSizePolicy(sizePolicy);
      mpTabWidget->setMinimumSize(QSize(210, 180));
      mpMain = new CQFittingResultTab1();
      mpMain->setObjectName(QString::fromUtf8("mpMain"));
      mpTabWidget->addTab(mpMain, QString());
      mpParameters = new Q3Table();
      mpParameters->setObjectName(QString::fromUtf8("mpParameters"));
      mpTabWidget->addTab(mpParameters, QString());
      mpExperiments = new Q3Table();
      mpExperiments->setObjectName(QString::fromUtf8("mpExperiments"));
      mpTabWidget->addTab(mpExperiments, QString());
      mpValues = new Q3Table();
      mpValues->setObjectName(QString::fromUtf8("mpValues"));
      mpTabWidget->addTab(mpValues, QString());
      mpCorrelations = new CQArrayAnnotationsWidget();
      mpCorrelations->setObjectName(QString::fromUtf8("mpCorrelations"));
      mpTabWidget->addTab(mpCorrelations, QString());
      mpFisherInformation = new CQArrayAnnotationsWidget();
      mpFisherInformation->setObjectName(QString::fromUtf8("mpFisherInformation"));
      mpTabWidget->addTab(mpFisherInformation, QString());
      mpCrossValidations = new Q3Table();
      mpCrossValidations->setObjectName(QString::fromUtf8("mpCrossValidations"));
      mpTabWidget->addTab(mpCrossValidations, QString());
      mpCrossValidationValues = new Q3Table();
      mpCrossValidationValues->setObjectName(QString::fromUtf8("mpCrossValidationValues"));
      mpTabWidget->addTab(mpCrossValidationValues, QString());

      gridLayout->addWidget(mpTabWidget, 1, 0, 1, 2);

      mpBtnSave = new QPushButton(CQFittingResult);
      mpBtnSave->setObjectName(QString::fromUtf8("mpBtnSave"));
      mpBtnSave->setGeometry(QRect(290, 10, 101, 31));

      gridLayout->addWidget(mpBtnSave, 0, 1, 1, 1);

      mpLblResult = new QLabel(CQFittingResult);
      mpLblResult->setObjectName(QString::fromUtf8("mpLblResult"));
      mpLblResult->setGeometry(QRect(10, 10, 260, 31));
      QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(5));
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(mpLblResult->sizePolicy().hasHeightForWidth());
      mpLblResult->setSizePolicy(sizePolicy1);
      mpLblResult->setWordWrap(false);

      gridLayout->addWidget(mpLblResult, 0, 0, 1, 1);

      retranslateUi(CQFittingResult);
      QObject::connect(mpBtnSave, SIGNAL(clicked()), CQFittingResult, SLOT(slotSave()));

      QMetaObject::connectSlotsByName(CQFittingResult);
    } // setupUi

    void retranslateUi(CopasiWidget *CQFittingResult)
    {
      CQFittingResult->setCaption(QApplication::translate("CQFittingResult", "Fitting Result", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpMain), QApplication::translate("CQFittingResult", "Main", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpParameters), QApplication::translate("CQFittingResult", "Parameters", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpExperiments), QApplication::translate("CQFittingResult", "Experiments", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpValues), QApplication::translate("CQFittingResult", "Fitted Values", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpCorrelations), QApplication::translate("CQFittingResult", "Correlation", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpFisherInformation), QApplication::translate("CQFittingResult", "Fisher Information", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpCrossValidations), QApplication::translate("CQFittingResult", "CV Experiments", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpCrossValidationValues), QApplication::translate("CQFittingResult", "CV Fitted Values", 0, QApplication::UnicodeUTF8));
      mpBtnSave->setText(QApplication::translate("CQFittingResult", "save data", 0, QApplication::UnicodeUTF8));
      mpLblResult->setText(QApplication::translate("CQFittingResult", "<h2>Parameter Estimation Result</h2>", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQFittingResult);
    } // retranslateUi
  };

namespace Ui
  {
  class CQFittingResult: public Ui_CQFittingResult {};
} // namespace Ui

QT_END_NAMESPACE

class CQFittingResult : public CopasiWidget, public Ui::CQFittingResult
  {
    Q_OBJECT

  public:
    CQFittingResult(QWidget* parent = 0, const char* name = 0);
    ~CQFittingResult();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key);

  protected slots:
    virtual void languageChange();

  private:
    const CFitTask * mpTask;
    const CFitProblem * mpProblem;

    void init();

  private slots:
    void slotSave();
  };

#endif // CQFITTINGRESULT_H
