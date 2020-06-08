// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSBML_FILE_DIALOG
#define CQSBML_FILE_DIALOG

#include <QtCore/QString>

#include <vector>
#include <utility>
#include "copasi/copasi.h"
//Added by qt3to4:
#include <QLabel>

class QWidget;

class CQSBMLFileDialog
{
public:
  static
  std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > getSaveFileName(QWidget * parent,
      const char * name,
      const QString & startWith,
      const QString & caption,
      unsigned int sbmlLevel = 2,
      unsigned int sbmlVersion = 4);
};

#endif // CQSBML_FILE_DIALOG
