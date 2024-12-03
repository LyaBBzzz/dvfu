#include <iostream> // считать время без учета построения таблицы, добавить кол-во вхождений, не разбивать фио и адрес
#include <vector>
#include <chrono> 
#include <fstream> 
#include <string> 
#include <iomanip> 
#include <codecvt>
#include <unordered_map>
using namespace std;

struct number {
    int kod = 0; // код региона
    int num = 0; // номер телефона
};

struct key {
    int s = 0; // номер строки

    number num;

    string f;

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

vector<key> inputF(vector<key> vector1, int n) {

    ifstream in;
    string str, kode, FIO, name, buf; //buf стринговая буфферная переменная
    int k = 0;
    key kkk;
    in.open("input.txt");
    if (in.is_open()) {
        while (!in.eof() and (k < n)) {
            key vector;
            vector.s = k;
            in >> kode;
            vector.num = strToNumber(kode);
            in >> buf;
            vector.f = buf;
            in >> buf;
            vector.f.append(" ").append(buf);
            in >> buf;
            vector.f.append(" ").append(buf);
            in >> buf;
            vector.adr = buf;
            in >> buf;
            vector.adr.append(" ").append(buf);
            in >> buf;
            vector.adr.append(" ").append(buf);
            k++;
            vector1.push_back(vector);
        }
    }
    in.close();
    return vector1;
}

void outFile(vector<key> vector, string nameFile, std::chrono::duration<long long, nano> t) {
    ofstream out;
    out.open(nameFile, ios_base::app);

    for (int i = 0; i < vector.size(); i++) {
        out << vector.at(i).s << ") " << vector.at(i).num.kod << vector.at(i).num.num << " " << vector.at(i).f << " " << vector.at(i).adr << endl;
    }
    out << "time: " << t.count() << "\n";
    out.close();
}

bool matching_lines(string pattern, string txt, int index) //совпадения
{
    size_t size_txt = txt.size();
    size_t size_pattern = pattern.size();

    for (int i = index; i < index + size_pattern; i++)
    {
        if (pattern[i - index] != txt[i]) return false;
    }
    return true;
}

bool RabinSearch(string str, string pattern, int coincidences) { //РК

    int count = 0;
    int hesh1 = 0; int hesh2 = 0;
    int length_pat = pattern.length();
    size_t size_str = str.size();
    size_t size_pattern = pattern.size();

    for (int i = 0; i < size_pattern; i++)
    {
        hesh1 += pattern[i];
        hesh2 += str[i];
    }

    for (int i = 0; i < size_str - size_pattern; i++) // счётчик кол-ва вхождений для рк
    {
        if (hesh1 == hesh2)
            if (matching_lines(pattern, str, i))
                count++;

        hesh2 -= abs(str[i]);
        hesh2 += abs(str[i + length_pat]);
    }

    if (count == coincidences) 
        return true;
    return false;
}

vector<key> RBSearch(vector<key> invector, int n, string patern1, int coincidences) { 

    vector<key> outVector;
    bool marker1, marker2;
    string s;
    for (int i = 0; i < n; i++)
    {
        s = invector[i].f;
        s = s.append(invector[i].adr);
        if (RabinSearch(s, patern1, coincidences))
        {
            outVector.push_back(invector[i]);
        }
    }

    return outVector;
}

unordered_map<char, int> CreateTableBMH(string pattern, unordered_map<char, int> offsetTable) //таблица 
{
    int len_find_str = pattern.length();
    for (int i = 0; i <= 255; i++)
    {
        offsetTable[(char)i] = len_find_str;
    }
    for (int i = 0; i < len_find_str - 1; i++)
    {
        offsetTable[pattern[i]] = len_find_str - i - 1;
    }

    return offsetTable;
}

bool BMH(string src_str, string pattern, int& start_i, unordered_map<char, int> offsetTable) // Бойера-Мура-Хорспула 
{
    int len_find_str = pattern.length();
    int len_src_str = src_str.length();
    if (len_find_str > len_src_str) return false;

    int i = len_find_str - 1;
    int j = i, k = i, step = 0; // step - положение в исходной строке на которой закончилась процедура

    while (j >= 0 and i <= len_src_str - 1)
    {
        j = len_find_str - 1;
        k = i;
        while (j >= 0 and src_str.at(k) == pattern.at(j))
        {
            k--; j--; step++;
        }
        i += offsetTable[src_str.at(i)];
        step++;
    }

    if (k >= len_src_str - len_find_str) { start_i = step; return false; }
    else {
        if (step > int(len_src_str / 2))
        {
            start_i = step; return false;
        }
        else
        {
            start_i = step; return true;
        }
    }
}

pair1 bmh_self(vector<key> list, string find_str, int count) // Обертка для БМХ
{
    unordered_map<char, int> offsetTable1;
    unordered_map<char, int> offsetTable2;
    pair1 answer;
    size_t size = list.size();
    vector<key> list1;
    offsetTable1 = CreateTableBMH(find_str, offsetTable1);
    string s1;
    int j; bool flag = false;
    int c1 = 0;
    auto start2 = std::chrono::steady_clock::now();

    for (int i = 0; i < size; i++)
    {
        s1 = list[i].f;
        c1 = 0; flag = false;

        while (find_str.length() <= s1.length()) // счетчик кол-ва вхождений для бмх
        {
            flag = BMH(s1, find_str, j, offsetTable1);
            if (flag == true)
            {
                c1++;
                s1.erase(0, j + s1.length());
            }
            else
                s1.erase(0, j);
        }
        j = 0;
        s1 = list[i].adr;

        while (find_str.length() <= s1.length())
        {
            flag = BMH(s1, find_str, j, offsetTable1);
            if (flag == true)
            {
                c1++;
                s1.erase(0, j + s1.length());
            }
            else
                s1.erase(0, j);
        }

        if (c1 == count)
            list1.push_back(list[i]);
    }
    auto end2 = std::chrono::steady_clock::now();
    auto time = end2 - start2;

    answer.list = list1;
    answer.time = time;
    return answer;
}

int main() {

    setlocale(LC_ALL, ".UTF8");

    string pattern1 = "ov";
    pair1 invector1;
    vector<key> vector, ivector;
    vector = inputF(vector, 9);

    auto start1 = std::chrono::steady_clock::now();
    ivector = RBSearch(vector, 9, pattern1, 2); 
    auto end1 = std::chrono::steady_clock::now();

    invector1 = bmh_self(vector, pattern1, 2);
    outFile(invector1.list, "bmh.txt", invector1.time);
    outFile(ivector, "output.txt", end1 - start1);

    return 0;
}