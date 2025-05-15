#ifndef MD5_H
#define MD5_H

#include <stdint.h>
#include <stddef.h>

void md5(const char *str, size_t initial_len, uint8_t *digest);

int hash_equals(const uint8_t *a, const uint8_t *b, size_t len);

#endif //MD5_H
