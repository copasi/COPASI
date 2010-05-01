// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGlobalRenderInformation.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/05/01 14:35:03 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGlobalRenderInformation_H__
#define CLGlobalRenderInformation_H__

#include <copasi/layout/CLRenderInformationBase.h>
#include <copasi/layout/CLGlobalStyle.h>

#include <copasi/utilities/CCopasiVector.h>

#include <string>

#include <sbml/layout/render/GlobalRenderInformation.h>

class CCopasiContainer;

class CLGlobalRenderInformation : public CLRenderInformationBase
{
protected:
  CCopasiVector<CLGlobalStyle> mListOfStyles;

public:
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
  unsigned int getNumStyles() const;

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
  CLStyle* getStyle(unsigned int i);

  /**
   * Returns a pointer to the style with the given index.
   * If the index is invalid, NULL is returned.
   */
  const CLStyle* getStyle(unsigned int i) const;

  CLGlobalStyle* createStyle();

  void addStyle(const CLGlobalStyle* pStyle);

  /**
   * Converts this object to the corresponding SBML object.
   */
  GlobalRenderInformation* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLGlobalRenderInformation_H__ */
