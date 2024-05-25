#include <iostream>
#include <string>
#include <vector>

// Define a structure to represent XML nodes
struct XmlNode {
    std::string name;
    std::vector<XmlNode> children;
    std::string content;
};

// Function to parse XML recursively
void parseXml(const std::string& xml, size_t& pos, XmlNode& node) {
    // Find the start tag
    size_t startTag = xml.find('<', pos);
    if (startTag == std::string::npos) {
        return; // No more tags found
    }

    // Skip the '<'
    startTag++;

    // Check if it's a closing tag
    if (xml[startTag] == '/') {
        return; // Closing tag, go back
    }

    // Extract the tag name
    size_t endTagName = xml.find_first_of(" \t\n>/", startTag);
    node.name = xml.substr(startTag, endTagName - startTag);

    // Move to the end of the start tag
    size_t endTag = xml.find('>', startTag);
    if (endTag == std::string::npos) {
        return; // Malformed XML
    }

    // Move to the content after the start tag
    pos = endTag + 1;

    // Find the end tag
    size_t endTagPos = xml.find("</" + node.name + ">", pos);
    if (endTagPos == std::string::npos) {
        return; // Malformed XML
    }

    // Extract the content between the tags
    node.content = xml.substr(pos, endTagPos - pos);

    // Move to the end of the end tag
    pos = endTagPos + node.name.size() + 3;

    // Recursively parse children
    while (true) {
        XmlNode child;
        parseXml(xml, pos, child);
        if (child.name.empty()) {
            break; // No more children
        }
        node.children.push_back(child);
    }
}


// Function to print XML recursively
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

int main() {
    // Example XML input
    std::string xmlInput = R"(
<ECUData>
    <ECU id="1">
        <Name>Engine Control Unit</Name>
        <Temperature>85</Temperature>
        <FuelLevel>2</FuelLevel>
    </ECU>
    <ECU id="2">
        <Name>Transmission Control Unit</Name>
        <Temperature>70</Temperature>
        <OilPressure>40</OilPressure>
    </ECU>
</ECUData>
)";

    // Initialize pos to 0
    size_t pos = 0;

    // Parse XML
    XmlNode root;
    parseXml(xmlInput, pos, root);

}
