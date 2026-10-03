double HardStreak::normalizeAngle(double angle) {
    if (angle > 360.0)
        return angle - 360.0;
    if (angle < 0.0)
        return angle + 360.0;
    return angle;
}