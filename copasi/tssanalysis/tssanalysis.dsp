# Microsoft Developer Studio Project File - Name="tssanalysis" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=trajectory - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tssanalysis.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tssanalysis.mak" CFG="trajectory - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tssanalysis - Win32 Build" (based on "Win32 (x86) External Target")
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
# PROP BASE Target_File "../lib/tssanalysis.lib"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f Makefile"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "../tmp/tssanalysis.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "tssanalysis - Win32 Build"

!IF  "$(CFG)" == "tssanalysis - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CILDMMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CCSPMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CTSSAMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\CTSSAProblem.cpp
# End Source File
# Begin Source File

SOURCE=.\CTSSATask.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CILDMMethod.h
# End Source File
# Begin Source File
 
SOURCE=.\CCSPMethod.h
# End Source File
# Begin Source File

SOURCE=.\CTSSAMethod.h
# End Source File
# Begin Source File

SOURCE=.\CTSSAProblem.h
# End Source File
# Begin Source File

SOURCE=.\CTSSATask.h
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

SOURCE=.\tssanalysis.pro
# End Source File
# End Target
# End Project
