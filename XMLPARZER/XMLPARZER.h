#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <string>
#include <vector>
#include <stack>

struct XMLNode {
    std::string name;
    std::string value;
    std::vector<std::pair<std::string, std::string>> attributes;
    std::vector<XMLNode> children;
};

class XMLParser {
public:
    static XMLNode parse(const std::string& xmlInput);

private:
    static void parseStartTag(const std::string& tag, XMLNode& node);
    static std::string trim(const std::string& str);
};

#endif // XML_PARSER_HPP
