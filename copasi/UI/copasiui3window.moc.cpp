/****************************************************************************
 ** CopasiUI3Window meta object code from reading C++ file 'copasiui3window.h'
 **
 **
 ** WARNING! All changes made in this file will be lost!
 *****************************************************************************/

#undef QT_NO_COMPAT
#include "copasiui3window.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.*. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CopasiUI3Window::className() const
  {
    return "CopasiUI3Window";
  }

QMetaObject *CopasiUI3Window::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CopasiUI3Window;

#ifndef QT_NO_TRANSLATION
QString CopasiUI3Window::tr(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("CopasiUI3Window", s, c, QApplication::DefaultCodec);
  else
    return QString::fromLatin1(s);
}

#ifndef QT_NO_TRANSLATION_UTF8
QString CopasiUI3Window::trUtf8(const char *s, const char *c)
{
  if (qApp)
    return qApp->translate("CopasiUI3Window", s, c, QApplication::UnicodeUTF8);
  else
    return QString::fromUtf8(s);
}

#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CopasiUI3Window::staticMetaObject()
{
  if (metaObj)
    return metaObj;

  QMetaObject* parentObject = QMainWindow::staticMetaObject();
  static const QUMethod slot_0 = {"slotFileOpen", 0, 0 };
  static const QUMethod slot_1 = {"slotFileSave", 0, 0 };
  static const QUMethod slot_2 = {"slotFileSaveAs", 0, 0 };
  static const QUMethod slot_3 = {"newDoc", 0, 0 };
  static const QUMethod slot_4 = {"slotFilePrint", 0, 0 };
  static const QUMethod slot_5 = {"about", 0, 0 };
  static const QUMethod slot_6 = {"aboutQt", 0, 0 };

  static const QMetaData slot_tbl[] =
    {
      { "slotFileOpen()", &slot_0, QMetaData::Protected },

      { "slotFileSave()", &slot_1, QMetaData::Protected },
      { "slotFileSaveAs()", &slot_2, QMetaData::Protected },
      { "newDoc()", &slot_3, QMetaData::Protected },
      { "slotFilePrint()", &slot_4, QMetaData::Protected },
      { "about()", &slot_5, QMetaData::Protected },
      { "aboutQt()", &slot_6, QMetaData::Protected }
    };

  metaObj = QMetaObject::new_metaobject(
              "CopasiUI3Window", parentObject,
              slot_tbl, 7,
              0, 0,
#ifndef QT_NO_PROPERTIES
              0, 0,
              0, 0,
#endif // QT_NO_PROPERTIES
              0, 0);

  cleanUp_CopasiUI3Window.setMetaObject(metaObj);

  return metaObj;
}

void* CopasiUI3Window::qt_cast(const char* clname)
{
  if (!qstrcmp(clname, "CopasiUI3Window"))
    return (CopasiUI3Window*)this;

  return QMainWindow::qt_cast(clname);
}

bool CopasiUI3Window::qt_invoke(int _id, QUObject* _o)
{
  switch (_id - staticMetaObject()->slotOffset())
    {
    case 0:
      slotFileOpen();
      break;

    case 1:
      slotFileSave();
      break;

    case 2:
      slotFileSaveAs();
      break;

    case 3:
      newDoc();
      break;

    case 4:
      slotFilePrint();
      break;

    case 5:
      about();
      break;

    case 6:
      aboutQt();
      break;

    default:
      return QMainWindow::qt_invoke(_id, _o);
    }

  return TRUE;
}

bool CopasiUI3Window::qt_emit(int _id, QUObject* _o)
{
  return QMainWindow::qt_emit(_id, _o);
}

#ifndef QT_NO_PROPERTIES

bool CopasiUI3Window::qt_property(int _id, int _f, QVariant* _v)
{
  return QMainWindow::qt_property(_id, _f, _v);
}

#endif // QT_NO_PROPERTIES
