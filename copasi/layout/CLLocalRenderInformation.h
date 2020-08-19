// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CLLocalRenderInformation_H__
#define CLLocalRenderInformation_H__

#include "copasi/layout/CLRenderInformationBase.h"
#include "copasi/layout/CLLocalStyle.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class LocalRenderInformation;
LIBSBML_CPP_NAMESPACE_END

class CLLocalRenderInformation: public CLRenderInformationBase
{
protected:
  CDataVector<CLLocalStyle> mListOfStyles;

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLLocalRenderInformation * pDataObject
   */
  static CLLocalRenderInformation * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   *  Constructor.
   */
  CLLocalRenderInformation(CDataContainer* pParent = NULL);

  /**
   *  Copy Constructor.
   */
  CLLocalRenderInformation(const CLLocalRenderInformation& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLLocalRenderInformation(const LocalRenderInformation& source,
                           /*
                           std::map<std::string,std::string>& colorIdToKeyMap,
                           std::map<std::string,std::string>& gradientIdToKeyMap,
                           std::map<std::string,std::string>& lineEndingIdToKeyMap,
                           */
                           CDataContainer* pParent = NULL);

  /**
   * Returns the number of styles.
   */
  virtual size_t getNumStyles() const;

  /**
   * Returns a pointer to the LitOfStyles object.
   */
  CDataVector<CLLocalStyle>* getListOfStyles();

  /**
   * Returns a pointer to the LitOfStyles object.
   */
  const CDataVector<CLLocalStyle>* getListOfStyles() const;

  /**
   * Returns a pointer to the style with the given index.
   * If the index is invalid, NULL is returned.
   */
  virtual CLLocalStyle* getStyle(size_t i);

  /**
   * Returns a pointer to the style with the given index.
   * If the index is invalid, NULL is returned.
   */
  virtual const CLLocalStyle * getStyle(size_t i) const;

  /**
   * Creates a new style, and adds it to the list of styles (where it is owned)
   *
   * @return the newly created style
   */
  virtual CLStyle * createStyle();

  /**
   * Returns the style for the graphical object or NULL
   *
   * @param pObject the graphical object
   * @return the style if one is available for the object
   */
  virtual const CLStyle * getStyleForGraphicalObject(const CLGraphicalObject * pObject) const;


  void addStyle(const CLLocalStyle* pStyle);

  /**
   * Converts this object to the corresponding SBML object.
   */
  LocalRenderInformation* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLLocalRenderInformation_H__ */
