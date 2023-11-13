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
        std::cout << "Valid Command! Execution complete\n";
        return true;
    } else {
        std::cout << "Invalid Command! Try again...\n";
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

void GameEngine::re
inforcementPhase(){
    for(Player* player: list_of_players){
        int territoriesOwned = player->toDefend().size();
        int reinforcementUnits = std::max(3, territoriesOwned/3); // Minimum reinforcement rule

        //check and assign continent control bonuses
        for(Continent* continent: game_map->getContinents()){
            if(player->ownsAllTerritoriesInContinent(continent))
            {
                reinforcementUnits += continent->getControlValue(); // Add control bonus value
            }
        }

        player->AddReinforcementPool(reinforcementUnits); // Add to player's reinforcement pool
    }
}

void GameEngine::issueOrdersPhase(){
    bool allPLayersDone = false;
    while(!allPlayersDone){
        allPlayersDone = true;
        for(Player* player: list_of_players){
            if(player->hasReinforcements()){
                player->issueOrder("deploy"); // Player issues a deploy order
            } else{
                // Player decides to issue advance or other orders based on their strategy
                player->issueOrder("advance");
                
                // Check if the player wants to use a card
                if(player->hasCards()){
                    player->issueOrder("play card");
                }
            }

            allPlayersDone &= player->isDoneIssuingOrders(); // Check if all players are done
        }
    }
}

void GameEngine::executeOrdersPhase(){
    bool ordersPending = true;
    while(ordersPending){
        ordersPending = false;
        for(Player* player: list_of_Players){
            if(!player->getOrders().empty()){
                Order* order = player->getNextOrder(); // Get the next order
                if(order->validate()){
                    // Validate before execution
                    order->execute(); // Execute order
                }
                ordersPending = true; // Continue executing orders
            }
        }
    }
}

void GameEngine::removeInactivePlayers(){
    auto it = list_of_Players.begin();
    while(it != list_of_Players.end()){
        if((*it)->toDefend().empty()){
            it = list_of_Players.erase(it); // Remove players with no territories
        } else {
            ++it;
        }
    }
}

bool GameEngine::checkGameOver(){
    return list_of_Players.size() <= 1; // Game over when one or fewer players remain
}

void GameEngine::mainGameLoop(){
    while(!checkGameOver()){
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();
        removeInactivePlayers(); // Reset players' states to issue orders for next turn if needed

        for(Player* player: list_of_Players){
            player->resetForNextTurn();
        }
    }

    if(list_of_Players.size() == 1){
        std::cout<< list_of_Players.front()->getName()<< "wins the game!"<< std::endl;
    } else {
        std::cout<< "Game ended with no winners."<< std::endl;
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

}
