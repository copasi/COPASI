// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLLAYOUTRENDERER_H__
#define CLLAYOUTRENDERER_H__

#include <stack>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <utility>

#include <copasi/layout/utility_classes.h>
#include <copasi/layout/CLRGBAColor.h>
#include "copasi/core/CDataVector.h"

class CLBoundingBox;
class CLCurve;
class CLEllipse;
class CLFontRendererBase;
class CLGlobalRenderInformation;
class CLGradientBase;
class CLGraphicalObject;
class CLGraphicalPrimitive1D;
class CLGraphicalPrimitive2D;
class CLGroup;
class CLayout;
class CLImage;
class CLImageTexturizer;
class CLLinearGradient;
class CLLineEnding;
class CLLineSegment;
class CLLocalRenderInformation;
class CLMetabGlyph;
class CLMetabReferenceGlyph;
class CLPoint;
class CLPolygon;
class CLRadialGradient;
class CLReactionGlyph;
class CLRectangle;
class CLRenderCurve;
class CLRenderPoint;
class CLRenderResolver;
class CLStyle;
class CLText;
class CLTextGlyph;
class CLTransform;
class CModel;
struct CLTextureSpec;
struct CLTextTextureSpec;

#ifdef _WIN32
#define STD_CALL _stdcall
#else
#define STD_CALL
#endif

class CLLayoutRenderer
{
protected:
  std::stack<CLGroupAttributes> mStateList;
  CLGroupAttributes mCurrentAttributes;
  const CModel* mpModel;
  CLayout* mpLayout;
  CLRenderResolver* mpResolver;
  // base directory to resolve relative references to image files
  // in Image objects.
  std::string mBaseDir;
  double mZoomFactor;
  // normally the aspect ratio of a draing will be the same as the
  // widget in which it is displayed, but for rendering into a
  // pixmap with Qt, we might need an aspect that is not 1.0
  // e.g. if the part of the layout the user has chosen
  // does not have the same aspect as the image the user wants to
  // create
  // Setting the aspect to a number other than 1.0 means
  // that the x axis is scaled by this aspect
  double mAspect;
  double mX;
  double mY;
  double mW;
  double mH;
  const CDataVector<CLGlobalRenderInformation>* mpGlobalRenderInfoList;

  // callable that can create a texture for some given font settings and
  // a piece of text
  CLFontRendererBase* mpFontRenderer;

  // stores all resolved colors
  std::map<std::string, CLRGBAColor> mColorMap;

  // stores the gradients
  std::map<std::string, std::pair<const CLGradientBase*, CLTextureSpec*> > mGradientMap;

  // stores the textures for the different text objects
  std::map<CLFontSpec, std::map<std::string, CLTextTextureSpec*> > mFontTextureMap;

  // stores the 1D line stipple textures for all line stipples
  std::map<const std::vector<unsigned int>, const CLLineStippleTexture*> mLinestippleMap;

  // stores the style for each layout object so that we only have to
  // resolve styles once
  // we assume the layout and the render information does not change
  std::map<const CLGraphicalObject*, const CLStyle*> mStyleMap;

  // list of objects that are within the current viewport
  // we only have to draw objects in this list and the list has to be
  // updated each time the viewport changes
  std::vector<const CLGraphicalObject*> mDrawables;

  // stores all line endings
  std::map<std::string, const CLLineEnding*> mLineEndingMap;

  // stores all image textures associated with the filename
  // this way if an image is used mre then once, we only need one texture
  std::map<std::string, const CLTextureSpec*> mImageMap;

  // stores the texture for each TextGlyph
  // this way we have to resolve texts only once and
  // lookup of the textures is easier as well
  std::map<const CLTextGlyph*, const CLTextTextureSpec*> mTextGlyphMap;

  // stores the texture for each text object
  // this way we have to resolve texts only once and
  // lookup of the textures is easier as well
  std::map<const CLText*, const CLTextTextureSpec*> mTextMap;

  // some constants that influence rendering

  // specifies how many segments are used to approximate the rounded
  // corners of a rectangle
  static const unsigned int NUM_CORNER_SEGMENTS;

  // specifies how many segments are used to draw circles and ellipses
  static const unsigned int NUM_CIRCLE_SEGMENTS;

  // specifies how many points to calculate for a cubic bezier curve
  static const unsigned int NUM_BEZIER_POINTS;

  // a constant that is considered to be zero
  static const double ALMOST_ZERO;

  // a constant that limits the size of gradient textures
  static const unsigned int GRADIENT_TEXTURE_SIZE_LIMIT;

  // the disatance between the selection frame and the object
  // this should be independent of the current zoom factor.
  static const double SELECTION_FRAME_WIDTH;

  // a set of available texture names.
  std::set<GLuint> mTextureNames;

  // flag that determines whether the render extension tries to guess
  // species reference roles from associated model objects
  bool mDeduceSpeciesReferenceRoles;

  // this is a set of species reference glyphs where we have deduced and set a role.
  // We need to remember this so that we can delete this information again if the flag is unset
  std::map<const CLMetabReferenceGlyph*, std::string> mSpeciesReferencesWithDeducedRole;

  // this is a set of selected objects
  std::set<CLGraphicalObject*> mSelection;

  // bounding box for the current selection frame
  CLBoundingBox* mpSelectionBox;

  // maps that stores the associations for text glyphs
  std::map<CLTextGlyph*, CLGraphicalObject*> mTextGlyphToGraphicalObjectMap;
  std::map<CLGraphicalObject*, std::set<CLTextGlyph*> > mGraphicalObjectToTextGlyphMap;

  // maps that store the associations for species reference glyphs
  std::map<CLMetabReferenceGlyph*, std::pair<CLMetabGlyph*, bool> > mSpeciesReferenceToSpeciesMap;
  std::map<CLMetabGlyph*, std::set<std::pair<CLMetabReferenceGlyph*, bool> > > mSpeciesToSpeciesReferenceMap;
  std::map<CLMetabReferenceGlyph*, std::pair<CLReactionGlyph*, bool> > mSpeciesReferenceToReactionMap;
  std::map<CLReactionGlyph*, std::set<std::pair<CLMetabReferenceGlyph*, bool> > > mReactionToSpeciesReferenceMap;

  // a class that can create a texture from a jpeg or png image file
  CLImageTexturizer* mpImageTexturizer;

  std::set<const CLGraphicalObject*> mHighlightedObjects;

  // flag that determines whether non-highlighted objects
  // are placed in a fog or if highlighted objects are highlighted
  // with a special color.
  bool mHighlight;

  // color value for highlighting
  GLfloat mHighlightColor[4];

  // color value for the fog
  GLfloat mFogColor[4];

  GLfloat mFogDensity;

  // stores whether the OpenGL functions we need
  // to allocate dynamically have been initialized
  bool mGLFunctionsInitialized;

  // have a function pointer to the glFogCoordf function
  // in the renderer
  // Maybe all this dynamic function initialization should
  // be moved to some global place
  void(STD_CALL *mpGlFogCoordfEXT)(GLfloat);

public:
  /**
   * constructor for global render information
   */
  CLLayoutRenderer(CLayout* pLayout, const CLGlobalRenderInformation* pRenderInformation, const CDataVector<CLGlobalRenderInformation>* pGlobalRenderInformationList, const CModel* pModel, const std::string& baseDir);

  /**
   * constructor for local render information
   */
  CLLayoutRenderer(CLayout* pLayout, const CLLocalRenderInformation* pRenderInformation, const CDataVector<CLGlobalRenderInformation>* pGlobalRenderInformationList, const CModel* pModel, const std::string& baseDir);

  /**
   * destructor.
   */
  ~CLLayoutRenderer();

  /**
   * Analyses the render information and creates some of the textures.
   * First it determines which object are drawn based on the viewport
   * coordinates that are passed in.
   * Next it resolves the styles for all the objects that are to be drawn
   * and it determines the size of the textures.
   * Last it creates all textures.
   */
  void analyse_render_information(double lx, double ly, double rx, double ry);

  /**
   * Method to draw a given layout with a given render resolver.
   */
  void draw_layout();

  /**
   * Resize method that is called whenever the GL window is resized.
   */
  void resize(GLsizei w, GLsizei h);

  /**
   * This method sets the left edge of the viewport.
   */
  void setX(double x);

  /**
   * This method sets the upper edge of the viewport.
   */
  void setY(double y);

  /**
   * Sets the zoom factor.
   */
  void setZoomFactor(double zoomFactor);

  /**
   * Returns the current zoom factor.
   */
  double getZoomFactor() const;

  /**
   * Sets a function that is able to generate a texture spec from
   * some given font settings and a piece of text.
   */
  void set_font_renderer(CLFontRendererBase* pFontRenderer);

  /**
   * This method replaces the current style with the given global render information.
   */
  void change_style(const CLGlobalRenderInformation* pRenderInformation, bool defaultStyle = false);

  /**
   * This method replaces the current style with the given glocal render information.
   */
  void change_style(const CLLocalRenderInformation* pRenderInformation);

  /**
   * Sets whether the render extension is to deduce specie reference roles from associated
   * model objects if there are any.
   */
  void setDeduceSpeciesReferenceRoles(bool deduce);

  /**
   * Returns true or false depending on whether the render extension
   * deduces specie reference roles from associated
   * model objects if there are any.
   */
  bool isSetDeduceSpeciesReferenceRoles() const;

  /**
   * This method adds a graphical object to the set of selected objects.
   */
  void addToSelection(CLGraphicalObject* pObject);

  /**
   * This method removes the given object from the selection if
   * it is selected.
   */
  void removeFromSelection(CLGraphicalObject* pObject);

  /**
   * This method returns a reference to the set of selected objects.
   */
  std::set<CLGraphicalObject*>& getSelection();

  /**
   * This method returns a const reference to the set of selected objects.
   */
  const std::set<CLGraphicalObject*>& getSelection() const;

  /**
   * This method returns true if the given object is part of the selection and false otherwise.
   */
  bool isSelected(const CLGraphicalObject*) const;

  /**
   * This method clears the selection.
   */
  void clearSelection();

  /**
   * This method returns all objects at the given 2D model coordinates.
   * The depth value is ignored.
   */
  std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> getObjectsAt(double x, double y);

  /**
   * This method returns all objects at the given 2D screen coordinates.
   * The depth value is ignored.
   */
  std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> getObjectsAtViewportPosition(unsigned int x, unsigned int y);

  /**
   * Calculates the bounding box of the curve by looking at all the basepoints.
   * The returned boundingbox object has to be deleted by the caller.
   */
  static CLBoundingBox* getCurveBoundingBox(const CLCurve* pCurve);

  /**
   * Returns all objects that are within a given bounding box.
   * The bounding box is determined by lx and ly which are the lower x and lower y values of the box and
   * rx, ry which are the higher x and y values of the box.
   * If partial is true, objects that are only parially included in the
   * box are returned.
   * If it is set to false, an object has to be completely within the
   * bounding box to be returned.
   */
  std::vector<CLGraphicalObject*> getObjectsInBoundingBox(double lx, double ly, double rx, double ry, bool partial = true);

  /**
   * Sets the current selection box.
   * Setting the Box to NULL means that no selection box is drawn.
   */
  void setSelectionBox(const CLBoundingBox* pBox);

  /**
   * returns a point to the current selection box.
   */
  CLBoundingBox* getSelectionBox();

  /**
   * returns a const point to the current selection box.
   */
  const CLBoundingBox* getSelectionBox() const;

  /**
   * Moves a given graphical object by a given vector.
   */
  void move_graphical_object(CLGraphicalObject* pObject, double dx, double dy);

  /**
   * converts the given coordinates from viewport space into model space.
   */
  std::pair<double, double> convert_to_model_space(double x, double y) const;

  /**
   * Moves a given curve object by a given vector.
   * Optionally the method can leave the start and/or the
   * endpoint of the curve where it is.
   */
  void move_curve_object(CLCurve* pCurve, double dx, double dy, bool leaveStartPoint = false, bool leaveEndpoint = false);

  /**
   * Moves the species reference glyph.
   * If the glpyh is represented by a curve,
   * the curves start and endpoint are left as they are.
   */
  void move_species_reference_glyph(CLMetabReferenceGlyph* pSRG, double dx, double dy);

  /**
   * Moves the given text glyph by the given vector.
   * For now, we do not move any associated object becuase it is difficult to
   * create a behaviour that makes sense. E.g. if the associated object is a species
   * glyph, all species reference glyphs might have to be moved.
   * So for now, it is easier to only move the text and if the user wants to move the text
   * with the associated object, he/she needs to move the object instead.
   */
  void move_text_glyph(CLTextGlyph* pTG, double dx, double dy);

  /**
   * Moves the given reaction glyph by the given vector.
   * The startpoints of all associated species reference glyphs are moved as well
   * if they are represented by curves otherwise the comple species reference glyph
   * is moved.
   * Also all associated text glyphs are moved.
   * The moveSelectedAssociations determines whether associated objects that
   * are selected are moved with this object or not.
   * The reason for this is that selected object might be part of the moving
   * process and the objects would in this case be changed twice.
   */
  void move_reaction_glyph(CLReactionGlyph* pRG, double dx, double dy, bool moveSelectedAssociation = false);

  /**
   * Moves the given Species glyph by the given vector.
   * The endpoints of all associated species reference glyphs are moved as well
   * if they are represented by curves.
   * Also all associated text glyphs are moved.
   * The moveSelectedAssociations determines whether associated objects that
   * are selected are moved with this object or not.
   * The reason for this is that selected object might be part of the moving
   * process and the objects would in this case be changed twice.
   */
  void move_species_glyph(CLMetabGlyph* pSG, double dx, double dy, bool moveSelectedAssociations = false);

  /**
   * Moves the current selection.
   * If the moveAssociations falg is set to true,
   * associated objects that are not selected are
   * moved as well.
   * In the case of associated species reference glyphs
   * this means that the start and/or endpoint is moved.
   */
  void move_selection(double dx, double dy, bool moveAssociated = true);

  /**
   * calculates the distance between two layout points.
   */
  static double distance(const CLPoint& p1, const CLPoint& p2);

  /**
   * Checks if the given curve would be visible in the box determined by lx,ly,rx,ry.
   * If the curve in any way intersects the box, true is returned.
   */
  static bool is_curve_visible(const CLCurve& curve, double lx, double ly, double rx, double ry, bool partial);

  /**
   * Checks if the given curve segment would be visible in the box determined by lx,ly,rx,ry.
   * If the curve in any way intersects the box, true is returned.
   */
  static bool is_curve_segment_visible(const CLLineSegment& segment, double lx, double ly, double rx, double ry, bool partial);

  /**
   * reverts the direction of the given curve.
   * The result is returned as a new curve object and
   * the caller has to make sure that the memory for the
   * new curve is freed.
   */
  static CLCurve* revert_curve(const CLCurve* pCurve);

  /**
   * Returns the current aspect.
   */
  double getAspect() const;

  /**
   * Sets the aspect.
   */
  void setAspect(double aspect);

  /**
   * Sets the class that can create textures from a given image file.
   */
  void setImageTexturizer(CLImageTexturizer* pTexturizer);

  // the following methods are used to highlight elements in the diagram
  // based on their association to model elements

  /**
   * Sets the list of model objects that are to be highlighted in the diagram.
   */
  void setHighlightedObjects(const std::set<const CLGraphicalObject*>& highlightedObjects);

  /**
   * Returns a const reference to the set of highlighted model objects.
   */
  const std::set<const CLGraphicalObject*>& getHighlightedObjects() const;

  /**
   * Returns a reference to the set of highlighted model objects.
   */
  std::set<const CLGraphicalObject*>& getHighlightedObjects();

  /**
   * Sets the highlight color.
   */
  void setHighlightColor(const GLfloat c[4]);

  /**
   * Returns a const pointer to the highlight color.
   * The array has a size of 4 elements.
   */
  const GLfloat* getHighlightColor() const;

  /**
   * Sets the fog color.
   */
  void setFogColor(const GLfloat c[4]);

  /**
   * Returns a const pointer to the fog color.
   * The array has a size of 4 elements.
   */
  const GLfloat* getFogColor() const;

  /**
   * Sets the fog density.
   */
  void setFogDensity(GLfloat dens);

  /**
   * Returns the current fog density.
   */
  GLfloat getFogDensity() const;

  /**
   * Toggles the flag that determines if highlighted objects
   * are actually highlighted or if the rest is fogged out.
   */
  void toggleHighlightFlag();

  /**
   * Toggles the flag that determines if highlighted objects
   * are actually highlighted or if the rest is fogged out.
   */
  void setHighlightFlag(bool flag);

  /**
   * Returns the highlight flag.
   */
  bool getHighlightFlag() const;

protected:
  /**
  * Extracts the group attributes from the outermost group of a style.
  */
  static void extract_group_attributes(const CLStyle* pStyle, CLGroupAttributes* attributes);

  /**
   * Extracts the group attributes from the given group.
   */
  static void extract_group_attributes(const CLGroup* pGroup, CLGroupAttributes* attributes);

  /**
   * Method that draws a line with the given start and end points.
   * All the other parameter like color, linewidth etc. have to be set
   * before.
   */
  void draw_line_segment(double x1, double y1, double z1, double x2, double y2, double z2, double line_width, bool texture = false, double s1 = 0.0, double s2 = 0.0);

  /**
   * Method that draws a curve from the layout extension.
   * All the other parameter like color, linewidth etc. have to be set
   * before.
   */
  void draw_curve(const CLCurve* pCurve, bool drawBasepoints = false);

  /**
   * Method that draws a curve from the render extension.
   * All the other parameter like color, linewidth etc. have to be set
   * before.
   */
  void draw_curve(const CLRenderCurve* pCurve, const CLBoundingBox* pBB);

  /**
   * Converts a given RenderPoint which can have relative values into a
   * layout Point with only absolute values.
   */
  static const CLPoint convert_to_absolute(const CLRenderPoint* pRenderPoint, const CLBoundingBox* pBB);

  /**
   * Method to draw an arbitrary object specified by it's bounding box
   * and the style with which it should be drawn.
   */
  void draw_object(const CLStyle* pStyle, const CLBoundingBox* pBB);

  /**
   * Method to draw a text object specified by it's bounding box
   * and the style with which it should be drawn as well as the actual
   * string.
   */
  void draw_text(const CLStyle* pStyle, const CLBoundingBox* pBB, const CLTextTextureSpec* pTexture);

  /**
   * Method to resolve the text that belongs to a text glyph.
   */
  static const std::string resolve_text(const CLTextGlyph* pTextGlyph);

  /**
    * Method that converts a color value or a color id into a color array for
    * OpenGL.
    */
  void resolve_color(const std::string& color, GLubyte array[4]);

  /**
   * Method to draw a render text object.
   */
  void draw_text(const CLText* pText, const CLBoundingBox* pBB);

  /**
   * Method to draw a render ellipse object.
   */
  void draw_ellipse(const CLEllipse* pEllipse, const CLBoundingBox* pBB);

  /**
   * Method to draw a render image object.
   */
  void draw_image(const CLImage* pImage, const CLBoundingBox* pBB);

  /**
   * Method to draw a render polygon object.
   */
  void draw_polygon(const CLPolygon* pPolygon, const CLBoundingBox* pBB);

  /**
   * Method to draw a render rectangle object.
   */
  void draw_rectangle(const CLRectangle* pRectangle, const CLBoundingBox* pBB);

  /**
   * Extracts the attributes from the given one dimensional object.
   */
  static void extract_1d_attributes(const CLGraphicalPrimitive1D* pObject, CLGroupAttributes* attributes);

  /**
   * Extracts the attributes from the given two dimensional object.
   */
  static void extract_2d_attributes(const CLGraphicalPrimitive2D* pObject, CLGroupAttributes* attributes);

  /**
   * Extracts the attributes from the given object with text attribute
   * information.
   * This template function can be used for group and text elements.
   */
  template <typename T>
  static void extract_text_attributes(const T* pObject, CLGroupAttributes* attributes)
  {
    assert(pObject != NULL);

    if (pObject == NULL) return;

    if (pObject->isSetFontFamily())
      {
        attributes->mFontFamily = pObject->getFontFamily();
      }

    if (pObject->isSetFontSize())
      {
        attributes->mFontSize = pObject->getFontSize();
      }

    if (pObject->isSetFontWeight())
      {
        attributes->mFontWeight = pObject->getFontWeight();
      }

    if (pObject->isSetFontStyle())
      {
        attributes->mFontStyle = pObject->getFontStyle();
      }

    if (pObject->isSetTextAnchor())
      {
        attributes->mTextAnchor = pObject->getTextAnchor();
      }

    if (pObject->isSetVTextAnchor())
      {
        attributes->mVTextAnchor = pObject->getVTextAnchor();
      }
  }

  /**
   * Extracts the attributes from the given transformation object.
   */
  static void extract_transformation_attributes(const CLTransformation* pObject, CLGroupAttributes* attributes);

  /**
   * Extracts the attributes from the given object with arrow head
   * information.
   * This template function can be used for group and curve elements.
   */
  template <typename T>
  static void extract_arrowhead_information(const T* pObject, CLGroupAttributes* attributes)
  {
    if (pObject->isSetStartHead())
      {
        attributes->mStartHead = pObject->getStartHead();
      }

    if (pObject->isSetEndHead())
      {
        attributes->mEndHead = pObject->getEndHead();
      }
  }

  /**
   * Method to draw an arbitrary object specified by it's bounding box
   * and the style with which it should be drawn.
   */
  void draw_group(const CLGroup* pGroup, const CLBoundingBox* pBB);

  /**
   * Method to draw a string at the given position within the given bounding box.
   */
  void draw_text(const CLTextTextureSpec* pTexture, double x, double y, double z, const CLBoundingBox* pBB);

  /**
   * This method calculates a texture for a given gradient definition and a
   * given size.
   * The data object has to be a vector that can store RGBA values for a rectangle
   * of the given size. The memory has to be allocated before calling the method.
   * The scale specifies by how much the original box has been scaled.
   */
  void create_gradient_texture(unsigned int size, GLubyte* pData, const CLGradientBase* pGradient, double z_value = 0.0);

  /**
   * This method calculates a texture for a given linear gradient definition
   * and a given size.
   * The data object has to be a vector that can store RGBA values for a rectangle
   * of the given size. The memory has to be allocated before calling the method.
   * The scale specifies by how much the original box has been scaled.
   */
  void create_linear_gradient_texture(unsigned int size, GLubyte* pData, const CLLinearGradient* pGradient, double z_value);

  /**
   * This method calculates a texture for a given radial gradient
   * definition and a given size.
   * The data object has to be a vector that can store RGBA values for a rectangle
   * of the given size. The memory has to be allocated before calling the method.
   * The scale specifies by how much the original box has been scaled.
   */
  void create_radial_gradient_texture(unsigned int size, GLubyte* pData, const CLRadialGradient* pGradient, double z_value);

  /**
   * Maps the relative distance to a color and set the color as an rgb value in
   * pData. pData has to be the pointer where 4 GLfloat values are going to be
   * stored.
   */
  void map_gradient_color(double rel_distance, const CLGradientBase* pGradient, GLubyte* pData);

  /**
   * Draw a set of datapoints with the current attributes using the given bounding box.
   */
  void draw_datapoints(GLdouble* pData, size_t numPoints, const CLBoundingBox* pBB, bool doTesselation = false, float xOffset = 0.0, float yOffset = 0.0, float zOffset = 0.0);

  /**
   * Maps the given arrow head to the given line segment.
   */
  void map_arrow_head(const CLPoint& p, const CLPoint& v, const std::string& headId);

  /**
   * This method is used as a callback for the GLU tesselator to report
   * errors during the tesselation process.
   */
  static void TESS_ERROR(GLenum error);

  /**
   * This static method is used as a callback for the GLU tesselator.
   * It is needed for polygons that intersect which itself and the
   * tesselator has to create a new vertex at the intersection.
   */
#ifdef _WIN32
  static void __stdcall COMBINE_CALLBACK(GLdouble coords[3], GLdouble** /*vertex_data[4]*/, GLfloat* /*weight[4]*/, GLdouble** dataOut);
#else
  static void COMBINE_CALLBACK(GLdouble coords[3], GLdouble** /*vertex_data[4]*/, GLfloat* /*weight[4]*/, GLdouble** dataOut);
#endif // _WIN32
  /**
   * This method is used as a callback for the GLU tesselator.
   * It is called for every vertex that is processed by the tesselator.
   * We need it to calculate the gradient colors at each vertex.
   */
#ifdef _WIN32
  static void _stdcall VERTEX_CALLBACK_GRADIENT(GLvoid* vertex);
#else
  static void VERTEX_CALLBACK_GRADIENT(GLvoid* vertex);
#endif // _WIN32

  /**
   * This static method is used as a callback for the GLU tesselator.
   * It is needed for polygons that intersect which itself and the
   * tesselator has to create a new vertex at the intersection.
   */
#ifdef _WIN32
  static void __stdcall COMBINE_CALLBACK_GRADIENT(GLdouble coords[3], GLdouble* vertex_data[4], GLfloat weight[4], GLdouble** dataOut);
#else
  static void COMBINE_CALLBACK_GRADIENT(GLdouble coords[3], GLdouble* vertex_data[4], GLfloat weight[4], GLdouble** dataOut);
#endif //_WIN32

  /**
   * Calculates the points for a cubic bezier curve.
   * The algorithm calculates numPoints and stores them in pData. pData
   * has to be an array with enough space for numPoints*3 GLfloat items.
   */
  static void calculate_cubicbezier(double sx, double sy, double sz, double p1x, double p1y, double p1z, double p2x, double p2y, double p2z, double ex, double ey, double ez, unsigned int numPoints, GLdouble* pData);

  /**
   * Method to draw a line made up of a set of points.
   */
  void draw_line(size_t numPoints, GLdouble* pData);

  static void createGLMatrix(const double* const matrix, GLdouble* glMatrix);

  /**
   * Creates a 1D texture for the line stippling.
   * The caller is responsible for deleting the returned object.
   * If the dasharray does not contain a valid stipple pattern NULL is
   * returned.
   */
  static CLLineStippleTexture* createLineStippleTexture(const std::vector<unsigned int>& dasharray);

  /**
   * This method takes a number of datapoints for a curve and segments
   * the curve into pieces that have a datapoint at every multiple of length.
   * This is needed if we need to apply line stippling for OpenGL < 2.0
   * where texture sizes have to be a power of 2.
   */
  void segment_data(double length, double ratio, size_t numPoints, GLdouble* pData, std::vector<simple_point>& v);

  /**
   * This method goes through all layout objects and checks them if they
   * are within the current viewport. If they are, they are added to the list of objects that are drawn.
   * An object is within the viewport if it's bounding box or parts of it
   * are within the viewport.
   * For curves, each start, end and base point is checked and if any
   * of those is within the viewport, the curve is added to the list.
   * The viewport is specified by its lower left (lx,ly) and upper right
   * point (rx,ry).
   */
  void update_drawables(double lx, double ly, double rx, double ry);

  /**
   * This method goes through all styles that are used by the current drawables
   * and figures out which gradients, colors and line stipples are used and
   * creates them.
   */
  void update_textures_and_colors();

  /**
   * Goes through all render objects in the given group and updates the color
   * map and gradients.
   * The maxDimension parameter is the maximum of the width and the height of the
   * corresponding layout object. This value is needed to determine the size of gradient textures.
   */
  void update_textures_and_colors(const CLGroup* pGroup, double maxDimension, double height, const std::string& parentFill = "", CLFontSpec parentFontSpec = CLFontSpec());

  /**
   * This method creates a FontSpec object from the font attributes in the given
   * group.
   * The height that is passed to the method is the height for the bounding box
   * and it used to calculate the font size if it has a relative component.
   */
  static CLFontSpec getFontSpec(const CLGroup* pGroup, double boxHeight, const CLFontSpec& parentFontSpec = CLFontSpec());

  /**
   * This method creates a FontSpec object from the font attributes in the given
   * text element.
   * The height that is passed to the method is the height for the bounding box
   * and it used to calculate the font size if it has a relative component.
   */
  static CLFontSpec getFontSpec(const CLText* pText, double boxHeight, const CLFontSpec& parentFontSpec = CLFontSpec());

  /**
   * This method goes throught the list of all drawables and tries to resolve the
   * style for each object.
   */
  void update_style_information();

  /**
   * This methods extracts all colors from the given gradient and adds them to the
   * color map.
   */
  void update_colors(const CLGradientBase* pGradient);

  /**
   * Stores the current attributes on a stack.
   */
  void save_current_attributes();

  /**
   * Restores the current attributes from the stack.
   * Any transformation object that might have been created after the
   * last call to save_current_attributes will be deleted.
   */
  void restore_current_attributes();

  /**
   * Routine to draw the caps between two line segments.
   * The method takes the three points that make the two line segments
   * and the width of the line.
   */
  void draw_cap(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double stroke_width);

  /**
   * Removes all entries from all cache maps and frees the memory for the textures.
   */
  void clear_cached_data();

  /**
   * calculates the intersection point of two lines.
   * The caller has to delete the returned point object.
   */
  static CLPoint* calculate_intersection(double p1x, double p1y, double p1z, double sx, double sy, double sz,
                                         double p2x, double p2y, double p2z, double tx, double ty, double tz);

  /**
   * Calculates the intersection point between two lines in 2D.
   * The intersection point is returned.
   * If the lines are parallel, a point with two NaN values is returned.
   * All numbers <= ALMOST_ZERO are considered to be 0.
   */
  static std::pair<double, double> calculate_intersection_point_2d(double p1x, double p1y, double sx, double sy, double p2x, double p2y, double tx, double ty);

  /**
   * Calculates wether 2d segments intersect within the length of the segments.
   * Calls calculate_intersection_point_2d.
   */
  static bool segments_intersect_2d(double p1x1, double p1y1, double p1x2, double p1y2, double p2x1, double p2y1, double p2x2, double p2y2);

  /**
   * Calculates if the point given as x,y is close enough to the given line segment
   * to count as a hit.
   */
  static bool isSegmentHit(const CLLineSegment* pLS, double x, double y, double toleranceRadius);

  /**
   * Calculates the distance between a point and a line segment.
   * It tries to calculate the intersection point of the line
   * and another line perpendicular to the first line through the given point.
   * If this intersection point is on the line segment, the result is the same
   * as the distance between the two lines, otherwise the distance is the distance of the given
   * point to the closest endpoint of the segment.
   */
  static double distancePointLineSegment(double x, double y, double lx1, double ly1, double lx2, double ly2);

  /**
   * Draw the selection frame around an graphical objects bounding object box.
   * If drawHandles is true, resize handles are drawn as well,
   * else only the box is drawn.
   * If the curve is given, the basepoints of the curve are also drawn
   * as small circles.
   */
  static void drawSelectionBox(double x, double y, double width, double height, bool drawHandles = false);

  /**
   * Updates the associations of species reference glyphs
   * and text glyphs.
   */
  void update_associations();

  /**
   * draws the selection box if there is one
   */
  void draw_selection_box() const;

  /**
   * The glFogCoordf function is part of OpenGL 1.4 and may not be available on
   * all implementations, so we need to query for this dynamically.
   */
  void initialize_gl_extension_functions();

#ifdef __APPLE__
  void * MyNSGLGetProcAddress(const char *name);
#endif // __APPLE__
};

#endif // CLLAYOUTRENDERER_H__
