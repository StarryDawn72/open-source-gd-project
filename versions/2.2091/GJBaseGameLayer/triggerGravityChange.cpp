void GJBaseGameLayer::triggerGravityChange(EffectGameObject* object, int playerID)
{
    // "m_followCPP" is actually the shared object property 201. It's semantically
    // different from trigger to trigger, though on gravity triggers it's the
    // "player touch" option.
    if (object->m_followCPP) {
        if (playerID == 1)
            m_player1->m_gravityMod = object->m_gravityValue;
        else if (playerID == 2)
            m_player2->m_gravityMod = object->m_gravityValue;
    }
    if (!object->m_targetPlayer2)
        m_player1->m_gravityMod = object->m_gravityValue;

    if (!object->m_targetPlayer1)
        m_player2->m_gravityMod = object->m_gravityValue;
}