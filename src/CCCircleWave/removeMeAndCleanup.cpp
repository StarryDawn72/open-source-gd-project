/*
	====== CCCircleWave::removeMeAndCleanup ======
	
	Overrides CCNode::removeMeAndCleanup to call
	its delegate's circleWaveWillBeRemoved method
	to notify its listeners before the node is
	destroyed.
	
*/
void CCCircleWave::removeMeAndCleanup()
{
    if (m_delegate)
        m_delegate->circleWaveWillBeRemoved(this);

    CCNode::removeMeAndCleanup();
}