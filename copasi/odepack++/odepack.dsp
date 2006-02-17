# Microsoft Developer Studio Project File - Name="odepack" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=odepack - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "odepack.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "odepack.mak" CFG="odepack - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "odepack - Win32 Build" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
# PROP BASE Use_MFC
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build"
# PROP BASE Intermediate_Dir "Build"
# PROP BASE Cmd_Line "nmake /f "odepack.mak""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "odepack.exe"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f Makefile"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "../lib/odepack++.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "odepack - Win32 Build"

!IF  "$(CFG)" == "odepack - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CLSODA.cpp
# End Source File
# Begin Source File

SOURCE=.\common.cpp
# End Source File
# Begin Source File

SOURCE=.\Cxerrwd.cpp
# End Source File
# Begin Source File

SOURCE=.\dbnorm.cpp
# End Source File
# Begin Source File

SOURCE=.\dcfode.cpp
# End Source File
# Begin Source File

SOURCE=.\dewset.cpp
# End Source File
# Begin Source File

SOURCE=.\dfnorm.cpp
# End Source File
# Begin Source File

SOURCE=.\dintdy.cpp
# End Source File
# Begin Source File

SOURCE=.\dmnorm.cpp
# End Source File
# Begin Source File

SOURCE=.\dprja.cpp
# End Source File
# Begin Source File

SOURCE=.\dsolsy.cpp
# End Source File
# Begin Source File

SOURCE=.\dstoda.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CInternalSolver.h
# End Source File
# Begin Source File

SOURCE=.\CLSODA.h
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\Cxerrwd.h
# End Source File
# Begin Source File

SOURCE=.\dbnorm.h
# End Source File
# Begin Source File

SOURCE=.\dcfode.h
# End Source File
# Begin Source File

SOURCE=.\dewset.h
# End Source File
# Begin Source File

SOURCE=.\dfnorm.h
# End Source File
# Begin Source File

SOURCE=.\dgbfa.h
# End Source File
# Begin Source File

SOURCE=.\dgbsl.h
# End Source File
# Begin Source File

SOURCE=.\dgefa.h
# End Source File
# Begin Source File

SOURCE=.\dgesl.h
# End Source File
# Begin Source File

SOURCE=.\dmnorm.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=".\odepack++.pro"
# End Source File
# End Target
# End Project
