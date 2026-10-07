#define kObjectAllowDartSlideModifier 1755
#define kObjectNoAutoJumpModifier 1813
#define kObjectDashStopModifier 1829
#define kObjectAllowHeadHitModifier 1859
#define kObjectForceCircle 3645
#define kObjectForceBlock 2069
#define kObjectFlipModifier 2866

void PlayerObject::touchedObject(GameObject* object)
{
    int id = object->m_objectID;

    if (id == kObjectAllowHeadHitModifier) {
        m_allowHeadHitTimer = 2;
    }
    else if (id == kObjectFlipModifier) {
        m_flipBlockTimer = 2; 
    }
    else if (id == kObjectForceCircle || id == kObjectForceBlock) {
        m_forceTimer = 2;

        ForceBlockGameObject* forceBlock = (ForceBlockGameObject*)object;

        int forceID = forceBlock->m_forceID;

        if (forceID > 0) {
            if (m_activeForceIDs[forceID])
                return;

            m_activeForceIDs[forceID] = true;
        }

        m_forceVector += forceBlock->calculateForceToTarget(this);

        float length = m_forceVector.getLength();

        if (length > 9999.0f) {
            m_forceVector *= 9999.0 / length;
        }
    }
    else if (id == kObjectNoAutoJumpModifier) {
        m_noAutoJumpTimer = 2;
    }
    else if (id == kObjectDashStopModifier) {
        if (m_isDashing) {
            stopDashing();
            m_holdingJump = false;
        }
    }
    else if (kObjectAllowDartSlideModifier) {
        m_allowDartSlideTimer = 2;
    }
}