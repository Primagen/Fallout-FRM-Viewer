
#ifndef FRM_HPP
#define FRM_HPP

#include <vector>
#include <cstdint>
#include <fstream>

/**
 * Holds data for a single Fallout .frm file,
 * see http://fallout.wikia.com/wiki/FRM_files
 *
 * TODO: Some of the "shift" variables should be
 * correctly read as signed int16_t or whatever the case is.
 * This is important to fix for the Mapper! Not so important for the Viewer.
 */
class FRM {
  public:

    /**
     * Default ctor, maybe should initialize properties
     * with -1 or 0 values, but does nothing right now.
     */
    FRM();

    /**
     * Loads a new FRM to be displayed.
     * Return false if not able to correctly parse file
     *
     * Also, clears current mColors256 vector so that it can
     * correctly push_back more elements
     */
    bool open(std::string filename);

    int getWidth()  const;
    int getHeight() const;
    const std::vector<int>& getColors() const;

  private:
    /**
     * TODO: Better, unified naming convention...
     */
    unsigned int mVersion;
    unsigned int mFPS;
    unsigned int mActionFrame;
    unsigned int mNumFramesPerDirection;

    unsigned int mShiftX0;
    int mShiftX1;
    int mShiftX2;
    int mShiftX3;
    int mShiftX4;
    int mShiftX5;

    int mShiftY0;
    int mShiftY1;
    int mShiftY2;
    int mShiftY3;
    int mShiftY4;
    int mShiftY5;

    unsigned int mOffsetF1_0;
    unsigned int mOffsetF1_1;
    unsigned int mOffsetF1_2;
    unsigned int mOffsetF1_3;
    unsigned int mOffsetF1_4;
    unsigned int mOffsetF1_5;

    unsigned int mFSize;

    unsigned int mF0_pixelWidth;
    unsigned int mF0_pixelHeight;
    unsigned int mF0_pixelArea;

    int mOffsetX_F0;
    int mOffsetY_F0;

    /**
     * Size of this vector should be equal to mF0_pixelArea;
     * ex: Tiles will have size 80*36
     */
    std::vector<int> mColors256;
};

#endif // FRM_HPP
