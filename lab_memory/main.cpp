#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "allocator.h"
#include "fileio.h"
#include "letter.h"
#include "room.h"

using namespace std;

/**
 * Main routine.
 * Creates an Allocator object and allocates the students.
 */
int main() {
    cout << endl;

    fileio::init();
    Allocator theAllocator("students.txt", "rooms.txt");
    theAllocator.allocate();
    theAllocator.printRooms();
    fileio::halt();

    cout << endl;
    return 0;
}
