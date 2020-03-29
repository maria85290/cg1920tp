#ifndef CG_TP_VECTORS_H
#define CG_TP_VECTORS_H

typedef struct vec3 {
    double x;
    double y;
    double z;
} vec3;

double norm(vec3 v);

vec3 normalize(vec3 v);

vec3 cross(vec3 a, vec3 b);

vec3 scale(vec3 v, double factor);

#endif //CG_TP_VECTORS_H