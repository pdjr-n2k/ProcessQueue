/**********************************************************************
 * ProcessQueue - ADT implementing a generic static queue.
 * Copyright (C) 2022 Paul Reeve <pdjr@pdjr.eu>
 */

#include "ProcessQueue.h"

template <class T> ProcessQueue<T>::ProcessQueue(unsigned int queueSize, unsigned long processInterval) {  
  this->queueSize = (queueSize == 0)?ProcessQueue::DEFAULT_QUEUE_SIZE:queueSize;
  this->processInterval = processInterval;
  this->transmitFunction = 0;

  this->queue = new T[queueSize];
  this->front = -1;
  this->rear = -1;
}

template <class T> void ProcessQueue<T>::setProcessFunction(void (*processFunction)(T&)) {
  this->processFunction = processFunction;
}

template <class T> bool ProcessQueue<T>::isEmpty() {
  return((this->front == -1) && (this->rear == -1));
}

template <class T> bool ProcessQueue<T>::isFull() {
  return(((this->rear + 1) % this->queueSize) == this->front);
}

template <class T> bool ProcessQueue<T>::enqueue(T message) {
  bool retval = false;

  if (!this->isFull()) {
    if (this->front == -1) this->front = 0;
    this->rear = ((this->rear + 1) % this->queueSize);
    this->queue[this->rear] = message;
    retval = true;
  }
  return(retval);
}

template <class T> void ProcessQueue<T>::dequeue() {
  if (!this->isEmpty()) {
    if (this->front == this->rear) {
      this->front = this->rear = -1;
    } else {
      this.front = ((this.front + 1) % this->queueSize);
    }
  }
}

template <class T> T* ProcessQueue<T>::head() {
  T *retval = 0;
  if (!this->isEmpty()) retval = this->queue[this->front];
  return(retval);
}

template <class T> void ProcessQueue<T>::process(bool force, bool retain) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if ((now > deadline) || (force)) {
    if (!this->isEmpty()) {
      this->processFunction(this->queue[this->front]);
      if (!retain) {
        if (this->front == this->rear) {
          this->front = this->rear = -1;
        } else {
          this.front = ((this.front + 1) % this->queueSize);
        }
      }
    }
    deadline = (now + this->processInterval());
  }
}
 