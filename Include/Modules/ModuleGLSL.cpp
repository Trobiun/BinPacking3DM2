#ifdef __MESA__
#define GL_GLEXT_PROTOTYPES
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef WIN32
#include <Windows.h>
#endif
#ifdef WIN64
#include <Windows.h>
#endif

#ifdef __NV__
#include <map>
#include <GL/glew.h>
#endif
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#ifdef __MESA__
#include <GL/glext.h>
#endif

#include "ModuleGLSL.h"

static void CheckError(int line) {
  GLenum err = glGetError();
  if (err) {
    printf("GL Error %s (0x%x) at line %d\n",
           gluErrorString(err), (int) err, line); }
}
 
static void LoadAndCompileShader(GLuint shader, const char *text) {
  GLint stat;
  glShaderSource(shader, 1, (const GLchar **) &text, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
  if (!stat) {
    GLchar log[1000];
    GLsizei len;
    glGetShaderInfoLog(shader, 1000, &len, log);
    fprintf(stderr, "Problem compiling shader: %s\n", log);
    exit(1); }
}

static void ReadShader(GLuint shader, const char *filename) {
  const int max = 100*1000;
  int n;
  char *buffer = (char*) malloc(max);
  FILE *f = fopen(filename, "r");
  if (!f) {
    fprintf(stderr, "Unable to open shader file %s\n", filename);
    exit(1); }
  n =(int) fread(buffer, 1, max, f);
  if (n > 0) {
    buffer[n] = 0;
    LoadAndCompileShader(shader, buffer); }
  fclose(f);
  free(buffer);
}

static void CheckLink(GLuint prog) {
  GLint stat;
  glGetProgramiv(prog, GL_LINK_STATUS, &stat);
  if ( !stat ) {
    GLchar log[1000];
    GLsizei len;
    glGetProgramInfoLog(prog, 1000, &len, log);
    fprintf(stderr, "Linker error:\n%s\n", log); }
  GLint charsWritten, infoLogLength; 
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH,&infoLogLength);
  if ( infoLogLength ) {
    char *infoLog = new char[infoLogLength]; 
    glGetProgramInfoLog(prog, infoLogLength, &charsWritten, infoLog); 
    printf(infoLog); 
    delete [] infoLog; }
}

GLuint createProgram(GLuint vertShader,GLuint fragShader) {
  GLuint program = glCreateProgram();
  if ( vertShader )
    glAttachShader(program,vertShader);
  if ( fragShader )
    glAttachShader(program,fragShader);
  glLinkProgram(program);
  CheckLink(program);
  CheckError(__LINE__);
  return(program);
}

GLuint createProgram(char *vertShaderFile,GLuint *vertShader,char *fragShaderFile,GLuint *fragShader) {
       printf("*\n");
   if ( vertShaderFile != NULL ) {
       printf("a\n");
     *vertShader = glCreateShader(GL_VERTEX_SHADER);
       printf("b\n");
     ReadShader(*vertShader,vertShaderFile);
       printf("c\n"); }
     else
     if ( vertShader )
       *vertShader = 0;
       printf("*\n");
   if ( fragShaderFile != NULL ) {
     *fragShader = glCreateShader(GL_FRAGMENT_SHADER);
     ReadShader(*fragShader,fragShaderFile); }
     else
     if ( fragShader )
       *fragShader = 0;
       printf("*\n");
   return(createProgram(( vertShader ) ? *vertShader : 0,
                        ( fragShader ) ? *fragShader : 0));
}

void checkUniforms(uniform_info *uniforms,GLuint program,int aff) {
  if ( uniforms == NULL )
    return;  
  for ( int i = 0 ; uniforms[i].name ; i++ ) {
    uniforms[i].location = glGetUniformLocation(program,uniforms[i].name);
	  if ( aff )
      printf("-> Uniform %s location: %d\n", uniforms[i].name,uniforms[i].location);
    if ( uniforms[i].type == GLSL_FLOAT ) {
      switch (uniforms[i].size) {
        case 1:
          glUniform1fv(uniforms[i].location, 1, uniforms[i].floatValue);
          break;
        case 2:
          glUniform2fv(uniforms[i].location, 1, uniforms[i].floatValue);
          break;
        case 3:
          glUniform3fv(uniforms[i].location, 1, uniforms[i].floatValue);
          break;
        case 4:
          glUniform4fv(uniforms[i].location, 1, uniforms[i].floatValue);
          break;
        default:
           abort(); } 
      CheckError(__LINE__); }
    if ( uniforms[i].type == GLSL_INT ) {
      switch (uniforms[i].size) {
        case 1:
          glUniform1iv(uniforms[i].location, 1, uniforms[i].intValue);
          break;
        case 2:
          glUniform2iv(uniforms[i].location, 1, uniforms[i].intValue);
          break;
        case 3:
          glUniform3iv(uniforms[i].location, 1, uniforms[i].intValue);
          break;
        case 4:
          glUniform4iv(uniforms[i].location, 1, uniforms[i].intValue);
          break;
        default:
           abort(); } 
      CheckError(__LINE__); } }
}

void checkUniforms(uniform_info *uniforms,GLuint program) {
  checkUniforms(uniforms,program,1);
}
