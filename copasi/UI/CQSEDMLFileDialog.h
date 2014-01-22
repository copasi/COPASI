// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQSEDMLFileDialog.h
 *
 *  Created on: 31 Jul 2013
 *      Author: dada
 */

#ifndef CQSEDMLFILEDIALOG_H_
#define CQSEDMLFILEDIALOG_H_

#include <qstring.h>

#include <vector>
#include <utility>
#include "copasi.h"
//Added by qt3to4:
#include <QLabel>

class QWidget;

class CQSEDMLFileDialog
{
public:
  static
  std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > getSaveFileName(QWidget * parent,
      const char * name,
      const QString & startWith,
      const QString & caption,
      unsigned int sedmlLevel = 1,
      unsigned int sedmlVersion = 2);
};

#endif /* CQSEDMLFILEDIALOG_H_ */
