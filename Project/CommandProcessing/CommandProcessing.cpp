#include <iostream>
#include <string>
#include <vector>
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"


//=================== Command class =======================
    Command::Command(){
        command_effect = "Effect no set";
        command_string = "Command not set";
    }

    // Constructor
    Command::Command(commandType command){

        command_effect = "Effect no set";

        switch (command){

            case commandType::loadmap:
                this->command_string = "loadmap";
                this->command_type = commandType::loadmap;
                break;

            case commandType::validatemap:
                this->command_string = "validatemap";
                this->command_type = commandType::validatemap;
                break;
        
            case commandType::addplayer:
                this->command_string = "addplayer";
                this->command_type = commandType::addplayer;
                break;

            case commandType::gamestart:
                this->command_string = "gamestart";
                this->command_type = commandType::gamestart;
                break;
        

            case commandType::replay:
                this->command_string = "replay";
                this->command_type = commandType::replay;
                break;

            case commandType::quit:
                this->command_string = "quit";
                this->command_type = commandType::quit;
                break;
        
            default:
                this->command_string = "quit";
                break;
        }
    }




    // Getters and setters
    string Command::getCommand(){return command_string;}
    string Command::getCommandEffect(){return command_effect;}
    int Command::get_id(){return id;}
    commandType Command::getCommandType (){return this->command_type;}
    void Command::setCommand(string command){command_string = command;}
    void Command::setCommandEffect(string command_eff){command_effect = command_eff;}



//=================== CommandProcessor class =======================

    // Temporary functions
    CommandProcessor::CommandProcessor(): list_of_commands(){}

    CommandProcessor::~CommandProcessor() {
    }

    vector<Command*> CommandProcessor::getCommandList() {return list_of_commands;}


    // Gets commands from the console as a string
    Command* CommandProcessor::readCommand(){

        cout << "Command List:\n===================\n"
             << "1. loadmap\n2. validatemap\n3. addplayer\n4. gamestart\n5. replay\n6. quit"
             << "Write the number associated to the command you wish to create: ";


        int  console_id;
        cin >> console_id;

        if (console_id == 1)
            return new Command(commandType::loadmap);

        else if (console_id ==2)
            return new Command(commandType::validatemap);

        else if (console_id == 3)
            return new Command(commandType::addplayer);

        else if (console_id == 4)
            return new Command(commandType::gamestart);

        else if (console_id == 5)
            return new Command(commandType::replay);

        else if (console_id == 6)
            return new Command(commandType::quit);

        else
            return new Command();
    }


// Change valide states

// The command processor should have a validate() method that can be called to 
// check if the command is valid in the current game state. If the command is not valid, a corresponding error 
// message should be saved in the effect of the command
    bool CommandProcessor::validate(Command* newCommand, GameEngine* risk){

        // Gets a string command from a command and passes that as a tring to the gameEngine
        if(risk->processCommand(newCommand->getCommand())){

            if (newCommand->getCommandType() == commandType::loadmap){
                string map;
                cout << "loadmap is being executed from CommandProcessor::validate()\n"
                     << "What map do you want to load: ";
                cin >> map;

                // e.g "loadmap" -> "3D Cliff.mp"
                newCommand->setCommand(map);
                newCommand->saveEffect(newCommand, map);

                return true;
            }

            // else if (newCommand->getCommand() =="validatemap"){}

            else if (newCommand->getCommandType() == commandType::addplayer){
                string player_name;
                cout << "addplayer is being executed from CommandProcessor::validate()\n"
                     << "Enter the name of the new player: ";
                cin >> player_name;

                // e.g "addplayer" -> "Marvin"
                newCommand->setCommand(player_name);
                newCommand->saveEffect(newCommand, player_name);

                return true;
            }

            // else if (newCommand->getCommand() =="gamestart")
            // else if (newCommand->getCommand() =="replay")

            else if (newCommand->getCommandType() == commandType::quit){
                cout << "quit is being executed from CommandProcessor::validate()\n"
                     << "Quiting the game!" << endl;
                     exit(0);
            }
            return false;
        }
        return false;
    }


    void Command::saveEffect(Command* command, string info) {
        switch (command->getCommandType()) {

        case commandType::loadmap :
            command->command_effect = info;
            break;
        case commandType::validatemap :
            command->command_effect = info + " has been validated";
            break;
        case commandType::addplayer :
            command->command_effect = info;
            break;
        case commandType::gamestart :
            command->command_effect = "The game has started";
            break;
        case commandType::replay :
            command->command_effect = "Replaying the game";
            break;
        case commandType::quit :
            command->command_effect = "Quitting the game";
            break;
        }
    }



    void CommandProcessor::getCommand(GameEngine* game_engine){

        Command* new_command = readCommand();

        // Compares new command and next game_engine command
        if (validate(new_command, game_engine)){

            // After validation saves the command to the commandprocessor
            this->saveCommand(new_command);
        }
    }


    void CommandProcessor::saveCommand(Command* new_command){
        list_of_commands.push_back(new_command);
    }






