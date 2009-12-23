OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c)) 
DEPS = $(patsubst $(SRCDIR)/%.c,$(INCDIR)/%.h,$(wildcard $(INCDIR)/*.h)) 
OBJDIR = bin
INCDIR = include
SRCDIR = src
GPONGOUTPUTDIR = .
RESDIR = resources
LIBDIR = lib
CC = mingw32-gcc.exe
CFLAGS = -I$(INCDIR)
LIBS = -lmingw32 -lSDLmain -lSDL -lSDL_mixer
DEL = del /F /Q
COPY = copy /Y

gpong: $(OBJ)
	$(CC) -o $(GPONGOUTPUTDIR)\$@.exe $(OBJ) $(LIBS)
	 
$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPS) 
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

#.PHONY: clean
install: gpong
	$(COPY) $(RESDIR)\*.* $(GPONGOUTPUTDIR)\ 
	$(COPY) $(LIBDIR)\*.* $(GPONGOUTPUTDIR)\ 
	
clean:
	$(DEL) $(OBJDIR)\*.o
	$(DEL) $(GPONGOUTPUTDIR)\*.exe 
