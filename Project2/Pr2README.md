Problem 1: Bounded-buffer Producer/Consumer problem:
This program creates and consumes items from the buffer. the buffer is there to keep a fixed size amount on how much can be created or consummed. We use a mutex to allow how many entries can be entered or exiting at once.

Excecution:
This allows the user to either create an item or remove an item. if an item hasn't been created then a messaged will show up saying that there is no item inside the buffer and vise versa for the consumer.

--------------------------------------------------------------
Problem 2: Mother Hubbard (children, mother, father):
This program shows the daily assigned task of the mother and father taking care of 12 children. While taking turns using two threads for mother and father.
Mother wakes up a child, feed Breakfast, send to school, gives dinner, gives baths, and signal Father to wake up for his assigned tasks.
While mother gives baths to the children, father wait until the first kid comes out of the shower to read a book and then tucks the childs to sleep.
At the end, the father wakes mother again for her tasks.

Excecution:
./mh <Enter the # of days here>

--------------------------------------------------------------
Problem 3: Airline Passengers:
The purpose of this program is take passengers through
an airline process and ensure they are all seated in
the end. This is done using multiple threads for each
the passengers and the baggage, security, and boarding.

Excecution:
./airline <passengers> <baggage handlers> <security screeners> <flight attendants>

--------------------------------------------------------------
