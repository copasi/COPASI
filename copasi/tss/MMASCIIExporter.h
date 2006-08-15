/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/MMASCIIExporter.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/08/15 11:37:24 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
    bool exportMathModel(const CModel* copasiModel, std::string mmasciiFilename, std::string Filter, bool overwriteFile = false);
    /**
    */
    bool exportMathModelInC(const CModel* copasiModel, std::ofstream & outFile);
    /**
     */
    bool exportMathModelInMMD(const CModel* copasiModel, std::ofstream & outFile);
    /**
     */
    bool exportMathModelInXPPAUT(const CModel* copasiModel, std::ofstream & outFile);

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
     **   This method finds internal functions calls for export in C
     **/
    void findFunctionsCallsC(const CEvaluationNode* pNode, std::set<std::string>& exportedFunctionSet, std::map< std::string, std::string > &functionNameMap, std::set<std::string> &functionNameSet, unsigned C_INT32 &findex, std::ostringstream & outFunction, std::ostringstream & outFunctionHeader);
    /**
     **    This method exports the functions in C format
     **/
    void functionExportC(const CFunction* pFunc, std::set<std::string>& exportedFunctionSet, std::map< std::string, std::string > &functionNameMap, std::set<std::string> &functionNameSet, unsigned C_INT32 &findex, std::ostringstream & outFunction, std::ostringstream & outFunctionHeader);
    /**
     **      This method adapt a Copasi name for Berkeley Madonna syntax:
     **      Names can not start with a number.
     **      Any other combination of letters and numbers is valid as is the underscore.
     **/
    std::string toMMDName(const std::string & name, std::set<std::string> & NameSet, std::map< std::string, unsigned C_INT32 > & EncounterNumber);
    /**
     **      This method tests whether the given Berkeley Madonna name already assigned,
     **      put the new name (in cappital letters:
     **      all names can be upper or lower case)
     **      in the set of assigned names
     **      or  modify the name
     **/
    std::string testMMDName(const std::string & name, std::set<std::string> & NameSet, std::map< std::string, unsigned C_INT32 > & EncounterNumber);
    /**
     **    This method exports the functions in Berkeley Madonna format
     **/
    void functionExportMMD (CEvaluationNode* pNode, std::ofstream & outFile, unsigned C_INT32 &findex, std::map< std::string, std::string > &functionNameMap);
    /**
     **      This method adapt a Copasi name for XPPAUT syntax:
     **      all XPPAUT names can have up to 9 letters each.
     **      Names can not start with a number.
     **      Any other combination of letters and numbers is valid as is the underscore.
     **/
    std::string toXPPName(const std::string & realName, std::set<std::string> & NameSet,
                          std::map< std::string, unsigned C_INT32 > & Frequancy);
    /**
     **      This method tests whether the given XPPAUT name already assigned,
     **      put the new name (in cappital letters:
     **      all names can be upper or lower case)
     **      in the set of assigned names
     **      or  modify the name
     **/
    std::string testXPPName(const std::string & name, std::set<std::string> & NameSet, std::map< std::string, unsigned C_INT32 > & Frequancy);

    /**
     **   The line length in XPPAUT ODE files (ASCII readable files) is limited to 256 characters.
     **   Individual lines can be continued with the UNIX backslash character, "\".
     **   The total length of any line cannot exceed 1000 characters.
     **/
    void toXPPLine(const std::string & line, std::ofstream & outFile);

    /**
     **      The method treats possible use of some XPP Reserved words as names in XPP ODE files
     **/
    void treatReservedXPPwords(std::set<std::string> & NameSet, std::map< std::string, unsigned C_INT32 > & Frequancy);

    /**
     **         This method exports internal functions in XPPAUT syntax
     **/
    void functionExportXPP (CEvaluationNode* pNode, std::ofstream & outFile,
                            unsigned C_INT32 &findex, std::map< std::string, std::string > &newNameMap,
                            std::set<std::string> & NameSet, std::map< std::string, unsigned C_INT32 > & Frequancy);

    /**
     **      This method assembles an expression sub tree for some internal call of Mass Action.
     **      The sub tree has to be included in the tree of corresponding root kinetic function in order to
     **      export this function in the C format whithout the user defined internall Mass Action calls
     **/
    void assembleSubTreeForMassAction(CEvaluationNode* newNode, CEvaluationNode* child1, CEvaluationNode* child2);

    /**
     **      This method modifies the export tree of the function for internal calls of Mass Action
     **/
    void modifyTreeForMassAction(CFunction* tmpFunc);
  };

#endif
