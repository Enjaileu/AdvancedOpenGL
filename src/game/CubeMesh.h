#ifndef CUBEMESH_H
#define CUBEMESH_H

#include <GL/glew.h>

class CubeMesh {
public:
  void Load();
  void Draw();
  void Clean();
  
private:
  GLuint vao;
  GLuint buffer;
};

#endif