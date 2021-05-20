
#include <Graph.h>

#include <map>
#include <set>
#include <iostream>



//
// Class Vertex
//


Vertex::Vertex(std::int32_t id)
: m_id{id}
{
}


std::int32_t Vertex::id() const
{
    return m_id;
}




//
// Class Edge
//


// Edge::Edge(Vertex * v0, Vertex * v1, std::int32_t weight)
Edge::Edge(std::shared_ptr<Vertex> v0, std::shared_ptr<Vertex> v1, std::int32_t weight)
: m_weight{weight}
{
    reset(v0, v1);
}


// void Edge::reset(Vertex * v0, Vertex * v1)
void Edge::reset(std::shared_ptr<Vertex> v0, std::shared_ptr<Vertex> v1)
{
    if (v0 < v1)
    {
        m_v0 = v0;
        m_v1 = v1;
    }
    else
    {
        m_v0 = v1;
        m_v1 = v0;
    }
}


std::int32_t Edge::weight() const
{
    return m_weight;
}


// Vertex * Edge::v0() const
std::shared_ptr<Vertex> Edge::v0() const
{
    if (auto shr = m_v0.lock()) {
        return shr;
    } else {
        return nullptr;
    }
}


// Vertex * Edge::v1() const
std::shared_ptr<Vertex> Edge::v1() const
{
    if (auto shr = m_v1.lock()) {
        return shr;
    } else {
        return nullptr;
    }
}




//
// Class Graph
//


// const std::vector<Vertex *> & Graph::vertices() const
const std::vector<std::shared_ptr<Vertex>> & Graph::vertices() const
{
    return m_vertices;
}


// const std::vector<Edge *> & Graph::edges() const
const std::vector<std::shared_ptr<Edge>> & Graph::edges() const
{
    return m_edges;
}


// void Graph::addVertex(Vertex * vertex)
void Graph::addVertex(std::shared_ptr<Vertex> vertex)
{
    m_vertices.emplace_back(vertex);
}


// void Graph::addEdge(Edge * edge)
void Graph::addEdge(std::shared_ptr<Edge> edge)
{
    m_edges.emplace_back(std::move(edge));
}


// void Graph::merge(Graph * g2)
void Graph::merge(std::shared_ptr<Graph> g2)
{
    // Edge id for the purpose of creating a map/set
    using EdgeId = std::pair<std::int32_t, std::int32_t>;
    // auto makeId = [](Edge * edge) { return std::make_pair(edge->v0()->id(), edge->v1()->id()); };
    auto makeId = [](std::shared_ptr<Edge> edge) {
        return std::make_pair(edge->v0()->id(), edge->v1()->id());
    };

    // build map for fast lookup of vertices by id
    // auto vertexMap = std::map<int, Vertex *>{};
    auto vertexMap = std::map<int, std::shared_ptr<Vertex>>{};
    for (const auto & vertex : m_vertices)
    {
        vertexMap[vertex->id()] = vertex;
    }

    // build map for fast lookup of edges by ids of its vertices
    auto edgeSet = std::set<EdgeId>{};
    for (const auto & edge : m_edges)
    {
        edgeSet.insert(std::make_pair(edge->v0()->id(), edge->v1()->id()));
    }

    // merge vertices
    for (const auto & vertex : g2->m_vertices)
    {
        if (vertexMap.find(vertex->id()) == vertexMap.end())
        {
            vertexMap[vertex->id()] = vertex;
            m_vertices.emplace_back(vertex);
        }
    }

    // merge edges
    for (const auto & edge : g2->m_edges)
    {
        if (edgeSet.find(std::make_pair(edge->v0()->id(), edge->v1()->id())) == edgeSet.end())
        {
            // rewire pointers
            const auto & v0 = vertexMap[edge->v0()->id()];
            const auto & v1 = vertexMap[edge->v1()->id()];
            edge->reset(v0, v1);

            edgeSet.insert(std::make_pair(edge->v0()->id(), edge->v1()->id()));
            m_edges.push_back(edge);
            m_edges.emplace_back(edge);
        }
    }

    // delete g2;
    std::move(g2);
}


std::ostream & operator<<(std::ostream & stream, const Graph & graph)
{
    for (const auto & edge : graph.edges())
    {
        stream << "(" << edge->v0()->id() << "," << edge->v1()->id() << ") ";
    }
    return stream;
}
