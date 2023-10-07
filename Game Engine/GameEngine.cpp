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