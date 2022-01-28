#ifndef _BOMBERMAN_MANAGERS_ASSET_MANAGER_H_
#define _BOMBERMAN_MANAGERS_ASSET_MANAGER_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <memory>
#include <string>
#include <unordered_map>

#include "../GameTextures.h"
#include "../Skins.h"
/**
    * @brief Enumeration for Texture
    *
    * @see getTexture
    */
//enum class Texture : int
//{
//    MenuBack,
//    Metal,
//    Stone,
//    Grass,
//    Brick,
//    Player,
//    Enemy1,
//    Enemy2,
//    Enemy3,
//    Bomb,
//    Explosion,
//    Door
//};

/**
    * @brief Enumeration for Music
    *
    */
enum class MusicEnum : int
{
    MainMenu,
    Credits,
    Level
};
/**
    * @brief Enumeration for Sounds
    *
    */
enum class SoundEnum : int
{
    Win,
    Lose,

    Teleport,
    Vida,
    AntiVida,
    Tortuga,
    AntiTiempo,
    Door,
    Velocidad,
    Tiempo,

    Explosion
};
/**
    * @brief Hash for Texture enum
    *
    */
struct EnumClassHash
{
    template<typename T> std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

/**
    * @brief Asset Manager
    *
    */
class AssetManager
{
    public:
    /**
        * @brief Load assets
        *
        * @param renderer - SDL2 Renderer
        */
    void load(SDL_Renderer* renderer);
    
    /**
        * @brief Get font
        *
        * @return std::shared_ptr<TTF_Font> - loaded font
        */
    std::shared_ptr<TTF_Font> getFont() const;
    std::shared_ptr<TTF_Font> getFont1() const;
    std::shared_ptr<TTF_Font> getFont2() const;
    /**
        * @brief Get textures
        *
        * @param texture - texture enumerator
        *
        * @return std::shared_ptr<SDL_Texture> - loaded texture
        */
    std::shared_ptr<SDL_Texture> getTexture(GameTexture texture);
    /**
        * @brief Get music
        *
        * @param music - music enumerator
        * @return std::shared_ptr<Mix_Music> - loaded music
        */
    std::shared_ptr<Mix_Music> getMusic(MusicEnum music);
    /**
        * @brief Get sound
        *
        * @param sound - sound enumerator
        * @return std::shared_ptr<Mix_Chunk> - loaded sound
        */
    std::shared_ptr<Mix_Chunk> getSound(SoundEnum sound);

    private:
    /**
        * @brief load font
        *
        */
    void loadFont();
    void loadFont1();
    void loadFont2();
    /**
        * @brief load textures
        *
        * @param renderer - SDL2 renderer
        * @param texture - texture enumerator
        * @param filePath - path to file with texture
        */
    void loadTexture(SDL_Renderer* renderer, GameTexture texture, const std::string& filePath);
    /**
        * @brief load music
        *
        * @param music - music enumerator
        * @param filePath - path to file with music
        */
    void loadMusic(MusicEnum music, const std::string& filePath);
    /**
        * @brief load sounds
        *
        * @param sound - sound enumerator
        * @param filePath - path to file with sound
        */
    void loadSound(SoundEnum sound, const std::string& filePath);

    std::shared_ptr<TTF_Font> font = nullptr;                                          // font
    std::shared_ptr<TTF_Font> font1 = nullptr;
    std::shared_ptr<TTF_Font> font2 = nullptr;
    std::unordered_map<GameTexture, std::shared_ptr<SDL_Texture>, EnumClassHash> textures; // map of textures
    std::unordered_map<MusicEnum, std::shared_ptr<Mix_Music>, EnumClassHash> musics;       // map of music
    std::unordered_map<SoundEnum, std::shared_ptr<Mix_Chunk>, EnumClassHash> sounds;       // map of sounds
};

#endif // _BOMBERMAN_MANAGERS_ASSET_MANAGER_H_
