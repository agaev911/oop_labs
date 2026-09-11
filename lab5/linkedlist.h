#pragma once

#pragma once

#include <stdint.h>

template<typename ItemType>
class LinkedList
{
private:

    class ListNode;

public:

    class iterator;

    LinkedList() = default; //конструктор по умолчанию
    LinkedList(const LinkedList<ItemType>&);
    ~LinkedList();

    LinkedList<ItemType>& operator=(const LinkedList<ItemType>&);
    
    //получение итераторов на начало / конец списка(методы должны называться begin и end
    iterator begin();
    iterator end();

    //добавление элемента
    void addToHead(const ItemType&); //в голову

    
    template<typename Predicate>
    iterator findIf(Predicate&& PredicateObject); //поиск элемента по ключу

private:

    ListNode* headPtr_ = nullptr;
    ListNode* tailPtr_ = nullptr;
    uint32_t size_ = 0;
};

template<typename ItemType>
class LinkedList<ItemType>::ListNode
{
public:

    ListNode(ItemType = ItemType(), ListNode* = nullptr, ListNode* = nullptr);

    ItemType& getValue();
    const ItemType& getValue() const;

    ListNode* getLinkToNextNode();
    ListNode* getLinkToPrevNode();

    void setLinkToNextNode(ListNode*);
    void setLinkToPrevNode(ListNode*);

private:

    ItemType value_;
    ListNode* linkToNextNode_;
    ListNode* linkToPrevNode_;
};

template<typename ItemType>
class LinkedList<ItemType>::iterator
{
public:

    iterator(ListNode*);

    bool operator==(const iterator&);
    bool operator!=(const iterator&);
    iterator& operator++();
    iterator operator++(int);
    ItemType& operator*();

private:

    ListNode* nodePtr_;
};

template<typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& other)
{
    // Самостоятельно
}

template<typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    // Самостоятельно
}

template<typename ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& other)
{
    return *this;
}

template<typename ItemType>
LinkedList<ItemType>::iterator LinkedList<ItemType>::begin()
{
    return LinkedList<ItemType>::iterator(headPtr_);
}

template<typename ItemType>
LinkedList<ItemType>::iterator LinkedList<ItemType>::end()
{
    return LinkedList<ItemType>::iterator(nullptr);
}

//получение итераторов на начало / конец списка(методы должны называться begin и end)
template<typename ItemType>
void LinkedList<ItemType>::addToHead(const ItemType& value)
{
    LinkedList<ItemType>::ListNode* newNode = new LinkedList<ItemType>::ListNode(value, headPtr_);

    if (headPtr_)
    {
        headPtr_->setLinkToPrevNode(newNode);
    }

    headPtr_ = newNode;

    if (!tailPtr_)
    {
        tailPtr_ = newNode;
    }

    ++size_;
}

template<typename ItemType>
template<typename Predicate>
//поиск элемента по ключу
LinkedList<ItemType>::iterator LinkedList<ItemType>::findIf(Predicate&& predicateObject)
{
    LinkedList<ItemType>::iterator it = begin();

    while (it != end())
    {
        if (predicateObject(*it)) return it;

        ++it;
    }

    return LinkedList<ItemType>::iterator(nullptr);
}

template<typename ItemType>
LinkedList<ItemType>::ListNode::ListNode(ItemType value, ListNode* linkToNextNode, ListNode* linkToPrevNode) :
    value_(value), linkToNextNode_(linkToNextNode), linkToPrevNode_(linkToPrevNode) {
}

template<typename ItemType>
ItemType& LinkedList<ItemType>::ListNode::getValue() { return value_; }

template<typename ItemType>
const ItemType& LinkedList<ItemType>::ListNode::getValue() const { return value_; }

template<typename ItemType>
LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode() { return linkToNextNode_; }

template<typename ItemType>
LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode() { return linkToPrevNode_; }

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToNextNode(ListNode* newLink) { linkToNextNode_ = newLink; }

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToPrevNode(ListNode* newLink) { linkToPrevNode_ = newLink; }

template<typename ItemType>
LinkedList<ItemType>::iterator::iterator(LinkedList<ItemType>::ListNode* nodePtr) : nodePtr_(nodePtr) {}

template<typename ItemType>
bool LinkedList<ItemType>::iterator::operator==(const iterator& other)
{
    return !(*this != other);
}

template<typename ItemType>
bool LinkedList<ItemType>::iterator::operator!=(const iterator& other)
{
    return nodePtr_ != other.nodePtr_;
}

template<typename ItemType>
LinkedList<ItemType>::iterator& LinkedList<ItemType>::iterator::operator++()
{
    nodePtr_ = nodePtr_->getLinkToNextNode();
    return *this;
}

template<typename ItemType>
LinkedList<ItemType>::iterator LinkedList<ItemType>::iterator::operator++(int)
{
    LinkedList<ItemType>::iterator oldIterator(*this);
    nodePtr_ = nodePtr_->getLinkToNextNode();
    return oldIterator;
}

template<typename ItemType>
ItemType& LinkedList<ItemType>::iterator::operator*()
{
    return nodePtr_->getValue();
}