#include <stdint.h>
extern uint32_t size;
extern uint32_t _random_array;
extern uint32_t _scrap_array;

uint32_t *random_array = &_random_array;
uint32_t *scrap_array = &_scrap_array;
