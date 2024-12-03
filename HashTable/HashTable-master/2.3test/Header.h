#pragma once

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>


int random(int start, int end) {
	return rand() % (end - start + 1);
}

std::string PostOrder_fio(std::vector<std::string> list_name, std::vector<std::string> list_surname, std::vector<std::string> list_fathername)
{
	std::string s = list_name[random(0, size(list_name) - 1)] + " " + list_surname[random(0, size(list_surname) - 1)] + " " + list_fathername[random(0, size(list_fathername) - 1)];
	return s;
}

std::string PostOrder_code()
{
	std::string s;
	s = "0" + std::to_string(random(1, 9)) + ".0" + std::to_string(random(1, 9)) + ".0" + std::to_string(random(1, 9));
	return s;
}

std::string PostOrder_spec(std::vector <std::string> list_name)
{
	return list_name[random(0, size(list_name) - 1)];
}

std::vector<std::string> make_list_string(std::string path)
{
	std::ifstream fin;
	fin.open(path);
	std::vector<std::string> list;
	std::string a;
	while (!fin.eof())
	{
		getline(fin, a);
		list.push_back(a);
	}
	fin.close();
	return list;
}

std::string phone_numb()
{
	std::string numb = "7";
	for (int i = 0; i < 10; i++)
	{
		numb.append(std::to_string(random(0, 9)));

	}
	return numb;
}

void generator(int n) {
	std::vector<std::string> name; name = make_list_string("generator_name.txt");
	std::vector<std::string> surname; surname = make_list_string("generator_surname.txt");
	std::vector<std::string> fathername; fathername = make_list_string("generator_fathername.txt");
	std::vector<std::string> name_str; name_str = make_list_string("name_streer.txt");
	std::basic_ofstream<char> file;

	file.open("generator.txt");
	for (int i = 0; i < n; i++)
	{
		file << std::setw(2) << random(10, 100) << std::setw(13) << phone_numb() << std::setw(30) << PostOrder_fio(name, surname, fathername) << std::setw(20) << PostOrder_spec(name_str) << std::setw(3) << random(10, 99) << "\n";
	}
	file.close();
}