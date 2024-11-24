#include <memory>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::unique_ptr;

struct HtmlBuilder;

struct HtmlElement {
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;
    friend HtmlBuilder;

    static unique_ptr<HtmlBuilder> create(const string& root_name) {
        return std::make_unique<HtmlBuilder>(root_name);
    }
    string str(int indent = 0) const {
        if(elements.empty()) {
            return "<" + name + "> " + text + " </" + name + ">";
        }
        string res;
        res += "<" + name + ">" + text;
        for(auto e : elements) {
            res += e.str();
        }
        res += "</" + name + ">";
        return res;
    }
protected:
    HtmlElement() {}
    HtmlElement(const string& name, const string& text) : name(name), text(text) {}
};

struct HtmlBuilder {
    HtmlElement root;
    
    operator HtmlElement() const {
        return root;
    }

    HtmlElement build() const {
        return root;
    }

    HtmlBuilder(string root_name) {
        root.name = root_name;
    }

    HtmlBuilder& add_child(string child_name, string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    string str() {
        return root.str();
    }
};

int main() {
    auto builder = HtmlElement::create("ul");
    builder->add_child("li", "hello world")
           .add_child("li", "user to api");
    std::cout << builder->str() << std::endl;
}