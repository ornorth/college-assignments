/**
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & Owen North
 * @date 9/1/20
 **/

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

#include <iostream>
template <class T>
class DoublyLinkedList {

        public:
                DoublyLinkedList();
                ~DoublyLinkedList();
                void append(T* data);
                bool empty() const { return (head == nullptr); }
                T* remove();
                T* first();
                T* next();

        private:
                class Node {
                        public:
                                Node();
                                Node(T* data);
                                Node* next;
                                Node* prev;
                                T* data;
                };
                Node* head;
                Node* tail;
                Node* current;
};

/**
 * @brief   Node constructor.
 */
template <class T>
DoublyLinkedList<T>::Node::Node() {

        next = nullptr;
        prev = nullptr;

}

/**
 * @brief   overloaded Node constructor
 */
        template <class T>
DoublyLinkedList<T>::Node::Node(T* data)
{
        next = nullptr;
        prev = nullptr;
        this->data = data;
}


/**
 * @brief   DoublyLinkedList constructor.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {

        head = nullptr;
        tail = nullptr;
        current = nullptr;

}

/**
 * @brief   DoublyLinkedList destructor.
 */
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

        //Start at beginning of list
        current = head;

        //Iterate through entire list
        while (current != nullptr)
        {
                //Use head as a placeholder - previous
                head = current;
                //Advance current and deallocate previous data
                current = current->next;
                delete head;
        }
}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data) {

        //Empty list
        Node* toInsert = new Node(data);
        if (head == nullptr)
        {
                head = toInsert;
                tail = toInsert;
                current = toInsert;
        }
        //List has at least one item
        else
        {
                //link tail and new node
                toInsert->prev = tail;
                tail->next = toInsert;

                //update tail and current
                tail = toInsert;
                current = tail;
        }

}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first() {

        current = head;
        return (current == nullptr? nullptr : current->data);

}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next() {

        if (current != nullptr)
        {
                current = current->next;
        }
        return (current == nullptr? nullptr : current->data);

}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::remove() {

        if (current != nullptr)
        {
                //create temp node to delete
                Node* tmp = current;

                //Update head
                if (current == head)
                {
                        head = current->next;
                        if (head != nullptr)
                        {
                                head->prev = nullptr;
                        }
                }
                //Update tail
                else if (current == tail)
                {
                        tail = current->prev;
                        if (tail != nullptr)
                        {
                                tail->next = nullptr;
                        }
                }
                //point previous and next nodes to each other
                if (current->next != nullptr)
                {
                        current->next->prev = current->prev;
                }
                if (current->prev != nullptr)
                {
                        current->prev->next = current->next;
                }
                //update current and delete temp node
                current = current->next;
                delete tmp;
        }
        return (current == nullptr? nullptr : current->data);

}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
