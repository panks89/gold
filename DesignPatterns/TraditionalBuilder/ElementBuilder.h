#ifndef ELEMENTBUILDER_H
#define ELEMENTBUILDER_H

#include <memory>
#include "Element.h"

class Element;
class ElementBuilder {
    std::unique_ptr<Element> elemPtr;
public:
    ElementBuilder& Name(const std::string & name);
    
    ElementBuilder& Tag(const std::string & tag);
    
    ElementBuilder& Value(const int value);

    Element build();

    ElementBuilder();
};

#endif /* ELEMENTBUILDER_H */
