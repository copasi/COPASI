/****************************************************************************
 ** MetabolitesWidget meta object code from reading C++ file 'MetabolitesWidget.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "MetabolitesWidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MetabolitesWidget::className() const
  {
    return "MetabolitesWidget";
  }

QMetaObject *MetabolitesWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MetabolitesWidget;

#ifndef QT_NO_TRANSLATION
QString MetabolitesWidget::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("MetabolitesWidget", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}

#ifndef QT_NO_TRANSLATION_UTF8
QString MetabolitesWidget::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("MetabolitesWidget", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}

#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MetabolitesWidget::staticMetaObject()
{
  if (metaObj)
    return metaObj;

  QMetaObject* parentObject = QWidget::staticMetaObject();

  static const QUParameter param_slot_0[] =
    {
      { "row", &static_QUType_int, 0, QUParameter::In },

      { "col", &static_QUType_int, 0, QUParameter::In },
      { "button", &static_QUType_int, 0, QUParameter::In },
      { "mousePos", &static_QUType_ptr, "const QPoint&", QUParameter::In }
    };
  static const QUMethod slot_0 = {"slotTableClicked", 4, param_slot_0 };
  static const QUMethod slot_1 = {"slotTableSelectionChanged", 0, 0 };

  static const QMetaData slot_tbl[] =
    {
      { "slotTableClicked(int,int,int,const QPoint&)", &slot_0, QMetaData::Protected },
      { "slotTableSelectionChanged()", &slot_1, QMetaData::Protected }
    };

  metaObj = QMetaObject::new_metaobject(
              "MetabolitesWidget", parentObject,
              slot_tbl, 2,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);

  cleanUp_MetabolitesWidget.setMetaObject(metaObj);

  return metaObj;
}

void* MetabolitesWidget::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "MetabolitesWidget"))
    return (MetabolitesWidget*)this;

  return QWidget::qt_cast(clname);
}

bool MetabolitesWidget::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0:
      slotTableClicked(static_QUType_int.get(_o + 1), static_QUType_int.get(_o + 2), static_QUType_int.get(_o + 3), *((QPoint*)static_QUType_ptr.get(_o + 4)));
      break;

    case 1:
      slotTableSelectionChanged();
      break;

    default:
      return QWidget::qt_invoke(_id, _o);
    }

  return TRUE;
}

bool MetabolitesWidget::qt_emit(int _id, QUObject* _o)
{
  return QWidget::qt_emit(_id, _o);
}

#ifndef QT_NO_PROPERTIES

bool MetabolitesWidget::qt_property(int _id, int _f, QVariant* _v)
{
  return QWidget::qt_property(_id, _f, _v);
}

#endif // QT_NO_PROPERTIES
