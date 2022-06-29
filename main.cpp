#include  <string>
#include <rapidxml/rapidxml.hpp>
#include <iostream>


std::string text = R"(
<part number="1976">
  <name>Windscreen Wiper</name>
  <description>The Windscreen wiper
        automatically removes rain
        from your windscreen, if it
        should happen to splash there.
        It has a rubber <ref part="1977">blade</ref>
         which can be ordered separately
if you need to replace it.
</description>
</part>
)";

template< typename ch >
void display_node(const rapidxml::xml_node<ch>& node)
{
    std::cout << "Node name\t:" << node.name() << std::endl;
    std::cout << "\t type\t:" << node.type() << std::endl;
    std::cout << "\t parent\t:" << node.parent()->name() << std::endl;
    std::cout << "\t 1st attribute\t: " << (node.first_attribute()?node.first_attribute()->name():"----" ) << std::endl;
    std::cout << "\t last attribute\t: " << (node.last_attribute()?node.last_attribute()->name():"----" ) << std::endl;
    std::cout << "\t value\t:" << node.value() << std::endl;
    std::cout << "\t next sibl.\t:" << (node.next_sibling()? node.next_sibling()->name():"----")<< std::endl;
    std::cout << "\t prev sibl.\t:" << (node.previous_sibling()? node.previous_sibling()->name():"----")<< std::endl;

}

int main()
{
    using namespace rapidxml;
    std::cout << "Hello from xml parser playground!" << std::endl;
    xml_document<> doc;
    doc.parse<0>(&text[0]);
    std::cout << "First node is named: " <<  doc.first_node()->name();
    std::cout << "\nand contains text " <<  doc.first_node()->value();
    display_node(*doc.first_node());
    display_node(*doc.last_node());



    for( auto node = doc.first_node(); node != doc.last_node(); node = node->next_sibling() )
    {
        std::cout << node->name() << std::endl;
    }


    return 0;
}
