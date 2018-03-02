# Spiderling
CMSC 335 Graphics Engine

Controls
j - Filled
k - Wireframe
l - Points
i - zoom in
o - zoom out
left - rotate left
right - rotate right
up - move camera up
down - move camera down


TODO:
fill new vector<VEC6> data in Obj with vec3 of vertex info and vec3 of associated normal info for each pair in the indexed list/ change the index to reference back to already created points/normals if the pairing is repeated

TODO change over all camera stuff to new functions at c and up
write functions for looking left and write, keeping cam.center the same distance away as you turn.
Fix buffer problem...

Figure out hLook and vLook functions for keeping the center the same distance away as you look around

Have Obj store associated ebo and vbo and have draw function.

change from pointers to const reference
