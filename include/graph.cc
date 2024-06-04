#include "../include/graph.h"

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
    return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
    if (has_vertex(v)) throw std::invalid_argument("[add_vertex] the vertex already exists");
    _vertices.push_back(v);
    _edges[v] = { };
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
    auto it = std::find(_vertices.begin(), _vertices.end(), v);
    if (it == _vertices.end()) return false;

    // ������� ������� �� ������ ������
    _vertices.erase(it);

    // ������� ��� �����, ��������� � ��������� ��������
    _edges.erase(v);
    for (auto& [vertex, edges] : _edges) {
        edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return e.to == v; }), edges.end());
    }

    return true;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& dist) {
    if (has_edge({ from, to, dist })) throw std::invalid_argument("[add_edge] the edge already exists");

    auto& edges = _edges[from];
    edges.push_back({ from, to, dist });
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e) {
    if (!has_edge(e)) return false;
    auto& edges = _edges.at(e.from);

    edges.erase(std::remove_if(edges.begin(), edges.end(), [e](const Edge& edge)
        { return (e.from == edge.from) && (e.to == edge.to) && (e.distance == edge.distance); }), edges.end());

    return true;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to) {
    if (!has_edge(from, to)) return false;
    auto& edges = _edges.at(from);

    edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return (e.from == from) && (e.to == to); }), edges.end());

    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) const {
    auto& edges = _edges.at(e.from);
    for (const auto& edge : edges) {
        if (edge.to == e.to && (abs(e.distance - edge.distance) < DBL_EPSILON)) return true;
    }
    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const {
    auto& edges = _edges.at(from);
    for (const auto& edge : edges) {
        if (edge.to == to) return true;
    }
    return false;
}

template<typename Vertex, typename Distance>
std::pair<typename std::vector<Vertex>::iterator, typename std::vector<Vertex>::iterator> Graph<Vertex, Distance>::vertices() {
    return { _vertices.begin(), _vertices.end() };
}

template<typename Vertex, typename Distance>
std::pair<typename std::vector<Vertex>::iterator, typename std::vector<Vertex>::iterator> Graph<Vertex, Distance>::edges(const Vertex& v) {
    return { exiting_edges(v).begin(), exiting_edges(v).end() };
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::exiting_edges(const Vertex& v) const {
    if (!has_vertex(v)) throw std::invalid_argument("[exiting_edges] there is no such vertex in the graph");

    return _edges.at(v);
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::incoming_edges(const Vertex& v) const {
    if (!has_vertex(v)) throw std::invalid_argument("[incoming_edges] there is no such vertex in the graph");
    std::vector<Edge> edges;
    for (auto& vertex : _vertices) {
        for (auto& edge : _edges.at(vertex))
            if (edge.to == v) edges.push_back(edge);
    }

    return edges;
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const {
    return _vertices.size();
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const {
    if (!has_vertex(v)) throw std::invalid_argument("[degree] there is no such vertex in the graph");

    return incoming_edges(v).size() + exiting_edges(v).size();
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::dfs(const Vertex& start_vertex) const { // ����� � �������
    if (!has_vertex(start_vertex)) throw std::invalid_argument("[dfs] there is no such vertex in the graph");

    std::vector<Vertex> result; // ���������� �������
    std::unordered_map<Vertex, Color> colors;

    for (const auto& vertex : _vertices) {
        colors[vertex] = Color::White;
    }

    std::stack<Vertex> stack;
    stack.push(start_vertex);
    colors[start_vertex] = Color::Gray;

    while (!stack.empty()) {
        Vertex current_vertex = stack.top();
        stack.pop();

        result.push_back(current_vertex);
        colors[current_vertex] = Color::Black;

        for (auto& edge : _edges.at(current_vertex)) {
            if (colors[edge.to] == Color::White) {
                stack.push(edge.to);
                colors[edge.to] = Color::Gray;
            }
        }
    }
    return result;
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const {
    if (!has_vertex(from) || !has_vertex(to))
        return {};

    std::unordered_map<Vertex, Distance> distances; // ���������� �� ��������� ������� from �� ������ �������
    std::unordered_map<Vertex, Vertex> prev; // ���������� ������� � ���������� ���� ��� ������ �������

    for (const auto& vertex : _vertices)
        distances[vertex] = std::numeric_limits<Distance>::max();
    distances[from] = 0;

    for (size_t i = 0; i < _vertices.size() - 1; ++i) {
        for (const auto& vertex : _vertices) {
            for (const auto& edge : _edges.at(vertex)) {
                if (distances[edge.from] + edge.distance < distances[edge.to]) {
                    distances[edge.to] = distances[edge.from] + edge.distance;
                    prev[edge.to] = edge.from;
                }
            }
        }
    }

    // �������� �� ������������� �����
    for (const auto& vertex : _vertices) {
        for (const auto& edge : _edges.at(vertex)) {
            if (distances[edge.from] + edge.distance < distances[edge.to]) {
                throw std::runtime_error("Negative cycles");
            }
        }
    }

    std::vector<Edge> path;
    Vertex current = to;
    while (current != from) {
        for (const auto& edge : _edges.at(prev[current])) {
            if (edge.to == current) {
                path.push_back(edge);
                break;
            }
        }
        current = prev[current];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

template<typename Vertex, typename Distance>
Distance Graph<Vertex, Distance>::length_shortest_path(const Vertex& start, const Vertex& end) const {
    std::vector<Edge> edges = shortest_path(start, end);
    Distance len = 0;
    for (const auto& edge : edges) {
        len += edge.distance;
    }
    return len;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print_vertices() const {
    std::cout << "Vertices: [ ";
    for (const Vertex& vertex : _vertices) {
        if (vertex != _vertices.back()) std::cout << vertex << ", ";
        else std::cout << vertex << " ]";
    }
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print_edges() const {
    std::cout << "Edges: " << std::endl;
    for (const Vertex& vertex : _vertices) {
        for (const Edge& edge : _edges.at(vertex)) {
            std::cout << edge.from << " -> " << edge.to << "(" << edge.distance << ")" << std::endl;
        }
    }
}

template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::find_farthest_vertex() {
    Vertex farthest_vertex{};//�������, �������� �������� �� ������ ������.
    Distance max_avg_distance = 0;//������������ ������� ���������� �� �����-���� ������� �� � �������.

    for (const auto& vertex : _vertices) {
        // ��������� ������� ���������� �� ������� ������� �� � �������
        Distance avg_distance = 0;
        size_t num_neighbors = 0;//���������� �������
        for (const auto& edge : exiting_edges(vertex)) {
            avg_distance += length_shortest_path(vertex, edge.to);
            num_neighbors++;
        }
        if (num_neighbors > 0) {
            avg_distance /= num_neighbors;
        }

        // ��������� ������������ ������� ���������� � ���������� ������� �������
        if (avg_distance > max_avg_distance) {
            max_avg_distance = avg_distance;
            farthest_vertex = vertex;
        }
    }

    return farthest_vertex;
}