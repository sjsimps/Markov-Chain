
#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

template <class T> struct Markov_Event;
template <class T> struct Markov_Node;

template <class T>
class Markov_Chain
{
public:
    Markov_Chain();
    ~Markov_Chain();

    //Adds a single node without any events
    void Add_Node(T node);

    //Adds a sequence of events to the chain through a vector of nodes
    void Add_Event_Sequence(std::vector<T> node_sequence);

    //Adds event to chain from the last_node to next_node
    //num_events determines the weight of the event
    void Add_Event(T last_node, T next_node, unsigned int num_events = 1);

    //Removes all events between two nodes
    void Remove_Event(T last_node, T next_node);

    //Returns the probability of transitioning from last_node to next_node
    float Get_Probability(T last_node, T next_node);

    //Outputs randomized node sequence
    std::vector<T> Output_Random_Sequence (int output_length, T start_node, bool random_start);

    //Outputs current chain status to console
    void Print_To_Console();

    //Writes markov chain to [.dot] format for visualization
    //Each data element's string conversion must operate as a valid graphviz ID to operate properly
    void Export_To_Graphviz(std::string filename);

    //Every Markov node is indexed by m_map using a data element
    std::map<T,Markov_Node<T>> m_map;

};

template <class T>
struct Markov_Node
{
    T data;
    unsigned int num_events;
    Markov_Event<T>* event_list;
};

template <class T>
struct Markov_Event
{
    unsigned int event_rate;
    Markov_Node<T>* next_node;
    Markov_Event<T>* next_event;
};

////////// - MARKOV CHAIN IMPLEMENTATION - //////////

template <class T>
Markov_Chain<T>::Markov_Chain()
{
}

template <class T>
Markov_Chain<T>::~Markov_Chain()
{
    Markov_Event<T>* current;
    Markov_Event<T>* next;
    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        current = ((Markov_Node<T>)iterator->second).event_list;
        next = NULL;

        while (current != NULL)
        {
            next = current->next_event;
            delete current;
            current = next;
        }
    }
}

//Insert new event with no events
template <class T>
void Markov_Chain<T>::Add_Node(T node)
{
    if (m_map.count(node) == 0)
    {
        Markov_Node<T> new_node;
        new_node.num_events = 0;
        new_node.data = node;
        new_node.event_list = NULL;
        m_map.insert(std::pair<T,Markov_Node<T>>(node,new_node));
    }
}

//Insert new event with an event from the previous node:
// Last Event -> Current Event
template <class T>
void Markov_Chain<T>::Add_Event(T last_node, T next_node, unsigned int num_events)
{
    Add_Node(next_node);
    Add_Node(last_node);

    //Update the event that points from the last to the current event
    m_map[last_node].num_events += num_events;
    Markov_Event<T>* index = m_map[last_node].event_list;

    if (index == NULL)
    {
        m_map[last_node].event_list = new Markov_Event<T>;
        index = m_map[last_node].event_list;
        index->event_rate = num_events;
        index->next_node = &m_map[next_node];
        index->next_event = NULL;
    }
    else
    {
        while (index->next_event != NULL && index->next_node->data != next_node)
        {
            index = index->next_event;
        }

        if (index->next_node->data != next_node)
        {
            index->next_event = new Markov_Event<T>;
            index = index->next_event;
            index->event_rate = num_events;
            index->next_node = &m_map[next_node];
            index->next_event = NULL;
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

    Markov_Event<T>* index;
    Markov_Node<T>* last_node;
    Markov_Node<T>* current_node = &m_map[data[0]];

    for(unsigned int i = 1; i < data.size(); i++)
    {
        Add_Node(data[i]);

        last_node = current_node;
        current_node = &m_map[data[i]];

        //Update the event that points from the last to the current event
        last_node->num_events += 1;
        index = last_node->event_list;

        if (index == NULL)
        {
            last_node->event_list = new Markov_Event<T>;
            index = last_node->event_list;
            index->event_rate = 1;
            index->next_node = current_node;
            index->next_event = NULL;
        }
        else
        {
            while (index->next_event != NULL && index->next_node->data != data[i])
            {
                index = index->next_event;
            }

            if (index->next_node->data != data[i])
            {
                index->next_event = new Markov_Event<T>;
                index = index->next_event;
                index->event_rate = 1;
                index->next_node = current_node;
                index->next_event = NULL;
            }
            else
            {
                index->event_rate += 1;
            }
        }
    }
}

template <class T>
void Markov_Chain<T>::Remove_Event(T last_node, T next_node)
{
    if (m_map.count(next_node) && m_map.count(last_node))
    {
        Markov_Node<T>* node = &m_map[last_node];
        Markov_Event<T>** index = &node->event_list;

        if ((*index) != NULL)
        {
            while ((*index)->next_event != NULL && (*index)->next_node->data != next_node)
            {
                index = &(*index)->next_event;
            }

            if ((*index) != NULL)
            {
                node->num_events -= (*index)->event_rate;
                Markov_Event<T>* todelete = *index;
                *index = (*index)->next_event;
                delete todelete;
            }
        }
    }
}

template <class T>
float Markov_Chain<T>::Get_Probability(T last_node, T next_node)
{
    Markov_Node<T>* node = &m_map[last_node];
    Markov_Event<T>* index = node->event_list;

    if (m_map.count(last_node) && m_map.count(next_node))
    {
        while (index != NULL && index->next_node->data != next_node)
        {
            index = index->next_event;
        }

        if ((index != NULL) && (node->num_events > 0))
        {
            return ((float)index->event_rate) / ((float)node->num_events);
        }
    }
    return 0;
}

template <class T>
void Markov_Chain<T>::Print_To_Console ()
{
    Markov_Node<T>* node;
    Markov_Event<T>* event;

    std::cout<<"\nFormat:\t\t[Node / #Events]\n";
    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        node = &iterator->second;
        event = node->event_list;
        std::cout<<"\nCurrent Node:\t[" <<  node->data << " / " << node->num_events << "]"
            <<"\nNext Nodes:";

        if (event != NULL)
        {
            std::cout <<"\t[" << event->next_node->data << " / " << event->event_rate << "]";
            event = event->next_event;
            while (event != NULL)
            {
                std::cout <<"\n\t\t[" << event->next_node->data << " / " << event->event_rate << "]";
                event = event->next_event;
            }
        }

        std::cout << "\n";
    }
}

template <class T>
std::vector<T> Markov_Chain<T>::Output_Random_Sequence (int output_size, T start_node, bool random_start)
{
    srand (time(NULL));
    std::vector<T> retval;
    int count = 0;
    int val;
    Markov_Node<T> node;
    Markov_Event<T>* event;

    if (random_start)
    {
        auto item = m_map.begin();
        val = rand() % m_map.size();
        std::advance( item, val );
        node = item->second;
    }
    else if (m_map.count(start_node) != 0)
    {
        node = m_map[start_node];
    }
    else
    {
        std::cout << "\nOutput_Random_Sequence : Markov chain does not contain specified start node\n";
        exit(EXIT_FAILURE);
    }

    event = node.event_list;

    while (count < output_size && event != NULL)
    {
        retval.push_back(node.data);
        val = rand() % node.num_events;
        while(val >= 0 && event->next_event != NULL)
        {
            val -= event->event_rate;
            if (val >= 0) event = event->next_event;
        }
        node = *event->next_node;
        event = node.event_list;
        count++;
    }
    return retval;
}

template <class T>
void Markov_Chain<T>::Export_To_Graphviz(std::string filename)
{
    Markov_Node<T> node;
    Markov_Event<T>* event;
    std::ofstream out(filename);
    int probability = 0;

    out << "\ndigraph markov_chain{";

    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        node = ((Markov_Node<T>)iterator->second);
        out << "\n_" <<  node.data << " [label=\"" << node.data << "\"];";
    }

    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        node = ((Markov_Node<T>)iterator->second);
        event  = node.event_list;
        while (event != NULL)
        {
            probability = (node.num_events == 0) ?
                0 : (int)(100 * ((float)event->event_rate) / ((float)node.num_events) );

            out << "\n_" << node.data << " -> _" << event->next_node->data << " [label=\"" << probability << "\"];";
            event = event->next_event;
        }
    }

    out << "\n}";
    out.close();
}

#endif
