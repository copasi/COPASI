# Microsoft Developer Studio Project File - Name="optimization" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=optimization - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "optimization.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "optimization.mak" CFG="optimization - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "optimization - Win32 Build" (based on "Win32 (x86) External Target")
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
# PROP BASE Target_File "../lib/optimization.lib"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f Makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "../lib/optimization.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "optimization - Win32 Build"

!IF  "$(CFG)" == "optimization - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CGA.cpp
# End Source File
# Begin Source File

SOURCE=.\COptFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\COptItem.cpp
# End Source File
# Begin Source File

SOURCE=.\COptMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\COptMethodEP2.cpp
# End Source File
# Begin Source File

SOURCE=.\COptMethodGA.cpp
# End Source File
# Begin Source File

SOURCE=.\COptMethodHGASA.cpp
# End Source File
# Begin Source File

SOURCE=.\COptMethodSA.cpp
# End Source File
# Begin Source File

SOURCE=.\COptProblem.cpp
# End Source File
# Begin Source File

SOURCE=.\COptTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CRandomSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\CRandomSearchMaster.cpp
# End Source File
# Begin Source File

SOURCE=.\CRealProblem.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CGA.h
# End Source File
# Begin Source File

SOURCE=.\COptFunction.h
# End Source File
# Begin Source File

SOURCE=.\COptItem.h
# End Source File
# Begin Source File

SOURCE=.\COptMethod.h
# End Source File
# Begin Source File

SOURCE=.\COptMethodEP2.h
# End Source File
# Begin Source File

SOURCE=.\COptMethodGA.h
# End Source File
# Begin Source File

SOURCE=.\COptMethodHGASA.h
# End Source File
# Begin Source File

SOURCE=.\COptMethodSA.h
# End Source File
# Begin Source File

SOURCE=.\COptProblem.h
# End Source File
# Begin Source File

SOURCE=.\COptTask.h
# End Source File
# Begin Source File

SOURCE=.\CRandomSearch.h
# End Source File
# Begin Source File

SOURCE=.\CRandomSearchMaster.h
# End Source File
# Begin Source File

SOURCE=.\CRealProblem.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\common.pri
# End Source File
# Begin Source File

SOURCE=..\lib.pri
# End Source File
# Begin Source File

SOURCE=.\optimization.pro
# End Source File
# End Target
# End Project
