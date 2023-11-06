#include "GameEngine.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

// -------------------------------------
// ----- Implementation for State ------
// -------------------------------------



// Default constructor: Initializes the state to "start".
State::State() {
    setStateName("start");
}

// Parameterized constructor: Initializes the state with a given name.
State::State(string name) {
    setStateName(name);
}
// Sets the name of the state.
void State::setStateName(string state) {
    stateName = state;
}
// Retrieves the name of the state.
string State::getStateName() {
    return stateName;
}
// Associates a command with a next state.
void State::setTransition(string command, State* nextState) {
    transitions[command] = nextState;
}
// Returns the next state associated with a given command, or nullptr if not found.
State* State::getTransition(string command) {
    if (transitions.find(command) != transitions.end()) {
        return transitions[command];
    }
    return nullptr;
}


// -----------------------------------------
// ----- Implementation for GameEngine -----
// -----------------------------------------


// Constructor: Initializes the game engine with the provided start state.
GameEngine::GameEngine(State* startState) : initialState(startState), currentState(startState) {}

// Processes the given command, moves to the next state if valid, and provides feedback.

bool GameEngine::processCommand(string command) {
    State* nextState = currentState->getTransition(command);

    if (nextState) {
        currentState = nextState;
        cout << "Valid Command! Execution complete\n";
        return true;
    } else {
        cout << "Invalid Command! Try again...\n";
        return false;
    }
}
// Returns the name of the current state, or "Unknown State..." if not set.
string GameEngine::getCurrentStateName() {
    if (currentState) {
        return currentState->getStateName();
    } else {
        return "Unknown State...";
    }
}

// ---------------------------------------
// ----- Implementation for Command ------
// ---------------------------------------


// Default constructor.
Command::Command() {}

// Sets the name of the command.
void Command::setCommandName(string command) {
    commandName = command;
}
// Retrieves the name of the command.
string Command::getCommandName() {
    return commandName;
}

// This is part 2 of assignment #2
// startupPhase function calls the following game commands
/*
- loadmap
- validatemap
- addplayer
- gamestart (call draw() twice)

*/
void GameEngine::startupPhase(const vector<string>& mapFiles){

    MapLoader::loadmap();


    // This is an example of what to do. 
    // 1. Create a deck 
    // 2. Create a hand for each players
    // 3. Draw cards
    Hand* hand = new Hand(size_of_hand); //Create an object hand
    cout << "# of cards a player can have is: " << hand->getSize() << '\n';
    
    for (int i =0; i <2; i++) { //draw two cards from deck
		hand->addCardToHand(deck->draw());	//Draws and add the drawn card to the hand
		cout << *deck << *hand;
	}

}
