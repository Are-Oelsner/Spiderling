# Spiderling
CMSC 335 Graphics Engine

Controls
j - Filled
k - Wireframe
l - Points
w - look up
a - look left
s - look down
d - look right
e - zoom in
q - zoom out
r - reset camera
y - change selected repulsor
u - move repulsor[rep] up
i - move repulsor[rep] left
o - move repulsor[rep] right
p - move repulsor[rep] down
[ - move repulsor[rep] closer
] - move repulsor[rep] further

<filename.obj> tx ty tz rx ry rz sx sy sz cr cg cb
tx float x translation in scene
ty float y translation in scene
tz float z translation in scene
rx float x rotation in scene
ry float y rotation in scene
rz float z rotation in scene
sx float x scale in scene
sy float y scale in scene
sz float z scale in scene
cr float red color of object
cg float green color of object
cb float blue color of object

<filename.par>
l intMin intMax                 # particle lifetime uniform generation range
g -float                        # negative float representing gravity, applied to y axis
i -float                        # negative float representing air resistance, applied to x, y, and z
w floatx floaty floatz          # floats representing wind in x, y, and z
n int                           # positive int number of particles
a float                         # angle from verticle specifying cone of generation for initial velocities
p xmin xmax ymin ymax zmin zmax # floats representing the bounding box for generating particle initial position
v vmin vmax                     # floats representing range of magnitudes for initial velocities
t xfloat yfloat zfloat          # floats representing translation of system within the scene. Default to 0 0 0
r xfloat yfloat zfloat          # floats representing rotation of system within the scene. Default to 0 0 0
s xfloat yfloat zfloat          # floats representing scale of system within the scene. Default to 1 1 1

<filename.rep> xpos ypos zpos mass status
xpos float representing x position of point attractor
ypos float representing y position of point attractor
zpos float representing z position of point attractor
mass float representing mass of point attractor
status int shows state of either repulsor when >0 or attractor when <= 0


left - move left
right - move right
up - move camera up
down - move camera down


fill new vector<VEC6> data in Obj with vec3 of vertex info and vec3 of associated normal info for each pair in the indexed list/ change the index to reference back to already created points/normals if the pairing is repeated

#TODO:
TODO change over all camera stuff to new functions at c and up
write functions for looking left and write, keeping cam.center the same distance away as you turn.
Fix buffer problem...

Figure out hLook and vLook functions for keeping the center the same distance away as you look around

Have Obj store associated ebo and vbo and have draw function.

change from pointers to const reference





//////////////////////////////////////////////////////////////////////////////////////////////////
Project 1 Revisions
#TODO

//////////////////////////////////////////////////////////////////////////////////////////////////
Project 2 Revisions

#Use library for PI.

have const correctness on functions + params

Don't return by pointer or value, Return by reference or const reference

Pass params by reference or const reference not by value

remove num variables in object. This is just the size of vectors. Try to be minimal.

Class Vec. Make all of these functions possibly in namespace, not members of a class

Reduce construction/copying cost of methods/code

Arrays in methods make static to reduce memory/initialization cost

#Have parse method for file, and not just part of main


//////////////////////////////////////////////////////////////////////////////////////////////////
Project 3 Details
In this assignment, you will create some sort of animation. You can either
design a key-frame system for a hierarchical model or create a particle system.
The hierarchical model should be non-trivial, i.e., a tree hierarchy with at
least five components in 3D. The particle system should contain a generator an
attractor and at least three other forces. Add the specification of the
animation to your working scene specification (your file format from assignment
2).

Extras
Improve the efficiency of your rendering.

Allow user input to influence your animation.

Support both hierarchical models and particle systems.

For a hierarchical model, support interpolation with splines in addition to
linear interpolation.

For the particle system, allow changes in state other than position and velocity.

For the particle system, support a large variety of generators, attractors,
repulsors, etc. in your file format.

For the particle system, support collision with objects.

Provide the ability to script the motion of the camera.

Etc


Particle System:
immediate mode for particles
ParticleSystem Object
with data struct for position, velocity
draw as points
after each draw loop
update based on force model - gravity

textbook pg. 726 actual or 719 tb


TODO Fix bug, check 'in loop, in loop 3' error

TODO get cone initial velocity generation working, find out why gravity goes to the leftish

Add 2 more forces and an attractor/repulsor
forces could be wind and air resistance
attractor could be vacuum in the sky/black hole

For attractor use gravity equation F = m1m2... and solve for acceleration

Project 4 Details

Don't need to write image loader
can use qt or soil or anything I want
only need to support 1 material per obj

//Personal -- add lots of cool models

Project 4//////////////////////////////////////////////////////////
look into qt image reader class link on proj4 pdf.
Check back with jory about qt error.

move includes to the file they are used in, ex to the cpp if theyre only used in the cpp
QGlWidget has function convert to gl format which I will pass in the data from imagereader, which will then
returns qimage , then use the above function to put it in gl format but will still be a qimage. Pass array contents of the qimage to the opengl function.
