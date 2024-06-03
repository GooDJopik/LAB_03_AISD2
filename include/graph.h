#ifndef LAB3_INCLUDE_GRAF_H
#define LAB3_INCLUDE_GRAF_H

#include <algorithm>
#include <cfloat>
#include <iostream>
#include <iterator>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from, to;
        Distance distance;
    };

    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);

    bool has_edge(const Edge& e) const;
    bool has_edge(const Vertex& from, const Vertex& to) const;
    void add_edge(const Vertex& from, const Vertex& to, const Distance& dist);
    bool remove_edge(const Edge& e);
    bool remove_edge(const Vertex& from, const Vertex& to);

private:
    std::vector<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;
};

#endif // LAB3_INCLUDE_GRAF_H
