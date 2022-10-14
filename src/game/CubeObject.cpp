#include "CubeObject.h"
#include "../engine/Shader.h"
#include "../engine/MacroUtils.h"
#include "../engine/Assets.h"
#include "CubeMesh.h"

CubeObject::CubeObject(float xP, float yP, float zP,
  float scaleWP, float scaleHP, float scaleDP,
  CubeMesh* cubeMeshP, Shader shaderP):
cubeMesh {cubeMeshP},
scaleW{scaleWP},
scaleH{scaleHP},
scaleD{scaleDP},
shader{shaderP}
{
  SetPosition(xP, yP, zP);
}

void CubeObject::Draw(Matrix4 projectionP){
  shader.use();
  shader.setMatrix4("proj_matrix", projectionP);
  shader.setMatrix4("mv_matrix", transform);
  cubeMesh->Draw();
}

void CubeObject::SetPosition(float xP, float yP, float zP){
  x = xP;
  y = yP;
  z = zP;

  transform = ComputeTransform();
}

Matrix4 CubeObject::ComputeTransform(){
  return Matrix4::createTranslation(Vector3(x, y, z))
  * Matrix4::createScale(scaleW, scaleH, scaleD);
}