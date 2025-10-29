# Assignment 4 = Programming Part A and B
**Author:** Nichole Lin\
**Language:** C++

# Graph.cpp
- Graph::Graph()
Initializes n and directed or not and resizes adjacency list
- addEdge(u,v)
adds connections \
If directed: only 1 direction\
If undirected: adds both ways

- hasCycleUndirected()
Uses DFS to detect cycles\
visited[] - tracks which nodes are seen\
parentList[] - remembers the parent node to avoid false cycle detection\
If DFS fins an already visited neighbor that's not theparent, a cycle exists\
Prints the actual cycle path when found

- dfsTopologicalSort()
Performs DFS on a directed graph\
Records discovery time and finishing time\
Labels edges as\
T = Tree edge\
B = Back edge\
F = Forward edge\
C = Cross edge\
Builds a topological order \
Write all this to the outputfile

- isBipartite()
Check if graph can be colored with two colors (0 or 1) so that no two adjacent vertices share the same color\
Uses BFS\
Alternates colors between neighbors\
If 2 connected vertices share the same color -> not bipartite\
Prints set V1 and V2 if it is

# Q2b
Tests undirected graphs using the hasCycleUndirected() function\
Creates 2 sample graphs (G1 and G2)\
Add edges manually\
Writes adjacency list to file\
Runs cycle detection\
Writes each graph as cyclic or acyclic\
Measures and prints runtime in nanoseconds

# Q5b
Test directed graph functionality\
Creates graph G with 8 vertices\
Add edges manually\
Write adjacency list to file\
Runs dfsTopologicalSort()\
    - Performs DGS\
    - Prints discorvery/finsih times\
    - Labels each edge (T, B, F, C)\
    - Prints topological order\
Measures and prints runtime in nanoseconds

# Q6b
Checks if a given undirected graph is bipartite\
Builds a graph of 11 nodes 
Writes adjacency list to file\
Calls isBipartite()\
    - Uses BFS coloring\
    - Outputs "Graph is bipartite and list two disjoint sets\
    - Or Outputs "Graph is NOT bipartite\
Measures and prints runtime in nanoseconds

# B1
Simulates course scheduling with prerequisites using graph layering\
Each course = node, edges = prerequisites\
Builds graph from 15 CS courses\
Computes indegree[] (how many prereq each course has)\
Repeatedly takes courses with indegree 0 -> 1 semesster's worth\
Reduces indegree of courses that depend on them\
Counts semesters needed until all courses are done\
Detects cycles = invalid schedule\
Write to output file which course can be taken each semester and total semesters

# B2
Minimizes cost of 2 drinks (X and Y) while meeting calories and vitamin requirements\
Uses brute-force intersection checks of constraint lines\
    - x + y ≥ 5\
    - 2x +y ≥ 6\
    - x +3y ≥ 9\
Computes candidate intersection points manually\
Teste each candidate for feasibility using cases()\
Calculate total cost (0.12x + 0.15y)\
Keeps the minimum\
Prints optimal number of cups for each drink and minimum cost\
Measures and prints runtime in nanoseconds