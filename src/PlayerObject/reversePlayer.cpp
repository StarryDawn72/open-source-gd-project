/*
    Only for jump rings/pads with the "Reverse" option enabled.
    Not for the reverse trigger or platformer mode.
*/
void PlayerObject::reversePlayer(EffectGameObject* object)
{
    // Rename incorrect geode bindings
    double& m_reverseSyncOffset = m_maybeReverseSpeed;

    if (!m_isPlatformer) {
        if (object && m_reverseSync) {

            // "object" is the jump ring/pad that reversed us
            CCPoint orbPosition = object->getRealPosition();
            CCPoint playerPos   = this->getPosition();

            CCPoint diff = orbPosition - (playerPos + ccp(m_reverseSyncOffset, m_reverseSyncOffset));

            float x = !m_isSideways ? diff.x : diff.y;

            m_reverseSyncOffset += x + x;
        }
        doReversePlayer(!m_isGoingLeft);
    }
}