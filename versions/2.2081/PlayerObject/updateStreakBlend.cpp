void PlayerObject::updateStreakBlend(bool blend)
{
	ccBlendFunc blendFunc;

    if (blend) {
        blendFunc.src = GL_SRC_ALPHA;
        blendFunc.dst = GL_ONE;
    } else {
		blendFunc.src = GL_SRC_ALPHA;
    	blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	}

    m_regularTrail->setBlendFunc(blendFunc);
    m_waveTrail->m_isSolid = !blend;
    m_waveTrail->setBlendFunc(blendFunc);
}