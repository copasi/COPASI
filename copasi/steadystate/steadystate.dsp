# Microsoft Developer Studio Project File - Name="steadystate" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=steadystate - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "steadystate.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "steadystate.mak" CFG="steadystate - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "steadystate - Win32 Build" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build"
# PROP BASE Intermediate_Dir "Build"
# PROP BASE Cmd_Line "nmake /f "Makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "../lib/steadystate.lib"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f Makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "../lib/steadystate.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "steadystate - Win32 Build"

!IF  "$(CFG)" == "steadystate - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CEigen.cpp
# End Source File
# Begin Source File

SOURCE=.\CMca.cpp
# End Source File
# Begin Source File

SOURCE=.\CMCAMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CMCAProblem.cpp
# End Source File
# Begin Source File

SOURCE=.\CMCATask.cpp
# End Source File
# Begin Source File

SOURCE=.\CNewtonMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CSteadyStateMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CSteadyStateProblem.cpp
# End Source File
# Begin Source File

SOURCE=.\CSteadyStateTask.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CEigen.h
# End Source File
# Begin Source File

SOURCE=.\CMca.h
# End Source File
# Begin Source File

SOURCE=.\CMCAMethod.h
# End Source File
# Begin Source File

SOURCE=.\CMCAProblem.h
# End Source File
# Begin Source File

SOURCE=.\CMCATask.h
# End Source File
# Begin Source File

SOURCE=.\CNewtonMethod.h
# End Source File
# Begin Source File

SOURCE=.\CSteadyStateMethod.h
# End Source File
# Begin Source File

SOURCE=.\CSteadyStateProblem.h
# End Source File
# Begin Source File

SOURCE=.\CSteadyStateTask.h
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

SOURCE=.\steadystate.pro
# End Source File
# End Target
# End Project
