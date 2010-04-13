// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.h,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/13 13:56:48 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#if !defined HANDLER_PROGRESS_BAR
#define HANDLER_PROGRESS_BAR

#include <qdatetime.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QMutex>
#include <QWaitCondition>

#include "utilities/CProcessReport.h"
#include "CQProgressDialog.h"

template < typename > class CVector;
class CQProgressItem;

/**
 *  This is used to call the progress bar code
 *  We do not want to call gui stuff directly from the CModel.
 */
class CProgressBar : public CQProgressDialog, public CProcessReport
{
  Q_OBJECT
public:
  CProgressBar(QWidget* parent = 0,
               const char* name = 0,
               bool modal = false,
               Qt::WFlags fl = 0);

  virtual ~CProgressBar();

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finsh, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const CCopasiParameter::Type & type
   * @param const void * pValue
   * @param const void * pEndValue = NULL
   * @return unsigned C_INT32 handle
   */
  virtual unsigned C_INT32 addItem(const std::string & name,
                                   const CCopasiParameter::Type & type,
                                   const void * pValue,
                                   const void * pEndValue = NULL);

  /**
   * Report process on item handle. If the return value is false the calling
   * process must halt execution and return.
   * @param const unsigned C_INT32 & handle
   * @param bool continue
   */
  virtual bool progress(const unsigned C_INT32 & handle);

  /**
   * Check whether processing shall proceed. If the return value is false
   * the calling process must halt execution and return. This method is
   * provided so that lenghty processing without advances in any of the
   * reporting items can check whether continuation is requested.
   * @param bool continue
   */
  virtual bool proceed();

  /**
   * Reset item handle. This means that the value of the item has changed
   * but not as part of a continous process. If you run multiple processes
   * call reset beween them. If the return value is false the calling
   * process must halt execution and return.
   * @param const unsigned C_INT32 & handle
   * @param bool continue
   */
  virtual bool reset(const unsigned C_INT32 & handle);

  /**
   * Indicate that all items are finished reporting. All item handles loose
   * their validity. If the return value is false the calling
   * process must halt execution and return.
   * @param bool continue
   */
  virtual bool finish();

  /**
   * Indicate that item handle is finished reporting. The handle of that
   * item is no longer valid after the call. If the return value is false
   * the calling process must halt execution and return.
   * @param const unsigned C_INT32 & handle
   * @param bool continue
   */
  virtual bool finish(const unsigned C_INT32 & handle);

  /**
   * Set the name of the process.
   * @param const std::string & name
   * @return sucess
   */
  virtual bool setName(const std::string & name);

protected:
  virtual void closeEvent(QCloseEvent *e);

  bool mSlotFinished;
  QMutex mMutex;
  QWaitCondition mWaitSlot;

private:
  CVector< CQProgressItem * > mProgressItemList;

  QDateTime mNextEventProcessing;

  QWidget * mpMainWidget;

signals:
  void processEvents();
  void addProgressItem(const unsigned int handle);
  void setProgressBarName(QString name);
  void finishProgressBar(const unsigned int handle);

protected slots:

  virtual void slotProcessEvents();

  virtual void slotAddItem(const unsigned int handle);

  virtual void slotSetName(QString name);

  virtual void slotFinish(const unsigned int handle);

};

#endif
