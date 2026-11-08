void PlayerObject::disableSwingFire()
{
    m_swingFireMiddle->setVisible(false);
    m_swingFireMiddle->stopAllActions();
    m_swingFireBottom->setVisible(false);
    m_swingFireBottom->stopAllActions();
    m_swingFireTop->setVisible(false);
    m_swingFireTop->stopAllActions();
    m_swingBurstParticles1->stopSystem();
    m_swingBurstParticles2->stopSystem();
}