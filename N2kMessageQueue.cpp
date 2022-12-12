/**********************************************************************
 * N2kMessageQueue - ADT implementing an N2K message transmit queue.
 * Copyright (C) 2022 Paul Reeve <pdjr@pdjr.eu>
 */

#include "N2kMessageQueue.h"

N2kMessageQueue::N2kMessageQueue(unsigned int queueSize, unsigned long processInterval) {
  this->queueSize = queueSize;
  this->processInterval = processInterval;
  this->transmitFunction = 0;

  this->queue = new tN2kMsg[queueSize];
  this->front = -1;
  this->rear = -1;
}

void N2kMessageQueue::setTransmitFunction(void (*transmitFunction)(tN2kMsg)) {
  this->transmitFunction = transmitFunction;
}

bool N2kMessageQueue::isEmpty() {
  return((this->front == -1) && (this->rear == -1));
}

bool N2kMessageQueue::isFull() {
  return(((this->rear + 1) % this->queueSize) == this->front);
}

bool N2kMessageQueue::enqueue(tN2kMsg message) {
  bool retval = false;

  if (!this->isFull()) {
    if (this->front == -1) this->front = 0;
    this->rear = ((this->rear + 1) % this->queueSize);
    this->queue[this->rear] = message;
    retval = true;
  }
  return(retval);
}

void N2kMessageQueue::process(bool force) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();
  tN2kMsg message;

  if ((now > deadline) || (force)) {
    if (!this->isEmpty()) {
      this->transmitFunction(this->queue[this->front]);
      if (this->front == this->rear) {
        this->front = this->rear = -1;
      } else {
        this.front = ((this.front + 1) % this->queueSize);
      }
    }
    deadline = (now + this->processInterval());
  }
}
 