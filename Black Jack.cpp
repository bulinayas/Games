#include<iostream>
#include<array>
#include<random>
#include<ctime>

using namespace std;

enum class Perech {

	TWO,
	TREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	VALET,
	DAMA,
	KING,
	TUS,

	LENGTH_PER,

};

enum class Dost {

	BUBEN,
	PIKI,
	CHERVI,
	KRESTI,

	LENGTH_Dost,

};

struct Card {

	Perech p;
	Dost d;

};

void printCard(Card const& card) {

	switch (card.p) {

		case Perech::TWO: cout << "2"; break;
		case Perech::TREE: cout << "3"; break;
		case Perech::FOUR: cout << "4"; break;
		case Perech::FIVE: cout << "5"; break;
		case Perech::SIX: cout << "6"; break;
		case Perech::SEVEN: cout << "7"; break;
		case Perech::EIGHT: cout << "8"; break;
		case Perech::NINE: cout << "9"; break;
		case Perech::TEN: cout << "10"; break;
		case Perech::VALET: cout << "V"; break;
		case Perech::DAMA: cout << "D"; break;
		case Perech::KING: cout << "K"; break;
		case Perech::TUS: cout << "T"; break;

		default: cout << "-"; break;
	}

	switch (card.d) {
			
		case Dost::BUBEN: cout << "B"; break;
		case Dost::CHERVI: cout << "CH"; break;
		case Dost::KRESTI: cout << "K"; break;
		case Dost::PIKI: cout << "P"; break;
	
		default: cout << "-";

	}
};

void printDeck(const array<Card,52>& deck) {

	for (const auto & value: deck) {
	
		printCard(value);
		cout << endl;
	}

}

void swapCard(Card& a, Card& b) {

	Card t = a;
	a = b;
	b = a;

}

int getNumber() {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> uin(0, 51);
	return uin(gen);
}

void shuffleDeck(array<Card,52>& card) {

	int j{ 0 };

	for (int i{ 0 }; i < card.size(); ++i) {

		j = getNumber();
		swap(card[i], card[j]);

	}

}

int getCardValue(Card& card) {

	switch (card.p) {

	case Perech::TWO: return 2; break;
	case Perech::TREE: return 3; break;
	case Perech::FOUR: return 4; break;
	case Perech::FIVE: return 5; break;
	case Perech::SIX: return 6; break;
	case Perech::SEVEN: return 7; break;
	case Perech::EIGHT: return 8; break;
	case Perech::NINE: return 9; break;
	case Perech::TEN: return 10; break;
	case Perech::VALET:
	case Perech::DAMA: 
	case Perech::KING: 
		return 10; break;
	case Perech::TUS: return 11; break;

	default: return -1; break;
	}

}

bool playBlackjack(array<Card,52>& deck) {
	
	const int DILERMAX = 17, OCHKO = 21,CARD_MAX=52;

	Card* cardPtr = &deck.at(0);
	int player{ 0 }, diler{0};
	bool playerChoice = true;

	shuffleDeck(deck);

	diler += getCardValue(*cardPtr++);
	player += getCardValue(*cardPtr++);
	player += getCardValue(*cardPtr++);

	int i = 3;
	do {

		if ((cardPtr->p == Perech::TUS)&&(player>OCHKO)) {
		
			++player;
		}
		else player += getCardValue(*cardPtr++);

		i++;

		cout << "You have " << player << " points" << endl;

		cout << "Your choice? Hit - 1, Stand - 0" << endl;
		cin >> playerChoice;

	} while ((playerChoice)&&(i<=(CARD_MAX-3)));

	if (player > OCHKO) return false;


	while ((diler < DILERMAX)&&(i <= (CARD_MAX - 3))) {

		cout << "Diler has " << diler << " points" << endl;
		if ((cardPtr->p == Perech::TUS) && (diler > OCHKO)) {

			++diler;
		}
		else diler += getCardValue(*cardPtr++);
		i++;
	}

	if (diler > OCHKO) return true;

	return (player >= diler);

	
}

int main() {
	
	array<Card, 52> deck;

	int card = 0;
	for (int i{ 0 }; i < (int)Dost::LENGTH_Dost; ++i) {

		for (int j{ 0 }; j < (int)Perech::LENGTH_PER; ++j) {
			deck[card].d = static_cast<Dost>(i);
			deck[card].p = static_cast<Perech>(j);
			++card;
		}
		
	}

	if (playBlackjack(deck)) cout << "You win!" << endl;
	else cout << "You lose!" << endl;



	return 0;
}