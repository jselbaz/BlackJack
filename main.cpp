#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<string> createDeck();
vector<string> dealCards(vector<string> &cards);
vector<string> hit(vector<string> deck, vector<string> currentHand);
int computeHand(vector<string> handOfCards);
string declareWinner(int playerHandValue, int dealerHandValue);

int main()
{
    srand(time(NULL)); //seed random number

    cout << "welcome to BlackJack" << endl;
    cout << "Good Luck!!" << endl;
    cout << "**********************" << endl;

    vector<string> playingDeck = createDeck();
    vector<string> playerHand = dealCards(playingDeck);
    cout << "Your hand is: " << endl;
    for (int i = 0; i < playerHand.size(); i++){
        cout << playerHand[i] << endl;
    }
    vector<string> dealerHand = dealCards(playingDeck);
    cout << "The dealer's hand is: " << endl;
    for (int i = 0; i < dealerHand.size() - 1; i++){
        cout << dealerHand[i] << endl;
    }

    int playerHandValue = computeHand(playerHand);
    if (playerHandValue == 21) {
        cout << "You have BlackJack!";
    }
    while (playerHandValue < 21) {
        char decision;
        cout << "Do you want to hit (h) or stay (s)? " << endl;
        cin >> decision;
        decision = toupper(decision);
        while (decision != 'H' && decision != 'S'){
            cout << "Invalid decision please use 'h' or 's' " << endl;
            cout << "Do you want to hit (h) or stay (s)? " << endl;
            cin >> decision;
        }
        if (decision == 'H'){
            playerHand = hit(playingDeck, playerHand);
            cout << "Players new hand is: " << endl;
            for (int i = 0; i < playerHand.size(); i++){
                cout << playerHand[i] << endl;
            }
            playerHandValue = computeHand(playerHand);
            if (playerHandValue > 21) {
                cout << "You busted!" << endl;
            }
            }
        if (decision == 'S') {
            playerHandValue = computeHand(playerHand);
            cout << "You have a " << playerHandValue << endl;
            break;
            }
    }
    for (int i = 0; i < dealerHand.size(); i++){
        cout << "The dealer's hand is: " << endl;
        cout << dealerHand[i] << endl;
    }
    int dealerHandValue = computeHand(dealerHand);
    cout << "The dealer's hand is: " << dealerHandValue << endl;
    if (dealerHandValue == 21) {
        cout << "The Dealer has BlackJack!" << endl;
    }
    if (dealerHandValue < 17) {
        dealerHand = hit(playingDeck, dealerHand);
    }
    if (dealerHandValue > 21) {
        cout << "The dealer busts!" << endl;
    }

    declareWinner(playerHandValue, dealerHandValue);

    //dealer must hit on soft 17 (ace + 6 or ace + 3 + 3)
    //play again
    //reshuffle deck every 6 rounds


    return 0;
}


vector<string> createDeck(){

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

    vector <string> dealtHand;
    string dealtCard1 = deck.back();
    deck.erase(deck.end());
    string dealtCard2 = deck.back();
    deck.erase(deck.end());
    dealtHand.push_back(dealtCard1);
    dealtHand.push_back(dealtCard2);

    return dealtHand;
}

vector<string> hit(vector<string> deck, vector<string> dealtHand) {

    string hitCard = deck.back();
    cout << "Your new card is " << hitCard << endl;
    deck.erase(deck.end());
    dealtHand.push_back(hitCard);

    return dealtHand;
}

int computeHand(vector<string> handOfCards){
    int handValue=0;
    for (int i = 0; i < handOfCards.size(); i++) {
        string faceValue = handOfCards[i];
        string delimiter = " ";
        string token = faceValue.substr(0, faceValue.find(delimiter));
        cout << token <<endl;
        if (token == "Jack" || token == "Queen" || token == "King" ) {
            handValue += 10;
            cout << handValue << endl;
        }
        if (token == "Ace") {
            handValue += 11;
            cout << handValue << endl;
        } else {
            int i_dec = stoi(token);
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
            }
    }
    cout << handValue << endl;
    return handValue;
}

string declareWinner(int playerHandValue, int dealerHandValue) {
    int wins = 0;
    int losses = 0;
    int ties = 0;
    if (playerHandValue == dealerHandValue) {
        cout << "Game is a tie" << endl;
        ties += 1;
    }
    if (playerHandValue < dealerHandValue) {
        cout << "You lost the game - better luck next time!" << endl;
        losses += 1;
    }
    if (playerHandValue > dealerHandValue) {
        cout << "You won! Good job!!" << endl;
        wins += 1;
    }
    cout << "You have won " << wins << " game(s)" << endl;
    cout << "You have lost " << losses << " game(s)" << endl;
    cout << "You have tied " << ties << " game(s)" << endl;
    double win_percentage = static_cast<double>(wins) / (wins + losses + ties);
    cout << "Your win percentage is: " << win_percentage << endl;
}
