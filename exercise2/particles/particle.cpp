
#include "particle.h"
#include <iostream>
#include <cstdlib>

class MallocStaticBuffer {
    Particle* stuff;
    Particle* current;
    size_t size;
    size_t maxSize;

public:
    explicit MallocStaticBuffer(std::size_t initial = 1048576): stuff(nullptr), current(nullptr), size(0), maxSize(1048576) {
        allocate_static_memory(initial);
    }
    ~MallocStaticBuffer() {
        std::free(stuff);
    }
    void* nextElement() {
        size_t new_size = size + sizeof(Particle);
        if (new_size >= maxSize) {
            std::cout << "return nullptr because all memory is used" << std::endl;
            return nullptr;
        } else {
            std::cout << "Use allocated mem chunk " << new_size << "/" << maxSize << std::endl;
            size = new_size;
            return current++;
        }
    }
    void previousElement() {
        size_t new_size = size - sizeof(Particle);
        std::cout << "Deleted a particle, now using " << new_size << "/" << maxSize << std::endl;
        size = new_size;
        current--;
    }
private:
    void allocate_static_memory(std::size_t mem_size) {
        stuff = static_cast<Particle*>(std::malloc(mem_size));
        current = stuff;
        size = 0;
        maxSize = mem_size;
    }
};

MallocStaticBuffer memBlock = MallocStaticBuffer();

static void* Particle::operator new(std::size_t sz) noexcept {
    return memBlock.nextElement();
};

static void Particle::operator delete(void *ptr) noexcept {
    memBlock.previousElement();
};
