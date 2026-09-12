#pragma once

#include <stdint.h>

template<typename ItemType>
class LinkedList
{
private:

    class ListNode;

public:

    class iterator;

    LinkedList() = default; //по умолчанию
    LinkedList(const LinkedList<ItemType>&);
    ~LinkedList(); //деструктор


    LinkedList<ItemType>& operator=(const LinkedList<ItemType>&);
    

    //получение итераторов на начало/конец списка
    iterator begin(); //итератор на начало
    iterator end(); //итератор на конец


    template<typename Predicate>
    iterator findIf(Predicate&& PredicateObject); //поиск элемента по ключу


    //добавление элемента
    void addToHead(const ItemType&); //в голову

    //удаление элемента
    bool delFromHead(); //из головы

    
    bool isEmpty() const; //возвращает true, если список пуст

    void Clear(); //очистка списка

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

//деструктор
template<typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    Clear();
}

template<typename ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& other)
{
    return *this;
}

//получение итераторов на начало/конец списка
template<typename ItemType>
LinkedList<ItemType>::iterator LinkedList<ItemType>::begin() //итератор на начало
{
    return LinkedList<ItemType>::iterator(headPtr_);
}

template<typename ItemType>
LinkedList<ItemType>::iterator LinkedList<ItemType>::end() //итератор на конец
{
    return LinkedList<ItemType>::iterator(nullptr);
}

//поиск элемента по ключу
template<typename ItemType>
template<typename Predicate>
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
//добавление элемента
template<typename ItemType>
void LinkedList<ItemType>::addToHead(const ItemType& value) //в голову
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



//удаление элемента
template<typename ItemType>
bool LinkedList<ItemType>::delFromHead() //из головы
{
    if (isEmpty()) return false;

    ListNode* temp = headPtr_;
    headPtr_ = headPtr_->getLinkToNextNode();

    if (headPtr_) headPtr_->setLinkToPrevNode(nullptr);
    else tailPtr_ = nullptr;

    delete temp;
    --size_;
    return true;
}


template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const //возвращает true, если список пуст
{
    return size_ == 0;
}

template<typename ItemType>
void LinkedList<ItemType>::Clear() //очистка списка
{
    while (!isEmpty())  
    {
        delFromHead(); 
    }
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