echo on
set PROGRAM=%~1

for /l %%x in (0, 1, 2) do (
   REM echo %%x
   %PROGRAM% test\in%%x.txt > %TEMP%\result.txt
   fc.exe test\out%%x.txt %TEMP%\result.txt
   if ERRORLEVEL 1 goto err 
)

echo "Program testing succcesed"
exit 0

:err
echo "Program testing failed : Incorrect result"
exit 1