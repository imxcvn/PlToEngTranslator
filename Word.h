#pragma once

class Word {
private:
	std::string word;
	std::string translation;
public:
	Word() noexcept {

	}
	Word(const std::string& word, const std::string& translation) {
		this->word = word;
		this->translation = translation;
	}
	void setWord(const std::string& word) {
		this->word = word;
	}
	const std::string& getWord() const {
		return word;
	}
	void setTranslation(const std::string& translation) {
		this->translation = translation;
	}
	const std::string& getTranslation() const {
		return translation;
	}
};
