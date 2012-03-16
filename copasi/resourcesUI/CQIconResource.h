// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/resourcesUI/CQIconResource.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/16 15:31:54 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQIconResource
#define COPASI_CQIconResource

#include <QtCore/QVector>
#include <QtGui/QIcon>

class CQIconResource
{
public:
  enum IconID
  {
    captureImage = 0,
    checkMark,
    copasi,
    edit,
    editAdd,
    editCopy,
    editDelete,
    fileAdd,
    fileExport,
    fileNew,
    fileOpen,
    filePrint,
    fileSave,
    fileSaveas,
    isToS,
    locked,
    miriam,
    moveDown,
    moveUp,
    playerKill,
    playerPause,
    playerStart,
    playerStop,
    preferences,
    reactionModifier,
    reactionProduct,
    reactionSubstrate,
    renderMarkup,
    renderMathML,
    separator,
    slider,
    sToIs,
    tool,
    unlocked,
    zoomOut,
    // This is the default icon which is empty
    unknown,
    // This must be the last entry to automatically determine the size!
    _size
  };

  static const QIcon & icon(const IconID & id);

private:
  static void init();

  static QVector< QIcon > Icons;
  static bool needInit;
};

#endif // COPASI_CQIconResource
