
#include <string>
#include <vector>

#ifndef CSV_PARSER_H
#define CSV_PARSER_H

class CSV_Parser
{
public:
    CSV_Parser();
    ~CSV_Parser();

    std::string Get_Entry(int i);
    void Set_Data(std::string filename);
    int m_size;

private:
    void Handle_Quotes(std::string* str);
    std::vector<std::string> m_data;
    std::string m_filename;
};

#endif
