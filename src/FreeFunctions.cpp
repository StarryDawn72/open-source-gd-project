// Here you will find a list of free functions
// RobTop used that don't belong to any class.


/*
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

float SquareDistance(float x1, float y1, float x2, float y2)
{
    return ((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1));
}

gd::string gen_random(int length)
{
	static const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	CCString* out = CCString::create("");

	for (int i = 0; i < length; i++) {
		out = CCString::createWithFormat(
			"%s%c",
			out->getCString(),
			characters[rand() % 62]
		);
	}

	return gd::string(out->getCString());	
}

float Slerp2D(float fromAngle, float toAngle, float t)
{
    float halfFrom = fromAngle * 0.5f;
    float halfTo = toAngle   * 0.5f;

    float cosFrom = cosf(halfFrom);
    float sinFrom = sinf(halfFrom);
    float cosTo = cosf(halfTo);
    float sinTo = sinf(halfTo);

    float cosOmega = (sinTo * sinFrom) + (cosTo * cosFrom);

    if (cosOmega < 0.0f)
    {
        cosOmega = -cosOmega;
        sinTo = -sinTo;
        cosTo = -cosTo;
    }

    float coeff0 = 1.0f - t;
    float coeff1 = t;

    if ((1.0f - cosOmega) > 0.0001f)
    {
        float omega    = acosf(cosOmega);
        float sinOmega = sinf(omega);
        coeff0 = sinf((1.0f - t) * omega) / sinOmega;
        coeff1 = sinf(t * omega) / sinOmega;
    }

    double halfResult = atan2((sinFrom * coeff0) + (coeff1 * sinTo), (cosFrom * coeff0) + (coeff1 * cosTo));

    return static_cast<float>((halfResult + halfResult));
}