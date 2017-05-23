// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGlobalRenderInformation_H__
#define CLGlobalRenderInformation_H__

#include <string>

#include "copasi/layout/CLRenderInformationBase.h"
#include "copasi/layout/CLGlobalStyle.h"

#include "copasi/core/CDataVector.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class GlobalRenderInformation;
LIBSBML_CPP_NAMESPACE_END

class CLGlobalRenderInformation : public CLRenderInformationBase
{
protected:
  CDataVector<CLGlobalStyle> mListOfStyles;

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CLGlobalRenderInformation * pDataObject
   */
  static CLGlobalRenderInformation * fromData(const CData & data);

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
  virtual bool applyData(const CData & data);

  /**
   *  Constructor.
   */
  CLGlobalRenderInformation(CDataContainer* pParent = NULL);

  /**
   *  Copy Constructor.
   */
  CLGlobalRenderInformation(const CLGlobalRenderInformation& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGlobalRenderInformation(const GlobalRenderInformation& source,
                            /*
                            std::map<std::string,std::string>& colorIdToKeyMap,
                            std::map<std::string,std::string>& gradientIdToKeyMap,
                            std::map<std::string,std::string>& lineEndingIdToKeyMap,
                            */
                            CDataContainer* pParent = NULL);

  /**
   * Returns the number of styles.
   */
  size_t getNumStyles() const;

  /**
   * Returns a pointer to the LitOfStyles object.
   */
  CDataVector<CLGlobalStyle>* getListOfStyles();

  /**
   * Returns a pointer to the LitOfStyles object.
   */
  const CDataVector<CLGlobalStyle>* getListOfStyles() const;

  /**
   * Returns a pointer to the style with the given index.
   * If the index is invalid, NULL is returned.
   */
  CLStyle* getStyle(size_t i);

  /**
   * Returns a pointer to the style with the given index.
   * If the index is invalid, NULL is returned.
   */
  const CLStyle* getStyle(size_t i) const;

  virtual CLStyle * createStyle();

  void addStyle(const CLGlobalStyle* pStyle);

  /**
   * Converts this object to the corresponding SBML object.
   */
  bool toSBML(GlobalRenderInformation* pGRI, unsigned int level, unsigned int version) const;
};

#endif /* CLGlobalRenderInformation_H__ */
