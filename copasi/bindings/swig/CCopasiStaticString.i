%{

#include "report/CCopasiStaticString.h"

%}  


class CCopasiStaticString: public CCopasiObject
{
  public:

   CCopasiStaticString(const std::string & name = "",
                        const CCopasiContainer * pParent = NULL,
                        const std::string & type = "String",
                        const unsigned C_INT32 & flag = CCopasiObject::StaticString);

    CCopasiStaticString(const CCopasiStaticString & src,
                        const CCopasiContainer * pParent = NULL);

    ~CCopasiStaticString();


    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    const std::string & getStaticString() const;
  };

class CCopasiReportSeparator: public CCopasiStaticString
{
  public:
   CCopasiReportSeparator(const std::string & name = "",
                           const CCopasiContainer * pParent = NULL);

    CCopasiReportSeparator(const CCopasiStaticString & src,
                           const CCopasiContainer * pParent = NULL);

    ~CCopasiReportSeparator();
    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

};


