
#include "Config.hpp"

#include <iostream>
#include <fstream>
#include <cstddef> // std::size_t
#include <cctype>  // isspace
#include <cstdlib> // atoi()
#include <algorithm> //remove_if
#include <stdexcept> //exceptions

Config::Config()
{
    //defaults if it fails to read config?
    mScreenWidth  = 800;
    mScreenHeight = 600;
    mVsync = false;
    mMaxFramerate = 100;
    mResourcePath = "./art";
}

bool Config::open(std::string filename)
{

    std::ifstream f(filename);
    if (!f.is_open())
    {
        std::cout << "Error opening " << filename << "!\n";
        return false;
    }

    std::string line;
    std::string lineL;
    std::string lineR;
    std::size_t equal_sign_pos;
    std::size_t comment_pos;
    while (getline(f, line))
    {
        //REMOVE WHITESPACE
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        //REMOVE START-OF-LINE COMMENT
        if ((line.length() > 0 && line[0] == '#') || line.length() == 0)
            continue;

        //CHECK FOR '=' AND PROCESS
        equal_sign_pos = line.find('=');
        if (equal_sign_pos == std::string::npos)
        {
            //TODO: Make this go into a log.
            std::cout << "Error while parsing. Check for missing =.\n";
            return false;
        }

        //LEFT-SIDE INFORMATION
        lineL = line.substr(0, equal_sign_pos);
        if (lineL.length() == 0)
        {
            std::cout << "Error while parsing. Check for missing data before =.\n";
            return false;
        }
        std::cout << lineL;// << std::endl;

        //RIGHT-SIDE INFORMATION +
        //REMOVE END-OF-LINE COMMENTS
        lineR = line.substr(equal_sign_pos+1);
        comment_pos = lineR.find('#');
        if (comment_pos != std::string::npos)
            lineR = lineR.substr(0, comment_pos);
        if (lineR.length() == 0)
        {
            std::cout << "Error while parsing. Check for missing data after =.\n";
            return false;
        }
        std::cout << lineR << std::endl;


        ///////////////////////////////////////
        //  ASSIGN DATA TO CLASS PROPERTIES  //
        //  * This could be a good place     //
        //  * to practice inheritance        //
        ///////////////////////////////////////
        if (lineL == "screen_width")
        {
            mScreenWidth = atoi(lineR.c_str());
        }
        else if (lineL == "screen_height")
        {
            mScreenHeight = atoi(lineR.c_str());
        }
        else if (lineL == "vsync")
        {
            //sets vsync to false unless it's explicitly "true/on/1"
            mVsync = (lineR=="true"||lineR=="on"||lineR=="1");
        }
        else if (lineL == "max_fps")
        {
            mMaxFramerate = atoi(lineR.c_str());
        }
        else if (lineL == "frm_path")
        {
            mResourcePath = lineR;
        }
        else
        {
            std::cout << "Error, unknown left-side variable \""<< lineL <<"\"\n";
            return false;
        }
    }
    return true;
}

unsigned int Config::getScreenWidth()
{
    return this->mScreenWidth;
}
unsigned int Config::getScreenHeight()
{
    return this->mScreenHeight;
}
bool Config::getVsync()
{
    return this->mVsync;
}
unsigned int Config::getMaxFramerate()
{
    return this->mMaxFramerate;
}
const std::string& Config::getResourcePath()
{
    return this->mResourcePath;
}
