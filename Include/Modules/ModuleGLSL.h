#ifndef MODULEGLSL
#define MODULEGLSL

#define GL_GLEXT_PROTOTYPES

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glext.h>

typedef enum {
  GLSL_FLOAT = 1,
  GLSL_INT = 2 } GLSL_type;

typedef struct uniform_info {
  const char *name;
  GLuint size;
  GLint type;
  GLint location;
  GLfloat floatValue[4];
  GLint intValue[4]; } uniform_info;

GLuint createProgram(GLuint vertShader,GLuint fragShader);
GLuint createProgram(char *vertShaderFile,GLuint *vertShader,char *fragShaderFile,GLuint *fragShader);
void checkUniforms(uniform_info *uniforms,GLuint program);
void checkUniforms(uniform_info *uniforms,GLuint program,int aff);

#endif
