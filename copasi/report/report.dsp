# Microsoft Developer Studio Project File - Name="report" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=report - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "report.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "report.mak" CFG="report - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "report - Win32 Build" (based on "Win32 (x86) External Target")
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
# PROP BASE Target_File "../lib/report.lib"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f Makefile"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "../lib/report.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "report - Win32 Build"

!IF  "$(CFG)" == "report - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCopasiContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\CCopasiObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CCopasiObjectName.cpp
# End Source File
# Begin Source File

SOURCE=.\CCopasiStaticString.cpp
# End Source File
# Begin Source File

SOURCE=.\CKeyFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\CReport.cpp
# End Source File
# Begin Source File

SOURCE=.\CReportBody.cpp
# End Source File
# Begin Source File

SOURCE=.\CReportDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\CReportDefinitionVector.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCopasiContainer.h
# End Source File
# Begin Source File

SOURCE=.\CCopasiObject.h
# End Source File
# Begin Source File

SOURCE=.\CCopasiObjectName.h
# End Source File
# Begin Source File

SOURCE=.\CCopasiObjectReference.h
# End Source File
# Begin Source File

SOURCE=.\CCopasiStaticString.h
# End Source File
# Begin Source File

SOURCE=.\CKeyFactory.h
# End Source File
# Begin Source File

SOURCE=.\CReport.h
# End Source File
# Begin Source File

SOURCE=.\CReportBody.h
# End Source File
# Begin Source File

SOURCE=.\CReportDefinition.h
# End Source File
# Begin Source File

SOURCE=.\CReportDefinitionVector.h
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

SOURCE=.\report.pro
# End Source File
# End Target
# End Project
