#include "player.hpp"
#include "game.hpp"
#include "card.hpp"
#include <string>
using namespace ariel;
using namespace std;

#define HALF_DECK 26

Player::Player(string name): name_(name),stacksize_(0),cardesTaken_(0),stack_pile_(create_pile_()){}

Player::~Player(){
    for (size_t i = 0; i < HALF_DECK; i++)
    {
        if (stack_pile_[i])
        {
            delete stack_pile_[i];
        }
        
    }
    
    delete[] stack_pile_;
}

Player::Player(Player &player): name_(player.name_),stacksize_(0),cardesTaken_(0),stack_pile_(create_pile_()){}
int Player::stacksize() const{
    return stacksize_;
}

Card** Player::create_pile_(){
    Card** pile = new Card*[HALF_DECK]; //need to destruct!
    for(size_t i = 0 ; i<HALF_DECK; i++){
        pile[i]=nullptr;
    }
    return pile;
}

int Player::cardesTaken() const{
    return cardesTaken_;
}

string Player::getName(){
    return name_;
}

Card** Player::getStackPile() const{
    return stack_pile_;
}

Card* Player::pop_card() {
    if(0/*pile is empty*/){
        /*throw error*/
        return nullptr;
    }
    else{
        int i = stacksize()-1; // i hold the pointer  last Card in the pile
        Card *popCard = stack_pile_[i];
        stack_pile_[i]=nullptr;
        decStacksize();
        return popCard;
    }
}

void Player::setStackPile(Card *c, int index) {
    stack_pile_[index]=c;
}

void Player::incStacksize(){
    stacksize_++;
}

void Player::decStacksize(){
    stacksize_--;
}

void Player::addToCardesTaken(int num){
    cardesTaken_+=num;
}