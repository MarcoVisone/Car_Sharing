#ifndef MD5_H
#define MD5_H

#include <stdint.h>
#include <stddef.h>

void md5(const char *str, size_t initial_len, uint8_t *digest);

int confronta_hash(uint8_t *hash_1, uint8_t *hash_2);

#endif //MD5_H
