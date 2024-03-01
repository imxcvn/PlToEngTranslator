#pragma once

class Dictionary {
private:
	List<Word> list;
	std::map<std::string, WordInf> map;
public:
	void addTranslation(const std::string& w, const std::string& v) {
		list.addElement({ w, v });
	}
	bool hasTranslation(const std::string& w) const {
		for (auto& el : list) {
			if (el.getWord() == w) {
				return true;
			}

		}
		return false;
	}

	std::string getTranslation(const std::string& w) const {
		if (hasTranslation(w) == false) {
			throw std::runtime_error(std::string{ "Slowa: " } + w + " nie ma w zadnym slowniku.");
		}
		for (auto& el : list) {
			if (el.getWord() == w) {
				return el.getTranslation();
			}
		}
		return {}; //zeby nie bylo ostrzezenia
	}

	void addInfo(const std::string& word, const WordInf& info) {
		map[word] = info;
	}

	bool hasInfo(const std::string& word) const {
		return map.count(word);
	}

	const WordInf& getInfo(const std::string& word) const {
		if (hasInfo(word) == false) {
			throw std::runtime_error(std::string{ "Slowo: " } + word + " nie ma dodatkowych informacji.");
		}
		return map.at(word);
	}

	void print() {
		for (auto& el : list) {
			std::cout << el.getWord() << " " << el.getTranslation();
			if (map.count(el.getWord())) {
				const WordInf& inf = map.at(el.getWord());
				std::cout << " " << inf.getPerson() << " " << inf.getForm();
			}
			std::cout << std::endl;
		}
	}
};
