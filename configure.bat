@echo off 

cd copasi
echo %1
echo %2
if "%1" == "--enable-debug"        goto ENABLE
if "%1" == "--disable-debug"       goto DISABLE

:ENABLE
if "%2" == "false"                 goto RELEASE
if "%2" == "no"                    goto RELEASE
goto DEBUG

:DISABLE
if "%2" == "false"                 goto DEBUG
if "%2" == "no"                    goto DEBUG
goto RELEASE

:DEBUG
set cps_release="CONFIG+=debug"
goto QMAKE

:RELEASE
set cps_release="CONFIG+=release"

:QMAKE
cd copasi
echo executing in copasi:
echo   del /s .qmake.internal.cache
del /s .qmake.internal.cache
echo   qmake %cps_release% "MKL_PATH=%CBLAS_LIB%" "EXPAT_PATH=%EXPAT_LIB%"
qmake %cps_release% "MKL_PATH=%CBLAS_LIB%" "EXPAT_PATH=%EXPAT_LIB%"

cd ..
