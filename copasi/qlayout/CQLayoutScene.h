// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef QLAYOUT_SCENE_H
#define QLAYOUT_SCENE_H

#include <QGraphicsScene>
#include <QtCore/QSharedPointer>

#include <string>
#include <map>

class CLayout;
class CLGraphicalObject;
class CLRenderResolver;
class CDataModel;
class CLRenderInformationBase;
class CQCopasiEffect;

class CQLayoutScene: public QGraphicsScene
{
  Q_OBJECT
public:
  CQLayoutScene(CLayout *layout, CDataModel* model = NULL, CLRenderInformationBase* renderInformation = NULL);
  virtual ~CQLayoutScene();
  void setResolver(CLRenderResolver* resolver);
  const CLRenderResolver* getResolver() const;
  CLRenderResolver * getResolver();
  void saveToFile(const std::string& fileName, const std::string& fileType = "pdf");
  void setLayout(CLayout *layout, CDataModel* model = NULL, CLRenderInformationBase* renderInformation = NULL);
  void setRenderInformation(CDataModel* model, CLRenderInformationBase* renderInformation);
  QGraphicsItem* getItemFor(const std::string& cn);
  const CLayout* getCurrentLayout() const;
  CLayout* getCurrentLayout();
  const CLRenderInformationBase* getCurrentRenderInfo() const;
  void updatePosition(const QString& key, const QPointF& newPos);
public slots:
  void recreate();
signals:
  void recreateNeeded();
protected:
  void initializeResolver(CDataModel* model, CLRenderInformationBase* renderInformation);
private:
  void addGlyph(const CLGraphicalObject* go);
  void fillFromLayout(const CLayout* layout);

  CLayout* mpLayout;
  CLRenderInformationBase* mpRender;
  QSharedPointer<CLRenderResolver> mpResolver;

  std::map< std::string, QGraphicsItem*> mItems;
};

#endif
