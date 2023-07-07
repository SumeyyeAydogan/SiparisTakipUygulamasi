
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <conio.h>
#include <regex>


using namespace std;





#pragma region TXT Files
static const string rootPath = ".\\";
static const string adminFile = "admin.txt";
static const string clientFile = "client.txt";
static const string feedbackFile = "feedback.txt";
static const string productFile = "product.txt";
static const string courierFile = "courier.txt";
static const string orderFile = "order.txt";
static const string invoiceFile = "invoice.txt";

#pragma endregion


#pragma region Siniflar
class Kiyafet
{
public:
	string kategori;
	int kiyafet_adi;
	double fiyat;
	string boyut;
	string renk;
	Kiyafet();
	Kiyafet(string, string, string, double);
	~Kiyafet();

private:

};
Kiyafet::Kiyafet(string a, string b, string c, double d)
{
	kategori = a;
	renk = b;
	boyut = c;
	fiyat = d;
}
Kiyafet::Kiyafet()
{
}
Kiyafet::~Kiyafet()
{
}


class Zaman
{
public:
	int saat;
	int dakika;

	Zaman operator+(const Zaman& z);
	bool operator<(const Zaman& z);
	bool operator>(const Zaman& z);


	Zaman();
	~Zaman();
};
Zaman Zaman :: operator+(const Zaman& z)
{
	Zaman z1;
	z1.dakika = dakika + z.dakika;
	z1.saat = saat + z.saat;

	if (z1.dakika > 59) {
		z1.saat++;
		z1.dakika %= 60;
	}

	return z1;
}

bool Zaman::operator<(const Zaman& z)
{
	if (saat < z.saat)
		return true;
	else if (saat == z.saat)
	{
		if (dakika < z.dakika)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Zaman:: operator>(const Zaman& z)
{
	{
		if (saat > z.saat)
			return true;
		else if (saat == z.saat)
		{
			if (dakika > z.dakika)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

Zaman::Zaman()
{
}

Zaman::~Zaman()
{
}

class Kisi
{
public:
	string ad_soyad;
	string telNo;

	Kisi();
	~Kisi();

};

Kisi::Kisi()
{
}

Kisi::~Kisi()
{
}

class Yonetici : public Kisi
{
public:
	string sifre;

	Yonetici();
	~Yonetici();

private:

};

Yonetici::Yonetici()
{
}

Yonetici:: ~Yonetici()
{
}

class Kurye : public Kisi
{
public:
	int siparis_no;
	Kurye();
	~Kurye();
	Zaman siparis_bitis;

private:

};

Kurye::Kurye()
{
}

Kurye::~Kurye()
{
}

class Kullanici : public Kisi
{
public:
	string kullanici_adi;
	string eposta;
	string adres_ilce;
	string sifre;
	string indirim_kodu;
	string dogum_tarihi;
	Kullanici();
	~Kullanici();

private:

};

Kullanici::Kullanici()
{
}

Kullanici::~Kullanici()
{
}

class Siparis : public Kiyafet
{
public:
	int siparis_no;
	double siparis_fiyat;
	// zaman  baslangic op mop fln
	// ulasim fln
	Siparis();
	~Siparis();

private:

};

Siparis::Siparis()
{
}

Siparis::~Siparis()
{
}

#pragma endregion


Kullanici mevcutKullanici;


void musteri_girisi();
void Start_menu();
#pragma region Kontrol Fonksiyonlari
auto musteri_kontrol()
{
	ifstream getInfo("user.txt");

	string line;
	string check, sifre;
	cout << "Kullanici adini giriniz: ";
	cin.get();
	getline(cin, check);
	cout << "Sifre Giriniz: ";
	int ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b' && uzunluk != 0) {
			sifre.pop_back();
			uzunluk--;
			cout << "\b \b";
		}
		else {
			putchar('*');
			uzunluk++;
			sifre  += ch;
		}
	}

	while (!getInfo.eof())
	{
		getline(getInfo, line);
		string username = line.substr(0, line.find("-"));
		if (line != "")
		{
			if (check == username)
			{

				string password = line.substr(line.find("-") + 1, line.rfind("-") - line.find("-") - 1);
				string adres = line.substr(line.rfind("-") + 1, line.length());
				if (sifre == password)
				{
					cout << "Giris basarili" << endl;
					getInfo.close();

					mevcutKullanici.kullanici_adi = username;
					mevcutKullanici.adres_ilce = adres;
					return true;
				}
				else
				{
					cout << "Sifre yanlis" << endl;
					getInfo.close();
					return false;
				}
			}
		}



	}
	cout << "Kullanici bulunamadi" << endl;
	getInfo.close();
	return false;

}




bool yonetici_kontrol()
{
	string kullanici_adi;
	string sifre;
	cout << "Kullanici Adi: ";
	cin >> kullanici_adi;
	cout << "Sifre: ";
	cin >> sifre;
	if (kullanici_adi == "admin" && sifre == "0")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isStrongPassword(string password) // Guclu sifre
{



	// en az 8 karakter olmali
   // sifrenin uzunlugunu kontrol ediyoz
	if (password.length() < 8)
		return false;

	// sifrenin icerisinde en az bir buyuk harf, bir kucuk harf ve bir rakam oldugunu kontrol ediyoz
	bool hasUpper = false, hasLower = false, hasDigit = false;
	for (char c : password)
	{
		if (isupper(c))
			hasUpper = true;
		else if (islower(c))
			hasLower = true;
		else if (isdigit(c))
			hasDigit = true;
	}

	if (!hasUpper || !hasLower || !hasDigit)
		return false;

	// sifrenin icerisinde en az bir ozel karakter oldugunu kontrol ediyoruz
	bool hasSpecial = false;
	for (char c : password)
	{
		if (!isalpha(c) && !isdigit(c))
		{
			hasSpecial = true;
			break;
		}
	}

	if (!hasSpecial)
		return false;

	// Tum kriterler saglanmiyosa, sifre gucludur.
	return true;
};

#pragma endregion

void addProduct();
#pragma region islevsel Fonksiyonlar

Zaman adrese_gore_zaman_ekle(string adres) {

	Zaman eklenecekZaman;

	for (int i = 0; i < adres.length(); i++)
		adres[i] = tolower(adres[i]);

	if (adres == "ortahisar") {
		eklenecekZaman.saat = 0;
		eklenecekZaman.dakika = 35;
	}
	if (adres == "arakli") {
		eklenecekZaman.saat = 1;
		eklenecekZaman.dakika = 40;
	}
	if (adres == "yomra") {
		eklenecekZaman.saat = 0;
		eklenecekZaman.dakika = 55;
	}
	if (adres == "vakfikebir") {
		eklenecekZaman.saat = 1;
		eklenecekZaman.dakika = 30;
	}
	if (adres == "besikduzu") {
		eklenecekZaman.saat = 1;
		eklenecekZaman.dakika = 50;
	}
	if (adres == "akcaabat") {
		eklenecekZaman.saat = 0;
		eklenecekZaman.dakika = 50;
	}
	if (adres == "arsin") {
		eklenecekZaman.saat = 1;
		eklenecekZaman.dakika = 10;
	}

	return eklenecekZaman;
}


void kiyafet_kategori_al()
{

	ifstream dosya;
	double toplamFiyat = 0;
	vector<vector<string>> kiyafetler;
	vector<vector<string>> sepet;

	int b;
	while (true) {

		kiyafetler.clear();

		system("cls");
		cout << "Alisveris yapmak istediginiz kategoriyi seciniz: " << endl;
		cout << "1-) Elbise" << endl;
		cout << "2-) T-shirt" << endl;
		cout << "3-) Pantolon" << endl;
		cout << "4-) Gomlek" << endl;
		cout << "5-) Etek " << endl;
		cout << "6-) Ayakkabi" << endl;
		cout << "7-) Geri Don" << endl;
		cin >> b;

		switch (b)
		{
		case 1:
			dosya.open("elbise.txt");
			break;
		case 2:
			dosya.open("tshirt.txt");
			break;
		case 3:
			dosya.open("pantolon.txt");
			break;
		case 4:
			dosya.open("gomlek.txt");
			break;
		case 5:
			dosya.open("etek.txt");
			break;
		case 6:
			dosya.open("ayakkabi.txt");
			break;
		case 7:
			musteri_girisi();
			break;
		default:
			cout << "Lutfen gecerli bir islem seciniz." << endl;
			break;
		}

		string secilenIsim, secilenFiyat, isim, fiyat;

		int index = 0;
		string line;
		while (!dosya.eof()) {
			getline(dosya, line);

			if (line != "") {
				isim = line.substr(0, line.find("-"));
				fiyat = line.substr(line.find("-") + 1, line.length());

				kiyafetler.push_back({ isim, fiyat });

				cout << "Numara: " << ++index << endl;
				cout << "Urun adi: " << isim << endl;
				cout << "Urun fiyati: " << fiyat << endl;
				cout << "-------------------------" << endl;
			}
		}

		cout << "Almak istediginiz urunun numarasini girin." << endl;
		int secim2;
		cin >> secim2;

		secilenIsim = kiyafetler[secim2 - 1][0];
		secilenFiyat = kiyafetler[secim2 - 1][1];
		cout << "Sectiginiz urun: ";
		cout << "isim: " << secilenIsim << ",  fiyat: " << secilenFiyat << endl;
		cout << "Sectiginiz urunu ozellestirin." << endl;
		string renk, beden;
		cout << "Renk seciniz:" << endl;
		cin.get();
		getline(cin, renk);
		cout << "Beden seciniz: " << endl;
		getline(cin, beden);


		toplamFiyat += stod(secilenFiyat);

		sepet.push_back({ secilenIsim, secilenFiyat, beden, renk });

		Kiyafet kiy = Kiyafet(secilenIsim, renk, beden, stod(secilenFiyat));

		cout << "****** Secilen urun *****" << endl << "Urun adi:" << secilenIsim << endl << "Fiyat:" << secilenFiyat << endl << "Renk: " << renk << endl << "Beden: " << beden << endl;

		cout << endl << "Urun sepete eklenmistir. Alisverise devam etmek ister misiniz? y/n" << endl;



		char sec;
		cin >> sec;

		if (sec == 'n') {
			break;
		}
		dosya.close();
	}

	system("cls");
	cout << "Faturaniz ekte gosterilmektedir" << endl << endl;

	for (int i = 0; i < sepet.size(); i++) {
		cout << "Urun adi: " << sepet[i][0] << " Urun fiyati: " << sepet[i][1] << " Urun rengi: " << sepet[i][2] << "Urun bedeni: " << sepet[i][3] << endl;
	}


	// kurye seçme iþlemi yapýlacak.
	// yapýlan sipariþ siparisler.txt dosyasýne eklenecek. bu dosya içerisinde kurye adý, siparis saati, siparis bitiþ saati olacak.

	// burada sistem zamaný alýnacak ve ayarlanacak.
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%H", timeinfo);
	std::string saat(buffer);

	strftime(buffer, sizeof(buffer), "%M", timeinfo);
	std::string dakika(buffer);

	Zaman guncelZaman;
	guncelZaman.saat = stoi(saat);
	guncelZaman.dakika = stoi(dakika);

	Zaman siparisUlasimZamani = adrese_gore_zaman_ekle(mevcutKullanici.adres_ilce);

	// kurye secimi yapacagiz. dosyadaki kuryeleri okuyalim.
	ifstream kuryeDosyasi("courier.txt");



	vector<Kurye> kuryeler;
	Kurye guncel_kurye;
	Zaman kurye_son_siparis;
	string line, isim, dogumtarihi, kuryeZaman, zaman_dakika, zaman_saat;
	while (!kuryeDosyasi.eof()) {
		getline(kuryeDosyasi, line);

		if (line != "") {
			isim = line.substr(0, line.find("-"));
			dogumtarihi = line.substr(line.find("-") + 1, line.rfind("-") - line.find("-") - 1);
			kuryeZaman = line.substr(line.rfind("-") + 1, line.length());

			zaman_saat = kuryeZaman.substr(0, kuryeZaman.find(":"));
			zaman_dakika = kuryeZaman.substr(kuryeZaman.find(":") + 1, kuryeZaman.length());

			kurye_son_siparis.saat = stoi(zaman_saat);
			kurye_son_siparis.dakika = stoi(zaman_dakika);

			guncel_kurye.ad_soyad = isim;
			guncel_kurye.siparis_bitis = kurye_son_siparis;
			kuryeler.push_back(guncel_kurye);
		}
	}

	Kurye secilecek_kurye = kuryeler[0];
	vector<Kurye> guncel_kuryeler;


	// butun kuryeler icinde zamaný en küçük kuryeyi seçelim ve bunun zamanýný arttýralým.
	int index = 0;
	for (int i = 0; i < kuryeler.size(); ++i) {
		if (kuryeler[i].siparis_bitis < secilecek_kurye.siparis_bitis)
			index = i;
	}

	// adrese göre aldýðýmýz zamaný kuryeye ekliyoruz.
	for (int i = 0; i < kuryeler.size(); ++i) {
		if (i == index) {

			if (guncelZaman > kuryeler[i].siparis_bitis) {
				kuryeler[i].siparis_bitis = guncelZaman + siparisUlasimZamani;
				guncel_kuryeler.push_back(kuryeler[i]);
			}
			else {
				kuryeler[i].siparis_bitis = kuryeler[i].siparis_bitis + siparisUlasimZamani;
				guncel_kuryeler.push_back(kuryeler[i]);
			}

		}
		else {
			guncel_kuryeler.push_back(kuryeler[i]);
		}
	}



	// kurye dosyasini güncelleyelim.
	fstream file2;
	file2.open("courier.txt", ofstream::out | ofstream::trunc);
	file2.clear(); file2.close();

	file2.open("courier.txt", std::ios_base::app);
	for (int i = 0; i < guncel_kuryeler.size(); ++i) {
		file2 << endl << guncel_kuryeler[i].ad_soyad << "-" << to_string(guncel_kuryeler[i].siparis_bitis.saat) << ":" << to_string(guncel_kuryeler[i].siparis_bitis.dakika);
	}
	file2.close();

	// sipariþ txt dosyasýna bu sipariþi ekleyelim.
	ofstream file3("siparis.txt", ios::app);
	file3 << endl << mevcutKullanici.kullanici_adi << "-" << guncel_kuryeler[index].ad_soyad << "-" << to_string(guncelZaman.saat) << ":" << to_string(guncelZaman.dakika) << "-" << to_string(guncel_kuryeler[index].siparis_bitis.saat) << ":" << to_string(guncel_kuryeler[index].siparis_bitis.dakika);
	file3.close();

	//
	// faturayý txt ye ekleme yeri
	ofstream file("fatura.txt", ios::app);
	file << endl << mevcutKullanici.kullanici_adi << "-" << to_string(guncelZaman.saat) << ":" << to_string(guncelZaman.dakika) << "-" << to_string(guncel_kuryeler[index].siparis_bitis.saat) << ":" << to_string(guncel_kuryeler[index].siparis_bitis.dakika) << "-";

	for (int i = 0; i < sepet.size(); ++i) {
		file << "{" << sepet[i][0] << "  -  " << sepet[i][1] << "  -  " << sepet[i][2] << "  -  " << sepet[i][3] << "}";
	}
	file << "-" << toplamFiyat;
	file.close();
	//
	//

	cout << "Islem Basarili. Geri donmek icin bir tusa basiniz. " << endl;
	_getch();
}

void Elbise()
{
	system("cls");
	string name, size, color;
	double price;
	int stock;
	cout << "Elbise adi: ";
	cin.get();
	getline(cin, name);
	cout << "Elbise fiyati: ";
	cin >> price;

	//Kiyafet elbise1(name, size, color, price);
	ofstream file("elbise.txt", ios::app);
	file << endl << name << "-" << price;
	cout << "Islem Basarili. Geri donmek icin bir tusa basiniz. " << endl;
	file.close();
	_getch();
	addProduct();
}
void Pantolon()
{
	system("cls");
	string name, size, color;
	double price;
	int stock;
	cout << "Pantolon adi: ";
	cin.get();
	getline(cin, name);
	cout << "Pantolon fiyati: ";
	cin >> price;

	Kiyafet pantolon1(name, size, color, price);
	ofstream file("pantolon.txt", ios::app);
	file << endl << name << "-" << price;
	cout << "Islem Basarili. Geri donmek icin bir tusa basiniz. " << endl;
	file.close();
	_getch();
	addProduct();

}
void Gomlek()
{
	system("cls");
	string name, size, color;
	double price;
	int stock;
	cout << "Gomlek adi: ";
	cin.get();
	getline(cin, name);

	cout << "Gomlek fiyati: ";
	cin >> price;

	Kiyafet gomlek1(name, size, color, price);
	ofstream file("gomlek.txt", ios::app);
	file << endl << name << "-" << price;
	cout << "Islem Basarili. Geri donmek icin bir tusa basiniz. " << endl;
	file.close();

	_getch();
	addProduct();
}
void Etek()
{
	system("cls");
	string name, size, color;
	double price;
	int stock;
	cout << "Etek adi: ";
	cin.get();
	getline(cin, name);

	cout << "Etek fiyati: ";
	cin >> price;

	Kiyafet etek1(name, size, color, price);
	ofstream file("etek.txt", ios::app);
	file << endl << name << "-" << price;
	cout << "Islem Basarili. Geri donmek icin bir tusa basiniz. " << endl;
	file.close();

	_getch();
	addProduct();
}
void Ayakkabi()
{
	system("cls");
	string name, size, color;
	double price;
	int stock;
	cout << "Ayakkabi adi: ";
	cin.get();
	getline(cin, name);
	cout << "Ayakkabi fiyati: ";
	cin >> price;

	Kiyafet ayakkabi1(name, size, color, price);
	ofstream file("ayakkabi.txt", ios::app);
	file << endl << name << "-" << price;
	cout << "Islem Basarili. Geri donmek icin bir tusa basiniz. " << endl;
	file.close();

	_getch();
	addProduct();
}
void Tshirt()
{
	system("cls");
	string name, size, color;
	double price;
	int stock;
	cout << "Tshirt adi: ";
	cin.get();
	getline(cin, name);

	cout << "Tshirt fiyati: ";
	cin >> price;

	Kiyafet tshirt1(name, size, color, price);
	ofstream file("tshirt.txt", ios::app);
	file << endl << name << "-" << price;
	cout << "Islem Basarili. Geri donmek icin bir tusa basiniz. " << endl;
	file.close();

	_getch();
	addProduct();
}

void indirim_kodu_tanimla();

void fatura_goruntule() {
	system("cls");
	ifstream dosya("fatura.txt");

	int  id = 0;
	cout << "******* Sistemdeki faturalar ********" << endl << endl;
	int cizgi1, cizgi2, cizgi3, cizgi4;
	string line, kullanici_adi, kurye_adi, siparis_zamani, teslimat_zamani, urunler, fiyat;
	while (!dosya.eof()) {
		getline(dosya, line);

		if (line != "") {
			id++;

			cizgi1 = line.find('-');
			cizgi2 = line.find('-', cizgi1 + 1);
			cizgi3 = line.find('-', cizgi2 + 1);
			cizgi4 = line.rfind('-');


			kullanici_adi = line.substr(0, cizgi1);
			siparis_zamani = line.substr(cizgi1 + 1, cizgi2 - cizgi1 - 1);
			teslimat_zamani = line.substr(cizgi2 + 1, cizgi3 - cizgi2 - 1);
			urunler = line.substr(cizgi3 + 1, cizgi4 - cizgi3 - 1);
			fiyat = line.substr(cizgi4 + 1, line.length());

			cout << "***********************************" << endl;
			cout << "Siparis Numarasi: " << id << endl;
			cout << "Kullanici Adi: " << kullanici_adi << endl;
			cout << "Siparis Zamani: " << siparis_zamani << endl;
			cout << "Teslimat Zamani: " << teslimat_zamani << endl;
			cout << "Urunler: " << urunler << endl;
			cout << "Toplam Fiyat: " << fiyat << endl;
			cout << "***********************************" << endl;

		}
	}
}

void siparis_takip() {

	system("cls");
	ifstream dosya("siparis.txt");

	cout << "******* Yapmis oldugunuz siparisler ********" << endl << endl;

	int cizgi1, cizgi2, cizgi3;
	string line, kullanici_adi, kurye_adi, siparis_zamani, teslimat_zamani;
	while (!dosya.eof()) {
		getline(dosya, line);

		if (line != "") {

			cizgi1 = line.find('-');
			cizgi2 = line.find('-', cizgi1 + 1);
			cizgi3 = line.find('-', cizgi2 + 1);


			kullanici_adi = line.substr(0, cizgi1);
			kurye_adi = line.substr(cizgi1 + 1, cizgi2 - cizgi1 - 1);
			siparis_zamani = line.substr(cizgi2 + 1, cizgi3 - cizgi2 - 1);
			teslimat_zamani = line.substr(cizgi3 + 1, line.length());

			if (kullanici_adi == mevcutKullanici.kullanici_adi) {
				cout << "***********************************" << endl;
				cout << "Kullanici Adi: " << kullanici_adi << endl;
				cout << "Teslim Edecek Kurye: " << kurye_adi << endl;
				cout << "Siparis Zamani: " << siparis_zamani << endl;
				cout << "Teslimat Zamani: " << teslimat_zamani << endl;
				cout << "***********************************" << endl;
			}

		}
	}
}


#pragma endregion


#pragma region Yonetici fonksiyonlar
void kiyafet_kategori();
void yonetici_girisi();

void addProduct()
{
	kiyafet_kategori();
}

void addCourier()
{
	system("cls");
	string name;
	string surname;
	string date_of_birth;

	cout << "Kurye adi: ";
	cin.get();
	getline(cin, name);
	cout << "Kurye soyadi:";
	getline(cin, surname);


	ofstream outfile("courier.txt", ios::app);                         //BUNUN TXTSINI YAZ
	outfile << endl << name << " " << surname << "-00:00" << endl;    //TXT'YE HATALI YAZIYOR

	cout << "Islem basarili. Geri donmek icin bir tusa basiniz." << endl;
	_getch();
	yonetici_girisi();
}

void showFeedback()
{
	system("cls");
	ifstream infile("feedback.txt");

	// Dosya acilirken bir hata olustuysa uyari mesaji veriyor
	if (!infile.is_open())
	{
		cout << "Dosya acilamadi!" << endl;
		return;
	}


	string line;
	while (getline(infile, line))
	{

		cout << line << endl << "***************" << endl;


	}
	cout << endl << endl;
}
#pragma endregion


#pragma region Kullanici fonksiyonlari


void addFeedback()
{
	system("cls");
	string feedback;
	cout << "Lutfen sikayet veya onerinizi yaziniz: ";
	cin.get();
	getline(cin, feedback);

	ofstream outfile("feedback.txt", ios::app);
	outfile << feedback << endl;

	cout << "Geri donmek icin bir tusa basiniz." << endl;
	_getch();
}


void changePassword()

{
	system("cls");
	ifstream getInfo("user.txt");
	ofstream temp("temp.txt");

	string line;
	string check;
	cout << "Kullanici adini giriniz: ";
	cin.get();
	getline(cin, check);


	while (!getInfo.eof())
	{
		getline(getInfo, line);
		string username = line.substr(0, line.find("-"));
		if (check == username)
		{

			string newPassword;
			cout << "Yeni Sifreyi Giriniz: ";
			cin >> newPassword;
			temp << username << "-" << newPassword << endl;
		}

		else
		{
			temp << line << endl;
		}

	}
	getInfo.close();
	temp.close();

	remove("user.txt");
	rename("temp.txt", "user.txt");

	cout << "Islem Basarili" << endl;
	cout << "Geri donmek icin bir tusa basiniz . " << endl;
	_getch();

}


#pragma endregion


#pragma region Menuler
void sisteme_giris();



void yonetici_girisi()
{

	system("cls");
	int x;
	cout << "Yapmak istediginiz islemi seciniz: " << endl;
	cout << "1-) Urun Girisi" << endl;
	cout << "2-) Sisteme kurye ekle" << endl;
	cout << "3-) Sikayet ve oneri oku" << endl;
	cout << "4-) Kullaniciya indirim kodu tanimla" << endl;
	cout << "5-) Yapilan siparisin faturasini goruntule" << endl;
	cout << "6-) Geri Don" << endl;
	cin >> x;

	switch (x)
	{
	case 1:
		addProduct();
		break;
	case 2:
		addCourier();
		break;
	case 3:
		showFeedback();
		break;

	case 4:
		//indirim_kodu_tanimla();					 //fonksiyon yazilacak
		break;
	case 5:
		fatura_goruntule();						 //fonksiyon yazilacak
		break;
	case 6:
		sisteme_giris();
		break;
	default:
		cout << "Lutfen gecerli bir islem giriniz." << endl;
		break;

	}
	_getch();
	yonetici_girisi();
}

void musteri_girisi()
{
	system("cls");
	int a;
	cout << "Lutfen yapmak istediginiz islemi seciniz: " << endl;
	cout << "1-) Kiyafet kategorisi ve urun secimi" << endl;
	cout << "2-) Siparis takip" << endl;
	cout << "3-) Sikayet ve oneri yaz" << endl;
	cout << "4-) Sifre degistir" << endl;
	cout << "5-) Geri don" << endl;
	cin >> a;
	switch (a)
	{
	case 1:
		kiyafet_kategori_al();					 //fonksiyon yazilacak
		break;
	case 2:
		siparis_takip();					 //fonksiyon yazilacak
		break;
	case 3:
		addFeedback();
		break;
	case 4:
		changePassword();
		break;
	case 5:
		sisteme_giris();
		break;
	default:
		cout << "Lutfen gecerli bir islem seciniz." << endl;
		break;
	}
	_getch();
	musteri_girisi();
}

void uye_kaydi()
{
	system("cls");
	ofstream user;
	user.open("user.txt", ios::app);

	string name, password, adress;
	cout << "Kullanici adi giriniz: ";
	cin.get();
	getline(cin, name);


	int uzunluk = 0;
	while (true) {
		cout << "Sifre Giriniz: ";
		int ch;

		while ((ch = _getch()) != '\r') {

			if (ch == '\b' && uzunluk != 0) {
				password.pop_back();
				uzunluk--;
				cout << "\b \b";
			}
			else {
				putchar('*');
				uzunluk++;
				password += ch;
			}
		}
		if (!isStrongPassword(password)) {
			cout << endl << "Lutfen guclu sifre giriniz!" << endl;

		}
		else {
			break;
		}
	}
	cout << "\nAdres bilgisi giriniz: " << endl;
	cin >> adress;


	for (int i = 0; i < adress.size(); i++)
	{
		adress[i] = tolower(adress[i]);
	}

	if (adress == "vakfikebir")
	{
		user << name << "-" << password << "-" << adress << endl;
		cout << "Uye kaydi basarili." << endl;
	}

	else if (adress == "akcaabat")
	{
		user << name << "-" << password << "-" << adress << endl;
		cout << "Uye kaydi basarili." << endl;
	}


	else if (adress == "yomra")
	{
		user << name << "-" << password << "-" << adress << endl;
		cout << "Uye kaydi basarili." << endl;
	}

	else if (adress == "ortahisar")
	{
		user << name << "-" << password << "-" << adress << endl;
		cout << "Uye kaydi basarili." << endl;
	}

	else if (adress == "besikduzu")
	{
		user << name << "-" << password << "-" << adress << endl;
		cout << "Uye kaydi basarili." << endl;
	}

	else if (adress == "arsin")
	{
		user << name << "-" << password << "-" << adress << endl;
		cout << "Uye kaydi basarili." << endl;
	}

	else if (adress == "arakli")
	{
		user << name << "-" << password << "-" << adress << endl;
		cout << "Uye kaydi basarili." << endl;
	}
	else {
		cout << "Adres bilgisi hatali!" << endl;
		cout << "Menuye donmek icin bir tusa basiniz.";
		user.close();
		_getch();
		Start_menu();

	}


	user.close();

	cout << "\nKaydiniz olusturuldu." << endl;
	cout << "Menuye donmek icin bir tusa basiniz.";
	_getch();
	Start_menu();

}

void kiyafet_kategori()
{
	system("cls");
	int b;
	cout << "Lutfen kategori seciniz: " << endl;
	cout << "1-) Elbise" << endl;
	cout << "2-) T-shirt" << endl;
	cout << "3-) Pantolon" << endl;
	cout << "4-) Gomlek" << endl;
	cout << "5-) Etek " << endl;
	cout << "6-) Ayakkabi" << endl;
	cout << "7-) Geri Don" << endl;
	cin >> b;
	switch (b)
	{
	case 1:
		Elbise();
		break;
	case 2:
		Tshirt();
		break;
	case 3:
		Pantolon();
		break;
	case 4:
		Gomlek();
		break;
	case 5:
		Etek();
		break;
	case 6:
		Ayakkabi();
		break;
	case 7:
		yonetici_girisi();
		break;
	default:
		cout << "Lutfen gecerli bir islem seciniz." << endl;
		break;
	}
}

void sisteme_giris()
{
	system("cls");
	int giris_islem2;
	cout << "1-) Yonetici Girisi" << endl;
	cout << "2-) Musteri Girisi" << endl;
	cout << "3-) Geri don" << endl;
	cin >> giris_islem2;
	switch (giris_islem2)
	{
	case 1:
		system("cls");
		if (yonetici_kontrol() == true)
		{
			yonetici_girisi();

		}

		else {
			cout << "Kullanici adi veya sifre yanlis." << endl;
			cout << "Geri donmek icin bir tusa basiniz." << endl;
			_getch();
			Start_menu();
			break;
		}
		break;



	case 2:
		system("cls");

		if (musteri_kontrol() == true)
		{
			return musteri_girisi();
		}
		else {

			cout << "Giris basarisiz" << endl;
			cout << "devam etmek icin tusa basiniz" << endl;
			_getch();
		}
		break;


	case 3:
		system("cls");
		Start_menu();
		break;
	default:
		cout << "Lutfen gecerli bir islem seciniz." << endl;
		break;
	}

	sisteme_giris();
}



#pragma endregion
void Start_menu()
{
	system("cls");
	int giris_islem;
	cout << "Lutfen yapmak istediginiz islemi seciniz : " << endl;
	cout << "1-) Sisteme giris " << endl;
	cout << "2-) Uye Kaydi" << endl;
	cout << "3-) Sistemden cikis " << endl;
	cin >> giris_islem;

	switch (giris_islem)
	{
	case 1:
		sisteme_giris();
		break;
	case 2:
		uye_kaydi();
		break;
	case 3:
		exit(0);
		break;
	default:
		cout << "Lutfen gecerli bir islem seciniz." << endl;
		break;
	}


}


int main()
{
	Start_menu();
}

