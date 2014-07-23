
#include "FRMViewer.hpp"

#include <iostream>

const sf::Time FRMViewer::TimePerFrame = sf::seconds(1.f/60.f);

/**
 * Don't use this ctor
 */
FRMViewer::FRMViewer()
: vsync(true)
, mWindow(sf::VideoMode(ScreenWidth, ScreenHeight), "FRM Viewer")
, mLoad(false)
, mReset(false)
, mShift(false)
, mEscape(false)
, mDrawOutline(false)
, mClick(false)
, mDrag(false)
, mDelete(false)
, mCurrSpriteIndex(0)
, mImageManager() //loads palette
, mMousePos(0, 0)
{
    if (vsync)
        mWindow.setVerticalSyncEnabled(true);
    else
        mWindow.setFramerateLimit(80); // change to 1.0/TimePerFrame

    mOutline.setFillColor(sf::Color::Transparent);
    mOutline.setOutlineThickness(2.0f);
    mOutline.setOutlineColor(sf::Color::Red);
    mView = mWindow.getView();

    mTestPoint.setFillColor(sf::Color::Magenta);
    mTestPoint.setSize(sf::Vector2f(4.f, 4.f));

    //Nothing else for now
    //If user presses L, console will prompt user to type filename
}

FRMViewer::FRMViewer(Config config)
: vsync(config.getVsync())
, mWindow(sf::VideoMode(config.getScreenWidth(), config.getScreenHeight()), "FRM Viewer")
, mLoad(false)
, mReset(false)
, mShift(false)
, mEscape(false)
, mDrawOutline(false)
, mClick(false)
, mDrag(false)
, mDelete(false)
, mImageManager() // loads Palette
, mCurrSpriteIndex(0)
, mMousePos(0, 0)
{
    if (vsync) //probably don't even need to store a vsync variable...
        mWindow.setVerticalSyncEnabled(true);
    else
        mWindow.setFramerateLimit(config.getMaxFramerate());

    mOutline.setFillColor(sf::Color::Transparent);
    mOutline.setOutlineThickness(2.0f);
    mOutline.setOutlineColor(sf::Color::Red);
    mView = mWindow.getView();

    mTestPoint.setFillColor(sf::Color::Magenta);
    mTestPoint.setSize(sf::Vector2f(4.f, 4.f));

    //Nothing else for now
    //If user presses L, console will prompt user to type filename
}

void FRMViewer::init()
{
    std::cout << "Error, init function not implemented yet.\n";
}

void FRMViewer::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void FRMViewer::handleUserInput(sf::Keyboard::Key key, bool isPressed)
{
    //separate handling 1-hit keys vs handling
    //keys that are held down for an extended duration (like movement)

    if (key == sf::Keyboard::L)
        mLoad = isPressed;
    else if (key == sf::Keyboard::Delete)
        mDelete = isPressed;
    else if (key == sf::Keyboard::LShift)
        mShift = isPressed;
    else if (key == sf::Keyboard::Escape)
        mEscape = isPressed;
}

void FRMViewer::processEvents()
{
    sf::Event event;
	while (mWindow.pollEvent(event))
	{
	    switch(event.type)
		{
            case sf::Event::MouseButtonPressed:
                mClick = true;
                break;
            case sf::Event::MouseButtonReleased:
                mClick = false;
                mDrag = false;
                break;
            case sf::Event::MouseMoved:
                mMousePos.x = event.mouseMove.x;
                mMousePos.y = event.mouseMove.y;
                break;
            case sf::Event::MouseLeft:
                mClick = false;
                mDrag = false;
                break;
		    case sf::Event::KeyPressed:
			    handleUserInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
			    handleUserInput(event.key.code, false);
				break;
            case sf::Event::Resized:
                onResize();
                break;
			case sf::Event::Closed:
			    mImageManager.deleteAll();
			    mWindow.close();
				break;
            default:
                break;
		}
	}
}

void FRMViewer::update(sf::Time deltaTime)
{
    /////////////////////////////////////////
    ///  Mouse movement + click-and-drag  ///
    /////////////////////////////////////////
    if (mClick)
        onClick();
    else
        mDiff = sf::Vector2f(0.f, 0.f);

    /**
     * TODO: open function's filename should know
     * what the Config's frm_path is.
     *
     * Easiest way to get this interaction would be
     * to store the frm_path in the FRMViewer class itself
     */
    if (mLoad)
    {
        std::cout << "\nEnter name of FRM to load\n:";
        std::string filename;
        std::cin >> filename;

        /**
         * Should the FRM be loaded on the fly
         * Or should all in "FRMS.LST" be loaded on start up?
         */
        sf::Sprite temp_sprite(mImageManager.getTexture(filename));
        mSprites.push_back(temp_sprite);

        mLoad = false; // I don't think this is necessary
                       // Won't matter once proper UI is set up
    }
    else if (mShift && mEscape)
        mWindow.close(); //onExit()?

    else if (mDelete)
    {
        mSprites.clear();
        mImageManager.deleteAll();
    }

    mTestPoint.setPosition(static_cast<sf::Vector2f>(mMousePos));
}

void FRMViewer::render()
{
    mWindow.clear(sf::Color::Cyan);
    mWindow.setView(mView);

    for (int i = 0; i < mSprites.size(); i++)
        mWindow.draw(mSprites[i]);
    if (mDrawOutline)
        mWindow.draw(mOutline);

    //mWindow.draw(mTestPoint);
	mWindow.display();
}

void FRMViewer::onResize()
{
    sf::Vector2f size = static_cast<sf::Vector2f>(mWindow.getSize());
    mView.setCenter(size/2.f);
    mView.setSize(size.x, size.y); // = sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y));
    mWindow.setView(mView);
}

/**
 * Seems to be conflicting with vsync
 * Apparently even some AAA games have this problem, too...
 * Solution for now is to have vsync off by default,
 * may bring up processing though
 */
void FRMViewer::onClick()
{
    if (!mDrag)
        mDrawOutline = false;
    for (int i = 0; i < mSprites.size(); i++)
    {
        sf::FloatRect sprite_rect = mSprites[i].getGlobalBounds();
        if (sprite_rect.contains(mWindow.mapPixelToCoords(mMousePos, mView)))
        {
            mDrawOutline = true;
            if (!mDrag)
            {
                mDrag = true;
                mCurrSpriteIndex = i;
            }
        }
    }
    if (mDrag)
    {
        if (mDiff.x == 0.f && mDiff.y == 0.f)
        {
            mDiff.x = mMousePos.x - mSprites[mCurrSpriteIndex].getPosition().x;
            mDiff.y = mMousePos.y - mSprites[mCurrSpriteIndex].getPosition().y;
        }
        mSprites[mCurrSpriteIndex].setPosition(mMousePos.x - mDiff.x,
                                               mMousePos.y - mDiff.y);
    }
    //mDiff resetting handled in update()

    if (mDrawOutline)
    {
        sf::FloatRect sprite_rect = mSprites[mCurrSpriteIndex].getGlobalBounds();
        mOutline.setPosition(mSprites[mCurrSpriteIndex].getPosition());
        mOutline.setSize(sf::Vector2f(sprite_rect.width, sprite_rect.height));
    }
}
