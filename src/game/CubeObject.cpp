#include "CubeObject.h"
#include "../engine/Shader.h"
#include "CubeMesh.h"

CubeObject::CubeObject(float xP, float yP, CubeMesh* cubeMeshP):
cubeMesh {cubeMeshP}
{
  SetPosition(xP, yP);
}

void CubeObject::Draw(Shader& shader){
  shader.setMatrix4("mv_matrix", transform);
  cubeMesh->Draw();
}

void CubeObject::SetPosition(float xP, float yP){
  x = xP;
  y = yP;

  transform = ComputeTransform();
}

Matrix4 CubeObject::ComputeTransform(){
  return Matrix4::createTranslation(Vector3(x, y, -4.0f));
}