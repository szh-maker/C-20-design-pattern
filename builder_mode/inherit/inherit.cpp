#include <string>
#include <iostream>

using std::string;
using std::ostream;

namespace InheritanceOfConstructor {
    class Person {
    public:
        string name;
        string position;
        string date_of_birth;

        friend ostream& operator<<(std::ostream& os, const Person& obj) {
            return os
                << "name: " << obj.name
                << "\nposition: " << obj.position
                << "\ndate_of_birth: " << obj.date_of_birth << '\n';
        }
    };

    class PersonBuilder {
    protected:
        Person person;

    public:
        [[nodiscard]] Person build() const {
            return person;
        }
    };

    template<typename TSelf>
    class PersonInfoBuilder : public PersonBuilder {
    public:
        TSelf& called(const string& name) {
            this->person.name = name;
            return static_cast<TSelf&>(*this);
        }    
    };

    template<typename TSelf>
    class PersonJobBuilder : public PersonInfoBuilder<PersonJobBuilder<TSelf>> {
    public:
        TSelf& works_as(const string& position) {
            this->person.position = position;
            return static_cast<TSelf&>(*this);
        }
    };

    template<typename TSelf>
    class PersonDateOfBirthBuilder : public PersonJobBuilder<PersonDateOfBirthBuilder<TSelf>> {
    public:
        TSelf& born_on(const string& date_of_birth) {
            this->person.date_of_birth = date_of_birth;
            return static_cast<TSelf&>(*this);
        }
    };

    class MyBuilder : public PersonDateOfBirthBuilder<MyBuilder> {};
}

int main() {
    using namespace InheritanceOfConstructor;
    MyBuilder builder;
    auto me = builder
       .called("John")
       .works_as("C++ Developer")
       .born_on("1990-01-01")
       .build();
    std::cout << me << '\n';
}