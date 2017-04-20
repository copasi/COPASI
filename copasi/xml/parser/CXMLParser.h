// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * CXMLParser class.
 * This class is the parses a COPASI XML file.
 *
 * Created for COPASI by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CXMLParser
#define COPASI_CXMLParser

#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "copasi/xml/parser/CXMLParserData.h"
#include "copasi/xml/parser/CXMLHandlerFactory.h"

#include "copasi/xml/CExpat.h"
#include "copasi/xml/CCopasiXMLInterface.h"

#include "copasi/core/CDataVector.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/model/CAnnotation.h"

class CXMLParser : public CExpat
{
  // Attributes
private:
  /**
   * Attributes accessible through the whole parser.
   */
  CXMLParserData mData;

  /**
   * The handler factory managing all needed handlers
   */
  CXMLHandlerFactory *mpFactory;

  /**
   * The character data.
   */
  std::string mCharacterData;

  /**
   * The character data.
   */
  CCopasiXMLInterface::EncodingType mCharacterDataEncoding;

  /**
   * The element handler stack
   */
  std::stack< CXMLHandler * > mElementHandlerStack;

  // Operations
private:
  /**
   * Constructor
   */
  CXMLParser();

public:
  /**
   * Public constructor
   * @param CVersion & version
   */
  CXMLParser(CVersion & version);

  /**
   * Destructor
   */
  ~CXMLParser();

  /**
   * Start element handler
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   */
  virtual void onStartElement(const XML_Char *pszName,
                              const XML_Char **papszAttrs);

  /**
   * End element handler
   * @param const XML_Char *pszName
   */
  virtual void onEndElement(const XML_Char *pszName);

  /**
   * Set the datamodel.
   * @param CDataModel* pDataModel
   */
  void setDatamodel(CDataModel* pDataModel);

  /**
   * Set the list of loaded functions
   * @param CDataVectorN< CFunction > * pFunctionList
   */
  void setFunctionList(CDataVectorN< CFunction > * pFunctionList);

#ifdef XXXX
  /**
   * Start CDATA section handler
   */
  virtual void onStartCdataSection();

  /**
   * End CDATA section handler
   */
  virtual void onEndCdataSection();
#endif // XXXX

  /**
   * Skipped entity handler
   * This is called in two situations:
   * 1) An entity reference is encountered for which no declaration
   *    has been read *and* this is not an error.
   * 2) An internal entity reference is read, but not expanded, because
   *    XML_SetDefaultHandler has been called.
   * Note: skipped parameter entities in declarations and skipped general
   *       entities in attribute values cannot be reported, because
   *       the event would be out of sync with the reporting of the
   *       declarations or attribute values
   * @param const XML_Char *entityName
   * @param int is_parameter_entity
   */
  virtual void onSkippedEntityHandler(const XML_Char * entityName,
                                      int is_parameter_entity);

  /**
   * Enable/Disable the character data handler
   * @param bool fEnable (Default: true)
   */
  void enableCharacterDataHandler(bool fEnable = true);

  /**
   * Character data handler
   * @param const XML_Char *pszData
   * @param int nLength
   */
  virtual void onCharacterData(const XML_Char *pszData,
                               int nLength);
  /**
   * Retrieve the data.
   * Any sequence of toBeStripped characters is replaced by a single
   * join character. The default is no stripping.
   * @param const std::string & toBeStripped (default: "")
   * @param const std::string & join (default: " ")
   * @return std::string data
   */
  std::string getCharacterData(const std::string & toBeStripped = "",
                               const std::string & join = " ");

  /**
   * Push the element handler on the stack.
   * @param CXMLHandler * pElementHandler
   */
  void pushElementHandler(CXMLHandler * pElementHandler);

  /**
   * Pop the element handler form the stack.
   */
  void popElementHandler();

  /**
   * Retrieve the loaded model functions
   * @return CModel * pModel
   */
  CModel * getModel() const;

  /**
   * Retrieve the list of loaded reports
   * @return CReportDefinitionVector * pReportList
   */
  CReportDefinitionVector * getReportList() const;

  /**
   * Retrieve the list of loaded functions
   * @return CDataVectorN< CTask > * pTaskList
   */
  CDataVectorN< CCopasiTask > * getTaskList() const;

  /**
   * Retrieve the list of loaded functions
   * @return COutputDefinitionVector * pPlotList
   */
  COutputDefinitionVector * getPlotList() const;

  /**
   * Set the GUI information to be saved
   * @param SCopasiXMLGUI * pGUI
   */
  void setGUI(SCopasiXMLGUI * pGUI);

  /**
   * Set the list of loaded layouts
   * @param CListOfLayouts * pLayoutList
   */
  void setLayoutList(CListOfLayouts * pLayoutList);

  /**
   * Retrieve the list of loaded layouts
   * @return CListOfLayouts * pLayoutList
   */
  CListOfLayouts * getLayoutList() const;

  /**
   * Retrieve Unit Definitions to be added
   * to the Root Container's global list.
   * @return CUnitDefinitionDB * pUnitDefinitionImportList
   */
  CUnitDefinitionDB *getUnitDefinitionImportList() const;

  /**
   * Retrieve a pointer to the current group if available
   * @return const CCopasiParameterGroup * currentGroup
   */
  const CCopasiParameterGroup * getCurrentGroup() const;

  CXMLHandler * getHandler(const CXMLHandler::Type & type);

  void setCharacterEncoding(const CCopasiXMLInterface::EncodingType & encoding);
};

#endif // COPASI_CXMLParser
