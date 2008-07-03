// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CConstants.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/03 12:33:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CConstants
#define COPASI_CConstants

#include <string>
#include <map>
#include <vector>

class CRDFNode;

class CMIRIAMResource
  {
  public:
    struct sResource
      {
        std::string MiriamId;
        std::string DisplayName;
        std::string URL;
        std::string URI;
        std::string Deprecated[4];
        std::string Regexp;
        bool Citation;
      };

  private:
    static sResource Resources[];

    static bool Initialized;
    static std::map< std::string, unsigned C_INT32 > DisplayName2Resource;
    // TODO when the URIBase is no longer unique we need to introduce a multi map.
    static std::map< std::string, unsigned C_INT32 > URI2Resource;

  private:
    static void createDisplayNameMap();
    static void createURIMap();

  public:
    static unsigned C_INT32 getResource(const std::string & URI);
    static const sResource * getResourceList();

  private:
    CMIRIAMResource();

  public:
    CMIRIAMResource(CRDFNode * pNode);

    CMIRIAMResource(const std::string & displayName, const std::string & id);

    CMIRIAMResource(const CMIRIAMResource & src);

    bool setId(const std::string & id);

    const std::string & getId() const;

    bool setURI(const std::string & URI);

    std::string getURI() const;

    bool setNode(CRDFNode * pNode);

    CRDFNode * getNode() const;

    bool setDisplayName(const std::string & displayName);

    std::string getDisplayName() const;

    bool isValid() const;

    bool isValid(const std::string & URI) const;

  private:
    void extractId(const std::string & URI);

  private:
    unsigned C_INT32 mResource;
    std::string mId;
    CRDFNode * mpNode;
  };

#endif
