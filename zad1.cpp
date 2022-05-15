//Ewa Figielska, Metody programowania
#include<iostream>
#include<string>

using namespace std;

class Stanowisko {
public:
	virtual string stanowisko() { return "-"; } //deklaracja metody jako wirtualnej
	virtual string profity() { return "-"; } //deklaracja metody jako wirtualnej
};

class Praktykant :public Stanowisko {
public:
	Praktykant() {}
	string stanowisko() { return "praktykant"; }
	string profity() { return "brak profitow"; }
};

class Specjalista :public Stanowisko {
private:
	string samochod;
public:
	Specjalista(string samochod) :samochod(samochod) {}
	string stanowisko() { return "specjalista"; }
	string profity() { return samochod; }
};

class Pracownik {
protected:
	string imie;
	string nazwisko;
	string adres;
	Stanowisko * s = nullptr; //odwolanie do klasy Stanowisko (asocjacja)
public:
	Pracownik(string imie, string nazwisko, string adres) :imie(imie), nazwisko(nazwisko), adres(adres) { }
	string dane() { return imie + " " + nazwisko + ", " + adres; }
	void przydziel_stanowisko(Stanowisko* stanowisko) {
		delete s;
		s = stanowisko;
	}
	string pokaz_stanowisko() { return s->stanowisko() + ", " + s->profity(); }
};

int main() {
	Pracownik p("Jan", "Bratek", "Fiolkowa 2");
	p.przydziel_stanowisko(new Praktykant);
	cout << endl << p.dane() << ", " << p.pokaz_stanowisko();
	p.przydziel_stanowisko(new Specjalista("Toyota auris"));
	cout << endl << p.dane() << ", " << p.pokaz_stanowisko();
}