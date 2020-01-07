#ifndef MTMPARKINGLOT_UNIQUEARRAYIMP_H
#define MTMPARKINGLOT_UNIQUEARRAYIMP_H

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :
    data(new Element*[size]), size(size) {
}

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(
    const UniqueArray<Element, Compare>& other ) :
    data(new Element*[other.size]), size(other.size) {
    for (unsigned int i = 0; i < size; ++i) {
        if (other.data[i]) {
            data[i] = new Element(*other.data[i]);
        }
    }
}

template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
    for (unsigned int i = 0; i < size; ++i) {
        if (data[i]) {
            delete data[i];
        }
    }
}

#endif //MTMPARKINGLOT_UNIQUEARRAYIMP_H
