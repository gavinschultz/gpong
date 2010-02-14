OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.obj,$(wildcard $(SRCDIR)/*.c)) 
DEPS = $(patsubst $(SRCDIR)/%.c,$(INCDIR)/%.h,$(wildcard $(INCDIR)/*.h)) 
OBJDIR = .
INCDIR = include
SRCDIR = src
OUTPUTDIR = .
RESDIR = resources
LIBDIR = lib
CC = cl.exe
LINK = link.exe
CFLAGS = /MT /O2 /TC /c /I$(INCDIR)
LIBS = SDL.lib SDLmain.lib SDL_mixer.lib SDL_ttf.lib glu32.lib opengl32.lib
DEL = del /F /Q
COPY = copy /Y

gpong: $(OBJ)
	$(LINK) /INCREMENTAL /SUBSYSTEM:WINDOWS /MACHINE:X86 /OUT:"$(OUTPUTDIR)\$@.exe" $(OBJ) $(LIBS)
	 
$(OBJDIR)/%.obj : $(SRCDIR)/%.c $(DEPS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< 

#.PHONY: clean
install: gpong
	$(COPY) $(RESDIR)\*.* $(OUTPUTDIR)\ 
	$(COPY) $(LIBDIR)\*.* $(OUTPUTDIR)\ 
	$(DEL) $(OUTPUTDIR)\*.ilk
	$(DEL) $(OUTPUTDIR)\*.obj
	
clean:
	$(DEL) $(OBJDIR)\*.obj
	$(DEL) $(OUTPUTDIR)\*.exe
	$(DEL) $(OUTPUTDIR)\*.manifest
	$(DEL) $(OUTPUTDIR)\*.ilk
