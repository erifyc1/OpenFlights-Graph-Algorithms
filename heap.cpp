#include "heap.h"
template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return floor(currentIdx / 2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return rightChild(currentIdx) < _elems.size() || leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    if (right >= _elems.size() || higherPriority(_elems[left], _elems[right])) {
        return left;
    }
    return right;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (!hasAChild(currentIdx)) return;
    size_t priority = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[priority], _elems[currentIdx])) {
    	std::swap(_elems[priority], _elems[currentIdx]);
    	heapifyDown(priority);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    _elems.push_back(T());

    for (const T& t : elems) {
    	_elems.push_back(t);
    }

    for (size_t idx = _elems.size() - 1; idx > 0; idx--) {
    	heapifyDown(idx);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (_elems.size() == root()) return T();

    T root_ = _elems[root()];
    std::swap(_elems[root()], _elems.back());
    _elems.pop_back();
    heapifyDown(root());
    return root_;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}   

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    _elems[idx] = elem;
    if (higherPriority(elem, _elems[parent(idx)])) {
    	heapifyUp(idx);
    }
    else {
        heapifyDown(idx);  
    }  
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.size() == root();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
