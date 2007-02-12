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
del /S Makefile
del commandline\CConfigurationFile.obj
del UI\copasiui3window.obj 
del UI\CQSplashWidget.obj 
del CopasiUI\main.obj 
del CopasiSE\CopasiSE.obj

echo executing in copasi:
echo   qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9
%QTDIR%\bin\qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9

nmake qmake_all

rem force relink

cd ..

rem Build the semantic test suite wrapper
cd semantic-test-suite
echo executing in semantic-test-suite:
rem  echo   for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
echo   qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9
%QTDIR%\bin\qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9

cd ..

rem Build the stochastic test suuite wrapper
cd stochastic-testsuite
echo executing in stochastic-testsuite:
rem  echo   for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
echo   qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9
%QTDIR%\bin\qmake "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9

cd ..
