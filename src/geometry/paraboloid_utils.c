#include "minirt.h"

t_paraboloid new_paraboloid(t_vec3d pos, t_vec3d axis, float focal)
{
    t_paraboloid para;
    
    para.base.pos = pos;
    para.axis = axis;
    para.focal = focal;
    return para;
}