double HardStreak::normalizeAngle(double angle) {
    if (angle > 360.0f)
        return angle - 360.0f;
    if (angle < 0.0f)
        return angle + 360.0f;
    return angle;
}
