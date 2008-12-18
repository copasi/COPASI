@echo off
:: Script for recursively processing Qt3 .ui files.

set UiLogFile="./uicmdlog.txt"
IF EXIST %UiLogFile% DEL %UiLogFile%
IF "%QTDIR%"=="" GOTO QTDIRMESSAGE
for /r "." %%X in (*.ui) do (
echo Now processing %%X ...
echo "%QTDIR%\bin\uic3" -o "%%~dpnX.h" "%%X">> %UiLogFile%
"%QTDIR%\bin\uic3" -o "%%~dpnX.h" "%%X"
echo "%QTDIR%\bin\uic3" -o "%%~dpnX.cpp" -impl "%%~dpnX.h" "%%X">> %UiLogFile%
"%QTDIR%\bin\uic3" -o "%%~dpnX.cpp" -impl "%%~dpnX.h" "%%X"
)

GOTO END
:QTDIRMESSAGE
echo.
echo Environment variable "QTDIR" is not set.
echo.
:END