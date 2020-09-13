#include <iostream>
#include "Element.h"
#include "ElementBuilder.h"

int main() {
    /*
      Traditional Builder pattern - BAD
      It's suffered with cyclic dependencies
    */
    auto a = Element::BUILDER()
        .Name("Pankaj")
        .Tag("CSE")
        .Value(9).build();
    std::cout << a << std::endl;
    
}
