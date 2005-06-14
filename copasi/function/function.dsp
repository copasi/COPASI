# Microsoft Developer Studio Project File - Name="function" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=function - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "function.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "function.mak" CFG="function - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "function - Win32 Build" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build"
# PROP BASE Intermediate_Dir "Build"
# PROP BASE Cmd_Line "nmake /f "Makefile""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "../lib/function.lib"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f Makefile"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "../lib/function.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "function - Win32 Build"

!IF  "$(CFG)" == "function - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCallParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationLexer_lex.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNode.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeConstant.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeOperator.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeStructure.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeWhiteSpace.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationParser_yacc.cpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationTree.cpp
# End Source File
# Begin Source File

SOURCE=.\CFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\CFunctionDB.cpp
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\CKinFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\CKinFunctionFlexLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\CMassAction.cpp
# End Source File
# Begin Source File

SOURCE=.\CNodeK.cpp
# End Source File
# Begin Source File

SOURCE=.\CRange.cpp
# End Source File
# Begin Source File

SOURCE=.\CUsageRange.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCallParameters.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationExpression.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationLexer.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNode.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeConstant.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeFunction.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeNumber.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeObject.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeOperator.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeStructure.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeVariable.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationNodeWhiteSpace.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationParser_yacc.h
# End Source File
# Begin Source File

SOURCE=.\CEvaluationTree.h
# End Source File
# Begin Source File

SOURCE=.\CFunction.h
# End Source File
# Begin Source File

SOURCE=.\CFunctionDB.h
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameter.h
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameters.h
# End Source File
# Begin Source File

SOURCE=.\CKinFunction.h
# End Source File
# Begin Source File

SOURCE=.\CKinFunctionFlexLexer.h
# End Source File
# Begin Source File

SOURCE=.\CMassAction.h
# End Source File
# Begin Source File

SOURCE=.\CNodeK.h
# End Source File
# Begin Source File

SOURCE=.\CRange.h
# End Source File
# Begin Source File

SOURCE=.\CUsageRange.h
# End Source File
# Begin Source File

SOURCE=.\FunctionDB.xml.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\CEvaluationLexer.lpp
# End Source File
# Begin Source File

SOURCE=.\CEvaluationParser.ypp
# End Source File
# Begin Source File

SOURCE=.\CKinFunctionFlexLexer.lpp
# End Source File
# Begin Source File

SOURCE=..\common.pri
# End Source File
# Begin Source File

SOURCE=.\function.pro
# End Source File
# Begin Source File

SOURCE=..\lib.pri
# End Source File
# End Target
# End Project
