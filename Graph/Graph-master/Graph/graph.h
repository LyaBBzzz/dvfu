// Заголовочный файл для класса Graph
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>

class Graph {
public:
    Graph(int vertices_count); // Конструктор
    ~Graph(); // Деструктор

    void addVertex(); // Добавить вершину
    void removeVertex(int v); // Удалить вершину
    void addEdge(int u, int v); // Добавить ребро
    void removeEdge(int u, int v); // Удалить ребро
    void printGraph(); // Печать графа
    void dfs(int start_vertex); // Обход в глубину (DFS)
    void findSСС();
    void readFromFile(const std::string& filename); // Чтение графа из файла

private:
    int vertices_count_; // Количество вершин
    std::vector<std::pair<int, int>> edges_; // Список ребер

    void dfsUtil(int v, std::vector<bool>& visited); // Вспомогательная функция для обхода в глубину
    void fillOrder(int v, std::vector<bool>& visited, std::vector<int>& stack); // Вспомогательная функция для наполнения стека в порядке окончания обработки для поиска компонент сильной связности
    void dfsUtilForSCC(int v, std::vector<bool>& visited, std::vector<int>& scc); // Вспомогательная функция поиска в глубину для поиска компонент сильной связности
    Graph getTranspose(); // Получить транспонированный граф (инвертирует направления всех рёбер)
};
