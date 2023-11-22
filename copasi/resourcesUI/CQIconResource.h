// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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
#include <QStyle>

#include "copasi/core/CEnumAnnotation.h"

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
    _reset,
    animation,
    dialog_error,
    dialog_information,
    dialog_warning,
    dialog_question,
    // This is the default icon which is empty
    unknown,
    // This must be the last entry to automatically determine the size!
    __SIZE
  };

  static const QIcon & icon(const IconID & id);

private:
  static void init();
  static void load(IconID iconID, QIcon::Mode mode = QIcon::Normal, QIcon::State state = QIcon::Off);

  static QVector< QIcon > Icons;
  static bool needInit;
  static const CEnumAnnotation< std::string, IconID > BackupName;
  static const CEnumAnnotation< std::string, IconID > ThemeName;
  static const CEnumAnnotation< QStyle::StandardPixmap, IconID > StandardIcon;
};

#endif // COPASI_CQIconResource
