#include "../include/graph.h"
#include "../include/graph.cc"
#include <locale>

int main() {

    setlocale(LC_ALL, "rus");

    // Создание экземпляра графа
    Graph<std::string, double> graph;

    // Добавление вершин
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_vertex("E");
    graph.add_vertex("F");

    // Добавление ребер
    graph.add_edge("A", "B", 4.5);
    graph.add_edge("A", "F", 1.5);
    graph.add_edge("D", "E", 5.5);
    graph.add_edge("C", "D", 4.5);
    graph.add_edge("D", "C", 4.5);
    graph.add_edge("B", "E", 5.0);
    graph.add_edge("D", "B", 1.0);
    graph.add_edge("F", "D", 5.5);

    graph.print_vertices();

    std::cout << std::endl;
    // Вывод списка ребер
    graph.print_edges();

    // Выполнение обхода в глубину, начиная с вершины "A"
    std::vector<std::string> dfs_result = graph.dfs("A");

    // Вывод результата обхода в глубину
    std::cout << "Поиск по глубине (начиная с A): " << std::endl;
    for (const auto& vertex : dfs_result) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Поиск кратчайшего пути
    std::vector<typename Graph<std::string, double>::Edge> path = graph.shortest_path("A", "E");
    std::cout << "Кратчайший путь из пункта А в пункт Е: ";
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    }
    std::cout << std::endl;

    // Проверка наличия ребра
    if (graph.has_edge("A", "B")) {
        std::cout << "Ребро (A, B) существует" << std::endl;
    }
    else {
        std::cout << "Ребро (A, B) не существует" << std::endl;
    }

    // Получение списка исходящих ребер из вершины
    std::cout << "Ребра, выходящие из А: ";
    for (const auto& edge : graph.exiting_edges("A")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    // Получение списка входящих ребер в вершину
    std::cout << "Ребра, входящие в D: ";
    for (const auto& edge : graph.incoming_edges("D")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    if (graph.remove_vertex("B")) {
        std::cout << "\n\nВершина B была удалена" << std::endl;
    }
    graph.print_vertices();

    if (graph.remove_vertex("F")) {
        std::cout << "\n\nВершина F была удалена" << std::endl;
    }
    graph.print_vertices();

    std::cout << std::endl;
    graph.print_edges();

    graph.remove_edge("C", "D");
    std::cout << "Ребро (C, D) было удалено" << std::endl;

    std::cout << "Кол-во вершин: " << graph.order() << std::endl;

    std::cout << "Степень вершины A: " << graph.degree("A") << std::endl;


    Graph<std::string, double> graph2;

    graph2.add_vertex("A");
    graph2.add_vertex("B");
    graph2.add_vertex("C");
    graph2.add_vertex("D");
    graph2.add_vertex("E");

    graph2.add_edge("A", "B", 5.0);
    graph2.add_edge("A", "C", 3.0);
    graph2.add_edge("B", "D", 2.0);
    graph2.add_edge("B", "E", 4.0);
    graph2.add_edge("C", "D", 6.0);
    graph2.add_edge("D", "E", 1.0);

    graph2.print_vertices();
    std::cout << std::endl;

    graph2.print_edges();

    // Определение самой удаленной вершины
    std::string farthest_vertex = graph2.find_farthest_vertex();
    std::cout << "Самая дальняя вершина - это: " << farthest_vertex << std::endl;

    return 0;
}
