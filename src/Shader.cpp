//
//  Shader.cpp
//  opengl-series
//
//  Created by Tim Zuercher on 11/21/15.
//
//
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "Shader.h"


GLchar * Shader::readShaderFile(const char *fileName){
    FILE *fp = NULL;
    GLchar * content = NULL;    
    int length = 0;
    
    //Check for null
    if (fileName == NULL) {
        printf( ANSI_COLOR_RED "File Name was empty of NULL!\n" ANSI_COLOR_RESET);
        exit(EXIT_FAILURE);
    };
    
    fp = fopen(fileName, "rt");
    
    //Check for errors opening file
    if (fp == NULL){
        fprintf(stderr, ANSI_COLOR_RED "Failed to read shader from '%s' file.\n\n" ANSI_COLOR_RESET,fileName );
        exit(EXIT_FAILURE);   
    };
    
    //Get File Length
    fseek(fp, 0, SEEK_END);    
    length = ftell(fp);   
    
    //Move Pointer back to start 
    rewind(fp);
    
    
    if (length > 0){
        //Allocate Space for file with addition of null byte
        content = (GLchar *)malloc(sizeof(char)* (length + 1));
        
        //Read Whole File and append null byte
        if (content != NULL){
            length = fread(content, sizeof(char), length, fp);
            content[length] = '\0';
        }
    }
    
    fclose(fp);
    
    //Check for Any errors
    if (content == NULL){
        fprintf(stderr, ANSI_COLOR_RED "Failed to read shader from '%s' file.\n\n" ANSI_COLOR_RESET,fileName );
        exit(EXIT_FAILURE);
    }
    
    return content;
}



bool Shader::checkErrors(string fileName){
    //Check for Compile Errors
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    
    if (success == GL_FALSE){
        //Get Length of Error Log
        printf(ANSI_COLOR_RED "Compilation Failed for %s.\n" ANSI_COLOR_RESET, fileName.c_str());
        GLint length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);        
        if (length > 0)
        {
            //Read Error
            char * log = new char[length];
            GLsizei written;
            glGetShaderInfoLog(shaderID, length, &written, log);
            //Print Error
            fprintf(stderr, ANSI_COLOR_RED "%s\n\n" ANSI_COLOR_RESET, log );
            delete[] log;
            return true;
        }
    }
    return false;
}

Shader::Shader(string file, GLenum type){
    this->shaderType = getShaderType(type);
    
    char buff[255];
    Logger::log(ANSI_COLOR_GREEN "################################################################################");
    snprintf(buff, sizeof(buff),"                             Creating %s                    ",  getShaderType(type).c_str());
    Logger::log(buff);
    Logger::log("################################################################################" ANSI_COLOR_RESET);
    shaderID = glCreateShader(type);
    //Read Shader from file
    
    Logger::log("Reading Source from file");
    GLchar * source = readShaderFile(file.c_str());
    Logger::log("Reading complete");
    
    
    //Link shader to source
    Logger::log("Linking Source to Shader");
    glShaderSource(shaderID, 1, (const GLchar **)&source, NULL);
    free(source);
    Logger::log("Linking Complete");
    
    
    snprintf(buff, sizeof(buff), ANSI_COLOR_GREEN "Compiling Shader '%s' as %s" ANSI_COLOR_RESET, file.c_str(), getShaderType(type).c_str());
    Logger::log(buff);
    glCompileShader(shaderID);
    if(!checkErrors(file))
        Logger::log("Compilation Complete\n");
}

string Shader::getShaderType(GLenum type){
    switch (type) {
        case GL_VERTEX_SHADER:
            return "Vertex Shader";
        case GL_FRAGMENT_SHADER:
            return "Fragment Shader";
        case GL_GEOMETRY_SHADER:
            return "Geometry Shader";
        case GL_TESS_CONTROL_SHADER:
            return "Tesselation Control Shader";
        case GL_TESS_EVALUATION_SHADER:
            return "Tesselation Evaluation Shader";
        default:
            return "Unknown Type";
    }
}


