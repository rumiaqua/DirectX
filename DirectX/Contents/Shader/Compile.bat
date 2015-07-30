@echo off
ShaderCompiler.exe /Tvs_4_0 /EVS %1
ShaderCompiler.exe /Tps_4_0 /EPS %1
del %~n1.vso
del %~n1.pso
pause
