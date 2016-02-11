
#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Edge;
struct State;

class Markov_Chain
{
public:
    Markov_Chain();
    ~Markov_Chain();

    void Parse_File(std::string filename);
    void Build_Chain();
    void Output_Chain (int output_size);

    struct Markov_Cfg
    {
        bool accept_all;
        bool split_lines;
        bool use_csv;
        int state_length;
    } m_cfg;

    std::vector<std::string> m_data;
    std::map<std::string,State> m_map;

private:
    bool Is_Valid_Word(std::string word);
    void Add_line_to_chain(std::string line);
    void Initialize_Cfg();
};

struct State
{
    std::string data;
    unsigned int num_events;
    Edge* edge_list;
};

struct Edge
{
    unsigned int event_rate;
    State* next_state;
    Edge* next_edge;
};

#endif
