# Microsoft Developer Studio Project File - Name="CopasiUI3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CopasiUI3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CopasiUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CopasiUI.mak" CFG="CopasiUI3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CopasiUI3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CopasiUI3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(QTDIR)\include" /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 mkl_lapack.lib mkl_p3.lib mkl_c.lib function.lib model.lib output.lib trajectory.lib utilities.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qt-mt230nc.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /machine:I386 /libpath:"../Release" /libpath:"$(CBLAS_LIB)/ia32/lib"

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mkl_lapack.lib mkl_p3.lib mkl_c.lib steadystate.lib utilities.lib function.lib model.lib output.lib report.lib trajectory.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qt-mt307.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /pdbtype:sept /libpath:"../Debug" /libpath:"$(CBLAS_LIB)/ia32/lib"
# SUBTRACT LINK32 /profile /incremental:no /nodefaultlib

!ENDIF 

# Begin Target

# Name "CopasiUI3 - Win32 Release"
# Name "CopasiUI3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CompartmentsWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\CompartmentsWidget.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\CompartmentsWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\CompartmentsWidget1.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\copasiui3window.cpp
# End Source File
# Begin Source File

SOURCE=.\copasiui3window.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionWidget.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionWidget1.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\listviews.cpp
# End Source File
# Begin Source File

SOURCE=.\listviews.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget1.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\MoietiesWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\MoietyWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\MoietyWidget.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\MoietyWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\MoietyWidget1.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\MyLineEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MyLineEdit.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Observer.cpp
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget1.moc.cpp
# End Source File
# Begin Source File

SOURCE=.\Subject.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CompartmentsWidget.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\CompartmentsWidget.h
InputName=CompartmentsWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\CompartmentsWidget.h
InputName=CompartmentsWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CompartmentsWidget1.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\CompartmentsWidget1.h
InputName=CompartmentsWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\CompartmentsWidget1.h
InputName=CompartmentsWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\copasiui3window.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\copasiui3window.h
InputName=copasiui3window

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\copasiui3window.h
InputName=copasiui3window

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DataModel.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FunctionWidget.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget.h...
InputDir=.
InputPath=.\FunctionWidget.h
InputName=FunctionWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\FunctionWidget.h
InputName=FunctionWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FunctionWidget1.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget1.h...
InputDir=.
InputPath=.\FunctionWidget1.h
InputName=FunctionWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\FunctionWidget1.h
InputName=FunctionWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\listviews.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\listviews.h
InputName=listviews

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\listviews.h
InputName=listviews

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MetabolitesWidget.h
InputName=MetabolitesWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MetabolitesWidget.h
InputName=MetabolitesWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget1.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MetabolitesWidget1.h
InputName=MetabolitesWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MetabolitesWidget1.h
InputName=MetabolitesWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoietiesWidget.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoietyWidget.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MoietyWidget.h
InputName=MoietyWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MoietyWidget.h
InputName=MoietyWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoietyWidget1.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MoietyWidget1.h
InputName=MoietyWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MoietyWidget1.h
InputName=MoietyWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyLineEdit.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MyLineEdit.h...
InputDir=.
InputPath=.\MyLineEdit.h
InputName=MyLineEdit

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\MyLineEdit.h
InputName=MyLineEdit

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyTable.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Observer.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget.h...
InputDir=.
InputPath=.\ReactionsWidget.h
InputName=ReactionsWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\ReactionsWidget.h
InputName=ReactionsWidget

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget1.h

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget1.h...
InputDir=.
InputPath=.\ReactionsWidget1.h
InputName=ReactionsWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build -  $(InputName).h -> $(InputName).moc.cpp
InputDir=.
InputPath=.\ReactionsWidget1.h
InputName=ReactionsWidget1

"$(InputDir)\$(InputName).moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\$(InputName).moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Structures.h
# End Source File
# Begin Source File

SOURCE=.\Subject.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Tree.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\FunctionWidget1.moc

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget1.cpp...
InputDir=.
InputPath=.\FunctionWidget1.moc
InputName=FunctionWidget1

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).cpp -o $(InputDir)\$(InputName).moc

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget1.cpp...
InputDir=.
InputPath=.\FunctionWidget1.moc
InputName=FunctionWidget1

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).cpp -o $(InputDir)\$(InputName).moc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget1.moc.moc

!IF  "$(CFG)" == "CopasiUI3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget1.moc.cpp...
InputDir=.
InputPath=.\ReactionsWidget1.moc.moc
InputName=ReactionsWidget1.moc

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).cpp -o $(InputDir)\$(InputName).moc

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget1.moc.cpp...
InputDir=.
InputPath=.\ReactionsWidget1.moc.moc
InputName=ReactionsWidget1.moc

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).cpp -o $(InputDir)\$(InputName).moc

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
