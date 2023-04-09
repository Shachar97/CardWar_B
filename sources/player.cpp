#include "player.hpp"
#include "game.hpp"
#include "card.hpp"

#include <iostream>
#include <string>
#include <array>
#include <vector>

#include <stdexcept>

using namespace ariel;
using namespace std;



Player::Player(string name): name_(name),stacksize_(0),cardesTaken_(0), wins_(0){}


Player::~Player(){
}

Player::Player(Player &player): name_(player.name_),stacksize_(0),cardesTaken_(0){}

int Player::stacksize() const{
    return stacksize_;
} 

int Player::getWins() const{
    return wins_;
}

void Player::incWins(){
    wins_++;
}

int Player::cardesTaken() const{
    return cardesTaken_;
}

string Player::getName() const{
    return name_;
}



Card* Player::pop_card() {
    try
    {
        if(pile_.size()==0){
            /*error*/
            throw out_of_range("pile is empty");
        }
        else{
            Card * pop_card = pile_.back();
            pile_.pop_back();
            decStacksize_();

            return pop_card;
        }
    }
    catch(const std::exception& e){//pile is empty
        cout << "Error: " << e.what() << endl;
        return nullptr;
    }
}


void Player::pushPile(Card *pcard) {
    try
    {
        if(pile_.size()>=26){
            throw runtime_error("pile is full");
        }
        if(!pcard){
            throw runtime_error("trying to push null card to the pile");
        
        }else{
            pile_.push_back(pcard);
            incStacksize_();
        }
    }
    catch(const std::exception& e){ //pile is full
        cout << "Error: " << e.what() << endl;
    }  
}

void Player::incStacksize_(){
    stacksize_++;
}

void Player::decStacksize_(){
    stacksize_--;
}

void Player::addToCardesTaken(int num){
    cardesTaken_+=num;
}