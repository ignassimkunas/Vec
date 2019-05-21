/**
* @file fun.cpp
* @author Ignas Šimkūnas
* @brief Funkcijų failas.
**/
#include "fun.h"

void Student::readData(std::ifstream &read) {

	int temp;
	std::string s;
	std::getline(read, s);
	std::stringstream stream;
	stream << s;
	stream >> vardas_ >> pavarde_;
	while(stream){
		stream >> temp;
		nd_.push_back(temp);
	}
	egzaminas_ = nd_.at(nd_.size() - 1);
	nd_.pop_back();
}
	
Student::Student(const Student& s){
	vardas_ = s.vardas_;
	pavarde_ = s.pavarde_;
	nd_ = s.nd_;
	egzaminas_ = s.egzaminas_;
 	vidurkis_ = s.vidurkis_;
	mediana_= s.mediana_;
	galutinis_ = s.galutinis_;
}

void Student::addData() {
		int pazym, egzaminas;
		int atsitiktiniuSkaicius;
		char atsitiktChar;
		std::cout << "Iveskite studento varda, pavarde ir egzamino pazymi." << std::endl;
		//Operatoriaus >> panaudojimas.
		std::cin >> *this;
 		std::cout << "Ar norite parinkti atsitiktinius namų darbų pazymius? (y/n)";
		std::cin >> atsitiktChar;
		//Kol vartotojas neįveda y arba n raidžių, tol išvedama, kad įvesta neteisinga raidė.
		while (atsitiktChar != 'y') {
			if (atsitiktChar == 'n')
				break;
			else {
				std::cout << "Ivesta ne ta raide\n";
				std::cout << "Ar norite parinkti atsitiktinius pazymius? (y/n) ";
				std::cin >> atsitiktChar;
			}	
		}
		if (atsitiktChar == 'n'){	
			std::cout << "Iveskite pazymius \nKai noresite pabaigti, iveskite bet kokia raide. \n";
			//Vartotojas įvedinėja pažymius, kurie dedami į vectorių nd, kai nusprendžia, kad nebėra pažymių, įveda bet kokią raidę.
			while (true){
				std::cin >> pazym;
				if (pazym < 0 || pazym > 10) {
					std::cout << "Pazymiai turi buti nuo 0 iki 10.\n";
					continue;
				}
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore();
					break;
				}
				nd_.push_back(pazym);
			}
		}
		else if (atsitiktChar == 'y') {
			return genRandom();
		}
	}
void Student::getResults(char vidArMed){
	if (vidArMed == 'v') {
		if (nd_.size() == 0)
			vidurkis_ = 0;
		else {
			for (std::size_t x = 0; x < nd_.size(); x++)
				vidurkis_ += nd_.at(x);
			vidurkis_ /= nd_.size();
		}
		galutinis_ = 0.4 * vidurkis_ + 0.6 * egzaminas_;
	}
	else {
		sort(nd_.begin(), nd_.end());
		if (nd_.size() == 0)
			mediana_ = 0;
		else if (nd_.size() % 2 == 0)
			mediana_ = (nd_.at(nd_.size() / 2) + nd_.at(nd_.size() / 2 - 1)) / 2;
		else
			mediana_ = nd_.at(nd_.size() / 2);
		galutinis_ = 0.4 * mediana_ + 0.6 * egzaminas_;
	}
}
//Atsitiktinių namų darbų generavimo funkcija.
void Student::genRandom() {
	int atsitiktiniuSkaicius = rand() % 100 + 1;
	for (size_t x = 0; x < atsitiktiniuSkaicius; x++) {
		nd_.push_back(rand() % 10 + 1);
	}
	egzaminas_ = rand() % 10 + 1;
}
bool compareLetter(Student &a, Student &b){
	return a.vardas() < b.vardas();
}
//Apskaičiuoja tarpo tarp lentelės elementų dydį gražiam lygiavimui.
size_t tarpIlgis(Vector<Student> &studentVec) {
	size_t pavardesIlgis = 0;
	size_t tarpoIlgis;
	for (std::size_t x = 0; x < studentVec.size(); x++) {
		if (studentVec.at(x).pavarde().length() > pavardesIlgis) {
			pavardesIlgis = studentVec.at(x).pavarde().length();
		}
	}
	if (pavardesIlgis <= 3) {
		tarpoIlgis = 15;
	}
	else {
		tarpoIlgis = pavardesIlgis + 10;
	}
	return tarpoIlgis;
}
//Spausdina lentelę.
void printTable(Student student, int tarpoIlgis) {
	std::cout << std::left <<std::setw(tarpoIlgis) << student.vardas();
	std::cout << std::setw(tarpoIlgis) << student.pavarde();
	std::cout << std::fixed << std::setprecision(2) << student.galutinis() ;
}
void writeTable(Student student, int tarpoIlgis, std::ofstream &write) {
	write << std::left <<std::setw(tarpoIlgis) << student.vardas();
	write << std::setw(tarpoIlgis) << student.pavarde();
	write << std::fixed << std::setprecision(2) << student.galutinis();
}
void print(Vector<Student> studentVec) {
	int bruksnSize = tarpIlgis(studentVec) * 2 + galutinisString.length();
	std::cout << std::left << std::setw(tarpIlgis(studentVec)) << vardasString;
	std::cout << std::setw(tarpIlgis(studentVec)) << pavardeString;
	std::cout << std::setw(tarpIlgis(studentVec)) << galutinisString;
	std::cout << std::endl;
	for (std::size_t i = 0; i < bruksnSize; i++)
		std::cout <<"-";
	std::cout<< std::endl;
	for (std::size_t x = 0; x < studentVec.size(); x++) {
		printTable(studentVec.at(x), tarpIlgis(studentVec));
		std::cout << std::endl;
	}
}
void write(Vector<Student> studentVec, std::string fileWrite) {

	std::ofstream write (fileWrite, std::ofstream::out);
	int tarpoIlgis = tarpIlgis(studentVec);

	for (std::size_t x = 0; x < studentVec.size(); x++) {
		writeTable(studentVec.at(x), tarpoIlgis, write);
		write << std::endl;
	}
}
void writeVec(Vector<Student> studentVec, std::ofstream &write) {

	int tarpoIlgis = tarpIlgis(studentVec);
	int bruksnSize = tarpoIlgis * 2 + galutinisString.length();
	write << std::left << std::setw(tarpoIlgis) << vardasString;
	write << std::setw(tarpoIlgis) << pavardeString;
	write << std::setw(tarpoIlgis) << galutinisString;
	write << std::endl;

	for (std::size_t i = 0; i < bruksnSize; i++) {
		write << "-";
	}

	write<< std::endl;
	for (std::size_t x = 0; x < studentVec.size(); x++) {
		writeTable(studentVec.at(x), tarpoIlgis, write);
		write << std::endl;
	}
}
//Rūšiuoja studentus į vargšiukus.
Vector<Student> sortVargsVec(Vector<Student> studentVec) {

	Vector<Student> vargsiukai;

	for (std::size_t i = 0; i < studentVec.size(); i++) {
		if (studentVec.at(i).galutinis() < 5.0) {
			vargsiukai.push_back(studentVec.at(i));
		}
	}
	return vargsiukai;
}

//Rūšiuoja studentus į kietiakus.
Vector<Student> sortKietVec(Vector<Student> studentVec) {

	Vector<Student> kietiakai;
	for (std::size_t i = 0; i < studentVec.size(); i++) {
		if (studentVec.at(i).galutinis() >= 5.0) {
			kietiakai.push_back(studentVec.at(i));
		}
	}
	return kietiakai;
}

//Nuskaito failą ir sudeda duomenis į vektorių.
Vector<Student> fileToVector(Vector<Student> studentVec, std::string fileName) {
	Student student;
	std::ifstream read(fileName);
	std::string vardas, pavarde;
	double galutinis;
	while (!read.eof()){
		read >> vardas >> pavarde >> galutinis;
		student.setVardas(vardas);
		student.setPavarde(pavarde);
		student.setGalutinis(galutinis);
		studentVec.push_back(student);
	}
	read.close();
	return studentVec;
}

//Pakeist, kad nenaudotų funkcijų
//Generuoja studentų duomenų failą.
void generateFile(char vidArMed, int studentuSk, std::string fileName) {

	std::ofstream write(fileName);
	double random;
	auto start = std::chrono::high_resolution_clock::now();
	for (std::size_t x = 0; x < studentuSk; x++) {
		srand(x + time(NULL));
		random = ((double)rand() / RAND_MAX) * 10;
		write << "Vardas" + std::to_string(x + 1) << std::setw(15);
		write << "Pavarde" + std::to_string(x + 1) << std::setw(15);
		write << random << std::fixed << std::setprecision(2) << "\n";
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end-start;
	std::cout << std::to_string(studentuSk) + " elementų generavimas truko: " << diff.count() << "\n";
}