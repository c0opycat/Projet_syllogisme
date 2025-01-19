#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdbool.h>
#include "types.h"

void clear_input_buffer();

MYVAL myfgets(MYPCHAR chaine);

MYPCHAR read_str();
MYCHAR read_char();
MYVAL read_int();

#endif