// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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
bool CQIconResource::needInit(true);

// static
QVector< QIcon > CQIconResource::Icons;

void CQIconResource::init()
{
  if (!needInit) return;

  Q_INIT_RESOURCE(copasi);

  Icons.resize(StandardIcon.size());

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

  return Icons[StandardIcon.toEnum(id)];
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
