#pragma once
#include <string>

class GameEngine{


private:
    std::string state;

public:
    GameEngine();

    GameEngine(std::string& current_state);

};

