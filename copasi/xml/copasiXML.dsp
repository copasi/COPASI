# Microsoft Developer Studio Project File - Name="copasiXML" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=copasiXML - Win32 Build
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "copasiXML.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "copasiXML.mak" CFG="copasiXML - Win32 Build"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "copasiXML - Win32 Build" (based on "Win32 (x86) External Target")
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
# PROP BASE Target_File "../lib/copasiXML.lib"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build"
# PROP Intermediate_Dir "Build"
# PROP Cmd_Line "nmake /f "Makefile""
# PROP Rebuild_Opt "/a"
# PROP Target_File "../lib/copasiXML.lib"
# PROP Bsc_Name ""
# PROP Target_Dir ""
# Begin Target

# Name "copasiXML - Win32 Build"

!IF  "$(CFG)" == "copasiXML - Win32 Build"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCopasiXML.cpp
# End Source File
# Begin Source File

SOURCE=.\CCopasiXMLInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\CCopasiXMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\CExpat.cpp
# End Source File
# Begin Source File

SOURCE=.\CXMLHandler.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCopasiXML.h
# End Source File
# Begin Source File

SOURCE=.\CCopasiXMLInterface.h
# End Source File
# Begin Source File

SOURCE=.\CCopasiXMLParser.h
# End Source File
# Begin Source File

SOURCE=.\CExpat.h
# End Source File
# Begin Source File

SOURCE=.\CXMLHandler.h
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

SOURCE=.\xml.pro
# End Source File
# End Target
# End Project
