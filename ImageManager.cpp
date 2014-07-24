
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
    unsigned int colorIndex; ///r, g, b;
    for (int i = 0; i < width*height*4; i+=4)
    {
        colorIndex = colors[i/4];
        //redundant:
        //r = colors[i/4]; //RGB values in the FRM file
        //g = colors[i/4];
        //b = colors[i/4];
        //TODO: Add palette to Image Manager

        /// Handling some support for the hardcoded animation indexes... ///
        if (colorIndex < 229 || colorIndex > 254) //if not an animated index
        {
            pixels[i]   = mPaletteColors[colorIndex].r      * 4;
            pixels[i+1] = mPaletteColors[colorIndex].g      * 4;
            pixels[i+2] = mPaletteColors[colorIndex].b      * 4;
            pixels[i+3] = (colorIndex == 0)? 0 : 255;
        }
        else //we're dealing with an animated index
        {
            //TODO: put into separate function
            switch (colorIndex) {

            //Slime
            case 229:
                pixels[i]   = 0;
                pixels[i+1] = 108;
                pixels[i+2] = 0;
                break;
            case 230:
                pixels[i]   = 11;
                pixels[i+1] = 115;
                pixels[i+2] = 7;
                break;
            case 231:
                pixels[i]   = 27;
                pixels[i+1] = 123;
                pixels[i+2] = 15;
                break;
            case 232:
                pixels[i]   = 43;
                pixels[i+1] = 131;
                pixels[i+2] = 27;
                break;

            //Shoreline
            case 248:
                pixels[i]   = 83;
                pixels[i+1] = 63;
                pixels[i+2] = 43;
                break;
            case 249:
                pixels[i]   = 75;
                pixels[i+1] = 59;
                pixels[i+2] = 43;
                break;
            case 250:
                pixels[i]   = 67;
                pixels[i+1] = 55;
                pixels[i+2] = 39;
                break;
            case 251:
                pixels[i]   = 63;
                pixels[i+1] = 51;
                pixels[i+2] = 39;
                break;
            case 252:
                pixels[i]   = 55;
                pixels[i+1] = 47;
                pixels[i+2] = 35;
                break;
            case 253:
                pixels[i]   = 51;
                pixels[i+1] = 43;
                pixels[i+2] = 35;
                break;

            //Slow fire
            case 238:
                pixels[i]   = 255;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;
            case 239:
                pixels[i]   = 215;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;
            case 240:
                pixels[i]   = 147;
                pixels[i+1] = 43;
                pixels[i+2] = 11;
                break;
            case 241:
                pixels[i]   = 255;
                pixels[i+1] = 119;
                pixels[i+2] = 0;
                break;
            case 242:
                pixels[i]   = 255;
                pixels[i+1] = 59;
                pixels[i+2] = 0;
                break;

            //Fast fire
            case 243:
                pixels[i]   = 71;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;
            case 244:
                pixels[i]   = 123;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;
            case 245:
                pixels[i]   = 123;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;
            case 246:
                pixels[i]   = 71;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;
            case 247:
                pixels[i]   = 71;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;

            //Monitors
            case 233:
                pixels[i]   = 107;
                pixels[i+1] = 107;
                pixels[i+2] = 111;
                break;
            case 234:
                pixels[i]   = 99;
                pixels[i+1] = 103;
                pixels[i+2] = 127;
                break;
            case 235:
                pixels[i]   = 87;
                pixels[i+1] = 107;
                pixels[i+2] = 143;
                break;
            case 236:
                pixels[i]   = 0;
                pixels[i+1] = 147;
                pixels[i+2] = 163;
                break;
            case 237:
                pixels[i]   = 107;
                pixels[i+1] = 187;
                pixels[i+2] = 255;
                break;

            //Alarm
            case 254:
                pixels[i]   = 252;
                pixels[i+1] = 0;
                pixels[i+2] = 0;
                break;
            default:
                std::cout << "Animated colorIndex " << colorIndex << " not handled\n";
                pixels[i]   = 255;
                pixels[i+1] = 255;
                pixels[i+2] = 255;
                break;
            }
            pixels[i+3] = 255; //alpha
        }

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
