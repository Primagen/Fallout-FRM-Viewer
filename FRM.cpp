#include "FRM.hpp"

#include <iostream>
#include "BinaryParsing.hpp"

FRM::FRM()
{
    //TODO: initialize properties with 0 or -1 if signed
}

int FRM::getWidth() const
{
    return this->mF0_pixelWidth;
}
int FRM::getHeight() const
{
    return this->mF0_pixelHeight;
}
const std::vector<int>& FRM::getColors() const
{
    return this->mColors256;
}

bool FRM::open(std::string filename)
{
    mColors256.clear();

    /**
     * TODO: Not sure how to separate the fact that it's loading from
     * "walls" directory
     * vs "tiles" directory.
     * Right now, everything is just in ./art/.
     */
    filename = "./art/"+filename+".frm";
    std::ifstream f(filename, std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cout << "Error opening " << filename << std::endl;
        return false;
    }

    /*********************\
     *  READ EVERYTHING  *
    \*********************/
    //using namespace bendian

    mVersion     = bendian::read_u32(f);
    mFPS         = bendian::read_u16(f);
    mActionFrame = bendian::read_u16(f);
    mNumFramesPerDirection = bendian::read_u16(f);

    //should be unsigned
    mShiftX0 = bendian::read_u16(f);

    //should be signed
    mShiftX1 = bendian::read_u16(f);
    mShiftX2 = bendian::read_u16(f);
    mShiftX3 = bendian::read_u16(f);
    mShiftX4 = bendian::read_u16(f);
    mShiftX5 = bendian::read_u16(f);

    //signed
    mShiftY0 = bendian::read_u16(f);
    mShiftY1 = bendian::read_u16(f);
    mShiftY2 = bendian::read_u16(f);
    mShiftY3 = bendian::read_u16(f);
    mShiftY4 = bendian::read_u16(f);
    mShiftY5 = bendian::read_u16(f);

    //unsigned
    mOffsetF1_0 = bendian::read_u32(f);
    mOffsetF1_1 = bendian::read_u32(f);
    mOffsetF1_2 = bendian::read_u32(f);
    mOffsetF1_3 = bendian::read_u32(f);
    mOffsetF1_4 = bendian::read_u32(f);
    mOffsetF1_5 = bendian::read_u32(f);

    //unsigned
    mFSize = bendian::read_u32(f);

    //unsigned
    mF0_pixelWidth  = bendian::read_u16(f);
    mF0_pixelHeight = bendian::read_u16(f);

    //unsigned
    mF0_pixelArea = bendian::read_u32(f);

    //signed
    mOffsetX_F0 = bendian::read_u16(f); //Offset x direction, frame 0
    mOffsetY_F0 = bendian::read_u16(f); //Offset y dircection, frame 0

    //unsigned
    for (int i = 0; i < mF0_pixelArea; i++)
    {
        mColors256.push_back(bendian::read_u8(f)); // This should be cleared for when you load the next image..

        if (!f.good())
        {
            std::cout << "Some error at pushing back colors in FRM\n";
            return false;
        }
    }
    return true;
}
