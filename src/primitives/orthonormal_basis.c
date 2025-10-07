#include "minirt.h" 
/*
Builds an orthonormal basis from a given axis vector `up`.
The resulting basis uses:
  up      → normalized given axis (local Y-axis), u = (ux, uy, uz)
  right   → perpendicular to up, computed from a temporary vector, r = (rx, uy, uz)
  forward → perpendicular to both up and right, f = (fx, fy, fz)
This basis forms the 3x3 matrix:
    | rx ux fx |
B = | ry uy fy |
    | rz uz fz |
which can be used for coordinate transformations.
*/
t_basis3d build_local_basis(t_vec3d up)
{
    t_basis3d basis;
    t_vec3d tmp;
    
    basis.up = up;
    normlize_vec3d(&basis.up);
    if (fabsf(basis.up.x) > 0.9f) 
        tmp = new_vec3d(0, 0, 1);
    else
        tmp = new_vec3d(1, 0, 0);
    basis.right = cross_vec3d(tmp, up);
    normlize_vec3d(&basis.right);
    basis.forward = cross_vec3d(up, basis.right);
    normlize_vec3d(&basis.forward);
    return basis;
}

/*
Converts a vector v from standard basis (world space) into given orthonormal basis (local).
vl = B^(-1)v, where B^(-1) is the inverse matrix of basis transformation matrix, v world vector
vl = B^(T)v, the inverse matrix B^(-1) is same as the transpose of B since as basis vectors are orthonormals
*/
t_vec3d vec_in_basis(t_vec3d vec, t_basis3d basis)
{
    t_vec3d vec_in_basis;

    vec_in_basis.x = dot_vec3d(vec, basis.right);
    vec_in_basis.y = dot_vec3d(vec, basis.up);
    vec_in_basis.z = dot_vec3d(vec, basis.forward);
    return vec_in_basis;
}
/*
Converts a point from standard basis (world) to given orthonormal basis (local),
vl = B^(-1)(v - O) --> vl = B^(T)(v - O), where B^(T) is the transpose matrix of the basis
transformation matrix B, v point in world and O origin of the basis in world.
*/
t_vec3d point_in_basis(t_vec3d vec, t_basis3d basis, t_vec3d origin)
{
    t_vec3d p_in_basis;
    t_vec3d tmp;

    tmp = sub_vec3d(vec, origin);
    p_in_basis.x = dot_vec3d(tmp, basis.right);
    p_in_basis.y = dot_vec3d(tmp, basis.up);
    p_in_basis.z = dot_vec3d(tmp, basis.forward);
    return p_in_basis;
}
/*
Converts a point from local to world, v = O + Bvl where B is basis transformation batrix
and vl local point, B basis transformation matrix and O origin of basis in world cordinates
*/
t_vec3d point_from_basis(t_vec3d vec, t_basis3d basis, t_vec3d origin)
{
    t_vec3d p;

    p = origin;
    p.x = origin.x + vec.x * basis.right.x + vec.y * basis.up.x + vec.z * basis.forward.x;
    p.y = origin.y + vec.x * basis.right.y + vec.y * basis.up.y + vec.z * basis.forward.y;
    p.z = origin.z + vec.x * basis.right.z + vec.y * basis.up.z + vec.z * basis.forward.z;
    return p;
}

