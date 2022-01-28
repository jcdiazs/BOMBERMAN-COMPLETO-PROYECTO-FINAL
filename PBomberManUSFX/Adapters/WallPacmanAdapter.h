#pragma once
#include "../Entities/GameActor.h"
#include "../Adapters/WallPacman.h"
#include "../Adapters/Tile.h"
#include "../Adapters/TextureManager.h"
#include "../Adapters/TileGraph.h"

class WallPacmanAdapter :
    public GameActor, public WallPacman
{
public:
    static bool clipsCreated;
    //static TileGraph* tileGraph;// = new TileGraph(25, 15);

    WallPacmanAdapter(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer, Tile* _tile);
    virtual void update(const unsigned int delta) override;
    virtual void render(const SDL_Rect& camera);
};

inline Texture* loadWallTexture() {
    Texture* wallTexture = new Texture();
    wallTexture->LoadFromImage("resources/wall_sprite.bmp");
    return wallTexture;
}

inline bool initiliceClips() {
    if (!WallPacmanAdapter::clipsCreated) {
        //TileGraph::TileGraph(25, 15);
        WallPacman::CreateClips();
        //std::cout << "into initiliceClips() " << "WallPacmanAdapter::clipsCreated: " << WallPacmanAdapter::clipsCreated << std::endl;
    }
    return true;
}