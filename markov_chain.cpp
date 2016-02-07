
#include <fstream>
#include <vector>
#include <regex>
#include <stdlib.h>

#include "markov_chain.h"

Markov_Chain::Markov_Chain()
{
    Initialize_Cfg();
}

Markov_Chain::~Markov_Chain()
{
}

void Markov_Chain::Initialize_Cfg()
{
    m_cfg.parse_by_line = false;
    m_cfg.state_length = 1;
    m_cfg.accept_all = false;
    m_cfg.split_lines = false;
}

bool Markov_Chain::Is_Valid_Word(std::string word)
{
    bool retval = m_cfg.accept_all;
    std::regex match_word ("[a-zA-Z,\\.]*", std::regex_constants::basic);
    retval = retval || std::regex_match(word, match_word);
    return retval;
}

static void Print_String_Vector(std::vector<std::string> arr)
{
    const int size = arr.size();
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void Markov_Chain::Parse_File(std::string filename, std::vector<std::string>* words)
{
    std::ifstream file;
    std::string line;
    std::string word;
    int position = 0;
    int is_end;
    int line_length;

    file.open(filename);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            line_length = line.length();
            position = 0;
            for (int i = 0; i < line_length; i++)
            {
                is_end = (i == line_length - 1) ? 1 : 0;
                
                if (line[i] == ' ' || is_end)
                {
                    word = line.substr(position, i - position + is_end);
                    position = (++i) % line_length;
                    
                    if (Is_Valid_Word(word))
                    {
                        words->push_back(word);
                    }
                }
            }
            if (m_cfg.split_lines) words->push_back("\n");
        }
        file.close();
    }
    else
    {
        std::cout << "File \"" << filename << "\" could not be opened!";
        exit(EXIT_FAILURE);
    }

    Print_String_Vector(*words);
}

void Markov_Chain::Build_Chain()
{
    const int data_size = m_data.size();

    for (int i = 0; i < data_size; i++)
    {
        //If the map contains this state already:
        if (m_map.count(m_data[i]))
        {
            m_map[m_data[i]].num_events++;
        }
        else
        {
            State new_state;
            new_state.num_events = 1;
            new_state.data = m_data[i];
            new_state.edge_list = NULL;

            m_map.insert(std::pair<std::string,State>(m_data[i],new_state));
        }

        if (i>0)
        {
            Edge* index;
            index = m_map[m_data[i-1]].edge_list;

            if (index == NULL)
            {
                m_map[m_data[i-1]].edge_list = new Edge;
                index = m_map[m_data[i-1]].edge_list;
                index->event_rate = 1;
                index->next_state = &m_map[m_data[i]];
                index->next_edge = NULL;
            }
            else
            {
                while (index->next_edge != NULL && index->next_state->data != m_data[i])
                {
                    index = index->next_edge;
                }

                if (index->next_edge == NULL)
                {
                    index->next_edge = new Edge;
                    index = index->next_edge;
                    index->event_rate = 1;
                    index->next_state = &m_map[m_data[i]];
                    index->next_edge = NULL;
                }
                else
                {
                    index->event_rate++;
                }
            }
        }

    }
}

void Markov_Chain::Output_Chain (int fd, int output_size)
{
    srand (time(NULL));

    int count = 0;
    int val = rand() % m_data.size();
    State state = m_map[m_data[val]];
    Edge* edge = state.edge_list;


    std::cout << "\nOUTPUT:\n" ;
    while (count < output_size && edge != NULL)
    {
        std::cout << state.data << " ";
        val = rand() % state.num_events;
        while(val >= 0 && edge->next_edge != NULL)
        {
            val -= edge->event_rate;
            if (val >= 0) edge = edge->next_edge;
        }
        state = *edge->next_state;
        edge = state.edge_list;
        count++;
    }
    std::cout << "\n";
}




