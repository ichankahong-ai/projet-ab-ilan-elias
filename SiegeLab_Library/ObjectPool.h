#pragma once
#include <cstdint>
#include <cstddef>
#include <array>
#include <utility>
#include <optional>

struct EntityId
{
    std::uint32_t slot = 0;
    std::uint32_t generation = 0;
};

template <typename T, std::size_t Capacity>

class ObjectPool {
public:
    template <typename... Args>
    EntityId create(Args&&... args)
    {
        for (std::uint32_t i = 0; i < Capacity; ++i)
        {
            if (!slots_[i].object.has_value())
            {
                slots_[i].object.emplace(std::forward<Args>(args)...);
                ++count_;
                return EntityId{ i, slots_[i].generation };
            }
        }
        return EntityId{};
    }

    bool full() const {
        return count_ == Capacity;
    }

    T* get(EntityId id)
    {
        if (!isValid(id))
            return nullptr;
        return &(*slots_[id.slot].object);
    }

    bool destroy(EntityId id)
    {
        if (!isValid(id))
            return false;
        slots_[id.slot].object.reset();
        --count_;
        slots_[id.slot].generation++;
        return true;
    }

    template <typename F>
    void forEach(F&& f)
    {
        for (std::uint32_t i = 0; i < Capacity; ++i)
        {
            if (slots_[i].object.has_value())
                f(EntityId{ i, slots_[i].generation }, *slots_[i].object);
        }
    }

    void clear()
    {
        for (std::uint32_t i = 0; i < Capacity; ++i)
        {
            if (slots_[i].object.has_value())
            {
                slots_[i].object.reset();
                slots_[i].generation++;
                --count_;
            }
        }
        
    }

    std::size_t size() const { return count_; }
private:
    struct Slot
    {
        std::optional<T> object;
        std::uint32_t generation = 1;
    };

    bool isValid(EntityId id) const
        {
            if (id.slot >= Capacity)
                return false;
    
            const Slot& s = slots_[id.slot];
            return s.object.has_value() && s.generation == id.generation;
        }

    std::array<Slot, Capacity> slots_;
    std::size_t count_ = 0;
};