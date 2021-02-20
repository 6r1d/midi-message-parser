#include "logging.h"

/**
* @brief Hook called when the module calls malloc() to allocate memory.
*
* @param[in] category - Null-terminated string with a category name for the memory operation
* @param[in] size     - number of bytes
* @return         - Pointer to the allocated memory
*/
typedef void (*on_malloc_hook_function_t) (char *category, size_t size);

/**
* @brief Hook called when the module calls free() to free memory.
*
* @param[in] category - Null-terminated string with a category name for the memory operation
* @param[in] size
*/
typedef void (*on_free_hook_function_t) (char *category, uint32_t size);

/**
* @brief Hook called when the module calls realloc() to reallocate memory.
*
* @param[in] category  - Null-terminated string with a category name for the memory operation
* @param[in] new_size
* @param[in] prev_size
* @return              - Pointer to the reallocated memory
*/
typedef void (*on_realloc_hook_function_t) (char *category, size_t new_size, size_t prev_size);

#ifndef MIDI_PARSER_MEM_
#define MIDI_PARSER_MEM_

static on_malloc_hook_function_t m_on_malloc_hook_function = NULL;
static on_free_hook_function_t m_on_free_hook_function = NULL;
static on_realloc_hook_function_t m_on_realloc_hook_function = NULL;

/**
* @brief Invokes malloc() and calls the optional hook function.
*
* @param[in] category - Null-terminated string with a category name for the memory operation
* @param[in] size     - number of bytes
* @return         - Pointer to the allocated memory
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
* @brief Invokes free() and calls the optional hook function.
*
* @param[in] category - Null-terminated string with a category name for the memory operation
* @param[in] ptr
* @param[in] size
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
* @brief Invokes realloc() and calls the optional hook function.
*
* @param[in] category  - Null-terminated string with a category name for the memory operation
* @param[in] ptr
* @param[in] new_size
* @param[in] prev_size
* @return              - Pointer to the reallocated memory
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
* @brief Allows the user to register a function that will get called when the module calls malloc().
*/
void midi_register_on_malloc_hook(on_malloc_hook_function_t on_malloc_hook_function)
{
    m_on_malloc_hook_function = on_malloc_hook_function;
}

/**
* @brief Allows the user to register a function that will get called when the module calls free().
*/
void midi_register_on_free_hook(on_free_hook_function_t on_free_hook_function)
{
    m_on_free_hook_function = on_free_hook_function;
}

/**
* @brief Allows the user to register a function that will get called when the module calls realloc().
*/
void midi_register_on_realloc_hook(on_realloc_hook_function_t on_realloc_hook_function)
{
    m_on_realloc_hook_function = on_realloc_hook_function;
}
#endif
