
#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

struct Markov_Edge;
struct Markov_State;

class Markov_Chain
{
public:
    Markov_Chain();
    ~Markov_Chain();

    //To add a single event to the chain, use this method.
    void Add_Event(std::string last_event, std::string current_event);

    //Output randomized state sequence
    std::vector<std::string> Output_Random_Sequence (int output_length);

    //Output current chain status to console
    void To_String();

    // Every Markov state is indexed by m_map using a data string
    std::map<std::string,Markov_State> m_map;

};


struct Markov_State
{
    std::string data;       //Data that corresponds to this state
    unsigned int num_events;//Number of times this state has occured given the input data
    Markov_Edge* edge_list; //List containing all edges to a next possible state
};

struct Markov_Edge
{
    unsigned int event_rate; //Number of time this edge has been taken from previous state given the input data
    Markov_State* next_state;//Next state corresponding to this edge
    Markov_Edge* next_edge;  //Next edge within the edge list
};

#endif
