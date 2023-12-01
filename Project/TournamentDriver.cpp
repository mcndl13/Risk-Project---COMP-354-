#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>

void testTournament() {
    CommandProcessor commandProcessor;
    GameEngine gameEngine;

    std::string tournamentCommand = "tournament -M Map1,Map2 -P Aggressive,Benevolent -G 3 -D 20";

    if (commandProcessor.processTournamentCommand(tournamentCommand)) {
        // Extract parameters from the command
        std::vector<std::string> maps = {"Map1", "Map2"};
        std::vector<std::string> strategies = {"Aggressive", "Benevolent"};
        int numberOfGames = 3;
        int maxTurns = 20;

        // Execute the tournament
        gameEngine.executeTournament(maps, strategies, numberOfGames, maxTurns);

        // Output the tournament results
        // Assuming the results are stored and accessible
        gameEngine.outputTournamentResults();
    } else {
        std::cout << "Invalid tournament command." << std::endl;
    }
}

int main() {
    testTournament();
    return 0;
}
