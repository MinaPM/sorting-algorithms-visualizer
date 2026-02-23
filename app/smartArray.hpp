#ifndef SMARTARRAY_HPP
#define SMARTARRAY_HPP
#include <vector>

class MemoryStats
{
public:
    mutable unsigned int
        readCount = 0,
        writeCount = 0,
        auxiliaryMemoryCount = 0,
        comparisonCount = 0;

    unsigned int getReadCount() { return readCount; }
    unsigned int getWriteCount() { return writeCount; }
    unsigned int getAuxiliaryMemoryCount() { return auxiliaryMemoryCount; }
    unsigned int getComparisonCount() { return comparisonCount; }

    void read(int count = 1) { readCount += count; }
    void write(int count = 1) { writeCount += count; }
    void auxMem(int count = 1) { auxiliaryMemoryCount += count; }
    void compare(int count = 1) { comparisonCount += count; }

    std::string to_string()
    {
        return "Memory reads: " + std::to_string(readCount) +
            "\nMemory writes: " + std::to_string(writeCount) +
            "\nAuxiliary Memory needed: " + std::to_string(auxiliaryMemoryCount);
    }

    void resetStats()
    {
        readCount = 0;
        writeCount = 0;
        auxiliaryMemoryCount = 0;
        comparisonCount = 0;
    }
};

template <typename item>
class SmartArray
{
private:
    std::vector<item> items;
    item auxiliaryMemory;

public:
    size_t length() { return items.size(); }

public: // operators
    MemoryStats memoryStats;

    item& operator[](size_t index)
    {
        return items[index];
    }

    // just in case
    item& read(size_t index)
    {
        memoryStats.read();
        return items[index];
    }

    void write(size_t index, item value)
    {
        memoryStats.write();
        items[index] = value;
    }

    // does both reading and writing depending on the arguments
    const item access(size_t index, item value = NULL)
    {
        if (value)
        {
            write(index, value);
            return NULL;
        }
        else
        {
            return read(index);
        }
    }

    void swap(size_t index1, size_t index2)
    {
        memoryStats.read(2);
        memoryStats.write(2);
        // memoryStats.auxiliaryMemoryCount++;
        auxiliaryMemory = items[index1];
        items[index1] = items[index2];
        items[index2] = auxiliaryMemory;
    }

    void shuffle()
    {
        std::mt19937 gen(std::random_device{}());
        std::iota(items.begin(), items.end(), 1);
        std::shuffle(items.begin(), items.end(), gen);
    }

    // Range-based for loop support
    auto begin() { return items.begin(); }
    auto end() { return items.end(); }

    auto begin() const { return items.begin(); }
    auto end() const { return items.end(); }

    void resize(size_t newSize)
    {
        items.resize(newSize);
        shuffle();
    }

    void resize(size_t newSize, const item& value)
    {
        items.resize(newSize, value);
        shuffle();
    }
};

#endif // SMARTARRAY_HPP
