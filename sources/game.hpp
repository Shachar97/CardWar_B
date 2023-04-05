#ifndef GAME_HPP
#define GAME_HPP
#include "player.hpp"
#include "card.hpp"

// using namespace ariel;
namespace ariel{
    typedef struct TURNS_LIST{
        string turnsList[26];
        int size;
    }turnsList;
    class Game
    {
    private:
        Player p1_;
        Player p2_;
        Card **deck_;
        turnsList turns_; 

    public:
        Game(Player player1,Player player2);
        ~Game();
        Game(Game &game)=delete;
        Game operator =(Game &game)=delete;
        Game(Game &&game)=delete;
        Game operator = (Game &&game)=delete;

        Card** create_deck();

        void shuffle();
        void splitDeck();

        Card** getDeck() const;
        
        void playTurn();
        void printLastTurn();
        void playAll(); //playes the game untill the end
        void printWiner(); // prints the name of the winning player
        void printLog(); // prints all the turns played one line per turn (same format as game.printLastTurn())
        void printStats();// for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )

    };    
}
#endif