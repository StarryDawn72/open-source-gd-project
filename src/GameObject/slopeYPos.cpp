/*
	====== GameObject::slopeYPos ======
	
	Calculates the Y-coordinate of the angled
	face of a slope with a given X-coordinate.
	
*/
double GameObject::slopeYPos(float x) {
    CCRect objectRect = getObjectRect();

    double minX  = objectRect.getMinX();
    double maxX  = objectRect.getMaxX();
    double minY  = objectRect.getMinY();
    double maxY  = objectRect.getMaxY();

    double slope = objectRect.size.height / objectRect.size.width;
    double yPos;

    if (minX < x) {
        double dx = x - maxX;

        if (m_slopeUphill)
            yPos = maxY + dx * slope;
        else
            yPos = minY - dx * slope;
    }
	else {
        double dx = minX - x;

        if (m_slopeUphill)
            yPos = minY - dx * slope;
        else
            yPos = maxY + dx * slope;
    }

    if (m_slopeIsHazard) {
        if (slopeFloorTop())
            return yPos - 4.0;
        else
            return yPos + 4.0;
    }

    return yPos;
}
/*
	
	Overload that returns the Y-coordinate of the
	point at which the slope rises given a CCRect.
	
*/
double GameObject::slopeYPos(CCRect *rect)
{

    if (m_slopeUphill == slopeFloorTop())
        return slopeYPos(rect->getMaxX());
	else
		return slopeYPos(rect->getMinX());

}
/*
	
	Another overload given another object.
	
*/
double GameObject::slopeYPos(GameObject *object)
{
    return this->slopeYPos(&object->getObjectRect());
}