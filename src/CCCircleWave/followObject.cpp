/*
	====== CCCircleWave::followObject ======
	
	Schedules updatePosition every frame to follow
	a given node unless staticPosition is true.
	
*/
void CCCircleWave::followObject(CCNode *newTarget, bool staticPosition)
{
	if (m_target) m_target->release();
	m_target = newTarget;
	m_target->retain();

	unschedule(schedule_selector(CCCircleWave::updatePosition));

	if (!staticPosition)
		schedule(schedule_selector(CCCircleWave::updatePosition), 0);

	setPosition(m_target->getPosition());
}