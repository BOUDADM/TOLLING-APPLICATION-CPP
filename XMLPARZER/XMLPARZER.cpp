#include <iostream>
#include <string>
#include <vector>

struct XmlNode {
    std::string name;
    std::vector<XmlNode> children;
    std::string content;
};

void parseXml(const std::string& xml, size_t& pos, XmlNode& node) {
    size_t startTag = xml.find('<', pos);
    if (startTag == std::string::npos) {
        return; // No more tags found
    }

    startTag++;

    if (xml[startTag] == '/') {
        return; // Closing tag, go back
    }

    size_t endTagName = xml.find_first_of(" \t\n>/", startTag);
    node.name = xml.substr(startTag, endTagName - startTag);

    size_t endTag = xml.find('>', startTag);
    if (endTag == std::string::npos) {
        return; // Malformed XML
    }

    pos = endTag + 1;

    size_t endTagPos = xml.find("</" + node.name + ">", pos);
    if (endTagPos == std::string::npos) {
        return; // Malformed XML
    }

    node.content = xml.substr(pos, endTagPos - pos);

    pos = endTagPos + node.name.size() + 3;

    while (true) {
        XmlNode child;
        parseXml(xml, pos, child);
        if (child.name.empty()) {
            break; // No more children
        }
        node.children.push_back(child);
    }
}


void printXml(const XmlNode& node, int depth = 0) {
    for (int i = 0; i < depth; ++i) {
        std::cout << "  "; // Indent
    }
    std::cout << node.name;
    if (!node.content.empty()) {
        std::cout << ": " << node.content;
    }
    std::cout << std::endl;

    // Print children recursively
    for (const auto& child : node.children) {
        printXml(child, depth + 1);
    }
}

