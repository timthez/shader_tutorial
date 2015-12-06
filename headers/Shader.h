//
//  Shader.hpp
//  opengl-series
//
//  Created by Tim Zuercher on 11/21/15.
//
//


#include "Logger.h"
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
using namespace std;


class Shader{
public:
    Shader(string file,GLenum type);
    GLuint getID(){return shaderID;};
private:
  GLuint shaderID;
  GLchar * readShaderFile(const char *fileName);
  void checkErrors(string fileName);
  static string getShaderType(GLenum type);
  
};

