# Microsoft Developer Studio Generated NMAKE File, Based on CopasiUI-Static.dsp
!IF "$(CFG)" == ""
CFG=CopasiUI Static - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CopasiUI Static - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CopasiUI Static - Win32 Release" && "$(CFG)" != "CopasiUI Static - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

OUTDIR=.\..\Release-Static
INTDIR=.\..\Release-Static
# Begin Custom Macros
OutDir=.\..\Release-Static
# End Custom Macros

ALL : ".\moc_ObjectBrowserItem.cpp" "$(OUTDIR)\CopasiUI-Static.exe"


CLEAN :
	-@erase "$(INTDIR)\CompartmentsWidget.obj"
	-@erase "$(INTDIR)\CompartmentsWidget1.obj"
	-@erase "$(INTDIR)\CompartmentSymbols.obj"
	-@erase "$(INTDIR)\ConstantSymbols.obj"
	-@erase "$(INTDIR)\copasiui3window.obj"
	-@erase "$(INTDIR)\copasiWidget.obj"
	-@erase "$(INTDIR)\DifferentialEquations.obj"
	-@erase "$(INTDIR)\FixedMetaboliteSymbols.obj"
	-@erase "$(INTDIR)\FunctionSymbols.obj"
	-@erase "$(INTDIR)\FunctionWidget.obj"
	-@erase "$(INTDIR)\FunctionWidget1.obj"
	-@erase "$(INTDIR)\listviews.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\MetabolitesWidget.obj"
	-@erase "$(INTDIR)\MetabolitesWidget1.obj"
	-@erase "$(INTDIR)\MetaboliteSymbols.obj"
	-@erase "$(INTDIR)\moc_CompartmentsWidget.obj"
	-@erase "$(INTDIR)\moc_CompartmentsWidget1.obj"
	-@erase "$(INTDIR)\moc_CompartmentSymbols.obj"
	-@erase "$(INTDIR)\moc_ConstantSymbols.obj"
	-@erase "$(INTDIR)\moc_copasiui3window.obj"
	-@erase "$(INTDIR)\moc_DifferentialEquations.obj"
	-@erase "$(INTDIR)\moc_FixedMetaboliteSymbols.obj"
	-@erase "$(INTDIR)\moc_FunctionSymbols.obj"
	-@erase "$(INTDIR)\moc_FunctionWidget.obj"
	-@erase "$(INTDIR)\moc_FunctionWidget1.obj"
	-@erase "$(INTDIR)\moc_listviews.obj"
	-@erase "$(INTDIR)\moc_MetabolitesWidget.obj"
	-@erase "$(INTDIR)\moc_MetabolitesWidget1.obj"
	-@erase "$(INTDIR)\moc_MetaboliteSymbols.obj"
	-@erase "$(INTDIR)\moc_ModelWidget.obj"
	-@erase "$(INTDIR)\moc_ModesWidget.obj"
	-@erase "$(INTDIR)\moc_MoietyWidget.obj"
	-@erase "$(INTDIR)\moc_MoietyWidget1.obj"
	-@erase "$(INTDIR)\moc_MyLineEdit.obj"
	-@erase "$(INTDIR)\moc_ObjectBrowser.obj"
	-@erase "$(INTDIR)\moc_ReactionsWidget.obj"
	-@erase "$(INTDIR)\moc_ReactionsWidget1.obj"
	-@erase "$(INTDIR)\moc_ScanWidget.obj"
	-@erase "$(INTDIR)\moc_SteadyStateWidget.obj"
	-@erase "$(INTDIR)\moc_TrajectoryWidget.obj"
	-@erase "$(INTDIR)\ModelWidget.obj"
	-@erase "$(INTDIR)\ModesWidget.obj"
	-@erase "$(INTDIR)\MoietyWidget.obj"
	-@erase "$(INTDIR)\MoietyWidget1.obj"
	-@erase "$(INTDIR)\MyLineEdit.obj"
	-@erase "$(INTDIR)\MyTable.obj"
	-@erase "$(INTDIR)\ObjectBrowser.obj"
	-@erase "$(INTDIR)\ObjectBrowserItem.obj"
	-@erase "$(INTDIR)\Observer.obj"
	-@erase "$(INTDIR)\ReactionsWidget.obj"
	-@erase "$(INTDIR)\ReactionsWidget1.obj"
	-@erase "$(INTDIR)\ScanWidget.obj"
	-@erase "$(INTDIR)\SteadyStateWidget.obj"
	-@erase "$(INTDIR)\StretchTable.obj"
	-@erase "$(INTDIR)\Subject.obj"
	-@erase "$(INTDIR)\TrajectoryWidget.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CopasiUI-Static.exe"
	-@erase ".\moc_ObjectBrowserItem.cpp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "$(QTDIR)\include" /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_NODLL" /D "QT_THREAD_SUPPORT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CopasiUI-Static.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(QTDIR)\lib\qt-mt302.lib mkl_lapack.lib mkl_p3.lib mkl_c.lib scan.lib randomGenerator.lib utilities.lib function.lib mathmodel.lib model.lib output.lib trajectory.lib winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qtmain.lib $(QTDIR)\lib\qt-mt.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CopasiUI-Static.pdb" /machine:I386 /nodefaultlib:"msvcrtd.lib" /out:"$(OUTDIR)\CopasiUI-Static.exe" /libpath:"../Release" /libpath:"$(CBLAS_LIB)/ia32/lib" 
LINK32_OBJS= \
	"$(INTDIR)\CompartmentsWidget.obj" \
	"$(INTDIR)\CompartmentsWidget1.obj" \
	"$(INTDIR)\CompartmentSymbols.obj" \
	"$(INTDIR)\ConstantSymbols.obj" \
	"$(INTDIR)\copasiui3window.obj" \
	"$(INTDIR)\copasiWidget.obj" \
	"$(INTDIR)\DifferentialEquations.obj" \
	"$(INTDIR)\FixedMetaboliteSymbols.obj" \
	"$(INTDIR)\FunctionSymbols.obj" \
	"$(INTDIR)\FunctionWidget.obj" \
	"$(INTDIR)\FunctionWidget1.obj" \
	"$(INTDIR)\listviews.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MetabolitesWidget.obj" \
	"$(INTDIR)\MetabolitesWidget1.obj" \
	"$(INTDIR)\MetaboliteSymbols.obj" \
	"$(INTDIR)\moc_CompartmentsWidget.obj" \
	"$(INTDIR)\moc_CompartmentsWidget1.obj" \
	"$(INTDIR)\moc_CompartmentSymbols.obj" \
	"$(INTDIR)\moc_ConstantSymbols.obj" \
	"$(INTDIR)\moc_copasiui3window.obj" \
	"$(INTDIR)\moc_DifferentialEquations.obj" \
	"$(INTDIR)\moc_FixedMetaboliteSymbols.obj" \
	"$(INTDIR)\moc_FunctionSymbols.obj" \
	"$(INTDIR)\moc_FunctionWidget.obj" \
	"$(INTDIR)\moc_FunctionWidget1.obj" \
	"$(INTDIR)\moc_listviews.obj" \
	"$(INTDIR)\moc_MetabolitesWidget.obj" \
	"$(INTDIR)\moc_MetabolitesWidget1.obj" \
	"$(INTDIR)\moc_MetaboliteSymbols.obj" \
	"$(INTDIR)\moc_ModelWidget.obj" \
	"$(INTDIR)\moc_ModesWidget.obj" \
	"$(INTDIR)\moc_MoietyWidget.obj" \
	"$(INTDIR)\moc_MoietyWidget1.obj" \
	"$(INTDIR)\moc_MyLineEdit.obj" \
	"$(INTDIR)\moc_ObjectBrowser.obj" \
	"$(INTDIR)\moc_ReactionsWidget.obj" \
	"$(INTDIR)\moc_ReactionsWidget1.obj" \
	"$(INTDIR)\moc_ScanWidget.obj" \
	"$(INTDIR)\moc_SteadyStateWidget.obj" \
	"$(INTDIR)\moc_TrajectoryWidget.obj" \
	"$(INTDIR)\ModelWidget.obj" \
	"$(INTDIR)\ModesWidget.obj" \
	"$(INTDIR)\MoietyWidget.obj" \
	"$(INTDIR)\MoietyWidget1.obj" \
	"$(INTDIR)\MyLineEdit.obj" \
	"$(INTDIR)\MyTable.obj" \
	"$(INTDIR)\ObjectBrowser.obj" \
	"$(INTDIR)\ObjectBrowserItem.obj" \
	"$(INTDIR)\Observer.obj" \
	"$(INTDIR)\ReactionsWidget.obj" \
	"$(INTDIR)\ReactionsWidget1.obj" \
	"$(INTDIR)\ScanWidget.obj" \
	"$(INTDIR)\SteadyStateWidget.obj" \
	"$(INTDIR)\StretchTable.obj" \
	"$(INTDIR)\Subject.obj" \
	"$(INTDIR)\TrajectoryWidget.obj"

"$(OUTDIR)\CopasiUI-Static.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

OUTDIR=.\..\Debug-Static
INTDIR=.\..\Debug-Static
# Begin Custom Macros
OutDir=.\..\Debug-Static
# End Custom Macros

ALL : "$(OUTDIR)\CopasiUI-Static.exe" "$(OUTDIR)\CopasiUI-Static.bsc"


CLEAN :
	-@erase "$(INTDIR)\CompartmentsWidget.obj"
	-@erase "$(INTDIR)\CompartmentsWidget.sbr"
	-@erase "$(INTDIR)\CompartmentsWidget1.obj"
	-@erase "$(INTDIR)\CompartmentsWidget1.sbr"
	-@erase "$(INTDIR)\CompartmentSymbols.obj"
	-@erase "$(INTDIR)\CompartmentSymbols.sbr"
	-@erase "$(INTDIR)\ConstantSymbols.obj"
	-@erase "$(INTDIR)\ConstantSymbols.sbr"
	-@erase "$(INTDIR)\copasiui3window.obj"
	-@erase "$(INTDIR)\copasiui3window.sbr"
	-@erase "$(INTDIR)\copasiWidget.obj"
	-@erase "$(INTDIR)\copasiWidget.sbr"
	-@erase "$(INTDIR)\DifferentialEquations.obj"
	-@erase "$(INTDIR)\DifferentialEquations.sbr"
	-@erase "$(INTDIR)\FixedMetaboliteSymbols.obj"
	-@erase "$(INTDIR)\FixedMetaboliteSymbols.sbr"
	-@erase "$(INTDIR)\FunctionSymbols.obj"
	-@erase "$(INTDIR)\FunctionSymbols.sbr"
	-@erase "$(INTDIR)\FunctionWidget.obj"
	-@erase "$(INTDIR)\FunctionWidget.sbr"
	-@erase "$(INTDIR)\FunctionWidget1.obj"
	-@erase "$(INTDIR)\FunctionWidget1.sbr"
	-@erase "$(INTDIR)\listviews.obj"
	-@erase "$(INTDIR)\listviews.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MetabolitesWidget.obj"
	-@erase "$(INTDIR)\MetabolitesWidget.sbr"
	-@erase "$(INTDIR)\MetabolitesWidget1.obj"
	-@erase "$(INTDIR)\MetabolitesWidget1.sbr"
	-@erase "$(INTDIR)\MetaboliteSymbols.obj"
	-@erase "$(INTDIR)\MetaboliteSymbols.sbr"
	-@erase "$(INTDIR)\moc_CompartmentsWidget.obj"
	-@erase "$(INTDIR)\moc_CompartmentsWidget.sbr"
	-@erase "$(INTDIR)\moc_CompartmentsWidget1.obj"
	-@erase "$(INTDIR)\moc_CompartmentsWidget1.sbr"
	-@erase "$(INTDIR)\moc_CompartmentSymbols.obj"
	-@erase "$(INTDIR)\moc_CompartmentSymbols.sbr"
	-@erase "$(INTDIR)\moc_ConstantSymbols.obj"
	-@erase "$(INTDIR)\moc_ConstantSymbols.sbr"
	-@erase "$(INTDIR)\moc_copasiui3window.obj"
	-@erase "$(INTDIR)\moc_copasiui3window.sbr"
	-@erase "$(INTDIR)\moc_DifferentialEquations.obj"
	-@erase "$(INTDIR)\moc_DifferentialEquations.sbr"
	-@erase "$(INTDIR)\moc_FixedMetaboliteSymbols.obj"
	-@erase "$(INTDIR)\moc_FixedMetaboliteSymbols.sbr"
	-@erase "$(INTDIR)\moc_FunctionSymbols.obj"
	-@erase "$(INTDIR)\moc_FunctionSymbols.sbr"
	-@erase "$(INTDIR)\moc_FunctionWidget.obj"
	-@erase "$(INTDIR)\moc_FunctionWidget.sbr"
	-@erase "$(INTDIR)\moc_FunctionWidget1.obj"
	-@erase "$(INTDIR)\moc_FunctionWidget1.sbr"
	-@erase "$(INTDIR)\moc_listviews.obj"
	-@erase "$(INTDIR)\moc_listviews.sbr"
	-@erase "$(INTDIR)\moc_MetabolitesWidget.obj"
	-@erase "$(INTDIR)\moc_MetabolitesWidget.sbr"
	-@erase "$(INTDIR)\moc_MetabolitesWidget1.obj"
	-@erase "$(INTDIR)\moc_MetabolitesWidget1.sbr"
	-@erase "$(INTDIR)\moc_MetaboliteSymbols.obj"
	-@erase "$(INTDIR)\moc_MetaboliteSymbols.sbr"
	-@erase "$(INTDIR)\moc_ModelWidget.obj"
	-@erase "$(INTDIR)\moc_ModelWidget.sbr"
	-@erase "$(INTDIR)\moc_ModesWidget.obj"
	-@erase "$(INTDIR)\moc_ModesWidget.sbr"
	-@erase "$(INTDIR)\moc_MoietyWidget.obj"
	-@erase "$(INTDIR)\moc_MoietyWidget.sbr"
	-@erase "$(INTDIR)\moc_MoietyWidget1.obj"
	-@erase "$(INTDIR)\moc_MoietyWidget1.sbr"
	-@erase "$(INTDIR)\moc_MyLineEdit.obj"
	-@erase "$(INTDIR)\moc_MyLineEdit.sbr"
	-@erase "$(INTDIR)\moc_ObjectBrowser.obj"
	-@erase "$(INTDIR)\moc_ObjectBrowser.sbr"
	-@erase "$(INTDIR)\moc_ReactionsWidget.obj"
	-@erase "$(INTDIR)\moc_ReactionsWidget.sbr"
	-@erase "$(INTDIR)\moc_ReactionsWidget1.obj"
	-@erase "$(INTDIR)\moc_ReactionsWidget1.sbr"
	-@erase "$(INTDIR)\moc_ScanWidget.obj"
	-@erase "$(INTDIR)\moc_ScanWidget.sbr"
	-@erase "$(INTDIR)\moc_SteadyStateWidget.obj"
	-@erase "$(INTDIR)\moc_SteadyStateWidget.sbr"
	-@erase "$(INTDIR)\moc_TrajectoryWidget.obj"
	-@erase "$(INTDIR)\moc_TrajectoryWidget.sbr"
	-@erase "$(INTDIR)\ModelWidget.obj"
	-@erase "$(INTDIR)\ModelWidget.sbr"
	-@erase "$(INTDIR)\ModesWidget.obj"
	-@erase "$(INTDIR)\ModesWidget.sbr"
	-@erase "$(INTDIR)\MoietyWidget.obj"
	-@erase "$(INTDIR)\MoietyWidget.sbr"
	-@erase "$(INTDIR)\MoietyWidget1.obj"
	-@erase "$(INTDIR)\MoietyWidget1.sbr"
	-@erase "$(INTDIR)\MyLineEdit.obj"
	-@erase "$(INTDIR)\MyLineEdit.sbr"
	-@erase "$(INTDIR)\MyTable.obj"
	-@erase "$(INTDIR)\MyTable.sbr"
	-@erase "$(INTDIR)\ObjectBrowser.obj"
	-@erase "$(INTDIR)\ObjectBrowser.sbr"
	-@erase "$(INTDIR)\ObjectBrowserItem.obj"
	-@erase "$(INTDIR)\ObjectBrowserItem.sbr"
	-@erase "$(INTDIR)\Observer.obj"
	-@erase "$(INTDIR)\Observer.sbr"
	-@erase "$(INTDIR)\ReactionsWidget.obj"
	-@erase "$(INTDIR)\ReactionsWidget.sbr"
	-@erase "$(INTDIR)\ReactionsWidget1.obj"
	-@erase "$(INTDIR)\ReactionsWidget1.sbr"
	-@erase "$(INTDIR)\ScanWidget.obj"
	-@erase "$(INTDIR)\ScanWidget.sbr"
	-@erase "$(INTDIR)\SteadyStateWidget.obj"
	-@erase "$(INTDIR)\SteadyStateWidget.sbr"
	-@erase "$(INTDIR)\StretchTable.obj"
	-@erase "$(INTDIR)\StretchTable.sbr"
	-@erase "$(INTDIR)\Subject.obj"
	-@erase "$(INTDIR)\Subject.sbr"
	-@erase "$(INTDIR)\TrajectoryWidget.obj"
	-@erase "$(INTDIR)\TrajectoryWidget.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CopasiUI-Static.bsc"
	-@erase "$(OUTDIR)\CopasiUI-Static.exe"
	-@erase "$(OUTDIR)\CopasiUI-Static.ilk"
	-@erase "$(OUTDIR)\CopasiUI-Static.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QT_NODLL" /D "QT_THREAD_SUPPORT" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CopasiUI-Static.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CompartmentsWidget.sbr" \
	"$(INTDIR)\CompartmentsWidget1.sbr" \
	"$(INTDIR)\CompartmentSymbols.sbr" \
	"$(INTDIR)\ConstantSymbols.sbr" \
	"$(INTDIR)\copasiui3window.sbr" \
	"$(INTDIR)\copasiWidget.sbr" \
	"$(INTDIR)\DifferentialEquations.sbr" \
	"$(INTDIR)\FixedMetaboliteSymbols.sbr" \
	"$(INTDIR)\FunctionSymbols.sbr" \
	"$(INTDIR)\FunctionWidget.sbr" \
	"$(INTDIR)\FunctionWidget1.sbr" \
	"$(INTDIR)\listviews.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\MetabolitesWidget.sbr" \
	"$(INTDIR)\MetabolitesWidget1.sbr" \
	"$(INTDIR)\MetaboliteSymbols.sbr" \
	"$(INTDIR)\moc_CompartmentsWidget.sbr" \
	"$(INTDIR)\moc_CompartmentsWidget1.sbr" \
	"$(INTDIR)\moc_CompartmentSymbols.sbr" \
	"$(INTDIR)\moc_ConstantSymbols.sbr" \
	"$(INTDIR)\moc_copasiui3window.sbr" \
	"$(INTDIR)\moc_DifferentialEquations.sbr" \
	"$(INTDIR)\moc_FixedMetaboliteSymbols.sbr" \
	"$(INTDIR)\moc_FunctionSymbols.sbr" \
	"$(INTDIR)\moc_FunctionWidget.sbr" \
	"$(INTDIR)\moc_FunctionWidget1.sbr" \
	"$(INTDIR)\moc_listviews.sbr" \
	"$(INTDIR)\moc_MetabolitesWidget.sbr" \
	"$(INTDIR)\moc_MetabolitesWidget1.sbr" \
	"$(INTDIR)\moc_MetaboliteSymbols.sbr" \
	"$(INTDIR)\moc_ModelWidget.sbr" \
	"$(INTDIR)\moc_ModesWidget.sbr" \
	"$(INTDIR)\moc_MoietyWidget.sbr" \
	"$(INTDIR)\moc_MoietyWidget1.sbr" \
	"$(INTDIR)\moc_MyLineEdit.sbr" \
	"$(INTDIR)\moc_ObjectBrowser.sbr" \
	"$(INTDIR)\moc_ReactionsWidget.sbr" \
	"$(INTDIR)\moc_ReactionsWidget1.sbr" \
	"$(INTDIR)\moc_ScanWidget.sbr" \
	"$(INTDIR)\moc_SteadyStateWidget.sbr" \
	"$(INTDIR)\moc_TrajectoryWidget.sbr" \
	"$(INTDIR)\ModelWidget.sbr" \
	"$(INTDIR)\ModesWidget.sbr" \
	"$(INTDIR)\MoietyWidget.sbr" \
	"$(INTDIR)\MoietyWidget1.sbr" \
	"$(INTDIR)\MyLineEdit.sbr" \
	"$(INTDIR)\MyTable.sbr" \
	"$(INTDIR)\ObjectBrowser.sbr" \
	"$(INTDIR)\ObjectBrowserItem.sbr" \
	"$(INTDIR)\Observer.sbr" \
	"$(INTDIR)\ReactionsWidget.sbr" \
	"$(INTDIR)\ReactionsWidget1.sbr" \
	"$(INTDIR)\ScanWidget.sbr" \
	"$(INTDIR)\SteadyStateWidget.sbr" \
	"$(INTDIR)\StretchTable.sbr" \
	"$(INTDIR)\Subject.sbr" \
	"$(INTDIR)\TrajectoryWidget.sbr"

"$(OUTDIR)\CopasiUI-Static.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=steadystate.lib report.lib clapack.lib $(QTDIR)\lib\qt-mt.lib scan.lib randomGenerator.lib utilities.lib function.lib mathmodel.lib model.lib output.lib trajectory.lib winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CopasiUI-Static.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"$(OUTDIR)\CopasiUI-Static.exe" /pdbtype:sept /libpath:"../Debug" /libpath:"$(CBLAS_LIB)/ia32/lib" 
LINK32_OBJS= \
	"$(INTDIR)\CompartmentsWidget.obj" \
	"$(INTDIR)\CompartmentsWidget1.obj" \
	"$(INTDIR)\CompartmentSymbols.obj" \
	"$(INTDIR)\ConstantSymbols.obj" \
	"$(INTDIR)\copasiui3window.obj" \
	"$(INTDIR)\copasiWidget.obj" \
	"$(INTDIR)\DifferentialEquations.obj" \
	"$(INTDIR)\FixedMetaboliteSymbols.obj" \
	"$(INTDIR)\FunctionSymbols.obj" \
	"$(INTDIR)\FunctionWidget.obj" \
	"$(INTDIR)\FunctionWidget1.obj" \
	"$(INTDIR)\listviews.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MetabolitesWidget.obj" \
	"$(INTDIR)\MetabolitesWidget1.obj" \
	"$(INTDIR)\MetaboliteSymbols.obj" \
	"$(INTDIR)\moc_CompartmentsWidget.obj" \
	"$(INTDIR)\moc_CompartmentsWidget1.obj" \
	"$(INTDIR)\moc_CompartmentSymbols.obj" \
	"$(INTDIR)\moc_ConstantSymbols.obj" \
	"$(INTDIR)\moc_copasiui3window.obj" \
	"$(INTDIR)\moc_DifferentialEquations.obj" \
	"$(INTDIR)\moc_FixedMetaboliteSymbols.obj" \
	"$(INTDIR)\moc_FunctionSymbols.obj" \
	"$(INTDIR)\moc_FunctionWidget.obj" \
	"$(INTDIR)\moc_FunctionWidget1.obj" \
	"$(INTDIR)\moc_listviews.obj" \
	"$(INTDIR)\moc_MetabolitesWidget.obj" \
	"$(INTDIR)\moc_MetabolitesWidget1.obj" \
	"$(INTDIR)\moc_MetaboliteSymbols.obj" \
	"$(INTDIR)\moc_ModelWidget.obj" \
	"$(INTDIR)\moc_ModesWidget.obj" \
	"$(INTDIR)\moc_MoietyWidget.obj" \
	"$(INTDIR)\moc_MoietyWidget1.obj" \
	"$(INTDIR)\moc_MyLineEdit.obj" \
	"$(INTDIR)\moc_ObjectBrowser.obj" \
	"$(INTDIR)\moc_ReactionsWidget.obj" \
	"$(INTDIR)\moc_ReactionsWidget1.obj" \
	"$(INTDIR)\moc_ScanWidget.obj" \
	"$(INTDIR)\moc_SteadyStateWidget.obj" \
	"$(INTDIR)\moc_TrajectoryWidget.obj" \
	"$(INTDIR)\ModelWidget.obj" \
	"$(INTDIR)\ModesWidget.obj" \
	"$(INTDIR)\MoietyWidget.obj" \
	"$(INTDIR)\MoietyWidget1.obj" \
	"$(INTDIR)\MyLineEdit.obj" \
	"$(INTDIR)\MyTable.obj" \
	"$(INTDIR)\ObjectBrowser.obj" \
	"$(INTDIR)\ObjectBrowserItem.obj" \
	"$(INTDIR)\Observer.obj" \
	"$(INTDIR)\ReactionsWidget.obj" \
	"$(INTDIR)\ReactionsWidget1.obj" \
	"$(INTDIR)\ScanWidget.obj" \
	"$(INTDIR)\SteadyStateWidget.obj" \
	"$(INTDIR)\StretchTable.obj" \
	"$(INTDIR)\Subject.obj" \
	"$(INTDIR)\TrajectoryWidget.obj"

"$(OUTDIR)\CopasiUI-Static.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CopasiUI-Static.dep")
!INCLUDE "CopasiUI-Static.dep"
!ELSE 
!MESSAGE Warning: cannot find "CopasiUI-Static.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CopasiUI Static - Win32 Release" || "$(CFG)" == "CopasiUI Static - Win32 Debug"
SOURCE=.\CompartmentsWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\CompartmentsWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\CompartmentsWidget.obj"	"$(INTDIR)\CompartmentsWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CompartmentsWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\CompartmentsWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\CompartmentsWidget1.obj"	"$(INTDIR)\CompartmentsWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CompartmentSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\CompartmentSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\CompartmentSymbols.obj"	"$(INTDIR)\CompartmentSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ConstantSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ConstantSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ConstantSymbols.obj"	"$(INTDIR)\ConstantSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\copasiui3window.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\copasiui3window.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\copasiui3window.obj"	"$(INTDIR)\copasiui3window.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\copasiWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\copasiWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\copasiWidget.obj"	"$(INTDIR)\copasiWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DifferentialEquations.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\DifferentialEquations.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\DifferentialEquations.obj"	"$(INTDIR)\DifferentialEquations.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FixedMetaboliteSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\FixedMetaboliteSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\FixedMetaboliteSymbols.obj"	"$(INTDIR)\FixedMetaboliteSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FunctionSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\FunctionSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\FunctionSymbols.obj"	"$(INTDIR)\FunctionSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FunctionWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\FunctionWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\FunctionWidget.obj"	"$(INTDIR)\FunctionWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FunctionWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\FunctionWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\FunctionWidget1.obj"	"$(INTDIR)\FunctionWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\listviews.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\listviews.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\listviews.obj"	"$(INTDIR)\listviews.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MetabolitesWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\MetabolitesWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\MetabolitesWidget.obj"	"$(INTDIR)\MetabolitesWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MetabolitesWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\MetabolitesWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\MetabolitesWidget1.obj"	"$(INTDIR)\MetabolitesWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MetaboliteSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\MetaboliteSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\MetaboliteSymbols.obj"	"$(INTDIR)\MetaboliteSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_CompartmentsWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_CompartmentsWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_CompartmentsWidget.obj"	"$(INTDIR)\moc_CompartmentsWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_CompartmentsWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_CompartmentsWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_CompartmentsWidget1.obj"	"$(INTDIR)\moc_CompartmentsWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_CompartmentSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_CompartmentSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_CompartmentSymbols.obj"	"$(INTDIR)\moc_CompartmentSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_ConstantSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_ConstantSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_ConstantSymbols.obj"	"$(INTDIR)\moc_ConstantSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_copasiui3window.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_copasiui3window.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_copasiui3window.obj"	"$(INTDIR)\moc_copasiui3window.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_DifferentialEquations.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_DifferentialEquations.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_DifferentialEquations.obj"	"$(INTDIR)\moc_DifferentialEquations.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_FixedMetaboliteSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_FixedMetaboliteSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_FixedMetaboliteSymbols.obj"	"$(INTDIR)\moc_FixedMetaboliteSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_FunctionSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_FunctionSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_FunctionSymbols.obj"	"$(INTDIR)\moc_FunctionSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_FunctionWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_FunctionWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_FunctionWidget.obj"	"$(INTDIR)\moc_FunctionWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_FunctionWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_FunctionWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_FunctionWidget1.obj"	"$(INTDIR)\moc_FunctionWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_listviews.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_listviews.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_listviews.obj"	"$(INTDIR)\moc_listviews.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_MetabolitesWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_MetabolitesWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_MetabolitesWidget.obj"	"$(INTDIR)\moc_MetabolitesWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_MetabolitesWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_MetabolitesWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_MetabolitesWidget1.obj"	"$(INTDIR)\moc_MetabolitesWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_MetaboliteSymbols.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_MetaboliteSymbols.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_MetaboliteSymbols.obj"	"$(INTDIR)\moc_MetaboliteSymbols.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_ModelWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_ModelWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_ModelWidget.obj"	"$(INTDIR)\moc_ModelWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_ModesWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_ModesWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_ModesWidget.obj"	"$(INTDIR)\moc_ModesWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_MoietyWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_MoietyWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_MoietyWidget.obj"	"$(INTDIR)\moc_MoietyWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_MoietyWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_MoietyWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_MoietyWidget1.obj"	"$(INTDIR)\moc_MoietyWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_MyLineEdit.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_MyLineEdit.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_MyLineEdit.obj"	"$(INTDIR)\moc_MyLineEdit.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_ObjectBrowser.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_ObjectBrowser.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_ObjectBrowser.obj"	"$(INTDIR)\moc_ObjectBrowser.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_ReactionsWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_ReactionsWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_ReactionsWidget.obj"	"$(INTDIR)\moc_ReactionsWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_ReactionsWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_ReactionsWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_ReactionsWidget1.obj"	"$(INTDIR)\moc_ReactionsWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_ScanWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_ScanWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_ScanWidget.obj"	"$(INTDIR)\moc_ScanWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_SteadyStateWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_SteadyStateWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_SteadyStateWidget.obj"	"$(INTDIR)\moc_SteadyStateWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\moc_TrajectoryWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\moc_TrajectoryWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\moc_TrajectoryWidget.obj"	"$(INTDIR)\moc_TrajectoryWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ModelWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ModelWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ModelWidget.obj"	"$(INTDIR)\ModelWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ModesWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ModesWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ModesWidget.obj"	"$(INTDIR)\ModesWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MoietyWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\MoietyWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\MoietyWidget.obj"	"$(INTDIR)\MoietyWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MoietyWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\MoietyWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\MoietyWidget1.obj"	"$(INTDIR)\MoietyWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MyLineEdit.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\MyLineEdit.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\MyLineEdit.obj"	"$(INTDIR)\MyLineEdit.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MyTable.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\MyTable.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\MyTable.obj"	"$(INTDIR)\MyTable.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ObjectBrowser.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ObjectBrowser.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ObjectBrowser.obj"	"$(INTDIR)\ObjectBrowser.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ObjectBrowserItem.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ObjectBrowserItem.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ObjectBrowserItem.obj"	"$(INTDIR)\ObjectBrowserItem.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Observer.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\Observer.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\Observer.obj"	"$(INTDIR)\Observer.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ReactionsWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ReactionsWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ReactionsWidget.obj"	"$(INTDIR)\ReactionsWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ReactionsWidget1.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ReactionsWidget1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ReactionsWidget1.obj"	"$(INTDIR)\ReactionsWidget1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ScanWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\ScanWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\ScanWidget.obj"	"$(INTDIR)\ScanWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SteadyStateWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\SteadyStateWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\SteadyStateWidget.obj"	"$(INTDIR)\SteadyStateWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StretchTable.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\StretchTable.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\StretchTable.obj"	"$(INTDIR)\StretchTable.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Subject.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\Subject.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\Subject.obj"	"$(INTDIR)\Subject.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TrajectoryWidget.cpp

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"


"$(INTDIR)\TrajectoryWidget.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"


"$(INTDIR)\TrajectoryWidget.obj"	"$(INTDIR)\TrajectoryWidget.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CompartmentsWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\CompartmentsWidget.h
InputName=CompartmentsWidget

".\moc_CompartmentsWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\CompartmentsWidget.h
InputName=CompartmentsWidget

".\moc_CompartmentsWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\CompartmentsWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\CompartmentsWidget1.h
InputName=CompartmentsWidget1

".\moc_CompartmentsWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\CompartmentsWidget1.h
InputName=CompartmentsWidget1

".\moc_CompartmentsWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\CompartmentSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\CompartmentSymbols.h
InputName=CompartmentSymbols

".\moc_CompartmentSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\CompartmentSymbols.h
InputName=CompartmentSymbols

".\moc_CompartmentSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\ConstantSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ConstantSymbols.h
InputName=ConstantSymbols

".\moc_ConstantSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\ConstantSymbols.h
InputName=ConstantSymbols

".\moc_ConstantSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\copasiui3window.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\copasiui3window.h
InputName=copasiui3window

".\moc_copasiui3window.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\copasiui3window.h
InputName=copasiui3window

".\moc_copasiui3window.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\DifferentialEquations.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\DifferentialEquations.h
InputName=DifferentialEquations

".\moc_DifferentialEquations.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\DifferentialEquations.h
InputName=DifferentialEquations

".\moc_DifferentialEquations.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\FixedMetaboliteSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\FixedMetaboliteSymbols.h
InputName=FixedMetaboliteSymbols

".\moc_FixedMetaboliteSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\FixedMetaboliteSymbols.h
InputName=FixedMetaboliteSymbols

".\moc_FixedMetaboliteSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\FunctionSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\FunctionSymbols.h
InputName=FunctionSymbols

".\moc_FunctionSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\FunctionSymbols.h
InputName=FunctionSymbols

".\moc_FunctionSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\FunctionWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\FunctionWidget.h
InputName=FunctionWidget

".\moc_FunctionWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\FunctionWidget.h
InputName=FunctionWidget

".\moc_FunctionWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\FunctionWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\FunctionWidget1.h
InputName=FunctionWidget1

".\moc_FunctionWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\FunctionWidget1.h
InputName=FunctionWidget1

".\moc_FunctionWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\listviews.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\listviews.h
InputName=listviews

".\moc_listviews.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\listviews.h
InputName=listviews

".\moc_listviews.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\MetabolitesWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\MetabolitesWidget.h
InputName=MetabolitesWidget

".\moc_MetabolitesWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\MetabolitesWidget.h
InputName=MetabolitesWidget

".\moc_MetabolitesWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\MetabolitesWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\MetabolitesWidget1.h
InputName=MetabolitesWidget1

".\moc_MetabolitesWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\MetabolitesWidget1.h
InputName=MetabolitesWidget1

".\moc_MetabolitesWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\MetaboliteSymbols.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\MetaboliteSymbols.h
InputName=MetaboliteSymbols

".\moc_MetaboliteSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\MetaboliteSymbols.h
InputName=MetaboliteSymbols

".\moc_MetaboliteSymbols.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\ModelWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ModelWidget.h
InputName=ModelWidget

".\moc_ModelWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\ModelWidget.h
InputName=ModelWidget

".\moc_ModelWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\ModesWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ModesWidget.h
InputName=ModesWidget

".\moc_ModesWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\ModesWidget.h
InputName=ModesWidget

".\moc_ModesWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\MoietyWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\MoietyWidget.h
InputName=MoietyWidget

".\moc_MoietyWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\MoietyWidget.h
InputName=MoietyWidget

".\moc_MoietyWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\MoietyWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\MoietyWidget1.h
InputName=MoietyWidget1

".\moc_MoietyWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\MoietyWidget1.h
InputName=MoietyWidget1

".\moc_MoietyWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\MyLineEdit.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\MyLineEdit.h
InputName=MyLineEdit

".\moc_MyLineEdit.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\MyLineEdit.h
InputName=MyLineEdit

".\moc_MyLineEdit.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\ObjectBrowser.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ObjectBrowser.h
InputName=ObjectBrowser

".\moc_ObjectBrowser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\ObjectBrowser.h
InputName=ObjectBrowser

".\moc_ObjectBrowser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\ObjectBrowserItem.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ObjectBrowserItem.h
InputName=ObjectBrowserItem

".\moc_ObjectBrowserItem.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

!ENDIF 

SOURCE=.\ReactionsWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ReactionsWidget.h
InputName=ReactionsWidget

".\moc_ReactionsWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\ReactionsWidget.h
InputName=ReactionsWidget

".\moc_ReactionsWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\ReactionsWidget1.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ReactionsWidget1.h
InputName=ReactionsWidget1

".\moc_ReactionsWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\ReactionsWidget1.h
InputName=ReactionsWidget1

".\moc_ReactionsWidget1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\ScanWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\ScanWidget.h
InputName=ScanWidget

".\moc_ScanWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\ScanWidget.h
InputName=ScanWidget

".\moc_ScanWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\SteadyStateWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\SteadyStateWidget.h
InputName=SteadyStateWidget

".\moc_SteadyStateWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\SteadyStateWidget.h
InputName=SteadyStateWidget

".\moc_SteadyStateWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 

SOURCE=.\TrajectoryWidget.h

!IF  "$(CFG)" == "CopasiUI Static - Win32 Release"

InputDir=.
InputPath=.\TrajectoryWidget.h
InputName=TrajectoryWidget

".\moc_TrajectoryWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ELSEIF  "$(CFG)" == "CopasiUI Static - Win32 Debug"

InputDir=.
InputPath=.\TrajectoryWidget.h
InputName=TrajectoryWidget

".\moc_TrajectoryWidget.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp
<< 
	

!ENDIF 


!ENDIF 

