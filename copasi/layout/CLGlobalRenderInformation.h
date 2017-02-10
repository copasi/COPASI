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

#include "copasi/utilities/CCopasiVector.h"

class CCopasiContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class GlobalRenderInformation;
LIBSBML_CPP_NAMESPACE_END

class CLGlobalRenderInformation : public CLRenderInformationBase
{
protected:
  CCopasiVector<CLGlobalStyle> mListOfStyles;

public:
  static CLGlobalRenderInformation * create(const CData & data);

  /**
   *  Constructor.
   */
  CLGlobalRenderInformation(CCopasiContainer* pParent = NULL);

  /**
   *  Copy Constructor.
   */
  CLGlobalRenderInformation(const CLGlobalRenderInformation& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGlobalRenderInformation(const GlobalRenderInformation& source,
                            /*
                            std::map<std::string,std::string>& colorIdToKeyMap,
                            std::map<std::string,std::string>& gradientIdToKeyMap,
                            std::map<std::string,std::string>& lineEndingIdToKeyMap,
                            */
                            CCopasiContainer* pParent = NULL);

  /**
   * Returns the number of styles.
   */
  size_t getNumStyles() const;

  /**
   * Returns a pointer to the LitOfStyles object.
   */
  CCopasiVector<CLGlobalStyle>* getListOfStyles();

  /**
   * Returns a pointer to the LitOfStyles object.
   */
  const CCopasiVector<CLGlobalStyle>* getListOfStyles() const;

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
