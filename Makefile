CFLAGS = /nologo /W3 /MD

build: so-cpp.exe

so-cpp.exe: so-cpp.obj hashtable.obj vector.obj parser.obj
	link /nologo /out:$@ $**

so-cpp.obj: so-cpp.c

hashtable.obj: hashtable.c

vector.obj: vector.c

parser.obj: parser.c

clean:
	del /Q /F *.obj so-cpp.exe
