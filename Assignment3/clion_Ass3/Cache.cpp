#include "Cache.h"
//FIFO



//HashTable For MRU-LRU
int OpenAddressingHash::hashFunction(int key, int i) const {
    int h1 = key % this->size;
    int h2 = 1 + (key % (this->size - 1));
    return (h1 + i * h2) % this->size;
}

int OpenAddressingHash::insertKey(Node *node) {
    int j;
    int i = 0;
    while (i < this->size) {
        j = this->hashFunction(node->elem->addr, i);
        if (this->status[j] != NON_EMPTY) {
            if (this->status[j] == DELETED) {
                delete this->data[j]->elem;
                delete this->data[j];
            }
            this->data[j] = node;
            this->status[j] = NON_EMPTY;
            return j;
        } else
            i += 1;
    }
    return -1;
}

int OpenAddressingHash::searchKey(int key) {
    int i = 0;
    int j;
    do {
        j = this->hashFunction(key, i);
        if (this->data[j]->elem->addr == key && this->status[j] == NON_EMPTY)
            return j;
        i += 1;
    } while (this->status[j] != NIL && i < this->size);
    return -1;
}

void OpenAddressingHash::removeKey(int key) {
    int k = this->searchKey(key);
    if (k != -1) {
        this->status[k] = DELETED;
    } else
        return;
}

Node *OpenAddressingHash::getNodeContainKey(int key) {
    int k = this->searchKey(key);
    if (k != -1)
        return this->data[k];
    else
        return nullptr;
}

//MRU

void MRU::putOnTop(Node *node) {
    node->next = this->head;
    node->prev = nullptr;
    if (this->head != nullptr)
        this->head->prev = node;
    this->head = node;
    if (this->tail == nullptr)
        this->tail = node;
};

void MRU::removeNode(Node *node) {
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else {
        this->head = node->next;
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        this->tail = node->prev;
    }
    this->count--;
}

void MRU::insert(Elem *e) {

    if (this->count >= MAXSIZE) {
        this->hash->removeKey(this->head->elem->addr);
        this->remove();
    }
    Node *temp = new Node(e);
    this->hash->insertKey(temp);
    this->putOnTop(temp);
    this->count++;

}


Elem *MRU::get(int key) {
    Node *tmp = this->hash->getNodeContainKey(key);
    if (tmp != nullptr) {
        this->removeNode(tmp);
        this->putOnTop(tmp);
        return tmp->elem;
    }
    return nullptr;
}

void MRU::replace(int key, Elem *e) {
    Node *tmp = this->hash->getNodeContainKey(key);
    if (tmp != nullptr) {
        this->removeNode(tmp);
        this->putOnTop(tmp);
        delete tmp->elem;
        tmp->elem = e;
    }
}

void MRU::print() {
    Node *tmp = this->head;
    while (tmp != nullptr) {
        tmp->elem->print();
        tmp = tmp->next;
    }
}
//LRU
void LRU::remove() {
    this->removeNode(this->tail);
}
//LFU
Cache::Cache(SearchEngine *s, ReplacementPolicy *r) : rp(r), s_engine(s) {}

Cache::~Cache() {
    delete rp;
    delete s_engine;
}

Data *Cache::read(int addr) {
    return NULL;
}

Elem *Cache::put(int addr, Data *cont) {
    return NULL;
}

Elem *Cache::write(int addr, Data *cont) {
    return NULL;
}

void Cache::printRP() {
}

void Cache::printSE() {
}