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
  GL_LIBS = -lglut -lGLU -lGL -lGLEW -lQt5Gui
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
	vim main.cpp +":tabf ParticleSystem.cpp" +":vsplit ParticleSystem.h" +":tabf Obj.cpp" +":vsplit Obj.h" +":tabf PS.dat" +":vsplit smoke.par" +":tabf README.md"

pdf:
	evince Project1.pdf

r:
	./spiderling objs.dat 0

rd:
	./spiderling objs.dat 1

r1:
	./spiderling obj2.dat 0


s:
	./spiderling obj1.dat 0

p:
	./spiderling PS.dat 0

s1:
	./spiderling obj1.dat 1

gdb:
	gdb spiderling

v:
	valgrind spiderling
