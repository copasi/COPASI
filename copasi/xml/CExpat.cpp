/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CExpat.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:06 $
   End CVS Header */

/**
 * CExpatTemplate class.
 * The class CExpatTemplate is a demplate definening a C++ interface to
 * the expat library.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CExpat.h"

#ifndef C_UNUSED
#define C_UNUSED(v)
#endif

CExpat::CExpat()
{}

CExpat::~CExpat()
{}

void CExpat::onStartElement(const XML_Char * C_UNUSED(pszName),
                            const XML_Char ** C_UNUSED(papszAttrs))
{return;}

void CExpat::onEndElement(const XML_Char * C_UNUSED(pszName))
{return;}

void CExpat::onCharacterData(const XML_Char * C_UNUSED(pszData),
                             int C_UNUSED(nLength))
{return;}

void CExpat::onProcessingInstruction(const XML_Char * C_UNUSED(pszTarget),
                                     const XML_Char * C_UNUSED(pszData))
{return;}

void CExpat::onComment(const XML_Char * C_UNUSED(pszData))
{return;}

void CExpat::onStartCdataSection()
{return;}

void CExpat::onEndCdataSection()
{return;}

void CExpat::onDefault(const XML_Char * C_UNUSED(pszData),
                       int C_UNUSED(nLength))
{return;}

bool CExpat::onExternalEntityRef(const XML_Char * C_UNUSED(pszContext),
                                 const XML_Char * C_UNUSED(pszBase),
                                 const XML_Char * C_UNUSED(pszSystemID),
                                 const XML_Char * C_UNUSED(pszPublicID))
{return false;}

bool CExpat::onUnknownEncoding(const XML_Char * C_UNUSED(pszName),
                               XML_Encoding * C_UNUSED(pInfo))
{return false;}

void CExpat::onStartNamespaceDecl(const XML_Char * C_UNUSED(pszPrefix),
                                  const XML_Char * C_UNUSED(pszURI))
{return;}

void CExpat::onEndNamespaceDecl(const XML_Char * C_UNUSED(pszPrefix))
{return;}

void CExpat::onXmlDecl(const XML_Char * C_UNUSED(pszVersion),
                       const XML_Char * C_UNUSED(pszEncoding),
                       bool C_UNUSED(fStandalone))
{return;}

void CExpat::onStartDoctypeDecl(const XML_Char * C_UNUSED(pszDoctypeName),
                                const XML_Char * C_UNUSED(pszSysID),
                                const XML_Char * C_UNUSED(pszPubID),
                                bool C_UNUSED(fHasInternalSubset))
{return;}

void CExpat::onEndDoctypeDecl()
{return;}
