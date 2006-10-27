%{

#include "report/CCopasiStaticString.h"

%}  

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


class CCopasiStaticString: public CCopasiObject
{
  public:

#ifdef COPASI_DEBUG
   CCopasiStaticString(const std::string & name = "",
                        const CCopasiContainer * pParent = NULL,
                        const std::string & type = "String",
                        const unsigned C_INT32 & flag = CCopasiObject::StaticString);

    CCopasiStaticString(const CCopasiStaticString & src,
                        const CCopasiContainer * pParent = NULL);

    ~CCopasiStaticString();
#endif /* COPASI_DEBUG */


    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    const std::string & getStaticString() const;
  };

class CCopasiReportSeparator: public CCopasiStaticString
{
  public:
#ifdef COPASI_DEBUG
   CCopasiReportSeparator(const std::string & name = "",
                           const CCopasiContainer * pParent = NULL);

    CCopasiReportSeparator(const CCopasiStaticString & src,
                           const CCopasiContainer * pParent = NULL);

    ~CCopasiReportSeparator();
#endif /* COPASI_DEBUG */
    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


