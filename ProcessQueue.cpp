/**********************************************************************
 * ProcessQueue - ADT implementing a generic static queue.
 * Copyright (C) 2022 Paul Reeve <pdjr@pdjr.eu>
 */

#include <Arduino.h>
#include "ProcessQueue.h"

template <typename T>
ProcessQueue<T>::ProcessQueue(unsigned int queueSize, unsigned long processInterval, void (*processFunction)(T)) {  
  this->queueSize = (queueSize == 0)?ProcessQueue::DEFAULT_QUEUE_SIZE:queueSize;
  this->processInterval = processInterval;
  this->processFunction = processFunction;

  this->queue = new T[queueSize];
  this->front = -1;
  this->rear = -1;
}

template <typename T>
void ProcessQueue<T>::setProcessFunction(void (*processFunction)(T)) {
  this->processFunction = processFunction;
}

template <typename T>
bool ProcessQueue<T>::isEmpty() {
  return((this->front == -1) && (this->rear == -1));
}

template <typename T>
bool ProcessQueue<T>::isFull() {
  return(((this->rear + 1) % this->queueSize) == this->front);
}

template <typename T>
bool ProcessQueue<T>::enqueue(T item) {
  bool retval = false;

  if (!this->isFull()) {
    if (this->front == -1) this->front = 0;
    this->rear = ((this->rear + 1) % this->queueSize);
    this->queue[this->rear] = item;
    retval = true;
  }
  return(retval);
}

template <typename T>
void ProcessQueue<T>::dequeue() {
  if (!this->isEmpty()) {
    if (this->front == this->rear) {
      this->front = this->rear = -1;
    } else {
      this->front = ((this->front + 1) % this->queueSize);
    }
  }
}

template <typename T>
T ProcessQueue<T>::head() {
  return(this->queue[this->front]);
}

template <typename T>
void ProcessQueue<T>::process(bool force, bool retain) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if ((now > deadline) || (force)) {
    if (!this->isEmpty()) {
      this->processFunction(this->queue[this->front]);
      if (!retain) {
        if (this->front == this->rear) {
          this->front = this->rear = -1;
        } else {
          this->front = ((this->front + 1) % this->queueSize);
        }
      }
    }
    deadline = (now + this->processInterval);
  }
}
 