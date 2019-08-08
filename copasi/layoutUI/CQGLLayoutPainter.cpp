// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifdef __APPLE__
// this should make sure g++ on apple does not load
// the glext from the 10.4 sdk so that we can load the one provided with COPASI
#define GL_GLEXT_LEGACY
#endif

// SBML includes
#include "copasi/copasi.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "CQFontRenderer.h"
#include "copasi/layout/CLLayoutRenderer.h"
#include "copasi/layout/CLDefaultStyles.h"
#include "copasi/layout/CLLocalRenderInformation.h"
#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/layoutUI/CQQtImageTexturizer.h"
#include "copasi/layoutUI/CQFontRenderer.h"
#include "copasi/utilities/CCopasiMessage.h"

#define GL_GLEXT_PROTOTYPES
#include "CQGLLayoutPainter.h"

// Qt includes
#include <QMouseEvent>
#include <QtCore/QTimer>
#include <QCursor>
#include <QApplication>
#include <QtCore/Qt>

// global includes
#include <limits>
#include <functional>
#include <algorithm>
#ifdef __APPLE__
#include <string>
#include <stdlib.h>
#include <mach-o/dyld.h>
#endif // __APPLE__

// opengl includes
#ifdef _WIN32
# ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
# endif // WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif // WIN32

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#undef GL_GLEXT_LEGACY
# include <GL/glext.h>
#else
#define GLX_GLXEXT_LEGACY
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef HAVE_GL_EXT
# include <GL/glext.h>
#else
# include <copasi/GL/glext.h>
#endif // HAVE_GL_EXT
#ifndef _WIN32
#include <GL/glx.h>
#endif // _WIN32
// somehow glx defines a macro called CursorShape which clashes with the Qt enum of the same name
#undef CursorShape
#endif // __APPLE__

#include "copasi/UI/CQMessageBox.h"

// check that the OpenGL extensions we plan to use are at least defined so that we have the necessary enumerations
#if !defined(GL_EXT_framebuffer_object) || !defined(GL_EXT_framebuffer_multisample)
#error "Error. Your header files do not define the OpenGL macros necessary to compile this program. For further information please see http://www.gamedev.net/community/forums/showfaq.asp?forum_id=25#q5."
#endif // GL_EXT_framebuffer_object

const int CQGLLayoutPainter::MARGIN = 10;

#ifdef _WIN32
// windows seems to declare a macro called max which clashes with the STL
// function
#undef max
#endif // _WIN32

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

CQGLLayoutPainter::CQGLLayoutPainter(const QGLFormat& format, QWidget *parent)
  : QGLWidget(format, parent),
    mInitialized(false),
    mMinX(std::numeric_limits<double>::max()),
    mMinY(std::numeric_limits<double>::max()),
    mMaxX(-std::numeric_limits<double>::max()),
    mMaxY(-std::numeric_limits<double>::max()),
    mCurrentZoom(1.0),
    mCurrentPositionX(mMinX),
    mCurrentPositionY(mMinY),
    mViewportWidth(0),
    mViewportHeight(0),
    mpRenderer(NULL),
    mMousePressPosition(),
    mMouseCurrentPosition(),
    mMouseLastPosition(),
    mMouseButton(Qt::NoButton),
    mDragTimeout(false),
    mState(CQGLLayoutPainter::STATE_NORMAL),
    mpDragPoint(NULL),
    glCheckFramebufferStatusEXTPtr(NULL),
    glGenFramebuffersEXTPtr(NULL),
    glGenRenderbuffersEXTPtr(NULL),
    glDeleteFramebuffersEXTPtr(NULL),
    glDeleteRenderbuffersEXTPtr(NULL),
    glBindFramebufferEXTPtr(NULL),
    glBindRenderbufferEXTPtr(NULL),
    glRenderbufferStorageEXTPtr(NULL),
    glFramebufferRenderbufferEXTPtr(NULL),
    glRenderbufferStorageMultisampleEXTPtr(NULL),
    glBlitFramebufferEXTPtr(NULL)

{
  this->setMouseTracking(true);
}

CQGLLayoutPainter::~CQGLLayoutPainter()
{
  if (this->mpRenderer)
    {
      delete this->mpRenderer;
    }
}

void CQGLLayoutPainter::initializeGL()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // accoring to the OpenGL documentation the blend function below
  // should be the one to be used on smoothed polygons, but when I try this,
  // nothing is displayed at all in the software renderer
  // Maybe the polygons have to be depth sorted first for this to work
  //glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
  glEnable(GL_POLYGON_SMOOTH);
  //glEnable(GL_LINE_SMOOTH);
  glShadeModel(GL_SMOOTH);
  this->mInitialized = true;
}

void CQGLLayoutPainter::resizeGL(int w, int h)
{
  this->mViewportWidth = w;
  this->mViewportHeight = h;

  if (this->mpRenderer && this->mInitialized)
    {
      this->mpRenderer->resize(w, h);
    }
  else
    {
      // setup viewport, projection etc.:
      glViewport(0, 0, (GLint)w, (GLint)h);
      glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
      glLoadIdentity();             // Reset The Projection Matrix
      gluOrtho2D((GLdouble)mCurrentPositionX,
                 (GLdouble)(mCurrentPositionX + w),
                 (GLdouble)(mCurrentPositionY + h),
                 (GLdouble)mCurrentPositionY); // y: 0.0 is bottom left instead of top left as in SBML
      glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix
    }
}

void CQGLLayoutPainter::paintGL()
{
  if (this->isVisible())
    {
      if (this->mpRenderer)
        {
          this->resizeGL(this->width(), this->height());
        }

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
      draw();
    }
}

void CQGLLayoutPainter::draw()
{
  glLoadIdentity();

  if (mpRenderer)
    {
      CCopasiMessage::clearDeque();
      mpRenderer->draw_layout();

      // display any error messages
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          CQMessageBox::critical(this, "Render Error",
                                 CCopasiMessage::getAllMessageText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }
}

void CQGLLayoutPainter::setZoomFactor(double zoom)
{
  if (mpRenderer != NULL && zoom != mpRenderer->getZoomFactor())
    {
      this->mpRenderer->setZoomFactor(zoom);
      this->mCurrentZoom = zoom;

      if (this->isVisible())
        {
          this->resizeGL(this->width(), this->height());
          this->updateGL();
        }
    }
}

double CQGLLayoutPainter::getZoomFactor() const
{
  double zoom = 1.0;

  if (this->mpRenderer)
    {
      zoom = this->mpRenderer->getZoomFactor();
    }

  return zoom;
}

void CQGLLayoutPainter::setCurrentPosition(double x, double y)
{
  if (this->mCurrentPositionX != x || this->mCurrentPositionY != y)
    {
      this->mCurrentPositionX = x;
      this->mCurrentPositionY = y;

      if (this->mpRenderer)
        {
          this->mpRenderer->setX(x);
          this->mpRenderer->setY(y);
        }

      this->update();
    }
}

void CQGLLayoutPainter::update()
{
  // only update if we have a renderer, otherwise we might call OpenGL
  // functions before OpenGL has been initialized
  if (this->mpRenderer && this->isVisible())
    {
      this->resizeGL(this->width(), this->height());
      this->updateGL();
    }
}

void CQGLLayoutPainter::setCurrentPositionX(double x)
{
  if (this->mCurrentPositionX != x)
    {
      this->mCurrentPositionX = x;

      if (this->mpRenderer != NULL)
        {
          this->mpRenderer->setX(x);
        }

      this->update();
    }
}

void CQGLLayoutPainter::setCurrentPositionY(double y)
{
  if (this->mCurrentPositionY != y)
    {
      this->mCurrentPositionY = y;

      if (this->mpRenderer != NULL)
        {
          this->mpRenderer->setY(y);
        }

      this->update();
    }
}

double CQGLLayoutPainter::getCurrentPositionX() const
{
  return this->mCurrentPositionX;
}

double CQGLLayoutPainter::getCurrentPositionY() const
{
  return this->mCurrentPositionY;
}

void CQGLLayoutPainter::resetView()
{
  this->setZoomFactor(1.0);
  this->setCurrentPosition(this->minX(), this->minY());
}

/**
 * Calculates the ratio that is needed to fit the diagram on the current viewport
 * and sets this as the zoom factor.
 * The method returns the new zoom factor.
 */
double CQGLLayoutPainter::fitToScreen()
{
  double zoom = 1.0;
  double width = this->mMaxX - this->mMinX;
  double height = this->mMaxY - this->mMinY;
  double wRatio = this->mViewportWidth / width;
  double hRatio = this->mViewportHeight / height;

  if (wRatio > hRatio)
    {
      zoom = hRatio;
    }
  else
    {
      zoom = wRatio;
    }

  this->setZoomFactor(zoom);
  this->setCurrentPosition(this->mMinX, this->mMinY);
  return zoom;
}

void CQGLLayoutPainter::setMinX(double x)
{
  mMinX = x;
}

void CQGLLayoutPainter::setMinY(double y)
{
  mMinY = y;
}
void CQGLLayoutPainter::setMaxX(double x)
{
  mMaxX = x;
}

void CQGLLayoutPainter::setMaxY(double y)
{
  mMaxY = y;
}

void CQGLLayoutPainter::setBounds(const QRectF& rect)
{
  setBounds(rect.left(), rect.top(), rect.right(), rect.bottom());
}

void CQGLLayoutPainter::setBounds(double minX, double minY, double maxX, double maxY)
{
  mMinX = minX;
  mMinY = minY;
  mMaxX = maxX;
  mMaxY = maxY;
}

double CQGLLayoutPainter::minX() const
{
  return this->mMinX;
}

double CQGLLayoutPainter::minY() const
{
  return this->mMinY;
}

double CQGLLayoutPainter::maxX() const
{
  return this->mMaxX;
}

double CQGLLayoutPainter::maxY() const
{
  return this->mMaxY;
}

void CQGLLayoutPainter::calculateAndAssignBounds(CLayout* pLayout)
{
  if (pLayout == NULL) return;

  // update minX, minY, maxX and maxY
  CLBoundingBox bb = pLayout->calculateBoundingBox();
  this->mMinX = bb.getPosition().getX();
  this->mMinY = bb.getPosition().getY();

  // move into the origin
  CLPoint differenceToOrigin(
    -mMinX,
    -mMinY
    , -bb.getPosition().getZ()
  );
  pLayout->moveBy(differenceToOrigin);

  if (mMinX > 0)
    bb.getDimensions().setWidth(bb.getDimensions().getWidth() + mMinX);

  if (mMinY > 0)
    bb.getDimensions().setHeight(bb.getDimensions().getHeight() + mMinY);

  mMinX = 0;
  mMinY = 0;

  if (pLayout->getDimensions().getWidth() > bb.getDimensions().getWidth())
    {
      this->mMaxX = pLayout->getDimensions().getWidth() + this->mMinX;
    }
  else
    {
      this->mMaxX = bb.getDimensions().getWidth() + this->mMinX;
    }

  if (pLayout->getDimensions().getHeight() > bb.getDimensions().getHeight())
    {
      this->mMaxY = pLayout->getDimensions().getHeight() + this->mMinY;
    }
  else
    {
      this->mMaxY = bb.getDimensions().getHeight() + this->mMinY;
    }

  this->mMinX -= MARGIN;
  this->mMinY -= MARGIN;
  this->setCurrentPosition(this->mMinX, this->mMinY);

  // call resize to set the correct viewport
  if (this->isVisible())
    {
      this->resizeGL(this->width(), this->height());
      // draw the layout
      this->updateGL();
    }
}

void CQGLLayoutPainter::update(const CDataModel* pDatamodel, CLayout* pLayout, const CLRenderInformationBase* pRenderInfo, const QString& baseDir)
{
  // delete the current renderer if there is one
  if (this->mpRenderer)
    {
      delete this->mpRenderer;
    }

  // create a new renderer with the given options
  if (dynamic_cast<const CLLocalRenderInformation*>(pRenderInfo))
    {
      this->mpRenderer = new CLLayoutRenderer(pLayout, static_cast<const CLLocalRenderInformation*>(pRenderInfo), &pDatamodel->getListOfLayouts()->getListOfGlobalRenderInformationObjects(), pDatamodel->getModel(), baseDir.toLatin1().data());
      // set the text renderer
    }
  else
    {
      this->mpRenderer = new CLLayoutRenderer(pLayout, static_cast<const CLGlobalRenderInformation*>(pRenderInfo), &pDatamodel->getListOfLayouts()->getListOfGlobalRenderInformationObjects(), pDatamodel->getModel(), baseDir.toLatin1().data());
    }

  if (this->mpRenderer)
    {
      this->mpRenderer->set_font_renderer(new CQFontRenderer());
      this->mpRenderer->setImageTexturizer(new CQQtImageTexturizer());
    }

  calculateAndAssignBounds(pLayout);
}

void CQGLLayoutPainter::change_style(const CLRenderInformationBase* pRenderInfo, bool defaultStyle)
{
  const CLLocalRenderInformation* pLRI = dynamic_cast<const CLLocalRenderInformation*>(pRenderInfo);

  if (pLRI != NULL)
    {
      this->mpRenderer->change_style(pLRI);
    }
  else
    {
      this->mpRenderer->change_style(dynamic_cast<const CLGlobalRenderInformation*>(pRenderInfo), defaultStyle);
    }

  if (this->isVisible())
    {
      this->updateGL();
    }
}

void CQGLLayoutPainter::mousePressEvent(QMouseEvent* pMouseEvent)
{
  if (this->mpRenderer != NULL)
    {
      // actually we only store the position of the click here
      // Selection occurs once the button is released
      // because a click can also start a drag selection
      // we need the position within the scene
      this->mMouseButton = pMouseEvent->button();
      this->mMousePressPosition = pMouseEvent->pos();
      this->mMouseCurrentPosition = this->mMousePressPosition;
      this->mMouseLastPosition = this->mMousePressPosition;
      this->mDragTimeout = false;

      // check if the left mouse button has been pressed.
      if (this->mMouseButton == Qt::LeftButton)
        {

          if (this->mMouseButton == Qt::LeftButton)
            {
              if (QApplication::keyboardModifiers() != Qt::ShiftModifier  &&
                  QApplication::keyboardModifiers() != Qt::ControlModifier)
                this->mpRenderer->clearSelection();

              // most often if someone clicks the canvas they want to move something
              // there is no reason to assume that they want to drag something else
              // so we are going to first select whatever is under the mouse click
              std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> hits = this->mpRenderer->getObjectsAtViewportPosition(this->mMouseCurrentPosition.x(), this->mMouseCurrentPosition.y());
              std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>::iterator it = hits.begin(), endit = hits.end();

              while (it != endit)
                {
                  if (dynamic_cast<CLTextGlyph*>(*it) == NULL)
                    if (dynamic_cast<CLCompartmentGlyph*>(*it) == NULL)
                      this->mpRenderer->addToSelection(*it);

                  ++it;
                }
            }

          // start a timer that fires after QApplication::startDragTime
          // if the mouse button is still down when the event fires, we might start a drag operation
          // depending on how far the mouse pointer has been moved
          QTimer::singleShot(QApplication::startDragTime(), this, SLOT(timeout()));
        }

      this->update_status_and_cursor();
    }
}

/**
 * This slot is called if a timer runs down that is started on a left mouse press
 */
void CQGLLayoutPainter::timeout()
{
  // if the mouse button has been released already, we don't start a drag operation
  if (this->mMouseButton != Qt::NoButton)
    {
      this->mDragTimeout = true;
    }
}

std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> removeTextGlyphs(std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>& hits)
{
  std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> result;
  std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>::iterator it = hits.begin();

  while (it != hits.end())
    {
      CLTextGlyph* glyph = dynamic_cast<CLTextGlyph*>((*it));
      CLMetabReferenceGlyph* refGlyph = dynamic_cast<CLMetabReferenceGlyph*>((*it));

      if (glyph == NULL && refGlyph == NULL)
        {
          result.insert(*it);
        }

      ++it;
    }

  return result;
}

/**
 * Gets called when the mouse is released on the scene.
 */
void CQGLLayoutPainter::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
  this->mMouseCurrentPosition = pMouseEvent->pos();

  if (pMouseEvent->buttons() == Qt::NoButton)
    {
      switch (this->mState)
        {
          case CQGLLayoutPainter::STATE_SELECTION:

            // the user has been selecting something by a selection rectangle
            // make the selection;
            if (this->mpRenderer != NULL)
              {
                double minX = this->mMousePressPosition.x() < this->mMouseCurrentPosition.x() ? this->mMousePressPosition.x() : this->mMouseCurrentPosition.x();
                double minY = this->mMousePressPosition.y() < this->mMouseCurrentPosition.y() ? this->mMousePressPosition.y() : this->mMouseCurrentPosition.y();
                double maxX = this->mMousePressPosition.x() > this->mMouseCurrentPosition.x() ? this->mMousePressPosition.x() : this->mMouseCurrentPosition.x();
                double maxY = this->mMousePressPosition.y() > this->mMouseCurrentPosition.y() ? this->mMousePressPosition.y() : this->mMouseCurrentPosition.y();
                std::pair<double, double> coords1 = this->mpRenderer->convert_to_model_space(minX, minY);
                std::pair<double, double> coords2 = this->mpRenderer->convert_to_model_space(maxX, maxY);
                std::vector<CLGraphicalObject*> objects = this->mpRenderer->getObjectsInBoundingBox(coords1.first, coords1.second, coords2.first, coords2.second, false);
                std::vector<CLGraphicalObject*>::iterator it = objects.begin(), endit = objects.end();
                Qt::KeyboardModifiers modifiers = pMouseEvent->modifiers();

                if (modifiers == Qt::NoModifier)
                  {
                    this->mpRenderer->clearSelection();

                    while (it != endit)
                      {
                        this->mpRenderer->addToSelection(*it);
                        ++it;
                      }
                  }
                else if (modifiers == (Qt::ControlModifier | Qt::ShiftModifier))
                  {
                    // intersection
                    std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

                    while (it != endit)
                      {
                        if (selection.find(*it) == selection.end())
                          {
                            this->mpRenderer->removeFromSelection(*it);
                          }

                        ++it;
                      }
                  }
                else if (modifiers == Qt::ControlModifier)
                  {
                    // subtraction
                    std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

                    while (it != endit)
                      {
                        if (selection.find(*it) != selection.end())
                          {
                            this->mpRenderer->removeFromSelection(*it);
                          }

                        ++it;
                      }
                  }
                else if (modifiers == Qt::ShiftModifier)
                  {
                    // addition
                    std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

                    while (it != endit)
                      {
                        if (selection.find(*it) == selection.end())
                          {
                            this->mpRenderer->addToSelection(*it);
                          }

                        ++it;
                      }
                  }

                this->mpRenderer->setSelectionBox(NULL);
                std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

                if (selection.size() == 1 &&
                    ((dynamic_cast<const CLMetabReferenceGlyph*>(*selection.begin()) && static_cast<const CLMetabReferenceGlyph*>(*selection.begin())->getCurve().getNumCurveSegments() != 0) ||
                     (dynamic_cast<const CLReactionGlyph*>(*selection.begin()) && static_cast<const CLReactionGlyph*>(*selection.begin())->getCurve().getNumCurveSegments())
                    )
                   )
                  {
                    emit singleCurveSelected(true);
                  }
                else
                  {
                    emit singleCurveSelected(false);
                  }
              }

            this->mState = CQGLLayoutPainter::STATE_NORMAL;

            if (this->isVisible())
              {
                this->updateGL();
              }

            break;

          case CQGLLayoutPainter::STATE_DRAG:

            // the user has been dragging the selected abstract_merge_items
            // and now we have to see if we have to merge items
            // move the selected objects
            if (this->mpRenderer != NULL)
              {
                std::pair<double, double> coords1 = this->mpRenderer->convert_to_model_space(this->mMouseCurrentPosition.x(), this->mMouseCurrentPosition.y());
                std::pair<double, double> coords2 = this->mpRenderer->convert_to_model_space(this->mMouseLastPosition.x(), this->mMouseLastPosition.y());
                double dx = coords1.first - coords2.first;
                double dy = coords1.second - coords2.second;

                // check if we are currently dragging a basepoint
                if (mpDragPoint != NULL)
                  {
                    // set the dragpoint to NULL
                    this->mpDragPoint->setX(this->mpDragPoint->getX() + dx);
                    this->mpDragPoint->setY(this->mpDragPoint->getY() + dy);
                    this->mpDragPoint = NULL;
                  }
                else
                  {
                    if (pMouseEvent->modifiers() & Qt::ControlModifier)
                      {
                        this->mpRenderer->move_selection(dx, dy, false);
                      }
                    else
                      {
                        this->mpRenderer->move_selection(dx, dy, true);
                      }
                  }

                emit documentChanged();

                if (this->isVisible())
                  {
                    this->updateGL();
                  }
              }

            this->mState = CQGLLayoutPainter::STATE_NORMAL;
            break;

          case CQGLLayoutPainter::STATE_NORMAL:

            // check if there is an item under the mouse
            if (this->mpRenderer)
              {
                std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> hits = this->mpRenderer->getObjectsAtViewportPosition(this->mMouseCurrentPosition.x(), this->mMouseCurrentPosition.y());

                hits = removeTextGlyphs(hits);

                if (!hits.empty())
                  {
                    // if there is only one element in hits, we change the selection
                    // depending on the keyboard buttons that were pressed simultaneously
                    if ((pMouseEvent->modifiers() & Qt::ControlModifier) && !(pMouseEvent->modifiers() & Qt::ShiftModifier))
                      {
                        // subtraction mode
                        // TODO enable selection cycling
                        // for now find the first hit object that is not already selected
                        std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>::iterator it = hits.begin(), endit = hits.end();

                        while (it != endit)
                          {
                            if (this->mpRenderer->isSelected(*it))
                              {
                                this->mpRenderer->removeFromSelection(*it);

                                if (this->isVisible())
                                  {
                                    this->updateGL();
                                  }

                                break;
                              }

                            ++it;
                          }
                      }
                    else if ((pMouseEvent->modifiers() & Qt::ShiftModifier) && !(pMouseEvent->modifiers() & Qt::ControlModifier))
                      {
                        // addition mode
                        // TODO enable selection cycling
                        //
                        // for now find the first hit object that is not already selected
                        std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>::iterator it = hits.begin(), endit = hits.end();

                        while (it != endit)
                          {
                            if (!this->mpRenderer->isSelected(*it))
                              {
                                this->mpRenderer->addToSelection(*it);

                                if (this->isVisible())
                                  {
                                    this->updateGL();
                                  }

                                break;
                              }

                            ++it;
                          }
                      }
                    else
                      {
                        // intersection mode (Ctrl + Shift) is handled the same as if no modifer is pressed.
                        //
                        // treat all others as if no modifier has been pressed
                        // if there are more elements in hits, we see if there is one selected and
                        // if there is, we deselect it and select the one that comes after it.
                        std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>::iterator pos;
                        CLGraphicalObject* pObject = NULL;

                        if ((hits.size() > 1) && (this->mpRenderer->getSelection().size() == 1) &&
                            (pos = std::find(hits.begin(), hits.end(), *(this->mpRenderer->getSelection().begin()))) != hits.end())
                          {
                            ++pos;

                            if (pos == hits.end())
                              {
                                pos = hits.begin();
                              }

                            pObject = *pos;
                          }
                        else
                          {
                            pObject = *(hits.begin());
                          }

                        this->mpRenderer->clearSelection();
                        this->mpRenderer->addToSelection(pObject);

                        if (this->isVisible())
                          {
                            this->updateGL();
                          }
                      }
                  }
                else
                  {
                    if (!this->mpRenderer->getSelection().empty())
                      {
                        this->mpRenderer->clearSelection();

                        if (this->isVisible())
                          {
                            this->updateGL();
                          }
                      }
                  }

                std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

                if (selection.size() == 1 &&
                    ((dynamic_cast<const CLMetabReferenceGlyph*>(*selection.begin()) && static_cast<const CLMetabReferenceGlyph*>(*selection.begin())->getCurve().getNumCurveSegments() != 0) ||
                     (dynamic_cast<const CLReactionGlyph*>(*selection.begin()) && static_cast<const CLReactionGlyph*>(*selection.begin())->getCurve().getNumCurveSegments() != 0)
                    )
                   )
                  {
                    emit singleCurveSelected(true);
                  }
                else
                  {
                    emit singleCurveSelected(false);
                  }
              }

            break;
            // didn't add a default statement so that I will get warning when I
            // miss an enum
        }

      this->mMouseButton = Qt::NoButton;
      this->mState = CQGLLayoutPainter::STATE_NORMAL;
      this->mDragTimeout = false;
      // change the cursor
      this->update_status_and_cursor();
    }
}

/**
 * Gets called when the mouse is moved on the scene.
 */
void CQGLLayoutPainter::mouseMoveEvent(QMouseEvent* pMouseEvent)
{
  // set the current position
  this->mMouseLastPosition = this->mMouseCurrentPosition;
  this->mMouseCurrentPosition = pMouseEvent->pos();

  switch (this->mState)
    {
      case CQGLLayoutPainter::STATE_SELECTION:

        // update the selection box
        if (this->mpRenderer != NULL)
          {
            double minX = this->mMousePressPosition.x() < this->mMouseCurrentPosition.x() ? this->mMousePressPosition.x() : this->mMouseCurrentPosition.x();
            double minY = this->mMousePressPosition.y() < this->mMouseCurrentPosition.y() ? this->mMousePressPosition.y() : this->mMouseCurrentPosition.y();
            double maxX = this->mMousePressPosition.x() > this->mMouseCurrentPosition.x() ? this->mMousePressPosition.x() : this->mMouseCurrentPosition.x();
            double maxY = this->mMousePressPosition.y() > this->mMouseCurrentPosition.y() ? this->mMousePressPosition.y() : this->mMouseCurrentPosition.y();
            std::pair<double, double> coords1 = this->mpRenderer->convert_to_model_space(minX, minY);
            std::pair<double, double> coords2 = this->mpRenderer->convert_to_model_space(maxX, maxY);
            CLBoundingBox bb(CLPoint(coords1.first, coords1.second), CLDimensions(coords2.first - coords1.first, coords2.second - coords1.second));
            this->mpRenderer->setSelectionBox(&bb);

            if (this->isVisible())
              {
                this->updateGL();
              }
          }

        break;

      case CQGLLayoutPainter::STATE_DRAG:

        if (this->mpRenderer != NULL)
          {
            std::pair<double, double> coords1 = this->mpRenderer->convert_to_model_space(this->mMouseCurrentPosition.x(), this->mMouseCurrentPosition.y());
            std::pair<double, double> coords2 = this->mpRenderer->convert_to_model_space(this->mMouseLastPosition.x(), this->mMouseLastPosition.y());
            double dx = coords1.first - coords2.first;
            double dy = coords1.second - coords2.second;

            // check if we are currently dragging a basepoint
            if (mpDragPoint != NULL)
              {
                // set the dragpoint to NULL
                this->mpDragPoint->setX(this->mpDragPoint->getX() + dx);
                this->mpDragPoint->setY(this->mpDragPoint->getY() + dy);
              }
            else
              {
                if (pMouseEvent->modifiers() & Qt::ControlModifier)
                  {
                    this->mpRenderer->move_selection(dx, dy, false);
                  }
                else
                  {
                    this->mpRenderer->move_selection(dx, dy, true);
                  }
              }

            // there is no need to emit the changed signal here
            // since the user (normally) releases the mouse button
            // before anything that can react to the change takes effect
            if (this->isVisible())
              {
                this->updateGL();
              }
          }

        break;

      case CQGLLayoutPainter::STATE_NORMAL:

        // check if a drag timout has occured and the user has moved the
        // mouse far enough to count as a drag
        if ((this->mDragTimeout == true) && ((this->mMousePressPosition - this->mMouseCurrentPosition).manhattanLength() >= QApplication::startDragDistance()))
          {
            // check if the drag start is on a selected item.
            // if so, move the selection
            // else create a new selection based on the rectangle covered by the drag
            // operation
            std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

            // we have to check hits on basepoints first since they are the smallest
            // entities so far that can be dragged.
            if (selection.size() == 1)
              {
                // now we have to check if the click was on a basepoint
                CLMetabReferenceGlyph* pSRG = dynamic_cast<CLMetabReferenceGlyph*>(*selection.begin());
                CLCurve* pCurve = NULL;

                if (pSRG != NULL)
                  {
                    if (pSRG->getCurve().getNumCurveSegments() > 0)
                      {
                        pCurve = &pSRG->getCurve();
                      }
                  }
                else
                  {
                    CLReactionGlyph* pRG = dynamic_cast<CLReactionGlyph*>(*selection.begin());

                    if (pRG != NULL && pRG->getCurve().getNumCurveSegments() > 0)
                      {
                        pCurve = &pRG->getCurve();
                      }
                  }

                if (pCurve != NULL)
                  {
                    size_t i, iMax = pCurve->getNumCurveSegments();
                    CLLineSegment* pLS = NULL;
                    std::pair<double, double> coords = this->mpRenderer->convert_to_model_space(this->mMousePressPosition.x(), this->mMousePressPosition.y());
                    CLPoint pressPoint(coords.first, coords.second);

                    for (i = 0; i < iMax ; ++i)
                      {
                        pLS = pCurve->getSegmentAt(i);
                        CLPoint* pP = &pLS->getStart();

                        if (this->mpRenderer->distance(*pP, pressPoint) <= 5.0 / this->mCurrentZoom)
                          {
                            this->mpDragPoint = pP;
                            this->mState = CQGLLayoutPainter::STATE_DRAG;
                            break;
                          }

                        pP = &pLS->getEnd();

                        if (this->mpRenderer->distance(*pP, pressPoint) <= 5.0 / this->mCurrentZoom)
                          {
                            this->mpDragPoint = pP;
                            this->mState = CQGLLayoutPainter::STATE_DRAG;
                            break;
                          }

                        pP = &pLS->getBase1();

                        if (this->mpRenderer->distance(*pP, pressPoint) <= 5.0 / this->mCurrentZoom)
                          {
                            this->mpDragPoint = pP;
                            this->mState = CQGLLayoutPainter::STATE_DRAG;
                            break;
                          }

                        pP = &pLS->getBase2();

                        if (this->mpRenderer->distance(*pP, pressPoint) <= 5.0 / this->mCurrentZoom)
                          {
                            this->mpDragPoint = pP;
                            this->mState = CQGLLayoutPainter::STATE_DRAG;
                            break;
                          }
                      }
                  }
              }

            if (this->mpDragPoint == NULL)
              {
                std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> hits = this->mpRenderer->getObjectsAtViewportPosition(this->mMousePressPosition.x(), this->mMousePressPosition.y());

                if (!hits.empty())
                  {
                    // see if the mouse was clicked on a selected item
                    std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>::iterator it = hits.begin(), endit = hits.end();

                    while (it != endit)
                      {
                        if (selection.find(*it) != selection.end())
                          {
                            this->mState = CQGLLayoutPainter::STATE_DRAG;
                            // TODO it might be a bit smoother if we already move the object here as well
                            // TODO but this is only sugar coating and not essential
                          }

                        ++it;
                      }
                  }
              }

            if (this->mState == CQGLLayoutPainter::STATE_NORMAL)
              {
                this->mState = CQGLLayoutPainter::STATE_SELECTION;

                // set the selection frame
                if (this->mpRenderer != NULL)
                  {
                    double minX = this->mMousePressPosition.x() < this->mMouseCurrentPosition.x() ? this->mMousePressPosition.x() : this->mMouseCurrentPosition.x();
                    double minY = this->mMousePressPosition.y() < this->mMouseCurrentPosition.y() ? this->mMousePressPosition.y() : this->mMouseCurrentPosition.y();
                    double maxX = this->mMousePressPosition.x() > this->mMouseCurrentPosition.x() ? this->mMousePressPosition.x() : this->mMouseCurrentPosition.x();
                    double maxY = this->mMousePressPosition.y() > this->mMouseCurrentPosition.y() ? this->mMousePressPosition.y() : this->mMouseCurrentPosition.y();
                    std::pair<double, double> coords1 = this->mpRenderer->convert_to_model_space(minX, minY);
                    std::pair<double, double> coords2 = this->mpRenderer->convert_to_model_space(maxX, maxY);
                    CLBoundingBox bb(CLPoint(coords1.first, coords1.second), CLDimensions(coords2.first - coords1.first, coords2.second - coords1.second));
                    this->mpRenderer->setSelectionBox(&bb);

                    if (this->isVisible())
                      {
                        this->updateGL();
                      }
                  }
              }
          }

        break;
        // didn't add a default statement so that I will get a warning when I
        // miss an enum
    }

  this->update_status_and_cursor();
}

/**
 * This method sets the correct cursor and updates status messages.
 */
void CQGLLayoutPainter::update_status_and_cursor()
{
  // in order to find out what type of cursor we need to set, we need
  // a) the position
  // b) which buttons are pressed
  // c) which keys are pressed
  // d) the state of the layout

  // first we check the state
  Qt::CursorShape shape = Qt::ArrowCursor;

  switch (this->mState)
    {
      case CQGLLayoutPainter::STATE_DRAG:
        shape = Qt::ClosedHandCursor;
        emit status_message("Drag item(s) out of their parent to break merge.", 0);
        break;

      case CQGLLayoutPainter::STATE_SELECTION:
        // make the cursor a crosshair
        shape = Qt::CrossCursor;
        emit status_message("Drag cursor to make selection.", 0);
        break;

      case CQGLLayoutPainter::STATE_NORMAL:
        // we check if we are currently over another item
        bool selectedHit = false;

        if (this->mpRenderer != NULL)
          {
            std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

            if (!selection.empty())
              {
                // maybe the user was not on a line, but on the basepoint of a bezier segment
                // this would not be covered by the above test and has to be handled separatly
                if (selection.size() == 1)
                  {
                    const CLMetabReferenceGlyph* pSRG = dynamic_cast<const CLMetabReferenceGlyph*>(*selection.begin());
                    const CLCurve* pCurve = NULL;

                    if (pSRG != NULL && pSRG->getCurve().getNumCurveSegments() != 0)
                      {
                        pCurve = &pSRG->getCurve();
                      }
                    else
                      {
                        const CLReactionGlyph* pRG = dynamic_cast<const CLReactionGlyph*>(*selection.begin());

                        if (pRG != NULL && pRG->getCurve().getNumCurveSegments() != 0)
                          {
                            pCurve = &pRG->getCurve();
                          }
                      }

                    if (pCurve != NULL)
                      {
                        size_t i, iMax = pCurve->getNumCurveSegments();
                        std::pair<double, double> coords = this->mpRenderer->convert_to_model_space(this->mMouseCurrentPosition.x(), this->mMouseCurrentPosition.y());
                        CLPoint currentPoint(coords.first, coords.second);
                        // we only need to consider the basepoints of cubic beziers since the method
                        // that checks for a line hit takes care of the other points
                        const CLPoint* pP = NULL;
                        const CLLineSegment* pLS = NULL;

                        for (i = 0; i < iMax ; ++i)
                          {
                            pLS = pCurve->getSegmentAt(i);

                            if (pLS->isBezier())
                              {
                                pP = &pLS->getBase1();

                                if (this->mpRenderer->distance(*pP, currentPoint) <= 5.0 / this->mCurrentZoom)
                                  {
                                    selectedHit = true;
                                    break;
                                  }

                                pP = &pLS->getBase2();

                                if (this->mpRenderer->distance(*pP, currentPoint) <= 5.0 / this->mCurrentZoom)
                                  {
                                    selectedHit = true;
                                    break;
                                  }
                              }
                          }
                      }
                  }

                if (!selectedHit)
                  {
                    std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> hits = this->mpRenderer->getObjectsAtViewportPosition(this->mMouseCurrentPosition.x(), this->mMouseCurrentPosition.y());

                    if (!hits.empty())
                      {
                        std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize>::iterator it = hits.begin(), endit = hits.end(), pos;

                        while (it != endit && !selectedHit)
                          {
                            selectedHit = (selection.find(*it) != selection.end());
                            ++it;
                          }
                      }
                  }
              }
          }

        if (selectedHit)
          {
            // if we are over a selected item
            // the cursor needs to be the open hand
            shape = Qt::OpenHandCursor;
            emit status_message("Drag item to new destination.", 0);
          }
        else
          {
            // if the button is pressed, the user probably wants to start a
            // selection
            if (this->mMouseButton == Qt::LeftButton)
              {
                shape = Qt::CrossCursor;
                emit status_message("Drag to select an area.", 0);
              }
            else
              {
                emit status_message("Click and drag to select an area.", 0);
              }
          }

        break;
    }

  if (this->cursor().shape() != shape)
    {
      this->setCursor(shape);
    }
}

/**
 * Reverts the currently selected curve if there is one.
 * If nothing is selected or the single selected item is not a curve,
 * nothing is done.
 */
void CQGLLayoutPainter::revertCurve()
{
  std::set<CLGraphicalObject*>& selection = this->mpRenderer->getSelection();

  if (selection.size() == 1)
    {
      if (dynamic_cast<const CLMetabReferenceGlyph*>(*selection.begin()) && static_cast<const CLMetabReferenceGlyph*>(*selection.begin())->getCurve().getNumCurveSegments() != 0)
        {
          const CLCurve* pCurve = this->mpRenderer->revert_curve(&static_cast<const CLMetabReferenceGlyph*>(*selection.begin())->getCurve());
          static_cast<CLMetabReferenceGlyph*>(*selection.begin())->setCurve(*pCurve);
          delete pCurve;

          if (this->isVisible())
            {
              this->updateGL();
            }
        }
      else if (dynamic_cast<const CLReactionGlyph*>(*selection.begin()) && static_cast<const CLReactionGlyph*>(*selection.begin())->getCurve().getNumCurveSegments() != 0)
        {
          const CLCurve* pCurve = this->mpRenderer->revert_curve(&static_cast<const CLReactionGlyph*>(*selection.begin())->getCurve());
          static_cast<CLReactionGlyph*>(*selection.begin())->setCurve(*pCurve);
          delete pCurve;

          if (this->isVisible())
            {
              this->updateGL();
            }
        }
    }
}

/**
 * Returns the width of the current drawing area.
 */
unsigned int CQGLLayoutPainter::getViewportWidth() const
{
  return this->mViewportWidth;
}

/**
 * Returns the height of the current viewport area.
 */
unsigned int CQGLLayoutPainter::getViewportHeight() const
{
  return this->mViewportHeight;
}

/**
 * Returns the width of the layout part that is currently displayed.
 */
double CQGLLayoutPainter::getCurrentWidth() const
{
  return (double)this->mViewportWidth / (double)this->mCurrentZoom;
}

/**
 * Returns the width of the layout part that is currently displayed.
 */
double CQGLLayoutPainter::getCurrentHeight() const
{
  return (double)this->mViewportHeight / (double)this->mCurrentZoom;
}

/**
 * Returns the currently selected items.
 */
std::set<CLGraphicalObject*> CQGLLayoutPainter::getSelection()
{
  std::set<CLGraphicalObject*> sel;

  if (this->mpRenderer != NULL)
    {
      sel = this->mpRenderer->getSelection();
    }

  return sel;
}

/**
 * Sets the selection to the items in the given set.
 */
void CQGLLayoutPainter::setSelection(const std::set<CLGraphicalObject*>& selection)
{
  if (this->mpRenderer == NULL) return;

  this->mpRenderer->getSelection() = selection;
}

/**
 * Sets the aspect for the renderer.
 */
void CQGLLayoutPainter::setAspect(double aspect)
{
  if (this->mpRenderer != NULL)
    {
      this->mpRenderer->setAspect(aspect);
    }
}

/**
 * Returns the aspect from the renderer.
 */
double CQGLLayoutPainter::getAspect() const
{
  double aspect = 0.0;

  if (this->mpRenderer != NULL)
    {
      aspect = this->mpRenderer->getAspect();
    }

  return aspect;
}

/**
 * Exports a bitmap of the given size to
 * the file with the given name.
 */
GLubyte* CQGLLayoutPainter::export_bitmap(double x, double y, double width, double height, unsigned int imageWidth, unsigned int imageHeight, bool drawSelection)
{
  this->makeCurrent();
  GLubyte* pImageData = NULL;
  const char* extensionsString = (const char*)glGetString(GL_EXTENSIONS);

  // TODO this method of testing if the extension is supported is not very safe, we should check if there is
  // a whitespace character or npos after the position
  if (std::string(extensionsString).find("GL_EXT_framebuffer_object") == std::string::npos)
    {
      // give an error message that the image is to large
      CQMessageBox::critical(this, tr("Framebuffers not supported"),
                             tr("This version of OpenGL does not support the framebuffer extension.\nSorry, can't create the bitmap."));
      return NULL;
    }

  // check if the size of the final image is ok.
  double size = imageWidth * imageHeight * 4;

  // TODO: again this arbitrary limit seems odd to me
  // I don't think we should write images that are larger than 500MB
  if (size >= 5e8)
    {
      // give an error message that the image is to large
      CQMessageBox::critical(this, tr("Image too large"),
                             tr("Sorry, refusing to create images that are larger than 500MB."));
      return NULL;
    }

  // set busy cursor
  QCursor cursor = this->cursor();
  this->setCursor(Qt::BusyCursor);

  // if draw selection is false, we first have to store the selection somewhere
  // reset the current selection
  std::set<CLGraphicalObject*> selection;

  if (!drawSelection)
    {
      selection = this->getSelection();
    }

  //
  size /= 4;
  // if the image size is larger than a certain size, we have to subdivide the drawing into smaller bits.
  GLint chunk_size = 0;
  glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &chunk_size);

  chunk_size /= 8;

  if (chunk_size > 0)
    {
      // create the framebuffer object, the render buffer objects and bind them
      GLuint fboName = 0;
      GLuint blitFBOName = 0;
      GLuint* rbuffers = NULL;
      GLuint* multisampleBuffers = NULL;
      bool multisample_supported = false;
      GLint samples = 0;

      if (std::string(extensionsString).find("GL_EXT_framebuffer_multisample") != std::string::npos)
        {
          // enable after the bugs have been fixed
          multisample_supported = true;
          // check how many samples we can use
          glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
          // we don't want to do more than 4x AA
          samples = (samples > 4) ? 4 : samples;
        }

      if (!multisample_supported || samples < 2)
        {
          CQMessageBox::warning(this, tr("Multisampling unsupported"),
                                tr("Your implementation does not support multisampling of\nframebuffer objects. The resulting\bitmap might not look very nice."));
        }

      // if we are not on an apple, we have to initialize the functions
      // for the OpenGL extensions
      this->initialize_extension_functions();

      if (imageWidth > (unsigned int)chunk_size || imageHeight > (unsigned int)chunk_size)
        {
          double currentX = x;
          double currentY = y;

          // create storage for the complete image
          try
            {
              pImageData = new GLubyte[imageWidth * imageHeight * 4];
            }
          catch (...)
            {
              CQMessageBox::critical(this, tr("Error creating image"),
                                     tr("Could not create image. Maybe you ran out of memory."));
              // set normal cursor
              this->setCursor(cursor);
              return NULL;
            }

          unsigned int xSteps = imageWidth / chunk_size;
          unsigned int ySteps = imageHeight / chunk_size;
          unsigned int restX = imageWidth % chunk_size;
          unsigned int restY = imageHeight % chunk_size;
          unsigned int i = 0, j = 0;
          int k;
          double xModelStep = chunk_size * width / imageWidth;
          double yModelStep = chunk_size * height / imageHeight;
          const uchar* pSrc = NULL;
          uchar* pDst = NULL;
          // For each step we reposition the gl widget, create the pixmap and add the content to the large pixmap
          //
          GLubyte* pTmpData = NULL;
          bool success = true;

          for (i = 0; i < ySteps && success; ++i)
            {
              currentX = x;

              for (j = 0; j < xSteps && success; ++j)
                {
                  success = this->draw_bitmap(currentX, currentY, xModelStep, yModelStep, chunk_size, chunk_size, fboName, blitFBOName, &rbuffers, &multisampleBuffers, &pTmpData, samples);

                  if (success)
                    {
                      for (k = 0; k < chunk_size; ++k)
                        {
                          // copy the data
                          pSrc = pTmpData + k * chunk_size * 4;
                          pDst = pImageData + (i * chunk_size + k) * imageWidth * 4 + j * chunk_size * 4;
                          memcpy(pDst, pSrc, 4 * chunk_size);
                        }
                    }

                  currentX += xModelStep;
                }

              currentY += yModelStep;
            }

          // delete the current render buffer
          this->destroy_buffers(fboName, rbuffers, blitFBOName, multisampleBuffers);

          if (rbuffers != NULL)
            {
              delete[] rbuffers;
              rbuffers = NULL;
            }

          if (multisampleBuffers != NULL)
            {
              delete[] multisampleBuffers;
              multisampleBuffers = NULL;
            }

          // check if there are some pixels left at the right edge
          if (success && restX != 0)
            {
              double tmpWidth = restX * width / imageWidth;
              // go back to the top
              currentY = y;

              for (i = 0; i < ySteps && success ; ++i)
                {
                  success = this->draw_bitmap(currentX, currentY, tmpWidth, yModelStep, restX, chunk_size, fboName, blitFBOName, &rbuffers, &multisampleBuffers, &pTmpData, samples);

                  // if rendering failed, we make sure the buffer for the image
                  // data is deleted so that it will not be used further down
                  if (success)
                    {
                      for (k = 0; k < chunk_size; ++k)
                        {
                          // copy the data
                          pSrc = pTmpData + k * restX * 4;
                          pDst = pImageData + (i * chunk_size + k) * imageWidth * 4 + j * chunk_size * 4;
                          memcpy(pDst, pSrc, 4 * restX);
                        }
                    }

                  currentY += yModelStep;
                }

              // delete the current render buffer
              this->destroy_buffers(fboName, rbuffers, blitFBOName, multisampleBuffers);

              if (rbuffers != NULL)
                {
                  delete[] rbuffers;
                  rbuffers = NULL;
                }

              if (multisampleBuffers != NULL)
                {
                  delete[] multisampleBuffers;
                  multisampleBuffers = NULL;
                }
            }

          if (success && restY != 0)
            {
              // go back to the right
              double tmpHeight = restY * height / imageHeight;
              currentX = x;

              for (j = 0; j < xSteps; ++j)
                {
                  success = this->draw_bitmap(currentX, currentY, xModelStep, tmpHeight, chunk_size, restY, fboName, blitFBOName, &rbuffers, &multisampleBuffers, &pTmpData, samples);

                  if (success)
                    {
                      for (k = 0; k < (int)restY; ++k)
                        {
                          // copy the data
                          pSrc = pTmpData + k * chunk_size * 4;
                          pDst = pImageData + (i * chunk_size + k) * imageWidth * 4 + j * chunk_size * 4;
                          memcpy(pDst, pSrc, 4 * chunk_size);
                        }
                    }

                  currentX += xModelStep;
                }

              // delete the current render buffer
              this->destroy_buffers(fboName, rbuffers, blitFBOName, multisampleBuffers);

              if (rbuffers != NULL)
                {
                  delete[] rbuffers;
                  rbuffers = NULL;
                }

              if (multisampleBuffers != NULL)
                {
                  delete[] multisampleBuffers;
                  multisampleBuffers = NULL;
                }

              // check if there are some pixels left
              if (success && restX != 0)
                {
                  double tmpWidth = restX * width / imageWidth;
                  // set the correct viewport size
                  success = this->draw_bitmap(currentX, currentY, tmpWidth, tmpHeight, restX, restY, fboName, blitFBOName, &rbuffers, &multisampleBuffers, &pTmpData, samples);

                  if (success)
                    {
                      for (k = 0; k < (int)restY; ++k)
                        {
                          // copy the data
                          pSrc = pTmpData + k * restX * 4;
                          pDst = pImageData + (i * chunk_size + k) * imageWidth * 4 + j * chunk_size * 4;
                          memcpy(pDst, pSrc, 4 * restX);
                        }
                    }

                  // delete the current render buffer
                  this->destroy_buffers(fboName, rbuffers, blitFBOName, multisampleBuffers);

                  if (rbuffers != NULL)
                    {
                      delete[] rbuffers;
                      rbuffers = NULL;
                    }

                  if (multisampleBuffers != NULL)
                    {
                      delete[] multisampleBuffers;
                      multisampleBuffers = NULL;
                    }
                }
            }

          // if rendering failed, we make sure the buffer for the image
          // data is deleted so that it will not be used further down
          if (!success)
            {
              if (pImageData != NULL) delete[] pImageData;

              pImageData = NULL;
            }

          if (pTmpData != NULL) delete[] pTmpData;
        }
      else
        {
          // we just draw it in one go
          bool success = this->draw_bitmap(x, y, width, height, imageWidth, imageHeight, fboName, blitFBOName, &rbuffers, &multisampleBuffers, &pImageData, samples);

          // if rendering failed, we make sure the buffer for the image
          // data is deleted so that it will not be used further down
          if (!success && pImageData != NULL)
            {
              delete[] pImageData;
              pImageData = NULL;
            }

          // delete the buffers
          this->destroy_buffers(fboName, rbuffers, blitFBOName, multisampleBuffers);

          if (rbuffers != NULL) delete[] rbuffers;

          if (multisampleBuffers != NULL) delete[] multisampleBuffers;
        }

      // if we are not on an apple, we have to deinitialize the functions
      // for the OpenGL extensions again because we can not reuse them
      // for the next export sicne they are context dependent and the context might have changed
      // This is not absolutly necessary, but it might help finding problems.
      this->clear_extension_functions();

      // if the stored selection is not empty, we have to restore the selection
      if (!selection.empty())
        {
          this->setSelection(selection);
        }

      // need to convert from RGBA to ARGB
      if (pImageData != NULL)
        {
          unsigned int i, iMax = imageWidth * imageHeight;

          for (i = 0; i < iMax; ++i)
            {
              // in OpenGL the color values are stored as bytes in
              // the order RR GG BB AA
              // In Qt the color value has to be an int 0xAARRGGBB
              // so the order in memory depends on the endianess of
              // the system
              ((GLuint*)pImageData)[i] = pImageData[i * 4 + 3] * 16777216 | ((GLuint)pImageData[i * 4]) * 65536 | ((GLuint)pImageData[i * 4 + 1]) * 256 | ((GLuint)pImageData[i * 4 + 2]);
            }
        }
    }

  // set normal cursor
  this->setCursor(cursor);

  return pImageData;
}

/**
 * Renders the specified part of the model into a bitmap.
 * The bitmap is returned as RGBA data in pImageData.
 * If pImageData is pointing to a null pointer, memory is alocated and the caller has to release it.
 * If drawing the bitmap is successfull, true is returned, else false is
 * returned.
 */
bool CQGLLayoutPainter::draw_bitmap(double x, double y, double width, double height, unsigned int imageWidth, unsigned int imageHeight, GLuint& fbo, GLuint& multiFBO, GLuint** rbuffers, GLuint** multiRBuffers, GLubyte** pImageData, GLuint samples)
{
  // make sure all the functions that we need are actually initialized
  assert(glGenFramebuffersEXTPtr != NULL);
  assert(glGenRenderbuffersEXTPtr != NULL);
  assert(glBindFramebufferEXTPtr != NULL);
  assert(glBindRenderbufferEXTPtr != NULL);
  assert(glRenderbufferStorageEXTPtr != NULL);
  assert(glFramebufferRenderbufferEXTPtr != NULL);
  this->makeCurrent();

  // create the framebuffer object, the render buffer objects and bind them
  if (fbo == 0)
    {
      //std::cout << "Frame buffer object must be created." << std::endl;
      // create the framebuffer object
      (*glGenFramebuffersEXTPtr)(1, &fbo);
      assert(fbo != 0);
      (*glBindFramebufferEXTPtr)(GL_FRAMEBUFFER_EXT, fbo);
      //std::cout << "Bound framebuffer object: " << fbo << std::endl;
    }

  if ((*rbuffers) == NULL)
    {
      //std::cout << "The render buffers need to be created." << std::endl;
      // create the render buffers and create storage for them
      (*rbuffers) = new GLuint[2];
      (*glGenRenderbuffersEXTPtr)(2, (*rbuffers));
      assert((*rbuffers)[0] != 0);
      assert((*rbuffers)[1] != 0);
      (*glBindRenderbufferEXTPtr)(GL_RENDERBUFFER_EXT, (*rbuffers)[0]);
      //std::cout << "render color buffer: " << (*rbuffers)[0] << std::endl;
      (*glRenderbufferStorageEXTPtr)(GL_RENDERBUFFER_EXT, GL_RGBA, imageWidth, imageHeight);
      (*glBindRenderbufferEXTPtr)(GL_RENDERBUFFER_EXT, (*rbuffers)[1]);
      //std::cout << "render depth buffer: " << (*rbuffers)[1] << std::endl;
      (*glRenderbufferStorageEXTPtr)(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, imageWidth, imageHeight);
    }

  // attach the color buffer
  //std::cout << "attaching color buffer: " << (*rbuffers)[0] << std::endl;
  (*glFramebufferRenderbufferEXTPtr)(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, (*rbuffers)[0]);
  // attach the depth buffer
  //std::cout << "attaching depth buffer: " << (*rbuffers)[1] << std::endl;
  (*glFramebufferRenderbufferEXTPtr)(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, (*rbuffers)[1]);

  if (samples > 1)
    {
      //std::cout << "We are doing multismpling." << std::endl;
      // make sure all the functions that we need are actually initialized
      assert(glRenderbufferStorageMultisampleEXTPtr != NULL);
      assert(glBlitFramebufferEXTPtr != NULL);

      // create the framebuffer and render buffers for multisampling
      if (multiFBO == 0)
        {
          // std::cout << "Usinging multisample FBO." << std::endl;
          (*glGenFramebuffersEXTPtr)(1, &multiFBO);
          assert(multiFBO != 0);
          //std::cout << "generated multisample fbo: " << multiFBO << std::endl;
          (*glBindFramebufferEXTPtr)(GL_FRAMEBUFFER_EXT, multiFBO);
        }

      if ((*multiRBuffers) == NULL)
        {
          //std::cout << "generating multisample buffers." << std::endl;
          // create the render buffers and create storage for them
          (*multiRBuffers) = new GLuint[2];
          (*glGenRenderbuffersEXTPtr)(2, (*multiRBuffers));
          //std::cout << "created multisamplebuffers: " << (*multiRBuffers)[0] << " " << (*multiRBuffers)[1] << std::endl;
          assert((*multiRBuffers)[0] != 0);
          assert((*multiRBuffers)[1] != 0);
          (*glBindRenderbufferEXTPtr)(GL_RENDERBUFFER_EXT, (*multiRBuffers)[0]);
          (*glRenderbufferStorageMultisampleEXTPtr)(GL_RENDERBUFFER_EXT, samples, GL_RGBA, imageWidth, imageHeight);
          //std::cout << "Bound multisample color buffer: " << (*multiRBuffers)[0] << std::endl;
          (*glBindRenderbufferEXTPtr)(GL_RENDERBUFFER_EXT, (*multiRBuffers)[1]);
          (*glRenderbufferStorageMultisampleEXTPtr)(GL_RENDERBUFFER_EXT, samples, GL_DEPTH_COMPONENT, imageWidth, imageHeight);
          //std::cout << "Bound multisample depth buffer: " << (*multiRBuffers)[1] << std::endl;
        }

      // attach the color buffer
      //std::cout << "attaching multisample color buffer: " << (*multiRBuffers)[0] << std::endl;
      (*glFramebufferRenderbufferEXTPtr)(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, (*multiRBuffers)[0]);
      // attach the depth buffer
      //std::cout << "attaching multisample depth buffer: " << (*multiRBuffers)[1] << std::endl;
      (*glFramebufferRenderbufferEXTPtr)(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, (*multiRBuffers)[1]);
    }

  // remember if we have to go on
  QString messageHeader, message;
  bool fail = !this->check_fbo_status(messageHeader, message);

  if (fail == false && (*pImageData) == NULL)
    {
      try
        {
          (*pImageData) = new GLubyte[imageWidth * imageHeight * 4];
        }
      catch (...)
        {
          messageHeader = tr("Error creating image");
          message = tr("Could not create image. Maybe you ran out of memory.");
          fail = true;
          (*pImageData) = NULL;
        }
    }

  // remember the old values
  if (fail == false)
    {
      bool visible = this->isVisible();

      if (visible)
        {
          this->setVisible(false);
        }

      double origX = this->getCurrentPositionX();
      double origY = this->getCurrentPositionY();
      double origWidth = this->mViewportWidth;
      double origHeight = this->mViewportHeight;
      double origZoom = this->getZoomFactor();
      double origAspect = this->getAspect();
      double zoom = (double)imageHeight / height;
      double aspect = (double)imageWidth / (width * zoom);
      this->setZoomFactor(zoom);
      this->setAspect(aspect);
      this->setCurrentPosition(x, y);
      this->resizeGL(imageWidth, imageHeight);
      // now we should be able to actually draw the image
      assert(this->mpRenderer != NULL);

      if (this->mpRenderer != NULL)
        {
          this->mpRenderer->draw_layout();
        }

      // now we need to get the pixels back from the render buffer
      if (samples > 1)
        {
          // we need to blit the image from the multisample buffer to the normal buffer
          (*glBindFramebufferEXTPtr)(GL_READ_FRAMEBUFFER_EXT, multiFBO);
          //std::cout << "Bound buffer for reading: " << multiFBO << std::endl;
          (*glBindFramebufferEXTPtr)(GL_DRAW_FRAMEBUFFER_EXT, fbo);
          //std::cout << "Bound buffer for drawing: " << fbo << std::endl;
          // check the status
          fail = !this->check_fbo_status(messageHeader, message);

          if (fail == false)
            {
              //std::cout << "blitting data from read buffer into draw buffer" << std::endl;
              (*glBlitFramebufferEXTPtr)(0, 0, imageWidth, imageHeight, 0, 0, imageWidth, imageHeight, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
              // now we need to bind the blit buffer in order to read from it
              //std::cout << "Binding framebuffer to read pixels: " << fbo << std::endl;
              (*glBindFramebufferEXTPtr)(GL_FRAMEBUFFER_EXT, fbo);
              fail = !this->check_fbo_status(messageHeader, message);
            }
        }

      if (fail == false)
        {
          //std::cout << "reading pixels from read buffer." << std::endl;
          glReadPixels(0, 0, imageWidth, imageHeight, GL_RGBA, GL_UNSIGNED_BYTE, *pImageData);
          // the picture is flipped horizontally, so we have to turn it around
          GLubyte* pTmpData = new GLubyte[imageWidth * 4];
          unsigned int i, iMax = imageHeight / 2;

          for (i = 0; i < iMax; ++i)
            {
              // save the first line
              memcpy(pTmpData, (*pImageData) + i * 4 * imageWidth, imageWidth * 4);
              // copy the iMax-1-i the line to the ith line
              memcpy((*pImageData) + i * 4 * imageWidth, (*pImageData) + (imageHeight - 1 - i)*imageWidth * 4, imageWidth * 4);
              // copy pTmpData into the iMax-1-i th line
              memcpy((*pImageData) + (imageHeight - 1 - i) * 4 * imageWidth, pTmpData, imageWidth * 4);
            }
        }

      // reset the zoom and the aspect
      this->setZoomFactor(origZoom);
      this->setAspect(origAspect);
      this->setCurrentPosition(origX, origY);
      this->resizeGL(origWidth, origHeight);

      if (visible)
        {
          this->setVisible(true);
        }
    }

  // issue the error message and reset the state
  if (fail == true)
    {
      CQMessageBox::critical(this, messageHeader,
                             message);
    }

  return !fail;
}

/**
 * Destroys the passed in render and framebuffers.
 */
void CQGLLayoutPainter::destroy_buffers(GLuint& fbo, GLuint* rbuffers, GLuint& multiFBO, GLuint* multiRBuffers)
{
  // make sure all the functions that we need are actually initialized
  assert(glDeleteFramebuffersEXTPtr != NULL);
  assert(glDeleteRenderbuffersEXTPtr != NULL);

  if (rbuffers != NULL)(*glDeleteRenderbuffersEXTPtr)(2, rbuffers);

  if (multiRBuffers != NULL)(*glDeleteRenderbuffersEXTPtr)(2, multiRBuffers);

  (*glDeleteFramebuffersEXTPtr)(1, &fbo);
  (*glDeleteFramebuffersEXTPtr)(1, &multiFBO);
  fbo = 0;
  multiFBO = 0;
}

/**
 * Checks the state of the currently bound framebuffer.
 * If the framebuffer is valid, true is returned, if it is invalid,
 * the return value is false and messageHeader and message contain a mesage
 * header and a message to display to the user.
 */
bool CQGLLayoutPainter::check_fbo_status(QString& messageHeader, QString& message)
{
  bool success = false;
  messageHeader = tr("Error creating image");
  // make sure all the functions that we need are actually initialized
  assert(glCheckFramebufferStatusEXTPtr != NULL);
  GLenum status = (*glCheckFramebufferStatusEXTPtr)(GL_FRAMEBUFFER_EXT);

  switch (status)
    {
      case GL_FRAMEBUFFER_COMPLETE_EXT:
        // everything is OK
        success = true;
        break;

      case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
        message = tr("Could not create framebuffer object (INCOMPLETE_ATTACHMENT). ");
        break;

      case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        message = tr("Could not create framebuffer object (INCOMPLETE_DIMENSIONS). ");
        break;

      case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        message = tr("Could not create framebuffer object (INCOMPLETE_MISSING_ATTACHMENT).");
        break;

      case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
        message = tr("Could not create framebuffer object (INCOMPLETE_UNSUPPORTED). ");
        break;

      default:
        message = tr("Could not create framebuffer object (UNKNOWN). ");
        break;
    }

  return success;
}

/**
 * On non apple systems, we need to get the pointers to extension functions.
 */
void CQGLLayoutPainter::initialize_extension_functions()
{
#ifdef _WIN32
  glCheckFramebufferStatusEXTPtr = (PFNGLCHECKFRAMEBUFFERSTATUSEXT)wglGetProcAddress("glCheckFramebufferStatusEXT");
  glGenFramebuffersEXTPtr = (PFNGLGENFRAMEBUFFERSEXT)wglGetProcAddress("glGenFramebuffersEXT");
  glGenRenderbuffersEXTPtr = (PFNGLGENRENDERBUFFERSEXT)wglGetProcAddress("glGenRenderbuffersEXT");
  glDeleteFramebuffersEXTPtr = (PFNGLDELETEFRAMEBUFFERSEXT)wglGetProcAddress("glDeleteFramebuffersEXT");
  glDeleteRenderbuffersEXTPtr = (PFNGLDELETERENDERBUFFERSEXT)wglGetProcAddress("glDeleteRenderbuffersEXT");
  glBindFramebufferEXTPtr = (PFNGLBINDFRAMEBUFFEREXT)wglGetProcAddress("glBindFramebufferEXT");
  glBindRenderbufferEXTPtr = (PFNGLBINDRENDERBUFFEREXT)wglGetProcAddress("glBindRenderbufferEXT");
  glRenderbufferStorageEXTPtr = (PFNGLRENDERBUFFERSTORAGEEXT)wglGetProcAddress("glRenderbufferStorageEXT");
  glFramebufferRenderbufferEXTPtr = (PFNGLFRAMEBUFFERRENDERBUFFEREXT)wglGetProcAddress("glFramebufferRenderbufferEXT");
  glRenderbufferStorageMultisampleEXTPtr = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXT)wglGetProcAddress("glRenderbufferStorageMultisampleEXT");
  glBlitFramebufferEXTPtr = (PFNGLBLITFRAMEBUFFEREXT)wglGetProcAddress("glBlitFramebufferEXT");
#else
#ifndef __APPLE__
  glCheckFramebufferStatusEXTPtr = (PFNGLCHECKFRAMEBUFFERSTATUSEXT)glXGetProcAddressARB((const GLubyte*)"glCheckFramebufferStatusEXT");
  glGenFramebuffersEXTPtr = (PFNGLGENFRAMEBUFFERSEXT)glXGetProcAddressARB((const GLubyte*)"glGenFramebuffersEXT");
  glGenRenderbuffersEXTPtr = (PFNGLGENRENDERBUFFERSEXT)glXGetProcAddressARB((const GLubyte*)"glGenRenderbuffersEXT");
  glDeleteFramebuffersEXTPtr = (PFNGLDELETEFRAMEBUFFERSEXT)glXGetProcAddressARB((const GLubyte*)"glDeleteFramebuffersEXT");
  glDeleteRenderbuffersEXTPtr = (PFNGLDELETERENDERBUFFERSEXT)glXGetProcAddressARB((const GLubyte*)"glDeleteRenderbuffersEXT");
  glBindFramebufferEXTPtr = (PFNGLBINDFRAMEBUFFEREXT)glXGetProcAddressARB((const GLubyte*)"glBindFramebufferEXT");
  glBindRenderbufferEXTPtr = (PFNGLBINDRENDERBUFFEREXT)glXGetProcAddressARB((const GLubyte*)"glBindRenderbufferEXT");
  glRenderbufferStorageEXTPtr = (PFNGLRENDERBUFFERSTORAGEEXT)glXGetProcAddressARB((const GLubyte*)"glRenderbufferStorageEXT");
  glFramebufferRenderbufferEXTPtr = (PFNGLFRAMEBUFFERRENDERBUFFEREXT)glXGetProcAddressARB((const GLubyte*)"glFramebufferRenderbufferEXT");
  glRenderbufferStorageMultisampleEXTPtr = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXT)glXGetProcAddressARB((const GLubyte*)"glRenderbufferStorageMultisampleEXT");
  glBlitFramebufferEXTPtr = (PFNGLBLITFRAMEBUFFEREXT)glXGetProcAddressARB((const GLubyte*)"glBlitFramebufferEXT");
#else
  glCheckFramebufferStatusEXTPtr = (PFNGLCHECKFRAMEBUFFERSTATUSEXT)MyNSGLGetProcAddress("glCheckFramebufferStatusEXT");
  glGenFramebuffersEXTPtr = (PFNGLGENFRAMEBUFFERSEXT)MyNSGLGetProcAddress("glGenFramebuffersEXT");
  glGenRenderbuffersEXTPtr = (PFNGLGENRENDERBUFFERSEXT)MyNSGLGetProcAddress("glGenRenderbuffersEXT");
  glDeleteFramebuffersEXTPtr = (PFNGLDELETEFRAMEBUFFERSEXT)MyNSGLGetProcAddress("glDeleteFramebuffersEXT");
  glDeleteRenderbuffersEXTPtr = (PFNGLDELETERENDERBUFFERSEXT)MyNSGLGetProcAddress("glDeleteRenderbuffersEXT");
  glBindFramebufferEXTPtr = (PFNGLBINDFRAMEBUFFEREXT)MyNSGLGetProcAddress("glBindFramebufferEXT");
  glBindRenderbufferEXTPtr = (PFNGLBINDRENDERBUFFEREXT)MyNSGLGetProcAddress("glBindRenderbufferEXT");
  glRenderbufferStorageEXTPtr = (PFNGLRENDERBUFFERSTORAGEEXT)MyNSGLGetProcAddress("glRenderbufferStorageEXT");
  glFramebufferRenderbufferEXTPtr = (PFNGLFRAMEBUFFERRENDERBUFFEREXT)MyNSGLGetProcAddress("glFramebufferRenderbufferEXT");
  glRenderbufferStorageMultisampleEXTPtr = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXT)MyNSGLGetProcAddress("glRenderbufferStorageMultisampleEXT");
  glBlitFramebufferEXTPtr = (PFNGLBLITFRAMEBUFFEREXT)MyNSGLGetProcAddress("glBlitFramebufferEXT");

#endif // __APPLE__
#endif // _WIN32
}

/**
 * Set all pointer to extension function to NULL.
 */
void CQGLLayoutPainter::clear_extension_functions()
{
  glCheckFramebufferStatusEXTPtr = NULL;
  glGenFramebuffersEXTPtr = NULL;
  glGenRenderbuffersEXTPtr = NULL;
  glDeleteFramebuffersEXTPtr = NULL;
  glDeleteRenderbuffersEXTPtr = NULL;
  glBindFramebufferEXTPtr = NULL;
  glBindRenderbufferEXTPtr = NULL;
  glRenderbufferStorageEXTPtr = NULL;
  glFramebufferRenderbufferEXTPtr = NULL;
  glRenderbufferStorageMultisampleEXTPtr = NULL;
  glBlitFramebufferEXTPtr = NULL;
}

#ifdef __APPLE__
#ifndef COPASI_MAC_USE_DEPRECATED_LOOKUP
#include <dlfcn.h>
#endif
void * CQGLLayoutPainter::MyNSGLGetProcAddress(const char *name)
{
#ifndef COPASI_MAC_USE_DEPRECATED_LOOKUP
  return dlsym(RTLD_DEFAULT, name);
#else
  NSSymbol symbol;
  char *symbolName;
  symbolName = (char*)malloc(strlen(name) + 2);

  strcpy(symbolName + 1, name);

  symbolName[0] = '_';
  symbol = NULL;

  if (NSIsSymbolNameDefined(symbolName))
    {
      symbol = NSLookupAndBindSymbol(symbolName);
    }

  free(symbolName);

  return symbol ? NSAddressOfSymbol(symbol) : NULL;
#endif
}

#endif // __APPLE__

// the following methods are used to highlight elements in the diagram
// based on their association to model elements

/**
 * Sets the list of model objects that are to be highlighted in the diagram.
 */
void CQGLLayoutPainter::setHighlightedObjects(const std::set<const CLGraphicalObject*>& highlightedObjects)
{
  this->mpRenderer->setHighlightedObjects(highlightedObjects);
}

/**
 * Returns a const reference to the set of highlighted model objects.
 */
const std::set<const CLGraphicalObject*>& CQGLLayoutPainter::getHighlightedObjects() const
{
  return this->mpRenderer->getHighlightedObjects();
}

/**
 * Returns a reference to the set of highlighted model objects.
 */
std::set<const CLGraphicalObject*>& CQGLLayoutPainter::getHighlightedObjects()
{
  return this->mpRenderer->getHighlightedObjects();
}

/**
 * Sets the highlight color.
 */
void CQGLLayoutPainter::setHighlightColor(const GLfloat c[4])
{
  this->mpRenderer->setHighlightColor(c);
}

/**
 * Sets the fog density value.
 */
void CQGLLayoutPainter::setFogDensity(GLfloat dens)
{
  this->mpRenderer->setFogDensity(dens);
}

/**
 * Sets the fog density value.
 */
GLfloat CQGLLayoutPainter::getFogDensity() const
{
  return this->mpRenderer->getFogDensity();
}

/**
 * Returns a const pointer to the highlight color.
 * The array has a size of 4 elements.
 */
const GLfloat* CQGLLayoutPainter::getHighlightColor() const
{
  return this->mpRenderer->getHighlightColor();
}

/**
 * Sets the fog color.
 */
void CQGLLayoutPainter::setFogColor(const GLfloat c[4])
{
  this->mpRenderer->setFogColor(c);
}

/**
 * Returns a const pointer to the fog color.
 * The array has a size of 4 elements.
 */
const GLfloat* CQGLLayoutPainter::getFogColor() const
{
  return this->mpRenderer->getFogColor();
}

/**
 * Toggles the flag that determines if highlighted objects
 * are actually highlighted or if the rest is fogged out.
 */
void CQGLLayoutPainter::toggleHighlightFlag()
{
  this->mpRenderer->toggleHighlightFlag();
}

/**
 * Toggles the flag that determines if highlighted objects
 * are actually highlighted or if the rest is fogged out.
 */
void CQGLLayoutPainter::setHighlightFlag(bool flag)
{
  this->mpRenderer->setHighlightFlag(flag);
}

/**
 * Returns the highlight flag.
 */
bool CQGLLayoutPainter::getHighlightFlag() const
{
  return this->mpRenderer->getHighlightFlag();
}
