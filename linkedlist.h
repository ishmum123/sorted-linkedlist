#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <ostream>

using std::ostream;

#define Ptr Node<Data>

template<class Data>
struct Node {
    Node(Data data, Ptr *next) : data(data), next(next) {}
    Data data;
    Ptr *next;
};

template<class Data>
class linkedlist {
private:
    Ptr *head;

public:
    ~linkedlist() {
        if(head) {
            Ptr *curr = head, *next;
            while(curr) {
                next = curr->next;
                delete curr;
                head = curr = next;
            }
        }
    }

    Data& front() {
        return head->data;
    }

    Data& back() {
        Ptr *curr = head, *prev;
        while(curr) {
            prev = curr;
            curr = curr->next;
        }
        return prev->data;
    }

    void push_front(const Data& d) {
        head = new Ptr(d, nullptr);
    }

    void push_back(const Data &d) {
        if(!head) push_front(d);
        else {
            Ptr *curr = head;
            while(curr->next) curr = curr->next;
            curr->next = new Ptr(d, nullptr);
        }
    }

    void push_sorted(const Data &d) {
        if(!head) {
            push_front(d);
            return;
        }
        else {
            Ptr *curr = head, *prev;

            while(curr) {
                if(d < curr->data) break;
                prev = curr;
                curr = curr->next;
            }

            Ptr *toInsert = new Ptr(d, nullptr);
            prev->next = toInsert;
        }
    }

    void pop_front() {
        if(!head) return;
        else {
            Ptr *newHead = head->next;
            delete head;
            head = newHead;
        }
    }

    void pop_back() {
        if(!head) return;
        else {
            Ptr *curr = head, *tail;
            while(curr->next) {
                tail = curr;
                tail->next = curr = curr->next;
            }
            delete curr;
        }
    }

    void pop_at(const Data &d) {
        if(!head) return;
        else if(front() == d) pop_front();
        else if(back() == d) pop_back();
        else {
            Ptr *curr = head, *prev;
            while(curr->next) {
                if(curr->data == d) break;
                prev = curr;
                prev->next = curr = curr->next;
            }
            delete curr;
        }
    }

    friend ostream& operator << (ostream& out, const linkedlist<Data> &ll) {
        if(ll.head == NULL) return out;
        else {
            Ptr *curr = ll.head;
            while(curr) {
                out << curr->data << " ";
                curr = curr->next;
            }
            return out;
        }
    }
};

#endif // LINKEDLIST_H
