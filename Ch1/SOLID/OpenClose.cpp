#include <iostream>
#include <vector>
#include <string>

enum class Size {
    Small,
    Medium,
    Large,
};

enum class Color {
    Red,
    Green,
    Blue,
    Yellow,
};

struct Product {
    std::string name;
    Size size;
    Color color;
    Product(std::string name, Size size, Color color) : 
        name(name), 
        size(size), 
        color(color) {}
};

/* INSTEAD OF ADDING A FILTER FUNCTION WE USE OPEN/CLOSE PRINCIPLE */
template <typename Type>
struct Specification {
    bool is_satisfied(Product& item)
    {
        return static_cast<Type*>(this)->is_valid(item);
    }
};

struct Filter {
    template <typename Type>
    std::vector<Product> filter(std::vector<Product> products, Specification<Type>& spec) {
        std::vector<Product> result;
        for (Product& p : products) {
            if (spec.is_satisfied(p)) {
                result.push_back(p);
            }
        }
        return result;
    }
};



struct ColorSpecification : Specification<ColorSpecification> {
    Color color;
    ColorSpecification(Color color) : color(color) {}
    bool is_valid(Product& item) {
        return item.color == color;
    }
};

struct SizeSpecification : Specification<SizeSpecification> {
    Size size;
    SizeSpecification(Size size) : size(size) {}
    bool is_valid(Product& item) {
        return item.size == size;
    }
};

int main() {
    Product apple("Apple", Size::Small, Color::Red);
    Product banana("Banana", Size::Medium, Color::Yellow);
    Product cherry("Cherry", Size::Large, Color::Red);
    std::vector<Product> products = {apple, banana, cherry};
    Filter filter;
    ColorSpecification red_spec(Color::Red);
    std::vector<Product> red_products = filter.filter(products, red_spec);
    for (Product& p : red_products) {
        std::cout << p.name << std::endl;
    }
}