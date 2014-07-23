
#include "ImageManager.hpp"

#include "BinaryParsing.hpp"
#include "FRM.hpp"

#include <iostream> //cout
#include <map>

ImageManager::ImageManager()
: mPaletteColors(256)
{
    loadPalette();
}

bool ImageManager::loadPalette()
{
    std::ifstream f("color.pal", std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cout << "Error opening color.pal.\n";
        return false;
    }

    int r, g, b;
    std::cout << "Palette size: " << mPaletteColors.size() << std::endl;
    for (int i = 0; i < mPaletteColors.size(); i++)
    {
        r = bendian::read_u8(f);
        g = bendian::read_u8(f);
        b = bendian::read_u8(f);
        //std::cout << "RGB: " << r << " " << g << " " << b << std::endl;
        mPaletteColors[i] = sf::Color(r, g, b);
    }
    return true;
}

const sf::Texture& ImageManager::getTexture(const std::string& frm_name)
{
    for( std::map<std::string, sf::Texture*>::const_iterator it = mTextureMap.begin();
         it != mTextureMap.end(); ++it)
    {
        if( frm_name == it->first)
        {
            std::cout << "Using existing texture...\n";
            return *it->second;
        }
    }
    //At this point, texture doesn't exist
    std::cout << frm_name << " is not in the map! Creating new texture...\n";

    //create texture
    //add to object's map
    //return texture (don't want to return a local reference...)
    FRM frm;
    if (!frm.open(frm_name))
    {
        std::cout << "Error opening frm...\n";
        frm.open("reserved");
    }
        //return an error texture to put onto the sprite
    int width  = frm.getWidth();
    int height = frm.getHeight();
    const std::vector<int>& colors = frm.getColors();
    std::cout << "colors size: "  << colors.size() << std::endl;
    std::cout << "width: "        << width         << std::endl;
    std::cout << "height: "       << height        << std::endl;
    std::cout << "width*height: " << width*height  << std::endl;

    sf::Texture *texture = new sf::Texture;
    texture->create(width, height);

    /**
     * Creates each pixel for the current FRM's image,
     * using the pixel data from the FRM
     */ //note see also http://www.codeproject.com/Tips/527353/Load-an-HBITMAP-into-SFML-sf-Image-container
    std::vector<sf::Uint8> pixels(width * height * 4); //*4 because SFML's rgba format
    unsigned int r, g, b;
    for (int i = 0; i < width*height*4; i+=4)
    {
        r = colors[i/4];
        g = colors[i/4];
        b = colors[i/4];
        //TODO: Add palette to Image Manager
        pixels[i]   = mPaletteColors[r].r      * 4;
        pixels[i+1] = mPaletteColors[g].g      * 4;
        pixels[i+2] = mPaletteColors[b].b      * 4;
        pixels[i+3] = (r == 0 && g == 0 && b == 0)? 0 : 255;
    }
    texture->update(&pixels[0]);

    //mTextureMap.insert( std::pair<std::string, sf::Texture*>::value_type(frm_name, texture) );
    mTextureMap[frm_name] = texture;
    //delete texture;  //Deleted in deleteAll()
    return *mTextureMap[frm_name];
}

void ImageManager::deleteSingle()
{
    std::cout << "Single delete not implemented yet.\n";
    //TODO:
    /*   When a user presses delete over a sprite,
    /    they would most likely want just that sprite to be deleted.
    / The FRM Viewer class needs to check if the deleted sprite
    / was the last instance of the texture the sprite was using
    / If it is, it calls this function
    / but how does it know which texture?*/
}

void ImageManager::deleteAll()
{
    std::vector<std::string>::const_iterator itIL;
    for (std::map<std::string, sf::Texture *>::iterator it = mTextureMap.begin(); it != mTextureMap.end();)
    {
        std::cout << "delete called!\n";
        delete it->second;
        mTextureMap.erase(it++);
    }
}
