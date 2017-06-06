@echo off

set NK_SOLUTION_DIR_TMP=%~dp0\customtower
set NK_SOLUTION_DIR=%NK_SOLUTION_DIR_TMP:\=/%

rem start %NK_SOLUTION_DIR%/nklib/include
rem start %NK_SOLUTION_DIR%/nklib/src
rem start %NK_SOLUTION_DIR%/game/code
rem start %NK_SOLUTION_DIR%/nklib.sln

rem pushd C:\cygwin\bin

bash -i -c "cygstart %NK_SOLUTION_DIR%/nklib/include"
bash -i -c "cygstart %NK_SOLUTION_DIR%/nklib/src"
bash -i -c "cygstart %NK_SOLUTION_DIR%/customtower/code"
bash -i -c "cygstart %NK_SOLUTION_DIR%/customtower/code"
bash -i -c "cygstart %NK_SOLUTION_DIR%/customtower.sln"

rem popd
