@echo off 

if '%1' == '--enable-debug'        goto DEBUG
if '%1' == '--disable-debug'       goto RELEASE
set cps_release=debug
goto QMAKE

:DEBUG
shift
set cps_release=debug
goto QMAKE

:RELEASE
shift
set cps_release=release

:QMAKE
cd copasi

set subdirs=.
set subdirs=%subdirs% commandline
set subdirs=%subdirs% elementaryFluxModes
set subdirs=%subdirs% function
set subdirs=%subdirs% mathmodel
set subdirs=%subdirs% model
set subdirs=%subdirs% optimization
set subdirs=%subdirs% output
set subdirs=%subdirs% randomGenerator
set subdirs=%subdirs% report
set subdirs=%subdirs% scan
set subdirs=%subdirs% steadystate
set subdirs=%subdirs% trajectory
set subdirs=%subdirs% utilities
set subdirs=%subdirs% xml
set subdirs=%subdirs% CopasiUI
set subdirs=%subdirs% CopasiSE
set subdirs=%subdirs% test

echo executing in copasi:
echo   for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
echo   qmake "CONFIG+=%cps_release%" %1 %2
qmake "CONFIG+=%cps_release%" %1 %2

cd ..

echo @echo off > config.status.bat
echo cd copasi >> config.status.bat
echo echo qmake "CONFIG+=%cps_release%" %1 %2 >> config.status.bat
echo qmake "CONFIG+=%cps_release%" %1 %2 >> config.status.bat
echo cd .. >> config.status.bat
