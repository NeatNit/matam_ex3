#ifndef MTMPARKINGLOT_UNIQUEARRAYIMP_H
#define MTMPARKINGLOT_UNIQUEARRAYIMP_H

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :
    data(new Element*[size]()), size(size) {}

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other) :
    data(new Element*[other.size]()), size(other.size)
{
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
    delete[] data;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element) {
    unsigned int first_empty_index = size;
    Compare equal;
    for (unsigned int i = 0; i < size; ++i) {
        if (data[i] && equal(*data[i], element)) {
            return i; // element already in array
        }

        if (i < first_empty_index && !data[i]) {
            first_empty_index = i;
        }
    }

    if (first_empty_index >= size) {
        throw UniqueArray<Element,Compare>::UniqueArrayIsFullException();
    }

    data[first_empty_index] = new Element(element);
    return first_empty_index;
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element,
    unsigned int& index) const
{
    Compare equal;
    for (unsigned int i = 0; i < size; ++i) {
        if (data[i] && equal(*data[i], element)) {
            index = i;
            return true;
        }
    }
    return false;
}

template <class Element, class Compare>
const Element* UniqueArray<Element, Compare>::operator[](
    const Element& element) const
{
    Compare equal;
    for (unsigned int i = 0; i < size; ++i) {
        if (data[i] && equal(*data[i], element)) {
            return data[i];
        }
    }
    return NULL;
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element& element) {
    Compare equal;
    for (unsigned int i = 0; i < size; ++i) {
        if (data[i] && equal(*data[i], element)) {
            delete data[i];
            data[i] = NULL;
            return true;
        }
    }
    return false;
}

#endif //MTMPARKINGLOT_UNIQUEARRAYIMP_H
