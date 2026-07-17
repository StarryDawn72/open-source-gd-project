/*
	====== CCCircleWave::baseSetup ======
	
	Initializes the circle effect with default
	values and a given start radius.
	
*/

void CCCircleWave::baseSetup(float radius)
{
    m_color.r = 255;
    m_color.g = 255;
    m_color.b = 255;
    m_lineWidth = 2;
    m_blendAdditive = true;
    m_circleMode = CircleMode::Filled;
    m_radius = radius;
    m_target = nullptr;
    m_opacity = 255.0f;
    m_opacityMod = 1.0f;
}