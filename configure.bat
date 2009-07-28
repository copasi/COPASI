@echo off 

echo @echo off > config.status.bat

echo echo running: configure.bat %* >> config.status.bat
echo configure.bat %* >> config.status.bat

set arguments=

:LOOP
if '%1' == ''                      goto QMAKE
if '%1' == '--enable-debug'        goto DEBUG
if '%1' == '--disable-debug'       goto RELEASE
if '%1' == '--enable-release'      goto RELEASE
if '%1' == '--disable-release'     goto DEBUG

set arguments=%arguments% %1
shift
goto LOOP

:DEBUG
:RELEASE
rem debug and release is ignored
shift
goto LOOP

:QMAKE
cd copasi
del /S Makefile*
del commandline\CConfigurationFile.obj
del UI\copasiui3window.obj 
del UI\CQSplashWidget.obj 
del CopasiUI\main.obj 
del CopasiSE\CopasiSE.obj

if '%QT4DIR%' == '' goto QT4DIR_NotSet
set QMAKE=%QT4DIR%\bin\qmake
goto CONFIGURE

:QT4DIR_NotSet
if '%QTDIR%' == '' goto QTDIR_NotSet
set QMAKE=%QTDIR%\bin\qmake
goto CONFIGURE

:QTDIR_NotSet
set QMAKE=qmake

:CONFIGURE
echo executing in copasi:
echo   %QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%
%QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%

nmake qmake_all

cd libs
nmake qmake_all
cd ..

rem force relink

cd ..

rem Build the semantic test suite wrapper
cd semantic-test-suite
echo executing in semantic-test-suite:
rem  echo   for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
echo   %QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%
%QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%

cd ..

rem Build the stochastic test suite wrapper
cd stochastic-testsuite
echo executing in stochastic-testsuite:
rem  echo   for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
echo   %QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%
%QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%

cd ..

rem Build the SBML test suite wrapper
cd sbml-testsuite
echo executing in sbml-testsuite:
rem  echo   for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\.qmake.internal.cache
echo   %QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%
%QMAKE% "CONFIG-=release" "CONFIG-=debug" %arguments%

cd ..

