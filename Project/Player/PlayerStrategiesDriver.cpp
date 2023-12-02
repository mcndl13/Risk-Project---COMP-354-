#include <iostream>
#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

using namespace std;

// g++ -std=c++17 -o pst ../Map/Map.cpp Player.cpp  ../Cards/Cards.cpp ../Orders/Orders.cpp ../GameEngine/GameEngine.cpp ../CommandProcessing/CommandProcessing.cpp PlayerStrategies.cpp PlayerStrategiesDriver.cpp 

int main() {

    CommandProcessor* command_processor = new CommandProcessor();

    Command* commnand_loadmap = new Command(commandType::loadmap);
    Command* commnand_validatemap = new Command(commandType::validatemap);
    Command* commnand_addplayer = new Command(commandType::addplayer);
    Command* commnand_gamestart = new Command(commandType::gamestart);
    Command* commnand_replay = new Command(commandType::replay);
    Command* commnand_quit = new Command(commandType::quit);


    command_processor->saveCommand(commnand_loadmap);
    command_processor->saveCommand(commnand_validatemap);
    command_processor->saveCommand(commnand_addplayer);
    command_processor->saveCommand(commnand_gamestart);
    command_processor->saveCommand(commnand_replay);
    command_processor->saveCommand(commnand_quit);


     // Initializing all the game states.
    State start("start");
    State mapLoaded("mapLoaded");
    State mapValidated("mapValidated");
    State playersAdded("playersAdded");
    State assignReinforcement("assignReinforcement");
    State issueOrders("issueOrders");
    State executeOrders("executeOrders");
    State win("win");
    State end("end");


    // Defining transitions between game states based on commands.
    start.setTransition("loadmap",&mapLoaded);
    mapLoaded.setTransition("loadmap",&mapLoaded);
    mapLoaded.setTransition("validatemap",&mapValidated);
    mapValidated.setTransition("addplayer",&playersAdded);
    playersAdded.setTransition("addplayer",&playersAdded);
    playersAdded.setTransition("assigncountries",&assignReinforcement);
    assignReinforcement.setTransition("issueorder",&issueOrders);
    issueOrders.setTransition("issueorder",&issueOrders);
    issueOrders.setTransition("endissueorders",&executeOrders);
    executeOrders.setTransition("execorder",&executeOrders);
    executeOrders.setTransition("endexecorders",&assignReinforcement);
    executeOrders.setTransition("win",&win);
    win.setTransition("play",&start);
    win.setTransition("end",&end);


    // Creating the game engine and setting the starting state.
    GameEngine* risk = new GameEngine(&start);
    cout <<"Welcome to the start of the game!\n================================\n\n";
    // Game loop.

    risk->startupPhase(command_processor);


    int counter = 0;
    for(Player* p : risk->getGamePlayers()){
        switch (counter) {
            case 0:
                p->setStrategy(new HumanPlayerStrategy());
                break;
            case 1:
                p->setStrategy(new AggressivePlayerStrategy());
                break;
            case 2:
                p->setStrategy(new BenevolentPlayerStrategy());
                break;

            case 3:
                p->setStrategy(new CheaterPlayerStrategy());
                break;

            default:
                p->setStrategy(new NeutralPlayerStrategy());
                break;
        }

        counter++;
    }


    // Launching game
    risk->mainGameLoop();

    // Printing out the players and their strategies.
    for(Player* p : risk->getGamePlayers())
    {
        cout << "========================================================" << endl;
        cout << *p << endl;
        cout << "Strategy was: " << p->getPlayerStartegy()->getStrategyType() << endl;
        cout << "========================================================" << endl;
    }
}