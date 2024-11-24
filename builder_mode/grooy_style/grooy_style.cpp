#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <utility>

using std::string;
using std::vector;
using std::pair;
using std::ostream;

struct Tag {
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend ostream& operator<<(ostream& os, const Tag& tag) {
        os << "name: " << tag.name << " text: " << tag.text << '\n';
        return os;
    }

protected:
    Tag(const string& name, const string& text) : name(name), text(text) {}
    Tag(const string& name, const vector<Tag>& children) : name(name), children(children) {}
};

struct P : Tag {
    explicit P(const string& text) : Tag("P", text) {}

    P(std::initializer_list<Tag> children) : Tag("P", children) {
        std::cout << "test." << '\n';
    }
};

struct IMG : Tag {
    explicit IMG(const string& url) : Tag("IMG", "") {
        attributes.emplace_back("src", url);
    }
};

int main() {
    std::cout << P{IMG{"http://baidu.com"}} << '\n';

    P p{IMG{"http://baidu.com"}};
    std::cout << p << '\n';

    return 0;
}