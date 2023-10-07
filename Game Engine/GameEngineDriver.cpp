#include "GameEngine.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;
// Forward declaration of the test function.
void testGameStates();

int main(){
    // Starting the test function to simulate the game states.
   testGameStates();
    return 0;
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
