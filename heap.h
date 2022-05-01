#pragma once

#include "utils.h"
#include <cmath>

template <class T, class Compare = std::less<T>>
class heap
{
  public:
    heap() {
        _elems.push_back(T());
    }

    heap(const std::vector<T>& elems) {
        _elems.push_back(T());

        for (const T& t : elems) {
          _elems.push_back(t);
        }

        for (size_t idx = _elems.size() - 1; idx > 0; idx--) {
          heapifyDown(idx);
        }
    }

    size_t root() const {
        return 1;
    }

    T pop() {
        if (_elems.size() == root()) return T();

        T root_ = _elems[root()];
        std::swap(_elems[root()], _elems.back());
        _elems.pop_back();
        heapifyDown(root());
        return root_;
    }

    T peek() const {
        return _elems[root()];
    }

    void push(const T& elem) {
        _elems.push_back(elem);
        heapifyUp(_elems.size() - 1);
    }   

    void updateElem(const size_t & idx, const T& elem) {
        _elems[idx] = elem;
        if (higherPriority(elem, _elems[parent(idx)])) {
          heapifyUp(idx);
        }
        else {
            heapifyDown(idx);  
        }  
    }


    bool empty() const {
        return _elems.size() == root();
    }

    void getElems(std::vector<T> & heaped) const {
        for (size_t i = root(); i < _elems.size(); i++) {
            heaped.push_back(_elems[i]);
        }
    }

  private:
    std::vector<T> _elems;
    Compare higherPriority;
    size_t leftChild(size_t currentIdx) const {
        return 2 * currentIdx;
    }

    size_t rightChild(size_t currentIdx) const {
        return 2 * currentIdx + 1;
    }

    size_t parent(size_t currentIdx) const {
        return floor(currentIdx / 2);
    }

    bool hasAChild(size_t currentIdx) const {
        return rightChild(currentIdx) < _elems.size() || leftChild(currentIdx) < _elems.size();
    }

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