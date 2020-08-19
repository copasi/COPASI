// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQIconResource
#define COPASI_CQIconResource

#include <QtCore/QVector>
#include <QIcon>

class CQIconResource
{
public:
  enum IconID
  {
    bars = 0,
    captureImage,
    checkMark,
    copasi,
    edit,
    editAdd,
    editCopy,
    editDelete,
    error,
    fileAdd,
    fileExport,
    fileNew,
    fileOpen,
    filePrint,
    fileSave,
    fileSaveas,
    information,
    isToS,
    locked,
    miriam,
    moveDown,
    moveUp,
    warning,
    parameterMissing,
    parameterModified,
    parameterObsolete,
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
    table,
    tool,
    unlocked,
    zoomOut,
    play,
    pause,
    stop,
    backward,
    forward,
    skipBackward,
    skipForward,
    roll,
    viewmagMinus,
    viewmagPlus,
    viewmag1,
    viewmagfit,
    reset,
    animation,
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
