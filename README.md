# omahaPoker
Program that evaluates the winner of a 2-player Omaha-High Hold’em poker game (also known as pot-limit Omaha).


High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
The cards are valued in the order:

2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of fives (see example 1 below). But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are compared (see example 4 below); if the highest cards tie then the next highest cards are compared, and so on.

A more elaborate description of poker hand rankings can be found here: http://www.pokerlistings.com/poker-hand-ranking

# **2	Goal**
The goal of this project is to write a program that given the hands of 2 players and the community cards, evaluates the winner.

|**Hand**|**Player 1**|**Player 2**|**Community**|<p>**Expected**</p><p>**Output**</p>|**Reason**|
| - | :-: | :-: | :-: | :-: | :-: |
|1|8H AS 3S 3H|TH AD 8D 9C|2C 9S JH 4D 5S|Player 1 wins|straight Five Four Three Two Ace beats two Nines Ace Jack Five|
|2|TC QC 9D 6S|5C 2S 6C 6H|6D TH JD 3S KH|Player 1 wins|<p>straight King Queen Jack Ten Nine beats</p><p>three of a kind Sixs with King Jack</p>|
|3|7S 3H 5D 3S|KH 5C KS 9C|AH 5S 4C TH 7C|Player 2 wins|<p>two Kings Ace Ten Seven beats</p><p>two Sevens two Fives Ace</p>|
|4|7D 5D 9H KS|7S 6H 3S 6D|TH 2S 7C 4D QD|Player 1 wins|<p>two Sevens King Queen Ten beats</p><p>two Sevens Queen Ten Six</p>|
|5|7H KC JD 7C|6D AD TH KD|KH 6C QD 2D 4D|Player 2 wins|<p>flush Ace King Queen Four Two beats</p><p>two Kings Queen Jack Six</p>|
|6|TC TD KH JS|8D JC 2H AD|4D 7S 8C JD 3C|Player 2 wins|<p>two Jacks two Eights Seven beats</p><p>two Jacks King Eight Seven</p>|
|7|7S 9D 2C JS|AC 4S AD 2D|QC 3H KH KD 9H|Player 2 wins|<p>two Aces two Kings Queen beats</p><p>two Kings two Nines Jack</p>|
|8|AH AC KH KC|AS AD KS KD|QC 3H TS 8H JD|No single winner|Both have straight Ace King Queen Jack Ten|
