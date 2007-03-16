// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMessageBox.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/16 16:40:24 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMessageBox.ui'
 **
 ** Created: Fri Mar 16 12:23:00 2007
 **      by: The User Interface Compiler ($Id: CQMessageBox.h,v 1.1 2007/03/16 16:40:24 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMESSAGEBOX_H
#define CQMESSAGEBOX_H

#include <qvariant.h>
#include <qdialog.h>
#include <qmessagebox.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QTextEdit;

class CQMessageBox : public QDialog
  {
    Q_OBJECT

  public:
    CQMessageBox(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQMessageBox();

    QPushButton* mpBtn0;
    QPushButton* mpBtn1;
    QPushButton* mpBtn2;
    QPushButton* mpBtn3;
    QLabel* mpLblIcon;
    QTextEdit* mpMessage;

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

    QGridLayout* CQMessageBoxLayout;
    QHBoxLayout* mpLayoutBtn;
    QVBoxLayout* mpLayoutIcon;
    QSpacerItem* mpSpacerIcon;

  protected slots:
    virtual void languageChange();

  private:
    int mBtnDefault;
    int mBtnEscape;
    bool mBtnFinished;

    void configure(const QString & caption, const QString & text, QMessageBox::Icon icon, int btn0, int btn1, int btn2, int btn3);
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
