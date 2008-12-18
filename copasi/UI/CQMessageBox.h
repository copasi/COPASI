// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMessageBox.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMESSAGEBOX_H
#define CQMESSAGEBOX_H

#include <qvariant.h>

#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <QCloseEvent>
#include <Q3GridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <Q3VBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CQMessageBox
  {
  public:
    Q3GridLayout *gridLayout;
    Q3HBoxLayout *hboxLayout;
    QPushButton *mpBtn0;
    QPushButton *mpBtn1;
    QPushButton *mpBtn2;
    QPushButton *mpBtn3;
    Q3VBoxLayout *vboxLayout;
    QLabel *mpLblIcon;
    QSpacerItem *mpSpacerIcon;
    QTabWidget *mpTabWidget;
    QWidget *tab;
    Q3HBoxLayout *hboxLayout1;
    Q3TextEdit *mpMessage;
    QWidget *tab1;
    Q3GridLayout *gridLayout1;
    Q3TextEdit *mpFilteredMessage;

    void setupUi(QDialog *CQMessageBox)
    {
      if (CQMessageBox->objectName().isEmpty())
        CQMessageBox->setObjectName(QString::fromUtf8("CQMessageBox"));
      CQMessageBox->resize(648, 324);
      CQMessageBox->setSizeGripEnabled(true);
      gridLayout = new Q3GridLayout(CQMessageBox);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpBtn0 = new QPushButton(CQMessageBox);
      mpBtn0->setObjectName(QString::fromUtf8("mpBtn0"));
      mpBtn0->setAutoDefault(true);

      hboxLayout->addWidget(mpBtn0);

      mpBtn1 = new QPushButton(CQMessageBox);
      mpBtn1->setObjectName(QString::fromUtf8("mpBtn1"));
      mpBtn1->setAutoDefault(true);
      mpBtn1->setDefault(true);

      hboxLayout->addWidget(mpBtn1);

      mpBtn2 = new QPushButton(CQMessageBox);
      mpBtn2->setObjectName(QString::fromUtf8("mpBtn2"));
      mpBtn2->setAutoDefault(true);

      hboxLayout->addWidget(mpBtn2);

      mpBtn3 = new QPushButton(CQMessageBox);
      mpBtn3->setObjectName(QString::fromUtf8("mpBtn3"));
      mpBtn3->setAutoDefault(true);

      hboxLayout->addWidget(mpBtn3);

      gridLayout->addLayout(hboxLayout, 1, 0, 1, 2);

      vboxLayout = new Q3VBoxLayout();
      vboxLayout->setSpacing(6);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      mpLblIcon = new QLabel(CQMessageBox);
      mpLblIcon->setObjectName(QString::fromUtf8("mpLblIcon"));
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(mpLblIcon->sizePolicy().hasHeightForWidth());
      mpLblIcon->setSizePolicy(sizePolicy);
      mpLblIcon->setAlignment(Qt::AlignTop);
      mpLblIcon->setWordWrap(false);

      vboxLayout->addWidget(mpLblIcon);

      mpSpacerIcon = new QSpacerItem(0, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout->addItem(mpSpacerIcon);

      gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);

      mpTabWidget = new QTabWidget(CQMessageBox);
      mpTabWidget->setObjectName(QString::fromUtf8("mpTabWidget"));
      tab = new QWidget();
      tab->setObjectName(QString::fromUtf8("tab"));
      hboxLayout1 = new Q3HBoxLayout(tab);
      hboxLayout1->setSpacing(6);
      hboxLayout1->setMargin(11);
      hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
      mpMessage = new Q3TextEdit(tab);
      mpMessage->setObjectName(QString::fromUtf8("mpMessage"));
      mpMessage->setResizePolicy(Q3ScrollView::Manual);
      mpMessage->setReadOnly(true);

      hboxLayout1->addWidget(mpMessage);

      mpTabWidget->addTab(tab, QString());
      tab1 = new QWidget();
      tab1->setObjectName(QString::fromUtf8("tab1"));
      gridLayout1 = new Q3GridLayout(tab1);
      gridLayout1->setSpacing(6);
      gridLayout1->setMargin(11);
      gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
      mpFilteredMessage = new Q3TextEdit(tab1);
      mpFilteredMessage->setObjectName(QString::fromUtf8("mpFilteredMessage"));

      gridLayout1->addWidget(mpFilteredMessage, 0, 0, 1, 1);

      mpTabWidget->addTab(tab1, QString());

      gridLayout->addWidget(mpTabWidget, 0, 1, 1, 1);

      retranslateUi(CQMessageBox);
      QObject::connect(mpBtn0, SIGNAL(clicked()), CQMessageBox, SLOT(slotBtn0()));
      QObject::connect(mpBtn1, SIGNAL(clicked()), CQMessageBox, SLOT(slotBtn1()));
      QObject::connect(mpBtn2, SIGNAL(clicked()), CQMessageBox, SLOT(slotBtn2()));
      QObject::connect(mpBtn3, SIGNAL(clicked()), CQMessageBox, SLOT(slotBtn3()));

      QMetaObject::connectSlotsByName(CQMessageBox);
    } // setupUi

    void retranslateUi(QDialog *CQMessageBox)
    {
      CQMessageBox->setWindowTitle(QApplication::translate("CQMessageBox", "MyDialog", 0, QApplication::UnicodeUTF8));
      mpBtn0->setText(QApplication::translate("CQMessageBox", "0", 0, QApplication::UnicodeUTF8));
      mpBtn0->setShortcut(QString());
      mpBtn1->setText(QApplication::translate("CQMessageBox", "1", 0, QApplication::UnicodeUTF8));
      mpBtn1->setShortcut(QString());
      mpBtn2->setText(QApplication::translate("CQMessageBox", "2", 0, QApplication::UnicodeUTF8));
      mpBtn2->setShortcut(QString());
      mpBtn3->setText(QApplication::translate("CQMessageBox", "3", 0, QApplication::UnicodeUTF8));
      mpBtn3->setShortcut(QString());
      mpLblIcon->setText(QString());
      mpTabWidget->setTabText(mpTabWidget->indexOf(tab), QApplication::translate("CQMessageBox", "Messages", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(tab1), QApplication::translate("CQMessageBox", "Filtered Messages", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQMessageBox);
    } // retranslateUi
  };

namespace Ui
  {
  class CQMessageBox: public Ui_CQMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

class CQMessageBox : public QDialog, public Ui::CQMessageBox
  {
    Q_OBJECT

  public:
    CQMessageBox(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~CQMessageBox();

    void configure(const QString & caption, const QString & text, QMessageBox::Icon icon, int btn0, int btn1, int btn2, int btn3);
    virtual void enableFilteredMessages(bool enable);
    virtual void addMessages(const QString & messageText);
    virtual void addFilteredMessages(const QString & messageText);
    virtual void setFilteredTabLabel(const QString & labelText);
    virtual void setMessageTabLabel(const QString & labelText);
    virtual void setMessageText(const QString & text);
    virtual void setFilteredMessageText(const QString & text);
    static int critical(QWidget * parent, const QString & caption, const QString & message, int btn0, int btn1, int btn2 = 0);
    static int critical(QWidget * parent, const QString & caption, const QString & message, const QString & text0 = QString::null, const QString & text1 = QString::null, const QString & text2 = QString::null, int btnDefault = 0, int btnEscape = -1);
    static int warning(QWidget * parent, const QString & caption, const QString & message, int btn0, int btn1, int btn2 = 0);
    static int warning(QWidget * parent, const QString & caption, const QString & message, const QString & text0 = QString::null, const QString & text1 = QString::null, const QString & text2 = QString::null, int btnDefault = 0, int btnEscape = -1);
    static int question(QWidget * parent, const QString & caption, const QString & message, int btn0, int btn1, int btn2 = 0);
    static int question(QWidget * parent, const QString & caption, const QString & message, const QString & text0 = QString::null, const QString & text1 = QString::null, const QString & text2 = QString::null, int btnDefault = 0, int btnEscape = -1);
    static int information(QWidget * parent, const QString & caption, const QString & message, int btn0, int btn1, int btn2 = 0);
    static int information(QWidget * parent, const QString & caption, const QString & message, const QString & text0 = QString::null, const QString & text1 = QString::null, const QString & text2 = QString::null, int btnDefault = 0, int btnEscape = -1);

  protected:
    QPushButton * mBtn[4];

    virtual void keyPressEvent(QKeyEvent * e);
    virtual void closeEvent(QCloseEvent * e);

  protected slots:
    virtual void languageChange();

  private:
    int mBtnDefault;
    int mBtnEscape;
    bool mBtnFinished;
    int mBtnAnswer[4];

    void configureBtn(int index, int type);
    void configure(const QString & caption, const QString & text, QMessageBox::Icon icon, const QString & text0, const QString & text1, const QString & text2, const QString & text3, int btnDefault, int btnEscape);
    void configureBtn(int index, const QString & text, int btnDefault, int btnEscape);
    void init();

  private slots:
    void slotBtn0();
    void slotBtn1();
    void slotBtn2();
    void slotBtn3();
  };

#endif // CQMESSAGEBOX_H
