// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCopasiApplication.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/02/22 16:28:44 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

private:
  CopasiUI3Window * mpMainWindow;

  QString mFile;

  bool mStarting;
};

#endif // COPASI_CQCopasiApplication
