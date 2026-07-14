// Here you will find a list of free functions
// RobTop used that don't belong to any class.


/*
	====== snapRotation360 ======
	
	Normalizes the given rotation to a -180 to 180 degree
	range. It's used exclusively in limitDashRotation and
	startDashing for dash ring mechanics.
	
*/
void snapRotation360(float& rotation)
{
	if (rotation <= 180.0f) {
		if (rotation < -180.0f) {
			rotation += 360.0f;
		}
	}
	else {
		rotation -= 360.0f;
	}
}



/*
	====== SquareDistance ======
	
	A simple math helper used for PlayerObject.
	
*/
float SquareDistance(float x1, float y1, float x2, float y2)
{
    return ((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1));
}