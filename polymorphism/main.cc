/**
 *  Runtime-concept idiom example
 * =======
 * This idiom provides runtime polymorphism without inheritance, which makes it ideal to implement
 * libraries that uses some user-supplied type to do some operation. In this example we create an
 * "document" that can contain any type, and draw it as long as custom behaviour is implemented
 * for custom classes as plain functions.
 * 
 * The object_t does also implement the rule of five for performance reasons (less copying).
 */
#include <iostream>
#include <vector>
#include <memory>


/**
 * The default draw function
 */
template<typename T>
void draw(const T& x, std::ostream &out, size_t position) {
    out << std::string(position, ' ') << x << std::endl;
}

/**
 * wrapper that makes the polymorphism possible
 */
class object_t {
    public:
        template<typename T>
        object_t(T x) : self_(std::make_unique<model_t<T>>(std::move(x))) {}

        object_t(const object_t &other) : self_(other.self_->copy_()) {}
        object_t(object_t && other) noexcept = default;

        object_t &operator=(const object_t &other) noexcept {
            return (*this = object_t(other));
        }
        object_t &operator=(object_t &&other) noexcept = default;


        friend void draw(const object_t& x, std::ostream& out, size_t position) {
            x.self_->draw_(out, position);
        }

    private:
        struct concept_t {
            virtual ~concept_t() = default;
            virtual void draw_(std::ostream &, size_t) const = 0;
            virtual std::unique_ptr<concept_t> copy_() const = 0;
        };

        template<typename T>
        struct model_t final : concept_t {
            model_t(T x) : data_(std::move(x)) {}

            void draw_(std::ostream &out, size_t position) const override {
                draw(data_, out, position);
            }

            std::unique_ptr<concept_t> copy_() const override {
                return std::make_unique<model_t<T>>(*this);
            }

            T data_;
        };

        std::unique_ptr<concept_t> self_;
};


using document_t = std::vector<object_t>;

/**
 * Specific draw implementation for document_t type
 */
void draw(const document_t& x, std::ostream &out, size_t position) {
    out << std::string(position, ' ') << "<document>" << std::endl;
    for (const auto & element : x) draw(element, out, position + 2);
    out << std::string(position, ' ') << "</document>" << std::endl;
}

class my_class_t  {
};

/**
 * Specific draw implementation for some custom type
 */
void draw(const my_class_t&, std::ostream& out, size_t position) {
    out << std::string(position, ' ') << "my_class_t" << std::endl;
}

int main() {

    document_t doc;

    doc.push_back(23);
    doc.push_back(std::string("Hello world!"));
    doc.push_back(42);
    doc.push_back(my_class_t());

    draw(doc, std::cout, 0);

    return 0;
}