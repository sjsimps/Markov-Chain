#Using the Markov_Chain Data Structure:

This document overviews how to use the markov chain data structure
as contained within
[markov_chain.h](https://github.com/sjsimps/Markov-Chain/blob/master/Markov_Chain/markov_chain.h)

###Adding Nodes:

```C++
//Adds a single node without a previous state
void Add_Node(T current_event);
```

###Adding Edges:

```C++
//Adds a sequence of events to the chain
void Add_Event_Sequence(std::vector<T> data);

//Adds event to chain with previous state information
void Add_Event(T last_event, T current_event, unsigned int num_events = 1);
```

###Markov Chain Visualization:

```C++
//Writes markov chain to [.dot] format for visualization
void Export_To_Graphviz(std::string filename);
```

###Randomized Output:

```C++
//Outputs randomized state sequence
std::vector<T> Output_Random_Sequence (int output_length);
```

###Sample Code:

The following code snippet shows how to create and visualize a
markov chain of type std::string:

```C++
//Construct new chain
Markov_Chain<std::string>* chain = new Markov_Chain();

//Create nodes and edges
chain->Add_Event("a", "b", 3);
chain->Add_Event("b", "c", 1);
chain->Add_Event("c", "a", 1);
chain->Add_Event("c", "b", 2);

//Print status to console
chain->Print_To_Console();

//Produce Graphviz file
chain->Export_To_Graphviz("abc.dot");

//Delete chain
delete chain;
```

Visual Output:

Console Output:

```
State: a
Num Events: 3
Next States: [Frequency / Data]
    [b / 3]

State: b
Num Events: 1
Next States: [Frequency / Data]
    [c / 1]

State: c
Num Events: 3
Next States: [Frequency / Data]
    [a / 1]
    [b / 2]
```


