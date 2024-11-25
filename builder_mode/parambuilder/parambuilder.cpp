#include <string>
#include <functional>
#include <iostream>

using std::string;

class MailService {
    class Email {
        public:
            string from;
            string to;
            string subject;
            string body;
            // possibly other members here
    };

public:
    class EmailBuilder {
        Email& email;
    public:
        explicit EmailBuilder(Email& email) : email(email) {}

        EmailBuilder& from(const string& from) {
            email.from = from;
            return *this;
        }

        EmailBuilder& to(const string& to) {
            email.to = to;
            return *this;
        }

        EmailBuilder& subject(const string& subject) {
            email.subject = subject;
            return *this;
        }

        EmailBuilder& body(const string& body) {
            email.body = body;
            return *this;
        }
    };

    void send_email(std::function<void(EmailBuilder&)> builder) {
        Email email;
        EmailBuilder eb(email);
        builder(eb);
        send_email_impl(email);
    }
private:
    void send_email_impl(const Email& email) {
        std::cout << "Sending email from " 
            << email.from << " to " << email.to 
            << " with subject " << email.subject 
            << " and body " << email.body << std::endl;
    }
};

int main() {
    MailService ms;
    ms.send_email([](MailService::EmailBuilder& eb) {
        eb.from("Alice").to("Bob").subject("Hello").body("Hi there!");
    });
}