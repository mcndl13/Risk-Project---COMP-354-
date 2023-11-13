#include <iostream>
#include "CommandProcessing.h"


// (1) commands can be read from the console using the CommandProcessor class 
// (2) commands can be read from a saved text file using the FileCommandProcessorAdapter class
// (3) commands that are invalid in the current game state are rejected, and valid commands result in the correct effect and state change.
void testCommandProcessor(){
    GameEngine engine();

    CommandProcessor* command_processor = new CommandProcessor();

    Command* commnand_validatemap = new Command(commandType::validatemap);
    Command* commnand_addplayer = new Command(commandType::addplayer);
    Command* commnand_gamestart = new Command(commandType::gamestart);
    Command* commnand_replay = new Command(commandType::replay);
    Command* commnand_quit = new Command(commandType::quit);
}






int main(int argc, char const *argv[])
{
    testCommandProcessor();
    
    return 0;
}