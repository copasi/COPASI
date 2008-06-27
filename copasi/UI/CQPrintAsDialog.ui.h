// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPrintAsDialog.ui.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/27 18:42:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
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

#include <qregexp.h>

#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CopasiFileDialog.h"

void CQPrintAsDialog::openFileDialog()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName = CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                 QString::null, "PNG Files (*.png);;SVG Files (*.svg);;", "Save to");

      std::cout << "fileName: " << fileName << std::endl;
      if (fileName.isEmpty()) return;
      /*
          if (!fileName.endsWith(".txt") &&
                !fileName.endsWith(".")) fileName += ".txt";

       fileName = fileName.remove(QRegExp("\\.$"));
      */

      QFileInfo fileInfo(fileName);
      fileName = fileInfo.baseName();

      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  mpEditFileName->setText(fileName);
}

void CQPrintAsDialog::confirm()
{
  if (mpEditFileName->text().isEmpty()) return;
  if (!mpCBPNG->isChecked() && !mpCBSVG->isChecked()) return;

  accept();
}
