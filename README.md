# Ring-buffer
This is an extremely simple ring buffer.  It can be easily integrated into resource-limited or embedded projects.

# Features
 - first in first out
 - When the buffer is used up and new data needs to be stored, discard the oldest data and save the latest data
 - compatible with C89
 - no dependencies (only depened on <stdlib.h> and <string.h>)
 - highly portable (tested on x86/amd64, ARM, AVR)

# Usage
Download **ringbuf.c** and **ringbuf.h**. Include in your project

```C
#include "ringbuf.h" // Include library files

...

// Create a ring buffer with a size of 128B
ringbuf_t* ringbuf = ringbuf_create(128);

// Write msg data to the buffer
ringbuf_write(ringbuf, msg, strlen(msg));

// Read all data when the second parameter is 0
char* data = ringbuf_read(ringbuf, 0);



```
If you want to see the results quickly, you can try to use make to compile the example.



# Other info
This software is distributed under MIT license, so feel free to integrate it in your commercial products.