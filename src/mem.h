#include <stdint.h>
#include "logging.h"

/**
 * Hook called when the module calls **malloc()** to allocate memory.
 *
 * :param category: Null-terminated string with a category name for the memory operation (**in**)
 * :param size: number of bytes (**in**)
 * :return: Pointer to the allocated memory
 *
 * :since: v0.1
 */
typedef void (*on_malloc_hook_function_t) (char *category, size_t size);

/**
 * Hook called when the module calls **free()** to free memory.
 *
 * :param category: Null-terminated string with a category name for the memory operation (**Input** only.)
 * :param size: TODO (**Input** only.) 
 *
 * :since: v0.1
 */
typedef void (*on_free_hook_function_t) (char *category, uint32_t size);

/**
 * Hook called when the module calls **realloc()** to reallocate memory.
 *
 * :param category:  Null-terminated string with a category name for the memory operation (**in**)
 * :param new_size:  **in**
 * :param prev_size: **in**
 * 
 * :return: Pointer to the reallocated memory
 *
 * :since: v0.1
 */
typedef void (*on_realloc_hook_function_t) (char *category, size_t new_size, size_t prev_size);

#ifndef MIDI_PARSER_MEM_
#define MIDI_PARSER_MEM_

static on_malloc_hook_function_t m_on_malloc_hook_function = NULL;
static on_free_hook_function_t m_on_free_hook_function = NULL;
static on_realloc_hook_function_t m_on_realloc_hook_function = NULL;

/**
 * Invokes **malloc()** and calls the optional hook function.
 *
 * :param category: Null-terminated string with a category name for the memory operation (**in**)
 * :param size:     Number of bytes (**in**)
 * :return:         Pointer to the allocated memory
 *
 * :since: v0.1
 */
void * midi_malloc_with_hook(char *category, size_t size)
{
    if (m_on_malloc_hook_function != NULL)
    {
        m_on_malloc_hook_function(category, size);
    }
    void * memory = malloc(size);

    if (memory == NULL)
    {
        midi_log_info("WARNING: malloc() returned NULL");
    }
    return memory;
}

/**
 * Invokes **free()** and calls the optional hook function.
 *
 * :param category: Null-terminated string with a category name for the memory operation (in)
 * :param ptr: (in)
 * :param size: (in)
 *
 * :since: v0.1
 */
void midi_free_with_hook(char *category, void * ptr, uint32_t size)
{
    if (ptr == NULL)
    {
        return;
    }

    if (m_on_free_hook_function != NULL)
    {
        m_on_free_hook_function(category, size);
    }
    return free(ptr);
}

/**
 * Invokes **realloc()** and calls the optional hook function.
 *
 * :param category: Null-terminated string with a category name for the memory operation (in)
 * :param ptr: (in)
 * :param new_size: (in)
 * :param prev_size: (in)
 *
 * :return: Pointer to the reallocated memory
 *
 * :since: v0.1
 */
void * midi_realloc_with_hook(char *category, void * ptr, size_t new_size, size_t prev_size)
{
    if (m_on_realloc_hook_function != NULL)
    {
        m_on_realloc_hook_function(category, new_size, prev_size);
    }

    void * new_ptr = realloc(ptr, new_size);

    // Add some logging to see if this every happens.
    if (new_ptr == NULL)
    {
        midi_log_info("realloc() returned NULL");
    }

    return new_ptr;
}

/**
 * Allows the user to register a function
 * that will get called when the module calls **malloc()**.
 *
 * :since: v0.1
 */
void midi_register_on_malloc_hook(on_malloc_hook_function_t on_malloc_hook_function)
{
    m_on_malloc_hook_function = on_malloc_hook_function;
}

/**
 * Allows the user to register a function
 * that will get called when the module calls **free()**.
 *
 * :since: v0.1
 */
void midi_register_on_free_hook(on_free_hook_function_t on_free_hook_function)
{
    m_on_free_hook_function = on_free_hook_function;
}

/**
 * Allows the user to register a function
 * that will get called when the module calls **realloc()**.
 *
 * :since: v0.1
 */
void midi_register_on_realloc_hook(on_realloc_hook_function_t on_realloc_hook_function)
{
    m_on_realloc_hook_function = on_realloc_hook_function;
}
#endif
