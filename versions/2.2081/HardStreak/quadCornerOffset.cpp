CCPoint HardStreak::quadCornerOffset(CCPoint start, CCPoint end, float width) {
    if (width < 1.0f)
        return CCPointZero;

    float angle = CC_RADIANS_TO_DEGREES(atan2(end.y - start.y, end.x - start.x));
    float perpAngle = CC_DEGREES_TO_RADIANS(normalizeAngle(angle + 90.0f));
    return ccp(
        cosf(perpAngle) * (width * 0.5f),
        sinf(perpAngle) * (width * 0.5f)
    );
}
