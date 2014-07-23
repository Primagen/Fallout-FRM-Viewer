
#ifndef FRM_VIEWER_HPP
#define FRM_VIEWER_HPP

#include "ImageManager.hpp"
#include "Config.hpp"

#include <SFML/Graphics.hpp>

/**
 * Main, big class used by the program
 * Handles window, update logic, user input
 *
 * TODO: mSprites sorted by layer!!!
 *       +/- to shift a sprite up/down a layer!!!
 *          would use mCurrSpriteIndex
 *       Get rid of ScreenWidth, that's from config
 *       Put palette in /data
 *       Animated palette stuff
 *       Support for .png+.fofrm file pairs
 *
 *  Use C# WFA for an optional config UI (separate program)
 *   FRM_config.exe
 */
class FRMViewer {

  public:
    FRMViewer();
    FRMViewer(Config config);
    void run();
    static const int ScreenWidth  = 600;
    static const int ScreenHeight = 400;

  private:

    /**
     * TODO: Group common things from the two ctors
     */
    void init();

    void handleUserInput(sf::Keyboard::Key key, bool isPressed);
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void onClick();
    void onResize();
    void loadPalette();

  private:
    static const sf::Time TimePerFrame;
    bool vsync;
    sf::RenderWindow mWindow;
    sf::View mView;

    bool mLoad;
    bool mReset; //not used?
    bool mDelete;

    bool mEscape; //used for shortcut to exit
    bool mShift;

    /**
     * TODO:
     * To handle overlapping sprites when dragging and drawing
     * it needs to go through the for loop in a sorted order,
     * sorted from "top-layer" to "bottom-layer"
     */
    ImageManager mImageManager;
    std::vector<sf::Sprite> mSprites;

    bool mDrawOutline;
    sf::RectangleShape mOutline;

    //Sprites Click and Drag stuff:
    sf::Vector2i mMousePos;
    sf::Vector2f mDiff;
    bool mClick;
    bool mDrag;
    int mCurrSpriteIndex;

    sf::RectangleShape mTestPoint;
};

#endif // FRM_VIEWER_HPP
