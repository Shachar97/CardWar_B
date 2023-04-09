#include "player.hpp"
#include "game.hpp"
#include "card.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <array>

using namespace ariel;
using namespace std;


Card::Card(int number, string type) : number_(number), type_(type){}
    
Card::~Card(){}

string Card::toString(){
    switch (this->number_)
    {
    case 1:
        return "Ace of " + this->type_;
    case 11:
        return "Jack of " + this->type_;
        
    case 12:
        return "Qween of " + this->type_;
        
    case 13:
        return "King of " + this->type_;
        
    default:
         return std::to_string(this->number_) + " of " + this->type_;
    }
}
int Card::getNumber()const { 
    return number_;
}
