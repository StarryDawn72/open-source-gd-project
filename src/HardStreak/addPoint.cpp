// @version 2.2081
void HardStreak::addPoint(CCPoint point)
{
    m_pointArray->addObject(PointNode::create(point));
}