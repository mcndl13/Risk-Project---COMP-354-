#ifndef HEADER_NAME_H
#define HEADER_NAME_H

#include <string>
#include <map>
#include <iostream>
// Class to represent a state in the game.
class State {
public:
    State(); // Default constructor with "start" state
    State(std::string name); //  Parameterized constructor to initialize a named state.
    // Setter and Getter for the state name.
    void setStateName(std::string state);
    std::string getStateName();
    // Method to set a transition from the current state based on a command.
    void setTransition(std::string command, State* nextState);
    // Method to retrieve the next state based on a given command.
    State* getTransition(std::string command);

private:
    // Name of the state.
    std::string stateName;
    // Mapping of commands to respective next states.
    std::map<std::string, State*> transitions;
};
// Class representing the game engine responsible for managing game states.
class GameEngine {
public:
    GameEngine(State* startState); // Constructor initializes with a start state
    // Method to process a given command and change the current state accordingly.
    bool processCommand(std::string command);
    // Method to retrieve the name of the current state.
    std::string getCurrentStateName();

private:
    // Pointer to the current active state.
    State* currentState;
    // Pointer to the initial start state.
    State* initialState;
};
// Class to represent commands.
class Command {
public:
    Command();// Default constructor.
    // Setter and Getter for the command name.
    void setCommandName(std::string command);
    std::string getCommandName();

private:
    // Name of the command.
    std::string commandName;
};

#endif // GAME_ENGINE_H