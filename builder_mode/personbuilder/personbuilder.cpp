#include <string>

using std::string;

class PersonBuilderBase;
class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

class Person {
    // address
    string street_address;
    string post_code;
    string city;

    // employment
    string company_name;
    string position;
    int annual_income = 0;

    Person() {}

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
public:
    static PersonBuilder create();
};

class PersonBuilderBase {
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person) : person(person) {}
public:
    operator Person() const { return std::move(person); }
    // builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase {
public:
    explicit PersonBuilder() : PersonBuilderBase(person) {}
protected:
    Person person;
};

class PersonAddressBuilder : public PersonBuilderBase {
    using self = PersonAddressBuilder;
public: 
    PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

    self& at(string street_address) {
        person.street_address = street_address;
        return *this;
    }

    self& with_postcode(string post_code) {
        person.post_code = post_code;
        return *this;
    }

    self& in(string city) {
        person.city = city;
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase {
    using self = PersonJobBuilder;

public:
    PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

    self& at(string company_name) {
        person.company_name = company_name;
        return *this;
    }

    self& as_a(string position) {
        person.position = position;
        return *this;
    }

    self& earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

PersonBuilder Person::create() {
    return PersonBuilder();
}

PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder(person);
}

int main() {
    Person p = Person::create()
       .lives().at("123 London Road").in("London").with_postcode("SW1 1GB")
       .works().at("PragmaSoft").as_a("Consultant").earning(10e6);
    return 0;
}