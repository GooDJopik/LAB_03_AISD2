#include "../include/graph.h"
#include "../include/graph.cc"
#include <locale>

int main() {

    setlocale(LC_ALL, "rus");

    // �������� ���������� �����
    Graph<std::string, double> graph;

    // ���������� ������
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_vertex("E");
    graph.add_vertex("F");

    // ���������� �����
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
    // ����� ������ �����
    graph.print_edges();

    // ���������� ������ � �������, ������� � ������� "A"
    std::vector<std::string> dfs_result = graph.dfs("A");

    // ����� ���������� ������ � �������
    std::cout << "����� �� ������� (������� � A): " << std::endl;
    for (const auto& vertex : dfs_result) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // ����� ����������� ����
    std::vector<typename Graph<std::string, double>::Edge> path = graph.shortest_path("A", "E");
    std::cout << "���������� ���� �� ������ � � ����� �: ";
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    }
    std::cout << std::endl;

    // �������� ������� �����
    if (graph.has_edge("A", "B")) {
        std::cout << "����� (A, B) ����������" << std::endl;
    }
    else {
        std::cout << "����� (A, B) �� ����������" << std::endl;
    }

    // ��������� ������ ��������� ����� �� �������
    std::cout << "�����, ��������� �� �: ";
    for (const auto& edge : graph.exiting_edges("A")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    // ��������� ������ �������� ����� � �������
    std::cout << "�����, �������� � D: ";
    for (const auto& edge : graph.incoming_edges("D")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    if (graph.remove_vertex("B")) {
        std::cout << "\n\n������� B ���� �������" << std::endl;
    }
    graph.print_vertices();

    if (graph.remove_vertex("F")) {
        std::cout << "\n\n������� F ���� �������" << std::endl;
    }
    graph.print_vertices();

    std::cout << std::endl;
    graph.print_edges();

    graph.remove_edge("C", "D");
    std::cout << "����� (C, D) ���� �������" << std::endl;

    std::cout << "���-�� ������: " << graph.order() << std::endl;

    std::cout << "������� ������� A: " << graph.degree("A") << std::endl;


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

    // ����������� ����� ��������� �������
    std::string farthest_vertex = graph2.find_farthest_vertex();
    std::cout << "����� ������� ������� - ���: " << farthest_vertex << std::endl;

    return 0;
}
