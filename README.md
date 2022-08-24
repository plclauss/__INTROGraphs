# Graphs, Intro.

While graphs also build off concepts of linked lists, the implementation details are largely different from anything I've seen yet. There were also a number of questions I had when building a graph, which we'll get into shortly.

---

## Background

The only exposure to graphs I've had prior to this project were:

- [_Clément Mihailescu's mock coding interview with William Lin_](https://www.youtube.com/watch?v=qz9tKlF431k) and
- Unique network-connectivity graphs, like this one, found in a [_Medium article published by Brim Security_](https://medium.com/brim-securitys-knowledge-funnel/visualizing-ip-traffic-with-brim-zeek-and-networkx-3844a4c25a2f).

I have to be honest, though: I've watched that mock interview video a lot, so that's where a lot of my "knowledge" came from. I noticed in the video that, Mihailescu provided Lin with two very important pieces of information:
1. The nodes of the graph (represented by starting airports), provided in the form of an array, and
2. An effective adjacency list, having pairs of airports; the first of which was a starting airport who had a nonstop connection to the second airport. So, while not entire adjacency list, as I *believe* it was missing key formatting details, it nonetheless provided edges for certain starting airports in the graph.

When implementing my graph (an undirected, weighted graph, containing a number of airports in the most populous cities United States with nonstop connections to other populous cities' airports), I asked:

> _Q_: When looking to create a graph, must I have all the information for the graph beforehand? That is, should I have all the starting airports and their connections to the other airports?

*A*: Short answer, no. It may be ideal to have **all** starting airports and their connections in the graph to start, so that you create a graph one time, and you can forget about it. However, we must consider scalability. <br>
What if a growing hotspot decides to build its own central airport, and flyers from one populous city (already in the graph) want to reach that hotspot destination? Well, you need to add the airport and its connections to the graph, as well as update any existing nodes already in the graph. <br>
What if, say, a pandemic hits and no one's allowed to fly in or out of a major city? Well, it might not be the best option to remove the airport from the graph entirely, as it may be available later, post-pandemic, but it'd be a good thing to let flyers know that flights to that destination are no longer occurring for the time being.

There's likely a large sum of questions relating to scalability here. Just know that, in this case, you'd *not* need every airport in the United States and it's connections. Start with the most populous ones, and add/remove from the graph as you see fit.

> _Q_: More of a concern, but: What are the complications of having an undirected, weighted graph?

*A*: Speaking purely theoretically here, since I've yet to do any practice problems with graphs, and I am unsure as to what the best practices are for graph infrastructure, most of the concerns reveal themselves when adding/removing nodes from the graph.

### Adding a node

Adding a node, even in the default construction of the graph, at least for an undirected graph, I *believe* it was required to make back-and-forth connections between airports. For instance, if ***IAD*** was connected to ***JFK***, then ***JFK*** would appear in the list of connections belonging to ***IAD***, and ***IAD*** would appear in the list of connections belonging to ***JFK***. I'm slightly uncertain about this implementation, however, because I'm curious if, as long as one connection exists between the two, any ordinary algorithm, like BFS, would still work. Although, there's likely a clever way to construct the graph such that this is the case; in my implementation, it seemed necessary to have both connections in both nodes.<br>
Adding additional nodes to the graph meant something similar: If the new node to be added had connections to a previously-added node, then we'd need to access that node and add the new node into it's list of connections.

### Deleting a node

Deleting an already existing node meant not only removing the node from the actual graph itself (*i.e.*, removed from the `Graph` class's `std::vector<Component> graph`), but also removing every instance of that node in every previously-added node who had a connection to the deleted node. <br>
...Lots of nodes, but alas.

---

## Classes and Private Data Members

As a crash course into my implementation:

- A class called `Graph` represented the entire graph; every node and its connections. This is also where all analysis of the graph would take place, such as finding the shortest path between two airports.
- A class called `Component`, which I've been referring to as "nodes." These are the airports themselves. They have an ID number, an airport code, and a list of connections to other airports (by their ID number) via a class called `Edge`.
- The `Edge` class simply holds a linked list containing that `Component`'s nonstop flight connections. In hindsight, this added class is likely unnecessary; I could've just added the `std::list<std::pair<int32_t, int32_t>> connections` directly under the `Component` class. 

---

### Issues

As far as I can tell, there are two major bugs with this implementation:

> *I*: Having numerous classes in the same file is difficult, especially if you don't want the client messing with any code relating to classes they shouldn't be referencing, like the `Component` and `Edge` classes. All the work is done through the `Graph` class provided the correct input.

*S*: I believe a possible solution is providing only the `Graph.h` file to `main.cpp`, and moving the `Component` (and `Edge`) classes to their own separate `.h/.cpp` files, referenced only by the `Graph.h` file.

> *I*: Extraneous classes. 

*S*: Either removing unnecessary classes or finding out clever implementation details such that one class is capable of accessing another class's public member functions, whose simultaneous (potential) use by the client doesn't also mess with anything important.<br>
For instance, when deleting nodes from the graph, I also updated each `Component`'s ID numbers; however, the ID number of a `Component` is clearly a private data member not accessible by the `Graph` class where the function was called from, and it's unwise to allow the user to arbitrarily change the IDs of a `Component` without reason. This is a huge implementation error that needed more thought in the design phase.

---

### A Quick Note:

There was a point where I tried to use static integers for the ID numbers of `Component`'s, but there's an interesting reason as to why C++'s compiler does not allow static data members in objects. See [here](https://stackoverflow.com/questions/61518284/error-non-const-static-data-member-must-be-initialized-out-of-line) for more details.

---

Happy Coding! :computer: