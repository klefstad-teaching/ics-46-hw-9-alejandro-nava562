#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

// ========== WORD LADDER TESTS ========== //

// Test 1: Simple word ladder transformation
TEST(WordLadderTest, BasicTransformation) {
    set<string> word_list = {"cat", "bat", "bet", "bot", "bog", "dog"};

    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    vector<string> expected = {"cat", "bat", "bot", "bog", "dog"};

    EXPECT_EQ(ladder, expected);
}

// Test 2: Word ladder with different lengths
TEST(WordLadderTest, VaryingWordLengths) {
    set<string> word_list = {"car", "cat", "chat", "cheat"};

    vector<string> ladder = generate_word_ladder("car", "cheat", word_list);
    vector<string> expected = {"car", "cat", "chat", "cheat"};

    EXPECT_EQ(ladder, expected);
}

// Test 3: No possible transformation
TEST(WordLadderTest, NoLadderFound) {
    set<string> word_list = {"cat", "dog", "bird"};

    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);

    EXPECT_TRUE(ladder.empty());  // No transformation possible
}

// Test 4: Start and end word are the same
TEST(WordLadderTest, SameStartEndWord) {
    set<string> word_list = {"code", "cade", "cate", "date", "data"};

    vector<string> ladder = generate_word_ladder("code", "code", word_list);

    EXPECT_EQ(ladder.size(), 1);
    EXPECT_EQ(ladder.front(), "code");
}

// ========== DIJKSTRA'S ALGORITHM TESTS ========== //

// Test 1: Simple Graph with 3 Nodes
TEST(DijkstraTest, SmallGraph) {
    Graph G;
    G.numVertices = 3;
    G.resize(3);
    
    G[0].push_back(Edge(0, 1, 4));
    G[0].push_back(Edge(0, 2, 1));
    G[2].push_back(Edge(2, 1, 2));

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 1);
}

// Test 2: Graph with an Unreachable Node
TEST(DijkstraTest, UnreachableNode) {
    Graph G;
    G.numVertices = 4;
    G.resize(4);

    G[0].push_back(Edge(0, 1, 2));
    G[1].push_back(Edge(1, 2, 3));
    // Node 3 is disconnected

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 2);
    EXPECT_EQ(distances[2], 5);
    EXPECT_EQ(distances[3], INF);  // Node 3 is unreachable
}

// Test 3: Extract Shortest Path from Dijkstra
TEST(DijkstraTest, ExtractPath) {
    Graph G;
    G.numVertices = 3;
    G.resize(3);
    
    G[0].push_back(Edge(0, 1, 2));
    G[1].push_back(Edge(1, 2, 3));

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    vector<int> path = extract_shortest_path(distances, previous, 2);

    vector<int> expected_path = {0, 1, 2};
    EXPECT_EQ(path, expected_path);
}

// Test 4: Graph with Single Node
TEST(DijkstraTest, SingleNode) {
    Graph G;
    G.numVertices = 1;
    G.resize(1);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
}

// Test 5: Larger Graph with Multiple Paths
TEST(DijkstraTest, LargeGraph) {
    Graph G;
    G.numVertices = 5;
    G.resize(5);

    G[0].push_back(Edge(0, 1, 10));
    G[0].push_back(Edge(0, 2, 3));
    G[1].push_back(Edge(1, 2, 1));
    G[1].push_back(Edge(1, 3, 2));
    G[2].push_back(Edge(2, 1, 4));
    G[2].push_back(Edge(2, 3, 8));
    G[2].push_back(Edge(2, 4, 2));
    G[3].push_back(Edge(3, 4, 7));
    G[4].push_back(Edge(4, 3, 9));

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 7);  // 0 -> 2 -> 1 (3+4)
    EXPECT_EQ(distances[2], 3);  // 0 -> 2 (3)
    EXPECT_EQ(distances[3], 9);  // 0 -> 2 -> 4 -> 3 (3+2+4)
    EXPECT_EQ(distances[4], 5);  // 0 -> 2 -> 4 (3+2)
}

// Main function for running all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

