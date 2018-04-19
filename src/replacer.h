
#include<iostream>


class cReplacer
{
private:
    std::string m_text;

public:
    cReplacer(std::string);
    ~cReplacer();

    std::string print_text();
};
