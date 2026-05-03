#pragma once
#include"Tile.h"
#include"Item.h"
#include<random>

enum class ResourceType {
    TREE, //can be only broken by wooden axe
    STONE, //can be only broken by wooden pickaxe
    IRON, //can be only broken by stone pickaxe
    TITANIUM, //can be only broken by iron pickaxe
    BARREL0, //can be broken with hands
    BARREL1, //can be only broken by wooden axe
    BARREL2, //can be only broken by stone axe
    BARREL3, //can be only broken by iron axe
    BARREL4, //can be only broken by titanium axe
    BARREL5 //can be only broken by etherite axe
};

class Breakable : public Tile {
    std::random_device rd;
    std::mt19937 gen;
    protected:
        ResourceType type;
        ItemStack drop;
    public:
        Breakable(ResourceType Type);
};
