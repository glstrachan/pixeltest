// This implementation is based on the Mach ECS system implemented by Stephen Gutenkanst

#pragma once

#include <map>
#include <string>
#include <vector>

typedef uint64_t EntityID;

// Type erased component storage
class ErasedComponentStorage {
  public:
    template <typename Component> ComponentStorage<Component> &cast() {
        return *dynamic_cast<ComponentStorage<Component> *>(this);
    }

    virtual ~ErasedComponentStorage() {}
};

template <typename Component> class ComponentStorage : public ErasedComponentStorage {
  public:
    uint64_t &totalRows;
    vector<Component> data;
};

// Represents all entities that have the same set of component type
class ArchetypeStorage {
  private:
    // The hash for this archetype
    uint64_t hash;
    // Maps a components name to where we store it in memory
    std::map<std::string, ErasedComponentStorage> components;

    std::vector<EntityID> entityIDs;

  public:
    ArchetypeStorage(uint64_t hash) : hash(hash) {}
    ~ArchetypeStorage() {}

    uint32_t newEntity(EntityID id) {
        entityIDs.push_back(id);
        return entityIDs.size() - 1;
    }

    void undoNewEntity() { entityIDs.pop_back(); }
};

class ArchetypePointer {
  public:
    std::map<uint64_t, ArchetypeStorage>::iterator archetypeIndex;
    uint32_t rowIndex;
};

class Entities {
  private:
    static const uint64_t voidArchetypeHash = std::numeric_limits<uint64_t>::max();
    std::map<uint64_t, ArchetypeStorage> archetypes;

    EntityID counter = 0;

    // Maps from entity id to the archetype table it belongs to
    std::map<EntityID, ArchetypePointer> entities;

  public:
    Entities() { archetypes[voidArchetypeHash] = ArchetypeStorage(voidArchetypeHash); }
    ~Entities() {}

    EntityID newEntity() {
        EntityID id = counter++;

        uint32_t row = archetypes[voidArchetypeHash].newEntity(id);
        ArchetypePointer pointer = {archetypes.begin(), row};

        entities[id] = pointer;

        return id;
    }
};