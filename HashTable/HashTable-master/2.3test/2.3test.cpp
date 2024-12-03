#include <iostream>
#include "Header.h"
#include <fstream> 
//Динамическая хэш таблица
//Статус ячейки 0 1 2
//Хэш функция мультипликативная
//Линейный поиск, место вставки k = 1

struct number {
    int kod = 0; // код региона
    int num = 0; // номер телефона

    bool operator ==(number b)
    {
        if (this->kod == b.kod and this->num == b.num) return true;
        return false;
    }
};

number strToNumber(std::string str) { //перевод номера телефона в структуру
    number num;
    std::string buf;

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

struct key {
    int s; // номер заявки

    number num;

    std::string fio;

    std::string adr;

    int status;

    int number_ord;

    key(number n, std::string f, std::string adr, int status, int number_ord) : num(n), fio(f), adr(adr), status(status), number_ord(number_ord) {}
    key() : status(0) {}


    bool operator ==(key b)
    {
        if (this->adr == b.adr and this->fio == b.fio and this->number_ord == b.number_ord and this->num == b.num) return true;
        return false;
    }
};

class hash_table
{
private:
    int initial_size;
    float A;
public:
    int size;
    int quantity_el;
    std::vector<key> list;

    hash_table() {}

    hash_table(int sizee, float coef)
    {
        list.resize(sizee);
        initial_size = sizee;
        size = sizee;
        A = coef;
    }

    int hash_func(key el)
    {
        if (A > 0 and A < 1)
        {
            float summ = el.number_ord;
            std::string k = el.fio;
            for (char i : k)
                summ += i;

            return int(size * ((summ * A) - int(summ * A)));
        }
        else
            return -1;
    }

    int get_index(key el, int count)
    {

        return (hash_func(el) + count * 1) % size;
    }

    void increase() //*2  увеличивает размер в два раза и вставляет элементы в новую таблицу
    {
        hash_table new_table(size * 2, A);

        for (int i = 0; i < size; i++)
        {
            if (list[i].status != 0)
            {
                //list[i].status = false;
                new_table.input(list[i]);
            }
        }
        size = size * 2;
        list = new_table.list;
        new_table.reduction(75);
    }

    void decrease() // :3/4
    {
        hash_table new_table(3 * int(size / 4), A);

        for (int i = 0; i < size; i++)
        {
            if (list[i].status != 0 and list[i].status != 2)
            {
                list[i].status = 0;
                new_table.input(list[i]);
            }
        }
        size = 3 * int(size / 4);
        //new_table.reduction(75);

        list = new_table.list;

    }

    void reduction(int coefficient) // проверяет массив на полноту, если недостаточно полный то сокращает размер в два раза, в противном случае увеличивает
    {
        float r = (size * coefficient / 100);
        if (quantity_el < r and size > initial_size) //11 !!
        {
            decrease();
        }
    }

    bool input(key el)
    {
        if (size == 0) { list.resize(1); size = 1; }


        int index = get_index(el, 0);

        //if (index == -1) return false;

        if (list[index].status == 0)  //Лучший случай
        {
            list[index] = el;
            list[index].status = 1;
            quantity_el += 1;
            return true;
        }
        else
        {
            return open_addressing(el, A);//Худший
        }
    }

    bool open_addressing(key el, float A)
    {
        int count = 0;
        int index = get_index(el, count);
        while (list[index].status != 1)
        {
            if (list[index].number_ord == el.number_ord and list[index].status == 1 and list[index].fio == el.fio) return false;
            count++;
            index = get_index(el, count);

            if (count >= size)
            {
                increase();
                input(el);
                return true;
            }
        }

        count = 0; index = get_index(el, count);
        while (list[index].status != 2 and list[index].status != 0) // поиски первой свободной ячейки
        {
            if (list[index].number_ord == el.number_ord and list[index].status == 1 and list[index].fio == el.fio) return false;
            count++;
            index = get_index(el, count);

            if (count > size)//если ячейки со статусом 2 нет, то расширяем
            {
                increase();
                input(el);
                return true;
            }

        }
        list[index] = el;
        list[index].status = 1;
        quantity_el++;
        return true;
    }

    void Fill(std::string path, int n) {
        std::ifstream in;
        std::string str, kode, FIO, name, buf; //buf стринговая буфферная переменная
        int k = 0;

        in.open(path);
        if (in.is_open()) {
            while (!in.eof() and (k < n)) {
                key vector;
                in >> buf;
                vector.number_ord = std::stoi(buf);


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


                vector.status = 0;
                k++;


                input(vector);

            }
        }
        in.close();
    }

    void print()
    {
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (list[i].status == 1 || list[i].status == 2)
            {
                count++;
                std::cout << std::setw(2) << i << std::setw(3) << list[i].number_ord << std::setw(35) << list[i].fio << std::setw(14) << list[i].num.kod << list[i].num.num << std::setw(30) << list[i].adr << std::setw(5) << get_index(list[i], 0) << std::setw(5) << get_index(list[i], 1) << std::setw(14) << list[i].status << "\n";
            }
        }
        std::cout << quantity_el << "               " << size << "\n";
    }


    int find(key el)
    {
        int count = 0;
        int index = get_index(el, count);

        if (el == list[index] and list[index].status == 1) //ЛУЧШИЙ СЛУЧАЙ
            return count + 1;
        else {
            count++;
            while (!(el == list[index]) or list[index].status == 0 or list[index].status == 2) //ХУДШИЙ
            {
                index = get_index(el, count);
                count++;

                if (count > size) return -1;
            }
        }

        return count + 1;
    }

    bool remove(key el)
    {
        int count = 0;
        int index = get_index(el, count);

        if (list[index] == el and list[index].status == 1) //Лучший случчай
        {
            list[index].status = 2;
        }
        else {//худший
            while (!(list[index] == el) or (list[index].status == 0 or list[index].status == 2))
            {
                count++;
                index = get_index(el, count);

                if (count > size)
                    return false;
            }

            list[index].status = 2;
        }


        int minecraft = get_index(el, count + 1);
        if (list[minecraft].status == 1)
        {
            key element = list[get_index(el, count)];

            while (list[get_index(el, count + 1)].status == 1)
            {
                element = list[get_index(el, count + 1)];
                list[get_index(el, count)] = element;
                count++;
            }

            list[get_index(el, count)].status = 2;
            quantity_el--;
            reduction(75);
            return true;
        }
        list[get_index(el, count)].status = 2;
        quantity_el--;
        reduction(75);
        return true;
    }
};

int main()
{
    //generator(100);
    hash_table list(13, 0.618); // размер 13 
    //list.Fill("generator.txt", 8);
    list.Fill("test1.txt", 2);
    list.print();

    //list.remove(list.list[4]);
    //list.print(); 
        
    // Добавляем элементы вручную
    key element1(number{ 7180, 7225910 }, "Stas Dolgov Popkovich", "Popova 3", 1, 21);
    list.input(element1);
    list.print();

    int index;
    while (list.quantity_el != 0)
    {
        std::cin >> index;
        list.remove(list.list[index]);
        list.print();
        //std::cin >> index; //поиск
        //std::cout << list.find(list.list[index]); //колво шагов

    }

    return 0;
}