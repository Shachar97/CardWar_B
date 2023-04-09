#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using namespace std;

namespace ariel{

    
    /**
     * each Card object should have int number[13], and string type{"Hearts","Clubs","Diamonds","Spades"} 
    */
    class Card
    {
    private:
         
        int number_;
        string type_;
        
    public:
        
        /**
         * constructor of Card object
         * @param number should be between 1-13
         * @param type one of the strings: "Hearts","Clubs","Diamonds" or "Spades"
        */
        Card(int number, string type);

        /**
         * destructor of Card object
        */
        ~Card();

        /**
         * @return string represent the Card: for example: "Ace of Hearts" or "6 of Diamonds"
        */
        string toString();

        /**
         * @return int represent the number of the card object
        */
        int getNumber() const;

        Card(const Card &card)=delete;
        Card operator =(const Card &card)=delete;
        Card(Card &&card)=delete;
        Card operator = (Card &&)=delete ;

    };
    
}
#endif