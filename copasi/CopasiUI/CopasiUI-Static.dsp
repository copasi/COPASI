# Microsoft Developer Studio Project File - Name="CopasiUI Static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CopasiUI Static - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CopasiUI-Static.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CopasiUI-Static.mak" CFG="CopasiUI Static - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CopasiUI Static - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CopasiUI Static - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release-Static"
# PROP Intermediate_Dir "..\Release-Static"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(QTDIR)\include" /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_NODLL" /D "QT_THREAD_SUPPORT" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 $(QTDIR)\lib\qt-mt302.lib mkl_lapack.lib mkl_p3.lib mkl_c.lib scan.lib randomGenerator.lib utilities.lib function.lib mathmodel.lib model.lib output.lib trajectory.lib winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qtmain.lib $(QTDIR)\lib\qt-mt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"msvcrtd.lib" /libpath:"../Release" /libpath:"$(CBLAS_LIB)/ia32/lib"

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug-Static"
# PROP Intermediate_Dir "..\Debug-Static"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QT_NODLL" /D "QT_THREAD_SUPPORT" /FR /FD /GZ /c
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
# ADD LINK32 steadystate.lib report.lib clapack.lib $(QTDIR)\lib\qt-mt.lib scan.lib randomGenerator.lib utilities.lib function.lib mathmodel.lib model.lib output.lib trajectory.lib winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /pdbtype:sept /libpath:"../Debug" /libpath:"$(CBLAS_LIB)/ia32/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "CopasiUI Static - Win32 Release"
# Name "CopasiUI Static - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CompartmentsWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\CompartmentsWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\CompartmentSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\ConstantSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\copasiui3window.cpp
# End Source File
# Begin Source File

SOURCE=.\copasiWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\DifferentialEquations.cpp
# End Source File
# Begin Source File

SOURCE=.\FixedMetaboliteSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\listviews.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\MetaboliteSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_CompartmentsWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_CompartmentsWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_CompartmentSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_ConstantSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_copasiui3window.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_DifferentialEquations.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_FixedMetaboliteSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_FunctionSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_FunctionWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_FunctionWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_listviews.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_MetabolitesWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_MetabolitesWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_MetaboliteSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_ModelWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_ModesWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_MoietyWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_MoietyWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_MyLineEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_ObjectBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_ReactionsWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_ReactionsWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_ScanWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_SteadyStateWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_TrajectoryWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\ModesWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\MoietyWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\MoietyWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\MyLineEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTable.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectBrowserItem.cpp
# End Source File
# Begin Source File

SOURCE=.\Observer.cpp
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget1.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\SteadyStateWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\StretchTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Subject.cpp
# End Source File
# Begin Source File

SOURCE=.\TrajectoryWidget.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CompartmentsWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing CompartmentsWidget.h...
InputDir=.
InputPath=.\CompartmentsWidget.h
InputName=CompartmentsWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing CompartmentsWidget.h...
InputDir=.
InputPath=.\CompartmentsWidget.h
InputName=CompartmentsWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CompartmentsWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing CompartmentsWidget1.h...
InputDir=.
InputPath=.\CompartmentsWidget1.h
InputName=CompartmentsWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing CompartmentsWidget1.h...
InputDir=.
InputPath=.\CompartmentsWidget1.h
InputName=CompartmentsWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CompartmentSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing CompartmentSymbols.h...
InputDir=.
InputPath=.\CompartmentSymbols.h
InputName=CompartmentSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing CompartmentSymbols.h...
InputDir=.
InputPath=.\CompartmentSymbols.h
InputName=CompartmentSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ConstantSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ConstantSymbols.h...
InputDir=.
InputPath=.\ConstantSymbols.h
InputName=ConstantSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ConstantSymbols.h...
InputDir=.
InputPath=.\ConstantSymbols.h
InputName=ConstantSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\copasiui3window.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing copasiui3window.h...
InputDir=.
InputPath=.\copasiui3window.h
InputName=copasiui3window

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing copasiui3window.h...
InputDir=.
InputPath=.\copasiui3window.h
InputName=copasiui3window

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\copasiWidget.h
# End Source File
# Begin Source File

SOURCE=.\DataModel.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DifferentialEquations.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing DifferentialEquations.h...
InputDir=.
InputPath=.\DifferentialEquations.h
InputName=DifferentialEquations

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing DifferentialEquations.h...
InputDir=.
InputPath=.\DifferentialEquations.h
InputName=DifferentialEquations

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FixedMetaboliteSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FixedMetaboliteSymbols.h...
InputDir=.
InputPath=.\FixedMetaboliteSymbols.h
InputName=FixedMetaboliteSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FixedMetaboliteSymbols.h...
InputDir=.
InputPath=.\FixedMetaboliteSymbols.h
InputName=FixedMetaboliteSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FunctionSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionSymbols.h...
InputDir=.
InputPath=.\FunctionSymbols.h
InputName=FunctionSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionSymbols.h...
InputDir=.
InputPath=.\FunctionSymbols.h
InputName=FunctionSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FunctionWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget.h...
InputDir=.
InputPath=.\FunctionWidget.h
InputName=FunctionWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget.h...
InputDir=.
InputPath=.\FunctionWidget.h
InputName=FunctionWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FunctionWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget1.h...
InputDir=.
InputPath=.\FunctionWidget1.h
InputName=FunctionWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing FunctionWidget1.h...
InputDir=.
InputPath=.\FunctionWidget1.h
InputName=FunctionWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\listviews.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing listviews.h...
InputDir=.
InputPath=.\listviews.h
InputName=listviews

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing listviews.h...
InputDir=.
InputPath=.\listviews.h
InputName=listviews

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MetabolitesWidget.h...
InputDir=.
InputPath=.\MetabolitesWidget.h
InputName=MetabolitesWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MetabolitesWidget.h...
InputDir=.
InputPath=.\MetabolitesWidget.h
InputName=MetabolitesWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MetabolitesWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MetabolitesWidget1.h...
InputDir=.
InputPath=.\MetabolitesWidget1.h
InputName=MetabolitesWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MetabolitesWidget1.h...
InputDir=.
InputPath=.\MetabolitesWidget1.h
InputName=MetabolitesWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MetaboliteSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MetaboliteSymbols.h...
InputDir=.
InputPath=.\MetaboliteSymbols.h
InputName=MetaboliteSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MetaboliteSymbols.h...
InputDir=.
InputPath=.\MetaboliteSymbols.h
InputName=MetaboliteSymbols

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ModelWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ModelWidget.h...
InputDir=.
InputPath=.\ModelWidget.h
InputName=ModelWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ModelWidget.h...
InputDir=.
InputPath=.\ModelWidget.h
InputName=ModelWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ModesWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ModesWidget.h...
InputDir=.
InputPath=.\ModesWidget.h
InputName=ModesWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ModesWidget.h...
InputDir=.
InputPath=.\ModesWidget.h
InputName=ModesWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoietyWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MoietyWidget.h...
InputDir=.
InputPath=.\MoietyWidget.h
InputName=MoietyWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MoietyWidget.h...
InputDir=.
InputPath=.\MoietyWidget.h
InputName=MoietyWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoietyWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MoietyWidget1.h...
InputDir=.
InputPath=.\MoietyWidget1.h
InputName=MoietyWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MoietyWidget1.h...
InputDir=.
InputPath=.\MoietyWidget1.h
InputName=MoietyWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyLineEdit.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MyLineEdit.h...
InputDir=.
InputPath=.\MyLineEdit.h
InputName=MyLineEdit

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing MyLineEdit.h...
InputDir=.
InputPath=.\MyLineEdit.h
InputName=MyLineEdit

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyTable.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ObjectBrowser.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ObjectBrowser.h...
InputDir=.
InputPath=.\ObjectBrowser.h
InputName=ObjectBrowser

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ObjectBrowser.h...
InputDir=.
InputPath=.\ObjectBrowser.h
InputName=ObjectBrowser

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObjectBrowserItem.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ObjectBrowserItem.h...
InputDir=.
InputPath=.\ObjectBrowserItem.h
InputName=ObjectBrowserItem

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Observer.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget.h...
InputDir=.
InputPath=.\ReactionsWidget.h
InputName=ReactionsWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget.h...
InputDir=.
InputPath=.\ReactionsWidget.h
InputName=ReactionsWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReactionsWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget1.h...
InputDir=.
InputPath=.\ReactionsWidget1.h
InputName=ReactionsWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ReactionsWidget1.h...
InputDir=.
InputPath=.\ReactionsWidget1.h
InputName=ReactionsWidget1

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScanWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ScanWidget.h...
InputDir=.
InputPath=.\ScanWidget.h
InputName=ScanWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ScanWidget.h...
InputDir=.
InputPath=.\ScanWidget.h
InputName=ScanWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SteadyStateWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing SteadyStateWidget.h...
InputDir=.
InputPath=.\SteadyStateWidget.h
InputName=SteadyStateWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing SteadyStateWidget.h...
InputDir=.
InputPath=.\SteadyStateWidget.h
InputName=SteadyStateWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StretchTable.h
# End Source File
# Begin Source File

SOURCE=.\Subject.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TrajectoryWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing TrajectoryWidget.h...
InputDir=.
InputPath=.\TrajectoryWidget.h
InputName=TrajectoryWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing TrajectoryWidget.h...
InputDir=.
InputPath=.\TrajectoryWidget.h
InputName=TrajectoryWidget

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tree.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
