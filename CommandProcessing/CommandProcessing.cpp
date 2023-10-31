#include <iostream>
#include <string>
#include <vector>
#include "CommandProcessing.h"



// class CommandProcessor

// Temporary functions
    CommandProcessor::CommandProcessor(/* args */){
    }

    CommandProcessor::~CommandProcessor() {
    }


    // Gets commands from the console as a string
    string CommandProcessor::readCommand(){

        string console_command;
        cin >> console_command;
        return console_command;
    }



    // Stores command in a collection of commands objects --> use a vector
    void CommandProcessor::saveCommand(string temp_command){

        list_of_commands.push_back(new Command(temp_command));
    }



    Command* CommandProcessor::getCommand(){



    }



    bool CommandProcessor::validate(){

    }

