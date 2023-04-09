#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"

#include <string>
#include <vector>


using namespace std;

namespace ariel{
    
    /**
     * each Player object have string name,
     * in addition Player hold pile of cards (0-26),
     * int cardesTaken - represent winning points, 
     * and wins - represent amount of turns that the player win
    */
    class Player{
        private:

            string name_;

            /**
             * holds Cards pile (0-26)
            */
            vector <Card*> pile_;

            /**
             * num of cards in pile
            */
            int stacksize_;

            /**
             * num of win-points
            */
            int cardesTaken_;

            /**
             * increase in each turn the player win
            */
            double wins_;

            /**
             * +1 to stacksize
            */
            void incStacksize_();

            /**
             * -1 to stacksize
            */
            void decStacksize_();

        public:

            /**
             * constructor for Player object.
             * @param name string name of the player
            */
            Player(string name);

            /**
             * destructor for Player object
            */
            ~Player();

            /**
             * copy constructor
            */
            Player(Player &player );


            Player operator =(Player &player)=delete;
            Player(Player &&player)=delete;
            Player operator=(Player &&player)=delete;

            /**
             * @return amount of cards in pile
            */
            int stacksize() const;
            
            /**
             * @return amount of points
            */
            int cardesTaken() const;

            /**
             * return amount of wins
            */
            int getWins() const;

            /**
             * @return name of player
            */
            string getName() const;

            /**
             * 
             * @param sum add sum of int to the points
            */
            void addToCardesTaken(int sum);

            /**
             * +1 to wins
            */
            void incWins();

            /**
             * @param pointer_Card add to the end of the pile
            */
            void pushPile(Card *pcard);

            /**
             * remove last pointer card from the pile
             * @return the pointer Card that had removed
            */
            Card* pop_card();
        };
}
#endif