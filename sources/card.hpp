#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using namespace std;

namespace ariel{
    class Card
    {
    private:
         
        int number_;
        string type_;
        
    public:
        Card(int number, string type);
        ~Card();

        string toString();

        Card(const Card &card)=delete;
        Card operator =(const Card &card)=delete;
        Card(Card &&card)=delete;
        Card operator = (Card &&)=delete ;

        int getNumber() const;
    };
    
}
#endif