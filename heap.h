#pragma once

#include "utils.h"
#include <cmath>

template <class T, class Compare = std::less<T>>
class heap
{
  public:
    // creates empty heap
    heap() {
        _elems.push_back(T());
    }
    
    // creates heap from vector
    heap(const std::vector<T>& elems) {
        _elems.push_back(T());

        for (const T& t : elems) {
          _elems.push_back(t);
        }

        for (size_t idx = _elems.size() - 1; idx > 0; idx--) {
          heapifyDown(idx);
        }
    }

    // returns root position of heap
    size_t root() const {
        return 1;
    }

    // returns next element in heap, removing it from the heap
    T pop() {
        if (_elems.size() == root()) return T();

        T root_ = _elems[root()];
        std::swap(_elems[root()], _elems.back());
        _elems.pop_back();
        heapifyDown(root());
        return root_;
    }

    // returns next element in heap, without removing it from the heap
    T peek() const {
        return _elems[root()];
    }

    // adds element to heap
    void push(const T& elem) {
        _elems.push_back(elem);
        heapifyUp(_elems.size() - 1);
    }   

    // changes elem at idx to new element
    void updateElem(const size_t & idx, const T& elem) {
        _elems[idx] = elem;
        if (higherPriority(elem, _elems[parent(idx)])) {
          heapifyUp(idx);
        }
        else {
            heapifyDown(idx);  
        }  
    }

    // returns whether the heap is empty
    bool empty() const {
        return _elems.size() == root();
    }

    // gets elems (adds them to heaped vector)
    void getElems(std::vector<T> & heaped) const {
        for (size_t i = root(); i < _elems.size(); i++) {
            heaped.push_back(_elems[i]);
        }
    }

  private:
    // vector containing elements of heap
    std::vector<T> _elems;

    // compare class to determine how elements are prioritized
    Compare higherPriority;

    // returns idx of left child of elem at idx
    size_t leftChild(size_t currentIdx) const {
        return 2 * currentIdx;
    }

    // returns idx of right child of elem at idx
    size_t rightChild(size_t currentIdx) const {
        return 2 * currentIdx + 1;
    }

    // returns idx of parent of elem at idx
    size_t parent(size_t currentIdx) const {
        return floor(currentIdx / 2);
    }

    // returns whether elem at idx has a child
    bool hasAChild(size_t currentIdx) const {
        return rightChild(currentIdx) < _elems.size() || leftChild(currentIdx) < _elems.size();
    }

    // returns the max priority child of elem at idx
    size_t maxPriorityChild(size_t currentIdx) const {
        size_t left = leftChild(currentIdx);
        size_t right = rightChild(currentIdx);

        if (right >= _elems.size() || higherPriority(_elems[left], _elems[right])) {
            return left;
        }
        return right;
    }

    void heapifyDown(size_t currentIdx) {
        if (!hasAChild(currentIdx)) return;
        size_t priority = maxPriorityChild(currentIdx);
        if (higherPriority(_elems[priority], _elems[currentIdx])) {
          std::swap(_elems[priority], _elems[currentIdx]);
          heapifyDown(priority);
        }
    }

    void heapifyUp(size_t currentIdx) {
        if (currentIdx == root())
            return;
        size_t parentIdx = parent(currentIdx);
        if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
            std::swap(_elems[currentIdx], _elems[parentIdx]);
            heapifyUp(parentIdx);
        }
    }
};