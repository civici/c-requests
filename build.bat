set sources=main.c sockr.c
set includepath=C:\vcpkg/installed/x64-windows/include
set libpath=C:\vcpkg/installed/x64-windows/lib

cl /EHsc /MD /I%includepath% %sources% /link /LIBPATH:%libpath% /out:a.exe
