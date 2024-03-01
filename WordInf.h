#pragma once

class WordInf {
private:
	int person;
	int form;
public:
	WordInf() noexcept {
		person = 0;
		form = 0;
	}
	WordInf(int person, int form) noexcept {
		this->person = person;
		this->form = form;
	}
	int getPerson() const {
		return person;
	}
	int getForm() const {
		return form;
	}
};
