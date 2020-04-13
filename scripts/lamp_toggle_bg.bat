@echo off
@setlocal enableextensions enabledelayedexpansion

FOR /F "tokens=* USEBACKQ" %%F IN (`mousestate.exe`) DO (
SET str1=%%F
)

echo %str1% | findstr /C:"left" && (
	echo LEFT
	bash "fan_ctrl.sh" "speed"
	exit
)

echo %str1% | findstr /C:"right" && (
	echo RIGHT
	bash "fan_ctrl.sh" "off"
	exit
)

set addr=192.168.1.4
echo Pinging the lamp (%addr%)...
for /L %%i in (1,1,10) do (
	ping -w 100 -n 1 %addr% > nul
	if not errorlevel=1 goto toggle
)
echo Lamp offline

timeout 1

exit

:toggle
echo {"id":1, "method":"toggle", "params":[]}| nc -w 1 %addr% 55443
