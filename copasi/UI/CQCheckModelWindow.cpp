// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/UI/CQCheckModelWindow.h"
#include "copasi/resourcesUI/CQIconResource.h"
#include "copasi/UI/CopasiFileDialog.h"

#include "copasi/copasi.h"
#include "copasi/UI/qtUtilities.h"

#include "copasi/model/CModelAnalyzer.h"

#include <iostream>
#include <sstream>

#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QPushButton>

void CQCheckModelWindow::setAnalyzer(CModelAnalyzer* analyzer)
{
  pdelete(mpAnalyzer);

  mpAnalyzer = analyzer;

  mbInitializing = true;

  mpSelection->clear();
  mpSelection->addItem("All Reactions");

  if (mpAnalyzer != NULL)
    {
      const std::vector<CReactionResult>& results = mpAnalyzer->getReactionResults();
      std::vector<CReactionResult>::const_iterator it = results.begin();

      for (; it != results.end(); ++it)
        {
          mpSelection->addItem(FROM_UTF8(it->getName()));
        }
    }

  mpSelection->setCurrentIndex(0);

  mbInitializing = false;

  displayResult();
}

CQCheckModelWindow::CQCheckModelWindow(CopasiUI3Window * pMainWindow)
  : CWindowInterface()
  , mbInitializing(true)
  , mpMainWindow(pMainWindow)
  , mpAnalyzer(NULL)
  , mpSelection(NULL)
{
  setupUi(this);

  textEdit->setReadOnly(true);

  mpActSave->setIcon(CQIconResource::icon(CQIconResource::fileSaveas));

  addToMainWindow(mpMainWindow);

  setAttribute(Qt::WA_DeleteOnClose);

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  mpSelection = new QComboBox(this);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
  mpSelection->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
#endif
  mpSelection->setSizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
  connect(mpSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(displayResult()));

  QPushButton* pButton = new QPushButton("Find &Next", this);
  pButton->setShortcut(QKeySequence::FindNext);

  connect(pButton, SIGNAL(clicked()), this, SLOT(findNext()));

  QFrame* pFrame1 = new QFrame(this);
  QHBoxLayout* pLayout1 = new QHBoxLayout(pFrame1);
  pLayout1->setSpacing(3);
  pFrame1->setLayout(pLayout1);
  QLabel* pLabel1 = new QLabel(tr("Reaction:"));
  pLabel1->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
  pLayout1->addWidget(pLabel1);
  pLayout1->addWidget(mpSelection);

  mpFindBox = new QLineEdit(this);
  mpFindBox->setSizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
  connect(mpFindBox, SIGNAL(textChanged(QString)), this, SLOT(findText(QString)));

  QFrame* pFrame2 = new QFrame(this);
  QHBoxLayout* pLayout2 = new QHBoxLayout(pFrame2);
  pLayout2->setSpacing(3);
  pFrame2->setLayout(pLayout2);
  QLabel* pLabel2 = new QLabel(tr("Find:"));
  pLayout2->addWidget(pLabel2);
  pLayout2->addWidget(mpFindBox);
  pLayout2->addWidget(pButton);

  toolBar->addWidget(pFrame1);
  toolBar->addWidget(pFrame2);
}

CQCheckModelWindow::~CQCheckModelWindow()
{
  removeFromMainWindow(mpMainWindow);
  pdelete(mpAnalyzer);
}

QMenu *CQCheckModelWindow::getWindowMenu() const
{
  return mpWindowMenu;
}

void CQCheckModelWindow::displayResult()
{
  textEdit->clear();

  if (mpAnalyzer == NULL || mbInitializing) return;

  int index = mpSelection->currentIndex();
  bool verbose = mpActVerbose->isChecked();

  std::ostringstream ss;

  if (index < 1)
    {
      mpAnalyzer->writeReport(ss, true, verbose);
    }
  else
    {
      std::string current = TO_UTF8(mpSelection->currentText());
      const std::vector<CReactionResult>& results = mpAnalyzer->getReactionResults();
      std::vector<CReactionResult>::const_iterator it = results.begin();

      for (; it != results.end(); ++it)
        {
          if (it->getName() != current)
            continue;

          it->writeResult(ss, true, verbose);
        }
    }

  textEdit->setText(FROM_UTF8(ss.str()));
}

void CQCheckModelWindow::findNext()
{
  textEdit->find(mpFindBox->text());
}

void CQCheckModelWindow::findText(const QString & text)
{
  textEdit->moveCursor(QTextCursor::Start);
  textEdit->find(text);
}

void CQCheckModelWindow::slotSaveAs()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName = CopasiFileDialog::getSaveFileName(this,
                 "Save File Dialog", CopasiFileDialog::getDefaultFileName(".html"), "HTML files (*.html)", "Save Report as HTML file");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);
  out << textEdit->document()->toHtml();
  file.close();
}
