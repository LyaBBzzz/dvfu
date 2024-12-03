#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>

using namespace std;

struct Number
{
    int num1;
    int num2;

    Number() {}

    Number(int _n1, int _n2)
    {
        num1 = _n1;
        num2 = _n2;
    }

    bool operator<(const Number& n)
    {
        return num1 < n.num1 || (num1 == n.num1 && num2 < n.num2);
    }

    bool operator>(const Number& n)
    {
        return num1 > n.num1 || (num1 == n.num1 && num2 > n.num2);
    }

    bool operator==(const Number& n)
    {
        return num1 == n.num1 && num2 == n.num2;
    }

    friend ostream& operator<<(ostream& out, const Number& n);
};

ostream& operator<<(ostream& out, const Number& number)
{
    out << number.num1 << " " << number.num2;
    return out;
}

struct Node
{
    int data;
    Node* next = nullptr;
    Node(int numb) : data(numb) {} // I've become so numb I can't feel you there...
};

struct tree
{
    Node* list;
    tree* root;
    tree* left;
    tree* right;
    Number key;
    int balance;

    tree()
    {
        list = nullptr;
        root = nullptr;
        left = nullptr;
        right = nullptr;
        balance = 0;
    }

    tree(int numb_str) : root(nullptr), left(nullptr), right(nullptr), balance(0)
    {
        list = new Node(numb_str);
        list->next = list;
    }
};

int count(Node*& head)
{
    int count = 0;
    if (head == nullptr)
    {
        return count;
    }
    else
    {
        Node* temp = head;
        do
        {
            count += 1;
            temp = temp->next;
        } while (temp != head);
    }
    return count;
}

void back(Node*& head, const int address)
{

    Node* node = new Node(address); //! 321

    if (head == nullptr)
    {
        head = node;
        head->next = head;
    }
    else
    {
        Node* temp = head;

        do
        {
            temp = temp->next;
        } while (temp->next != head);

        temp->next = node;
        node->next = head;
    }
}

bool contains(Node* head, int data)
{
    if (head == nullptr)
    {
        return false;
    }

    Node* temp = head;
    do
    {
        if (temp->data == data)
        {
            return true;
        }
        temp = temp->next;
    } while (temp != head);
    return false;
}

void add(tree*& root, Number data, const int number, bool& h)
{
    if (root == nullptr)
    {
        h = true;
        root = new tree(number);
        root->key = data;
    }
    else if (data < root->key)
    {
        add(root->left, data, number, h);

        if (h)
        {
            if (root->balance == 1)
            {
                root->balance = 0;
                h = false;
            }
            else if (root->balance == 0)
            {
                root->balance = -1;
            }
            else
            {
                tree* p1 = root->left;
                if (p1->balance == -1)
                { // LL Case
                    root->left = p1->right;
                    p1->right = root;
                    root->balance = 0;
                    root = p1;
                }
                else
                { // LR Case
                    tree* p2 = p1->right;
                    p1->right = p2->left;
                    p2->left = p1;
                    root->left = p2->right;
                    p2->right = root;
                    root->balance = (p2->balance == -1) ? 1 : 0;
                    p1->balance = (p2->balance == 1) ? -1 : 0;
                    root = p2;
                }
                root->balance = 0;
                h = false;
            }
        }
    }
    else if (data > root->key)
    {
        add(root->right, data, number, h);

        if (h)
        {
            if (root->balance == -1)
            {
                root->balance = 0;
                h = false;
            }
            else if (root->balance == 0)
            {
                root->balance = 1;
            }
            else
            {
                tree* p1 = root->right;
                if (p1->balance == 1)
                { // RR Case
                    root->right = p1->left;
                    p1->left = root;
                    root->balance = 0;
                    root = p1;
                }
                else
                { // RL Case
                    tree* p2 = p1->left;
                    p1->left = p2->right;
                    p2->right = p1;
                    root->right = p2->left;
                    p2->left = root;
                    root->balance = (p2->balance == 1) ? -1 : 0;
                    p1->balance = (p2->balance == -1) ? 1 : 0;
                    root = p2;
                }
                root->balance = 0;
                h = false;
            }
        }
    }
    else
    {
        back(root->list, number);
        h = false;
    }
}

void delList(Node*& head, int data)
{
    Node* temp = head;
    do
    {
        if (temp->next == head && head->data == data)
        {
            Node* del = head;
            temp->next = del->next;
            head = temp->next;
            delete del;
            return;
        }

        else if (temp->next->data == data)
        {
            Node* del = temp->next;
            temp->next = del->next;
            delete del;
            return;
        }
        temp = temp->next;
    } while (temp != head);
}

void balanceL(tree*& root, bool& h)
{
    tree* temp1 = new tree(0); 
    tree* temp2 = new tree(0); 
    if (root->balance == -1)
    {
        root->balance = 0;
    }
    else if (root->balance == 0)
    {
        root->balance = 1;
        h = false;
    }
    else
    {
        temp1 = root->right;
        if (temp1->balance >= 0)
        { // LL
            root->right = temp1->left;
            temp1->left = root;
            if (temp1->balance == 0)
            {
                root->balance = 1;
                temp1->balance = -1;
                h = false;
            }
            else
            {
                root->balance = 0;
                temp1->balance = 0;
            }
            root = temp1;
        }
        else
        { // 2RL
            temp2 = temp1->left;
            temp1->left = temp2->right;
            temp2->right = temp1;
            root->right = temp2->left;
            temp2->left = root;
            if (temp2->balance == 1)
            {
                root->balance = -1;
            }
            else
            {
                root->balance = 0;
            }
            if (temp2->balance == -1)
            {
                temp1->balance = 1;
            }
            else
            {
                temp1->balance = 0;
            }
            root = temp2;
            temp2->balance = 0;
        }
    }
}

void balanceR(tree*& root, bool& h)
{
    tree* temp1 = new tree(0); 
    tree* temp2 = new tree(0); 
    if (root->balance == 1)
    {
        root->balance = 0;
    }
    else if (root->balance == 0)
    {
        root->balance = -1;
        h = false;
    }
    else
    {
        temp1 = root->left;
        if (temp1->balance <= 0)
        { // RR
            root->left = temp1->right;
            temp1->right = root;
            if (temp1->balance == 0)
            {
                root->balance = -1;
                temp1->balance = 1;
                h = false;
            }
            else
            {
                root->balance = 0;
                temp1->balance = 0;
            }
            root = temp1;
        }
        else
        { // 2LR
            temp2 = temp1->right;
            temp1->right = temp2->left;
            temp2->left = temp1;
            root->left = temp2->right;
            temp2->right = root;
            if (temp2->balance == -1)
            {
                root->balance = 1;
            }
            else
            {
                root->balance = 0;
            }
            if (temp2->balance == 1)
            {
                temp1->balance = -1;
            }
            else
            {
                temp1->balance = 0;
            }
            root = temp2;
            temp2->balance = 0;
        }
    }
}

void search(tree* p, Number d)
{
    if (p != NULL)
    {
        if (p->key == d)
        {
            std::cout << "Элемент: " << p << std::endl;
            return;
        }
        if (p->key > d)
            return search(p->left, d);
        if (p->key < d)
            return search(p->right, d);
    }
    else
    {
        std::cout << "Элемента нет" << std::endl;
    }
}

void delIfChildren(tree*& root, tree*& q, bool& h)
{
    if (root->left != nullptr)
    {
        delIfChildren(root->left, q, h);
        if (h == true)
        {
            balanceL(root, h);
        }
    }
    else
    {
        q->key = root->key;
        q->list = root->list;
        root = root->left;
        h = true;
    }
}

void deleteLeft(tree*& root, Number x, bool& h, int number)
{
    if (root == nullptr)
    {
        return;
    }
    else if (root->key == x)
    {
        if (contains(root->list, number))
        {
            if (count(root->list) == 1)
            {
                tree* q = root;
                if (q->right == nullptr)
                {
                    root = q->left;
                    h = true;
                }
                else if (q->left == nullptr)
                {
                    root = q->right;
                    h = true;
                }
                else
                {
                    delIfChildren(q->right, q, h); // удаление мин справа
                    if (h == true)
                    {
                        balanceR(root, h);
                    }
                }
            }
            else
            {
                delList(root->list, number);
                h = false;
            }
        }
    }
    else if (x < root->key)
    {
        deleteLeft(root->left, x, h, number);
        if (h == true)
        {
            balanceL(root, h);
        }
    }
    else if (x > root->key)
    {
        deleteLeft(root->right, x, h, number);
        if (h == true)
        {
            balanceR(root, h);
        }
    }
    else
    {
        std::cout << "номера строки нет в списке";
        h = false;
        return;
    }
}

void symmetric(tree* p, std::ofstream& file)
{
    if (p != nullptr)
    {
        symmetric(p->left, file);
        file << p->key << std::endl;
        symmetric(p->right, file);
    }
}

void readFromFileAndAdd(tree*& root, const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    int lineNumber = 1;

    Node* current;
    Node* first = new Node(1);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::istringstream iss(line);
            int token;
            tree* data = new tree();

            if (iss >> token)
            {
                data->key.num1 = token;
                iss >> token;
                data->key.num2 = token;
                bool h = false;

                if (data->list == nullptr)
                {
                    data->list = first;
                }
                else
                {
                    first = data->list;
                    current = data->list;
                    while (data->list->next != nullptr)
                    {
                        data->list = data->list->next;
                    }
                    data->list->data = lineNumber;
                }

                add(root, data->key, lineNumber, h);
            }
            lineNumber++;
        }
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }
}

void print(Node* head)
{
    Node* temp = head;
    do
    {
        if (temp->next != head)
            cout << temp->data << ", ";
        else
            cout << temp->data;
        temp = temp->next;
    } while (temp != head);
}

void printTree(tree* root, int h)
{
    if (root != nullptr)
    {
        printTree(root->right, h + 4);
        cout << endl;
        for (int i = 1; i <= h; i++)
            cout << " ";
        cout << root->key << " ";
        cout << "(";
        print(root->list);
        cout << ")";
        printTree(root->left, h + 4);
    }
}

void delTree(tree*& root)
{
    if (root == nullptr)
        return;

    delTree(root->left);
    delTree(root->right);
    delete root;
    root = nullptr;
}

int main()
{
    bool h = true;
    tree* root = nullptr;
    std::string filename = ("phoneNumbers.txt");
    std::string output = ("Obhod.txt");
    readFromFileAndAdd(root, filename);
    deleteLeft(root, Number(123, 45678912), h, 1);
    deleteLeft(root, Number(323, 45678912), h, 2);
    deleteLeft(root, Number(423, 45678912), h, 3);
    deleteLeft(root, Number(923, 35678912), h, 4);
    add(root, Number(223, 45678901), 6, h);
    //add(root, Number(123, 45678901), 55, h);
    //deleteLeft(root, Number(623, 45678912), h, 5);
    //deleteLeft(root, Number(678, 23434545), h, 8);
    //delTree(root);

    printTree(root, h);

    ofstream file(output);
    if (file.is_open())
        symmetric(root, file);
    return 0;
}