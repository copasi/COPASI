// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLViewport.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/05 09:29:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qframe.h>

class CQGLNetworkPainter;
class QScrollBar;
class CLayout;

/**
 * This class is supposed to act as a sort of scrollview for a
 * CQGLNetworkPainter.
 */
class CQGLViewport : public QFrame
  {
    Q_OBJECT

  protected:
    QScrollBar* mpVerticalScrollbar;
    QScrollBar* mpHorizontalScrollbar;
    CQGLNetworkPainter* mpNetworkPainter;

  public:
    /**
     * Constructor.
     */
    CQGLViewport(QWidget* pParent = 0, const char* name = 0, WFlags f = 0);

    /**
     * Destructor.
     */
    virtual ~CQGLViewport();

    const CQGLNetworkPainter* getPainter() const;

    CQGLNetworkPainter* getPainter();

    /**
     * Pass the layout on to the network painters createGraph and set the
     * scrollbar ranges.
     */
    void createGraph(CLayout *lP);

    /**
     * Sets the zoom factor on the network painter and updates the
     *scrollbars.
     */
    void setZoomFactor(double zoom);

    void resetView();

  protected:
    virtual void resizeEvent(QResizeEvent* e);

    void updateScrollbars();

  protected slots:
    void slotVValueChanged(int value);
    void slotHValueChanged(int value);

  public slots:
    void updateWidget();
  };
