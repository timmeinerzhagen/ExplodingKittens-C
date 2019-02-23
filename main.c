void shuffle(int deck[], int deckSize) 	/* Deck, Deckgröße */
{
	int i, deckShuffled[deckSize], rInts[deckSize];
	randomInts(&rInts, deckSize, deckSize);
	for(i = 0; i < deckSize; i++)
	{
    	int r = rInts[i];
    	deckShuffled[r] = deck[i];
	}
	int d;
	for(d = 0; d < deckSize; d++)
	{
    	deck[d] = deckShuffled[d];
	}
}
void randomInts(int array[], int anzahl, int hoehe) /* Legt zufällige Werte von 0 - hoehe in den array[anzahl] */
{
 	int i,r,a, done[anzahl];
 	for(i = 0;i<anzahl;i++) done[i] = -1;

 	srand((unsigned)time(NULL));
 	for(a=0;a<anzahl;a++)
 	{
    	do
    	{
        	r = rand() % anzahl;
    	} while(done[r] != -1);
    	done[r] = 1;
    	array[a] = r;
 	}
}



//PROGRAMM//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createDeck(int array[], int size, int deck[], int deckSize);
//void shuffle(int deck[], int deckSize);
int aktiv(int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten]);
int drawTop(int anSpieler, int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten], int deck[], int deckSize);
void zeigeHand(int vonSpieler, int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten], char * kartenName[]);
void addCard(int card, int anSpieler, int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten]);
void shuffle(int[], int); /* Liste, Größe */
void randomInts(int[], int, int); /* Zielliste, Liste, höhe */

int main()
{
    const int ANZAHL_KARTEN = 8;
    enum { EMPTY, EXPLODING_KITTEN, DEFUSE, SKIP, REVERSE, ATTACK, SEE_THE_FUTURE, KITTEN };
    const char *kartenName[] = {"EMPTY", "EXPLODING_KITTEN", "Defuse", "Skip", "Reverse", "Attack", "See the Future", "Kitten"};
    /*Spieleranzahl einlesen */
    int anzahlSpieler = 0, deckSize = 40;
    printf("Anzahl spieler: \n");
    scanf("%d", &anzahlSpieler);

    /* Decks erstellen */
    int karten[] = {deckSize, 0, 6-anzahlSpieler, 5, 4, 3, 3, 10};
    int it;
    for(it=1;it<ANZAHL_KARTEN; it++) karten[0] -=karten[it];
    int deck[deckSize];
    createDeck(karten, ANZAHL_KARTEN, &deck, deckSize);
    shuffle(&deck, deckSize);
    //printf("!!3!!");
    /* Haende erstellen */
    int spieler[anzahlSpieler][ANZAHL_KARTEN];
    int i;
    for(i=0; i<anzahlSpieler; i++){
        int e;
        for(e=0; e<ANZAHL_KARTEN; e++) spieler[i][e] = 0;
        spieler[i][DEFUSE] = 1;
        //printf("!!5!!");
        int handKarten;
        for(handKarten=0;handKarten<5;handKarten++) drawTop(i, anzahlSpieler, ANZAHL_KARTEN, &spieler, &deck, deckSize);
        //printf("!!6!!");
    }
    //printf("!!4!!");


    /* Exploding Kittens */
    int k;
    for(k=0;k<anzahlSpieler;k++) addToDeck(EXPLODING_KITTEN,&deck, deckSize);
    shuffle(&deck, deckSize);
    /* Game Lopp */
    int turn = 1;
    int currSpieler = 0;
    int nextZiehen = 1;
    int direction = 1;
    while(aktiv(anzahlSpieler, ANZAHL_KARTEN, spieler) > 1){
        if(spieler[i][0] == 1) continue;
        system("cls");
        int mussZiehen = nextZiehen;
        nextZiehen = 1; // Wie viel der naechste Spieler ziehen muss. Kann durch aktionen veraendert werden
        printf("-------------------------------\nZug %d - Spieler %d\nMuss %d Karte(n) ziehen.\n", turn, currSpieler+1, mussZiehen);
        zeigeHand(currSpieler, anzahlSpieler, ANZAHL_KARTEN, spieler, kartenName);

        char c;
        printf("(Karte spielen : k) \n(Ziehen : z)\n");
        fflush(stdin);
        scanf("%c", &c);
        if(c == 'k'){
            char weiter = 'j';
            do{
                printf("Welche Karte willst du legen? (Gib den ganzen namen ein)\n");
                fflush(stdin);
                char* eingabe[20];
                gets(eingabe);
                if(strcmp(eingabe, "Skip") == 0){
                    if(spieler[currSpieler][SKIP]>=1){
                        printf("<<Skip\n");
                        mussZiehen = 0;
                        spieler[currSpieler][SKIP] -= 1;
                        break;
                    }
                }else if(strcmp(eingabe, "Reverse")  == 0){
                    if(spieler[currSpieler][REVERSE]>=1){
                        printf("<<Reverse\n");
                        direction = !direction;
                        mussZiehen = 0;
                        spieler[currSpieler][REVERSE] -= 1;
                        break;
                    }
                }else if(strcmp(eingabe, "Attack")  == 0){
                    if(spieler[currSpieler][ATTACK]>=1){
                        printf("<<Attack\n");
                        nextZiehen = 2;
                        mussZiehen = 0;
                        spieler[currSpieler][ATTACK] -= 1;
                        break;
                    }
                }else if(strcmp(eingabe, "See the Future")  == 0){
                    if(spieler[currSpieler][SEE_THE_FUTURE]>=1){
                        printf("<<See the Future\n");
                        printf("Top cards: ");
                        int view, nr = 0;
                        for(view =0;view<deckSize && nr<3; view++)
                            if(deck[view] != 0){
                                printf("%s, ", kartenName[deck[view]]);
                                nr++;
                            }
                        spieler[currSpieler][SEE_THE_FUTURE] -= 1;
                    }
                }
                printf("Weitere Karten spielen? (j/n)\n");
                fflush(stdin);
                scanf("%c", &weiter);
            }while(weiter == 'j');
        }

        /* Karte ziehen */
        int ziehe = 0;
        for(ziehe=0; ziehe<mussZiehen; ziehe++){
                int karte = drawTop(currSpieler, anzahlSpieler, ANZAHL_KARTEN, &spieler, &deck, deckSize);
                printf(">>%s gezogen\n", kartenName[karte]);
                if(karte == EXPLODING_KITTEN){
                    if(spieler[currSpieler][DEFUSE]>=1){
                        spieler[currSpieler][DEFUSE] -=1;
                        spieler[currSpieler][EXPLODING_KITTEN] = 0;
                        printf("Als wie vielte Karte willst du sie einlegen?\n(0=top, 1=2nd, ...)\n");
                        int stelle;
                        fflush(stdin);
                        scanf("%d", &stelle);
                        putIn(karte, stelle, &deck, deckSize);
                    }
                }
        }

        zeigeHand(currSpieler, anzahlSpieler, ANZAHL_KARTEN, spieler, kartenName);

        /* naechster Spieler */
        currSpieler += direction;
        if(direction >= 0 && currSpieler>anzahlSpieler-1) currSpieler = 0;
        if(direction <= 0 && currSpieler<0) currSpieler = anzahlSpieler-1;
        turn++;
    }
    int sieger;
    for(sieger=0; sieger<anzahlSpieler; sieger++) if(spieler[sieger][EXPLODING_KITTEN]==0) break;
    printf("ENDE\nSpieler %d hat gewonnen", sieger+1);

    return 0;
}

void zeigeHand(int vonSpieler, int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten], char * kartenName[]){
    printf("Hand von Spieler %d: ", vonSpieler + 1);
    int hand;
    int schonEineKarte=0;
    for(hand =  0; hand<anzahlKarten; hand++) {
        int z = spieler[vonSpieler][hand];
            //printf("%sx %d", "JA", z);
        if(z>0){
            if(schonEineKarte) printf(", ");
            printf("%dx %s ", z, kartenName[hand]);
            schonEineKarte = 1;
        }
    }
    printf("\n");
}

void createDeck(int array[], int size, int deck[], int deckSize){
    int i, e, pos=0;
    for(i=0; i<size && pos<deckSize ;i++){
        for(e=0;e<array[i];e++){
                //printf("%d ", i);
            deck[pos] = i;
            pos++;
        }
    }
}

void addToDeck(int card, int deck[], int deckSize){
    int i;
    for(i=0;i<deckSize;i++){
        if(deck[i]==0){
            deck[i]=card;
            break;
        }
    }
}

int aktiv(int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten]){
    int i, anzahl = 0;
    for(i=0; i<anzahlSpieler; i++) if(spieler[i][1] == 0) anzahl++;
    return anzahl;
}

int drawTop(int anSpieler, int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten], int deck[], int deckSize){
    int i;
    //printf("JA");
    for(i=0;i<deckSize;i++){
        int gezogen = deck[i];
        if(gezogen !=0){
                spieler[anSpieler][gezogen] += 1;
                deck[i] = 0;
                return gezogen;
        }
    }
}


void addCard(int card, int anSpieler, int anzahlSpieler, int anzahlKarten, int spieler[anzahlSpieler][anzahlKarten]){

}


void putIn(int card, int stelle, int deck[], int deckSize){
    int akt = card, i;
    for(i=0;i<deckSize; i++){
            if(stelle>0){
                if(deck[i] != 0) stelle--;
            }else{
                int temp = deck[i];
                deck[i] = akt;
                akt = temp;
                if(akt == 0) return;
            }
    }
}

void shuffle(int deck[], int deckSize) 	/* Deck, Deckgröße */
{

	int i, deckShuffled[deckSize], rInts[deckSize];
	int z;
	//for(z=0;z<deckSize;z++) printf("%d, ", deck[z]);
	//printf("\n");
	randomInts(&rInts, deckSize, deckSize);
	for(i = 0; i < deckSize; i++)
	{
    	int r = rInts[i];
    	int zahl = deck[r];
    	//printf("%d\n", r);
    	deckShuffled[r] = deck[i];
    	//deck[i] = deck[r];
        //printf("%d ", deck[i]);
	}
        //printf("!!1!!\n");
    //printf("!!1!!\n");
	int d;
	for(d = 0; d < deckSize; d++)
	{
    	deck[d] = deckShuffled[d];
	    //printf("%d, ", deck[d]);
	}
    //printf("\n!!2!!\n");
}
void randomInts(int array[], int anzahl, int hoehe) /* Legt zufällige Werte von 0 - hoehe in den array[anzahl] */
{
 	int i,r,a, done[anzahl];
 	for(i = 0;i<anzahl;i++) done[i] = -1;

 	srand((unsigned)time(NULL));
 	for(a=0;a<anzahl;a++)
 	{
    	do
    	{
        	r = rand() % anzahl;
    	} while(done[r] != -1);
    	done[r] = 1;
    	array[a] = r;
 	}
}



