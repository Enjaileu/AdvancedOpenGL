#include "Scene_Pong.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "CubeMesh.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_Pong::Scene_Pong()
{
}

Scene_Pong::~Scene_Pong() {
    clean();
}

void Scene_Pong::setGame(Game *_game) {
    game = _game;
}

void Scene_Pong::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    cubeMesh = new CubeMesh();
    cubeMesh->Load();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    cubes.emplace_back(0.0f, 0.0f, cubeMesh);
    cubes.emplace_back(-3.f, 0.f, cubeMesh);
}

void Scene_Pong::clean() {
    cubeMesh->Clean();
    delete cubeMesh;
}

void Scene_Pong::pause() {
}

void Scene_Pong::resume() {
}

void Scene_Pong::handleEvent(const InputState &inputState) {
}

void Scene_Pong::update(float dt) {
    cubes[0].SetPosition(cubes[0].GetX() + (ballSpeedX*dt), cubes[0].GetY());
    if(cubes[0].GetX() >= 3|| cubes[0].GetX() <= -3){
        ballSpeedX *= -1;
    }
    /*
    ball->SetPosition(ball->GetX() + (ballSpeedX*dt), ball->GetY() + (ballSpeedY*dt));
    if(ball->GetX() >= 10|| ball->GetX() <= 0){
        ballSpeedX *= -1;
    }
    else if( ball->GetY() <= 0 || ball->GetY() >= 10){
        ballSpeedY *= -1;
    }*/
}

void Scene_Pong::draw() {

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    for (auto& cube : cubes) {
        cube.Draw(shader);
    }
}
