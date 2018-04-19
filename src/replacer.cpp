
#include "replacer.h"

cReplacer::cReplacer(std::string text):
    m_text(text)
{

}


cReplacer::~cReplacer()
{

}


std::string cReplacer::print_text()
{
    std::cout << m_text << std::endl;
    return m_text;
}


int main()
{
    cReplacer my_replacer("hallo du");
    my_replacer.print_text();
    return 0;
}
