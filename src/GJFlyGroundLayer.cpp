// @version 2.2081
#include "GJFlyGroundLayer.h"

bool GJFlyGroundLayer::init()
{
    if (!GJGroundLayer::init()) {
        return false;
    }

    m_showGround = false;
    return true;
}