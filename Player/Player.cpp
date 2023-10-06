#include <iostream>
#include "Player.h"

Player::Player(const std::string& playerName) : name(playerName) {
    return playerName;
}

void Player::toDefend() {
    return owned_territories;
}

void Player::toAttack() {
    return enemy_territories;
}

void Player::issueOrder(OrderList* order) {
    orders.push_back(order);
}
