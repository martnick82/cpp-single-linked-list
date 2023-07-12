#include "single_linked_list.h"

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList()
{
    head_.next_node = nullptr;
    size_ = 0;
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(std::initializer_list<Type> values)
{
    SingleLinkedList tmp;
    try
    {
        for (auto it = rbegin(values); it != rend(values); ++it)
        {
            tmp.PushFront(*it);
        }
    }
    catch (...)
    {
        tmp.Clear();
        throw;
    }
    this->swap(tmp);
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(const SingleLinkedList& other)
{
    SingleLinkedList tmp;
    try
    {
        for (const Type& t : other)
        {
            tmp.PushFront(t);
        }
        tmp.Reverse();
    }
    catch (...)
    {
        tmp.Clear();
        throw;
    }
    this->swap(tmp);
}

template <typename Type>
SingleLinkedList<Type>& SingleLinkedList<Type>::operator=(const SingleLinkedList& rhs)
{
    if (this != &rhs)
    {
        try
        {
            SingleLinkedList tmp(rhs);
            this->swap(tmp);
        }
        catch (...)
        {
            throw;
        }
    }
    return *this;
}

template <typename Type>
void SingleLinkedList<Type>::swap(SingleLinkedList& other) noexcept 
{
    Node* tmp_head = head_.next_node;
    size_t tmp_size = size_;
    head_.next_node = other.head_.next_node;
    size_ = other.size_;
    other.head_.next_node = tmp_head;
    other.size_ = tmp_size;
}

template <typename Type>
SingleLinkedList<Type>::~SingleLinkedList()
{
    Clear();
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::begin() noexcept
{
    return Iterator(head_.next_node);
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::end() noexcept 
{
    return Iterator(nullptr);
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::begin() const noexcept 
{
    return ConstIterator(head_.next_node);
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::end() const noexcept 
{
    return ConstIterator(nullptr);
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cbegin() const noexcept
{
    return  ConstIterator(head_.next_node);
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cend() const noexcept 
{
    return ConstIterator(nullptr);
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::before_begin() noexcept
{
    return Iterator(&head_);
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cbefore_begin() const noexcept
{
    return ConstIterator(const_cast<Node*>(&head_));
}

template <typename Type>
[[nodiscard]] SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::before_begin() const noexcept
{
    return ConstIterator(const_cast<Node*>(&head_));
}

template <typename Type>
SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::InsertAfter(ConstIterator pos, const Type& value)
{
    Node* tmp_ptr = nullptr;
    try
    {
        tmp_ptr = new Node(value, pos.node_->next_node);
    }
    catch (...)
    {
        delete tmp_ptr;
        throw;
    }
    pos.node_->next_node = tmp_ptr;
    ++size_;
    return Iterator(tmp_ptr);
}

template <typename Type>
void SingleLinkedList<Type>::PopFront() noexcept
{
    Node* tmp_ptr = head_.next_node;
    head_.next_node = head_.next_node->next_node;
    delete tmp_ptr;
    tmp_ptr = nullptr;
    --size_;
}

template <typename Type>
SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::EraseAfter(ConstIterator pos) noexcept
{
    Node* tmp_ptr = pos.node_->next_node;
    pos.node_->next_node = tmp_ptr->next_node;
    delete tmp_ptr;
    tmp_ptr = nullptr;
    --size_;
    return Iterator(pos.node_->next_node);
}

template <typename Type>
[[nodiscard]] size_t SingleLinkedList<Type>::GetSize() const noexcept
{
    return size_;
}

template <typename Type>
[[nodiscard]] bool SingleLinkedList<Type>::IsEmpty() const noexcept
{
    return size_ == 0;
}

template <typename Type>
void SingleLinkedList<Type>::PushFront(const Type& value)
{
    head_.next_node = new Node(value, head_.next_node);
    ++size_;
}

template <typename Type>
void SingleLinkedList<Type>::Reverse()
{
    SingleLinkedList tmp;
    try
    {
        for (const Type& t : *this)
        {
            tmp.PushFront(t);
        }
    }
    catch (...)
    {
        throw;
    }
    this->swap(tmp);
}

template <typename Type>
void SingleLinkedList<Type>::Clear() noexcept
{
    while (head_.next_node != nullptr)
    {
        Node* temp_ptr = head_.next_node;
        head_.next_node = (*head_.next_node).next_node;
        delete temp_ptr;
        temp_ptr = nullptr;
        --size_;
    }
}