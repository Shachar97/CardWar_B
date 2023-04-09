#include "player.hpp"
#include "game.hpp"
#include "card.hpp"

#include <iostream>
#include <exception>
#include <stdexcept>
#include <array>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

using namespace ariel;



// #define DEBUG


Game::Game(Player &p1,Player &p2):p1_(p1),p2_(p2),currentTurn_(0),drows_(0){
    create_deck();
    shuffle();
    splitDeck();
}

Game::~Game(){

    while(deck_list_.size() != 0){ //not all cads had split between the players

        Card* pcard = deck_list_.back(); 
        deck_list_.pop_back();
        delete pcard;
    }

    while(p1_.stacksize() != 0){//destruct p1 Cards
      
        delete p1_.pop_card();
    }
    while(p2_.stacksize() != 0 ){//destruc p2 Cards
       
        delete p2_.pop_card();
    }
    
 }


void Game::create_deck(){
    const std::string types[] = {"Hearts","Clubs","Diamonds","Spades"};
    for (size_t i = 1; i <= FULL_SET; i++){ //1-13
        for(size_t j=0; j<NUM_TYPES; j++){ // {"Hearts","Clubs","Diamonds","Spades"}

            deck_list_.push_back((new Card(i,types[j]))); //create card  in stack and hold his address in the vector.
        }
    }
}


void Game::shuffle(){// idea from https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    random_device rd;
    mt19937 rng(rd());
    std::shuffle(deck_list_.begin(), deck_list_.end(), rng);
}

void Game::splitDeck(){
    try{

        if(&p1_==&p2_){//split only if two players 
            throw runtime_error("Error! same player.\ntwo different players needed to play!\n");
        }
    
        #ifdef DEBUG
            cout << "in p1_: "<< endl << "[ ";
        #endif

        for(size_t i=0 ; i < HALF_DECK ; i++){ //first 26 cards in deck to p1
            Card* pcard = deck_list_.back();
            p1_.pushPile(pcard);
            #ifdef DEBUG
                cout << "("<< pcard->toString() << ") ";
            #endif
            deck_list_.pop_back();
        }

        #ifdef DEBUG
            cout << "]"<< endl << "in p2_:  "<< endl << "[ ";
        #endif

        for(size_t i=0 ; i < HALF_DECK ; i++){ ///last 26 cards in deck to p2
            Card* pcard = deck_list_.back();
            p2_.pushPile(pcard);
            #ifdef DEBUG
                cout << "("<< pcard->toString() << ") ";
            #endif
            deck_list_.pop_back();    
        }

        #ifdef DEBUG
            cout << "]"<< endl;
            cout << "num of cards in  p1 pile: " << p1_.stacksize() <<endl;
            cout << "num of cards in  p2 pile: " << p2_.stacksize() <<endl;
        #endif

    }catch(const std::exception& e){//if p1==p2
        cout << "Error: " << e.what() << endl;
    }
}

void Game::playTurn(){

     /*ERRORS*/
    if(&p1_==&p2_){//cant play with only one player
        throw runtime_error("Error! same player.\ntwo different players needed to play!\n");
    }
    if(p1_.stacksize()<=0){//the game is over
       
        throw runtime_error("ERROR! no card left in piles!\nthe game is over!\n");
    }

    /*else*/
    currentTurn_++;//for stats
    string thisTurn ="";//for log
    int jackpot=0; //the winner points

    Card* card_1 = p1_.pop_card(); //reveal p1 card
    Card* card_2 = p2_.pop_card();// reveal p2 card
    
    /*while Drow*/
    while(card_1->getNumber() == card_2->getNumber()){
        drows_++; // for stats
        jackpot += 2;

        /*LOG*/
        thisTurn += this->p1_.getName() + " played " + card_1->toString() + " ";
        thisTurn += this->p2_.getName() + " played " + card_2->toString() + ". Draw.";

        #ifdef DEBUG
            cout << endl;
            cout << "currentTurn: " << currentTurn_ << endl;
            cout << "thisTurn: '" << thisTurn <<"'"<< endl;
            cout << "jackpot: " << jackpot << endl;
        #endif

        /*release from memory*/
        delete card_1;
        delete card_2;

        //how to proceed:
        switch (p1_.stacksize()){

            case 0: /* split jackpot and finish the game */
                
                #ifdef DEBUG
                    cout << "in case 0: split jackpot and finish the game" << endl;
                #endif

                /*POINTS*/
                p1_.addToCardesTaken(jackpot/2);
                p2_.addToCardesTaken(jackpot/2);
                
                /*LOG*/
                turns_.push_back(thisTurn);

                return;

            case 1:/* not enough cards for playing Draw*/

                #ifdef DEBUG
                    cout << "in case 1: not enough cards for playing Draw" << endl;
                #endif

                /*release from memory*/
                delete p1_.pop_card(); //one card upside down
                delete p2_.pop_card(); //one card upside down

                jackpot+=2;

                /*POINTS*/
                p1_.addToCardesTaken(jackpot/2);
                p2_.addToCardesTaken(jackpot/2);
                
                /*LOG*/
                turns_.push_back(thisTurn);

                #ifdef DEBUG
                    cout << endl;
                    cout << "currentTurn: " << currentTurn_ << endl;
                    cout << "thisTurn: '" << thisTurn <<"'"<< endl;
                    cout << "jackpot: " << jackpot << endl;
                    cout << "p1 and p2 adding to cardstaken: " << jackpot/2 << endl;
                    cout << "p1 cardstaken: " << p1_.cardesTaken() << endl;
                    cout << "p2 cardstaken: " << p2_.cardesTaken() << endl;
                #endif

                return;

            default: /*playing Drow*/
                
                #ifdef DEBUG
                    cout << "in default: playing DRAW" << endl;
                #endif

                delete p1_.pop_card();          //one card upside down
                card_1 = p1_.pop_card(); //other card revealed
                delete p2_.pop_card();          //one card upside down
                card_2 = p2_.pop_card(); //other card revealed
                jackpot +=2; //only the upside down count
                break;
        }

    }

    /*there is a winner:*/

    jackpot += 2;

    /*LOG*/
    thisTurn += this->p1_.getName() + " played " + card_1->toString() + " ";
    thisTurn += this->p2_.getName() + " played " + card_2->toString() + ". ";
    

    if(card_1->getNumber() > card_2->getNumber()){
        thisTurn += p1_.getName() + " wins."; //for log
        p1_.addToCardesTaken(jackpot); //points
        p1_.incWins(); //for stats

        #ifdef DEBUG
            cout << endl;
            cout << "currentTurn: " << currentTurn_ << endl;
            cout << "thisTurn: '" << thisTurn <<"'"<< endl;
            cout << "jackpot: " << jackpot << endl;
            cout << "p1 adding to cardstaken: " << jackpot << endl;
            cout << "p1 cardstaken: " << p1_.cardesTaken() << endl;
            cout << "p2 cardstaken: " << p2_.cardesTaken() << endl;
        #endif

    }else{
        thisTurn += p2_.getName() + " wins."; //for log
        p2_.addToCardesTaken(jackpot); //points
        p2_.incWins(); //for stats
    
        #ifdef DEBUG
            cout << endl;
            cout << "currentTurn: " << currentTurn_ << endl;
            cout << "thisTurn: '" << thisTurn <<"'"<< endl;
            cout << "jackpot: " << jackpot << endl;
            cout << "p2 adding to cardstaken: " << jackpot << endl;
            cout << "p1 cardstaken: " << p1_.cardesTaken() << endl;
            cout << "p2 cardstaken: " << p2_.cardesTaken() << endl;
        #endif
    }

     /*LOG*/
    turns_.push_back(thisTurn);

    /*release from memory*/
    delete card_1;
    delete card_2;

    return;
}


void Game::printLastTurn(){
        /*ERRORS*/
        if(turns_.size()<=0){//no turns
            throw runtime_error("ERROR! the game hasn't started yet\n");
        }
        
        cout << turns_.back();
}

void Game::playAll(){//playes the game until the end
    while (p1_.stacksize()>0){
        playTurn();
    }
} 

void Game::printWiner(){// prints the name of the winning player
    
    if(deck_list_.size()!=0){
        throw runtime_error("ERROR! the game hasn't start yet\n");
    }
    try{
        if(p1_.stacksize()>0){
            throw runtime_error("ERROR! the game not over yet\n");
        }else if(p1_.cardesTaken()==p2_.cardesTaken()){
            throw runtime_error("ERROR! Draw, no winner!\n");
        }else if(p1_.cardesTaken()>p2_.cardesTaken()){//check hwo have more points:
            cout << p1_.getName() << " WON!" << endl;
        }else{
            cout << p2_.getName() << " WON!" << endl;
        }   
    }catch(const std::exception& e){//no winner
        cout << "Error: " << e.what() << endl;
    }
    
} 

void Game::printLog(){
    
    if(turns_.size()<=0){
        throw runtime_error("ERROR! the game hasn't started yet\n");
    }

    unsigned long current_turn =0;
    while (current_turn <turns_.size()){ // print all turns
        cout << "turn " << current_turn+1 << ": ";
        cout << turns_.at(current_turn) << endl;
        current_turn++;
    }
} 

void Game::printStats(){

    cout << "GAME STATS:" << endl;

    if(p1_.stacksize()== 0){
        cout <<"game  over, ";
        printWiner();
    }else{
        cout << "game on, ";
    }
    cout<< currentTurn_ << " rounds ";

    if(currentTurn_!=0){
        double drowRate = ((double)drows_*100)/(double)currentTurn_;

        printf("%f%% drows (%d\\%d)\n",drowRate,drows_,currentTurn_);
        
        cout << endl << "PLAYERS STATS:" << endl;
        cout << p1_.getName() << ":" << endl;
        double winRate = ((double)p1_.getWins()*100)/(double)currentTurn_;
        printf("%f%% wins (%d\\%d)\ncards won: %d\n",winRate,p1_.getWins(),currentTurn_,p1_.cardesTaken());
        

        cout << p2_.getName() << ":" << endl;
        winRate = ((double)p2_.getWins()*100)/(double)currentTurn_;
        printf("%f%% wins (%d\\%d)\ncards won: %d\n",winRate,p2_.getWins(),currentTurn_,p2_.cardesTaken());   
    }
}

