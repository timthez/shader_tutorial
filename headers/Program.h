#include <stdio.h>
#include <string>
#include "Shader.h"

#include <GL/glew.h>
using namespace std;


class Program{
public:
  Program();
  void attachShader(Shader shader);
  void link();
  void use();
  void printActiveAttribs();
  void printActiveUniforms();
  static void resetProgram();
  GLuint getID(){return programID;};
private: 
  bool checkErrors();
  static string getTypeString(GLenum type);
  GLuint programID;  
};

