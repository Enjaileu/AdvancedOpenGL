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
    Assets::loadShader("assets/shaders/Pong.vert", "assets/shaders/Pong.frag", "", "", "", "Pong");
    Assets::loadShader("assets/shaders/Pong.vert", "assets/shaders/003_triangle.frag", "", "", "", "Grass");
    shaderBall = Assets::getShader(SHADER_ID(IDENT(Pong)));
    shaderWallBack = Assets::getShader(SHADER_ID(IDENT(Grass)));
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    cubeMesh = new CubeMesh();
    cubeMesh->Load();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //ball
    cubes.emplace_back(0.0f, 0.0f, -4.f, 
                    0.5f, 0.5f, 0.3f, 
                    cubeMesh, shaderBall);
                   
    //walls
    cubes.emplace_back(3.5f, 0.f, -4.f,
                    1.f, 10.f, 1.f, 
                    cubeMesh, shaderBall);
    cubes.emplace_back(0.f, -2.f, -4.f,
                    15.f, 1.f, 1.f, 
                    cubeMesh, shaderBall);
    cubes.emplace_back(0.f, 2.f, -4.f,
                    15.f, 1.f, 1.f, 
                    cubeMesh, shaderBall);
    //racket
    cubes.emplace_back(-3.f, 0.f, -4.f, 
                    0.3f, 1.5f, 0.5f, 
                    cubeMesh, shaderBall);
    //bg
    cubes.emplace_back(0.f, 0.f, -5.f,
                    18.f, 15.f, 1.f, 
                    cubeMesh, shaderWallBack);
    
    ball = &cubes[0];
    racket = &cubes[4];
    
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
   
   // Keyboard state
   const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	if (keyboardState[SDL_SCANCODE_UP]) {
        if(!IsCollided(*racket, cubes[3])){
            racket->SetPosition(racket->GetX(), racket->GetY()+ (racketSpeed*dt), racket->GetZ());
        }
	}
    else if(keyboardState[SDL_SCANCODE_DOWN]){
        if(!IsCollided(*racket, cubes[2])){
            racket->SetPosition(racket->GetX(), racket->GetY()- (racketSpeed*dt), racket->GetZ());
        }
    }
    
    //ball deplacement
    ball->SetPosition(ball->GetX() + ballSpeedX * dt, ball->GetY() + ballSpeedY * dt, ball->GetZ());
    if(IsCollided(*ball, cubes[3]) || IsCollided(*ball, cubes[2])){
        ballSpeedY *= -1;
    }else if(IsCollided(*ball, *racket) || IsCollided(*ball, cubes[1])){
        ballSpeedX *= -1;
    }

    //gameover
    if(ball->GetX() <= -4){
        ball->SetPosition(-1.f, 0.f, -4.f);
        ballSpeedX = {4.f};
    }
}

void Scene_Pong::draw() {

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    for (auto& cube : cubes) {
        cube.Draw(projection);
    }
}

bool Scene_Pong::IsCollided(CubeObject cube2 , CubeObject cube1){
    float cube1minX = cube1.GetX() - cube1.GetWidth();
    float cube1maxX = cube1.GetX() + cube1.GetWidth();
    float cube1minY = cube1.GetY() - cube1.GetHeight();
    float cube1maxY = cube1.GetY() + cube1.GetHeight();

    float cube2minX = cube2.GetX() - cube2.GetWidth();
    float cube2maxX = cube2.GetX() + cube2.GetWidth();
    float cube2minY = cube2.GetY() - cube2.GetHeight();
    float cube2maxY = cube2.GetY() + cube2.GetHeight();

    return (cube2maxX >= cube1minX && cube2maxX <= cube1maxX
    && cube2minY >= cube1minY && cube2minY <= cube1maxY )
    || (cube2minX >= cube1minX && cube2minX <= cube1maxX
    && cube2minY >= cube1minY && cube2minY <= cube1maxY )
    || (cube2minX >= cube1minX && cube2minX <= cube1maxX
    && cube2maxY <= cube1maxY && cube2maxY >= cube1minY)
    || (cube2maxX >= cube1minX && cube2maxX <= cube1maxX
    && cube2maxY >= cube1minY && cube2maxY <= cube1maxY);
    
}

bool IsColliedWalls(CubeObject cube1){
    return false;
}
