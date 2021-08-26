cd /d %~dp0

SET WorkDir=%~dp0

SET CORECLR_PROFILER={941EC77E-F7C0-42C8-84E1-15FEFA3CE96F}
SET CORECLR_ENABLE_PROFILING=1
SET CORECLR_PROFILER_PATH=E:\source_code\ILRewriting\ILRewriting_src\Debug\ILRewriteProfiler.dll

SET COR_PROFILER={941EC77E-F7C0-42C8-84E1-15FEFA3CE96F}
SET COR_ENABLE_PROFILING=1
SET COR_PROFILER_PATH=E:\source_code\ILRewriting\ILRewriting_src\Debug\ILRewriteProfiler.dll

SET ILREWRITE_PROFILER_DEBUG=E:\source_code\ILRewriting\ILRewriting_src\Debug\ilrewrite_debug.txt
SET ILREWRITE_PROFILER_OUTPUT=E:\source_code\ILRewriting\ILRewriting_src\Debug\ilrewrite_output.txt

echo Starting Visual Studio...
set _VSWHERE="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist %_VSWHERE% (
  for /f "usebackq tokens=*" %%i in (`%_VSWHERE% -latest -prerelease -property installationPath`) do set _VSPATH=%%i
)
START "Visual Studio" "%_VSPATH%\Common7\IDE\devenv.exe" "%~dp0\WebApplication1.sln"
