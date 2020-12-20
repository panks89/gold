#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include "ElementBuilder.h"

class ElementBuilder;
class Element {
    std::string name;
    std::string tag;
    int value;
    Element() = default;
public:
    static ElementBuilder BUILDER();

    friend std::ostream& operator<<(std::ostream& os, const Element& obj)
    {
        return os
            << "Name: " << obj.name << std::endl
            << "Tag : " << obj.tag << std::endl
            << "Value: " << obj.value << std::endl;
    }

    friend class ElementBuilder;
};
#endif /* ELEMENT_H */
