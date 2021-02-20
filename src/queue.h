#include <stdint.h>
#include "mem.h"
#include "msg.h"

/**
 * A queue that holds MIDI messages.
 */
typedef struct {
    /** Message count */
    uint16_t length;
    /** Array of pointers to messages */
    midi_message_t * messages[];
} midi_message_queue_t;

/**
 * MIDI message queue constructor.
 * 
 * :returns: a new midi_message_queue_t instance
 *
 * :since: v0.1
 */
midi_message_queue_t * new_midi_message_queue()
{
    midi_message_queue_t * message_queue = (midi_message_queue_t *) midi_malloc_with_hook(MIDI_MEMORY_CATEGORY, sizeof(midi_message_queue_t));
    message_queue->length = 0;
    return message_queue;
}

/**
 * Deallocates the memory for the message queue and the messages it contains.
 *
 * :since: v0.1
 */
void free_midi_message_queue(midi_message_queue_t * message_queue)
{
    // First, free the messages in the queue
    for (uint16_t i = 0; i < message_queue->length; i++)
    {
        free_midi_message(message_queue->messages[i]);
    }
    uint32_t size = sizeof(midi_message_queue_t) + sizeof(midi_message_t *) * message_queue->length;
    midi_log_info("Freeing %u bytes for MIDI message queue", size);
    midi_free_with_hook(MIDI_MEMORY_CATEGORY, message_queue, size);
}

/**
 * Pushes a MIDI message into a MIDI message queue.
 *
 * :param message_queue_ptr: Pointer to the message queue into
 *                           which the message should be pushed (**Input and output**)
 * :param message:           The message to push into the queue (**Input only**)
 * :return:                  The updated message queue pointer
 *                           after reallocating the memory
 *                           to store the new message
 *
 * :since: v0.1
 */
void add_midi_message_to_queue(midi_message_queue_t **message_queue_ptr, midi_message_t *message)
{
    if (!(message_queue_ptr && *message_queue_ptr && message))
    {
        // This shouldn't happen.
        return;
    }

    size_t prev_size = sizeof(midi_message_queue_t) + (*message_queue_ptr)->length * sizeof(midi_message_t *);
    (*message_queue_ptr)->length++;
    size_t new_size = prev_size + sizeof(midi_message_t *);

    // Resize the array of pointers to to have room for the new message pointer.
    // In order to do this for a struct with a flexible array in standard c, the entire struct needs to be resized.
    *message_queue_ptr = midi_realloc_with_hook(MIDI_MEMORY_CATEGORY, *message_queue_ptr, new_size, prev_size);
    (*message_queue_ptr)->messages[(*message_queue_ptr)->length - 1] = message;
}

/**
 * Revmoes a MIDI message at a given index from a MIDI message queue.
 *
 * :param message_queue_ptr: Pointer to the message queue
 *                           from which the message should be removed (**Input and output**)
 * :param index:             The index of the message to be removed (**Input only**)
 *
 * :return: The updated message queue pointer after reallocating the memory for the message queue.
 *
 * :since: v0.1
 */
void remove_midi_message_from_queue(midi_message_queue_t **message_queue_ptr, uint16_t index)
{
    if (!(message_queue_ptr && *message_queue_ptr))
    {
        return;
    }

    if (index > (*message_queue_ptr)->length - 1)
    {
        return;
    }

    size_t prev_size = sizeof(midi_message_queue_t) + (*message_queue_ptr)->length * sizeof(midi_message_t *);
    size_t new_size = prev_size - sizeof(midi_message_t *);


    // Unless the message removed is at the end of the queue, we need to shift the messages after it
    // up 1 spot.
    if (index != (*message_queue_ptr)->length - 1)
    {
        memcpy((*message_queue_ptr)->messages[index], (*message_queue_ptr)->messages[index + 1], (*message_queue_ptr)->length - (index + 1));
    }

    // Resize the array of pointers to to have room for the new message pointer.
    // In order to do this for a struct with a flexible array in standard c, the entire struct needs to be resized.
    *message_queue_ptr = midi_realloc_with_hook(MIDI_MEMORY_CATEGORY, *message_queue_ptr, new_size, prev_size);
    (*message_queue_ptr)->length--;
}

/**
 * Transfers all of the MIDI messages from one queue to another.
 *
 * :param destination_queue_ptr: (**Input and output**)
 * :param source_queue_ptr: (**Input and output**)
 *
 * :since: v0.1
 */
void transfer_midi_messages(midi_message_queue_t **destination_queue_ptr, midi_message_queue_t **source_queue_ptr)
{
    if (!(destination_queue_ptr && *destination_queue_ptr && source_queue_ptr && *source_queue_ptr))
    {
        return;
    }

    for (uint16_t i = (*source_queue_ptr)->length - 1; i >= 0 ; i--)
    {
        midi_message_t *message = (*source_queue_ptr)->messages[i];
        add_midi_message_to_queue(destination_queue_ptr, message);
        remove_midi_message_from_queue(source_queue_ptr, i);
    }
}
