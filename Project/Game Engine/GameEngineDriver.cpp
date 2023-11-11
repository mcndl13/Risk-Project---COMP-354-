#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

// g++ -std=c++17 -o p2  ../Player/Player.cpp GameEngineDriver.cpp ../Map/Map.cpp ../Cards/Cards.cpp ../Orders/Orders.cpp ../GameEngine/GameEngine.cpp ../CommandProcessing/CommandProcessing.cpp

// Used to run the code: g++ -std=c++17 GameEngine.cpp GameEngineDriver.cpp

// Forward declaration of the test function.
void testGameStates();
void testStartupPhase();

int main(){
    // Starting the test function to simulate the game states.
//    testGameStates();
   testStartupPhase();
    return 0;
}

void testStartupPhase(){

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
    GameEngine risk(&start);
    cout <<"Welcome to the start of the game!\n================================\n\n";
    // Game loop.

    risk.startupPhase(command_processor);

}






void testGameStates(){

    
   // Flag to check if the game is ongoing or not.
    bool continuePlaying = true;
    string command;


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
    GameEngine risk(&start);
    cout <<"Welcome to the start of the game!\n";
    // Game loop.
    while(continuePlaying){
    cout << "Current state: " << risk.getCurrentStateName()<<endl;
     // Check if the game has ended.
    if(risk.getCurrentStateName()=="end"){
        continuePlaying=false;
        break;
    }
    // Prompt the user for a command to transition between states.
     cout <<"Enter Command: ";
     cin >> command;
    // If user inputs command to exit,quit the game.
    if(command=="exit"){
        continuePlaying=false;
        break;
    }
    else{
          // Process the user's command.
        risk.processCommand(command);
        if(risk.getCurrentStateName()=="win"){
            cout <<"Congratulations, you win!" <<endl;
            
        }
    }
  }
    // Game over message.
   cout <<"Thanks for playing :)";
};
