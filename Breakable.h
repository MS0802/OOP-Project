#include"Tile.h"

enum class ResourceType {
    TREE,
    STONE,
    IRON,
    TITANIUM
};

class Breakable : public Tile {
    protected:
        ResourceType type;
    public:
        Breakable(ResourceType Type);
};
