// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQIcons.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2009/12/17 02:47:12 $
// End CVS Header

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
    unknown_ID
  };

  static QPixmap getIcon(const IconID & id);
};

#endif // CQICONS_H
