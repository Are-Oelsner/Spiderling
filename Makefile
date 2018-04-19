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
FLAGS = -fPIC #-Wall -Werror 
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
  GL_LIBS = -lglut -lGLU -lGL -lGLEW -lQt5Gui -lQt5Core -lSOIL
else
  ifeq "$(OS)" "OSX"
  GL_LIBS = -framework GLUT -framework OpenGL
endif
endif

################################################################################
## Rules
################################################################################
INCL = $(GL_INCL) -I /usr/include/x86_64-linux-gnu/qt5
LIBS = $(GL_LIBS)

OBJS = WindowClass.o\
			 Camera.o\
			 Light.o\
			 Obj.o\
			 Vec.o\
			 ParticleSystem.o\
       main.o

EXECUTABLE = spiderling

default: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(OBJMOC)
	$(CC) $(OPTS) $(FLAGS) $(DEFS) $(OBJS) $(LIBS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJS)

.cpp.o:
	$(CC) $(OPTS) $(FLAGS) $(DEFS) -MMD $(INCL) -c $< -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

-include Dependencies

################################################################################
## My Stuff
################################################################################
os:
	vim main.cpp +":tabf ParticleSystem.cpp" +":vsplit ParticleSystem.h" +":tabf Obj.cpp" +":vsplit Obj.h" +":tabf Camera.cpp" +":vsplit Camera.h" +":tabf Vec.cpp" +":vsplit Vec.h" +":tabf PS.dat" +":vsplit smoke.par" +":tabf README.md"

o:
	vim main.cpp +":tabf Light.cpp" +":vsplit Light.h" +":tabf Obj.cpp" +":vsplit Obj.h" +":tabf README.md"

pdf:
	evince Project1.pdf

r:
	./spiderling obj.dat objs

rs:
	./spiderling objs.dat objs

rd:
	./spiderling obj1.dat objs

p:
	./spiderling PS.dat objs

gdb:
	gdb spiderling

v:
	valgrind spiderling
