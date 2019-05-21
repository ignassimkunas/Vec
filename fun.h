#include <iostream>

/**
* @file fun.h
* @author Ignas Šimkūnas
* @brief Header failas.
* \mainpage Aprašymas
* Objektinio programavimo 3 užduotis.
**/

#include <vector>
#include <list>
#include <queue>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "vector.h"

class Zmogus {
protected:
	std::string vardas_;
	std::string pavarde_;
public:
	/** \brief nustato vardą*/
	virtual void setVardas(std::string) = 0;
	/** \brief nustato pavardę*/
	virtual void setPavarde(std::string) = 0;
	/** \brief grąžina vardą*/
	std::string vardas() {return vardas_;}
	/** \brief grąžina pavardę*/
	std::string pavarde()  {return pavarde_;}
};

class Student: public Zmogus{
private:
	std::vector<int> nd_;
	int egzaminas_;
	double vidurkis_;
	double mediana_;
	double galutinis_;
public:
	/** \brief konstruktorius */
	Student(): egzaminas_(0), vidurkis_(0), galutinis_(0){} 
	/** \brief konstruktorius, kai paduodamas studento galutinis balas */
	Student(double gal): galutinis_{gal} {}
	Student(std::string v, std::string pav, double gal){
		vardas_ = v;
		pavarde_ = pav;
		galutinis_ = gal;
	}
	/** \brief copy konstruktorius */
	//Student(const Student& s); 
	/** \brief destruktorius */
	~Student() {}; 
	/** \brief grąžina studento gautinį balą */
	double galutinis() {return galutinis_;}
	/** \brief grąžina vector konteinerį, kuriame laikomi studento namų darbų pažymiai */
	std::vector<int> nd() {return nd_;}
	/** \brief grąžina studento pažymių vidurkį */
	double vidurkis() {return vidurkis_;}
	/** \brief grąžina studento pažymių medianą */
	double mediana() {return mediana_;}
	/** \brief grąžina studento egzamino balą */
	int egzaminas() {return egzaminas_;}
	/** \brief prideda prie studento galutinio balo kito studento galutinį balą */
	Student& operator+=(Student c) {galutinis_ += c.galutinis_;}
	/** \brief atima iš studento galutinio balo kito studento galutinį balą */
	Student& operator-=(Student c) {galutinis_ -= c.galutinis_;}
	/** \brief sudaugina studento galutinį balą su kito studento galutiniu balu */
	Student& operator*=(Student c) {galutinis_ *= c.galutinis_;}
	/** \brief priskiria studento objektui kitą studento objektą */
	Student& operator=(const Student& v){
	  if (&v == this) return *this;
	  vardas_ = v.vardas_;
	  pavarde_ = v.pavarde_;
	  nd_ = v.nd_;
	  egzaminas_ = v.egzaminas_;
	  vidurkis_ = v.vidurkis_;
	  mediana_= v.mediana_;
	  galutinis_ = v.galutinis_;
	  return *this;
	}
	/** \brief atima dviejų studentų galutinius balus */
	friend Student operator-(const Student &a, const Student &b){
	  return Student {a.galutinis_ - b.galutinis_};
	}
	/** \brief prideda dviejų studentų galutinius balus */
	friend Student operator+(const Student &a, const Student &b){
	  return Student {a.galutinis_ + b.galutinis_};
	}
	/** \brief sudaugina dviejų studentų galutinius balus */
	friend Student operator*(const Student &a, const Student &b){
	  return Student {a.galutinis_ * b.galutinis_};
	}
	/** \brief išveda studento vardą, pavardę ir galutinį balą */
	friend std::ostream& operator<<(std::ostream& out, const Student &a){
	  out << a.vardas_ << " " << a.pavarde_ << " " << a.galutinis_;
	  return out;
	}
	/** \brief įveda studento vardą, pavardę ir galutinį balą */
	friend std::istream& operator>>(std::istream& in, Student &a){
	  in >> a.vardas_ >> a.pavarde_ >> a.egzaminas_;
	  return in;
	}
	/** \brief grąžina bool tipo reikšmę, parodanti ar studento vardas, pavardė bei galutiniai balai lygūs */
	friend bool operator==(Student a, Student b) {
	  return a.galutinis_ == b.galutinis_ && a.vardas_ == b.vardas_ && a.pavarde_ == b.pavarde_;
	}
	/** \brief grąžina bool tipo reikšmę parodanti ar studento vardas, pavardė bei galutiniai balai nėra lygūs */
	friend bool operator!=(Student a, Student b) {
	  return !(a == b);
	}
	/** \brief nustato studento vardą */
	void setVardas(std::string v){vardas_ = v;}
	/** \brief nustato studento pavardę */
	void setPavarde(std::string p){pavarde_ = p;}
	/** \brief priskiria duoto vector konteinerio reikšmes studento namų darbų reikšmėms */
	void setNd(std::vector<int> vec) {nd_ = vec;}
	/** \brief nustato studento egzamino balą */
	void setEgzaminas(int egz) {egzaminas_ = egz;}
	/** \brief nustato studento namų darbų vidurkį */
	void setVidurkis(double vid) {vidurkis_ = vid;}
	/** \brief nustato studento namų darbų medianą */
	void setMediana(double med) {mediana_ = med;}
	/** \brief nustato studento namų darbų galutinį balą */
	void setGalutinis(double gal) {galutinis_ = gal;}
	/** \brief nuskaito studento duomenis */
	void readData(std::ifstream&);
	/** \brief įvedami studento duomenys konsolėje */
	void addData();
	/** \brief nustato studento vidurkį arba medianą pagal namų darbų pažymius */
	void getResults(char);
	/** \brief sugeneruoja atsitiktinius studento namų darbų pažymius */
	void genRandom();
};
const std::string vardasString = "Vardas";
const std::string pavardeString = "Pavarde";
const std::string galutinisString = "Galutinis";
const std::string file10String = "f10.txt";
const std::string file100String = "f100.txt";
const std::string file1000String = "f1000.txt";
const std::string file10000String = "f10000.txt";
const std::string file100000String = "f100000.txt";
/** \brief palyginimo funkcija rūšiavimui pagal alfabetą */
bool compareLetter(Student&, Student&);
/** \brief funkcija skirta lentelės tarpo ilgiui apskaičiuoti */
size_t tarpIlgis(Vector<Student>&);
/** \brief funkcija studento duomenų spausdinimui į lentelę */
void printTable(Student, int);
/** \brief funkcija studento duomenų spausdinimui į failą */
void writeTable(Student, int, std::ofstream&);
/** \brief studentų vektoriaus spausdinimo į lentelę funkcija */
void print(Vector<Student>);
/** \brief studentų vektoriaus spausdinimo į failą funkcija, kai paduodamas failo pavadinimas */
void write(Vector<Student>, std::string);
/** \brief studentų vektoriaus spausdinimo į failą funkcija, kai paduodamas ofstream */
void writeVec(Vector<Student>, std::ofstream&);
/** \brief grąžina išrūšiuota studentų vektorių, kuriame lieka vien "kietiakai" */
Vector<Student> sortKietVec(Vector<Student>);
/** \brief grąžina išrūšiuota studentų vektorių kuriame lieka vien "vargšiukai" */
Vector<Student> sortVargsVec(Vector<Student>);
/** \brief išspausdina vektoriuje esančius studentų duomenis į failą pagal failo pavadinimą */
Vector<Student> fileToVector(Vector<Student>, std::string);
/** \brief sugeneruoja failą su duotu skaičiumi studentų ir failo pavadinimu */
void generateFile(char, int, std::string);

