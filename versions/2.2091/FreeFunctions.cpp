// Here you will find a list of free functions
// RobTop used that don't belong to any class.

/*
    Used for CCLightning strike.
*/
unsigned int getNextRandom(unsigned long long* seed)
{
    (*seed) = (*seed) * 1103515245 + 12345;
    return (unsigned)((*seed) / 65536) % 32768;
}

CCPoint drawLightning(CCPoint pt1, CCPoint pt2, int displacement, int minDisplacement, unsigned long long seed, CCPoint* points, unsigned int* numPoints)
{
    CCPoint sum = pt1 + pt2;
    CCPoint midPoint = sum * 0.5f;

    if (displacement < minDisplacement) {
        points[*numPoints] = pt1;
        points[*numPoints + 1] = pt2;
        *numPoints += 2;        
    }
    else {
        midPoint.x += ((getNextRandom(&seed) % 101) / 100.0f - 0.5f) * displacement;
        midPoint.y += ((getNextRandom(&seed) % 101) / 100.0f - 0.5f) * displacement;

        drawLightning(pt1, midPoint, displacement / 2, minDisplacement, seed, points, numPoints);
        drawLightning(pt2, midPoint, displacement / 2, minDisplacement, seed, points, numPoints);        
    }
    
    return midPoint;
}
 
/*
    Quicksort comparison functions for spider jump.
*/

int boxCompMin(const void* a, const void* b)
{
    GameObject* objA = *(GameObject**)a;
    GameObject* objB = *(GameObject**)b;

    return (int)(objA->getObjectRect().getMinY() * 10.0f) -
           (int)(objB->getObjectRect().getMinY() * 10.0f);
}

int boxCompMax(const void* a, const void* b)
{
    GameObject* objA = *(GameObject**)a;
    GameObject* objB = *(GameObject**)b;

    return (int)(objB->getObjectRect().getMaxY() * 10.0f) -
           (int)(objA->getObjectRect().getMaxY() * 10.0f);
}

int boxCompMinX(const void* a, const void* b)
{
    GameObject* objA = *(GameObject**)a;
    GameObject* objB = *(GameObject**)b;

    return (int)(objA->getObjectRect().getMinX() * 10.0f) -
           (int)(objB->getObjectRect().getMinX() * 10.0f);
}

int boxCompMaxX(const void* a, const void* b)
{
    GameObject* objA = *(GameObject**)a;
    GameObject* objB = *(GameObject**)b;

    return (int)(objB->getObjectRect().getMaxX() * 10.0f) -
           (int)(objA->getObjectRect().getMaxX() * 10.0f);
}