
///  NHO DOI TEN BIEN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void push(T item)
{
    this->list.add(item);
}

T pop()
{
    int size = this->list.size();
    return this->list.removeAt(size - 1);
}

T top()
{
    int size = this->list.size();
    return this->list.get(size - 1);
}

bool empty()
{
    return this->list.empty();
}

int size()
{
    return this->list.size();
}

void clear()
{
    this->list.clear();
}