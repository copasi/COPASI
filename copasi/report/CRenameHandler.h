/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CRenameHandler.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/12 15:06:33 $
   End CVS Header */

#ifndef COPASI_CRenameHandler
#define COPASI_CRenameHandler

//just the abstract class to handle things that need to be done after every rename

class CRenameHandler
  {
  public:
    virtual bool handle(const std::string & oldCN, const std::string & newCN) const = 0;
  };

#endif
