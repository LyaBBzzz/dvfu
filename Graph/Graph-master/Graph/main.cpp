#include "graph.h"

int main() {
    // Создаем граф с 13 вершинами
    Graph graph(13);

    //// Добавляем ребра
    //graph.addEdge(0, 1);
    //graph.addEdge(0, 2);
    //graph.addEdge(0, 3);

    //graph.addEdge(1, 0);
    //graph.addEdge(2, 0);
    //graph.addEdge(2, 6);
    //graph.addEdge(3, 2);
    //graph.addEdge(3, 7);
    //graph.addEdge(3, 8);

    //graph.addEdge(4, 1);
    //graph.addEdge(4, 2);
    //graph.addEdge(4, 5);

    //graph.addEdge(5, 9);
    //graph.addEdge(6, 5);
    //graph.addEdge(7, 6);
    //graph.addEdge(7, 8);
    //graph.addEdge(8, 7);

    //graph.addEdge(9, 6);
    //graph.addEdge(10, 7);
    //graph.addEdge(10, 11);
    //graph.addEdge(10, 12);
    //graph.addEdge(11, 8);
    //graph.addEdge(11, 10);

    //graph.addEdge(12, 11);

    ////Поиск компонент сильной связности для графа
    //graph.findSСС();

    // Печатаем граф
    //std::cout << "Graph:" << std::endl;
    //graph.printGraph();

    //// Выполняем обход в глубину (DFS) начиная с вершины 0
    //std::cout << "\ndepth-first traversal (DFS) starting from vertex 2:" << std::endl;
    //graph.dfs(2);

    // Чтение графа из файла
    std::cout << "\nreading a graph from a file graph.txt:" << std::endl;
    graph.readFromFile("input.txt");
    graph.printGraph();

    //// Добавляем ребро между 4 и 5 вершинами (5-ой вершины не сущетсвует, поэтому ошибка будет)
    //graph.addEdge(4, 5);

    //// Добавляем ребро между 4 и 5 вершинами (теперь гуд)
    //graph.addVertex();
    //graph.addEdge(4, 5);
    //graph.printGraph();

    //// Удаление несуществующей вершины
    //graph.removeVertex(8);

    //// Удаление существующей вершины
    //graph.removeVertex(2);
    //graph.printGraph();

    // Удаление ребра
    std::cout << std::endl;
    graph.removeEdge(4, 2);
    graph.printGraph();

    return 0;
}
