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

class Dysk: public Produkt {
	int pojemnosc;
public:
	string opis() { return "Dysk, pojemnosc " + to_string(pojemnosc); }
	Dysk(int pojemnosc): pojemnosc(pojemnosc) {}
};

class Monitor: public Produkt {
	double przekatna;
public:
	string opis() { return "Monitor, przekatna " + to_string(przekatna); }
	Monitor(double przekatna): przekatna(przekatna) {}
};

class RAM: public Produkt {
	int pamiec;
public:
	string opis() { return "RAM, pamiec " + to_string(pamiec); }
	RAM(int pamiec): pamiec(pamiec) {}
};

class Procesor: public Produkt {
	int taktowanie;
public:
	string opis() { return "Procesor, taktowanie " + to_string(taktowanie) + "GHz"; }
	Procesor(int taktowanie): taktowanie(taktowanie) {}
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

	void aktualizuj_produkt(int id, int ilosc) {
		if(id >= produkty.size() || id <= 0) {
			cout << endl << "Wybrany produkt nie istnieje";
		} else {
			id--;
			produkty[id].second = ilosc;
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
	magazyn.dodaj(new Procesor(3), 5);
	magazyn.dodaj(new RAM(16), 12);
	magazyn.pokaz();
	magazyn.aktualizuj_produkt(1, 11);
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