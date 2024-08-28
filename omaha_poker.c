#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "omaha_poker.h"

/*Define 2 global instances of struct player--one for each player */
struct player player1;
struct player player2;

/* Parse card from a 2 char input */
struct card parse(const char* card) {
	struct card result;

	// Parse the card value (first character)
	switch (card[0]) {
	case '2':
		result.val = TWO;
		break;

	case '3':
		result.val = THREE;
		break;

	case '4':
		result.val = FOUR;
		break;
	case '5':
		result.val = FIVE;
		break;

	case '6':
		result.val = SIX;
		break;

	case '7':
		result.val = SEVEN;
		break;
	case '8':
		result.val = EIGHT;
		break;


	case '9':
		result.val = NINE;
		break;

	case 'T':
		result.val = TEN;
		break;

	case 'J':
		result.val = JACK;
		break;

	case 'Q':
		result.val = QUEEN;
		break;

	case 'K':
		result.val = KING;
		break;

	case 'A':
		result.val = ACE;
		break;

	default:
		// Handle invalid card value
		result.val = ACE; 
		break;
	}

	// Parse the card suit (second character)
	switch (card[1]) {
	case 'C':
		result.suit = CLUB;
		break;

	case 'D':
		result.suit = DIAMOND;
		break;

	case 'H':
		result.suit = HEART;
		break;


	case 'S':
		result.suit = SPADE;
		break;

	default:
		// Handle invalid card suit
		// Set a default suit, such as SPADE, in case of an invalid card suit
		result.suit = SPADE; // You can change this to any other default suit as needed
		break;
	}

	return result;
}

/* Count the number of occurrences of each card 2 through Ace */
void count_cards(struct hand* h) {
	for (int i = 0; i < 5; i++) {

		switch (h->cards[i].val) {

		case TWO:
			h->card_count[0]++;
			break;

		case THREE:
			h->card_count[1]++;
			break;

		case FOUR:
			h->card_count[2]++;
			break;
			
		case FIVE:
			h->card_count[3]++;
			break;

		case SIX:
			h->card_count[4]++;
			break;

		case SEVEN:
			h->card_count[5]++;
			break;

		case EIGHT:
			h->card_count[6]++;
			break;

		case NINE:
			h->card_count[7]++;
			break;

		case TEN:
			h->card_count[8]++;
			break;

		case JACK:
			h->card_count[9]++;
			break;

		case QUEEN:
			h->card_count[10]++;
			break;

		case KING:
			h->card_count[11]++;
			break;

		case ACE:
			h->card_count[12]++;
			break;

		}
	}
}

int is_flush(struct hand *h)
{
	return h->cards[0].suit == h->cards[1].suit && h->cards[1].suit == h->cards[2].suit && h->cards[2].suit == h->cards[3].suit && h->cards[3].suit == h->cards[4].suit;
	
}


int is_straight(struct hand *h)
{
    int count = 0;
    int is_Ace = 0;
    if ((h->card_count[12]) > 0 && (h->card_count[0]) > 0 && h->card_count[1] > 0 && h->card_count[2] > 0  && h->card_count[3] > 0 ) return 1;
    for (int i = 0; i < 13; i++) {
        if ((h->card_count[i]) > 0) {
            count++;
            if(count == 5)return 1;
        } else count=0;
    }return 0;
}

int is_straight_flush(struct hand *h){ 
	return is_straight(h) == 1 && is_flush(h) == 1 ? 1 : 0;
}
		

void print_hand(struct hand *h)
{
	int i;
	for(i = 0; i < 5; i++) {
		printf("%d%d ", h->cards[i].val, h->cards[i].suit);
	}
}



void eval_strength(struct hand *h)
{
    h->vector = 0;
    int two_Of_Rank = 0;
    int three_Of_Rank = 0;
    int count = 0;
	int offSet=(18-count)/10;
    for (int i = 0; i < 13; i++) {
        if(h->card_count[i] == 1){count += i;BIT_SET(h->vector,i);}
        if(h->card_count[i] == 2){two_Of_Rank = 1;BIT_SET(h->vector,13+i);}
        if(h->card_count[i] == 3){BIT_SET(h->vector,i+26);three_Of_Rank = 1;}
        if(h->card_count[i] == 4)BIT_SET(h->vector,i+43);
    }
	if(count == 18 && h->card_count[12] != 0)offSet=0;
    if (is_straight(h) && !is_flush(h))BIT_SET(h->vector,offSet+39);
    if (is_flush(h) && !is_straight(h))BIT_SET(h->vector,offSet+40);
    if(two_Of_Rank == 1 && three_Of_Rank == 1)BIT_SET(h->vector,offSet+41);
    if(is_straight_flush(h))BIT_SET(h->vector,offSet+55);
}

void eval_players_best_hand(struct player *p)
{
    p->best_hand = &p->hands[0];
    eval_strength(p->best_hand);
    for(int i = 0; i < MAX_COMBINATIONS; i++){
        eval_strength(&p->hands[i]);
		if(p->hands[i].vector > p->best_hand->vector)p->best_hand = &p->hands[i];
	}
}

void copy_card(struct card *dst, struct card *src)
{
	dst->val = src->val;
    dst->suit = src->suit;
}


void initialize_player_omaha(struct player *p, struct card *player_cards, struct card *community_cards) {
    memset(p, 0, sizeof(struct player));
    int count = 0;
    for (int player_card1 = 0;player_card1 < 4;player_card1++) {
        for (int player_card2 = player_card1 + 1;player_card2 < 4;player_card2++) {
            for (int comm_card1 = 0; comm_card1 < 5;comm_card1++) {
                for (int comm_card2 = comm_card1 + 1;comm_card2 < 5; comm_card2++) {
                    for (int comm_card3 = comm_card2 + 1;comm_card3 < 5; comm_card3++) {
                        copy_card(&p->hands[count].cards[0], &player_cards[player_card1]);
                        copy_card(&p->hands[count].cards[1], &player_cards[player_card2]);
                        copy_card(&p->hands[count].cards[2], &community_cards[comm_card1]);
                        copy_card(&p->hands[count].cards[3], &community_cards[comm_card2]);
                        copy_card(&p->hands[count].cards[4], &community_cards[comm_card3]);
                        count_cards(&p->hands[count]);
                        count++;
                    }
                }
            }
        }
    }
}


void process_input_omaha(FILE *fp)
{

	char p1[4][3];
	char p2[4][3];
	char comm[5][3];
	struct card p1_cards[4], p2_cards[4], community_cards[5];
	int i;

	while(fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s",
		&p1[0][0], &p1[1][0], &p1[2][0], &p1[3][0], &p2[0][0], &p2[1][0], &p2[2][0], &p2[3][0],
		&comm[0][0], &comm[1][0], &comm[2][0], &comm[3][0], &comm[4][0]) == 13) {

		memset(p1_cards, 0, sizeof(struct card) * 4);
		memset(p2_cards, 0, sizeof(struct card) * 4);
		memset(community_cards, 0, sizeof(struct card) * 5);

		for(i = 0; i < 4; i++) {
			p1_cards[i] = parse(&p1[i][0]);
		}
        for(i = 0; i < 4; i++) {
            p2_cards[i] = parse(&p2[i][0]);
        }
		for(i = 0; i < 5; i++) {
            community_cards[i] = parse(&comm[i][0]);
        }

        initialize_player_omaha(&player1, p1_cards, community_cards);
        initialize_player_omaha(&player2, p2_cards, community_cards);
        eval_players_best_hand(&player1);
        eval_players_best_hand(&player2);
        unsigned long p1=player1.best_hand->vector;
        unsigned long p2=player2.best_hand->vector;
        if(p1>p2)printf("Player 1 wins\n");
		else if(p2>p1)printf("Player 2 wins\n");
		else printf("No single winner\n");
    }
}

int main(int argc, char *argv[])
{
	FILE *fp;

	if(argc != 2 || (fp = fopen(argv[1], "r")) == NULL) {
		printf("Unable to open input file\n");
		exit(-1);
	}
	
	process_input_omaha(fp);

	return 0;
}
