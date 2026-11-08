float PlayerObject::convertToClosestRotation(float rotation)
{
    if (!isFlying() && !m_isRobot && !m_isSpider && !m_isDashing)
    {
        float closest = rotation;
        int current = (int)getRotation() % 360;

        if (rotation < current) {
            while (true) {
                rotation += 90.0f;
                if (rotation >= current)
                    break;
                closest = rotation;
            }
        }
        else {
            while (true) {
                rotation -= 90.0f;
                if (rotation <= current)
                    break;
                closest = rotation;
            }
        }
        if (fabsf(current - rotation) >= fabsf(current - closest))
            return closest;
    }
    return rotation;
}