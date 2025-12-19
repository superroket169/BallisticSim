@echo off

set "ROOT=%~dp0.."

cd /d "%ROOT%"

set "PATH=%ROOT%\bin;%PATH%"

build\main.exe

pause
