@echo off
REM Set URL of your website here.
SET URL=http://finalgalaxy.github.io/vistriker-FE/

REM To know Chrome path in Windows systems, the best practice is to relay on the following registry key:
REM HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\chrome.exe
REM There is a key called 'Path'. This is the Path of the executable 'chrome.exe'.
REM Executing 'REG QUERY key /v Path' command extracts this text in my Windows 10 installation:
REM     Path    REG_SZ    C:\Program Files (x86)\Google\Chrome\Application
REM We need the third value so we skip 2 values and we set output to variable CHROMEPATH.

FOR /F "skip=2 tokens=2,*" %%A IN ('REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\chrome.exe" /v Path') DO SET CHROMEPATH=%%B

REM Now 'ECHO %CHROMEPATH%' would output chrome installation path. Nice! Let's chain command so
REM we can execute './chrome --app=URL_OF_YOUR_WEBSITE --force-app-mode --hide-scrollbars

"%CHROMEPATH%/chrome" --app=%URL% --force-app-mode --hide-scrollbars