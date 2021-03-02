#include <assert.h>
#include "Matrix.h"


using namespace std;

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);

    m.modify(1,2,3);
    assert(m.element(1, 2) == 3);
    int e;
    e =m.modify(1, 1, 0);
    assert(e == 6);

}