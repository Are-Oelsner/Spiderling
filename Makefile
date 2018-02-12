################################################################################
## OS
################################################################################
OS = LINUX

################################################################################
## GCC
################################################################################
CC = g++ -std=c++14
OPTS = -O3
#OPTS = -g
FLAGS = -Wall -Werror
ifeq "$(OS)" "LINUX"
  DEFS = -DLINUX
else
  ifeq "$(OS)" "OSX"
  DEFS = -DOSX
endif
endif

################################################################################
## GL and QT
################################################################################
# Open gl
ifeq "$(OS)" "LINUX"
  GL_LIBS = -lglut -lGLU -lGL -lGLEW
else
  ifeq "$(OS)" "OSX"
  GL_LIBS = -framework GLUT -framework OpenGL
endif
endif

################################################################################
## Rules
################################################################################
INCL = $(GL_INCL)
LIBS = $(GL_LIBS)

OBJS = WindowClass.o\
			 Obj.o\
       main.o

EXECUTABLE = spiderling

default: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(OBJMOC)
	$(CC) $(OPTS) $(FLAGS) $(DEFS) $(OBJS) $(LIBS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) Dependencies $(OBJS)

.cpp.o:
	$(CC) $(OPTS) $(DEFS) -MMD $(INCL) -c $< -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

-include Dependencies

################################################################################
## My Stuff
################################################################################
o:
	vim -p main.cpp Obj.cpp WindowClass.cpp

pdf:
	evince Project1.pdf

r:
	./spiderling cube.obj
