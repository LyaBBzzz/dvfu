#include <iostream>
#include <vector>
#include <chrono> 
#include <fstream> 
#include <string> 
#include <iomanip> 
#include <codecvt>
#include <unordered_map>
#include "Header.h";
using namespace std;


struct number {
    int kod = 0; // код региона
    int num = 0; // номер телефона
};

struct key {
    int s; // номер за€вки

    number num;

    string fio;

    string adr;
};

struct pair1
{
    vector<key> list;
    std::chrono::duration<long long, std::nano> time;

    pair1() {};
};

struct pair2
{
    vector<key> list;

};

number strToNumber(string str) { //перевод номера телефона в структуру
    number num;
    string buf;

    for (int i = 0; i < 4; i++) {
        buf = buf + str[i];
    }
    num.kod = stoi(buf);
    buf = "";
    for (int i = 4; i < str.size(); i++) {
        buf = buf + str[i];
    }
    num.num = stoi(buf);
    buf = "";
    return num;
}

vector<key> inputF(vector<key> vector1, int n, std::string path) {
    ifstream in;
    string str, kode, FIO, name, buf; //buf стрингова€ буфферна€ переменна€
    int k = 0;

    in.open(path);
    if (in.is_open()) {
        while (!in.eof() and (k < n)) {
            key vector;
            in >> buf;
            vector.s = std::stoi(buf);


            in >> buf;
            vector.num = strToNumber(buf);


            in >> buf;
            vector.fio = buf;
            in >> buf;
            vector.fio.append(" ").append(buf);
            in >> buf;
            vector.fio.append(" ").append(buf);


            in >> buf;
            vector.adr = buf;
            in >> buf;
            vector.adr.append(" ").append(buf);
            k++;
            vector1.push_back(vector);

        }
    }
    in.close();
    return vector1;
}

vector<key> algo_quick(std::vector<key> list) //быстрый сорт
{
    string b = "";
    int n = size(list);
    const int m = 12;
    int low[m];
    int high[m];
    int i, j, s, L, R;

    s = 0;
    key w;
    key x;

    low[0] = 0;
    high[0] = n - 1;

    do
    {
        L = low[s];
        R = high[s];
        s--;
        do
        {
            i = L;
            j = R;
            x = list[int((L + R) / 2)];

            do
            {
                while (list[i].s < x.s) i++;  //list[i]< x
                while (x.s < list[j].s) j--;    //x < list[j]
                if (i <= j)
                {
                    w = list[i];
                    list[i] = list[j];
                    list[j] = w;
                    i++;
                    j--;
                }
            } while (!(i > j));

            if (i < R)
            {
                s++;
                low[s] = i;
                high[s] = R;

            }
            R = j;
        } while (!(L >= R));
    } while (!(s < 0));
    return list;
}

void PostOrder(std::vector<key> list, std::basic_ofstream<char>& file, std::string path)
{
    file.open(path);
    int i = 0;
    int n = size(list);
    for (int i = 0; i < n; i++)
    {
        std::string num = std::to_string(list[i].num.kod);
        num.append(std::to_string(list[i].num.num));
        file << std::setw(3) << list[i].s << std::setw(13) << num << std::setw(30) << list[i].fio << std::setw(20) << list[i].adr << "\n";
    }
    //file << std::setw(3) <<random(100,200) << " | " << std::setw(30) << PostOrder_fio(name, surname, fathername) << "|" << std::setw(8) << PostOrder_code() << "|" << std::setw(30)<<PostOrder_spec(name_spec) << "\n";
    file.close();
}

void QuickSort(vector<key> list, std::basic_ofstream<char>& file, int n)
{
    vector<key> a;
    a = algo_quick(list);
    PostOrder(a, file, "quicksort.txt");

}

bool linear_search(std::vector<key> list, size_t size, int value) //лин с барьером
{
    key tail;
    tail.s = value;
    list.push_back(tail);
    basic_ofstream<char> file;
    file.open("linear search.txt");
    int i;
    for (i = 0; list[i].s != value; i++)
    {
    }

    if (i != size)
    {
        std::string num = std::to_string(list[i].num.kod);
        num.append(std::to_string(list[i].num.num));
        file << std::setw(3) << list[i].s << std::setw(13) << num << std::setw(30) << list[i].fio << std::setw(20) << list[i].adr << "\n";
        file << i + 1; //кол-во шагов

        file.close();
        list.pop_back();
        return true;
    }
    file << i;
    file.close();
    list.pop_back();
    return false;
}

bool Interpol(std::vector<key> list, size_t size, int value) //интерпол€ционный
{
    int mid;
    int l = 0;
    int r = size - 1;
    int count = 0; // счетчик шагов
    basic_ofstream<char> file;
    file.open("interpol.txt");

    while (list[l].s < value and list[r].s > value)
    {
        count++;
        if (list[l].s == list[r].s)
        {
            file << count;
            file.close();
            return false;
        }

        mid = l + (value - list[l].s) * (r - l) / (list[r].s - list[l].s);

        if (list[mid].s < value)
        {
            l = mid + 1;
        }
        else if (list[mid].s > value)
        {
            r = mid - 1;
        }
        else
        {
            std::string num = std::to_string(list[mid].num.kod);
            num.append(std::to_string(list[mid].num.num));
            file << std::setw(3) << list[mid].s << std::setw(13) << num << std::setw(30) << list[mid].fio << std::setw(20) << list[mid].adr << "\n";
            file << count;
            return true;

        }
    }

    if (list[l].s == value)
    {
        std::string num = std::to_string(list[l].num.kod);
        num.append(std::to_string(list[l].num.num));
        file << std::setw(3) << list[l].s << std::setw(13) << num << std::setw(30) << list[l].fio << std::setw(20) << list[l].adr << "\n";
        file << count + 1;
        return true;
    }

    if (list[r].s == value)
    {
        std::string num = std::to_string(list[r].num.kod);
        num.append(std::to_string(list[r].num.num));
        file << std::setw(3) << list[r].s << std::setw(13) << num << std::setw(30) << list[r].fio << std::setw(20) << list[r].adr << "\n";
        file << count + 1;
        return true;
    }

    file << count;
    file.close();
    return false;
}

int main()
{
     generator(15);
     vector<key> list = inputF(list, 15,"generator.txt");
     std::basic_ofstream<char> output;
     QuickSort(list, output, 15);

    vector<key> list2 = inputF(list2, 15, "quicksort.txt");
    vector<key> list1 = inputF(list1, 15, "generator.txt");
    Interpol(list2, list2.size(), 9); // сорт 
    linear_search(list1, list1.size(), 9); // не сорт
}