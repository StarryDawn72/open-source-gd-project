// Here you will find a list of free functions
// RobTop used that don't belong to any class.

 
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