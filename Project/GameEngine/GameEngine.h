
class CommandProcessor;
class Deck;
#include "../Map/Map.h"
#include "../Player/Player.h"

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

        friend std::ostream& operator<<(std::ostream& out, const State*);


    private:
        // Name of the state.
        std::string stateName;
        
        // Mapping of commands to respective next states.
        std::map<std::string, State*> transitions;
};



// Class representing the game engine responsible for managing game states.
class GameEngine {

        std::vector<std::string> tournamentResults;

    public:
        GameEngine(State* startState); // Constructor initializes with a start state


        // Method to process a given command and change the current state accordingly.
        bool processCommand(std::string command);

        
        // Method to retrieve the name of the current state.
        std::string getCurrentStateName();

//////////////////// A3 PART 2/////////////////////////////////////

        // store tournament result for A3 Part 2
        void outputTournamentResults();
        // Method to execute the tournament- for A3
        void executeTournament(const std::vector<std::string>& maps, const std::vector<std::string>& strategies,int numberOfGames, int maxTurns);

        // Declare new methods for tournament mode- setupGame and playGame methods
        void setupGame(const std::string& map, const std::vector<std::string>& strategies);
        void playGame(int maxTurns);

///////////////////////////////////////////////////////////////////
        void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();
        void removeInactivePlayers();
        bool checkGameOver();

        void startupPhase(CommandProcessor*);
        void mainGameLoop();
        void setMap(Map* map);

        

    private:

        // Pointer to the current active state.
        State* currentState;
        // Pointer to the initial start state.
        State* initialState;

        Map* game_map;
        Deck* game_deck;
        std::vector<Player*> list_of_Players;


};
#endif // GAME_ENGINE_H
