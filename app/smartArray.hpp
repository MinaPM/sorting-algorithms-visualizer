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

    class SmartIndex
    {
    private:
        item &ref;
        MemoryStats &memoryStatsRef;

    public:
        SmartIndex(item &ref, MemoryStats &memoryStatsRef) : ref(ref),
                                                             memoryStatsRef(memoryStatsRef) {}

        operator item() const
        {
            memoryStatsRef.readCount++;
            return ref;
        }

        SmartIndex &operator=(item value)
        {
            memoryStatsRef.writeCount++;
            ref = value;
            return *this;
        }

        friend bool operator==(const SmartIndex &lhs, const SmartIndex &rhs)
        {
            // memoryStatsRef.comparisonCount++;
            return lhs.ref == rhs.ref;
        }

        friend bool operator!=(const SmartIndex &lhs, const SmartIndex &rhs)
        {
            // comparisons++;

            return lhs.ref != rhs.ref;
        }

        friend bool operator<(const SmartIndex &lhs, const SmartIndex &rhs)
        {
            // comparisons++;

            return lhs.ref < rhs.ref;
        }

        friend bool operator>(const SmartIndex &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs.ref > rhs.ref;
        }

        friend bool operator<=(const SmartIndex &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs.ref <= rhs.ref;
        }

        friend bool operator>=(const SmartIndex &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs.ref >= rhs.ref;
        }

        // Comparisons with raw item
        friend bool operator==(const SmartIndex &lhs, const item &rhs)
        {
            // comparisons++;
            return lhs.ref == rhs;
        }
        friend bool operator!=(const SmartIndex &lhs, const item &rhs)
        {
            // comparisons++;
            return lhs.ref != rhs;
        }
        friend bool operator<(const SmartIndex &lhs, const item &rhs)
        {
            // comparisons++;
            return lhs.ref < rhs;
        }
        friend bool operator>(const SmartIndex &lhs, const item &rhs)
        {
            // comparisons++;
            return lhs.ref > rhs;
        }
        friend bool operator<=(const SmartIndex &lhs, const item &rhs)
        {
            // comparisons++;
            return lhs.ref <= rhs;
        }
        friend bool operator>=(const SmartIndex &lhs, const item &rhs)
        {
            // comparisons++;
            return lhs.ref >= rhs;
        }

        friend bool operator==(const item &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs == rhs.ref;
        }
        friend bool operator!=(const item &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs != rhs.ref;
        }
        friend bool operator<(const item &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs < rhs.ref;
        }
        friend bool operator>(const item &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs > rhs.ref;
        }
        friend bool operator<=(const item &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs <= rhs.ref;
        }
        friend bool operator>=(const item &lhs, const SmartIndex &rhs)
        {
            // comparisons++;
            return lhs >= rhs.ref;
        }
    };

public: // operators
    MemoryStats memoryStats;

    SmartIndex operator[](size_t index) { return SmartIndex(items[index], memoryStats); }

    // item &operator[](size_t index)
    // {
    //     return items[index];
    // }

    // const item &operator[](size_t index) const
    // {
    //     return read(index);
    // }

    // // just in case
    // item& read(size_t index)
    // {
    //     readCount++;
    //     return items[index];
    // }

    // void write(size_t index, item value)
    // {
    //     writeCount++;
    //     items[index] = value;
    // }

    // // does both reading and writing depending on the arguments
    // const item access(size_t index, item value = NULL)
    // {
    //     if (value)
    //     {
    //         write(index, value);
    //         return NULL;
    //     }
    //     else
    //     {
    //         return read(index);
    //     }
    // }

    const item &of(size_t index)
    {
        return items[index];
    }

    void swap(size_t index1, size_t index2)
    {

        memoryStats.readCount += 2;
        memoryStats.writeCount += 2;
        memoryStats.auxiliaryMemoryCount++;
        auxiliaryMemory = items[index1];
        items[index1] = items[index2];
        items[index2] = auxiliaryMemory;
    }

    // Range-based for loop support
    auto begin() { return items.begin(); }
    auto end() { return items.end(); }

    auto begin() const { return items.begin(); }
    auto end() const { return items.end(); }

    void resize(size_t newSize) { items.resize(newSize); }
    void resize(size_t newSize, const item &value) { items.resize(newSize, value); }
};

#endif // SMARTARRAY_HPP