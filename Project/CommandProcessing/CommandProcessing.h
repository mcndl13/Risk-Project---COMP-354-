#pragma once
#include <string>
#include <vector>
#include "../Player/Player.h"

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



        // Checks if the command is valid
        bool validate();
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

// class FileCommandProcessorAdapter{


//     private:
//         FileLineReader flr;

//     public:
//     // Methods    
//         void saveCommand();
        
//         Command* getCommand();

//         bool validate();
// };



// class FileLineReader{


//     public:
//         string readFileFromLine();


// };