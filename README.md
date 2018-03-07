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
i - look left beta
o - look right beta

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
Project 2 Revisions

Use library for PI.

have const correctness on functions + params

Don't return by pointer or value, Return by reference or const reference

Pass params by reference or const reference not by value

remove num variables in object. This is just the size of vectors. Try to be minimal.

Class Vec. Make all of these functions possibly in namespace, not members of a class

Reduce construction/copying cost of methods/code

Arrays in methods make static to reduce memory/initialization cost

Have parse method for file, and not just part of main
