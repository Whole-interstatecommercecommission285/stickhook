#ifndef STICKHOOK_H
#define STICKHOOK_H

#define CONCAT(a, b) __CONCAT(a, b)

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STICK_HEADSIZE 8
#define STICK_JUMPSIZE 16
#define STICK_RESSIZE  (STICK_HEADSIZE + STICK_JUMPSIZE)

struct stick_entry {
    char *image_name;
    uint64_t vmaddr;
    void *replacement;
    void *original;
    uint64_t reserved;
};

void stickhook_init(void);

/*
void stick_hook(char *image_name, intptr_t vmaddr, void *replacement, void **originptr);
*/
#define stick_hook(_image_name, _vmaddr, _replacement, _originptr)                                                                                                                                                              \
    __attribute__((used, section("__TEXT,__text"))) static const unsigned char CONCAT(_stickhook_origin_, __LINE__)[STICK_RESSIZE];                                                                                             \
    __attribute__((used, section("__DATA,__stick_info"))) static const struct stick_entry CONCAT(_stickhook_entry_, __LINE__) = {_image_name, _vmaddr, (void *)(_replacement), (void *)CONCAT(_stickhook_origin_, __LINE__)};   \
    *(const void **)(_originptr) = CONCAT(_stickhook_origin_, __LINE__);

/*
void stick_replace(char *image_name, intptr_t vmaddr, void *replacement);
*/
#define stick_replace(_image_name, _vmaddr, _replacement)                                                                                                                                                                       \
    __attribute__((used, section("__DATA,__stick_info"))) static const struct stick_entry CONCAT(_stickhook_entry_, __LINE__) = {_image_name, _vmaddr, (void *)(_replacement)};

#ifdef __cplusplus
}
#endif

#endif
