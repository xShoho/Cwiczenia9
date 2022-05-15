//Ewa Figielska, Metody programowania
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Produkt { //klasa abstrakcyjna 
public:
	virtual string opis() = 0;//deklaracja metody jako czysto wirtualnej, czy abstrakcyjnej
	Produkt(){}
};
class Dysk :public Produkt {
	int pojemnosc;
public:
	string opis() { return "Dysk, pojemnosc " + to_string(pojemnosc); }
	Dysk(int pojemnosc) :pojemnosc(pojemnosc) {}
};
class Monitor :public Produkt {
	double przekatna;
public:
	string opis() { return "Monitor, przekatna " + to_string(przekatna); }
	Monitor(double przekatna) :przekatna(przekatna) {}
};
class Magazyn {
	vector<pair<Produkt*, int>> produkty; // relacja agregacji
public:
	void dodaj(Produkt *produkt, int ilosc) {
		produkty.push_back(make_pair(produkt,ilosc));
	}
	void pokaz() {
		int id = 1;
		cout << endl << endl << "Stan magazynu";
		for (auto & p : produkty) {
			cout << endl << id++ << ": " << p.first->opis() <<", sztuk: "<<p.second ;
		}
	}
	Produkt* pobierz(int id, int ile) {
		id--;
		if (ile <= produkty[id].second) {
			produkty[id].second -= ile; //aktualizacja dostepnej ilosci produktu 
			return produkty[id].first;
		}
		else return nullptr;
	}
};

int main() {
	Magazyn magazyn;
	magazyn.dodaj(new Dysk(256), 10);
	magazyn.dodaj(new Dysk(512), 8);
	magazyn.dodaj(new Monitor(13.2), 5);
	magazyn.pokaz();
	cout << endl << "Wzkaz produkt i ilosc (lub wpisz z, aby zakonczyc):";
	int wybrany = 1, ile = 0;
	while (cin >> wybrany >> ile) {
		Produkt *produkt = magazyn.pobierz(wybrany, ile);
		if (produkt)
			cout << "Pobrany produkt: " << produkt->opis();
		else
			cout << "Nie udalo sie pobrac produktu - za mala ilosc w magazynie";
		cout << endl << "Wzkaz produkt i ilosc (lub wpisz z, aby zakonczyc):";
	}
	magazyn.pokaz();
}


