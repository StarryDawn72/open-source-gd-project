// @version 2.2081
bool HardStreak::init()
{
    if (!CCDrawNode::init())
        return false;

    m_pointArray = CCArray::create();
    m_pointArray->retain();
    firstSetup();
    return true;
}