/****************************************************************************
 ** Folder meta object code from reading C++ file 'listviews.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "listviews.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Folder::className() const
{
  return "Folder";
}

QMetaObject *Folder::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Folder;

#ifndef QT_NO_TRANSLATION
QString Folder::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("Folder", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Folder::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("Folder", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Folder::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = QObject::staticMetaObject();
  metaObj = QMetaObject::new_metaobject(
              "Folder", parentObject,
              0, 0,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_Folder.setMetaObject(metaObj);
  return metaObj;
}

void* Folder::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "Folder")) return (Folder*)this;
  return QObject::qt_cast(clname);
}

bool Folder::qt_invoke(int _id, QUObject* _o)
{
  return QObject::qt_invoke(_id, _o);
}

bool Folder::qt_emit(int _id, QUObject* _o)
{
  return QObject::qt_emit(_id, _o);
}
#ifndef QT_NO_PROPERTIES

bool Folder::qt_property(int _id, int _f, QVariant* _v)
{
  return QObject::qt_property(_id, _f, _v);
}
#endif // QT_NO_PROPERTIES

const char *ListViews::className() const
{
  return "ListViews";
}

QMetaObject *ListViews::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ListViews;

#ifndef QT_NO_TRANSLATION
QString ListViews::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("ListViews", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ListViews::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("ListViews", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ListViews::staticMetaObject()
{
  if (metaObj)
    return metaObj;
  QMetaObject* parentObject = QSplitter::staticMetaObject();
  static const QUParameter param_slot_0[] = {
        {0, &static_QUType_QString, 0, QUParameter::InOut}
      };
  static const QUMethod slot_0 = {"slotFunctionTableChanged", 1, param_slot_0};
  static const QUParameter param_slot_1[] = {
        {0, &static_QUType_QString, 0, QUParameter::InOut}
      };
  static const QUMethod slot_1 = {"slotCompartmentTableChanged", 1, param_slot_1};
  static const QUParameter param_slot_2[] = {
        {0, &static_QUType_QString, 0, QUParameter::InOut}
      };
  static const QUMethod slot_2 = {"slotMetaboliteTableChanged", 1, param_slot_2};
  static const QUParameter param_slot_3[] = {
        {0, &static_QUType_QString, 0, QUParameter::InOut}
      };
  static const QUMethod slot_3 = {"slotMoietyTableChanged", 1, param_slot_3};
  static const QUParameter param_slot_4[] = {
        {0, &static_QUType_QString, 0, QUParameter::InOut}
      };
  static const QUMethod slot_4 = {"slotReactionTableChanged", 1, param_slot_4};
  static const QUParameter param_slot_5[] = {
        {0, &static_QUType_ptr, "QListViewItem", QUParameter::In}
      };
  static const QUMethod slot_5 = {"slotFolderChanged", 1, param_slot_5};
  static const QMetaData slot_tbl[] = {
                                        {"slotFunctionTableChanged(QString&)", &slot_0, QMetaData::Public},
                                        {"slotCompartmentTableChanged(QString&)", &slot_1, QMetaData::Public},
                                        {"slotMetaboliteTableChanged(QString&)", &slot_2, QMetaData::Public},
                                        {"slotMoietyTableChanged(QString&)", &slot_3, QMetaData::Public},
                                        {"slotReactionTableChanged(QString&)", &slot_4, QMetaData::Public},
                                        {"slotFolderChanged(QListViewItem*)", &slot_5, QMetaData::Protected}
                                      };
  metaObj = QMetaObject::new_metaobject(
              "ListViews", parentObject,
              slot_tbl, 6,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);
  cleanUp_ListViews.setMetaObject(metaObj);
  return metaObj;
}

void* ListViews::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "ListViews")) return (ListViews*)this;
  if (!qstrcmp(clname, "Observer")) return (Observer*)this;
  return QSplitter::qt_cast(clname);
}

bool ListViews::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0: slotFunctionTableChanged(static_QUType_QString.get(_o + 1)); break;
    case 1: slotCompartmentTableChanged(static_QUType_QString.get(_o + 1)); break;
    case 2: slotMetaboliteTableChanged(static_QUType_QString.get(_o + 1)); break;
    case 3: slotMoietyTableChanged(static_QUType_QString.get(_o + 1)); break;
    case 4: slotReactionTableChanged(static_QUType_QString.get(_o + 1)); break;
    case 5: slotFolderChanged((QListViewItem*)static_QUType_ptr.get(_o + 1)); break;
    default:
      return QSplitter::qt_invoke(_id, _o);
    }
  return TRUE;
}

bool ListViews::qt_emit(int _id, QUObject* _o)
{
  return QSplitter::qt_emit(_id, _o);
}
#ifndef QT_NO_PROPERTIES

bool ListViews::qt_property(int _id, int _f, QVariant* _v)
{
  return QSplitter::qt_property(_id, _f, _v);
}
#endif // QT_NO_PROPERTIES
