#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <ctime> // For random
#include <time.h>
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../Cards/Cards.h"
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

ostream& operator<<(ostream& out, const State* state){
	out << state->stateName << "\n";
	return out;
}


// -----------------------------------------
// ----- Implementation for GameEngine -----
// -----------------------------------------


// Constructor: Initializes the game engine with the provided start state.
GameEngine::GameEngine(State* startState) 
			: initialState(startState), currentState(startState), game_map(), list_of_Players() {

				game_deck = new Deck();
			}

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


void GameEngine::mainGameLoop(){


    // Phase 1


}



// This is part 2 of assignment #2
// startupPhase function calls the following game commands
/*
- loadmap
- validatemap
- addplayer
- gamestart (call draw() twice)
*/


void GameEngine::setMap(Map* map){this->game_map = map;}


void GameEngine::startupPhase(CommandProcessor* commandProcessor){

// 1) use the loadmap <filename> command to select a map from a list of map files as stored in a directory, 
// which results in the map being loaded in the game.

    for(Command* command: commandProcessor->getCommandList()){

		cout << "- Current game engine state: " << this->currentState << "\n" << endl;

		int num_extra_territories, min_territory_per_player;

		string map_name, map_file_path, new_player_name;
		MapLoader* loader;
		vector<Player*> playing_order;
		vector<Territory*> remaining_territories;


        switch (command->getCommandType()){

			case (commandType::loadmap):

				// check if the command is valid in the current game state
				if(commandProcessor->validate(command, this)){
					map_name = command->getCommandEffect();
					map_file_path = "../Map/Mapfiles/" + map_name;
					loader = new MapLoader(map_file_path);
					this->setMap(loader->loadMap());
				}
			

				break;

			case (commandType::validatemap) :

				if(commandProcessor->validate(command, this)){
					if(this->game_map->validate()){
						cout << command->getCommandEffect();
					}
					cout << "An invalid map was loaded\n\n";

				}else {
					cout << "The command validatemap"
						 << " cannot be executed in the current game engine state (" 
						 << this->getCurrentStateName() << ")\n\n";
				}
				break;

			case (commandType::addplayer) :

				if (commandProcessor->validate(command, this)) {
					while (list_of_Players.size() < 6) {
						if (list_of_Players.size() < 2) {
							// Should only contain the name of the player
							new_player_name = command->getCommandEffect();
							list_of_Players.push_back(new Player(new_player_name, new Hand()));
							cout << command->getCommandEffect() << " was successfully added to the game!\n\n";

							if (list_of_Players.size() < 2) {
								cout << "You still need " << 2 - list_of_Players.size() << " more player(s) to start the game.\n\n";
								cout << "Enter a player: ";
								cin >> new_player_name;
								command->setCommandEffect(new_player_name);
							} else {
								cout << "The game has enough players to start!\n\n";
							}
						} else {
							cout << "The current players are:\n";
							for (Player* p : list_of_Players) {
								cout << "- " << p->getName() << "\n";
							}

							cout << "Do you want to add more players? (y/n): ";
							char choice;
							cin >> choice;

							if (choice == 'y' || choice == 'Y') {
								// Should only contain the name of the player
								cout << "Enter a player: ";
								cin >> new_player_name;
								command->setCommandEffect(new_player_name);
								list_of_Players.push_back(new Player(new_player_name, new Hand()));
								cout << command->getCommandEffect() << " was successfully added to the game!\n\n";
							} else {
								cout << "The game is at full capacity ("
									<< list_of_Players.size() << " players).\n"
									<< command->getCommandEffect() << " couldn't be added to the game.\n\n";
								break;  // Exit the loop as the user doesn't want to add more players
							}
						}
					}
				}

				break;

			case (commandType::gamestart):
				cout << "\n\n\nPhase: gamestart\n\n\n";
				srand(time(NULL)); // Makes the random change every single run

				// a) distributing the territories to the players at random
				min_territory_per_player = floor(game_map->getTerritory().size() / list_of_Players.size());
				cout << "Min territories per player: " << min_territory_per_player << endl;

				num_extra_territories = game_map->getTerritory().size() % list_of_Players.size();

				remaining_territories = game_map->getTerritory();
				int random_territory_index, random_player_index;

				// Insert debug output here

				for (Player *p : list_of_Players)
				{
					for (int i = 0; i < min_territory_per_player; i++)
					{
						random_territory_index = rand() % remaining_territories.size();

						p->add_new_player_territory(remaining_territories.at(random_territory_index));

						remaining_territories.erase(remaining_territories.begin() + random_territory_index);
					}
				}


				// case 1): number territories > number players
				// case 2): number territories < number players
				random_player_index = rand() % list_of_Players.size();

				

				for (int i = 0; i < remaining_territories.size(); i++)
				{
					cout << remaining_territories.at(i);
					if (!remaining_territories.empty())
					{
						random_territory_index = rand() % remaining_territories.size();
						cout << "Random territory index for remaining territories: " << random_territory_index << endl;

						list_of_Players.at(random_player_index)->add_new_player_territory(remaining_territories.at(random_territory_index));
					}
				}

				// b) determine randomly the order of play of the players in the game
				// c) give 50 initial army units to the players, which are placed in their respective reinforcement pool

					
				for (Player* p : list_of_Players) {

					// Fix: Ensure the random_player_index is within the valid range
					if (!list_of_Players.empty()) {
						random_player_index = rand() % list_of_Players.size();

						if (random_player_index < 0 || random_player_index >= list_of_Players.size()) {
							cerr << "Error: Invalid random_player_index\n";
							exit(EXIT_FAILURE);
						}

						playing_order.push_back(list_of_Players.at(random_player_index));

						// Give each player 50 armies
						p->setReinforcementPool(50);
						cout << "- " << p->getName() << " is drawing:\n\n";
						p->getHand()->addCardToHand(game_deck->draw());
						p->getHand()->addCardToHand(game_deck->draw());
					}
				}



					 
				if(this->processCommand("assigncountries")){ // might be assigncountries don't forget to change
					cout << "\n\n\nPhase: play!\n\n\n";

				}
				break;

			
			case (commandType::replay):
				break;

			case (commandType::quit):
				break; 
        }
    
    } 


// 2) use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1).

    // This is an example of what to do. 
    // 1. Create a deck 
    // 2. Create a hand for each players
    // 3. Draw cards

    // Hand* hand = new Hand(size_of_hand); //Create an object hand
    // cout << "# of cards a player can have is: " << hand->getSize() << '\n';

    // for (int i =0; i <2; i++) { //draw two cards from deck
	// 	hand->addCardToHand(deck->draw());	//Draws and add the drawn card to the hand
	// 	cout << *deck << *hand;
	// }

}
































//////////////////////////////////////////////// erase ////////////////////////////////////////////OOOOOOOOOOOOOOOOOOOOOO
// void GameEngine::startupPhase(CommandProcessor* cp) {
// 	// Use the command list to get the commands, make sure to change states in between commands
// 	for (Command* c : cp->getCommandList()) {
// 		string command = c->getCommandStr();

// 		if (command == "loadmap") {
// 			// Load the map (how to parse the filename from the command?)
// 			string effect = c->getEffect();
// 			std::regex extractionPattern(".*(.*\\.map).*");
// 			std::smatch match;

// 		// 	// We found a map file name from the commmand's effect!
// 			if (std::regex_search(effect, match, extractionPattern)) {
// 				string mapFileName = "Assets/" + (string)match[1];
// 				setMap(MapLoader::createMapfromFile(mapFileName));
// 				changeState("validatemap");
// 			}
// 		}

// 		// Do I have to check if we are in a valid state before executing the command?
// 		else if (command == "validatemap") {
// 			// Validate the map
// 			map->validate();

// 			if (map->isValid()) {
// 				changeState("addplayer");
// 			}

// 			else {
// 				// Does the state go back to loadmap, or do we just fail and exit?
// 				cout << "An invalid map has been loaded." << endl;
// 			}
// 		}

// 		else if (command == "addplayer") {
// 			// Add player (This part should loop so as to ensure that we have 2-6 players in the game.)
// 			string effect = c->getEffect();

// 			std::regex extractionPattern("(.*) player has been added");
// 			std::smatch match;

// 			// Check to see if we have 2-6 players in the game

// 			if (players.size < 6) {
// 				if (std::regex_search(effect, match, extractionPattern)) {
// 					addPlayer(new Player(match[1], new Hand));
// 				}
// 			}

// 			else {
// 				// Let the user know that they cannot add anymore players
// 				cout << "Limit of players in game has been reached, no new players may be added." << endl;
// 			}


// 			if (players.size >= 2) {
// 				// Switch states
// 				changeState("gamestart");
// 			}

// 			else {
// 				// Let the user know that there needs to be more players for the game to start
// 			}
// 		}

// 		else if (command == "gamestart") {
// 			/* Gamestart command does the following:
// 			*  a) Evenly pass out territories to players (what happens when there aren't enough to go around?).

// 			*  b) Determine the order in which players get their turns (Randomly rearrange this class's Players list)

// 			*  c) Give 50 armies to each player, which are placed in their respective reinforcement pool (new Player field)

// 			*  d) Let each player draw 2 cards from the deck using Deck's draw() method (Call Player.getHand()->push_back(Deck.draw())?)

// 			*  e) Switch the game to the "play" state. (Call mainGameLoop())
// 			*/
			
// 			// Assign territories - TODO: Come up with a way to fairly distribute all countries between players
// 			for (Player* p : players) {

// 			}

// 			// Determine the turn order randomly - Re-arrange the players in the vector
			
// 			// Store randomly sorted arrangement of players
			

// 			// Initialize random seed
// 			srand(time(NULL));

// 			while (players.size() > 0) {
// 				// Generate a random number from 0 to the final index in the players vector
// 				int choose = rand() % (players.size() - 1);

// 				// Place randomly selected player in new vector
// 				tmp.push_back(players.at(choose));

// 				// Exclude newly placed player from next choice
// 				players.erase(players.begin()+choose);
// 			}

// 			// Reset players vector
// 			for (Player* player : tmp) {
// 				players.push_back(player);
// 			}

// 			// Give each player 50 armies to begin with and let them draw 2 cards from the deck
// 			for (Player* p : players) {
// 				p->setReinforcementPool(50);

// 				// TODO: I think the GameEngine needs its own deck?
				
// 			}

// 			// Switch the game to the play phase
// 			mainGameLoop();
// 		}
// 	}
// }
