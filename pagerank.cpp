#include <iostream>
#include <map>
#include <list>
using namespace std;

const int rows = 4;
const int cols = 4;
const int iterations = 10;

int main() {
  int testLinkStructure[rows][cols] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
  }; 
  int rows = 4;
  int cols = 4;

  runPageRank(testLinkStructure); 
  return 0;
}

int runPageRank(int linkMatrix[rows][cols]) {
  // Convert matrix to adjacency list. 
  // That is if [a][b] = 1 in the matrix, a -> {b} in the adjacency map
  std::map<int, std::list<int>> adjacencyList = linkMatrixToAdjacencyList(linkMatrix);

  // Initialize each value of pageRanks as 1/N where N is the number of webpages
  // So: webPageId or rowIndex -> pageRank or 1/N initially
  std::map<int, float> pageRanks;
  float initialPageRank = 1/rows;
  for (int i = 0; i < rows; i++){
    pageRanks.insert({i, initialPageRank});
  }

  // Run page rank until iterations are exhausted, 
  // later, until the ranks stop changing substantially.
  for (int i = 0; i < iterations; i++) {

    // Pick a page
    for (int j = 0; j < rows; j++){
      // Collect the pages it leads to, how many they are, 
      // and the pageRank to be added to the children pages.
      std::list linksFrom = adjacencyList[j];
      int noOfLinksFrom = sizeof(linksFrom);
      float rankToAddForKids = pageRanks[i] / noOfLinksFrom;

      // Iterate through the kids of this page
      for (int k = 0; k < noOfLinksFrom; k++) {
        // int linkFrom = linksFrom;

      }

    }
  }



  return 0;
}

map<int, std::list<int>> linkMatrixToAdjacencyList(int matrix[rows][cols]) {
  std::map<int, std::list<int>> adjacencyList;
  for (int i = 0; i < rows; i++) {
    std::list<int> linksFrom;
    if (adjacencyList.find(i) != adjacencyList.end()) {
      linksFrom = adjacencyList[i];
    }

    for (int j = 0; j < cols; j++) {
      int entry = matrix[i][j];
      if (entry == 1) {
        linksFrom.push_back(j);
        adjacencyList[i] = linksFrom;
      }
    }
  }
  return adjacencyList;
}


/**
 * 
*/#   p a g e r a n k  
 