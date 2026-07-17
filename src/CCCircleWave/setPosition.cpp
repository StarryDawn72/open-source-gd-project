/*
	====== CCCircleWave::setPosition ======
	
	Wrapper around CCNode::setPosition in order to
	update the class's own m_position member as well.
	
*/
void CCCircleWave::setPosition(const CCPoint& position)
{
    setPosition(position);
    m_position = position;
}