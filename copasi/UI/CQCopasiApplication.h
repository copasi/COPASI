// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQCopasiApplication
#define COPASI_CQCopasiApplication

#include <QApplication>

class QString;
class CopasiUI3Window;

class CQCopasiApplication: public QApplication
{
  Q_OBJECT

public:
  CQCopasiApplication(int & argc, char ** argv);

  virtual ~CQCopasiApplication();

  virtual bool event(QEvent * pEvent);

  void setMainWindow(CopasiUI3Window * pMainWindow);

#ifdef COPASI_DEBUG
  bool notify(QObject *, QEvent *);
#endif

private:
  CopasiUI3Window * mpMainWindow;

  QString mFile;

  bool mStarting;
};

#endif // COPASI_CQCopasiApplication
