#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <concepts>
#include <type_traits>

#include "ObjectPool.h"

class GameEntity
{
public:
    virtual ~GameEntity() = default;
    virtual void draw() = 0;
};

template <typename T>
concept ConcreteEntity = std::derived_from<T, GameEntity> && !std::is_abstract_v<T>;

class SceneObjects {
public:
    template <ConcreteEntity T, typename... Args>
    EntityId createEntity(Args&&... args)
    {
        if (pool_.full())
            return EntityId{};
        return pool_.create(std::make_unique<T>(std::forward<Args>(args)...));
    }

    GameEntity* get(EntityId id)
    {
        auto* p = pool_.get(id);
        if (p == nullptr)
            return nullptr;
        return p->get();
    }

    void flushRemovals()
    {
        for (EntityId id : pending_)
        {
            GameEntity* e = get(id);
            if (e == nullptr)
                continue;
            if (beforeDestroy_)
                beforeDestroy_(*e);
            pool_.destroy(id);
        }
        pending_.clear();
    }

private:

    ObjectPool<std::unique_ptr<GameEntity>, 256> pool_;
    std::vector<EntityId> pending_;
    std::function<void(GameEntity&)> beforeDestroy_;
};
