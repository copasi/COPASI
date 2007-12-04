// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMessageBox.ui.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/04 15:47:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include <assert.h>

void CQMessageBox::configure(const QString & caption, const QString & text,
                             QMessageBox::Icon icon, int btn0, int btn1, int btn2, int btn3)
{
  mpLblIcon->setPixmap(QMessageBox::standardIcon(icon));
  mpMessage->setText(text);
  this->enableFilteredMessages(false);
  setCaption(caption);

  mBtnEscape = -1;
  mBtnDefault = -1;
  mBtnFinished = false;

  configureBtn(0, btn0);
  configureBtn(1, btn1);
  configureBtn(2, btn2);
  configureBtn(3, btn3);
}

void CQMessageBox::configureBtn(int index, int type)
{
  const char * BtnText[] =
    {
      0,
      "OK",
      "Cancel",
      "&Yes",
      "&No",
      "&Abort",
      "&Retry",
      "&Ignore",
      "Yes to &All",
      "N&o to All",
      0
    };

  if (type & QMessageBox::Default)
    {
      assert(mBtnDefault == -1); // Only 1 default button
      mBtnDefault = index;
      mBtn[index]->setFocus();
    }

  if (type & QMessageBox::Escape)
    {
      assert(mBtnEscape == -1); // Only 1 escape button
      mBtnEscape = index;
    }

  type &= QMessageBox::ButtonMask;

  if (type == 0)
    {
      mBtn[index]->hide();
      mBtnFinished = true;
    }
  else
    {
      assert(!mBtnFinished); // The used buttons must be consecutive
      mBtn[index]->setText(tr(BtnText[type]));
      mBtnAnswer[index] = type;
    }

  return;
}

void CQMessageBox::configure(const QString & caption, const QString & text, QMessageBox::Icon icon,
                             const QString & text0, const QString & text1,
                             const QString & text2, const QString & text3,
                             int btnDefault, int btnEscape)
{
  mpLblIcon->setPixmap(QMessageBox::standardIcon(icon));
  mpMessage->setText(text);
  setCaption(caption);

  mBtnEscape = -1;
  mBtnDefault = -1;
  mBtnFinished = false;

  configureBtn(0, text0, btnDefault, btnEscape);
  configureBtn(1, text1, btnDefault, btnEscape);
  configureBtn(2, text2, btnDefault, btnEscape);
  configureBtn(3, text3, btnDefault, btnEscape);

  return;
}

void CQMessageBox::configureBtn(int index, const QString & text, int btnDefault, int btnEscape)
{
  int type;

  if (text.isEmpty())
    type = QMessageBox::NoButton;
  else
    type = index + 1; // We must not use index 0 as this is equal to QMessageBox::NoButton

  if (index == btnDefault)
    type |= QMessageBox::Default;

  if (index == btnEscape)
    type |= QMessageBox::Escape;

  configureBtn(index, type);

  mBtn[index]->setText(text);

  // Correct for the above introduced offset;
  mBtnAnswer[index]--;

  return;
}

void CQMessageBox::slotBtn0() {done(mBtnAnswer[0]);}

void CQMessageBox::slotBtn1() {done(mBtnAnswer[1]);}

void CQMessageBox::slotBtn2() {done(mBtnAnswer[2]);}

void CQMessageBox::slotBtn3() {done(mBtnAnswer[3]);}

void CQMessageBox::init()
{
  // Center the buttons and prevent horizontal stretching.
  mpLayoutBtn->insertStretch(0, 0);
  mpLayoutBtn->addStretch(0);

  // Initialize the button area.
  mBtn[0] = mpBtn0;
  mBtn[1] = mpBtn1;
  mBtn[2] = mpBtn2;
  mBtn[3] = mpBtn3;

  // Initialize the results
  mBtnAnswer[0] = QMessageBox::NoButton;
  mBtnAnswer[1] = QMessageBox::NoButton;
  mBtnAnswer[2] = QMessageBox::NoButton;
  mBtnAnswer[3] = QMessageBox::NoButton;

  this->enableFilteredMessages(false);
}

void CQMessageBox::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Key_Escape && mBtnEscape != -1)
    done(mBtnAnswer[mBtnEscape]);
}

void CQMessageBox::closeEvent(QCloseEvent * e)
{
  QDialog::closeEvent(e);
  if (mBtnDefault != -1)
    setResult(mBtnAnswer[mBtnDefault]);
}

int CQMessageBox::critical(QWidget * parent, const QString & caption, const QString & message,
                           int btn0, int btn1, int btn2)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);
  pDialog->configure(caption, message, QMessageBox::Critical, btn0, btn1, btn2, 0);

  return pDialog->exec();
}

int CQMessageBox::critical(QWidget * parent, const QString & caption, const QString & message,
                           const QString & text0, const QString & text1, const QString & text2,
                           int btnDefault, int btnEscape)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);

  pDialog->configure(caption, message, QMessageBox::Critical, text0, text1, text2, QString::null,
                     btnDefault, btnEscape);

  return pDialog->exec();
}

int CQMessageBox::warning(QWidget * parent, const QString & caption, const QString & message,
                          int btn0, int btn1, int btn2)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);
  pDialog->configure(caption, message, QMessageBox::Warning, btn0, btn1, btn2, 0);

  return pDialog->exec();
}

int CQMessageBox::warning(QWidget * parent, const QString & caption, const QString & message,
                          const QString & text0, const QString & text1, const QString & text2,
                          int btnDefault, int btnEscape)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);

  pDialog->configure(caption, message, QMessageBox::Warning, text0, text1, text2, QString::null,
                     btnDefault, btnEscape);

  return pDialog->exec();
}

int CQMessageBox::question(QWidget * parent, const QString & caption, const QString & message,
                           int btn0, int btn1, int btn2)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);
  pDialog->configure(caption, message, QMessageBox::Question, btn0, btn1, btn2, 0);

  return pDialog->exec();
}

int CQMessageBox::question(QWidget * parent, const QString & caption, const QString & message,
                           const QString & text0, const QString & text1, const QString & text2,
                           int btnDefault, int btnEscape)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);

  pDialog->configure(caption, message, QMessageBox::Question, text0, text1, text2, QString::null,
                     btnDefault, btnEscape);

  return pDialog->exec();
}

int CQMessageBox::information(QWidget * parent, const QString & caption, const QString & message,
                              int btn0, int btn1, int btn2)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);
  pDialog->configure(caption, message, QMessageBox::Information, btn0, btn1, btn2, 0);

  return pDialog->exec();
}

int CQMessageBox::information(QWidget * parent, const QString & caption, const QString & message,
                              const QString & text0, const QString & text1, const QString & text2,
                              int btnDefault, int btnEscape)
{
  CQMessageBox * pDialog = new CQMessageBox(parent);

  pDialog->configure(caption, message, QMessageBox::Information, text0, text1, text2, QString::null,
                     btnDefault, btnEscape);

  return pDialog->exec();
}

void CQMessageBox::enableFilteredMessages(bool enable)
{
  this->mpTabWidget->setTabEnabled(this->mpTabWidget->page(1), enable);
}

void CQMessageBox::addMessages(const QString & messageText)
{
  QString text = this->mpMessage->text();
  text += "\n";
  text += messageText;
  this->mpMessage->setText(text);
}

void CQMessageBox::addFilteredMessages(const QString & messageText)
{
  QString text = this->mpFilteredMessage->text();
  text += "\n";
  text += messageText;
  this->mpFilteredMessage->setText(text);
}

void CQMessageBox::setFilteredTabLabel(const QString & labelText)
{
  this->mpTabWidget->setTabLabel(this->mpTabWidget->page(1), labelText);
}

void CQMessageBox::setMessageTabLabel(const QString & labelText)
{
  this->mpTabWidget->setTabLabel(this->mpTabWidget->page(0), labelText);
}

void CQMessageBox::setMessageText(const QString & text)
{
  this->mpMessage->setText(text);
}

void CQMessageBox::setFilteredMessageText(const QString & text)
{
  this->mpFilteredMessage->setText(text);
}
