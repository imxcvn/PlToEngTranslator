#pragma once

class Verb {
private:
	std::string infinitive;
	List<std::string> allForms;
	std::string first_translation;
	std::string second_translation;
public:
	Verb() noexcept {

	}
	Verb(const std::string& inf, const std::string& first, const std::string& second) {
		infinitive = inf;
		first_translation = first;
		second_translation = second;
	}
	Verb(const Verb& other)
		: infinitive{ other.infinitive }, first_translation{ other.first_translation }, second_translation{ other.second_translation }, allForms{ other.allForms } {
	}
	bool hasWord(const std::string& w) const {
		for (auto& el : allForms) {
			if (el == w) {
				return true;
			}
		}
		return false;
	}
	bool isEmpty() const {
		if (infinitive == "" || first_translation == "" || second_translation == "") {
			return true;
		}
		return false;
	}
	void addForm(const std::string& form) {
		allForms.addElement(form);
	}
	const std::string& getFirst() const {
		return first_translation;
	}
	void setFirst(const std::string& first) {
		first_translation = first;
	}
	const std::string& getSecond() const {
		return second_translation;
	}
	void setSecond(const std::string& second) {
		second_translation = second;
	}
	const std::string& getInfinitive() const {
		return infinitive;
	}
	void setInfinitive(const std::string& inf) {
		infinitive = inf;
	}
};
