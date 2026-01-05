#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct HtmlElement {
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;
    HtmlElement(const std::string& name, const std::string& text) : name(name), text(text) {}
    std::string str(int indent = 0) const {
        std::ostringstream oss;
        oss << std::string(indent, ' ') << "<" << name << ">" << std::endl;
        if (text.size() > 0)
            oss << std::string(indent + 1, ' ') << text << std::endl;
        for (const HtmlElement& e : elements)
            oss << e.str(indent + 1);
        oss << std::string(indent, ' ') << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

struct HtmlSimpleBuilder {
    HtmlElement root;
    HtmlSimpleBuilder(const std::string& name, const std::string& text) : root(name, text) {}
    void add_child(const std::string& name, const std::string& text) {
        root.elements.emplace_back(name, text);
    }
};

struct HtmlFluentBuilder {
    HtmlElement root;

    HtmlFluentBuilder(const std::string& name, const std::string& text) : root(name, text) {}
    HtmlFluentBuilder& add_child(const std::string& name, const std::string& text) {
        root.elements.emplace_back(name, text);
        return *this;
    }
};

int main() {
    HtmlSimpleBuilder builder("ul", "");
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    std::cout << builder.root.str() << std::endl;

    HtmlFluentBuilder builder2("ul", "");
    builder2.add_child("li", "hello").add_child("li", "world");
    std::cout << builder2.root.str() << std::endl;
}