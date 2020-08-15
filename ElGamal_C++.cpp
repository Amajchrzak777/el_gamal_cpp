// ElGamal_C++.cpp 
// Adam Majchrzak 09.04.2020

//krotka instrukcja jak uzywac wpisz plain text program go odszyfruje i stworzy pliki
//szyfr.txt - plain_text
//(encrypted)szyfr.txt - encrypt
//(decrypted)szyfr.txt - decrypt

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

//wartosci stale uzywane do kodowania szyfru. podaje dla przykladu odgornie
//zeby pokazac ze algorytm spelnia swoje zadanie
const int g = 7;  // g grupa mutltiplikatwyna
int p = 29; // wybieramy dowolna liczbe pierwsza
const int k = 10; // 1<k<p
int x = 6;


bool if_prime(int n)
{
	if (n < 2) {
		std::cerr << "This is not prime number so encrypting and decrypting will fail";
		return false; //gdy liczba jest mniejsza niż 2 to nie jest pierwszą
	}
	for (int i = 2; i * i <= n; i++){
		if (n % i == 0) {
			std::cerr << "This is not prime number so encrypting and decrypting will fail";
			return false; //gdy znajdziemy dzielnik, to dana liczba nie jest pierwsza
		}
	}
	return true;
}

bool check_k(int k) {
	if ((k < 1) || (k > p)) {
		std::cerr << "Wrong scope of k";
		return false;
	}
	return true;
}

int genereta_random_number(int random_number) {
	srand(time(NULL));
	random_number = rand() % 10 + 1;
	return random_number;
}
//vector w ktorym przechowuje wiadomosc zaszyfrowana
std::vector<int> przechowaj_szyfr;

//generuje szyfr wpisuje go do pliku
int plain_text(std::string filename) {
	int m;
	std::cin >> m;
	std::ofstream ost(filename.c_str());
	if (!ost) std::cerr << "can't open output file ";
	ost << m;
	ost.close();
	return 0;
}

//generowanie klucza jawnego
int key_generator(int g, int x, int p) {
	int key = fmod(pow(g, x), p);
	return key;
}

//generuje r, jedna ze skladowej tekstu zaszyfrowanego i wpsiuje do wektora
int encryption_r() {
	int r = fmod(pow(g, k), p);
	przechowaj_szyfr.push_back(r);
	return r;
}

//odczytuje tekst jawny a nastepnie szyfruje do nastepnego pliku "(encrypted)szyfr.txt"
//dane wrzucam do wektora
int encryption_c(std::string filename) {
	int m;
	std::ifstream ist(filename.c_str());
	if (!ist) std::cerr << "can't open input file";
	ist >> m;
	int c = fmod(m * pow(key_generator(g, x, p), k), p);
	przechowaj_szyfr.push_back(c);
	std::ofstream ost2("(encrypted)szyfr.txt");
	if (!ost2) std::cerr << "can't open output file ";
	for (int i = 0; i < przechowaj_szyfr.size(); ++i) {
		ost2 << przechowaj_szyfr[i] << " ";
	}
	return c;
}

//odczytuje plik zaszyfrowany a nastepnie deszyfruje
//tekst odszyfrowany zapisuje do pliku "(decrypted)szyfr.txt"
int decrypt(std::string filename2) {
	int z = p - 1 - x;
	int c, r;
	std::ifstream ist1("(encrypted)szyfr.txt");
	if (!ist1) std::cerr << "can't open input file";
	ist1 >> r >> c;
	unsigned long long int x1 = fmod(c * pow(r, z), p);
	std::ofstream ost1(filename2.c_str());
	if (!ost1) std::cerr << "can't open output file ";
	ost1 << x1;
	return x1;
}



int main()
{
	check_k(k); // zakres k musi byc 1<k<p sprawdz to 
	if_prime(p); // p musi byc parzyste sprawdzz to
	x = genereta_random_number(x); //liczba x moze byc losowa 
	plain_text("szyfr.txt");
	encryption_r();
	encryption_c("szyfr.txt");
	std::cout << decrypt("(decrypted)szyfr.txt"); //wyswietlam wartosc odszyfrowana
}

//wada mojej wersji algorytmu kryptograficznego ElGamal'a jest przede wszystkim mały zakres liczb calkowitych
//w momencie w ktorym chce zwiekszyc dlugosc szyfru w tym przypadku liczbe program sie wysypuje i nie dziala poprawnie

//Generowanie klucza - wybieram dowolna liczbe pierwsza p, dowolny generator g z grupy multiplikatywnej którego rząd jest równy	p-1
//oraz z k w zakresie [1<k<p] następnie wyliczam
//key  =fmod(pow(g,x),p) 
//publikuję (p,g,key) i prywatne zostawiam (p,g,key,x)