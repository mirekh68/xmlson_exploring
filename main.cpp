#include  <string>
#include <iostream>
#include <iomanip>

#include <rapidxml/rapidxml.hpp>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <nlohmann/json.hpp>
using nljson = nlohmann::json;

using namespace rapidjson;


std::string operator*(const std::string& str, int n)
{
    std::string res{str};
    for( int i =0; i < n -1; ++i)
    {
        res += str;
    }
    return  res;
}

std::string dash("-");

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

    std::cout << "\n-------------------\nNow Json :\n" ;
    // rapidjson/example/simpledom/simpledom.cpp`


    // 1. Parse a JSON string into DOM.
//    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    const char* json = R"(
    {
        "project":"rapidjson",
        "stars":10
    }
    )";

    std::string js1 = R"RawString(
    {
        "pi": 3.141,
                "happy": true,
                "name": "Boost",
                "nothing": null,
                "answer": {
            "everything": 42
        },
        "list": [1, 0, 2],
        "object": {
            "currency": "USD",
                    "value": 42.99
        }
    }
    )RawString";


    std::string js = R"RawString(
    {"pi":3.141,"happy":true,"name":"Boost","nothing":null,"answer":{"everything":42},
        "list": [1, 0, 2],
        "object": {
            "currency": "USD",
                    "value": 42.99
        }
    }
    )RawString";

    Document d;
    d.Parse(js.c_str());

    // 2. Modify it by DOM.
    Value& s = d["list"];
    //s.SetInt(s.GetInt() + 1);
    auto arr = s.GetArray();
    //auto  i = s.Get<double>();

    //std::cout << i << std::endl;
    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    for( int i = 0; i < 20; ++i)
        s.PushBack(Value().SetInt(i), d.GetAllocator());
    //s.Set(arr);
    d.Accept(writer);

    for( const auto &i : arr)
    {
        std::cout << i.GetInt() << " ";
    }
    // Output {"project":"rapidjson","stars":11}
    std::cout << "\n\n";
    std::cout << buffer.GetString() << std::endl;


    nljson j
            {
                    {"pi", 3.141},
                    {
                     "answer", {"everything", 42}
                    },
                    {"list", {1, 0, 2}},
            };

    // add new values
    j["new"]["key"]["value"] = {"another", "list"};

    // count elements
    auto sz = j.size();
    j["size"] = sz;


    std::cout << dash*30 << '\n' << "nlohmann json\n" << dash*30 << '\n' ;


    // pretty print with indent of 4 spaces
    std::cout << std::setw(4) << j << '\n';



    return 0;
}
