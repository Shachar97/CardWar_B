#ifndef GAME_HPP
#define GAME_HPP
#include "player.hpp"
#include "card.hpp"
#include <array>
#include <vector>




namespace ariel{

    const int DECK_SIZE = 52;
    const int HALF_DECK = 26;
    const int FULL_SET = 13;
    const int NUM_TYPES = 4;

    /**
     * represent a cards-wor-game:
     * given two Players, the Class split deck (52) of Cards, each player get to his pile 26 cards
     * the winner of the game is the player hwo got the biggest pile of cards taken
     * the game save a log list of the turns and stats of the game.
    */
    class Game
    {
    private:

        Player &p1_;
        Player &p2_;
        
        /**
         * holds 52 a whole deck of  pointers-cards
        */
        vector <Card*> deck_list_;
        
        /**
         * holds strings of all the turns that exist in the game
        */
        vector <string> turns_;

        int currentTurn_;
        int drows_;
        
    public:
        /**
         * constructor of Game
         * each game should have two players
         * @param player1 first player
         * @param player2 second player
        */
        Game(Player &player1,Player &player2);

        /**
         * destructor of Game object
        */
        ~Game();

        
        Game(Game &game)=delete;
        Game operator =(Game &game)=delete;
        Game(Game &&game)=delete;
        Game operator = (Game &&game)=delete;

        /**
         * fill the deck_list with 52 different cards
        */
        void create_deck();

        /**
         * shuffle the cards in deck_list
        */
        void shuffle();

        /**
         * split the deck_list between the two players each one get 26 Cards
        */
        void splitDeck();

        /**
         * in each turn, the two players reveal the last card in theres pile,
         * the player with the bigger Card, win the turn.
         * in tie- both player put the next card unrevealed, and reveal the one after.
         * the player hwo won the turn get points for each card that had played (both, reveals and und reveals).
         * the played Cards in the turn, are destruct.
        */
        void playTurn();

        /**
         * print the last turn
         * for example- Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
         * 
        */
        void printLastTurn();

        /**
         * playes the game untill the end
        */
        void playAll(); 

        /**
         * prints the name of the winning player
        */
        void printWiner();

        /**
         * prints all the turns played one line per turn (same format as game.printLastTurn())
        */
        void printLog();

        /**
         * for each player prints basic statistics: 
         * win rate, cards won. Also print the draw rate and amount of draws that happand.
         * (draw within a draw counts as 2 draws. )
        */
        void printStats();

    };    
}
#endif