#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <iostream>
#include <vector>


class Neighbor
{
public:


    int label;
    int weight;

    Neighbor(){};

    Neighbor(int label){
        this->label = label;
    };

    Neighbor(int label , int weight){
        this->label = label;
        this->weight = weight;
    }

    ~Neighbor(){};

    bool operator ==(const Neighbor &N){
        return (this->label == N.label) && (this->weight == N.weight);
    }

};

class Vertex
{

public:
    int label;

    std::vector<Neighbor> neighbors;
    Vertex(){};
    Vertex(int label){
        this->label = label;
    }
    ~Vertex(){};
};


class Graph_operations
{
public:

    std::vector<Vertex> VertexArr;
    virtual void Allocate_vertexMem(int n) = 0;
    virtual void addEdge(const int label_1, const int label_2 , const int weight) = 0;
    virtual int shortest_path(const int label_1 , const int label_2) = 0;
    virtual int mst_weight() = 0;
    virtual bool two_colorable() = 0;

};


class Implement : public Graph_operations
{
public:
    void Allocate_vertexMem(int n)
    {
        VertexArr.resize(n);
        for(int i = 0 ; i < n ; i++)
            VertexArr[i].label = i;
    }
    void addEdge(const int label_1, const int label_2 , const int weight);
	int shortest_path(const int label_1 , const int label_2);
	int mst_weight();
	bool two_colorable();
};


#endif // FUNCTION_H
