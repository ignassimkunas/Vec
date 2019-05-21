#include <iostream>
#include <chrono>
#include <vector>
#include "fun.h"
template <typename T>
void kiekTrunka(size_t count, T param){
	Vector<T> v1;
	std::vector<T> v2;
	auto start = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < count; i++){
		v1.push_back(i);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end-start;
	std::cout << "Vector užpildymas su " << count << " elementų truko: " << diff.count() << "\n";
	start = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < count; i++){
		v2.push_back(i);
	}
	end = std::chrono::high_resolution_clock::now();
	diff = end-start;
	std::cout << "std::vector užpildymas su " << count << " elementų truko: " << diff.count() << "\n\n";
}
int main(){
	Student student;
	std::cout << "Su integer: \n";
	for (auto i = 10000; i <= 10000000; i *= 10){
		kiekTrunka(i, 1);
	}
	std::cout <<"Su student: \n";
	for (auto i = 10000; i <= 10000000; i *= 10){
		kiekTrunka(i, student);
	}
}