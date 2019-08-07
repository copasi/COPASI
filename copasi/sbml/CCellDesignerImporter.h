// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CCellDesignerImporter_H__
#define CCellDesignerImporter_H__

#include <vector>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <limits>

#include "copasi/copasi.h"

#include <sbml/packages/layout/sbml/BoundingBox.h>
#include <sbml/packages/layout/sbml/Curve.h>
#include <sbml/packages/layout/sbml/Dimensions.h>
#include <sbml/packages/layout/sbml/LineSegment.h>
#include <sbml/packages/layout/sbml/Point.h>
#include <sbml/packages/render/sbml/Text.h>

#include "copasi/utilities/CCopasiNode.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class ColorDefinition;
class GraphicalObject;
class RenderGroup;
class Layout;
class LocalRenderInformation;
class Model;
class LocalStyle;
class Reaction;
class ReactionGlyph;
class SBase;
class SBMLDocument;
class SpeciesReferenceGlyphs;
class XMLNode;
LIBSBML_CPP_NAMESPACE_END

enum SPECIES_CLASS
{
  UNDEFINED_CLASS
  , PROTEIN_CLASS
  , GENE_CLASS
  , RNA_CLASS
  , ANTISENSE_RNA_CLASS
  , PHENOTYPE_CLASS
  , ION_CLASS
  , SIMPLE_MOLECULE_CLASS
  , DRUG_CLASS
  , UNKNOWN_CLASS
  , COMPLEX_CLASS
  , SQUARE_CLASS
  , OVAL_CLASS
  , SQUARE_NW_CLASS
  , SQUARE_NE_CLASS
  , SQUARE_SW_CLASS
  , SQUARE_SE_CLASS
  , SQUARE_N_CLASS
  , SQUARE_E_CLASS
  , SQUARE_W_CLASS
  , SQUARE_S_CLASS
  , DEGRADED_CLASS
  // the next three enums are actually not
  // species classes but attributes on
  // protein elements, but we will store them
  // as a class enum
  , TRUNCATED_CLASS
  , RECEPTOR_CLASS
  , CHANNEL_CLASS
};

enum SPECIES_MODIFICATION_TYPE
{
  UNDEFINED_MOD_TYPE
  , PHOSPHORYLATED_MOD_TYPE
  , ACETYLATED_MOD_TYPE
  , UBIQUITINATED_MOD_TYPE
  , METHYLATED_MOD_TYPE
  , HYDROXYLATED_MOD_TYPE
  , DONTCARE_MOD_TYPE
  , UNKNOWN_MOD_TYPE
  , GLYCOSYLATED_MOD_TYPE
  , MYRISTOYLATED_MOD_TYPE
  , PALMYTOYLATED_MOD_TYPE
  , PRENYLATED_MOD_TYPE
  , PROTONATED_MOD_TYPE
  , SUFLATED_MOD_TYPE
  , EMPTY_MOD_TYPE
};

enum POSITION_TO_COMPARTMENT
{
  UNDEFINED_POSITION
  , OUTER_SURFACE
  , TRANSMEMBRANE
  , INNER_SURFACE
  , INSIDE
  , INSIDE_MEMBRANE
};

enum REACTION_TYPE
{
  UNDEFINED_RTYPE
  , STATE_TRANSITION_RTYPE
  , KNOWN_TRANSITION_OMITTED_RTYPE
  , UNKNOWN_TRANSITION_RTYPE
  , CATALYSIS_RTYPE
  , UNKNOWN_CATALYSIS_RTYPE
  , INHIBITION_RTYPE
  , UNKNOWN_INHIBITION_RTYPE
  , TRANSPORT_RTYPE
  , HETERODIMER_ASSOCIATION_RTYPE
  , DISSOCIATION_RTYPE
  , TRUNCATION_RTYPE
  , TRANSCRIPTIONAL_ACTIVATION_RTYPE
  , TRANSCRIPTIONAL_INHIBITION_RTYPE
  , TRANSLATIONAL_ACTIVATION_RTYPE
  , TRANSLATIONAL_INHIBITION_RTYPE
  , TRANSCRIPTION_RTYPE
  , TRANSLATION_RTYPE
};

enum MODIFICATION_TYPE
{
  UNDEFINED_MTYPE
  , CATALYSIS_MTYPE
  , UNKNOWN_CATALYSIS_MTYPE
  , INHIBITION_MTYPE
  , UNKNOWN_INHIBITION_MTYPE
  , TRANSPORT_MTYPE
  , HETERODIMER_ASSOCIATION_MTYPE
  , TRANSCRIPTIONAL_ACTIVATION_MTYPE
  , TRANSCRIPTIONAL_INHIBITION_MTYPE
  , TRANSLATIONAL_ACTIVATION_MTYPE
  , TRANSLATIONAL_INHIBITION_MTYPE
  , PHYSICAL_STIMULATION_MTYPE
  , MODULATION_MTYPE
};

enum MODIFICATION_LINK_TYPE
{
  UNDEFINED_ML_TYPE
  , CATALYSIS_ML_TYPE
  , UNKNOWN_CATALYSIS_ML_TYPE
  , INHIBITION_ML_TYPE
  , UNKNOWN_INHIBITION_ML_TYPE
  , TRANSPORT_ML_TYPE
  , HETERODIMER_ASSOCIATION_ML_TYPE
  , TRANSCRIPTIONAL_ACTIVATION_ML_TYPE
  , TRANSCRIPTIONAL_INHIBITION_ML_TYPE
  , TRANSLATIONAL_ACTIVATION_ML_TYPE
  , TRANSLATIONAL_INHIBITION_ML_TYPE
  , PHYSICAL_STIMULATION_ML_TYPE
  , MODULATION_ML_TYPE
  , TRIGGER_ML_TYPE
  , BOOLEAN_LOGIC_GATE_AND_ML_TYPE
  , BOOLEAN_LOGIC_GATE_OR_ML_TYPE
  , BOOLEAN_LOGIC_GATE_NOT_ML_TYPE
  , BOOLEAN_LOGIC_GATE_UNKNOWN_ML_TYPE
};

/**
 * The positions are ordered so that the
 * mid points of the edges come before corners
 * and those come before the rest.
 * This way the connection finding algorithm
 * will favor connections to side midpoints
 * before connections to other anchor points.
 */
enum POSITION
{
  POSITION_UNDEFINED
  , POSITION_N
  , POSITION_E
  , POSITION_S
  , POSITION_W
  , POSITION_NE
  , POSITION_NW
  , POSITION_SE
  , POSITION_SW
  , POSITION_NNE
  , POSITION_ENE
  , POSITION_ESE
  , POSITION_SSE
  , POSITION_SSW
  , POSITION_WSW
  , POSITION_WNW
  , POSITION_NNW
};

enum CONNECTION_POLICY
{
  POLICY_UNDEFINED
  , POLICY_DIRECT
  , POLICY_SQUARE
};

enum DIRECTION_VALUE
{
  DIRECTION_UNDEFINED
  , DIRECTION_UNKNOWN
  , DIRECTION_HORIZONTAL
  , DIRECTION_VERTICAL
};

enum PAINT_SCHEME
{
  PAINT_UNDEFINED
  , PAINT_COLOR
  , PAINT_GRADIENT
};

struct LinkTarget
{
  std::string mAlias;
  std::string mSpecies;
  POSITION mPosition;

  // Default constructor
  LinkTarget();
};

struct SpeciesModification
{
  std::string mResidue;
  SPECIES_MODIFICATION_TYPE mType;

  // default constructor
  SpeciesModification();
};

// structure for the species state
struct SpeciesState
{
  std::vector<SpeciesModification> mModifications;

  // default constructor
  SpeciesState();
};

struct SpeciesIdentity
{
  SPECIES_CLASS mSpeciesClass;
  std::string mNameOrReference;
  SpeciesState mState;
  bool mHypothetical;

  // Default constructor
  SpeciesIdentity();
};

// structure for the modifications in a species state
struct SpeciesAnnotation
{
  enum POSITION_TO_COMPARTMENT mPosition;
  std::string mParentComplex;
  SpeciesIdentity mIdentity;

  // Default constructor
  SpeciesAnnotation();
};

struct CompartmentAnnotation
{
  std::string mName;

  // Default constructor
  CompartmentAnnotation();
};

struct Line
{
  std::string mColor;
  double mWidth;
  bool mCurve;

  // Default constructor
  Line();
};

struct LineDirection
{
  int mIndex;
  int mArm;
  DIRECTION_VALUE mValue;

  // default constructor
  LineDirection();
};

struct ConnectScheme
{
  CONNECTION_POLICY mPolicy;
  int mRectangleIndex;
  std::vector<LineDirection> mLineDirections;

  // default constructor
  ConnectScheme();
};

struct EditPoints
{
  int mNum0;
  int mNum1;
  int mNum2;
  int mOmittedShapeIndex;
  int mTShapeIndex;
  std::vector<Point> mPoints;

  // default constructor
  EditPoints();
};

struct ReactionModification
{
  // attributes to the modification element
  std::vector<std::string> mAliases;
  std::vector<std::string> mModifiers;
  MODIFICATION_LINK_TYPE mType;
  int mTargetLineIndex;
  // to calculate the absolute values
  // of modification edit points,
  // we need to calculate the vector from the
  // anchor on the modifier to the anchor on the reaction
  // The second vector is the vector with the same length that
  // is orthogonal to the initial vector
  // These two vectors seem to be used for the calculation
  // of edit points
  // Most modifications are unbranched, at least the ones we import
  // so the edit points are listed from the modifier to the reaction symbol
  EditPoints mEditPoints;
  int mNum0;
  int mNum1;
  int mNum2;
  MODIFICATION_TYPE mModType;
  Point mOffset;

  // additional children to the modification element
  ConnectScheme mConnectScheme;
  std::vector<LinkTarget> mLinkTargets;
  Line mLine;

  // Default constructor
  ReactionModification();
};

struct ReactantLink
{
  // attributes
  std::string mAlias;
  std::string mReactant;
  int mTargetLineIndex;

  // children
  POSITION mPosition;
  Line mLine;

  // default constructor
  ReactantLink();
};

struct ReactionAnnotation
{
  std::string mName;
  REACTION_TYPE mType;
  std::vector<LinkTarget> mBaseReactants;
  std::vector<LinkTarget> mBaseProducts;
  std::vector<ReactantLink> mReactantLinks;
  std::vector<ReactantLink> mProductLinks;
  ConnectScheme mConnectScheme;
  Point mOffset;

  // to calculate the absolute values
  // of modification edit points we need to know
  // if the reaction is branched or not.
  // If it is an unbranched reaction with one base substrate
  // and one base product
  // we need to calculate the vector from the
  // center of the base substrate to the center of the base product
  // The second vector is the vector with the same length that
  // is orthogonal to the initial vector
  // These two vectors seem to be used for the calculation
  // of edit points

  // for branched reactions we need the two vectors that run from the center
  // of the first base substrate to the other two reactants centers
  // These two vectors create a new coordinate system.
  // The base points are listed from the reaction symbol to the reactant symbols
  // if the reaction is branched
  EditPoints mEditPoints;
  Line mLine;
  std::vector<ReactionModification> mModifications;

  // Default constructor
  ReactionAnnotation();
};

// some structures for the general model annotation
//
struct CellDesignerSpecies
{
  std::string mId;
  std::string mName;
  std::string mCompartment;

  // we can use the same annotation as for the SBML species
  SpeciesAnnotation mAnnotation;

  // default constructor
  CellDesignerSpecies();
};

struct Paint
{
  // aRGB value
  std::string mColor;
  // optional scheme
  // default seems to be Color
  PAINT_SCHEME mScheme;

  // default constructor
  Paint();
};

struct DoubleLine
{
  double mInnerWidth;
  double mOuterWidth;
  double mThickness;

  // default constructor
  DoubleLine();
};

struct CompartmentAlias
{
  std::string mId;
  std::string mCompartment;

  SPECIES_CLASS mClass;
  Point mNamePoint;
  DoubleLine mDoubleLine;
  Paint mPaint;
  // a compartment alis either has a point or bounds
  BoundingBox mBounds;
  double mFontSize;

  // default constructor
  CompartmentAlias();
};

struct UsualView
{
  Point mInnerPosition;
  Dimensions mBoxSize;
  double mLineWidth;
  Paint mPaint;

  // default constructor
  UsualView();
};

// ComplexSpeciesAlias seems to have the
// same attributes and elements
// so we can use one structure for both
struct SpeciesAlias
{
  std::string mId;
  std::string mSpecies;
  std::string mComplexSpeciesAlias;
  std::string mCompartmentAlias;
  double mFontSize;
  // store whether we are dealing with a complex
  bool mComplex;

  BoundingBox mBounds;
  UsualView mUView;

  // default constructor
  SpeciesAlias();
};

struct ProteinModification
{
  std::string mId;
  std::string mName;
  double mAngle;

  // default constructor
  ProteinModification();
};

// data type to store protein data
// from the listOfProteins
struct Protein
{
  std::string mId;
  std::string mName;
  SPECIES_CLASS mType;
  std::vector<ProteinModification> mModifications;

  // default constructor
  Protein();
};

/**
 * This class converts CellDesigner layout information
 * into SBML layout.
 * Maybe later versions will also be able to handle the
 * render information part.
 */
class CCellDesignerImporter
{
protected:

  // to work the class needs
  // an SBMLDocument
  SBMLDocument* mpDocument;

  // the documents sbml model
  Model* mpModel;

  // the result is stored in an instance of the
  // SBML Layout class
  Layout* mpLayout;

  // we also create local render information
  LocalRenderInformation* mpLocalRenderInfo;

  // we need to store all ids so that we can create unique ids
  // for new elements
  std::map<std::string, const SBase*> mIdMap;

  // we need a map that associates the ids of CellDesigner aliases
  // to the corresponding layout elements
  // In case of complex species aliases, the id is assigned to
  // the layout element that was created for the top most parent
  std::map<std::string, GraphicalObject*> mCDIdToLayoutElement;

  // we need a map that associates the ids of CellDesigner aliases
  // to their BoundingBoxes
  std::map<std::string, BoundingBox> mCDBounds;

  // we need to store the associations between model element ids and layout elements
  // Since there can be multiple representations in the layout per model element
  // we have to use a multimap
  std::multimap<std::string, GraphicalObject*> mModelIdToLayoutElement;

  // a map to store the location of compartment names
  std::map<const CompartmentGlyph*, Point> mCompartmentNamePointMap;

  // we need a data structure that can store the dependencies of complex species aliases
  std::list<CCopasiNode<std::string>*> mComplexDependencies;

  // a map that stores protein types for protein ids
  std::map<std::string, Protein> mProteinInformationMap;

  // a map that stores antisense RNA names for antisense RNA ids
  // These are used as TextGlyphs on antisense RNA nodes
  //std::map<std::string,std::string> mASRNANameMap;

  // a map that stores RNA names for RNA ids
  // These are used as TextGlyphs on RNA nodes
  //std::map<std::string,std::string> mRNANameMap;

  // a map that stores gene names for gene ids
  // These are used as TextGlyphs on gene nodes
  //std::map<std::string,std::string> mGeneNameMap;

  // a map that maps color strings to the corresponding id of the ColorDefinition
  std::map<std::string, std::string> mColorStringMap;

  // a map that stores the CompartmentAlias information for a certain CompartmentGlyph
  // We need this to create styles for the text glyphs
  std::map<const CompartmentGlyph*, CompartmentAlias> mCompartmentAliasMap;

  // a map that stores the SpeciesAlias information for a certain SpeciesGlyph
  // We need this to create styles for the text glyphs
  std::map<const SpeciesGlyph*, SpeciesAlias> mSpeciesAliasMap;

  /**
   * a map that associates the parsed alias data with the id
   * of the species alias or complex species alias
   */
  std::map<std::string, SpeciesAlias> mSpeciesAliases;

  /**
   * a map that stores the species annotation with each species.
   */
  std::map<std::string, SpeciesAnnotation> mSpeciesAnnotationMap;

  /**
   * a map that stores the compartment annotation with each compartment.
   */
  std::map<std::string, CompartmentAnnotation> mCompartmentAnnotationMap;

  /**
   * a map that stores the name of a CellDesigner species with its id.
   */
  std::map<std::string, std::pair<std::string, SpeciesIdentity> > mIncludedSpeciesNameMap;

  /**
   * a map that associated a modifier type with  the corresponding style.
   */
  std::map<MODIFICATION_LINK_TYPE, LocalStyle*> mModificationLinkStyleMap;

  /**
   * the font to be used for text glyphs
   */
  std::string mFont;

public:
  /**
   * Constructor that takes a pointer to an
   * SBMLDocument.
   * The SBMLDocument will not be copied and it will not be
   * owned by the importer.
   * If the pointer is not NULL, the class will try
   * to directly convert the CellDesigner layout if there is one.
   */
  CCellDesignerImporter(SBMLDocument* pDocument = 0);

  /**
   * Method to set the SBMLDocument.
   * If the pointer is not NULL, the class will try
   * to directly convert the CellDesigner layout if there is one.
   */
  void setSBMLDocument(SBMLDocument* pDocument);

  /**
   * Method to return a const pointer to the SBMLDocument.
   */
  const SBMLDocument* getSBMLDocument() const;

  /**
   * Method to return the layout object.
   * Since the layout object is owned by the importer,
   * the caller should make a copy of the layout.
   */
  const Layout* getLayout() const;

  /**
   * Goes through the SBMLDocument and tries to find a CellDesigner
   * annotation.
   * If one is found, a const pointer to the corresponding XMLNode
   * is returned.
   * If the current SBMLDocument is NULL or if no CellDesigner annotation
   * is found, NULL is returned.
   */
  static const XMLNode* findCellDesignerAnnotation(SBMLDocument* pDocument, const XMLNode* pAnnotation);

  /**
   * This method searches for the CellDesigner namespace in the annotation to the model
   * as well as the annotation to the document.
   * The method returns a pair of bool and string. The bool determines if the namespace was
   * found and the string specifies the prefix for the namespace.
   */
  static std::pair<bool, std::string> findCellDesignerNamespace(const SBMLDocument* pDocument);

  /**
   * Tries to find the version number of CellDesigner that was used to write
   * this annotation.
   * The node should be the CellDesigner annotation of the model.
   * If the version number is not found or could not be parsed, we
   * return -1.
   */
  static double determineVersion(const XMLNode* pNode);

  /**
   * removes the current layout
   */
  void removeCurrentLayout();

  /**
   * @brief creates a curve connecting one substrate to one product
   * @param ranno the reaction annotation
   * @param pRGlyph the reaction glyph
   * @param pReactionStyle the style of the current reaction
   * @return status whether creation worked or not
   */
  bool createUniUniCurve(ReactionAnnotation& ranno,
                         ReactionGlyph* pRGlyph,
                         LocalStyle* pReactionStyle);

  /**
   * @brief creates a curve connecting one substrate to two products
   * @param ranno the reaction annotation
   * @param pRGlyph the reaction glyph
   * @param pReactionStyle the style of the current reaction
   * @return status whether creation worked or not
   */
  bool createUniBiCurve(ReactionAnnotation& ranno,
                        ReactionGlyph* pRGlyph,
                        LocalStyle* pReactionStyle);

  /**
   * @brief creates a curve connecting two substrates to one product
   * @param ranno the reaction annotation
   * @param pRGlyph the reaction glyph
   * @param pReactionStyle the style of the current reaction
   * @return status whether creation worked or not
   */
  bool createBiUniCurve(ReactionAnnotation& ranno,
                        ReactionGlyph* pRGlyph,
                        LocalStyle* pReactionStyle);

  bool createSubstrate(std::vector<Point>& reactantPoints,
                       ReactionGlyph* pRGlyph,
                       LocalStyle* pReactionStyle,
                       ReactionAnnotation& ranno
                      );

  bool createProduct(std::vector<Point>& productPoints,
                     ReactionGlyph* pRGlyph,
                     LocalStyle* pReactionStyle,
                     ReactionAnnotation& ranno
                    );

  void setProductStyle(const std::string& id, LocalStyle* pReactionStyle);

  void enforceSquare(const ConnectScheme& connectScheme,
                     Point &p,
                     const Point &pStart,
                     const Point &pEnd,
                     int &directionCount,
                     bool isLast,
                     const std::vector<Point> &points);
protected:
  /**
   * This method tries to convert the CellDesigner annotation to an SBML Layout.
   * On success the method will return true and false otherwise.
   */
  bool convertCellDesignerLayout(const XMLNode* pCellDesignerAnnotation);

  /**
   * Creates the compartment glyphs from the given node
   * that represents the listOfCompartmentAliases.
   */
  bool createCompartmentGlyphs(const XMLNode* pLoCA);

  /**
   * Creates the species glyphs from the given node
   * that represents the listOfSpeciesAliases.
   */
  bool createSpeciesGlyphs(const XMLNode* pLoSA);

  /**
   * Creates the compartment glyph from the given
   * compartmentAliase structure.
   */
  bool createCompartmentGlyph(const CompartmentAlias& ca);

  /**
   * Creates the species glyph from the given
   * SpeciesAliases structure.
   */
  bool createSpeciesGlyph(const SpeciesAlias& sa);

  /**
   * Creates a unique id with the given prefix.
   */
  std::string createUniqueId(const std::string& prefix);

  /**
   * Traverses the reactions of the model and looks for CellDesigner annotations.
   * These are used to create reaction glyphs.
   */
  bool convertReactionAnnotations();

  /**
   * Traverses the compartments of the model and looks for CellDesigner annotations.
   * These are used to create text glyphs associated with compartments.
   */
  bool convertCompartmentAnnotations();

  /**
   * Traverses the species of the model and looks for CellDesigner annotations.
   * These are used to create text glyphs associated with species.
   */
  bool convertSpeciesAnnotations();

  /**
   * Looks for CellDesigner annotation in the given reaction and tries to convert
   * the information in that annotation into a ReactionGlyph.
   */
  bool convertReactionAnnotation(Reaction* pReaction, const Model* pModel);

  LocalStyle* createStyleFromLine(Line &line, const std::string &glyphId);

  /**
   * Takes a node that contains a number of baseReactants or baseProducts
   * and creates species reference glyphs for each one.
   */
  bool createSpeciesReferenceGlyphs(ReactionGlyph* pRGlyph,
                                    const std::vector<LinkTarget>& link,
                                    std::map<SpeciesReferenceGlyph*, Point>& startsMap,
                                    bool reactants);

  /**
   * Takes a bounding box and a position string and returns the position on the bounding box that corresponds
   * to the given position.
   */
  static Point getPositionPoint(const BoundingBox& box, POSITION position);

  /**
   * Adds a new entry to the dependency tree for complex species aliases.
   */
  void addDependency(const std::string& parent, const std::string& child);

  /**
   * Goes through the children of the given node which represents a list of
   * protein definitions and check the types.
   * If the type is RECEPTOR, ION_CHANNEL or TRUNCATED, store that information.
   */
  bool parseProteins(const XMLNode* pNode);

  /**
   * Goes through the children of the given node which represents a list of protein definitions
   * and collects the names for them.
   * These names are converted to text glyphs for the proteins.
   */
  //bool parseGeneNames(const XMLNode* pNode);

  /**
   * Goes through the children of the given node which represents a list of protein definitions
   * and collects the names for them.
   * These names are converted to text glyphs for the proteins.
   */
  //bool parseRNANames(const XMLNode* pNode);

  /**
   * Goes through the children of the given node which represents a list of protein definitions
   * and collects the names for them.
   * These names are converted to text glyphs for the proteins.
   */
  //bool parseASRNANames(const XMLNode* pNode);

  /**
   * Searches for a child with a certain name and a certain prefix
   * in the tree based on pNode.
   * The first child that fits the name and the prefix or NULL is returned.
   * If recursive is true, the tree is searched recursively.
   */
  static const XMLNode* findChildNode(const XMLNode* pNode,
                                      const std::string& prefix,
                                      const std::string& name,
                                      bool recursive = false);

  /**
   * Parses the node which represents a speciesIdentity node and fills the given SpeciesIdentity
   * structure with the data.
   * If the parsing fails, false is returned.
   */
  static bool parseSpeciesIdentity(const XMLNode* pNode,
                                   SpeciesIdentity& identity);

  /**
   * Parses the node which represents the state in a speciesIdentity node and fills the given SpeciesState
   * structure with the data.
   * If the parsing fails, false is returned.
   */
  static bool parseSpeciesState(const XMLNode* pNode,
                                SpeciesState& state);

  /**
   * Parses the node which represents a modification ion a species node and fills the given SpeciesModification
   * structure with the data.
   * If the parsing fails, false is returned.
   */
  static bool parseSpeciesModification(const XMLNode* pNode,
                                       SpeciesModification& mod);

  /**
   * Tries to parse the species annotation in the given node and stores the data in the given
   * SpeciesAnnotation structure.
   * If parsing fails, false is returned.
   */
  static bool parseSpeciesAnnotation(const XMLNode* pNode,
                                     SpeciesAnnotation& anno);

  /**
   * Tries to parse the compartment annotation in the given node and stores the data in the given
   * CompartmentAnnotation structure.
   * If parsing fails, false is returned.
   */
  static bool parseCompartmentAnnotation(const XMLNode* pNode,
                                         CompartmentAnnotation& anno);

  /**
   * Tries to parse the reaction annotation in the given node and stores the data in the given
   * ReactionAnnotation structure.
   * If parsing fails, false is returned.
   */
  static bool parseReactionAnnotation(const XMLNode* pNode,
                                      ReactionAnnotation& ranno);

  /**
   * Parses the given node and stored the information in the width and height attribute
   * in the given dimensions object.
   * If parsinf fails, false is returned.
   */
  static bool parseBoxSize(const XMLNode* pNode, Dimensions& d);

  /**
   * Parses the data in the given node which represents a UsualView object and stores
   * the parsed data in the given UsualView structure.
   * If parsinf fails, false is returned.
   */
  static bool parseUsualView(const XMLNode* pNode, UsualView& view);

  /**
   * Parse the data in the given node assuming that this is a node that represents a point
   * and therefore contains an "x" and a "y" attribute.
   * The data is stored in the given point object.
   * If parsing fails, false is returned.
   */
  static bool parseBounds(const XMLNode* pNode, BoundingBox& box);

  /**
   * Parse the data in the given node assuming that this is a node that represents a point
   * and therefore contains an "x" and a "y" attribute.
   * The data is stored in the given point object.
   * If parsing fails, false is returned.
   */
  static bool parsePoint(const XMLNode* pNode, Point& p);

  /**
   * Parses the data in the given node which represents a species
   * (or ComplexSpecies) alias
   * and stores it in the given SpeciesAlias structure.
   * If parsing fails, false is returned.
   */
  static bool parseSpeciesAlias(const XMLNode* pNode, SpeciesAlias& sa);

  /**
   * Parses the data in the given node which represents a compartment alias
   * and stores it in the given CompartmentAlias structure.
   * If parsing fails, false is returned.
   */
  static bool parseCompartmentAlias(const XMLNode* pNode,
                                    CompartmentAlias& ca,
                                    const Dimensions& layout_dimensions);

  /**
   * Parses the given XMLNode which represents a double line element.
   * The parsed data is stored in the given DoubleLine structure.
   * If parsing fails, false is returned.
   */
  static bool parseDoubleLine(const XMLNode* pNode, DoubleLine& dl);

  /**
   * Parses the modelDisplay data in the given XMLNode and stores the result in the
   * given Dimensions structure.
   * If parsing fails, false is returned.
   */
  static bool parseModelDisplay(const XMLNode* pNode, Dimensions& d);

  /**
   * Parses the paint data in the given XMLNode and stores the result in the
   * given Paint structure.
   * If parsing fails, false is returned.
   */
  static bool parsePaint(const XMLNode* pNode, Paint& p);

  /**
   * Tries to parse the reaction elements (baseReactants or baseProducts) in the given
   * node and stores the data in the given ReactionAnnotation structure.
   * If parsing fails, false is returned.
   */
  static bool parseReactionElements(const XMLNode* pNode, std::vector<LinkTarget>& elements);

  /**
   * Tries to parse the connection scheme in the given node and stores the data in the given
   * ConnectionScheme structure.
   * If parsing fails, false is returned.
   */
  static bool parseConnectScheme(const XMLNode* pNode, ConnectScheme& scheme);

  /**
   * Tries to parse the line data in the given node and stores the data in the given
   * Line structure.
   * If parsing fails, false is returned.
   */
  static bool parseLine(const XMLNode* pNode, Line& line);

  /**
   * Tries to parse the extra reactant links in the given node and stores the data in the given
   * vector of ReactantLinks structure.
   * If parsing fails, false is returned.
   */
  static bool parseExtraLinks(const XMLNode* pNode, std::vector<ReactantLink>& rlinks);

  /**
   * Tries to parse the edit points in the given node and stores the data in the given
   * vector of Points.
   * If parsing fails, false is returned.
   */
  static bool parseEditPoints(const XMLNode* pNode, EditPoints& editpoints);

  /**
   * Tries to parse the reaction modifications in the given node and stores the data in the given
   * vector of ReactionModifications.
   * If parsing fails, false is returned.
   */
  static bool parseReactionModifications(const XMLNode* pNode,
                                         std::vector<ReactionModification>& rmods);

  /**
   * Tries to parse the link target in the given node and stores the data in the given
   * vector of LinkTarget structure.
   * If parsing fails, false is returned.
   */
  static bool parseLinkTarget(const XMLNode* pNode, LinkTarget& l);

  /**
   * Tries to parse the line direction in the given node and stores the data in the given
   * vector of LineDirection structure.
   * If parsing fails, false is returned.
   */
  static bool parseLineDirection(const XMLNode* pNode, LineDirection& d);

  /**
   * Tries to parse the reactant link in the given node and stores the data in the given
   * vector of ReactionLink structure.
   * If parsing fails, false is returned.
   */
  static bool parseExtraLink(const XMLNode* pNode, ReactantLink& l);

  /**
   * Tries to parse the w2D points in the given string and stores the data in the given
   * vector of Points.
   * If parsing fails, false is returned.
   */
  static bool parsePointsString(const std::string& s, std::vector<Point>& points);

  /**
   * Tries to parse the reaction modification in the given node and stores the data in the given
   * ReactionModification structure.
   * If parsing fails, false is returned.
   */
  static bool parseReactionModification(const XMLNode* pNode, ReactionModification& mod);

  /**
   * Tries to parse the protein modification in the given node and stores the data in the given
   * ProteinModification structure.
   * If parsing fails, false is returned.
   */
  static bool parseProteinModification(const XMLNode* pNode, ProteinModification& mod);

  /**
   * Tries to parse the CellDesigner species in the listOfincludedSpecies.
   * If parsing fails, false is returned.
   */
  bool handleIncludedSpecies(const XMLNode* pNode);

  /**
   * Converts the given paint scheme string to the corresponding PAINT_SCHEME enum value.
   * If no enum is found, PAINT_UNDEFINED is returned.
   */
  static PAINT_SCHEME paintSchemeToEnum(std::string s);

  /*
   * Converts the given modification string to the corresponding MODIFICATION_TYPE enum value.
   * If no enum is found, UNDEFINED_MOD_TYPE is returned.
   */
  static SPECIES_MODIFICATION_TYPE speciesModificationTypeToEnum(std::string cl);

  /**
  * Converts the given class string to the corresponding SPECIES_CLASS enum value.
  * If no enum is found, UNDEFINED is returned.
  */
  static SPECIES_CLASS classToEnum(std::string cl);

  /**
   * Converts the given position string to an enum.
   */
  static POSITION positionToEnum(std::string pos);

  /**
   * Converts the given reaction type string to the corresponding enum.
   * If there is no enum that corresponds to the string, UNDEFINED_RTYPE is returned.
   */
  static REACTION_TYPE reactionTypeToEnum(std::string s);

  /**
   * Converts the given modification link type string to the corresponding enum.
   * If there is no enum that corresponds to the string, UNDEFINED_ML_TYPE is returned.
   */
  static MODIFICATION_LINK_TYPE modificationLinkTypeToEnum(std::string s);

  /**
   * Converts the given modification type string to the corresponding enum.
   * If there is no enum that corresponds to the string, UNDEFINED_MTYPE is returned.
   */
  static MODIFICATION_TYPE modificationTypeToEnum(std::string s);

  /**
   * Converts the given position to compartment string to the corresponding enum.
   * If there is no enum that corresponds to the string, UNDEFINED_POSITION is returned.
   */
  static POSITION_TO_COMPARTMENT positionToCompartmentToEnum(std::string s);

  /**
   * Converts the given connection policy string to the corresponding enum.
   * If there is no enum that corresponds to the string, POLICY_UNDEFINED is returned.
   */
  static CONNECTION_POLICY connectionPolicyToEnum(std::string s);

  /**
   * Converts the given direction string to the corresponding enum.
   * If there is no enum that corresponds to the string, DIRECTION_UNDEFINED is returned.
   */
  static DIRECTION_VALUE directionToEnum(std::string s);

  /**
   * Splits the given string at each character occurs in splitChars.
   * The parts generated are stored in the given vector.
   * The vector is cleared by the method.
   * If something goes wrong false is returned.
   */
  static bool splitString(const std::string& s,
                          std::vector<std::string>& parts,
                          const std::string& splitChars);

  /**
   * This method creates a new local style based on the passed in CompartmentAlias object.
   * The style is associated with the object via the given id.
   * If Creating the style fails, false is returned.
   */
  bool createCompartmentStyle(const CompartmentAlias& ca, const CompartmentGlyph* pCGlyph);

  /**
   * This method creates a new local style based on the passed in SpeciesAlias object.
   * The style is associated with the object via the given id.
   * If Creating the style fails, false is returned.
  bool createSpeciesStyle(const SpeciesAlias& sa,const std::string& objectReference);
   */

  /**
   * Creates a local style for a certain text glyph.
   * The style is associated with the text glyph via the id
   * of the text glyph.
   */
  bool createTextGlyphStyle(double size, Text::TEXT_ANCHOR hAlign,
                            Text::TEXT_ANCHOR vAlign,
                            const std::string& objectReference);

  /**
   * TODO right now, we use default styles for species reference glyphs
   * TODO and reaction glyphs.
   * TODO These are created here.
   * TODO later we have to create individual styles based on the type of reaction
   * TODO and the color set in the CellDesigner annotation.
   */
  bool createDefaultStyles();

  /**
   * Adds all possible POSITION enums to the given vector.
   * The vector is cleared first.
   */
  static void addAllPositions(std::vector<POSITION>& v);

  /**
   * Finds the shortest connection between two objects given the potential
   * connection positions for each object and the bounding boxes for each object.
   * The result is returned in the original vectors as position values.
   * If the method fails, e.g. because one of the vectors is empty or the bounding box contains
   * values we can't use for calculations (inf,NAN), false is returned.
   */
  static bool findShortestConnection(std::vector<POSITION>& pos1,
                                     std::vector<POSITION>& pos2,
                                     const BoundingBox& box1,
                                     const BoundingBox& box2);

  /**
   * Finds the shortest connection between the given point and the object which is
   * defined by its connection positions and its bounding box.
   * If the method fails, e.g. because one of the vectors is empty or the bounding box contains
   * values we can't use for calculations (inf,NAN), POSITION_UNDEFINED
   */
  static POSITION findShortestConnection(const Point& p,
                                         std::vector<POSITION>& pos,
                                         const BoundingBox& box);

  /**
   * Calculate the distance between the two points.
   */
  static double distance(const Point& p1, const Point& p2);

  /**
   * Checks if the given ReactantLink object has a valid linkAnchor
   * If not, we try to determine the best anchor be finding the one that is closest
   * to the given point.
   */
  void checkLinkAnchor(LinkTarget& link, const Point& p);

  /**
   * Checks if the given ReactantLink objects have valid linkAnchors
   * If not, we try to determine the best anchor be finding the ones that
   * give the shortest connection between the two objects
   */
  void checkLinkAnchors(LinkTarget& substrate, LinkTarget& product);

  /**
   * Calculates the absolute position for point p
   * based on the three other points (p1,p2,p3) given.
   * The formula for that is:
   * p1 + p.x * (p2 - p1) + p.y * (p3 - p1)
   */
  static Point calculateAbsoluteValue(const Point& p,
                                      const Point& p1,
                                      const Point& p2,
                                      const Point& p3);

  /**
   * Tries to set the species glyph id in the given species reference glyph.
   */
  bool setSpeciesGlyphId(SpeciesReferenceGlyph* pGlyph, const LinkTarget& link);

  /**
   * Tries to set the species reference id on the given SPeciesReferenceGlyph.
   */
  bool setSpeciesReferenceId(SpeciesReferenceGlyph* pGlyph,
                             const LinkTarget& link,
                             const std::string& reactionId);

  /**
   * Creates the structures for the extra product links.
   * If processing fails, false is returned;
   */
  bool handleExtraReactionElements(ReactionGlyph* pRGlyph,
                                   ReactionAnnotation& ranno,
                                   bool substrate);

  /**
   * Creates the structures for the modification links
   * in a reaction.
   * If processing fails, false is returned;
   */
  bool handleModificationLinks(ReactionGlyph* pRGlyph,
                               ReactionAnnotation& ranno);

  /**
   * Create default style for reaction glyphs.
   */
  bool createDefaultReactionGlyphStyle();

  /**
   * Create default style for modifiers.
   */
  bool createDefaultModifierStyle();

  /**
   * Create style for catalysis.
   */
  bool createCatalysisStyles();

  /**
   * Create default style for inhibitors.
   */
  bool createDefaultInhibitorStyle();

  /**
   * Create default style for activators.
   */
  bool createDefaultActivatorStyle();

  /**
   * Create default style for products.
   */
  bool createDefaultProductStyle();

  /**
   * Create default style for substrates.
   */
  bool createDefaultSubstrateStyle();

  /**
   * Create a primitive that corresponds to the given species specific class
   * The primitive is created in the given group object.
   * The complete primitive is translated by the given offset.
   *
   * If creation of the primitive fails, false is returned.
   */
  bool createPrimitive(RenderGroup* pGroup,
                       const SpeciesIdentity& si,
                       const BoundingBox& bounds,
                       const Point& offset,
                       double stroke_width,
                       const std::string& stroke_color,
                       const std::string& fill_color,
                       const std::string& text = ""
                      );

  /**
   * Takes a protein modification description and creates the corresponding primitive.
   */
  bool createProteinModification(RenderGroup* pGroup,
                                 SPECIES_MODIFICATION_TYPE type,
                                 const BoundingBox& bounds,
                                 const std::string& stroke_color,
                                 double angle = 0.0
                                );

  /**
   * Creates styles for all species glyphs.
   */
  bool createSpeciesStyles();

  /**
   * Check if a color with the given color string already exists.
   * If so, the id of the color is set on the given id string.
   * If the color does not exist yet, a color definition for it is
   * created and the id of the newly created color is returned in
   * the id string.
   * If color creation fails, false is returned by the method.
   */
  bool findOrCreateColorDefinition(const std::string& color_string, std::string& id);

  bool findOrCreateColorDefinition(const Paint& paint, std::string& id);

  /**
   * Tries to find the name for the given species identity.
   * If the name was found, it is returned in the name argument.
   * If something goes wrong, false is returned.
   */
  //bool findNameForSpeciesIdentity(const SpeciesIdentity& identity,std::string& name);

  /**
   * Goes through the dependency graph
   * and tries to find the root element for the given species alias id.
   */
  std::string findRootElementId(const std::string& id) const;

  /**
   * Creates a vector that is orthogonal to the given first vector.
   * If there is a problem, false is returned.
   */
  static bool createOrthogonal(const Point& v1, Point& v2);

  /**
   * Calculates the angle between the given vector and the positive x axis.
   * The result is returned in radians.
   */
  static double angle(const Point& v);

  /**
   * Calculates the position of point p after rotation by angle a
   * around the origin.
   * The angle is given in radians.
   * The result is returned in r.
   */
  static void rotate(const Point& p, double a, Point& r);

  /**
   * @brief adds the given protein modifications to the given group
   * @param pGroup the render group to add the modification to
   * @param bounds the bounds of the element
   * @param modifications list of angles where to attach the modifications
   * @param speciesModifications list of modification types
   * @param stroke_color the stroke color
   * @return status information as to whether or not the operation was successful
   */
  bool addProteinModifications(RenderGroup* pGroup,
                               const BoundingBox& bounds,
                               const std::vector<ProteinModification>& modifications,
                               const std::vector<SpeciesModification>& speciesModifications,
                               const std::string& stroke_color);

  /**
   * This method takes a pointer to a curve object
   * as well as a start iterator and an end iterator which
   * both iterate over a data structure that contains points.
   * For each point pair, a line segment is created and added to
   * curve.
   * The new curve segments are added to the end of the curve.
   *
   * If no error occurs, true is returned, else false is returned.
   */
  template<typename ITERATOR>
  static bool createLineSegments(Curve* pCurve, ITERATOR start, ITERATOR end)
  {
    bool result = true;

    // check if there is a curve and if there are points
    if (pCurve != NULL && start != end)
      {
        ITERATOR tmpEnd = end;
        --tmpEnd;

        // make sure there is more than one point
        if (start != tmpEnd)
          {
            LineSegment* pLS = pCurve->createLineSegment();
            pLS->setStart(&(*start));
            ++start;

            while (start != tmpEnd)
              {
                pLS->setEnd(&(*start));
                pLS = pCurve->createLineSegment();
                pLS->setStart(&(*start));
                ++start;
              }

            pLS->setEnd(&(*start));
          }
        else
          {
            result = false;
          }
      }
    else
      {
        result = false;
      }

    return result;
  }

  /**
   * Returns the color string for the given color id
   * or an empty string if the color id was not found.
   */
  std::string getColorString(const std::string& color_id) const;

  /**
   * @brief cleanString replaces sequences within the given text string
   * @param text the string to be cleaned
   * @return the cleaned string
   */
  static std::string cleanString(const std::string& text);

  static void replaceStringInPlace(std::string& subject, const std::string& search,
                                   const std::string& replace);

  static bool isDefaultOrEmpty(const Line &line);
};

#endif // CCellDesignerImporter_H__


