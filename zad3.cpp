//Ewa Figielska, Metody programowania
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Produkt {//klasa abstrakcyjna
public:
	virtual string opis() = 0;//metoda czysto wirtualna - abstrakcyjna
	virtual float daj_cene() = 0;
	virtual ~Produkt(){}
};

class Monitor: public Produkt { //dziedziczenie
	float cena;
	float przekatna;
public:
	string opis() { return "Monitor, przekatna " + to_string(przekatna) + " cena: " + to_string(cena) + "zl"; }
	float daj_cene() { return cena; }
	Monitor(float przekatna, float cena): przekatna(przekatna), cena(cena) {}
};

class Dysk: public Produkt {
	float cena;
	float pojemnosc;
public:
	string opis() { return "Dysk, pojemnosc " + to_string(pojemnosc) + " cena: " + to_string(cena) + "zl"; }
	float daj_cene() { return cena; }
	Dysk(float pojemnosc, float cena): pojemnosc(pojemnosc), cena(cena) {}
};

class Procesor: public Produkt {
	float cena;
	float taktowanie;
public:
	string opis() { return "Procesor, taktowanie " + to_string(taktowanie) + "GHz, cena: " + to_string(cena) + "zl"; }
	float daj_cene() { return cena; }
	Procesor(float taktowanie, float cena): taktowanie(taktowanie), cena(cena) {}
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
	Produkt *produkt;//odwolanie do Produktu, wskaznik typu Produkt (klasy bazowej) - bedzie wskazywal obiekty konkretnych podklas Produktu  
	int ilosc;
	float cena;
public:
	PozycjaZamowienia(Produkt *produkt, int ilosc): produkt(produkt), ilosc(ilosc) {
		cena = produkt->daj_cene() * ilosc;
	}
	string opis() { 
	//wywolanie metody pokaz_opis() dla obiektu klasy pochodnej za pomoca wskaznika typu klasy bazowej Produkt
	//wywolanie to jest polimorficzne - mozliwe dzieki zdefiniowaniu metody pokaz_opis() jako wirtualnej w klasie bazowej Produkt
	//kod jest ten sam niezaleznie od tego ktorej klasy pochodnej jest obiekt
	return produkt->opis() + ", ilosc " + to_string(ilosc); }
	float daj_cene() { return cena; }
};

class Zamowienie {
	vector<PozycjaZamowienia*> pozycje_zamowienia;
	float cena;
public:
	Zamowienie() { cena = 0; }
	void dodaj(Produkt* produkt, int ilosc) {
		PozycjaZamowienia pozycja(produkt, ilosc);
		cena += pozycja.daj_cene();
		pozycje_zamowienia.push_back(&pozycja);
	}
	void drukuj() {
		int nr = 1;
		cout << endl << endl << "Zamowienie";
		for (auto&pz : pozycje_zamowienia) {
			cout << endl << nr++ << ": " << pz->opis();
		}
	}

	string opis() { return "Pozycje zamowienia: " + to_string(pozycje_zamowienia.size()) + " cena: " + to_string(cena) + "zl"; }
};

class Klient {
	string imie;
	string nazwisko;
	Zamowienie *zamowienie;
public:
	Klient(string imie, string nazwisko, Zamowienie* zamowienie): imie(imie), nazwisko(nazwisko), zamowienie(zamowienie) {}
	string opis() { return "Imie: " + imie + " Nazwisko: " + nazwisko + " zamowienie: " + zamowienie->opis(); }
};

class Klienci {
	vector<Klient*> klienci;
public:
	void dodaj(Klient* klient) {
		klienci.push_back(klient);
	}

	void drukuj() {
		int nr = 1;
		cout << endl << endl << "Klienci";
		for(auto & k : klienci) {
			cout << endl << nr++ << ": " << k->opis();
		}
	}
};

int main() {
	Magazyn magazyn;
	magazyn.dodaj(new Dysk(256, 200), 25);
	magazyn.dodaj(new Dysk(512, 500), 30);
	magazyn.dodaj(new Monitor(22, 650), 15);
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