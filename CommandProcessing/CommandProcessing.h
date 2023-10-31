#pragma once
#include <string>
#include <vector>

using namespace std;


class CommandProcessor {

private:
    // Gets commands from the console as a string
    string readCommand();
    vector<Command*> list_of_commands;
    
    
public:
    CommandProcessor();
    ~CommandProcessor();


// Methods

    // Stores command in a collection of commands objects --> use a vector
    void saveCommand(string);


    // Returns a Command, should be used with Player and GameEngine objects
    Command* getCommand();



    // Checks if the command is valid
    bool validate();
};




class Command{

    private:
        string command_effect;
        string command;

    public:
        Command();
        Command(string command);
        
        // A command's effect description (string) saved onto Command object
        void saveEffect();
};





class FileCommandProcessorAdapter{


    private:
        FileLineReader flr;

    public:
    // Methods    
        void saveCommand();
        
        Command* getCommand();

        bool validate();
};



class FileLineReader{


    public:
        string readFileFromLine();


};