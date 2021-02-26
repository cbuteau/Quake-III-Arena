rem msbuild .\code\quake3.sln /t:Clean,Build /p:Configuration=Release /p:Platform=x86
rem msbuild .\code\quake3.sln /t:Clean,Build /p:Configuration=Debug /p:Platform=x86
rem msbuild .\q3asm\q3asm.sln /t:Clean,Build /p:Configuration=Release /p:Platform=x86

premake
msbuild build\Q3Withv8.sln /p:Configuration=release /p:Configuration=debug
