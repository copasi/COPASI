# Microsoft Developer Studio Project File - Name="model" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=model - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "model.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "model.mak" CFG="model - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "model - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "model - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "model - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy
PostBuild_Cmds=copy Release\*.lib ..\Release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "model - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy
PostBuild_Cmds=copy Debug\*.lib ..\Debug
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "model - Win32 Release"
# Name "model - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CChemEq.cpp
# End Source File
# Begin Source File

SOURCE=.\CChemEqElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CCompartment.cpp
# End Source File
# Begin Source File

SOURCE=.\CDeTerm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CMetab.cpp
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CMoiety.cpp
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CReaction.cpp
# End Source File
# Begin Source File

SOURCE=.\CScanInputFlexLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\CSpec2Model.cpp
# End Source File
# Begin Source File

SOURCE=.\CSpecLine.cpp
# End Source File
# Begin Source File

SOURCE=.\CState.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CChemEq.h
# End Source File
# Begin Source File

SOURCE=.\CChemEqElement.h
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CCompartment.h
# End Source File
# Begin Source File

SOURCE=.\CDeTerm.h
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CMetab.h
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CModel.h
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CMoiety.h
# End Source File
# Begin Source File

SOURCE=..\..\copasi\model\CReaction.h
# End Source File
# Begin Source File

SOURCE=.\CSpec2Model.h
# End Source File
# Begin Source File

SOURCE=.\CSpecLine.h
# End Source File
# Begin Source File

SOURCE=.\CState.h
# End Source File
# Begin Source File

SOURCE=.\model.h
# End Source File
# End Group
# End Target
# End Project
