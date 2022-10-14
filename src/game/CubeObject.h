#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "../engine/maths/Matrix4.h"
#include "../engine/Shader.h"

class Shader;
class CubeMesh;

class CubeObject {
public:
  CubeObject(float xP, float yP, float zP,
    float scaleWP, float scaleHP, float ScaleDP,
    CubeMesh* cubeMeshP, Shader shaderP);

  void Draw(Matrix4 pojectionP);

  float GetX() const { return x; }
  float GetY() const { return y; }
  float GetZ() const { return z; }
  float GetWidth() const {return scaleW *0.25f;}
  float GetHeight() const {return scaleH * 0.25f;}
  void SetPosition(float xP, float yP, float zP);
  Matrix4 ComputeTransform();

private:
  float x { 0.0f };
  float y { 0.0f };
  float z {0.f};
  float scaleW{1.f};
  float scaleH{1.f};
  float scaleD{1.f};
  Matrix4 transform {};

  CubeMesh* cubeMesh { nullptr };
  Shader shader;
  
};

#endif