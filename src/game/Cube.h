
#ifndef Cube_H
#define Cube_H
#include <GL/glew.h>
#include "../engine/Shader.h"

class Cube{
public:
    Cube(float widthP, float heigthP, float depthP, float scale);
    ~Cube();
    void Load();
    void Draw(Matrix4 mv_matrixP, Matrix4 project_matrixP);

private:
    GLuint buffer;
    float width;
    float height;
    float depth;
    float scale;
};

#endif //Cube_H