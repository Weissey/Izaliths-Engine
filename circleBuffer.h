#pragma once
#include <cstdint>




template <typename T>
class circularBuffer {

public:
	T* buffer;
	int count; //of the buffer
	int max; //of the buffer

	circularBuffer(int bufferSize) : max(bufferSize), count(0) {
		buffer = new T[max];
	}

	~circularBuffer() {
		delete[] buffer;
	}

    void write(T i) {
		buffer[count] = i;
		count = (count + 1) % max;
    }

	T* write_ptr(size_t i) {
		//std::cout << i << std::endl;
		return &buffer[i % max];
	}

	T read() {
		return buffer[count % max];
	}

    // Read data from the buffer
    T read(size_t i) {
		return buffer[i % max];
    }

};

