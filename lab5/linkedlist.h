#pragma once

#include <stdint.h>
#include <assert.h>
#include <iostream>
using namespace std;

template<typename ItemType>
class LinkedList
{
private:

    class ListNode;

public:

    class iterator;

    LinkedList() = default; //по умолчанию
    LinkedList(const ItemType[], uint32_t); //конструктор из обычного массива
    LinkedList(const LinkedList<ItemType>&); //конструктор копирования
    ~LinkedList(); //деструктор

    uint32_t getSize() const; //получение размера списка

    void swap(LinkedList<ItemType>& other); //обмен содержимого с другим списком(swap)


    //ввод/вывод в консоль (потоковый)
    friend ostream& operator<<(ostream& r, const LinkedList<ItemType>& list) //вывод
    {
        LinkedList<ItemType>::ListNode* temp = list.headPtr_;
        while (temp != nullptr)
        {
            r << temp->getValue() << " ";
            temp = temp->getLinkToNextNode();
        }
        return r;
    }
    friend istream& operator>>(istream& r, LinkedList<ItemType>& list) //ввод
    {
        uint32_t size;
        cout << "Введите количество элементов: ";
        r >> size;

        list.Clear();

        for (uint32_t i = 0; i < size; ++i)
        {
            ItemType value;
            cout << "Элемент " << i + 1 << ": ";
            r >> value;
            list.addToTail(value);
        }
        return r;
    }

    //получение итераторов на начало/конец списка
    iterator begin(); //итератор на начало
    iterator end(); //итератор на конец
    
    template<typename Predicate>
    iterator findIf(Predicate&& PredicateObject); //поиск элемента по ключу

    //добавление элемента
    void addToHead(const ItemType&); //в голову
    void addToTail(const ItemType&); //в хвост
    bool insertAt(uint32_t index, const ItemType& value); //на позицию
    bool addAfter(const ItemType& key, const ItemType& value); //после ключа
    void addByIterator(iterator it, const ItemType& value); //по итератору

    //удаление элемента
    bool delFromHead(); //из головы
    bool delFromTail(); // c хвоста
    bool delAt(uint32_t index); //с позиции
    bool delKey(const ItemType& key); //по ключу
    iterator delByIterator(iterator it); //по итератору

    //поиск максимального / минимального элемента
    ItemType getMax() const; //max
    ItemType getMin() const; //min
   
    bool isEmpty() const; //возвращает true, если список пуст

    void Clear(); //очистка списка

    //присваивание(= )
    LinkedList<ItemType>& operator=(const LinkedList<ItemType>&); 

    //получение ссылки на ключ элемента([])
    ItemType& operator[](uint32_t index);           
    const ItemType& operator[](uint32_t index) const;
    
    //сравнение(== , != )
    bool operator==(const LinkedList<ItemType>& other) const; //==
    bool operator!=(const LinkedList<ItemType>& other) const; //!=

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

//конструктор из обычного массива
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const ItemType array[], uint32_t size)
{
    for (uint32_t i = 0; i < size; ++i)
    {
        addToTail(array[i]);
    }
}

//конструктор копирования
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& other)
{
    ListNode* temp = other.headPtr_;

    while (temp != nullptr)
    {
        addToTail(temp->getValue());

        temp = temp->getLinkToNextNode();
    }
}

//деструктор
template<typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    Clear();
}

//получение размера списка
template<typename ItemType>
uint32_t LinkedList<ItemType>::getSize() const
{
    return size_;
}

//обмен содержимого с другим списком(swap)
template<typename ItemType>
void LinkedList<ItemType>::swap(LinkedList<ItemType>& other)
{
    ListNode* tempHead = headPtr_;
    headPtr_ = other.headPtr_;
    other.headPtr_ = tempHead;

    ListNode* tempTail = tailPtr_;
    tailPtr_ = other.tailPtr_;
    other.tailPtr_ = tempTail;

    uint32_t tempSize = size_;
    size_ = other.size_;
    other.size_ = tempSize;
}

//получение итераторов на начало/конец списка
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::begin() //итератор на начало
{
    return LinkedList<ItemType>::iterator(headPtr_);
}
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::end() //итератор на конец
{
    return LinkedList<ItemType>::iterator(nullptr);
}

//поиск элемента по ключу
template<typename ItemType>
template<typename Predicate>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::findIf(Predicate&& predicateObject)
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
template<typename ItemType>
void LinkedList<ItemType>::addToTail(const ItemType& value) //в хвост
{
    ListNode* newNode = new ListNode(value, nullptr, tailPtr_);

    if (tailPtr_)
    {
        tailPtr_->setLinkToNextNode(newNode);
    }
    else
    {
        headPtr_ = newNode;
    }

    tailPtr_ = newNode;

    ++size_;
}
template<typename ItemType>
bool LinkedList<ItemType>::insertAt(uint32_t index, const ItemType& value) //на позицию
{
    if (index > size_) return false;

    if (index == 0)
    {
        addToHead(value);  
        return true;
    }
    if (index == size_)
    {
        addToTail(value);   
        return true;
    }

    ListNode* temp = headPtr_;
    for (uint32_t i = 0; i < index; ++i)
    {
        temp = temp->getLinkToNextNode();
    }

    ListNode* newNode = new ListNode(value, temp, temp->getLinkToPrevNode());

    temp->getLinkToPrevNode()->setLinkToNextNode(newNode);
    temp->setLinkToPrevNode(newNode);

    ++size_;

    return true;
}
template<typename ItemType>
bool LinkedList<ItemType>::addAfter(const ItemType& key, const ItemType& value) //после ключа
{
    ListNode* temp = headPtr_;
    while (temp != nullptr && temp->getValue() != key)
    {
        temp = temp->getLinkToNextNode();
    }

    if (temp == nullptr) return false;

    ListNode* newNode = new ListNode(value, temp->getLinkToNextNode(), temp);

    if (temp->getLinkToNextNode())
    {
        temp->getLinkToNextNode()->setLinkToPrevNode(newNode);
    }
    else
    {
        tailPtr_ = newNode;
    }

    temp->setLinkToNextNode(newNode);

    ++size_;
    return true;
}
template<typename ItemType>
void LinkedList<ItemType>::addByIterator(iterator it, const ItemType& value) //по итератору
{
    if (it == end())
    {
        addToTail(value);
        return;
    }

    ListNode* current = it.getNodePtr();

    ListNode* newNode = new ListNode(value, current, current->getLinkToPrevNode());

    if (current->getLinkToPrevNode())
    {
        current->getLinkToPrevNode()->setLinkToNextNode(newNode);
    }
    else
    {
        headPtr_ = newNode;
    }

    current->setLinkToPrevNode(newNode);

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
bool LinkedList<ItemType>::delFromTail() //с хвоста
{
    if (isEmpty()) return false;

    ListNode* temp = tailPtr_;

    tailPtr_ = tailPtr_->getLinkToPrevNode();

    if (tailPtr_)
    {
        tailPtr_->setLinkToNextNode(nullptr);
    }
    else
    {
        headPtr_ = nullptr;
    }

    delete temp;

    --size_;
    return true;
}
template<typename ItemType>
bool LinkedList<ItemType>::delAt(uint32_t index) //с позиции
{
    if (index >= size_) return false;

    if (index == 0)
    {
        return delFromHead();
    }
    if (index == size_ - 1)
    {
        return delFromTail();
    }

    ListNode* temp = headPtr_;
    for (uint32_t i = 0; i < index; ++i)
    {
        temp = temp->getLinkToNextNode();
    }

    ListNode* prevNode = temp->getLinkToPrevNode();
    ListNode* nextNode = temp->getLinkToNextNode();

    prevNode->setLinkToNextNode(nextNode);
    nextNode->setLinkToPrevNode(prevNode);

    delete temp;

    --size_;
    return true;
}
template<typename ItemType>
bool LinkedList<ItemType>::delKey(const ItemType& key) //по ключу
{
    ListNode* temp = headPtr_;
    while (temp != nullptr && temp->getValue() != key)
    {
        temp = temp->getLinkToNextNode();
    }

    if (temp == nullptr) return false;

    if (temp == headPtr_)
    {
        return delFromHead();  
    }
    if (temp == tailPtr_)
    {
        return delFromTail(); 
    }

    ListNode* prevNode = temp->getLinkToPrevNode();
    ListNode* nextNode = temp->getLinkToNextNode();

    prevNode->setLinkToNextNode(nextNode);
    nextNode->setLinkToPrevNode(prevNode);

    delete temp;
    --size_;
    return true;
}
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::delByIterator(iterator it) //по итератору 
{
    if (it == end()) return end();

    ListNode* current = it.getNodePtr();
    ListNode* nextNode = current->getLinkToNextNode();

    if (current->getLinkToPrevNode())
    {
        current->getLinkToPrevNode()->setLinkToNextNode(nextNode);
    }
    else
    {
            headPtr_ = nextNode;
    }

    if (nextNode)
    {
        nextNode->setLinkToPrevNode(current->getLinkToPrevNode());
    }
    else
    {
         tailPtr_ = current->getLinkToPrevNode();
    }

    delete current;
    --size_;

    return iterator(nextNode);
}

//поиск максимального / минимального элемента
template<typename ItemType>
ItemType LinkedList<ItemType>::getMax() const //max
{
     assert(!isEmpty() && "List is empty");

    ItemType maxValue = headPtr_->getValue();

    ListNode* temp = headPtr_->getLinkToNextNode();
    while (temp != nullptr)
    {
        if (temp->getValue() > maxValue)
        {
            maxValue = temp->getValue();
        }
        temp = temp->getLinkToNextNode();
    }

    return maxValue;
}
template<typename ItemType>
ItemType LinkedList<ItemType>::getMin() const //min
{
    assert(!isEmpty() && "List is empty");

    ItemType minValue = headPtr_->getValue();

    ListNode* temp = headPtr_->getLinkToNextNode();
    while (temp != nullptr)
    {
        if (temp->getValue() < minValue)
        {
            minValue = temp->getValue();
        }
        temp = temp->getLinkToNextNode();
    }

    return minValue;
}

//возвращает true, если список пуст
template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const 
{
    return size_ == 0;
}

//очистка списка
template<typename ItemType>
void LinkedList<ItemType>::Clear() 
{
    while (!isEmpty())  
    {
        delFromHead(); 
    }
}

//присваивание(= )
template<typename ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& other)
{
    if (this != &other)
    {
        Clear();

        ListNode* temp = other.headPtr_;
        while (temp != nullptr)
        {
            addToTail(temp->getValue());
            temp = temp->getLinkToNextNode();
        }
    }

    return *this;
}

// получение ссылки на ключ элемента([])
template<typename ItemType>
ItemType& LinkedList<ItemType>::operator[](uint32_t index)
{
    assert(index < size_ && "Index out of range");

    ListNode* temp = headPtr_;
    for (uint32_t i = 0; i < index; ++i)
    {
        temp = temp->getLinkToNextNode();
    }

    return temp->getValue();
}
template<typename ItemType>
const ItemType& LinkedList<ItemType>::operator[](uint32_t index) const
{
    assert(index < size_ && "Index out of range");

    ListNode* temp = headPtr_;
    for (uint32_t i = 0; i < index; ++i)
    {
        temp = temp->getLinkToNextNode();
    }

    return temp->getValue();
}

// сравнение(== , != )
template<typename ItemType>
bool LinkedList<ItemType>::operator==(const LinkedList<ItemType>& other) const //==
{
    if (size_ != other.size_) return false;

    ListNode* temp1 = headPtr_;
    ListNode* temp2 = other.headPtr_;

    while (temp1 != nullptr)
    {
        if (temp1->getValue() != temp2->getValue()) return false;

        temp1 = temp1->getLinkToNextNode();
        temp2 = temp2->getLinkToNextNode();
    }

    return true;
}
template<typename ItemType>
bool LinkedList<ItemType>::operator!=(const LinkedList<ItemType>& other) const //!=
{
    if (size_ != other.size_) return true;

    ListNode* temp1 = headPtr_;
    ListNode* temp2 = other.headPtr_;

    while (temp1 != nullptr)
    {
        if (temp1->getValue() != temp2->getValue()) return true;

        temp1 = temp1->getLinkToNextNode();
        temp2 = temp2->getLinkToNextNode();
    }

    return false;
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
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode() { return linkToNextNode_; }

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode() { return linkToPrevNode_; }

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
typename LinkedList<ItemType>::iterator& LinkedList<ItemType>::iterator::operator++()
{
    nodePtr_ = nodePtr_->getLinkToNextNode();
    return *this;
}

template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::iterator::operator++(int)
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