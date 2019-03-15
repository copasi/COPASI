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

#ifndef COPASI_CAnnotation
#define COPASI_CAnnotation

#include <string>
#include <map>

#include "copasi/undo/CUndoData.h"

class CDataObject;
class CMIRIAMInfo;
class CDataContainer;

class CAnnotation
{
public:
  typedef std::map< std::string, std::string > UnsupportedAnnotation;

private:
  static std::map< CDataContainer *, CMIRIAMInfo * > Container2Info;

  // Operations
public:
  static CAnnotation * castObject(CDataObject * pObject);
  static const CAnnotation * castObject(const CDataObject * pObject);

  /**
   * Allocat a MIRIAM Info object for the given CDataContainer * pParent.
   * The ownership is with the parent
   * @param CDataContainer * pParent
   * @return CMIRIAMInfo * pMiriamInfo
   */
  static CMIRIAMInfo * allocateMiriamInfo(CDataContainer * pParent);

  /**
   * Free if possible an existing MIRIAM Info object for the given CDataContainer * pParent.
   * @return CMIRIAMInfo * pMiriamInfo
   */
  static void freeMiriamInfo(CDataContainer * pParent);

  /**
   * Retrieve the data describing the annotation
   * @return CData data
   */
  CData toData() const;

  /**
   * Apply the provided data to the annotation
   * @param const CData & data
   * @return bool success
   */
  bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  void createUndoData(CUndoData & undoData,
                      const CUndoData::Type & type,
                      const CData & oldData = CData(),
                      const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   * Default constructor
   */
  CAnnotation();

  /**
   * Copy constructor
   * @param const CAnnotation & src
   */
  CAnnotation(const CAnnotation & src);

  /**
   * Destructor
   */
  virtual ~CAnnotation();

  /**
   * Retrieve the key
   * @return std::string key
   */
  virtual const std::string & getKey() const;

  void initMiriamAnnotation(const std::string & newId);

  /**
   * Set the RDF/XML representation of the MIRIAM annotation
   * @param const std::string & miriamAnnotation
   * @param const std::string & newId
   * @param const std::string & oldId
   */
  void setMiriamAnnotation(const std::string & miriamAnnotation,
                           const std::string & newId,
                           const std::string & oldId);

  /**
   * Retrieve the RDF/XML representation of the MIRIAM annotation
   * @return const std::string & miriamAnnotation
   */
  const std::string & getMiriamAnnotation() const;

  /**
   * Set the XHTML Notes
   * @param const std::string & notes
   */
  void setNotes(const std::string & notes);

  /**
   * Retrieve the XHTML notes
   * @return const std::string & notes
   */
  const std::string & getNotes() const;

  /**
   * Comparison operator
   * @param const CAnnotation & rhs
   * @return bool equal
   */
  bool operator == (const CAnnotation & rhs) const;

  /**
   * Retrieve the unsupported annotations in xml format.
   * @return std::map< std::string, std::string > & unsupportedAnnotations
   */
  UnsupportedAnnotation & getUnsupportedAnnotations();
  const UnsupportedAnnotation & getUnsupportedAnnotations() const;

  /**
   * Add an unsupported annotation
   * @param const std::string & name
   * @param const std::string & xml
   * @return bool success
   */
  bool addUnsupportedAnnotation(const std::string & name, const std::string & xml);

  /**
   * Replace an unsupported annotation
   * @param const std::string & name
   * @param const std::string & xml
   * @return bool success
   */
  bool replaceUnsupportedAnnotation(const std::string & name, const std::string & xml);

  /**
   * Remove an unsupported annotation
   * @param const std::string & name
   * @return bool success
   */
  bool removeUnsupportedAnnotation(const std::string & name);

private:
  static bool isValidXML(const std::string & xml);

  // Attributes
protected:
  /**
   *  Key of the model entity. It is stored here, but constructed in the derived classes.
   */
  std::string mKey;

private:
  /**
   * Notes in XHTML format
   */
  std::string mNotes;

  /**
   * MIRIAM compliant annotation in RDF/XML format
   */
  std::string mMiriamAnnotation;

  /**
   * The XMLId used in the about statement
   */
  std::string mXMLId;

  /**
   * The annotations which are not supported by COPASI. Note,
   * the name is enforced to be unique.
   */
  UnsupportedAnnotation mUnsupportedAnnotations;
};

#endif // COPASI_CAnnotation
