@echo off 

echo @echo off > config.status.bat
echo echo running: configure.bat %1 %2 %3 %4 %5 %6 %7 %8 %9 >> config.status.bat
echo configure.bat %1 %2 %3 %4 %5 %6 %7 %8 %9 >> config.status.bat

if '%1' == '--enable-debug'        goto DEBUG
if '%1' == '--disable-debug'       goto RELEASE
if '%1' == '--enable-release'      goto RELEASE
if '%1' == '--disable-release'     goto DEBUG
set cps_plus=debug
set cps_minus=release
goto QMAKE

:DEBUG
shift
set cps_plus=debug
set cps_minus=release
goto QMAKE

:RELEASE
shift
set cps_plus=release
set cps_minus=debug

:QMAKE
cd copasi

rem set subdirs=.
rem set subdirs=%subdirs% commandline
rem set subdirs=%subdirs% elementaryFluxModes
rem set subdirs=%subdirs% function
rem set subdirs=%subdirs% mathmodel
rem set subdirs=%subdirs% model
rem set subdirs=%subdirs% optimization
rem set subdirs=%subdirs% output
rem set subdirs=%subdirs% randomGenerator
rem set subdirs=%subdirs% report
rem set subdirs=%subdirs% scan
rem set subdirs=%subdirs% steadystate
rem set subdirs=%subdirs% trajectory
rem set subdirs=%subdirs% utilities
rem set subdirs=%subdirs% xml
rem set subdirs=%subdirs% CopasiUI
rem set subdirs=%subdirs% CopasiSE
rem set subdirs=%subdirs% test

echo executing in copasi:
rem  echo   for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
echo   qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2
%QTDIR%\bin\qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2
nmake qmake_all
cd ..

