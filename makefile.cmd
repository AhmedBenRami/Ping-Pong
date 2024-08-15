@ECHO OFF
gcc .\main.c -Iraylib -Lraylib -lraylib -lopengl32 -lgdi32 -lwinmm