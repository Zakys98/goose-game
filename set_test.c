#include "set.h"
#include "types.h"

#include <stdlib.h>
#include <assert.h>

int main() {
    Set *s;
    assert(s == NULL);
    assert(set_get_size(s) == -1);
    s = set_create();
    assert(s != NULL);
    assert(set_get_size(s) == 0);

    set_add(s, 1);
    set_add(s, 2);
    set_add(s, 3);
    assert(set_get_size(s) == 3);

    set_add(s, 1);
    set_add(s, 1);
    assert(set_get_size(s) == 3);

    set_add(s, 15);
    set_add(s, 23);
    set_add(s, 222);
    assert(set_get_size(s) == 6);

    return 0;
}