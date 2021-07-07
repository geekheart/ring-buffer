/**
 * @file ringbuf.c
 * @author geekheart (sky.kirto@gmail.com)
 * @brief A simple ring buffer
 * @version 0.1
 * @date 2021-07-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <string.h>
#include <stdlib.h>

#include "ringbuf.h"

/**
 * @brief create ring buffer object
 * 
 * @param buf_size ringbuf size
 * @return ringbuf_t* ring buffer object. 
 *      If NULL is returned, the creation fails
 */
ringbuf_t *ringbuf_create(unsigned int buf_size)
{
    ringbuf_t *ringbuf = (ringbuf_t *)malloc(sizeof(ringbuf_t));
    if (ringbuf == NULL)
    {
        return NULL;
    }

    ringbuf->size = buf_size;
    ringbuf->head = (char *)malloc(sizeof(char) * ringbuf->size);
    if (ringbuf->head == NULL)
    {
        return NULL;
    }
    ringbuf->tail = ringbuf->head + ringbuf->size;
    ringbuf->valid_head = ringbuf->head;
    ringbuf->valid_tail = ringbuf->head;
    ringbuf->valid_len = 0;

    return ringbuf;
}

/**
 * @brief delete ring buffer object. reclaim memory
 * 
 * @param self ring buffer object
 */
void ringbuf_delete(ringbuf_t *self)
{
    free(self->head);
    free(self);
}

/**
 * @brief Write data to ring buffer
 * 
 * @param self ring buffer object
 * @param buffer The data you want to write
 * @param len ring buffer data length
 * @return char Fail if it returns -1.Return 0 if successful
 */
char ringbuf_write(ringbuf_t *self, char *buffer, unsigned int len)
{
    if (len > self->size)
    {
        return -1;
    }
    if (self->valid_tail + len > self->tail)
    {
        int len1 = self->tail - self->valid_tail;
        int len2 = len - len1;
        memcpy(self->valid_tail, buffer, len1);
        memcpy(self->valid_head, buffer + len1, len2);
        self->valid_tail = self->head + len2;
    }
    else
    {
        memcpy(self->valid_tail, buffer, len);
        self->valid_tail += len;
    }

    if (self->valid_len + len > self->size)
    {
        int move_len = self->valid_len + len - self->size;
        if (self->valid_head + move_len > self->tail)
        {
            int len1 = self->tail - self->valid_head;
            int len2 = move_len - len1;
            self->valid_head = self->head + len2;
        }
        else
        {
            self->valid_head += move_len;
        }
        self->valid_len = self->size;
    }
    else
    {
        self->valid_len += len;
    }
    return 0;
}

/**
 * @brief Read ring buffer data
 * 
 * @param self ring buffer object
 * @param len ring buffer data length
 * @return char* Return the read result
 */
char *ringbuf_read(ringbuf_t *self, unsigned int len)
{
    if (self->valid_len == 0)
    {
        return NULL;
    }
    if (len == 0 || len > self->valid_len)
    {
        len = self->valid_len;
    }
    char *buffer = (char *)malloc(sizeof(char) * len);
    if (buffer == NULL)
    {
        return NULL;
    }

    if (self->valid_head + len > self->tail)
    {
        int len1 = self->tail - self->valid_head;
        int len2 = len - len1;
        memcpy(buffer, self->valid_head, len1);
        memcpy(buffer + len1, self->head, len2);
        self->valid_tail = self->head + len2;
    }
    else
    {
        memcpy(buffer, self->valid_head, len);
        self->valid_head += len;
    }
    self->valid_len -= len;
    return buffer;
}
