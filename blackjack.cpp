/******************************************************************************
    blackjack.cpp
    Purpose: Create a CLI game of BlackJack
    Required Specifications:
    •   Dealer must hit on soft 17
    •   Single Deck. The deck is shuffled every 6 rounds.
    •   Player is not allowed to split cards.
    •   Keep track of win percentage for the player.
    @author Sefi Elbaz
    @version 1.0 9/13/18
*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <algorithm> // for random shuffle function
#include <string>
#include <thread> //for time delay so program does not
#include <chrono> //overload user with input at end game

using namespace std;

// function prototype declarations
vector<string> createDeck();
vector<string> dealCards(vector<string> &cards);
vector<string> hit(vector<string> &deck, vector<string> currentHand);
int computeHand(vector<string> handOfCards, char &soft17);
void delay (int delayTime);

int main()
{
    cout << "welcome to BlackJack" << endl;
    cout << "Good Luck!!" << endl;
    cout << ".------..------..------..------..------..------..------..------..------.\n"
            "|B.--. ||L.--. ||A.--. ||C.--. ||K.--. ||J.--. ||A.--. ||C.--. ||K.--. |\n"
            "| :(): || :/\\: || (\\/) || :/\\: || :/\\: || :(): || (\\/) || :/\\: || :/\\: |\n"
            "| ()() || (__) || :\\/: || :\\/: || :\\/: || ()() || :\\/: || :\\/: || :\\/: |\n"
            "| '--'B|| '--'L|| '--'A|| '--'C|| '--'K|| '--'J|| '--'A|| '--'C|| '--'K|\n"
            "`------'`------'`------'`------'`------'`------'`------'`------'`------'\n";
    cout << endl << endl;
    srand(time(NULL)); //seed random number
    int wins = 0;
    int losses = 0;
    int ties = 0;
    char soft17;
    int timeDelay = 2000;
    vector<string> playingDeck = createDeck();
    int numOfRounds = 1;
    char playAgain = 'Y';
    while (playAgain =='Y'){
        cout << "Round number: " << numOfRounds << endl;
        if (numOfRounds % 6 == 0){ //reshuffle deck every 6 rounds
            playingDeck = createDeck();
        }
        vector<string> playerHand = dealCards(playingDeck);
        cout << "Your hand is: " << endl;
        for (int i = 0; i < playerHand.size(); i++){
            cout << playerHand[i] << endl;
        }
        vector<string> dealerHand = dealCards(playingDeck);
        cout << "The Dealer's face up card is: " << endl;
        for (int i = 0; i < dealerHand.size() - 1; i++){ //only display dealers "face up" card
            cout << dealerHand[i] << endl;
        }
        cout << endl << endl;
        int playerHandValue = computeHand(playerHand, soft17);
        if (playerHandValue == 21) {
                    cout << "You have BlackJack!" << endl;
                }
        while (playerHandValue < 21) {
            char decision;
            cout << "Do you want to hit (h) or stay (s)? " << endl;
            cin >> decision;
            decision = toupper(decision);
            while (decision != 'H' && decision != 'S'){ //validate user input
                cout << "Invalid decision please use 'h' or 's' " << endl;
                cout << "Do you want to hit (h) or stay (s)? " << endl;
                cin >> decision;
            }
            if (decision == 'H'){
                playerHand = hit(playingDeck, playerHand);
                cout << "Player's new hand is: " << endl;
                for (int i = 0; i < playerHand.size(); i++){
                    cout << playerHand[i] << endl;
                }
                playerHandValue = computeHand(playerHand, soft17);
                if (playerHandValue == 21) {
                    cout << "You have BlackJack!" << endl;
                }
                if (playerHandValue > 21) {
                    cout << "You busted!" << endl;
                }
                }
            if (decision == 'S') {
                playerHandValue = computeHand(playerHand, soft17);
                if (playerHandValue == 21) {
                    cout << "You have BlackJack!" << endl;
                }
                cout << "You have a " << playerHandValue << endl;
                cout << "*******************" << endl;
                break;
                }
        }
        cout << endl << endl;
        delay(timeDelay); //slow down flow of game so user isnt overloaded with too much data at once
        cout << "The Dealer's hand is: " << endl;
        for (int i = 0; i < dealerHand.size(); i++){
            cout << dealerHand[i] << endl;
        }
        delay(timeDelay);
        int dealerHandValue = computeHand(dealerHand, soft17);
        delay(timeDelay);
        cout << "The Dealer's hand is: " << dealerHandValue << endl;
        while (dealerHandValue < 17) {
            cout << "The Dealer hits" << endl;
            dealerHand = hit(playingDeck, dealerHand);
            delay(timeDelay);
            dealerHandValue = computeHand(dealerHand, soft17);
            delay(timeDelay);
        }
        if (dealerHandValue == 17 && soft17 == 'Y') {
            dealerHand = hit(playingDeck, dealerHand);
            delay(timeDelay);
            dealerHandValue = computeHand(dealerHand, soft17);
            delay(timeDelay);
            while (dealerHandValue < 17) {
                cout << "The Dealer hits" << endl;
                dealerHand = hit(playingDeck, dealerHand);
                delay(timeDelay);
                dealerHandValue = computeHand(dealerHand, soft17);
                delay(timeDelay);
            }
        }
        if (dealerHandValue == 21) {
            cout << "The Dealer has BlackJack!" << endl;
        }
        if (dealerHandValue > 21) {
            cout << "The Dealer busts!" << endl;
        }
        if (playerHandValue <= 21 && dealerHandValue > 21) {
            cout << "You won! Good job!!" << endl;
            wins += 1;
        }
        else if (playerHandValue > dealerHandValue && playerHandValue <= 21) {
            cout << "You won! Good job!!" << endl;
            wins += 1;
        }
        else if (playerHandValue == dealerHandValue && playerHandValue <= 21) {
            cout << "Game is a tie" << endl;
            ties += 1;
        }
        else if (playerHandValue > 21 && dealerHandValue > 21) {
            cout << "Game is a tie" << endl;
            ties += 1;
        }
        else if (playerHandValue < dealerHandValue && dealerHandValue <= 21) {
            cout << "You lost the game - better luck next time!" << endl;
            losses += 1;
        }
        else if (playerHandValue > 21 && dealerHandValue <= 21) {
            cout << "You lost the game - better luck next time!" << endl;
            losses += 1;
        }
        cout << "This round is over" << endl;
        cout << "*******************" << endl;
        delay(timeDelay);
        cout << "You have won " << wins << " game(s)" << endl;
        cout << "You have lost " << losses << " game(s)" << endl;
        cout << "You have tied " << ties << " game(s)" << endl;
        double win_percentage = 100 * (static_cast<double>(wins) / (wins + losses + ties));
        cout << "Your win percentage is: " << win_percentage << "%" << endl;
        numOfRounds++;
        cout << "Do you want to play again? (y or n)" << endl;
        cin >> playAgain;
        playAgain = toupper(playAgain);
        while (playAgain != 'Y' && playAgain != 'N'){
                cout << "Invalid decision please use 'y' or 'n' " << endl;
                cout << "Do you want to play again? (y or n) " << endl;
                cin >> playAgain;
            }
        if (playAgain == 'N') {
            cout << "Thanks for playing BlackJack" << endl;
            cout << "Hope you had fun!" << endl;
            return 0;
        }
    }
    return 0;
}


vector<string> createDeck(){
/**
    Creates a single deck of 52 playing cards and shuffles it randomly
    @param none
    @return the shuffled deck of cards as a vector of strings
*/

// set up deck variables
    const int suitNum = 4;
    const int faceNum = 13;
    int cardNum = 0;
    string card ="";
// create labels for deck
    const string suits[] = {"Diamonds", "Spades", "Hearts", "Clubs"};
    const string face[] = {"2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
// create vector to store deck
    vector<string> deck;
//generate the deck
    for (int i = 0; i < suitNum; i++){
        for (int j = 0; j < faceNum; j++){
            card = face[j] + " of " + suits[i];
            deck.push_back(card);
            cardNum++;
            }
    }
// shuffle the deck
    random_shuffle(deck.begin(), deck.end());
    return deck;
}

vector<string> dealCards(vector<string> &deck) {
/**
    Deals two preshuffled cards to a player and deletes the dealt card from the vector
    @param the string vector representing the deck (by reference so each card is only dealt once) of cards to deal
    @return the dealt hand consisting of two cards as a vector of strings
*/

    vector <string> dealtHand;
    string dealtCard1 = deck.back();
    deck.erase(deck.end()); //erase the dealt card so it wont be dealt more than once
    string dealtCard2 = deck.back();
    deck.erase(deck.end());
    dealtHand.push_back(dealtCard1); //add the dealt card to player's hand
    dealtHand.push_back(dealtCard2);

    return dealtHand;
}

vector<string> hit(vector<string> &deck, vector<string> dealtHand) {
/**
    Deals and announces a single random card to a player every time it is called
    @param the string vector representing the deck (by reference so each card is only dealt once)
    @param the string vector representing the dealtHand to append the newly dealt card
    @return the dealt hand which now includes the hit card represented as a vector of strings
*/

    string hitCard = deck.back();
    cout << "The new card dealt is " << hitCard << endl;
    deck.erase(deck.end());
    dealtHand.push_back(hitCard);

    return dealtHand;
}

int computeHand(vector<string> handOfCards, char &soft17){
/**
    Computes a player's hand in terms of numerical value
    @param the string vector representing the player's hand of cards
    @param the char representing a soft 17 by reference so dealer can hit on it.
    @return an int representing the player's hand value
*/

    int handValue = 0;
    char hasAce;
    for (int i = 0; i < handOfCards.size(); i++) {
        string faceValue = handOfCards[i];
        string delimiter = " ";
        string token = faceValue.substr(0, faceValue.find(delimiter)); //tokenize face of card
        if (token == "Jack" || token == "Queen" || token == "King" ) { //compute value for J,Q,K,A face cards
            handValue += 10;
        }
        if (token == "Ace") {
            hasAce = 'Y';
            if (hasAce == 'Y' && (handValue + 11) > 21) { //count most recent Ace as a 1 if an 11 would bust the player
                handValue += 1;
                }
            else {
                handValue += 11;
        }
        }
        if (token == "2" || token == "3" || token == "4" || token == "5" || token == "6" || token == "7" || token == "8" || token == "9" || token == "10"){
            int i_dec = stoi(token); //if token is a number convert it to an int and compute numerical face cards
            switch(i_dec) {
                case 2:
                    handValue += 2;
                    break;
                case 3:
                    handValue += 3;
                    break;
                case 4:
                    handValue += 4;
                    break;
                case 5:
                    handValue += 5;
                    break;
                case 6:
                    handValue += 6;
                    break;
                case 7:
                    handValue += 7;
                    break;
                case 8:
                    handValue += 8;
                    break;
                case 9:
                    handValue += 9;
                    break;
                case 10:
                    handValue += 10;
                    break;
                }
                if (hasAce == 'Y' && handValue == 17) {
                    soft17 = 'Y';
                }
            }
    }
    if (hasAce && handValue > 21) { //count an old ace as a 1 if an 11 would bust the player
        handValue -= 10;
        }
    cout << "The hand value is: " << handValue << endl;
    return handValue;
}

void delay(int delayTime) {
/**
    Introduces a time delay so the dealer's turn does not occur faster than the user can keep up
    @param the int representing the time delay in milliseconds
    @return none
*/

    std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
}
