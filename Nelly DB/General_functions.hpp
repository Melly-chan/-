#pragma once
#include <iostream>
#include "Student.hpp"
#include "Subject.hpp"
#include "Grade.hpp"

void menu();
void average_grade();
void update_all();
void add_to_file();
void remove_from_file();
void add_new_field();
void change_in_file();
void delete_in_file();




void average_grade() {
	std::vector<Student> vec_student = from_file_student();
	std::vector<Subject> vec_subject = from_file_subject();
	std::vector<Grade> vec_grade = from_file_grade();

	for (size_t i = 1; i < vec_student.size(); i++){
		double av_gr = 0;
		size_t count = 0;
		for (size_t k = 1; k < vec_grade.size(); k++){
			if (vec_student[i].id_student_ == vec_grade[k].id_student_) {
				++count;
				av_gr += stof(vec_grade[k].grade_);
			}
		}
		std::cout << "student id = " << vec_student[i].id_student_ << " avarege grade = " << av_gr / count << std::endl;
	}

	menu();

}

void update_all() {

	std::vector<Student> vec_student = from_file_student();
	std::vector<Subject> vec_subject = from_file_subject();
	std::vector<Grade> vec_grade = from_file_grade();

	//делаем общий файл All.csv
	std::ofstream fout("All.csv");
	fout << "surname;name;patronymic;";
	for (size_t i = 1; i < vec_subject.size(); i++) {
		fout << vec_subject[i].subject_ << ";";
	}
	fout << std::endl;
	for (size_t i = 1; i < vec_student.size(); i++) {
		fout << vec_student[i].surname_ << ";" << vec_student[i].name_ << ";" << vec_student[i].patronymic_ << ";";
		//ищем оценки по предметам
		for (size_t l = 0; l < vec_subject.size(); l++) {
			std::string curr = "";
			for (size_t j = 1; j < vec_grade.size(); j++) {
				if (vec_grade[j].id_student_ == vec_student[i].id_student_ && vec_grade[j].id_subject_ == vec_subject[l].id_subject_) {
					curr += vec_grade[j].grade_ + ',';
				}
			}
			if (curr.length()) {
				fout << curr << ";";
			}
			
		}
		fout << std::endl;
	}
	fout.close();

}

//добавить в файл  
void add_to_file() {
	system("CLS");

	std::cout << "Enter number:\n	1 - Add student\n	2 - Add subject\n	3 - Add grade" << std::endl;
	int number;
	std::cin >> number;

	std::vector<Student> vec_student = from_file_student();
	std::vector<Subject> vec_subject = from_file_subject();
	std::vector<Grade> vec_grade = from_file_grade();



	if (number == 1) {
		add_student(vec_student);
	}

	if (number == 2) {
		add_subject(vec_subject);
	}

	if (number == 3) {
		add_grade(vec_grade);
	}

	vec_student_to_file(vec_student);
	vec_subject_to_file(vec_subject);
	vec_grade_to_file(vec_grade);

	update_all();
		menu();

}

//удал€ем столбец
void remove_from_file() {
	system("CLS");

	std::cout << "Enter column (only additionals columns can be deleted)" << std::endl;
	std::string column;
	std::cin >> column;

	std::vector<Student> vec_student = from_file_student();
	std::vector<Subject> vec_subject = from_file_subject();
	std::vector<Grade> vec_grade = from_file_grade();

	//поиск совпадений в каждой бд
	for (size_t i = 0; i < vec_student[0].other_field_.size(); i++) {
		if (column == vec_student[0].other_field_[i]) {
			for (size_t j = 0; j < vec_student.size(); j++) {
				vec_student[j].other_field_.erase(vec_student[j].other_field_.begin() + i);
			}
		}
	}

	for (size_t i = 0; i < vec_subject[0].other_field_.size(); i++) {
		if (column == vec_subject[0].other_field_[i]) {
			for (size_t j = 0; j < vec_subject.size(); j++) {
				vec_subject[j].other_field_.erase(vec_subject[j].other_field_.begin() + i);
			}
		}
	}

	for (size_t i = 0; i < vec_grade[0].other_field_.size(); i++) {
		if (column == vec_grade[0].other_field_[i]) {
			for (size_t j = 0; j < vec_grade.size(); j++) {
				vec_grade[j].other_field_.erase(vec_grade[j].other_field_.begin() + i);
			}
		}
	}

	vec_student_to_file(vec_student);
	vec_subject_to_file(vec_subject);
	vec_grade_to_file(vec_grade);

	update_all();
	menu();

}


void add_new_field() {
	system("CLS");
	           //крокоз€бра чтобы помен€ть цвет текста
	std::cout << "\x1B[32mEnter number:\033[0m\n	1 - Add new field in student\n	2 - Add new field in subject\n	3 - Add new field in grade" << std::endl;
	int number;
	std::cin >> number;

	if (number == 1) {
		 add_new_field_student();
	}

	if (number == 2) {
		 add_new_field_subject();
	}

	if (number == 3) {
		 add_new_field_grade();
	}
	update_all();
	menu();

}

void change_in_file() {
	//очистить консоль
	system("CLS");

	std::cout << "\x1B[32mEnter number:\033[0m\n	1 - Change in student file \n	2 - Change in subject file\n	3 - Change in grade file\n	4 - EXIT" << std::endl;
	int number;
	std::cin >> number;

	if (number == 1) {
		 change_student();
	}

	if (number == 2) {
		 change_subject();
	}

	if (number == 3) {
		 change_grade();
	}

	if (number == 4) {
		menu();
	}
	update_all();

	menu();

}

//удалить из файла объект, не €чейку, а объект(всю строку)
void delete_in_file() {
	system("CLS");

	std::cout << "\x1B[32mEnter number:\033[0m\n	1 - Delete in student file \n	2 - Delete in subject file\n	3 - Delete in grade file" << std::endl;
	int number;
	std::cin >> number;

	if (number == 1) {
		delete_student();
	}

	if (number == 2) {
		delete_subject();
	}

	if (number == 3) {
		delete_grade();
	}
	update_all();
	menu();
}

//главное меню
void menu() {
	system("CLS");
	std::cout << "\x1B[32mEnter number:\033[0m\n	1 - Edit file\n	2 - Write average grade \n	3 - Open DB" << std::endl;
	int number;
	std::cin >> number;



	if (number == 1) {
		system("CLS");
		std::cout << "\x1B[32mEnter number:\033[0m\n	1 - Add to file\n	2 - Change in file \n	3 - Add column\n	4 - Remove column\n	5 - delete row in file\n 	6 - EXIT to menu" << std::endl;
		std::cin >> number;
		if (number == 1) {
			add_to_file();
		}

		if (number == 2) {
			change_in_file();
		}

		if (number == 3) {
			add_new_field();
		}

		if (number == 4) {
			remove_from_file();
		}

		if (number == 5) {
			delete_in_file();
		}

		if (number == 6) {
			menu();
		}
	}

	if (number == 2) {
		average_grade();
	}

	if (number == 3) {
		system("CLS");

		std::cout << "\x1B[32mEnter number:\033[0m\n	1 - Open Students DB\n	2 - Open Subject DB\n	3 - Open Grades DB\n	4 - Open All DB\n	5 - EXIT" << std::endl;

		std::cin >> number;
		if (number == 1) {
			//создаем копию тк нельз€ мен€ть что-то в насто€щей бд
			std::ifstream fin("Students.csv");
			if (fin)
			{
				std::ofstream fout("copy.csv");
				fout << fin.rdbuf();
				fout.close();
				fin.close();
			}
		}

		if (number == 2) {
			std::ifstream fin("Subjects.csv");
			if (fin)
			{
				std::ofstream fout("copy.csv");
				fout << fin.rdbuf();
				fout.close();
				fin.close();
			}
		}

		if (number == 3) {
			std::ifstream fin("Grades.csv");
			if (fin)
			{
				std::ofstream fout("copy.csv");
				fout << fin.rdbuf();
				fout.close();
				fin.close();
			}
		}
		if (number == 4) {
			std::ifstream fin("All.csv");
			if (fin)
			{
				std::ofstream fout("copy.csv");
				fout << fin.rdbuf();
				fout.close();
				fin.close();
			}
		}

		if (number == 5) {
			menu();
		}

		system("copy.csv");
		menu();
	}

	std::cout << "\n\x1B[32mEXIT?\033[0m\n	Yes = 1\n	No = 2" << std::endl;
	std::cin >> number;
	if (number == 2) {
		menu();
	}

}
