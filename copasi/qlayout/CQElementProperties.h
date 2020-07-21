// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQELEMENTPROPERTIES_H
#define CQELEMENTPROPERTIES_H

#include <QWidget>

namespace Ui
{
class CQElementProperties;
}

class CQLayoutScene;
class CLGraphicalObject;

class CQElementProperties : public QWidget
{
  Q_OBJECT

public:
  explicit CQElementProperties(QWidget *parent = nullptr);
  ~CQElementProperties();

  void setScene(CQLayoutScene* scene);
  void loadFromGlyph(CLGraphicalObject* glyph);
  void loadFromGlyph(const std::string& key);

  void fillStylesFromScene(CQLayoutScene * scene);
  void removeGlyphFromStyle(const std::string& glyphKey, const std::string& styleKey);
  void addGlyphToStyle(const std::string & glyphKey, const std::string & styleKey);

public slots:
  void slotSelectionChanged();
  void slotApply();
  void slotDisplayStyle();
  void slotSelectTextGlyph();
  void slotSelectTarget();
  void slotRenderInformationChanged();

private:
  CQLayoutScene* mpScene;
  Ui::CQElementProperties *ui;

  std::string mGlyphKey;
  std::string mTargetCN;
  std::string mTextKey;
  std::string mStyleKey;


};

#endif // CQELEMENTPROPERTIES_H
