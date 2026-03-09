#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {CLUBS=0,SPADES=1,HEARTS=2,DIAMONDS=3} SUIT;

typedef struct _card {
	int rank;
	SUIT suit;
} Card;
typedef Card Hand[5];

char* labels[4]={"clubs","spades","hearts","diamonds"};

/*randomCard
 * Description: Generates a random playing card
 * Arguments: card: A pointer to a card object to store the result
 * Returns: None
 */
void randomCard(Card* card){
	int value= rand();
	card->rank=value%13+1;
	card->suit=(SUIT)rand()%4;

}
/*getTotalTrials
 * Description: Gets the total trials from the user and stores it in cnt
 * Arguments: cnt: an output variable to hold the selected number of trials
 * Returns: None
 */
 void getTotalTrials(int* cnt){
	printf("Enter the number of trials:\n");
	scanf("%d",cnt);
 }

/*inHand
 * Description: checks if a card is in the hand so far
 * Arguments: card: A pointer to a card object to check against the hand
 * 	      hand: An array of cards representing the hand
 * 	      cardCount: The number of valid cards in the hand so far
 * Returns: non-zero if card is in the hand, zero otherwise
 */
int inHand(Card* card, Hand hand,int cardCount){
	for (int i=0;i<cardCount;i++){
		if (card->rank==hand[i].rank && card->suit==hand[i].suit)
			return -1;
	}
	return 0;
}

/*isStraightFlush
 * Description: Checks if the hand is a straight flush
 * Arguments: hand: The hand to check (array of cards)
 * Returns: non-zero if hand represents a straight flush, zero otherwise
 */
int isStraightFlush(Hand hand){
	int swap;
	//first check flush
	SUIT suit=hand[0].suit;
	for (int i=1;i<5;i++)
		if (hand[i].suit!=suit)
			return 0;
	for (int i=0;i<4;i++)
		for (int j=0;j<4-i;j++){
			if(hand[j].rank>hand[j+1].rank){
			       swap=hand[j].rank;	
			       hand[j].rank=hand[j+1].rank;
			       hand[j+1].rank=swap;
			}
		}
	if (hand[4].rank==hand[3].rank+1 && hand[3].rank==hand[2].rank+1 && hand[2].rank==hand[1].rank+1 && (hand[1].rank==hand[0].rank+1 || (hand[0].rank==1 && hand[4].rank==13))){
#ifdef DEBUG
		printf("is a straight flush\n");
#endif
		return -1;
	}

	return 0;
}

/*printHand
 * Description: prints out a hand
 * Arguments: hand: Array of card objects to print out
 * Returns: None
 */
void printHand(Hand hand){
		for (int i=0;i<5;i++)
			printf("\t(%d of %s)",hand[i].rank,labels[hand[i].suit]);
		printf("\n");
}

/*makeStraightFlush1
 * Description: Debugging function to generate a straight flush starting at 1 pre-sorted
 * Arguments: hand: An array of cards to store the result in
 * Returns: None
 */
void makeStraightFlush1(Hand hand){
	hand[0].rank=1;
	hand[0].suit=SPADES;
	hand[1].rank=2;
	hand[1].suit=SPADES;
	hand[2].rank=3;
	hand[2].suit=SPADES;
	hand[3].rank=4;
	hand[3].suit=SPADES;
	hand[4].rank=5;
	hand[4].suit=SPADES;
}

/*makeStraightFlush2
 * Description: Debugging function to generate a straight flush starting at 4 unsorted
 * Arguments: hand: An array of cards to store the result in
 * Returns: None
 */
void makeStraightFlush2(Hand hand){
	hand[0].rank=4;
	hand[0].suit=SPADES;
	hand[1].rank=8;
	hand[1].suit=SPADES;
	hand[2].rank=7;
	hand[2].suit=SPADES;
	hand[3].rank=6;
	hand[3].suit=SPADES;
	hand[4].rank=5;
	hand[4].suit=SPADES;
}

/*makeStraightFlush3
 * Description: Debugging function to generate a straight flush starting at 10 unsorted
 * Arguments: hand: An array of cards to store the result in
 * Returns: None
 */
void makeStraightFlush3(Hand hand){
	hand[0].rank=11;
	hand[0].suit=SPADES;
	hand[1].rank=13;
	hand[1].suit=SPADES;
	hand[2].rank=12;
	hand[2].suit=SPADES;
	hand[3].rank=10;
	hand[3].suit=SPADES;
	hand[4].rank=1;
	hand[4].suit=SPADES;
}

int main(int argc,char** argv){
	int straightFlushes=0;
	float percent;
	Hand pokerHand;
	srand(time(0));
	int cnt;
	getTotalTrials(&cnt);
	for (int i=0;i<cnt;i++){
		int cardCount=0;
		while (cardCount<5){
			Card card;
			randomCard(&card);
			if (!inHand(&card,pokerHand,cardCount)){
				pokerHand[cardCount].rank=card.rank;
				pokerHand[cardCount].suit=card.suit;
				cardCount++;
			}
		}
#ifdef DEBUG
		printHand(pokerHand);
#endif
		if (isStraightFlush(pokerHand))
			straightFlushes++;
	}
	percent=(float)straightFlushes/(float)cnt*100.0;

	printf("We found %d straight flushes out of %d hands or %f percent.\n",straightFlushes,cnt,percent);

	return 0;
}
