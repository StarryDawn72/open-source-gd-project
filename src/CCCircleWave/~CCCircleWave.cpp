// @version 2.2081
CCCircleWave::~CCCircleWave()
{
    if (m_target) m_target->release();
}