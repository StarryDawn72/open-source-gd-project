void PlayerObject::stopParticles()
{
    deactivateParticle();
    m_trailingParticles->stopSystem();
    m_shipClickParticles->stopSystem();
    m_vehicleGroundParticles->stopSystem();
    m_robotBurstParticles->stopSystem();
}