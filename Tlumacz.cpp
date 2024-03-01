#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "List3.h"
#include "Word.h"
#include "WordInf.h"
#include "Verb.h"
#include "VerbDictionary.h"
#include "Dictionary.h"


void Split(const std::string& sentence, List<std::string>& list) {

	std::istringstream iss(sentence);

	std::string word;
	while (iss >> word) {
		list.addElement(word);
	}
	/*
	for (auto& el : list) {
		std::cout << el << "\n";
	}
	*/
	if (list.getSize() != 0) {
		std::string& lastWord = list.getElementAt(list.getSize() - 1);
		if (lastWord.back() == '.') {
			lastWord.pop_back();
		}
	}
	/*
	std::cout << "\n" << std::endl;

	for (auto& el : list) {
		std::cout << el << "\n";
	}
	*/
}

std::string ToLowerCase(const std::string& word) {
	std::string result = word;
	for (int i = 0; i < word.length(); i++) {
		result[i] = std::tolower(result[i]);
	}
	return result;
}

void LoadWithoutInfo(Dictionary& dictionary, const std::string& name) {
	std::ifstream file{ name };
	if (!file.is_open()) {
		throw std::runtime_error("Nie udalo sie otworzyc pliku wejsciowego ze slowami bez dodatkowymi informacjami.");
	}
	else {
		std::string word, translation;
		int person, form;
		while (file >> word >> translation >> person >> form) {

			dictionary.addTranslation(word, translation);
			dictionary.addInfo(word, WordInf(person, form));

		}

		//dictionary.print();
		file.close();
	}

}

void LoadWithInfo(Dictionary& dictionary, const std::string& name) {
	std::ifstream file{ name };
	if (!file.is_open()) {
		throw std::runtime_error("Nie udalo sie otworzyc pliku wejsciowego ze slowami z dodatkowymi informacjami.");
	}
	else {
		std::string word;
		std::string translation;
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			if (std::getline(iss, word, ' ')) {
				std::getline(iss, translation);
				dictionary.addTranslation(word, translation);
			}
			else {
				throw std::runtime_error(std::string{ "Nie udalo sie wczytac linii:" } + line + " .");
			}
		}
		file.close();

	}
}
                                                           //z inf               //z odmienionym
void Loading(VerbDictionary& dictionary, const std::string& name_translations, const std::string& name_forms) {
	std::ifstream file1{ name_translations };
	std::ifstream file2{ name_forms };
	if (!file1.is_open() || !file2.is_open()) {
		throw std::runtime_error("Nie udalo sie otworzyc plikow wejsciowych.");
	}
	else {
		std::string word, translation1, translation2;
		while (file1 >> word >> translation1 >> translation2) {
			Verb verb{ word, translation1, translation2 };
			if (verb.isEmpty()) {
				throw std::runtime_error("Blad przy wczytywaniu orzeczen i tlumaczen.");
			}
			dictionary.addVerb(verb);
		}

		std::string og_word, inf_word;
		while (file2 >> og_word >> inf_word) {
			if (og_word == "" || inf_word == "") {
				throw std::runtime_error("Blad przy wczytywaniu form i bezokolicznika.");
			}
			if (dictionary.hasVerb(inf_word)) {
				Verb& verb = dictionary.getVerb(inf_word);
				verb.addForm(og_word);
			}

		}
		file1.close();
		file2.close();
	}
}

List<std::string> Translation(const List<std::string>& sentence, const Dictionary& subjects, const Dictionary& adverbs, const VerbDictionary& verbs, const Dictionary& complements) {
	List<std::string> translation;

	WordInf subInfo;
	std::string ad;

	for (auto& el : sentence) {
		if (subjects.hasTranslation(el)) {
			subInfo = subjects.getInfo(el);
			translation.addElement(subjects.getTranslation(el));
		}
		else if (adverbs.hasTranslation(el)) {
			ad = adverbs.getTranslation(el);
			translation.addElement(ad);
		}
		else if (verbs.hasTranslation(el)) {
			translation.addElement(verbs.getTranslation(el, subInfo));
		}
		else if (complements.hasTranslation(el)) {
			translation.addElement(complements.getTranslation(el));
		}
		else if (el == "nie") {
			if (ad == "never") {

			}
			else {
				if (subInfo.getPerson() == 3 && subInfo.getForm() == 1) {
					translation.addElement("doesn't");
				}
				else
					translation.addElement("don't");
			}
		}
		else if (el == "do") {
			translation.addElement("to");
		}
		else
			throw std::runtime_error(std::string{ "Slowa: " } + el + " nie ma w zadnym slowniku.");
	}

	std::string& f = translation.getElementAt(0);
	f[0] = std::toupper(f[0]);

	return translation;
}

int main()
{
	/*
	List<int> lista;
	lista.addElement(10);
	lista.addElement(70);
	lista.addElement(5);
	lista.addElement(66);
	auto wynik = std::find(lista.begin(), lista.end(), 79);
	if (wynik != lista.end()) {
		std::cout << "Znaleziono element." << std::endl;
	}
	else {
		std::cout << "Nie znaleziono elementu." << std::endl;
	}

	List<int> list;
	list.addElement(70);
	list.addElement(5);
	list.addElement(30);
	list.addElement(40);
	list.addElement(66);

	auto first = ++lista.begin();
	auto last = ++++++lista.begin();
	auto wynik2 = std::search(list.begin(), list.end(), first, last);
	if (wynik2 != list.end()) {
		std::cout << "Znaleziono." << std::endl;
		*wynik2 = 100;
	}
	else {
		std::cout << "Nie znaleziono." << std::endl;
	}

	for (auto& el : list) {
		std::cout << el << std::endl;
	}
	*/
	
	try {
		//////////wczytywanie slownikow//////////
		Dictionary subjects; //1.
		LoadWithoutInfo(subjects, "plikPodmiot.txt");

		Dictionary adverbs; //2.
		LoadWithInfo(adverbs, "plikPrzysl.txt");

		VerbDictionary verbs; //3.
		Loading(verbs, "plikO1.txt", "plikO2.txt");

		Dictionary complements; //4.
		LoadWithInfo(complements, "plikDopel.txt");

		//////////wczytywanie zdania//////////
		std::string input;
		List<std::string> list2; //zdanie

		std::ifstream file{ "zdanie.txt" };
		if (!file.is_open()) {
			std::cout << "Pliku nie udalo sie otworzyc." << std::endl;
			return 0;
		}
		std::getline(file, input);

		file.close();

		//////////dzielenie na elementy i sprowadzanie do malej litery//////////
		Split(input, list2);
		for (auto& el : list2) {
			el = ToLowerCase(el);
		}

		//////////tlumaczenie//////////
		List<std::string> translation = Translation(list2, subjects, adverbs, verbs, complements);

		std::cout << "\n" << std::endl;

		//////////wypisywanie//////////
		for (int i = 0; i < translation.getSize(); i++) {
			std::cout << translation.getElementAt(i);
			if (i < translation.getSize() - 1) {
				std::cout << " ";
			}
			else {
				std::cout << ".";
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
	
}

////////////////Przyklady zdan do przetlumaczenia////////////////

//on idzie spac
//he goes to sleep

//oni czesto jezdza samochodem
//they often drive a car

//ona nigdy nie czyta ksiazek
//she never reads books

//ja czasami czytam ksizake
//i sometimes read a book

//oni zawsze gotuja obiad
//they always cook dinner

//ona zawsze gotuje obiad
//she always cooks (a) dinner

//ty czesto chodzisz do kina
//you often go to the cinema

//ty czesto chodzisz poplywac
//you often go swimming

//ona nie czesto jezdzi samochodem
//she doesn't often drive a car