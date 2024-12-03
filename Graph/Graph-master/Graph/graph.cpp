#include "graph.h"

Graph::Graph(int vertices_count) : vertices_count_(vertices_count < 5 ? 5 : vertices_count) {}

Graph::~Graph() {}

// Добавление вершины
void Graph::addVertex() {
    vertices_count_++;
}

// Удаление вершины
void Graph::removeVertex(int v) {
    try {
        if (v >= vertices_count_) {
            throw std::out_of_range("The vertex does not exist");
        }

        // Удаляем все ребра, связанные с данной вершиной
        edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
            [v](const std::pair<int, int>& edge) {
                return edge.first == v || edge.second == v;
            }), edges_.end());

        vertices_count_--;
    } catch (const std::exception& e) {
        std::cerr << "Error when deleting a vertex: " << e.what() << std::endl;
    }
}

// Добавление ребра с блоком try-catch
void Graph::addEdge(int u, int v) {
    try {
        if (u >= vertices_count_ || v >= vertices_count_) {
            throw std::out_of_range("One or both vertices do not exist");
        }
        edges_.emplace_back(u, v);
    } catch (const std::exception& e) {
        std::cerr << "Error when adding an edge: " << e.what() << std::endl;
    }
}

// Удаление ребра
void Graph::removeEdge(int u, int v) {
    edges_.erase(std::remove(edges_.begin(), edges_.end(), std::make_pair(u, v)), edges_.end());
}

// Печать графа
void Graph::printGraph() {
    for (const auto& edge : edges_) {
        std::cout << edge.first << " -> " << edge.second << std::endl;
    }
}

// Вспомогательная функция для обхода в глубину (DFS)
void Graph::dfsUtil(int v, std::vector<bool>& visited) {
    visited[v] = true;
    std::cout << v << " ";

    for (const auto& edge : edges_) {
        if (edge.first == v && !visited[edge.second]) {
            dfsUtil(edge.second, visited);
        }
    }
}

// Обход в глубину (DFS)
void Graph::dfs(int start_vertex) {
    std::vector<bool> visited(vertices_count_, false);
    dfsUtil(start_vertex, visited);
    std::cout << std::endl;
}

// Вспомогательная функция для алгоритма Косарайю (наполнение стека)
void Graph::fillOrder(int v, std::vector<bool>& visited, std::vector<int>& stack) {
    visited[v] = true;

    for (const auto& edge : edges_) {
        if (edge.first == v && !visited[edge.second]) {
            fillOrder(edge.second, visited, stack);
        }
    }
    stack.push_back(v);
}

// Получение транспонированного графа
Graph Graph::getTranspose() {
    Graph g(vertices_count_);
    for (const auto& edge : edges_) {
        g.addEdge(edge.second, edge.first);
    }
    return g;
}

// Вспомогательная функция для поиска компонент сильной связности
void Graph::dfsUtilForSCC(int v, std::vector<bool>& visited, std::vector<int>& scc) {
    visited[v] = true;
    scc.push_back(v);

    for (const auto& edge : edges_) {
        if (edge.first == v && !visited[edge.second]) {
            dfsUtilForSCC(edge.second, visited, scc);
        }
    }
}

// Поиск всех компонент сильной связности
void Graph::findSСС() {
    std::vector<bool> visited(vertices_count_, false);
    std::vector<int> stack;

    // Заполнение стека вершин в порядке завершения обхода
    for (int i = 0; i < vertices_count_; ++i) {
        if (!visited[i]) {
            fillOrder(i, visited, stack);
        }
    }

    // Получение транспонированного графа
    Graph gr = getTranspose();

    // Сброс состояния посещенных вершин
    std::fill(visited.begin(), visited.end(), false);

    // Обработка вершин в порядке, заданном в стеке
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();

        if (!visited[v]) {
            std::vector<int> scc;
            gr.dfsUtilForSCC(v, visited, scc);

            // Печать найденной компоненты сильной связности
            std::cout << "The component of strong connectivity: ";
            for (int vertex : scc) {
                std::cout << vertex << " ";
            }
            std::cout << std::endl;
        }
    }
}

// Чтение графа из файла
void Graph::readFromFile(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("The file could not be opened");
        }

        file >> vertices_count_;
        if (vertices_count_ < 5) {
            vertices_count_ = 5;
        }

        edges_.clear();

        int u, v;
        while (file >> u >> v) {
            if (u < vertices_count_ && v < vertices_count_) {
                addEdge(u, v);
            }
        }

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error when reading from a file: " << e.what() << std::endl;
    }
}
