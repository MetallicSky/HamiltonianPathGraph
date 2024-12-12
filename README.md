# Hamiltonian Path Graph

[Hamiltonian path (Wikipedia)](https://en.wikipedia.org/wiki/Hamiltonian_path)

[Depth-first search algorithm (Wikipedia)](https://en.wikipedia.org/wiki/Depth-first_search)

![presentation3](https://github.com/user-attachments/assets/fc41b4d1-3f14-4c1f-8d7f-f94da3bf764e)

## Core features:

1. Generate graph with specified amount of vertices
2. Choose how many edges (random between min and max) can each vertex have
3. Check if generated graph is connected
4. Proceed to find calculate all possible hamiltonian paths for this graph (a path from A to B that visits all other vertices once) and show a specified amount of the most short ones
5. Check any of the generated paths - both by highlighted edges and information in built-in console
6. Click on any vertex to see what it's connected to
7. Zoom in or out as you like, pan the camera by holding LMB
8. Ready to use Graph data type with various methods, checks and operator overloads 

## Clone and build

```
git clone https://github.com/MetallicSky/HamiltonianPathGraph.git
cd HamiltonianPathGraph
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
