# Spiderling
Author: Are Oelsner
CMSC 335 Graphics Engine
Project 5: Ray Tracer


/////////////////////////////////////////////////////////////////////////////////////////
///Notes
/////////////////////////////////////////////////////////////////////////////////////////
Don't need to store recursive tree for ray tracing algorithm. That is done by the recursive stack.
Ask Jory about the function he mentioned for constructing spheres in GL and how I could add support for that for my obj parser.
remove timer function that calls glutpost redisplay
set up so I can push a key and it re-raytraces
no projection matrix, no scan line conversion, just shoot rays into the scene and use collision detection.
Textbook page 634

Terminate a ray tracing path if any of the following conditions are satisfied
    Ray doesn't intersect any surfaces
    Ray intersects a light source that is not a reflecting surface (almost never happens)
    The tree has been generated to its maximum allowable depth.

Functions to find/implement:
  Collision detection
    Sphere, Quad, Maybe Triangle
  Ray Tracing Algorithm with just Reflection


/////////////////////////////////////////////////////////////////////////////////////////
///Info
/////////////////////////////////////////////////////////////////////////////////////////
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

Lights
light <position floatx floaty floatz (float 0/1 for directional/spot)> <direction floatx floaty floatz> <ambient floatx floaty floatz floatt> <diffuse floatx floaty floatz floatt> <specular floatx floaty floatz float t> <constant atten float> <linear atten float> <quadratic atten float> <angular atten float> <angular limit float>
