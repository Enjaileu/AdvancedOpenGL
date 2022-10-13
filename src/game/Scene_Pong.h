#ifndef Scene_Pong_H
#define Scene_Pong_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "CubeObject.h"
#include "CubeMesh.h"
#include <vector>

using namespace std;

class Scene_Pong : public Scene {
public:
    Scene_Pong();
    ~Scene_Pong();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;
    CubeMesh* cubeMesh;

    Matrix4 transform;
    Matrix4 projection;

    Shader shader;
    vector<CubeObject> cubes;

    CubeObject* ball;
    float ballSpeedX{3.f};
    float ballSpeedY{3.f};
};


#endif //Scene_Pong_H