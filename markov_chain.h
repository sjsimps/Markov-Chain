
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

    //Add whole file to chain
    void Parse_File(std::string filename);

    //Add individual line to chain
    void Add_line_to_chain(std::string line);

    //Once all desired data has been added to the chain,
    //run this method to construct the markov chain.
    void Build_Chain();
    
    //Ouptut random sequence
    std::vector<std::string> Output_Chain (int output_size);

    struct Markov_Cfg
    {
        //Set to true to accept all input, unfiltered
        bool accept_all;

        //Set to true to separate data lines with newline
        //characters
        bool split_lines;

        //CSV Options
        bool use_csv;
        int csv_column;
        int csv_n_columns;
    } m_cfg;

    std::vector<std::string> m_data;
    std::map<std::string,State> m_map;

private:
    bool Is_Valid_Word(std::string word);
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
