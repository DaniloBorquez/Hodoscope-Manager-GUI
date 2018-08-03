#include "buffer.h"

Buffer::Buffer(int maxSize)
{
    this->maxSize = maxSize;
    this->buf = new QVector<Data*>();
}

void Buffer::push(Data *data)
{
    this->buf->push_back(data);
    if(this->buf->size() > this->maxSize){
        this->buf->pop_front();
    }
}
