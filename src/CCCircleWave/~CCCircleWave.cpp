/*
	====== CCCircleWave::~CCCircleWave ======
	
	Destructor.
	
*/
CCCircleWave::~CCCircleWave()
{
    if (m_target) m_target->release();
}