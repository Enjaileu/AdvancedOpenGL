#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "../engine/maths/Matrix4.h"

class Shader;
class CubeMesh;

class CubeObject {
public:
  CubeObject(float xP, float yP, 
    float scaleWP, float scaleHP, float ScaleDP,
    CubeMesh* cubeMeshP);

  void Draw(Shader& shader);

  float GetX() const { return x; }
  float GetY() const { return y; }
  void SetPosition(float xP, float yP);
  Matrix4 ComputeTransform();

private:
  float x { 0.0f };
  float y { 0.0f };
  float scaleW{1.f};
  float scaleH{1.f};
  float scaleD{1.f};
  Matrix4 transform {};

  CubeMesh* cubeMesh { nullptr };
  
};

#endif