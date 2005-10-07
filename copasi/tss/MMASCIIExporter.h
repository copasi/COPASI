/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/MMASCIIExporter.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: nsimus $ 
   $Date: 2005/10/07 12:35:49 $
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
     ** This method takes some of the copasi CModel objects
     ** and writes them in the ASCII format in an output file.
     ** The filename is given as the second
     ** argument to the function. The function return "true" on success and
     ** "false" on failure.
     */
    bool exportMathModel(const CModel* copasiModel, std::string mmasciiFilename, bool overwriteFile = false);

    /**
    ** This method tests if a string only consists of whitespace characters
    */
    bool isEmptyString(std::string & str);
    /**
     ** This method finds the metab by the name, returns an index
     **/
    C_INT32 findMetabXByName(const CModel* copasiModel, const std::string & Target);
    /**
     **  This method finds the compartement by the name, returns an index 
     **/
    C_INT32 findCompByName(const CModel* copasiModel, const std::string & Target);
    /**
     ** This method finds the global parameter by the name, returns an index 
     **/
    C_INT32 findGlobalParamByName(const CModel* copasiModel, const std::string & Target);
    /**
     ** This method finds the local reactions parameter by the name, returns an index
     **/
    C_INT32 findKinParamByName(const CReaction* reac, const std::string & Target);
    /**
     **   This method finds internal functions calls in a temporary evaluation tree
     **   and export them in output file 
     **/ 
    //void functionExport(CEvaluationNode* pNode, std::set<std::string>& exportedFunctionSet,  std::map< std::string, std::string > &functionNameMap, std::string mmasciiFilename);
    void functionExport(CEvaluationNode* pNode, std::set<std::string>& exportedFunctionSet, std::map< std::string, std::string > &functionNameMap, std::ostringstream & outFunction);
  };

#endif
