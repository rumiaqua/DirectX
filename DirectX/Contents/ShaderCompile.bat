@echo off
ShaderCompiler.exe /Tvs_5_0 /EVS %1
del %~n1.vso
ShaderCompiler.exe /Tps_5_0 /EPS %1
del %~n1.pso
pause
