

 /******************************************\
 *       Uses SFML 2.1                      *
 *     http://sfml-dev.org/                 *
 *     http://sfml-dev.org/download.php     *
 *     SFML is made by Laurent Gomila       *
 \******************************************/

#include "FRMViewer.hpp"
#include "Config.hpp"

#include <iostream>

/**
 * Loads and runs the FRM Viewer class
 * Color Palette loading is done in the Image Manager
 *
 * TODO: Should Config aggregate the FRMViewer class,
 * or should we just put the Config's properties into
 * the FRMViewer during construction.
 * The latter seems redundant, but...
 *
 * There is probably an sf::RenderWindow::getWidth/Height
 * functions, this is probably sufficient for the sprite placement
 */
int main()
{
    Config config;
    if (!config.open("./data/viewer.cfg"))
    {
        std::cout << "Error reading data/viewer.cfg...\n";
        return -1;
    }
    std::cout << "Configuration file read.\n";
    FRMViewer viewer(config);
    viewer.run();

    //generate log
    //return -2 if unable to save log

    return 0;
}
