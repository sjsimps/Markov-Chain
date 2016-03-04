
#include <fstream>
#include <vector>
#include <regex>
#include <stdlib.h>

#include "markov_chain.h"
#include "csv_parser.h"

Markov_Chain::Markov_Chain()
{
}

Markov_Chain::~Markov_Chain()
{
    Markov_Edge* current;
    Markov_Edge* next;
    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        current = ((Markov_State)iterator->second).edge_list;
        next = NULL;

        while (current != NULL)
        {
            next = current->next_edge;
            delete current;
            current = next;
        }
    }
}

void Markov_Chain::Add_Event(std::string last_event, std::string current_event)
{
    //If the map contains this state already, increase event count
    if (m_map.count(current_event))
    {
        m_map[current_event].num_events++;
    }
    else
    //Else create new state for this event
    {
        Markov_State new_state;
        new_state.num_events = 1;
        new_state.data = current_event;
        new_state.edge_list = NULL;

        m_map.insert(std::pair<std::string,Markov_State>(current_event,new_state));
    }

    //If the last event is not empty, update the edge that points to the current event
    if (last_event != "")
    {
        Markov_Edge* index = m_map[last_event].edge_list;

        if (index == NULL)
        {
            m_map[last_event].edge_list = new Markov_Edge;
            index = m_map[last_event].edge_list;
            index->event_rate = 1;
            index->next_state = &m_map[current_event];
            index->next_edge = NULL;
        }
        else
        {
            while (index->next_edge != NULL && index->next_state->data != current_event)
            {
                index = index->next_edge;
            }

            if (index->next_state->data != current_event)
            {
                index->next_edge = new Markov_Edge;
                index = index->next_edge;
                index->event_rate = 1;
                index->next_state = &m_map[current_event];
                index->next_edge = NULL;
            }
            else
            {
                index->event_rate++;
            }
        }
    }

}

void Markov_Chain::To_String ()
{
    Markov_State* state;
    Markov_Edge* edge;
    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        state = &iterator->second;
        edge = state->edge_list;
        std::cout<<"\nState: " <<  state->data
            <<"\nNum Events: " << state->num_events
            <<"\nNext States: [Frequency / Data]";

        while (edge != NULL)
        {
            std::cout <<"\n\t[" << edge->next_state->data << " / " << edge->event_rate << "]";
            edge = edge->next_edge;
        }

        std::cout << "\n";
    }
}

std::vector<std::string> Markov_Chain::Output_Random_Sequence (int output_size)
{
    srand (time(NULL));
    std::vector<std::string> retval;
    int count = 0;
    int val = rand() % m_map.size();
    
    auto item = m_map.begin();
    std::advance( item, val );
    Markov_State state = item->second; 
    Markov_Edge* edge = state.edge_list;

    while (count < output_size && edge != NULL)
    {
        retval.push_back(state.data);
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
    return retval;
}





