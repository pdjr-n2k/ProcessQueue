/**********************************************************************
 * N2kMessageQueue - ADT implementing an N2K message transmit queue.
 * Copyright (C) 2022 Paul Reeve <pdjr@pdjr.eu>
 * 
 * N2kMessageQueue messageQueue();
 * 
 * Create a new message queue instance using the default queue size
 * (10 items) and process interval (4000 ms).
 * 
 * N2kMessageQueue messageQueue(20);
 * 
 * Create a new message queue instance capable of queueing up to 20
 * messages with a default process interval (4000 ms).
 * 
 * N2kMessageQueue messageQueue(15,10000UL);
 * 
 * Create a new message queue instance capable of queueing 15 items
 * with a process interval of 10s.
 * 
 * setTransmitFunction(void (*transmitFunction)(tN2kMsg));
 * 
 * void transmit(tN2kMsg message) {
 * }
 * 
 * void dispose(tN2kMsg message) {
 * }
 * 
 * void setup() {
 *   messageQueue.setCallbacks(transmit, dispose);
 * }
 * 
 * void loop() {
 *   messageQueue.process();
 * }
 * 
 */



#ifndef N2K_MESSAGE_QUEUE
#define N2K_MESSAGE_QUEUE

#include <NMEA2000.h>

class N2kMessageQueue {
    public:
      const static int DEFAULT_MAX_QUEUE_SIZE = 10;
      const static long DEFAULT_PROCESS_INTERVAL = 4000;

      N2kMessageQueue(unsigned int queueSize = N2kMessageQueue::DEFAULT_MAX_QUEUE_SIZE, unsigned long processInterval = N2kMessageQueue::DEFAULT_PROCESS_INTERVAL);

      void setTransmitFunction(void (*transmitFunction)(tN2kMsg));

      bool isEmpty();
      bool isFull();

      bool enqueue(tN2kMsg message);
      void process(bool force = false);

    private:
      int queueSize;
      unsigned long processInterval;
      void (*transmitFunction)(tN2kMsg);

      tN2kMsg* queue;
      int front;
      int rear;
}

#endif

 