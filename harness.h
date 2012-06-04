#ifndef __HARNESS_H__
#define __HARNESS_H__
#include <stdint.h>
void harness_error(uint32_t code, char *message);
void harness_info(uint32_t code, char *message);
#endif /* __HARNESS_H__ */
