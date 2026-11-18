void PlayerObject::performSlideCheck()
{
    if (m_lastSlope && (m_isOnSlope || m_wasOnSlope) && !m_hitSlopeTop && !m_lastSlope->m_isGripSlope) {
        float slopeAngleDeg = fabsf(CC_RADIANS_TO_DEGREES(m_slopeAngle));
        if (slopeAngleDeg > 40.f) {

            bool forceLeft = m_isSlopeUphillRelative;
            bool wasForceLeft = m_slopeForceLeft;
            bool wasForceRight = m_slopeForceRight;
            bool forceRight = m_isUpsideDown;

            if (m_isSlopeUphillRelative) {
                forceLeft = !m_isUpsideDown;
            }
            else {
                forceLeft = m_isUpsideDown;
                forceRight = !forceRight;
            }

            m_slopeForceRight = forceRight;
            m_slopeForceLeft = forceLeft;

            if (wasForceLeft != forceLeft || wasForceRight != forceRight)
                m_changedDirectionsTime = m_totalTime;

            m_lastPlatformerSlopeAngle = slopeAngleDeg;
            m_hasPlatformMomentum = true; // TODO
            // I'm keeping an eye on you...
        }
    }
    else {
        m_slopeForceLeft = false;
        m_slopeForceRight = false;
    }
}