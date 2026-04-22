#include"Breakable.h"

Breakable::Breakable(ResourceType Type) : 
Tile(TileType::RESOURCE, false, true), type(Type) {}
