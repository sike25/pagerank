#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

const int rows = 4;
const int cols = 4;
const int iterations = 10;

map<int, std::vector<int>> linkMatrixToAdjacencyMap(int matrix[rows][cols]) {
    // page -> {kidPage, kidPage}
    std::map<int, std::vector<int>> adjacencyMap;

    // pick a page
    for (int i = 0; i < rows; i++) {

        std::vector<int> linksFrom;
        // check what other pages it leads to (i.e. matrix[i][j] == 1)
        // and add them to its linksFrom
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                linksFrom.push_back(j);
            }
            // set that page to point at the linksFrom list in our adjacency map
            adjacencyMap[i] = linksFrom;
        }
    }

//    std::cout << "adjacency map:" << std::endl;
//    for (const auto &entry : adjacencyMap) {
//        std::cout << "Page: " << entry.first << ", Kids: ";
//        for (int value : entry.second) {
//            std::cout << value << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << " " << std::endl;

    return adjacencyMap;
}

std::map<int, float> runPageRank(int linkMatrix[rows][cols]) {
    // Convert matrix to adjacency map.
    // That is if [a][b] = 1 and [a][c] = 1 in the matrix, a -> {b, c} in the adjacency map
    // where a, b, and c are link Ids, indices of the matrix
    std::map<int, std::vector<int>> adjacencyMap = linkMatrixToAdjacencyMap(linkMatrix);

    // Initialize each value of pageRanks as 1/N where N is the number of webpages
    // So: map: webPageId or rowIndex -> pageRank or 1/N initially
    std::map<int, float> pageRanks;
    float initialPageRank = 1.0/rows;
    for (int i = 0; i < rows; i++){
        pageRanks.insert({i, initialPageRank});
    }

    // Run page rank until iterations are exhausted,
    // TODO: later, until the ranks stop changing substantially.
    for (int i = 0; i < iterations; i++) {

        // Pick a page
        for (int j = 0; j < rows; j++){
            // Collect the pages it leads to (kids),
            // and calculate the rank value to be added to the children pages' present rank
            std::vector<int> linksFrom = adjacencyMap[j];
            float rankToAddForKids = pageRanks[j] / (float) linksFrom.size();

            // Iterate through the kids of this page
            for (int childLink : linksFrom) {
                pageRanks[childLink] = pageRanks[childLink] + rankToAddForKids;
            }
        }
    }

//    std::cout << "Contents of the map:" << std::endl;
//    for (auto & pageRank : pageRanks) {
//        std::cout << "Page: " << pageRank.first << ", Rank: " << pageRank.second << std::endl;
//    }

    return pageRanks;
}

int main() {
    int testLinkStructure[rows][cols] = {
            {0, 1, 1, 1},
            {1, 0, 0, 0},
            {0, 1, 0, 1}
    };

    runPageRank(testLinkStructure);
    return 0;
}
