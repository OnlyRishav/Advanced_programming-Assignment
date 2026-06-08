#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char   *data;
    size_t  length;
    size_t  capacity;
} StringBuffer;

StringBuffer *sb_init(size_t initial_capacity) {
    if (initial_capacity == 0) initial_capacity = 1;

    StringBuffer *sb = (StringBuffer *)malloc(sizeof(StringBuffer));
    if (sb == NULL) {
        fprintf(stderr, "sb_init: failed to allocate struct\n");
        return NULL;
    }

    sb->data = (char *)malloc(initial_capacity);
    if (sb->data == NULL) {
        fprintf(stderr, "sb_init: failed to allocate data buffer\n");
        free(sb);
        return NULL;
    }

    sb->data[0]  = '\0';
    sb->length   = 0;
    sb->capacity = initial_capacity;
    return sb;
}

int sb_append(StringBuffer *sb, const char *str) {
    if (sb == NULL || str == NULL) return -1;

    size_t str_len = strlen(str);
    size_t needed  = sb->length + str_len + 1;

    while (needed > sb->capacity) {
        size_t new_cap = sb->capacity * 2;
        /* safe realloc: temp pointer preserves original on failure */
        char *tmp = (char *)realloc(sb->data, new_cap);
        if (tmp == NULL) {
            fprintf(stderr, "sb_append: realloc failed\n");
            return -1;
        }
        sb->data     = tmp;
        sb->capacity = new_cap;
        printf("  [realloc] capacity grew to %zu bytes\n", sb->capacity);
    }

    memcpy(sb->data + sb->length, str, str_len + 1);
    sb->length += str_len;
    return 0;
}

void sb_free(StringBuffer *sb) {
    if (sb == NULL) return;
    free(sb->data);
    sb->data     = NULL;
    sb->length   = 0;
    sb->capacity = 0;
    free(sb);
}

static void sb_print_state(const StringBuffer *sb, const char *label) {
    printf("  %-12s | length=%-4zu | capacity=%-4zu | data=\"%s\"\n",
           label, sb->length, sb->capacity, sb->data);
}

int main(void) {
    
    StringBuffer *sb = sb_init(8);
    if (sb == NULL) {
        fputs("Fatal: could not create StringBuffer.\n", stderr);
        return EXIT_FAILURE;
    }

    puts("Initialized StringBuffer:");
    sb_print_state(sb, "initial");
    puts("");

    puts("Appending \"Hello, \" (7 chars)...");
    if (sb_append(sb, "Hello, ") != 0) { sb_free(sb); return EXIT_FAILURE; }
    sb_print_state(sb, "after #1");
    puts("");

    puts("Appending \"World! \" (7 chars, pushes past 8-byte capacity)...");
    if (sb_append(sb, "World! ") != 0) { sb_free(sb); return EXIT_FAILURE; }
    sb_print_state(sb, "after #2");
    puts("");

    puts("Appending \"How are you doing today?\" (24 chars, pushes past 16)...");
    if (sb_append(sb, "How are you doing today?") != 0) { sb_free(sb); return EXIT_FAILURE; }
    sb_print_state(sb, "after #3");
    puts("");

    puts("Appending \" Great!\" (7 chars, fits without growth)...");
    if (sb_append(sb, " Great!") != 0) { sb_free(sb); return EXIT_FAILURE; }
    sb_print_state(sb, "after #4");
    puts("");

    puts("------------------------------------------------------");
    printf("Final string (%zu chars): \"%s\"\n\n", sb->length, sb->data);

    puts("Calling sb_free -- releasing data buffer then struct...");
    sb_free(sb);
    sb = NULL;
    puts("Memory freed successfully. sb is now NULL.");

    return EXIT_SUCCESS;
}