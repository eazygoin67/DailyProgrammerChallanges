echo ===COMPILING===
gcc -std=c99 -O3 -I"C:\Libs\SDL2.0.3\include\SDL2" -c main.c -o main.o
echo === LINKING ===
echo    -no mwindows
gcc -L"C:\Libs\SDL2.0.3\lib" -o Test.exe main.o -lmingw32 -lSDL2main -lSDL2 -s -static-libgcc  
echo ===  DONE   ===