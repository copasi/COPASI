// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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
#include "copasi/copasi.h"
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
      unsigned int sedmlVersion = 4);
};

#endif /* CQSEDMLFILEDIALOG_H_ */
