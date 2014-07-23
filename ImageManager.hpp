
/**
 * Image Manager, to work with FRM images.
 * Made to prevent making multiple Textures
 * for the same, repeated sprite
 *
 * Made with help from:
 * https://github.com/LaurentGomila/SFML/wiki/Tutorial:-Image-Manager
 */

#ifndef IMAGE_MANAGER_HPP
#define IMAGE_MANAGER_HPP

#include <SFML/Graphics.hpp>

/**
 * TODO: class FRM_TextureManager : public ResourceManager
 *
 * TODO: Make all things be tolower() so that it wouldn't load 'ROCK01' differently form 'rock01'
 */
 // *Texture* Manager instead? Not dealing with sf::Image
class ImageManager {
  public:

    /**
     * Constructor
     * Initializes mPaletteColors with a size of 256.
     * Loads Palette file
     */
    ImageManager();

    /**
     * Loads information from color.pal into mPaletteColors
     * TODO: Set path for color.pal in Config
     */
    bool loadPalette();

    /**
     * Returns reference to a texture,
     * would normally be used to set
     * the correct texture to a sprite.
     */
    const sf::Texture& getTexture(const std::string& frm_name) /*const*/;

    /**
     * TODO: Implement
     * Would delete the texture a certain sprite was using
     * if that sprite was the last one to be using the texture
     */
    void deleteSingle();

    /**
     * Frees memory for all dynamically allocated textures.
     * FRM Viewer class is still responsible for removing the
     * sprites that would be using the deleted texture.
     */
    void deleteAll();
    //typedef std::string value_type;
    //typedef const std::string &const_reference;

  private:
    std::vector<sf::Color> mPaletteColors;
    std::vector<sf::Texture> mTextures;
    std::map<std::string, sf::Texture*> mTextureMap;

};

#endif // IMAGE_MANAGER_HPP
