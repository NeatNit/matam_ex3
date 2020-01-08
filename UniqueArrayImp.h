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
    unsigned int index;
    if (getIndex(element, index)) {
        return index;
    }
    // else - new element:
    for (unsigned int i = 0; i < size; ++i) {
        if (!data[i]) {
            data[i] = new Element(element);
            return i;
        }
    }

    throw UniqueArray::UniqueArrayIsFullException();
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
    unsigned int index;
    if (getIndex(element, index)) {
        return data[index];
    }
    return NULL;
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element& element) {
    unsigned int index;
    if (getIndex(element, index)) {
        delete data[index];
        data[index] = NULL;
        return true;
    }
    return false;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    // Possible optimization: keep the current count as a private member and
    // update it on insert/remove, then just return it here to get O(1).
    unsigned int count = 0;
    for (unsigned int i = 0; i < size; ++i)
    {
        if (data[i]) ++count;
    }
    return count;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
    return size;
}

template <class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter(
    const Filter& f ) const
{
    // first copy everything
    UniqueArray filtered_array = UniqueArray(*this);

    // then delete the unwanted stuff
    for (unsigned int i = 0; i < size; ++i)
    {
        if (data[i] && !f(*data[i])){
            filtered_array.remove(*data[i]);
        }
    }
    return filtered_array;
}

#endif //MTMPARKINGLOT_UNIQUEARRAYIMP_H
