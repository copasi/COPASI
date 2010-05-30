// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQIcons.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2010/05/30 15:23:55 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQICONS_H
#define CQICONS_H

#include <QPixmap>

class CQIcons
{
public:
  enum IconID
  {
    Pause,
    Continue,
    Stop,
    SelectObject,
    Add,
    Delete,
    View,
    Edit,
    Save,
    unknown_ID
  };

  static QPixmap getIcon(const IconID & id);
};

#endif // CQICONS_H
