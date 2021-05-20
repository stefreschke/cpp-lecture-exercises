
#pragma once

#include <vector>
#include <array>
#include <memory>

#include <InstanceCounter.h>


/*
 * @class Vertex
 */
class Vertex {
public:
    explicit Vertex(std::int32_t id);

    std::int32_t id() const;

private:
    std::int32_t m_id;
    InstanceCounter<Vertex> m_instanceCounter;
};


/*
 * @class Edge
 */
class Edge {
public:
    // Edge(Vertex * v0, Vertex * v1, std::int32_t weight);
    Edge(std::shared_ptr<Vertex> v0, std::shared_ptr<Vertex> v1, std::int32_t weight);

    // void reset(Vertex * v0, Vertex * v1);
    void reset(std::shared_ptr<Vertex> v0, std::shared_ptr<Vertex> v1);

    std::int32_t weight() const;

    // Vertex * v0() const;
    std::shared_ptr<Vertex> v0() const;
    // Vertex * v1() const;
    std::shared_ptr<Vertex> v1() const;

private:
    std::int32_t m_weight;

    // Vertex * m_v0;
    std::weak_ptr<Vertex> m_v0;
    // Vertex * m_v1;
    std::weak_ptr<Vertex> m_v1;

    InstanceCounter<Edge> m_instanceCounter;
};


/*
 * @class Graph
 */
class Graph {
public:
    // void addVertex(Vertex * vertex);
    void addVertex(std::shared_ptr<Vertex> vertex);

    // void addEdge(Edge * edge);
    void addEdge(std::shared_ptr<Edge> edge);

    // const std::vector<Vertex *> & vertices() const;
    const std::vector<std::shared_ptr<Vertex>> & vertices() const;

    // const std::vector<Edge *> & edges() const;
    const std::vector<std::shared_ptr<Edge>> & edges() const;

    /*
     * @postcondition g2 is empty, i.e., does not contain any vertices or edges
     */
    // void merge(Graph *  g2);
    void merge(std::shared_ptr<Graph>  g2);
    // Graph * minimumSpanningTree() const;
    std::shared_ptr<Graph> minimumSpanningTree() const;
    // friend std::ostream& operator<<(std::ostream& stream, const Graph & graph);
    friend std::ostream& operator<<(std::ostream& stream, const Graph & graph);

private:
    // std::vector<Vertex *> m_vertices;
    std::vector<std::shared_ptr<Vertex>> m_vertices;
    // std::vector<Edge *> m_edges;
    std::vector<std::shared_ptr<Edge>> m_edges;
    InstanceCounter<Graph> m_instanceCounter;
};
