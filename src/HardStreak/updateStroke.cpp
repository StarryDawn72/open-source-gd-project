void HardStreak::updateStroke(float dt)
{
    if (!m_drawStreak)
        return;

    CCDrawNode::clear();
    if (m_pointArray->count() == 0 || getOpacity() == 0)
        return;

    int strokeCount = m_isSolid ? 1 : 2;

    CCPoint pos = getPosition();

    CCObject* pointNode;
    CCARRAY_FOREACH(m_pointArray, pointNode) {
        CCPoint& point = ((PointNode*)pointNode)->m_point;
        point -= pos;
    }

    m_currentPoint -= pos;

    CCPoint points[4];

    for (int stroke = 0; stroke < strokeCount; stroke++) {
        for (int i = 0; i < m_pointArray->count(); i++) {
            CCPoint currPoint = ((PointNode*)(m_pointArray->objectAtIndex(i)))->m_point;
            
            CCPoint nextPoint;
            if (i >= m_pointArray->count() - 1)
                nextPoint = m_currentPoint;
            else
                nextPoint = ((PointNode*)(m_pointArray->objectAtIndex(i + 1)))->m_point;

            if (currPoint == nextPoint)
                continue;

            if (m_isFlipped)
                std::swap(currPoint, nextPoint);

            for (int j = 0; j < 4; j++)
                points[j] = CCPoint();

            float width = (stroke == 0 ? 6.0f : 2.0f) * m_waveSize * m_pulseSize;
            CCPoint cornerOffset = quadCornerOffset(currPoint, nextPoint, width);

            float  absCorX = fabsf(cornerOffset.x);
            double tanVal  = tanh(asinh(absCorX / (width * 0.5)));
            float  unkVal  = fabsf((float)tanVal * absCorX);

            bool someBool;

            if (i >= m_pointArray->count() - 1 && stroke == 0 && m_isFlipped) {
                if (fabsf(ccpDistance(currPoint, nextPoint)) > 10.0f) {
                    float value = fabsf((float)(tanVal * 4.0f));
                    if (m_isFlipped) {
                        currPoint.x += 4.0f;
                        if (currPoint.y >= nextPoint.y)
                            currPoint.y -= value;
                        else
                            currPoint.y += value;
                    } else {
                        currPoint.x -= 4.0f;
                        if (currPoint.y >= nextPoint.y)
                            currPoint.y += value;
                        else
                            currPoint.y -= value;
                    }
                }

                someBool = true;
            } else {
                someBool = false;
            }

            CCPoint currOPoint = currPoint;
            CCPoint nextOPoint = nextPoint;
            currOPoint.x -= absCorX;
            nextOPoint.x += absCorX;

            if (stroke != 0) {
                currPoint.x += absCorX;
                nextPoint.x -= absCorX;

                if (nextOPoint.y > currOPoint.y) {
                    currPoint.y += unkVal;
                    nextPoint.y -= unkVal;
                } else {
                    currPoint.y -= unkVal;
                    nextPoint.y += unkVal;
                }
            }

            if (nextOPoint.y > currOPoint.y) {
                currOPoint.y -= unkVal;
                nextOPoint.y += unkVal;

                points[0] = currOPoint - cornerOffset;
                points[1] = currPoint  + cornerOffset;
                points[2] = (someBool ? nextPoint : nextOPoint) + cornerOffset;
                points[3] = nextPoint - cornerOffset;
            } else {
                currOPoint.y += unkVal;
                nextOPoint.y -= unkVal;

                points[0] = currPoint  - cornerOffset;
                points[1] = currOPoint + cornerOffset;
                points[2] = nextPoint  + cornerOffset;
                points[3] = (someBool ? nextPoint : nextOPoint) - cornerOffset;
            }

            ccColor3B color;
            float opacity;

            if (stroke == 0) {
                color = getColor();
                opacity = (float)getOpacity() / 255.0f;
            } else {
                color = ccWHITE;
                opacity = (float)getOpacity() / 255.0f * 0.65f;
            }

            ccColor4F fColor = ccc4FFromccc3B(color);
            fColor.a = opacity;

            drawPolygon(points, 4, fColor, 0.0f, ccc4f(0.0f, 0.0f, 0.0f, 0.0f));
        }
    }
    
    CCARRAY_FOREACH(m_pointArray, pointNode) {
        CCPoint& point = (PointNode*(pointNode)->m_point;
        point += pos;
    }

    m_currentPoint += pos;
}
