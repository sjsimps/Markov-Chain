
#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

template <class T> struct Markov_Edge;
template <class T> struct Markov_State;

template <class T>
class Markov_Chain
{
public:
    Markov_Chain();
    ~Markov_Chain();

    //Adds a sequence of events to the chain
    void Add_Event_Sequence(std::vector<T> data);

    //Adds event to chain with previous state information
    void Add_Event(T last_event, T current_event, unsigned int num_events = 1);

    //Adds a single node without a previous state
    void Add_Node(T current_event);

    //Outputs randomized state sequence
    std::vector<T> Output_Random_Sequence (int output_length);

    //Outputs current chain status to console
    void Print_To_Console();

    //Writes markov chain to [.dot] format for visualization
    //Each data element's string conversion must operate as a valid graphviz ID to operate properly
    void Export_To_Graphviz(std::string filename);

    //Every Markov state is indexed by m_map using a data element
    std::map<T,Markov_State<T>> m_map;

};

template <class T>
struct Markov_State
{
    T data;       //Data that corresponds to this state
    unsigned int num_events;//Number of times this state has occured given the input data
    Markov_Edge<T>* edge_list; //List containing all edges to a next possible state
};

template <class T>
struct Markov_Edge
{
    unsigned int event_rate; //Number of time this edge has been taken from previous state given the input data
    Markov_State<T>* next_state;//Next state corresponding to this edge
    Markov_Edge<T>* next_edge;  //Next edge within the edge list
};

////////// - MARKOV CHAIN IMPLEMENTATION - //////////

template <class T>
Markov_Chain<T>::Markov_Chain()
{
}

template <class T>
Markov_Chain<T>::~Markov_Chain()
{
    Markov_Edge<T>* current;
    Markov_Edge<T>* next;
    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        current = ((Markov_State<T>)iterator->second).edge_list;
        next = NULL;

        while (current != NULL)
        {
            next = current->next_edge;
            delete current;
            current = next;
        }
    }
}

//Insert new event with no edges
template <class T>
void Markov_Chain<T>::Add_Node(T current_event)
{
    if (m_map.count(current_event) == 0)
    {
        Markov_State<T> new_state;
        new_state.num_events = 0;
        new_state.data = current_event;
        new_state.edge_list = NULL;
        m_map.insert(std::pair<T,Markov_State<T>>(current_event,new_state));
    }
}

//Insert new event with an edge from the previous state:
// Last Event -> Current Event
template <class T>
void Markov_Chain<T>::Add_Event(T last_event, T current_event, unsigned int num_events)
{
    Add_Node(current_event);
    Add_Node(last_event);

    //Update the edge that points from the last to the current event
    m_map[last_event].num_events += num_events;
    Markov_Edge<T>* index = m_map[last_event].edge_list;

    if (index == NULL)
    {
        m_map[last_event].edge_list = new Markov_Edge<T>;
        index = m_map[last_event].edge_list;
        index->event_rate = num_events;
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
            index->next_edge = new Markov_Edge<T>;
            index = index->next_edge;
            index->event_rate = num_events;
            index->next_state = &m_map[current_event];
            index->next_edge = NULL;
        }
        else
        {
            index->event_rate += num_events;
        }
    }

}

template <class T>
void Markov_Chain<T>::Add_Event_Sequence(std::vector<T> data)
{
    Add_Node(data[0]);

    Markov_Edge<T>* index;
    Markov_State<T>* last_state;
    Markov_State<T>* current_state = &m_map[data[0]];

    for(unsigned int i = 1; i < data.size(); i++)
    {
        Add_Node(data[i]);

        last_state = current_state;
        current_state = &m_map[data[i]];

        //Update the edge that points from the last to the current event
        last_state->num_events += 1;
        index = last_state->edge_list;

        if (index == NULL)
        {
            last_state->edge_list = new Markov_Edge<T>;
            index = last_state->edge_list;
            index->event_rate = 1;
            index->next_state = current_state;
            index->next_edge = NULL;
        }
        else
        {
            while (index->next_edge != NULL && index->next_state->data != data[i])
            {
                index = index->next_edge;
            }

            if (index->next_state->data != data[i])
            {
                index->next_edge = new Markov_Edge<T>;
                index = index->next_edge;
                index->event_rate = 1;
                index->next_state = current_state;
                index->next_edge = NULL;
            }
            else
            {
                index->event_rate += 1;
            }
        }
    }
}

template <class T>
void Markov_Chain<T>::Print_To_Console ()
{
    Markov_State<T>* state;
    Markov_Edge<T>* edge;
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

template <class T>
std::vector<T> Markov_Chain<T>::Output_Random_Sequence (int output_size)
{
    srand (time(NULL));
    std::vector<T> retval;
    int count = 0;
    int val = rand() % m_map.size();

    auto item = m_map.begin();
    std::advance( item, val );
    Markov_State<T> state = item->second;
    Markov_Edge<T>* edge = state.edge_list;

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

template <class T>
void Markov_Chain<T>::Export_To_Graphviz(std::string filename)
{
    Markov_State<std::string> state;
    Markov_Edge<std::string>* edge;
    std::ofstream out(filename);
    int probability = 0;

    out << "\ndigraph markov_chain{";

    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        state = ((Markov_State<std::string>)iterator->second);
        out << "\n" <<  state.data << " [label=\"" << state.data << "\"];";
    }

    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        state = ((Markov_State<std::string>)iterator->second);
        edge  = state.edge_list;
        while (edge != NULL)
        {
            probability = (int)(100 * ((float)edge->event_rate) / ((float)state.num_events) );

            out << "\n" << state.data << " -> " << edge->next_state->data << " [label=\"" << probability << "\"];";
            edge = edge->next_edge;
        }
    }

    out << "\n}";
    out.close();
}

#endif
