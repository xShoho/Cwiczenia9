//Ewa Figielska, Metody programowania
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Produkt {//klasa abstrakcyjna
public:
	virtual string opis() = 0;//metoda czysto wirtualna - abstrakcyjna
	virtual ~Produkt(){}
};
class Monitor :public Produkt { //dziedziczenie
	float przekatna;
public:
	string opis() { return "Monitor, przekatna " + to_string(przekatna); }
	Monitor(float przekatna) :przekatna(przekatna) {}
};
class Dysk :public Produkt {
	float pojemnosc;
public:
	string opis() { return "Dysk, pojemnosc " + to_string(pojemnosc); }
	Dysk(float pojemnosc) :pojemnosc(pojemnosc) {}
};
class Magazyn {
	vector<pair<Produkt*,int>> produkty; //agregacja
public:
	void dodaj(Produkt*produkt, int ilosc) {
		produkty.push_back(make_pair(produkt, ilosc));
	}
	void pokaz() {
		int id = 1;
		cout << endl << endl << "Stan magazynu ";
		for (auto &p : produkty) {
			cout << endl <<id++ <<": "<< p.first->opis() << ", sztuk " << p.second;//wywolanie polimorficzne
		}
	}
	Produkt* pobierz(int id, int ile) {
		--id;
		try {
			if (ile <= produkty.at(id).second) {
				produkty.at(id).second -= ile;
				return produkty.at(id).first;
			}
			else {
				cout << "Za malo produktu";
			}
		}
		catch (out_of_range & e) {
			cout << "Nieprawidlowy numer produktu";
		}
		return nullptr;
	}
};
class PozycjaZamowienia {
	Produkt*produkt;//odwolanie do Produktu, wskaznik typu Produkt (klasy bazowej) - bedzie wskazywal obiekty konkretnych podklas Produktu  
	int ilosc;
public:
	PozycjaZamowienia(Produkt *produkt, int ilosc): produkt(produkt), ilosc(ilosc) {}
	string opis() { 
	//wywolanie metody pokaz_opis() dla obiektu klasy pochodnej za pomoca wskaznika typu klasy bazowej Produkt
	//wywolanie to jest polimorficzne - mozliwe dzieki zdefiniowaniu metody pokaz_opis() jako wirtualnej w klasie bazowej Produkt
	//kod jest ten sam niezaleznie od tego ktorej klasy pochodnej jest obiekt
	return produkt->opis() + ", ilosc " + to_string(ilosc); }
};
class Zamowienie {
	vector<PozycjaZamowienia*> pozycje_zamowienia;
public:
	void dodaj(Produkt* produkt, int ilosc) {
		pozycje_zamowienia.push_back(new PozycjaZamowienia(produkt, ilosc));
	}
	void drukuj() {
		int nr = 1;
		cout << endl << endl << "Zamowienie";
		for (auto&pz : pozycje_zamowienia) {
			cout << endl << nr++ << ": " << pz->opis();
		}
	}
};

int main() {
	Magazyn magazyn;
	magazyn.dodaj(new Dysk(256), 25);
	magazyn.dodaj(new Dysk(512), 30);
	magazyn.dodaj(new Monitor(22), 15);
	magazyn.pokaz();
	Zamowienie zamowienie;
	cout << endl << endl << "Tworzenie zamowienia\nWybierz produkt i jego ilosc (lub wpisz z, aby zakonczyc): ";
	int id, ile;
	while (cin >> id >> ile) {
		Produkt*pobrany_produkt = nullptr;
		pobrany_produkt = magazyn.pobierz(id, ile);
		if (pobrany_produkt) {
			cout << "Pobrany produkt: " << pobrany_produkt->opis(); //wywolanie polimorficzne
			zamowienie.dodaj(pobrany_produkt, ile);
		}
		else cout << " - nie mozna dodac do zamowienia";

		cout << endl << "Wybierz nastepny produkt i jego ilosc (lub wpisz z, aby zakonczyc): ";
	}
	
	zamowienie.drukuj();
	magazyn.pokaz();
}