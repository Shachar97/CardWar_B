#include "player.hpp"
#include "game.hpp"
#include "card.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

using namespace ariel;

#define DECK_SIZE 52
#define HALF_DECK 26
#define FULL_SET 13
#define NUM_TYPES 4


Game::Game(Player p1,Player p2):p1_(p1),p2_(p2),deck_(create_deck()){
    // turns_.turnsList[26];
    turns_.size=0;
}
Game::~Game(){
    //free the deck;
    for (size_t i = 0; i < DECK_SIZE; i++){//delete all cards in the list. [1]
        delete deck_[i];
        deck_[i]=nullptr;
    }
    delete[] deck_; //delete the list. [2]
    
}

Card** Game::create_deck(){

    Card** deck = new Card*[DECK_SIZE]; //need to destruct! [2]
    const string types[] = {"Hearts","Clubs","Diamonds","Spades"};
    for (size_t i = 1; i <= FULL_SET; i++)
    {
        for(size_t j=0; j<NUM_TYPES; j++){
            deck[(i-1)*NUM_TYPES +j]= new Card(i,types[j]); //need to destruct! [1]
        }
    }
    return deck;
}

/*shuffle the deck*/
void Game::shuffle(){
    random_device rd;
    mt19937 rng(rd());
    std::shuffle(deck_, deck_+DECK_SIZE, rng);
}

void Game::splitDeck(){
    for(size_t i=0 ; i < HALF_DECK ; i++){
        p1_.setStackPile( deck_[i] , i );
        p1_.incStacksize();
    }
    for(size_t i=0 ; i < HALF_DECK ; i++){
        p2_.setStackPile( deck_[HALF_DECK + i] , i );
        p2_.incStacksize();
    }
}

Card** Game::getDeck() const {
    return deck_;
}


void Game::playTurn(){
    if(p1_.stacksize()==0){
        /*error*/
        cout << "TODO throw, no card left" << endl;
        return;
    }
    string thisTurn ="";
    int jackpot=0;
    Card* card_1 = p1_.pop_card();
    Card* card_2 = p2_.pop_card();
    while(card_1->getNumber() == card_2->getNumber()){
        jackpot += 2;
        thisTurn += this->p1_.getName() + " played " + card_1->toString() + " ";
        thisTurn += this->p2_.getName() + " played " + card_2->toString() + ". Draw.";
        switch (p1_.stacksize())
        {
        case 0:
            /* split jackpot and finish the game */
            p1_.addToCardesTaken(jackpot/2);
            p2_.addToCardesTaken(jackpot/2);
            turns_.turnsList[turns_.size]=thisTurn;
            return;
        case 1:
            /* not enough cards for playing Drow*/

            p1_.pop_card(); //one card upside down
            p2_.pop_card(); //one card upside down
            jackpot+=2;

            p1_.addToCardesTaken(jackpot/2);
            p2_.addToCardesTaken(jackpot/2);
            turns_.turnsList[turns_.size]=thisTurn;
            return;
        default: /*playing Drow*/
            p1_.pop_card();          //one card upside down
            card_1 = p1_.pop_card(); //other card revealed
            p2_.pop_card();          //one card upside down
            card_2 = p2_.pop_card(); //other card revealed
            jackpot +=2; //only the upside down count (the revealed count somwer else )
            break;
        }

    }
    
    jackpot += 2;
    thisTurn += this->p1_.getName() + " played " + card_1->toString() + " ";
    thisTurn += this->p2_.getName() + " played " + card_2->toString() + ". ";

    if(card_1->getNumber() > card_2->getNumber()){
        thisTurn += p1_.getName() + " wins.";
        p1_.addToCardesTaken(jackpot);

    }else{
        thisTurn += p2_.getName() + " wins.";
        p2_.addToCardesTaken(jackpot/2);

    }
    turns_.turnsList[turns_.size]=thisTurn;
    turns_.size++;
    
    cout << "print playTurn" << endl;
    return;
}
void Game::printLastTurn(){// print the last turn stats. For example:
        // Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
        // Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
    cout << this->p1_.getName() + " played " + this->p1_.pop_card()->toString() + " ";
    cout << this->p2_.getName() + " played " + this->p2_.pop_card()->toString() + ". " << endl;
}

void Game::playAll(){//playes the game untill the end
    cout << "print playAll" << endl;
} 
void Game::printWiner(){// prints the name of the winning player
    cout << "print printWiner" << endl;
} 
void Game::printLog(){// prints all the turns played one line per turn (same format as game.printLastTurn())
    cout << "print printLog" << endl;
} 
void Game::printStats(){// for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
    cout << "print print Stats " << p1_.getName() << " " << p1_.cardesTaken() << " " <<p1_.stacksize() << " " << p2_.getName() << " " << p2_.cardesTaken() << " "  <<p2_.stacksize() << endl;
}
