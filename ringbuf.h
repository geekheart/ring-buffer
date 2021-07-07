#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    // Ring buffer class
    typedef struct
    {
        char *head;             // Head pointer of the entire ring buffer
        char *tail;             // Tail pointer of the entire ring buffer
        char *valid_head;       // Head of used memory
        char *valid_tail;       // End of used memory
        unsigned int size;      // Ring buffer size
        unsigned int valid_len; // Used area size
    } ringbuf_t;

    ringbuf_t *ringbuf_create(unsigned int buf_size);
    void ringbuf_delete(ringbuf_t *self);
    char ringbuf_write(ringbuf_t *self, char *buffer, unsigned int len);
    char *ringbuf_read(ringbuf_t *self, unsigned int len);

#ifdef __cplusplus
} /* extern "C" */
#endif