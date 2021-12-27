#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
class Grade {
	std::string id_grade_;
	std::string id_student_;
	std::string id_subject_;
	std::string grade_;
	std::vector<std::string> other_field_;
	friend void vec_grade_to_file(std::vector<Grade> vec);
	
public:
	Grade() = default;

	Grade(std::string id_grade, std::string id_student, std::string id_subject, std::string grade) :
		id_grade_(id_grade), id_student_(id_student), id_subject_(id_subject), grade_(grade) {}


	friend std::vector<Grade> from_file_grade();
	friend void add_new_field_grade();
	friend void add_grade(std::vector <Grade>& vec_grade);
	friend void remove_from_file();
	friend void change_grade();
	
	friend void add_to_file();
	friend void update_all();
	friend void average_grade();
	friend void delete_grade();
};


void vec_grade_to_file(std::vector<Grade> vec) {
	std::ofstream fout;
	fout.open("Grades.csv");
	for (size_t i = 0; i < vec.size(); i++) {
		fout << vec[i].id_grade_ << ";" << vec[i].id_student_ << ";" << vec[i].id_subject_ << ";" << vec[i].grade_ << ";";
		for (size_t j = 0; j < vec[i].other_field_.size(); j++) {
			fout << vec[i].other_field_[j] + ";";
		}
		fout << std::endl;
	}
	fout.close();

}


std::vector<Grade> from_file_grade() {
	std::ifstream fin("Grades.csv");

	if (!fin.is_open()) {
		fin.close();
		std::ofstream fout("Grades.csv");
		fout << "id_grade;id_student;id_subject;grade;" << std::endl;
		fout.close();
		fin.open("Grades.csv");
	}
	std::vector<Grade> vec;
	std::string str;

	while (!fin.eof()) {
		std::getline(fin, str);
		if (str.length() == 0) {
			break;
		}
		Grade g;

		g.id_grade_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		g.id_student_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		g.id_subject_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		g.grade_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		for (; str.find(';') != std::string::npos; ) {
			g.other_field_.push_back(str.substr(0, str.find(';')));
			str.erase(0, str.find(';') + 1);
		}
		vec.push_back(g);
	}
	fin.close();
	return vec;

}

void add_new_field_grade() {

	std::vector<Grade> vec_grade = from_file_grade();
	std::string new_field;
	std::cout << "Enter new_field" << std::endl;
	std::cin >> new_field;
	vec_grade[0].other_field_.push_back(new_field);

	for (size_t i = 1; i < vec_grade.size(); i++) {
		vec_grade[i].other_field_.push_back(";");
	}


	vec_grade_to_file(vec_grade);
}

void change_grade() {
	std::string id;
	std::string param;
	std::string new_param;

	std::cout << "Enter id" << std::endl;
	std::cin >> id;
	std::cout << "Enter name of parametr" << std::endl;
	std::cin >> param;

	std::cout << "Enter new parametr" << std::endl;
	std::cin >> new_param;

	std::vector<Grade> vec_grade = from_file_grade();

	for (size_t i = 0; i < vec_grade.size(); i++) {
		if (id == vec_grade[i].id_grade_) {
			if (param == vec_grade[0].id_student_) {
				vec_grade[i].id_student_ = new_param;
			}
			if (param == vec_grade[0].id_subject_) {
				vec_grade[i].id_subject_ = new_param;
			}
			if (param == vec_grade[0].grade_) {
				vec_grade[i].grade_ = new_param;
			}

			for (size_t j = 0; j < vec_grade[0].other_field_.size(); j++) {
				if (vec_grade[0].other_field_[j] == param) {
					vec_grade[i].other_field_[j] = new_param;
				}
			}
		}
	}
	vec_grade_to_file(vec_grade);

}

void add_grade(std::vector <Grade>& vec_grade) {
	size_t count;
	std::cout << "Enter count of grades " << std::endl;
	std::cin >> count;
	for (size_t i = 0; i < count; i++) {
		Grade g;
		if (vec_grade.size() == 1) {
			g.id_grade_ = "1";
		}
		else {
			g.id_grade_ = std::to_string(stoi(vec_grade[vec_grade.size() - 1].id_grade_) + 1);
		}

		std::cout << "\nEnter student id" << std::endl;
		std::cin >> g.id_student_;


		std::cout << "\nEnter subject id" << std::endl;
		std::cin >> g.id_subject_;

		std::cout << "\nEnter grade" << std::endl;
		std::cin >> g.grade_;
		while (g.grade_[0] < '0' || g.grade_[0]>'5') {
			std::cout << "\n\x1B[31mINCORRECT INPUT\033[0m try again" << std::endl;
			std::cin >> g.grade_;
		}


		for (size_t j = 0; j < vec_grade[0].other_field_.size(); j++) {
			std::cout << "\nEnter " << vec_grade[0].other_field_[j] << std::endl;
			std::string curr;
			std::cin >> curr;
			g.other_field_.push_back(curr);
		}

		vec_grade.push_back(g);
	}
}

void delete_grade() {
	std::string id;
	std::cout << "Enter id" << std::endl;
	std::cin >> id;
	std::vector<Grade> vec_grade = from_file_grade();

	for (size_t i = 0; i < vec_grade.size(); i++) {
		if (vec_grade[i].id_grade_ == id) {
			vec_grade.erase(vec_grade.begin() + i);
		}
	}
	vec_grade_to_file(vec_grade);

}
 