#include <stdio.h>
#include <math.h>

#define MAX 1024  // Maximum memory size

int splitBuddy(int size) {
    int buddy = 1;
    while (buddy < size) buddy *= 2;
    return buddy;
}

void buddyAllocation(int blockSize, int requestSize) {
    int originalBlock = blockSize;
    int buddy = splitBuddy(requestSize);

    if (requestSize > blockSize) {
        printf("Request of size %d cannot be allocated in block of size %d.\n", requestSize, blockSize);
        return;
    }

    printf("Original block: %d\n", originalBlock);
    while (buddy < blockSize) {
        blockSize /= 2;
        printf("Split block into: %d and %d\n", blockSize, blockSize);
    }

    printf("Allocated block of size %d for request %d.\n", blockSize, requestSize);
}

int main() {
    int blockSize = MAX;
    int requestSize[] = {200, 300, 50, 600};

    for (int i = 0; i < sizeof(requestSize) / sizeof(requestSize[0]); i++) {
        printf("\nRequest %d:\n", i + 1);
        buddyAllocation(blockSize, requestSize[i]);
    }

    return 0;
}
