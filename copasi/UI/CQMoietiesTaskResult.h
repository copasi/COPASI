// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQMoietiesTaskResult.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:47:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMOIETIESTASKRESULT_H
#define CQMOIETIESTASKRESULT_H

#include <qvariant.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3GridLayout>
#include <QLabel>

class QSignalMapper;
class CMoietiesTask;

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
#include "copasiWidget.h"

class Ui_CQMoietiesTaskResult
{
public:
  Q3GridLayout *gridLayout;
  QTabWidget *mpTabWidget;
  Q3Table *mpMoieties;
  CQArrayAnnotationsWidget *mpStoichiometry;
  CQArrayAnnotationsWidget *mpLinkMatrix;
  CQArrayAnnotationsWidget *mpReducedStoichiometry;
  QLabel *mpLblResult;
  QPushButton *mpBtnSave;

  void setupUi(CopasiWidget *CQMoietiesTaskResult)
  {
    if (CQMoietiesTaskResult->objectName().isEmpty())
      CQMoietiesTaskResult->setObjectName(QString::fromUtf8("CQMoietiesTaskResult"));

    CQMoietiesTaskResult->resize(337, 237);
    gridLayout = new Q3GridLayout(CQMoietiesTaskResult);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    mpTabWidget = new QTabWidget(CQMoietiesTaskResult);
    mpTabWidget->setObjectName(QString::fromUtf8("mpTabWidget"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(2), static_cast<QSizePolicy::Policy>(5));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mpTabWidget->sizePolicy().hasHeightForWidth());
    mpTabWidget->setSizePolicy(sizePolicy);
    mpTabWidget->setMinimumSize(QSize(210, 180));
    mpMoieties = new Q3Table();
    mpMoieties->setObjectName(QString::fromUtf8("mpMoieties"));
    mpTabWidget->addTab(mpMoieties, QString());
    mpStoichiometry = new CQArrayAnnotationsWidget();
    mpStoichiometry->setObjectName(QString::fromUtf8("mpStoichiometry"));
    mpTabWidget->addTab(mpStoichiometry, QString());
    mpLinkMatrix = new CQArrayAnnotationsWidget();
    mpLinkMatrix->setObjectName(QString::fromUtf8("mpLinkMatrix"));
    mpTabWidget->addTab(mpLinkMatrix, QString());
    mpReducedStoichiometry = new CQArrayAnnotationsWidget();
    mpReducedStoichiometry->setObjectName(QString::fromUtf8("mpReducedStoichiometry"));
    mpTabWidget->addTab(mpReducedStoichiometry, QString());

    gridLayout->addWidget(mpTabWidget, 1, 0, 1, 2);

    mpLblResult = new QLabel(CQMoietiesTaskResult);
    mpLblResult->setObjectName(QString::fromUtf8("mpLblResult"));
    QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(5));
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(mpLblResult->sizePolicy().hasHeightForWidth());
    mpLblResult->setSizePolicy(sizePolicy1);
    mpLblResult->setWordWrap(false);

    gridLayout->addWidget(mpLblResult, 0, 0, 1, 1);

    mpBtnSave = new QPushButton(CQMoietiesTaskResult);
    mpBtnSave->setObjectName(QString::fromUtf8("mpBtnSave"));

    gridLayout->addWidget(mpBtnSave, 0, 1, 1, 1);

    retranslateUi(CQMoietiesTaskResult);
    QObject::connect(mpBtnSave, SIGNAL(clicked()), CQMoietiesTaskResult, SLOT(slotSave()));

    QMetaObject::connectSlotsByName(CQMoietiesTaskResult);
  } // setupUi

  void retranslateUi(CopasiWidget *CQMoietiesTaskResult)
  {
    CQMoietiesTaskResult->setCaption(QApplication::translate("CQMoietiesTaskResult", "Moieties Result", 0, QApplication::UnicodeUTF8));
    mpTabWidget->setTabText(mpTabWidget->indexOf(mpMoieties), QApplication::translate("CQMoietiesTaskResult", "Moieties", 0, QApplication::UnicodeUTF8));
    mpTabWidget->setTabText(mpTabWidget->indexOf(mpStoichiometry), QApplication::translate("CQMoietiesTaskResult", "Stoichiometry", 0, QApplication::UnicodeUTF8));
    mpTabWidget->setTabText(mpTabWidget->indexOf(mpLinkMatrix), QApplication::translate("CQMoietiesTaskResult", "Link Matrix", 0, QApplication::UnicodeUTF8));
    mpTabWidget->setTabText(mpTabWidget->indexOf(mpReducedStoichiometry), QApplication::translate("CQMoietiesTaskResult", "Reduced Stoichiometry", 0, QApplication::UnicodeUTF8));
    mpLblResult->setText(QApplication::translate("CQMoietiesTaskResult", "<h2>Moieties Result</h2>", 0, QApplication::UnicodeUTF8));
    mpBtnSave->setText(QApplication::translate("CQMoietiesTaskResult", "save data", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CQMoietiesTaskResult);
  } // retranslateUi
};

namespace Ui
{
class CQMoietiesTaskResult: public Ui_CQMoietiesTaskResult {};
} // namespace Ui

class CQMoietiesTaskResult : public CopasiWidget, public Ui::CQMoietiesTaskResult
{
  Q_OBJECT

public:
  CQMoietiesTaskResult(QWidget* parent = 0, const char* name = 0);
  ~CQMoietiesTaskResult();

  virtual bool leave();
  void load();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();
  QPixmap mToolBtn;
  QSignalMapper * mpToolBtnMap;
  CMoietiesTask * mpMoietiesTask;

protected slots:
  virtual void languageChange();

private:
  void init();

private slots:
  void slotSave(void);
  void slotCreateGlobalQuantity(int row);
};

#endif // CQMOIETIESTASKRESULT_H
