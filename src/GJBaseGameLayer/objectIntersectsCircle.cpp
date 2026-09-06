/*
    Overlap test used in pre-2.2 levels against the object's circle and the player's axis-aligned bounding box.
*/
bool GJBaseGameLayer::objectIntersectsCircle(GameObject* object, GameObject* circle)
{
    CCRect objectRect = object->getObjectRect();
    float radius = circle->getObjectRadius();
    CCPoint circlePos = circle->getRealPosition();

    float maxX = objectRect.getMaxX();
    float minX = objectRect.getMinX();
    float maxY = objectRect.getMaxY();
    float minY = objectRect.getMinY();
    
    if (objectRect.containsPoint(circlePos))
        return true;

    if (fabsf(ccpDistance(ccp(maxX, maxY), circlePos)) < radius)
        return true;

    if (fabsf(ccpDistance(ccp(maxX, minY), circlePos)) < radius)
        return true;

    if (fabsf(ccpDistance(ccp(minX, minY), circlePos)) < radius)
        return true;

    return fabsf(ccpDistance(ccp(minX, maxY), circlePos)) < radius;
}  