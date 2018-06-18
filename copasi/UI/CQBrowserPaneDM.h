// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQBrowserPaneDM
#define COPASI_CQBrowserPaneDM

#include <QSortFilterProxyModel>

#include "copasi/UI/listviews.h"

#include "copasi/utilities/CCopasiNode.h"
#include "copasi/utilities/CValidity.h"
#include "copasi/core/CRegisteredCommonName.h"

class DataModelGUI;
class CDataModel;

class CQBrowserPaneDM : public QAbstractItemModel
{
  Q_OBJECT

public:
  class SData
  {
  public:
    size_t mId;

    CRegisteredCommonName mCN;

    QString mDisplayRole;
  };

  class CNode : public CCopasiNode< SData >
  {
  private:
    CNode();

  public:
    friend std::ostream & operator<<(std::ostream & os, const CNode & d);

    CNode(const size_t & id,
          const CCommonName & cn,
          const QString & displayRole,
          CNode * pParent);

    ~CNode();

    const size_t & getId() const;

    void setDisplayRole(const QString & displayRole);

    const QString & getDisplayRole() const;

    QString getSortRole() const;

    void setCN(const CCommonName & cn);

    const CCommonName & getCN() const;

    const CDataObject * getObject(const CDataModel * pDataModel) const;

    int getRow() const;
  };

public:
  enum Type
  {
    Model = 0x01,
    Tasks = 0x02,
    Output = 0x04,
    FunctionDB = 0x08,
    Units = 0x10
  };

  CQBrowserPaneDM(QObject * parent = 0);

  virtual ~CQBrowserPaneDM();

  virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;

  virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

  virtual QModelIndex parent(const QModelIndex & index) const;

  virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

  virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

  QModelIndex index(const size_t & id, const CCommonName & cn) const;

  // virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  CNode * findNodeFromId(const size_t & id) const;

  CNode * findNodeFromCN(const CCommonName & cn) const;

  size_t getIdFromIndex(const QModelIndex & index) const;

  const CCommonName & getCNFromIndex(const QModelIndex & index) const;

  void remove(CNode * pNode);

  void rename(CNode * pNode, const QString & displayRole);

  void add(const size_t & id,
           const CCommonName & cn,
           const QString & displayRole,
           const size_t & parentId = C_INVALID_INDEX);

  void setCopasiDM(const CDataModel * pDataModel);

  void setGuiDM(const DataModelGUI * pDataModel);

  void load();

  void load(const size_t & id);

private slots:
  bool slotNotify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  void slotRefreshValidityFilters();

private:
  static CNode * nodeFromIndex(const QModelIndex & index);

  CNode * createNode(const size_t & id,
                     const CCommonName & cn,
                     const QString & displayRole,
                     CNode * pParent);

  void updateNode(CNode * pNode, const CCommonName & CN);

  void destroyNode(CNode * pNode);

  QModelIndex index(CNode * pNode) const;

  // bool isNodeFromTree(const void * pNode) const;

  void createStaticDM();

  void clear();

  QString getObjectIssueMessages(const CNode * pNode) const;

  QIcon getObjectIssueIcon(const CNode *pNode) const;

  CNode * mpRoot;

  const CDataModel * mpCopasiDM;

  const DataModelGUI * mpGuiDM;

  bool mEmitDataChanged;

  int mFlags;

  CValidity::Severity mSeverityFilter;
  CValidity::Kind mKindFilter;

  std::map< std::string, CNode * > mCN2Node;
  std::map< size_t, CNode * > mId2Node;
};

#endif // COPASI_CQBrowserPaneDM
