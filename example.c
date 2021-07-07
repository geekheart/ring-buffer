#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ringbuf.h"

int main(int argc, char *argv[])
{
    char msg1[27], msg2[27];
    strcpy(msg1, "abcde");
    strcpy(msg2, "fghij");
    ringbuf_t* ringbuf = ringbuf_create(9);

    ringbuf_write(ringbuf, msg1, strlen(msg1));
    ringbuf_write(ringbuf, msg2, strlen(msg2));
    
    char* data = ringbuf_read(ringbuf, 2);
    printf("%s\n", data);
    char* data2 = ringbuf_read(ringbuf, 0);
    printf("%s\n", data2);

    free(data);
    free(data2);
    ringbuf_delete(ringbuf);
}