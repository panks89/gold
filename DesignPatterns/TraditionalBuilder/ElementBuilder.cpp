#include "Element.h"
#include "ElementBuilder.h"

ElementBuilder::ElementBuilder()
    : elemPtr { new Element{} } {
}

ElementBuilder& ElementBuilder::Name(const std::string & name) {
    elemPtr->name = name;
    return *this;
}
    
ElementBuilder& ElementBuilder::Tag(const std::string & tag) {
    elemPtr->tag = tag;
    return *this;
}
    
ElementBuilder& ElementBuilder::Value(const int value) {
    elemPtr->value = value;
    return *this;
}

Element ElementBuilder::build() {
    return std::move(*elemPtr);
}

