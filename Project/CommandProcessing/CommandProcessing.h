#pragma once
#include <string>
#include <vector>
#include "../Player/Player.h"
#include <fstream>
using namespace std;

class GameEngine;
class Command;

enum class commandType { loadmap, validatemap, addplayer, gamestart, replay, quit};


class CommandProcessor {

    private:
        // Gets commands from the console as a string
        Command* readCommand();
        vector<Command*> list_of_commands;

        
        
    public:
        CommandProcessor();
        ~CommandProcessor();


    // Methods

        vector<Command*> getCommandList();

        // Stores command in a collection of commands objects --> use a vector
        void saveCommand(Command*);

        bool validate(Command *newCommand, GameEngine *risk);

        // Returns a Command, should be used with Player and GameEngine objects
        void getCommand(GameEngine* game_engine);
        void getCommand(Player* game_engine);

        // Method to process the tournament command
        bool processTournamentCommand(const std::string& command);
};


class Command{

    private:
        string command_effect;
        string command_string;
        commandType command_type;
        int id;

    public:
        
        Command();
        Command(commandType);
        
        // A command's effect description (string) saved onto Command object
        void saveEffect();

        string getCommand();
        string getCommandEffect();
        int get_id();
        commandType getCommandType ();

        void setCommand(string);
        void setCommandEffect(string);
        void saveEffect(Command *command, string toAdd);
};

class FileCommandProcessorAdapter{

private:
    FileLineReader fileLineReader;
    std::vector<Command*> commands;
    GameEngine* gameEngine; // Reference to the game engine for validation

public:
    FileCommandProcessorAdapter(const std::string& filePath, GameEngine* ge);
    ~FileCommandProcessorAdapter();

    void saveCommand();
    Command* getCommand();
    bool validate(Command* command);


};
class FileLineReader{

public:
private:
    ifstream fileStream;

public:
    FileLineReader(const std::string& filePath);
    ~FileLineReader();

    std::string readFileLine();

};
