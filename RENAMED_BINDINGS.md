Some nasty variables I had to rename, either because they were completely incorrect or I because found a more suitable name. Found through extensive runtime analysis and reverse-engineering.
---

**PlayerObject**:
- m_jumpBuffered -> m_holdingJump
- m_stateJumpBuffered -> m_holdingJumpReleaseDelayed
- m_isOnGround -> m_canJump
- m_isOnGround2 -> m_onGround
- m_maybeChangedDirectionAngle -> m_lastPlatformerSlopeAngle
- m_platformerMovingRight -> m_slopeForceRight
- m_platformerMovingLeft -> m_slopeForceLeft
- m_playEffects -> m_isInPlayLayer
- m_unkA99 -> m_isInDualMode
- m_ringJumpRelated -> m_ringJumpingThisTick
- m_padRingRelated -> m_canDisableAutoJump
- m_ringRelatedSet -> m_activatedRingIDs? (maybe something to do with J blocks as well)
- m_maybeIsBoosted -> m_isJumping (seen on-stream)
- m_isAccelerating -> m_isVelocityUncapped
- m_touchedGravityPortal -> m_touchedTeleportRing
- m_maybeReducedEffects -> m_isRespawning
- m_maybeSlopeForce -> m_slideBoostValue (from RobTop's stream)
- m_stateRingJump -> m_isJumpUnused
- m_stateRingJump2 -> m_canRingJump
- m_vehicleSize -> m_playerScale
- m_isBallRotating -> m_ballRotationMultiplierActive
- m_rotateSpeed -> m_ballRotationMultiplier
- m_enable22Changes -> m_2p2ChangesDisabled (inverted lol)
- m_maybeCanRunIntoBlocks -> m_ignoreDamagePlayLayer
- m_ignoreDamage -> m_ignoreDamageEditor
- m_maybeIsColliding -> m_tookDamage
- m_unk3e0 -> m_slopeWasClampedMax
- m_unk3e1 -> m_slopeWasClampedMin
- m_slopeFlipGravityRelated -> m_isGoingDownSlope
- unk_584 -> m_slopeYOffset
- m_potentialSlopeMap -> m_preSlopeObjects
- m_rotateObjectsRelated -> m_rotatedObjectDeltas
- m_unk3d0 -> m_lastSlopeYPos
- m_blackOrbRelated -> m_lastSlopeYPosRotated
- m_maybeSlidingTime -> m_slopeSlideTimer
- m_maybeUpsideDownSlope -> m_hitSlopeTop
- m_slopeSlidingMaybeRotated -> m_isSlopeUphillRelative
- m_lastActivatedPortal -> m_lastEffectObject
- m_lastPortalPos -> m_lastEffectObjectPos

**GameObject**
- m_editorEnabled -> m_isInEditor
- m_unk367 -> m_isAnimatedGameObject
- m_unk3F8 -> m_isEndPortal

**GJGameState**
- m_levelFlipping -> m_levelFlipProgress

**AudioEffectsLayer**
- m_unk1c0 -> m_pulseQueue