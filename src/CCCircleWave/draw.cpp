/*
	====== CCCircleWave::draw ======
	
	CCNode::draw override. Uses the current drawn
	radius to choose from a set of hard coded LOD's
	every draw call.
	
*/
void CCCircleWave::draw()
{
	if (m_blendAdditive)
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE);

	if (m_circleMode == CircleMode::Outline)
		glLineWidth(m_lineWidth);

	float opacity = MIN(MAX(0.0f, m_opacityMod * m_opacity), 255.0f);

	ccDrawColor4B(m_color.r, m_color.g, m_color.b, opacity);

	unsigned int segments;
	if      (m_radius < 10.0f)  segments = 10;
	else if (m_radius < 20.0f)  segments = 15;
	else if (m_radius < 40.0f)  segments = 20;
	else if (m_radius < 200.0f) segments = 30;
	else                        segments = 50;

	if (m_circleMode == CircleMode::Outline)
		ccDrawCircle(m_position, m_radius, 0.0, segments, false);
	else
		ccDrawFilledCircle(m_position, m_radius, 0.0, segments);

	if (m_blendAdditive)
		ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}