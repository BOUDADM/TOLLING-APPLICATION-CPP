#include <iostream>
#include <string>
#include "XMLPARZER.h"

/*void printXMLNode(const XMLNode& node, int indent = 0) {
    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
    std::cout << "Node: " << node.name << std::endl;

    for (const auto& attr : node.attributes) {
        for (int i = 0; i < indent + 1; ++i) {
            std::cout << "  ";
        }
        std::cout << "Attribute: " << attr.first << " = " << attr.second << std::endl;
    }

    if (!node.value.empty()) {
        for (int i = 0; i < indent + 1; ++i) {
            std::cout << "  ";
        }
        std::cout << "Value: " << node.value << std::endl;
    }

    for (const auto& child : node.children) {
        printXMLNode(child, indent + 1);
    }
}

int main() {
    std::cout << "Enter the XML input:" << std::endl;
    std::string xmlInput;
    std::getline(std::cin, xmlInput);

    XMLNode rootNode = XMLParser::parse(xmlInput);

    std::cout << "Parsed XML Data:" << std::endl;
    printXMLNode(rootNode);

    return 0;
}
