#pragma once
#include <cassert>

//  �� ���������� � ���� ������� ���������� ������� �� ������. �������� � ����� ����:
//  template <typename Type>
//  [[nodiscard]] SingleLinkedList<Type>::Iterator  SingleLinkedList<Type>::end() noexcept 
//   {...}
//  �� ��� ���������� ����� ������ ����������
//  ������� ��� ���� �� ���������� ��������)))
//

template <typename Type>
class SingleLinkedList 
{
    // ���� ������
    struct Node 
    {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {}
        Type value;
        Node* next_node = nullptr;
    };

// ������ ������ �������� ��������.
// ���������� ��������� ��������� �� �������� ������������ ������
// ValueType � ��������� � Type (��� Iterator) ���� � const Type (��� ConstIterator)
    template <typename ValueType>
    class BasicIterator 
    {
        // ����� ������ ����������� �������������, ����� �� ������� ������
        // ��� ������ � ��������� ������� ���������
        friend class SingleLinkedList;

        // �������������� ����������� ��������� �� ��������� �� ���� ������
        explicit BasicIterator(Node* node) 
        {
            node_ = node;
        }

    public:
        // ����������� ���� ���� �������� ����������� ���������� � ��������� ����� ���������

        // ��������� ��������� � forward iterator
        // (��������, ������� ������������ �������� ���������� � ������������ �������������)
        using iterator_category = std::forward_iterator_tag;
        // ��� ���������, �� ������� ������������ ��������
        using value_type = Type;
        // ���, ������������ ��� �������� �������� ����� �����������
        using difference_type = std::ptrdiff_t;
        // ��� ��������� �� ����������� ��������
        using pointer = ValueType*;
        // ��� ������ �� ����������� ��������
        using reference = ValueType&;

        BasicIterator() = default;

        // �������������� �����������/����������� �����������
        // ��� ValueType, ����������� � Type, ������ ���� ����������� ������������
        // ��� ValueType, ����������� � const Type, ������ ���� ��������������� ������������
        BasicIterator(const BasicIterator<Type>& other) noexcept 
        {
            node_ = other.node_;
        }

        // ����� ���������� �� ������� �������������� �� ���������� ��������� = ��� �������
        // ����������������� ������������ �����������, ���� ������� �������� = �
        // �������� ���������� ������������� ��� �� ���
        BasicIterator& operator=(const BasicIterator& rhs) = default;

        // �������� ��������� ���������� (� ���� ������� ��������� ��������� ����������� ��������)
        // ��� ��������� �����, ���� ��� ��������� �� ���� � ��� �� ������� ������ ���� �� end()
        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept 
        {
            return node_ == rhs.node_;
        }

        // �������� �������� ���������� �� �����������
        // �������������� !=
        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept 
        {
            return !(*this == rhs);
        }

        // �������� ��������� ���������� (� ���� ������� ��������� ��������)
        // ��� ��������� �����, ���� ��� ��������� �� ���� � ��� �� ������� ������ ���� �� end()
        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept 
        {
            return (node_ == rhs.node_);
        }

        // �������� �������� ���������� �� �����������
        // �������������� !=
        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept 
        {
            return !(*this == rhs);
        }

        // �������� ��������������. ����� ��� ������ �������� ��������� �� ��������� ������� ������
        // ���������� ������ �� ������ ����
        // ��������� ���������, �� ������������ �� ������������ ������� ������, �������� � �������������� ���������
        BasicIterator& operator++() noexcept 
        {
            if (node_)
            {
                node_ = node_->next_node;
            }
            return *this;
        }

        // �������� ��������������. ����� ��� ������ �������� ��������� �� ��������� ������� ������
        // ���������� ������� �������� ���������
        // ��������� ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        BasicIterator operator++(int) noexcept 
        {
            BasicIterator temp = *this;
            if (node_)
            {
                node_ = node_->next_node;
            }
            return temp;
        }

        // �������� �������������. ���������� ������ �� ������� �������
        // ����� ����� ��������� � ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        [[nodiscard]] reference operator*() const noexcept
        {
  // ���������: ����� �������� assert, ��� �����, �� ������� ��������� ���������� ���� ���������(�� nullptr), 
  // ����� ����������� ����� �� ������� ������
  // 
  //  ���������: ��������. � ������� ������� ���� ������� �� ��������� ��������. ��������. 
   // � ����������� ��������� ����� ���� ����.
            assert(node_ != nullptr);
            return node_->value;
        }

        // �������� ������� � ����� ������. ���������� ��������� �� ������� ������� ������
        // ����� ����� ��������� � ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        [[nodiscard]] pointer operator->() const noexcept 
        {
            assert(node_ != nullptr);
            return &node_->value;
        }

    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    // ��������, ����������� ��������� ��������� ������
    using Iterator = BasicIterator<Type>;
    // ����������� ��������, ��������������� ������ ��� ������ � ��������� ������
    using ConstIterator = BasicIterator<const Type>;

    SingleLinkedList()
    {
        head_.next_node = nullptr;
        size_ = 0;
    }

    SingleLinkedList(std::initializer_list<Type> values)
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

    SingleLinkedList(const SingleLinkedList& other)
    {
        SingleLinkedList tmp;
        try
        {
            auto it2 = tmp.before_begin();
            for (auto it1 = other.begin();  it1 != other.end(); ++it1, ++it2)
            {
                tmp.InsertAfter(it2, *it1);
            }
        }
        catch (...)
        {
            tmp.Clear();
            throw;
        }
        this->swap(tmp);
    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs)
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

    // ���������� ���������� ������� �� ����� O(1)
    void swap(SingleLinkedList& other) noexcept 
    {
// ���������: ����� ������������ std::swap
// 
// ���������: ��������, �� ��������� ��� �����? ������ � ����� �������?
//         � ����� ��������� �������. ��� ������� �������, ��� std::swap �������� ����������� �� ������, 
// ������� �������� ����� swap. �������� ���-�� � ���� �� ��� � ����, �� �� �������� ��� ��� ������.
//
 //       std::swap(*this, other);
        Node* tmp_head = head_.next_node;
        size_t tmp_size = size_;
        head_.next_node = other.head_.next_node;
        size_ = other.size_;
        other.head_.next_node = tmp_head;
        other.size_ = tmp_size;
    }

    ~SingleLinkedList()
    {
        Clear();
    }

    void Clear() noexcept
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

    // ���������� ��������, ����������� �� ������ �������
    // ���� ������ ������, ������������ �������� ����� ����� end()
    [[nodiscard]] Iterator begin() noexcept
    {
        return Iterator(head_.next_node);
    }

    // ���������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������������ ������
    // �������������� ���� �������� ������ � ������� ������������� ������� � �������������� ���������
    [[nodiscard]] Iterator end() noexcept 
    {
        return Iterator(nullptr);
    }

    // ���������� ����������� ��������, ����������� �� ������ �������
    // ���� ������ ������, ������������ �������� ����� ����� end()
    // ��������� ������ ������������ ������ ������ cbegin()
    [[nodiscard]] ConstIterator begin() const noexcept 
    {
        return ConstIterator(head_.next_node);
    }

    // ���������� ����������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������������ ������
    // �������������� ���� �������� ������ � ������� ������������� ������� � �������������� ���������
    // ��������� ������ ������������ ������ ������ cend()
    [[nodiscard]] ConstIterator end() const noexcept 
    {
        return ConstIterator(nullptr);
    }

    // ���������� ����������� ��������, ����������� �� ������ �������
    // ���� ������ ������, ������������ �������� ����� ����� cend()
    [[nodiscard]] ConstIterator cbegin() const noexcept
    {
        return  ConstIterator(head_.next_node);
    }

    // ���������� ����������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������������ ������
    // �������������� ���� �������� ������ � ������� ������������� ������� � �������������� ���������
    [[nodiscard]] ConstIterator cend() const noexcept 
    {
        return ConstIterator(nullptr);
    }

    // ���������� ��������, ����������� �� ������� ����� ������ ��������� ������������ ������.
   // �������������� ���� �������� ������ - ������� ������������� ������� � �������������� ���������
    [[nodiscard]] Iterator before_begin() noexcept
    {
        return Iterator(&head_);
    }

    // ���������� ����������� ��������, ����������� �� ������� ����� ������ ��������� ������������ ������.
    // �������������� ���� �������� ������ - ������� ������������� ������� � �������������� ���������
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept
    {
        return ConstIterator(const_cast<Node*>(&head_));
    }

    // ���������� ����������� ��������, ����������� �� ������� ����� ������ ��������� ������������ ������.
    // �������������� ���� �������� ������ - ������� ������������� ������� � �������������� ���������
    [[nodiscard]] ConstIterator before_begin() const noexcept
    {
        return ConstIterator(const_cast<Node*>(&head_));
    }

    /*
     * ��������� ������� value ����� ��������, �� ������� ��������� pos.
     * ���������� �������� �� ����������� �������
     * ���� ��� �������� �������� ����� ��������� ����������, ������ ��������� � ������� ���������
     */
    Iterator InsertAfter(ConstIterator pos, const Type& value)
    {
        assert(pos.node_ != nullptr);
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

    void PopFront() noexcept
    {
        if (!IsEmpty())
        {
            Node* tmp_ptr = head_.next_node;
            head_.next_node = head_.next_node->next_node;
            delete tmp_ptr;
            tmp_ptr = nullptr;
            --size_;
        }
    }

    void PushFront(const Type& value)
    {
        try
        {
            head_.next_node = new Node(value, head_.next_node);
            ++size_;
        }
        catch (...)
        {
            throw;
        }
    }

    /*
    * ������� �������, ��������� �� pos.
    * ���������� �������� �� �������, ��������� �� ��������
    */
    Iterator EraseAfter(ConstIterator pos) noexcept
    {
        assert(pos.node_ != nullptr);
        Node* tmp_ptr = pos.node_->next_node;
        pos.node_->next_node = tmp_ptr->next_node;
        delete tmp_ptr;
        tmp_ptr = nullptr;
        --size_;
        return Iterator(pos.node_->next_node);
    }

    // ���������� ���������� ��������� � ������ �� ����� O(1)
    [[nodiscard]] size_t GetSize() const noexcept
    {
        return size_;
    }

    // ��������, ������ �� ������ �� ����� O(1)
    [[nodiscard]] bool IsEmpty() const noexcept
    {
        return size_ == 0;
    }

    //����������� ������ �(N) -��������� ������ ��� �� ���� ������
    void Reverse()
    {
//   ���������:  �� ����� ���� ����� �� ����� - ��� ��� �� ��� ����������, ����� ������� �����.
// ���������� ������� ��������� ���������� - �������� �� ������ ������(head_) � ������ InsertAfter 
//  � ����� � ��, ������� � ������.
// 
//  ���������: ��������. ������ �� ���� ����� ������� ����� ���� ����������� ����������� �� ������, 
// � � ��������� ������ ����� ���� ����������� ����� InsertAfter. �������������� � ��� ���������� ������������� ��� �� ���������. 
// �� � ����� Reverse ����� ����������� ��� �� ����, ������� � ������ ��� ���������. �� ���� ������� ������� ���. 
// � ����������� ���������. ������������ ���� ������ �������� � ����� ���������� � ������.
//
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
            tmp.Clear();
            throw;
        }
        this->swap(tmp);
    }

private:
    // ��������� ����, ������������ ��� ������� "����� ������ ���������"
    Node head_;
    size_t size_ = 0;
};

//------- ���������� ��������� ������� ��� ������ � ������������ ������ SingleLinkedList -------

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept 
{
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs)
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());;
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) 
{
    //����� ���� ����������, �� ���� ���
    return !(lhs == rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs)
{
    return !(rhs > lhs);
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs)
{
    return rhs < lhs;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs)
{
    return !(lhs < rhs);
}