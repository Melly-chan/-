#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
class Subject {
private:
	std::string id_subject_;
	std::string subject_;
	std::vector<std::string> other_field_;

	friend void vec_subject_to_file(std::vector<Subject> vec);

public:
	Subject() = default;
	Subject(std::string id, std::string subject) :id_subject_(id), subject_(subject) {}


	friend std::vector<Subject> from_file_subject();
	friend void add_new_field_subject();
	friend void add_subject(std::vector <Subject>& vec_subject);
	friend void remove_from_file();
	friend void change_subject();
	friend void delete_subject();

	
	friend void add_to_file();
	friend void update_all();
	friend void average_grade();

};

void vec_subject_to_file(std::vector<Subject> vec) {
	std::ofstream fout;
	fout.open("Subjects.csv");
	for (size_t i = 0; i < vec.size(); i++) {
		fout << vec[i].id_subject_ << ";" << vec[i].subject_ << ";";
		for (size_t j = 0; j < vec[i].other_field_.size(); j++) {
			fout << vec[i].other_field_[j] + ";";
		}
		fout << std::endl;
	}
	fout.close();
}

std::vector<Subject> from_file_subject() {
	std::ifstream fin("Subjects.csv");

	if (!fin.is_open()) {
		fin.close();
		std::ofstream fout("Subjects.csv");
		fout << "id;subject;" << std::endl;
		fout.close();
		fin.open("Subjects.csv");
	}
	std::string str;
	std::vector <Subject> vec;
	while (!fin.eof()) {
		std::getline(fin, str);
		if (str.length() == 0) {
			break;
		}
		Subject s;

		s.id_subject_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		s.subject_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		for (; str.find(';') != std::string::npos; ) {
			s.other_field_.push_back(str.substr(0, str.find(';')));
			str.erase(0, str.find(';') + 1);
		}

		vec.push_back(s);
	}

	fin.close();
	return vec;

}


void add_new_field_subject() {

	std::vector<Subject> vec_subject = from_file_subject();
	std::string new_field;
	std::cout << "Enter new_field" << std::endl;
	std::cin >> new_field;
	vec_subject[0].other_field_.push_back(new_field);
	for (size_t i = 1; i < vec_subject.size(); i++) {
		vec_subject[i].other_field_.push_back(";");
	}
	vec_subject_to_file(vec_subject);

}

void change_subject() {
	std::string id;
	std::string param;
	std::string new_param;

	std::cout << "Enter id" << std::endl;
	std::cin >> id;
	std::cout << "Enter name of parametr" << std::endl;
	std::cin >> param;

	std::cout << "Enter new parametr" << std::endl;
	std::cin >> new_param;

	std::vector<Subject> vec_subject = from_file_subject();

	for (size_t i = 0; i < vec_subject.size(); i++) {
		if (id == vec_subject[i].id_subject_) {
			if (param == vec_subject[0].subject_) {
				vec_subject[i].subject_ = new_param;
			}
			for (size_t j = 0; j < vec_subject[0].other_field_.size(); j++) {
				if (vec_subject[0].other_field_[j] == param) {
					vec_subject[i].other_field_[j] = new_param;
				}
			}
		}
	}
	vec_subject_to_file(vec_subject);

}

void add_subject(std::vector<Subject>& vec_subject) {
	size_t count;
	std::cout << "Enter count of subject" << std::endl;
	std::cin >> count;
	for (size_t i = 0; i < count; i++) {
		Subject S;
		if (vec_subject.size() == 1) {
			S.id_subject_ = "1";
		}
		else {
			S.id_subject_ = std::to_string(stoi(vec_subject[vec_subject.size() - 1].id_subject_) + 1);
		}

		std::cout << "\nEnter Subject" << std::endl;
		std::cin >> S.subject_;

		for (size_t j = 0; j < vec_subject[0].other_field_.size(); j++) {
			std::cout << "\nEnter " << vec_subject[0].other_field_[j] << std::endl;
			std::string curr;
			std::cin >> curr;
			S.other_field_.push_back(curr);
		}
		vec_subject.push_back(S);
	}
}

void delete_subject() {
	std::string id;
	std::cout << "Enter id" << std::endl;
	std::cin >> id;
	std::vector<Subject> vec_subject = from_file_subject();

	for (size_t i = 0; i < vec_subject.size(); i++) {
		if (vec_subject[i].id_subject_ == id) {
			vec_subject.erase(vec_subject.begin() + i);
		}
	}
	vec_subject_to_file(vec_subject);

}
