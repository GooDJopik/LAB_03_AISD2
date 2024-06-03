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

    _vertices.erase(it);

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
