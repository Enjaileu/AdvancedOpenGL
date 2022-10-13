#include "Cube.h"
#include "../engine/Assets.h"
#include "../engine/MacroUtils.h"

Cube::Cube(float widthP, float heightP, float depthP, float scaleP):
    width{widthP},
    height{heightP},
    depth{depthP},
    scale{scaleP}
{
     //CreateVertex(widthP, heightP, depthP, scaleP);
}

Cube::~Cube(){}

void Cube::Load(){
    static const GLfloat vertexPositions[]{
        
        -(width/2), height/2, (depth/2),
        width/2, height/2, (depth/2),
        -(width/2), -(height/2), (depth/2),
        
        width/2, height/2, (depth/2),
        width/2, -(height/2),  (depth/2),
        -(width/2), -(height/2), (depth/2),
        
        (width/2), (height/2), -(depth/2),
        -width/2, -height/2, -(depth/2),
        (width/2), -height/2, -(depth/2),
        
        (width/2), (height/2), -(depth/2),
        -width/2, (height/2), -(depth/2),
        -width/2, -height/2, -(depth/2),
        

        width/2, height/2,-(depth/2),
        width/2,  -(height/2),-(depth/2),
        width/2, -(height/2), depth/2,
        
        width/2, height/2, -(depth/2),
        width/2, -(height/2), depth/2,
        width/2, height/2, depth/2,

        -width/2, -height/2, (depth/2),
        -width/2,  (height/2), -depth/2,
        -width/2,   (height/2),  (depth/2),
        
        -width/2, -height/2,  (depth/2),
        -width/2, -height/2, -depth/2,
        -width/2,  (height/2), -depth/2,
        

        -(width/2), height/2, -(depth/2),
        width/2,  height/2, -(depth/2),
        width/2, height/2, depth/2,

        -(width/2),  height/2, -(depth/2),
        width/2, height/2, depth/2,
        -(width/2), height/2, depth/2,

        -width/2, -height/2, (depth/2),
        (width/2), -height/2, (depth/2),
        -width/2, -height/2, -depth/2,

        (width/2), -height/2, (depth/2),
        (width/2), -height/2,-depth/2,
        -width/2, -height/2, -depth/2
    };

    // Generate data and put it in buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
    
    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

}

void Cube::Draw(Matrix4 mv_matrixP, Matrix4 project_matrixP){
    Shader shader = Assets::getShader(SHADER_ID(SHADER_NAME));
    shader.use();
    shader.setMatrix4("mv_matrix", mv_matrixP);
    shader.setMatrix4("proj_matrix", project_matrixP);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
/*
void Cube::CreateVertex(float widthP, float heigthP, float depthP, float scale){
    vertex{
        -0.25f,  0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
        0.25f, -0.25f, -0.25f,

        0.25f, -0.25f, -0.25f,
        0.25f,  0.25f, -0.25f,
        -0.25f,  0.25f, -0.25f,

        0.25f, -0.25f, -0.25f,
        0.25f, -0.25f,  0.25f,
        0.25f,  0.25f, -0.25f,

        0.25f, -0.25f,  0.25f,
        0.25f,  0.25f,  0.25f,
        0.25f,  0.25f, -0.25f,

        0.25f, -0.25f,  0.25f,
        -0.25f, -0.25f,  0.25f,
        0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
        -0.25f,  0.25f,  0.25f,
        0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f, -0.25f,
        -0.25f,  0.25f, -0.25f,
        -0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
        0.25f, -0.25f,  0.25f,
        0.25f, -0.25f, -0.25f,

        0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f,  0.25f,

        -0.25f,  0.25f, -0.25f,
        0.25f,  0.25f, -0.25f,
        0.25f,  0.25f,  0.25f,

        0.25f,  0.25f,  0.25f,
        -0.25f,  0.25f,  0.25f,
        -0.25f,  0.25f, -0.25f
    }
}*/