void PlayeObject::placeStreakPoint()
{
    // Rename bindings
    bool& m_isRespawning = m_maybeReducedEffects;

    if ( !m_isRespawning
      && m_isDart
      && !m_isLocked
      && m_fadeOutStreak
      && !levelFlipping())
    {
        m_waveTrail->addPoint(getPosition() + ccp(0, 30));
    }

    m_justPlacedStreak = false; // TODO might need a rename
}