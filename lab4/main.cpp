#include <iostream>
#include <fstream>
#include <limits>

#include "booleanmatrix.h"

template<typename T>
using MatrixRow = DynamicArray<T>;

template<typename T>
using Matrix = DynamicArray<MatrixRow<T>>;

int main()
{
#if 0
    BooleanMatrix testMatrix1(10, 10, false);

    for (uint32_t i = 0; i < 10; ++i)
    {
        testMatrix1[i][i] = true;
    }

    std::cout << testMatrix1;
#endif

    std::fstream graphFile("graph.txt", std::ios::in);

    uint32_t numVertices;
    uint32_t numEdges;

    graphFile >> numVertices;
    graphFile >> numEdges;

    BooleanMatrix adjacencyMatrix(numVertices, numVertices, false);
    Matrix<uint32_t> weightMatrix;

    for (uint32_t i = 0; i < numVertices; ++i)
    {
        MatrixRow<uint32_t> matrixRow;

        for (uint32_t j = 0; j < numVertices; ++j)
        {
            matrixRow += 0;
        }

        weightMatrix += matrixRow;
    }

    for (uint32_t i = 0; i < numEdges; ++i)
    {
        uint32_t startVertex, endVertex, edgeWeight;

        graphFile >> startVertex >> endVertex >> edgeWeight;

#if 0
        std::cout << startVertex << " " << endVertex << " " << edgeWeight << std::endl;
#endif

        adjacencyMatrix[startVertex - 1][endVertex - 1] = true;
        adjacencyMatrix[endVertex - 1][startVertex - 1] = true;

        weightMatrix[startVertex - 1][endVertex - 1] = edgeWeight;
        weightMatrix[endVertex - 1][startVertex - 1] = edgeWeight;
    }

    std::cout << adjacencyMatrix << std::endl;

    DynamicArray<uint32_t> shortestPathLength;

    shortestPathLength += 0;

    for (uint32_t i = 1; i < numVertices; ++i)
    {
        shortestPathLength += std::numeric_limits<uint32_t>::max();
    }

    BooleanVector visitedVertices(numVertices, false);

    while (true)
    {
        if (visitedVertices.getWeight() == numVertices) break;

        uint32_t firstIndex = -1;
        uint32_t length = -1;

        for (uint32_t i = 0; i < numVertices; i++)
        {
            if (!visitedVertices[i])
            {
                firstIndex = i;
                length = shortestPathLength[i];
                break;
            }
        }

        for (uint32_t i = firstIndex + 1; i < numVertices; i++)
        {
            if (!visitedVertices[i] && shortestPathLength[i] < length)
            {
                length = shortestPathLength[i];
                firstIndex = i;
            }
        }

        for (uint32_t i = 0; i < numVertices; ++i)
        {
            if (adjacencyMatrix[firstIndex][i] && !visitedVertices[i])
            {
                uint32_t currPathLength = shortestPathLength[i];
                uint32_t probablyShorterPathLength = shortestPathLength[firstIndex] + weightMatrix[firstIndex][i];
                if (probablyShorterPathLength < currPathLength)
                {
                    shortestPathLength[i] = probablyShorterPathLength;
                }
            }
        }

        visitedVertices[firstIndex] = true;
    }

    return 0;
}