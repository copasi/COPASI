rem @echo off 

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
echo executing in copasi:
echo   for %%d in (*\.qmake.internal.cache) do del %d
for %%d in (*\.qmake.internal.cache) do del %d
echo   qmake "CONFIG+=%cps_release%" %1 %2
qmake "CONFIG+=%cps_release%" %1 %2

cd ..
