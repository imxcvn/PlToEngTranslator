#pragma once

class VerbDictionary {
private:
	List<Verb> list;
public:
	void addVerb(const Verb& v) {
		list.addElement(v);
	}
	bool hasTranslation(const std::string& word) const {   //dla oryginalnego slowa
		for (auto& el : list) {
			if (el.hasWord(word)) {
				return true;
			}
		}
		return false;
	}
	const Verb& getVerbToTranslate(const std::string& w) const {   //verb (oryginalne slowo)
		for (auto& el : list) {
			if (el.hasWord(w)) {
				return el;
			}
		}
		throw std::runtime_error(std::string{ "Slowa: " } + w + "nie ma w liscie form orzeczenia.");
	}
	bool hasVerb(const std::string& w) const {   //dla bezokolicznika
		for (auto& el : list) {
			if (el.getInfinitive() == w) {
				return true;
			}
		}
		return false;
	}
	Verb& getVerb(const std::string& w) {   //verb (dla bezokolicznika)
		for (auto& el : list) {
			if (el.getInfinitive() == w) {
				return el;
			}
		}
		throw std::runtime_error(std::string{ "Slowa: " } + w + "nie ma w liscie orzeczen.");
	}

	std::string getTranslation(const std::string& word, WordInf inf) const {
		if (hasTranslation(word) == false) {
			throw std::runtime_error(std::string{ "Slowa: " } + word + " nie ma w slowniku orzeczen.");
		}
		if (inf.getPerson() == 3 && inf.getForm() == 1) {
			return getVerbToTranslate(word).getSecond();
		}
		else
			return getVerbToTranslate(word).getFirst();
	}
};
