#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Pizza {
public:
    Pizza(const std::string& name, const std::string& description, int size, double base_price)
        : name(name), description(description), size(size), base_price(base_price), salt_count(0), cheese_count(0) {}

    virtual double calculatePrice() const {
        double price = base_price;

        switch (size) {
        case 25:
            price *= 1.0;
            break;
        case 30:
            price *= 1.2;
            break;
        case 35:
            price *= 1.4;
            break;
        case 40:
            price *= 1.6;
            break;
        default:
            std::cerr << "Неверный размер пиццы\n";
            return -1.0;
        }

        price += salt_count * 0.5;
        price += cheese_count * 1.0;

        return price;
    }

    virtual void printPizzaDetails() const {
        std::cout << "Название: " << name << "\nОписание: " << description
            << "\nРазмер: " << size << " см\nСоль: " << salt_count << " порций\nСыр: " << cheese_count
            << " порций\nЦена: " << calculatePrice() << " руб.\n\n";
    }

    void addSalt(int count) {
        salt_count += count;
    }

    void addCheese(int count) {
        cheese_count += count;
    }

protected:
    std::string name;
    std::string description;
    int size;
    double base_price;
    int salt_count;
    int cheese_count;
};

class MargheritaPizza : public Pizza {
public:
    MargheritaPizza(int size)
        : Pizza("Маргарита", "Классическая пицца с томатным соусом и моцареллой", size, 500.0) {}
};

class PepperoniPizza : public Pizza {
public:
    PepperoniPizza(int size)
        : Pizza("Пепперони", "Пицца с пикантным пепперони и сыром", size, 600.0) {}
};

class SuperMeatPizza : public Pizza {
public:
    SuperMeatPizza(int size)
        : Pizza("Супер Мясная", "Пицца с множеством видов мяса", size, 750.0) {}
};

class FourCheesePizza : public Pizza {
public:
    FourCheesePizza(int size)
        : Pizza("Четыре сыра", "Пицца с моцареллой, пармезаном, горгонзолой и дор-блю", size, 700.0) {}
};

class BurgerPizza : public Pizza {
public:
    BurgerPizza(int size)
        : Pizza("Бургер-пицца", "Пицца с овощами, соусом и бургерными ингредиентами", size, 680.0) {}
};

class Order {
public:
    void addPizza(const Pizza& pizza) {
        pizzas.push_back(pizza);
    }

    void printOrder() const {
        std::cout << "Состав заказа:\n";
        double total_price = 0.0;

        for (const auto& pizza : pizzas) {
            pizza.printPizzaDetails();
            total_price += pizza.calculatePrice();
        }

        std::cout << "Итоговая сумма заказа: " << total_price << " руб.\n";
    }

private:
    std::vector<Pizza> pizzas;
};

int main() {
    setlocale(LC_CTYPE, "Russian");
    Order order;

    std::cout << "Добро пожаловать в пиццерию!\n";

    char answer;
    do {
        std::cout << "Выберите вид пиццы (1 - Маргарита, 2 - Пепперони, 3 - Супер Мясная, 4 - Четыре сыра, 5 - Бургер-пицца):\n";
        int choice;
        std::cin >> choice;

        int size;
        std::cout << "Введите размер пиццы (25, 30, 35, 40): ";
        std::cin >> size;

        Pizza* selectedPizza = nullptr;

        switch (choice) {
        case 1:
            selectedPizza = new MargheritaPizza(size);
            break;
        case 2:
            selectedPizza = new PepperoniPizza(size);
            break;
        case 3:
            selectedPizza = new SuperMeatPizza(size);
            break;
        case 4:
            selectedPizza = new FourCheesePizza(size);
            break;
        case 5:
            selectedPizza = new BurgerPizza(size);
            break;
        default:
            std::cout << "Неверный выбор.\n";
            continue;
        }

        int salt, cheese;
        std::cout << "Желаете посолить пиццу? (1 - да, 0 - нет): ";
        std::cin >> salt;

        std::cout << "Желаете добавить сыра? (1 - да, 0 - нет): ";
        std::cin >> cheese;

        if (salt == 1) {
            int saltCount;
            std::cout << "Введите количество соли: ";
            std::cin >> saltCount;
            selectedPizza->addSalt(saltCount);
        }

        if (cheese == 1) {
            int cheeseCount;
            std::cout << "Введите количество сыра: ";
            std::cin >> cheeseCount;
            selectedPizza->addCheese(cheeseCount);
        }

        order.addPizza(*selectedPizza);
        delete selectedPizza;

        std::cout << "Хотите добавить еще одну пиццу? (y/n): ";
        std::cin >> answer;

    } while (answer == 'y' || answer == 'Y');

    order.printOrder();

    return 0;
}
