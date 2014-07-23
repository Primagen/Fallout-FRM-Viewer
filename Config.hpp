
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

/**
 * Handles reading a config file,
 * and storing its values
 */
class Config {
  public:

    /**
     * Default constructor,
     * initializes data members
     * with default values.
     */
    Config();

    /*
     * Reads the file,
     * stores its data in the members
     */
    bool open(std::string filename);

    /**
     * Accessors...
     */
    unsigned int       getScreenWidth();
    unsigned int       getScreenHeight();
    bool               getVsync();
    unsigned int       getMaxFramerate();
    const std::string& getResourcePath();

  private:
    //TODO: Implement
    /**
     * Helper function
     * To separate from long open() function
     * Would handle the "if (lineL == "screen_width")...etc" stuff
     */
    bool assignValue(std::string lineL);

  private:
    /**
     * Data properties,
     * one for each runtime constant
     */
    unsigned int mScreenWidth;
    unsigned int mScreenHeight;
    bool         mVsync;
    unsigned int mMaxFramerate;
    std::string  mResourcePath;
};

#endif // CONFIG_HPP
