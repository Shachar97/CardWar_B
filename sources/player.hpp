#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"

#include <string>

using namespace std;

namespace ariel{
    
    class Player{
        private:
            string name_;
            Card** stack_pile_;
            int stacksize_, cardesTaken_;

            Card** create_pile_();
        public:
            Player(string name);
            ~Player();
            Player(Player &player );
            Player operator =(Player &player)=delete;
            Player(Player &&player)=delete;
            Player operator=(Player &&player)=delete;


            int stacksize() const;
            int cardesTaken() const;

            string getName();
            Card** getStackPile() const;

            void incStacksize();
            void decStacksize();

            void addToCardesTaken(int);
            
            void setStackPile(Card *c, int index);
            Card* pop_card();
        };
}
#endif