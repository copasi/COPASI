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

/*
 * CQIconResource.cpp
 *
 *  Created on: Mar 12, 2012
 *      Author: shoops
 */

#include <QApplication>

#include "CQIconResource.h"

// Uncomment to enable system icons
// #define SYSTEM_ICONS

// static
const CEnumAnnotation< std::string, CQIconResource::IconID > CQIconResource::BackupName(
{
  "bars.png",
  "captureImage.png",
  "checkMark.png",
  "copasi.png",
  "edit.png",
  "editAdd.png",
  "editCopy.png",
  "editDelete.png",
  "error.png",
  "fileAdd.png",
  "fileExport.png",
  "fileNew.png",
  "fileOpen.png",
  "filePrint.png",
  "fileSave.png",
  "fileSaveas.png",
  "information.png",
  "isToS_128.png",
  "locked.png",
  "miriam.png",
  "moveDown.png",
  "moveUp.png",
  "warning.png",
  "parameterMissing.png",
  "parameterModified.png",
  "parameterObsolete.png",
  "playerKill.png",
  "playerPause.png",
  "playerStart.png",
  "playerStop.png",
  "preferences.png",
  "reactionModifier.png",
  "reactionProduct.png",
  "reactionSubstrate.png",
  "renderMarkup.png",
  "renderMathML.png",
  "separator.png",
  "slider.png",
  "sToIs_128.png",
  "table.png",
  "tool.png",
  "unlocked.png",
  "zoomOut.png",
  "media-playback-start.png",
  "media-playback-pause.png",
  "media-playback-stop.png",
  "media-seek-backward.png",
  "media-seek-forward.png",
  "media-skip-backward.png",
  "media-skip-forward.png",
  "roll.png",
  "viewmagMinus.png",
  "viewmagPlus.png",
  "viewmag1.png",
  "viewmagfit.png",
  "reset.png",
  "animation.png",
  "dialog_error.png",
  "dialog_information.png",
  "dialog_warning.png",
  "dialog_question.png",
  // This is the default icon which is empty
  ""
});

// static
const CEnumAnnotation< std::string, CQIconResource::IconID > CQIconResource::ThemeName(
{
  "bars",
  "captureImage",
  "checkMark",
  "copasi",
  "document-open",
  "document-new",
  "edit-copy",
  "edit-delete",
  "error",
  "list-add",
  "document-save-as",
  "document-new",
  "document-open",
  "document-print",
  "document-save",
  "document-save-as",
  "information",
  "isToS",
  "locked",
  "miriam",
  "go-down",
  "go-up",
  "warning",
  "parameterMissing",
  "parameterModified",
  "parameterObsolete",
  "playerKill",
  "media-playback-pause",
  "media-playback-start",
  "media-playback-stop",
  "preferences",
  "reactionModifier",
  "reactionProduct",
  "reactionSubstrate",
  "renderMarkup",
  "renderMathML",
  "separator",
  "slider",
  "sToIs",
  "table",
  "tool",
  "unlocked",
  "zoom-out",
  "media-playback-start",
  "media-playback-pause",
  "media-playback-stop",
  "media-seek-backward",
  "media-seek-forward",
  "media-skip-backward",
  "media-skip-forward",
  "roll",
  "zoom-out",
  "zoom-in",
  "zoom-original",
  "zoom-fit-best",
  "reset",
  "animation",
  "dialog_error",
  "dialog_information",
  "dialog_warning",
  "dialog_question",
  // This is the default icon which is empty
  "unknown"
});

// static
const CEnumAnnotation< QStyle::StandardPixmap, CQIconResource::IconID > CQIconResource::StandardIcon(
{
  QStyle::SP_CustomBase, // "bars.png",
  QStyle::SP_CustomBase, // "captureImage.png",
  QStyle::SP_CustomBase, // "checkMark.png",
  QStyle::SP_CustomBase, // "copasi.png",
  QStyle::SP_CustomBase, // "edit.png",
  QStyle::SP_CustomBase, // "editAdd.png",
  QStyle::SP_CustomBase, // "editCopy.png",
  QStyle::SP_CustomBase, // "editDelete.png",
  QStyle::SP_MessageBoxCritical, // "error.png",
  QStyle::SP_CustomBase, // "fileAdd.png",
  QStyle::SP_CustomBase, // "fileExport.png",
  QStyle::SP_CustomBase, // "fileNew.png",
  QStyle::SP_CustomBase, // "fileOpen.png",
  QStyle::SP_CustomBase, // "filePrint.png",
  QStyle::SP_CustomBase, // "fileSave.png",
  QStyle::SP_CustomBase, // "fileSaveas.png",
  QStyle::SP_MessageBoxInformation, // "information.png",
  QStyle::SP_CustomBase, // "isToS.png",
  QStyle::SP_CustomBase, // "locked.png",
  QStyle::SP_CustomBase, // "miriam.png",
  QStyle::SP_ArrowDown, // "moveDown.png",
  QStyle::SP_ArrowUp, // "moveUp.png",
  QStyle::SP_MessageBoxWarning, // "warning.png",
  QStyle::SP_CustomBase, // "parameterMissing.png",
  QStyle::SP_CustomBase, // "parameterModified.png",
  QStyle::SP_CustomBase, // "parameterObsolete.png",
  QStyle::SP_CustomBase, // "playerKill.png",
  QStyle::SP_MediaPause, // "playerPause.png",
  QStyle::SP_MediaPlay,  // "playerStart.png",
  QStyle::SP_MediaStop,  // "playerStop.png",
  QStyle::SP_CustomBase, // "preferences.png",
  QStyle::SP_CustomBase, // "reactionModifier.png",
  QStyle::SP_CustomBase, // "reactionProduct.png",
  QStyle::SP_CustomBase, // "reactionSubstrate.png",
  QStyle::SP_CustomBase, // "renderMarkup.png",
  QStyle::SP_CustomBase, // "renderMathML.png",
  QStyle::SP_CustomBase, // "separator.png",
  QStyle::SP_CustomBase, // "slider.png",
  QStyle::SP_CustomBase, // "sToIs.png",
  QStyle::SP_CustomBase, // "table.png",
  QStyle::SP_CustomBase, // "tool.png",
  QStyle::SP_CustomBase, // "unlocked.png",
  QStyle::SP_CustomBase, // "zoomOut.png",
  QStyle::SP_MediaPlay, // "play.png",
  QStyle::SP_MediaPause, // "pause.png",
  QStyle::SP_MediaStop, // "stop.png",
  QStyle::SP_MediaSeekBackward, // "backward.png",
  QStyle::SP_MediaSeekForward, // "forward.png",
  QStyle::SP_MediaSkipBackward, // "skipBackward.png",
  QStyle::SP_MediaSkipForward, // "skipForward.png",
  QStyle::SP_CustomBase, // "roll.png",
  QStyle::SP_CustomBase, // "viewmagMinus.png",
  QStyle::SP_CustomBase, // "viewmagPlus.png",
  QStyle::SP_CustomBase, // "viewmag1.png",
  QStyle::SP_CustomBase, // "viewmagfit.png",
  QStyle::SP_CustomBase, // "reset.png",
  QStyle::SP_CustomBase, // "animation.png",
  QStyle::SP_MessageBoxCritical, // "dialog_error.png",
  QStyle::SP_MessageBoxInformation, // "dialog_information.png",
  QStyle::SP_MessageBoxWarning, // "dialog_warning.png",
  QStyle::SP_MessageBoxQuestion, // "dialog_question.png",
  // This is the default icon which is empty
  QStyle::SP_CustomBase, // ""
});

// static
bool CQIconResource::needInit(true);

// static
QVector< QIcon > CQIconResource::Icons;

void CQIconResource::init()
{
  if (!needInit) return;

  Q_INIT_RESOURCE(copasi);

  Icons.resize(__SIZE);

  load(bars, QIcon::Normal, QIcon::Off);
  load(captureImage, QIcon::Normal, QIcon::On);
  load(copasi, QIcon::Normal, QIcon::On);
  load(checkMark, QIcon::Normal, QIcon::On);
  load(edit, QIcon::Normal, QIcon::On);
  load(editAdd, QIcon::Normal, QIcon::On);
  load(editCopy, QIcon::Normal, QIcon::On);
  load(editDelete, QIcon::Normal, QIcon::On);
  load(error, QIcon::Normal, QIcon::On);
  load(fileAdd, QIcon::Normal, QIcon::On);
  load(fileExport, QIcon::Normal, QIcon::On);
  load(fileNew, QIcon::Normal, QIcon::On);
  load(fileOpen, QIcon::Normal, QIcon::On);
  load(filePrint, QIcon::Normal, QIcon::On);
  load(fileSave, QIcon::Normal, QIcon::On);
  load(fileSaveas, QIcon::Normal, QIcon::On);
  load(information, QIcon::Normal, QIcon::On);
  load(isToS, QIcon::Normal, QIcon::On);
  load(locked, QIcon::Normal, QIcon::On);
  load(miriam, QIcon::Normal, QIcon::On);
  load(moveDown, QIcon::Normal, QIcon::On);
  load(moveUp, QIcon::Normal, QIcon::On);
  load(warning, QIcon::Normal, QIcon::On);
  load(parameterMissing, QIcon::Normal, QIcon::On);
  load(parameterModified, QIcon::Normal, QIcon::On);
  load(parameterObsolete, QIcon::Normal, QIcon::On);
  load(playerKill, QIcon::Normal, QIcon::On);
  load(playerPause, QIcon::Normal, QIcon::On);
  load(playerStart, QIcon::Normal, QIcon::On);
  load(playerStop, QIcon::Normal, QIcon::On);
  load(preferences, QIcon::Normal, QIcon::On);
  load(reactionModifier, QIcon::Normal, QIcon::On);
  load(reactionProduct, QIcon::Normal, QIcon::On);
  load(reactionSubstrate, QIcon::Normal, QIcon::On);
  load(renderMarkup, QIcon::Normal, QIcon::On);
  load(renderMathML, QIcon::Normal, QIcon::On);
  load(separator, QIcon::Normal, QIcon::On);
  load(slider, QIcon::Normal, QIcon::On);
  load(sToIs, QIcon::Normal, QIcon::On);
  load(table, QIcon::Normal, QIcon::On);
  load(tool, QIcon::Normal, QIcon::On);
  load(unlocked, QIcon::Normal, QIcon::On);
  load(zoomOut, QIcon::Normal, QIcon::On);
  load(play, QIcon::Normal, QIcon::On);
  load(pause, QIcon::Normal, QIcon::On);
  load(stop, QIcon::Normal, QIcon::On);
  load(backward, QIcon::Normal, QIcon::On);
  load(forward, QIcon::Normal, QIcon::On);
  load(skipBackward, QIcon::Normal, QIcon::On);
  load(skipForward, QIcon::Normal, QIcon::On);
  load(roll, QIcon::Normal, QIcon::On);
  load(viewmagMinus, QIcon::Normal, QIcon::On);
  load(viewmagPlus, QIcon::Normal, QIcon::On);
  load(viewmag1, QIcon::Normal, QIcon::On);
  load(viewmagfit, QIcon::Normal, QIcon::On);
  load(_reset, QIcon::Normal, QIcon::On);
  load(animation, QIcon::Normal, QIcon::On);
  load(dialog_error, QIcon::Normal, QIcon::On);
  load(dialog_information, QIcon::Normal, QIcon::On);
  load(dialog_warning, QIcon::Normal, QIcon::On);
  load(dialog_question, QIcon::Normal, QIcon::On);

  needInit = false;
}

// static
const QIcon & CQIconResource::icon(const CQIconResource::IconID & id)
{
  init();

  if (id < __SIZE)
    return Icons[id];

  return Icons[unknown];
}

// static
void CQIconResource::load(IconID iconID, QIcon::Mode mode, QIcon::State state)
{
  QIcon & Icon = Icons[iconID];

#ifdef SYSTEM_ICONS

  if (StandardIcon[iconID] < QStyle::SP_CustomBase)
    Icon = QApplication::style()->standardIcon(StandardIcon[iconID]);
  else if (QIcon::hasThemeIcon(QString::fromUtf8(ThemeName[iconID].c_str())))
    Icon = QIcon::fromTheme(QString::fromUtf8(ThemeName[iconID].c_str()));
  else
#endif // SYSTEM_ICONS

    Icon.addFile(QString(":/images/" + QString::fromUtf8(BackupName[iconID].c_str())), QSize(), mode, state);
}
