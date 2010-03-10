// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLLocalRenderInformation.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLLocalRenderInformation_H__
#define CLLocalRenderInformation_H__

#include <copasi/layout/CLRenderInformationBase.h>
#include <copasi/layout/CLLocalStyle.h>

#include <sbml/layout/render/LocalRenderInformation.h>

class CCopasiContainer;

class CLLocalRenderInformation: public CLRenderInformationBase
{
protected:
  CCopasiVector<CLLocalStyle> mListOfStyles;

public:
  /**
   *  Constructor.
   */
  CLLocalRenderInformation(CCopasiContainer* pParent = NULL);

  /**
   *  Copy Constructor.
   */
  CLLocalRenderInformation(const CLLocalRenderInformation& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLLocalRenderInformation(const LocalRenderInformation& source,
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
  CCopasiVector<CLLocalStyle>* getListOfStyles();

  /**
   * Returns a pointer to the LitOfStyles object.
   */
  const CCopasiVector<CLLocalStyle>* getListOfStyles() const;

  /**
   * Returns a pointer to the style with the given index.
   * If the index is invalid, NULL is returned.
   */
  CLLocalStyle* getStyle(unsigned int i);

  /**
   * Returns a pointer to the style with the given index.
   * If the index is invalid, NULL is returned.
   */
  const CLLocalStyle* getStyle(unsigned int i) const;

  CLLocalStyle* createStyle();

  void addStyle(const CLLocalStyle* pStyle);

  /**
   * Converts this object to the corresponding SBML object.
   */
  LocalRenderInformation* toSBML(
    /*
    std::map<std::string,std::string>& colorKeyToIdMap,
    std::map<std::string,std::string>& gradientKeyToIdMap,
    std::map<std::string,std::string>& lineEndingKeyToIdMap
    */
  ) const;
};

#endif /* CLLocalRenderInformation_H__ */
