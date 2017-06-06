@echo off

set PROJECT_ROOT=%~dp0..\..\
set DATA_DIR=%PROJECT_ROOT%customtower\customtower\data
set HEADER_OUT_PATH=%PROJECT_ROOT%customtower\customtower\code\out\data_list.h

set DATA_DIR=%DATA_DIR:\=/%
set HEADER_OUT_PATH=%HEADER_OUT_PATH:\=/%
echo %DATA_DIR%
bash -i -c "python create_data_list.py %DATA_DIR% %HEADER_OUT_PATH%"

pause