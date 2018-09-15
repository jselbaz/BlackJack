# Blackjack

A CLI based game of BlackJack in C++
README

I. File List
-------------------
bin/Debug
obj/Debug
Blackjack.cbp
Blackjack.depend
README.md
Blackjack.cpp

Program can be built using default make arguments.
Program written and built using CodeBlocks 17.12 on Windows 7 using GCC.


II. Design
-------------------
Game Requirements:
•   Dealer must hit on soft 17
•   Single Deck. The deck is shuffled every 6 rounds.
•   Player is not allowed to split cards.
•   Keep track of win percentage for the player.
•   Provide a readme file explaining how to compile the source and other info that might be interesting.

You don't have to implement any AI other than the one mentioned above - it's just one player vs. dealer.
If any third party code is used, please give credit and cite source.

A. Program Overview
The rules of Blackjack are listed here: https://www.bicyclecards.com/how-to-play/blackjack/
This program will be a simpler version of one player against the dealer. There is only a single deck used and no 
splitting.

B. Program Design
I chose to program this game procedurally. I wrote functions: to create a deck, deal cards, hit for a card, to 
compute the user's and dealer's hands, and to introduce a time delay for game flow purposes.
The main program will initialize all necessary variables, seed the random number, and initialize play.
The user and dealer will be dealt two cards and then the player will begin their turn.
The player will hit by calling the appropriate function until they bust or until they choose to stay.
After the player's turn the dealer's second card will be flipped face up and his turn will begin.
At the end of the dealer's turn the game will announce a winner and present the stats.
It will then ask the player if they want to play another round. 
If yes it will repeat the above process. If not it the program will end.

C. Potential future improvements
	I. Coding a GUI for the interface
	II. Programming this as an Object Oriented program
	III. Make it more modular
	IV. Abstract the data more

III. Credit
A. ASCII generator used: http://patorjk.com/software/taag

