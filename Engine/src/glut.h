/**
 * Este ficheiro serve apenas para que qualquer outro ficheiro do projeto possa facilmente incluir as libraries
 * do glut e do glew sem ter de copiar e colar várias vezes o mesmo pedaço de código.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif
