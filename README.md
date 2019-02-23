# ExplodingKittens-C
C Implementation of the Card Game Exploding Kittens

## Variablen von main() ##
anzahlSpieler 		//Anzahl aller Mitspieler; nutzbar für Rundenschleife
anzahlKarten		//Anzahl von Spielkarten im Spiel
1 Array pro Spieler (Anzahl entspricht Kartenanzahl)

while(anzahlSpieler > 1)  // Schleife

## Runde(Spieler, AnzahlKartenZuZiehen): ##
A Handkarten angezeigen (als Text)
Karten ausführen (Schleife mit Abfrage ob ausführbar wollen + kann)
Aktion;
Skip:				Ende des Zuges
Reverse:			Ende des Zuges + Spieler zuvor ist dran
Attack:				Ende des Zuges + Gegner 2 ziehen
See the Future:		3 Karten der Zukunft sehen
A Handkarten anzeigen;
B Karte ziehen (Anzahl)
ExplodingKitten -> Defuse / TOD
Andere -> Ende des Zuges
A Handkarten anzeigen

Karten : 30
6-Anzahl x ExplodingKitten			Spieler kann Defuse spielen, sonst TOD
5-Anzahl x Defuse				---- spielbar wenn ExplodingKitten, (oder Sonderaktion)
4 x Skip				Ende des Zuges
4 x Reverse				Ende des Zuges, Spieler zuvor ist dran
3 x Attack				Nächster Spieler zieht 2 Karten
3 x See the future			Man sieht die nächsten 3 Karten
10 x Kitten				---- Keine Aktion, (außer Sonderaktion)

int shuffle(int[], int[], int); /* ZielListe, Liste, Größe */
void randomInts(int[], int, int); /* Zielliste, Liste, höhe */






