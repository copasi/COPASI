/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/MMASCIIExporter.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: nsimus $ 
   $Date: 2005/07/14 10:52:03 $
   End CVS Header */

#ifndef MMASCIIExpoter_H__
#define MMASCIIExpoter_H__

#include "model/CModel.h"
#include "model/CMetab.h"
#include <string>

class MMASCIIExporter
  {
  protected:
    /*
    **  
    */
  public:
    /**
     ** Default constructor for the exporter.
     */

    MMASCIIExporter();
    /*
    ** Destructor for the exporter.
     */
    virtual ~MMASCIIExporter();

    /**
     ** This method takes some of the copasi objects : such as CMetab, ... 
     ** and writes them to an ASCII output file. The filename is given as the second
     ** argument to the function. The function return "true" on success and
     ** "false" on failure.
     */
    bool exportMathModel(const CModel* copasiModel, std::string mmasciiFilename, bool overwriteFile = false);

    /**
    ** This method tests if a string only consists of whitespace characters
    */ 
    //bool isEmptyString(const std::string& str);
  };

#endif
