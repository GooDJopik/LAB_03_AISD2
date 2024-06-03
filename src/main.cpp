#include "../include/graph.h"
#include "../include/graph.cc"

int main() {
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
    graph.add_edge("A", "C", 1.5);
    graph.add_edge("B", "C", 3.0);
    graph.add_edge("C", "D", 4.5);
    graph.add_edge("D", "E", 5.0);
    graph.add_edge("E", "A", 1.0);
    graph.add_edge("F", "B", 3.5);

    graph.print_vertices();

    // �������� �������
    if (graph.remove_vertex("B")) {
        std::cout << "\n\nVertex B has been removed" << std::endl;
    }
    graph.print_vertices();

    // �������� �������
    if (graph.remove_vertex("F")) {
        std::cout << "\n\nVertex F has been removed" << std::endl;
    }
    graph.print_vertices();

    std::cout << std::endl;
    // ����� ������ �����
    graph.print_edges();

    // �������� ������� �����
    if (graph.has_edge("A", "B")) {
        std::cout << "Edge (A, B) exists" << std::endl;
    }
    else {
        std::cout << "Edge (A, B) does not exist" << std::endl;
    }

    // ��������� ������ ��������� ����� �� �������
    std::cout << "Edges exiting from A: ";
    for (const auto& edge : graph.exiting_edges("A")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    // ��������� ������ �������� ����� � �������
    std::cout << "Edges incoming to D: ";
    for (const auto& edge : graph.incoming_edges("D")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    // �������� �����
    graph.remove_edge("E", "A");
    std::cout << "Edge (E, A) has been removed" << std::endl;

    // ��������� ���������� ������
    std::cout << "Order of the graph: " << graph.order() << std::endl;

    // ��������� ������� �������
    std::cout << "Degree of vertex A: " << graph.degree("A") << std::endl;

    // �������� ���������� �����
    Graph<std::string, double> graph2;

    // ���������� ������
    graph2.add_vertex("A");
    graph2.add_vertex("B");
    graph2.add_vertex("C");
    graph2.add_vertex("D");
    graph2.add_vertex("E");

    // ���������� �����
    graph2.add_edge("A", "B", 5.0);
    graph2.add_edge("A", "C", 3.0);
    graph2.add_edge("B", "D", 2.0);
    graph2.add_edge("B", "E", 4.0);
    graph2.add_edge("C", "D", 6.0);
    graph2.add_edge("D", "E", 1.0);

    // ����� ������ ������
    graph2.print_vertices();

    std::cout << std::endl;
    // ����� ������ �����
    graph2.print_edges();

    // ����� ����������� ����
    std::vector<typename Graph<std::string, double>::Edge> path = graph2.shortest_path("A", "E");
    std::cout << "Shortest path from A to E: ";
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    }
    std::cout << std::endl;

    // ����������� ����� ��������� �������
    std::string farthest_vertex = graph2.find_farthest_vertex();
    std::cout << "The farthest vertex is: " << farthest_vertex << std::endl;

    return 0;
}
