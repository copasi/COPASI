%{

#include "report/CCopasiContainer.h"

%}



%ignore CCopasiContainer::CCopasiContainer(const std::string& name,
                                           const CCopasiContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);

class CCopasiContainer: public CCopasiObject
{
  private:
    CCopasiContainer();

  public:
    static CCopasiContainer* Root;
    static CCopasiObject* ObjectFromName(const CCopasiObjectName& objName);
    static void init();
    
    CCopasiContainer(const std::string& name,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & type = "CN",
                     const unsigned C_INT32 & flag = CCopasiObject::Container);

    virtual ~CCopasiContainer();
    
    

};
