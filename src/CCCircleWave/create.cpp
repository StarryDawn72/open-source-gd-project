/*
	====== CCCircleWave::create ======
	
	Static create factory method.
	
*/
CCCircleWave* CCCircleWave::create(float startRadius, float endRadius, float duration, bool fadeIn, bool easeOut) {
    CCCircleWave* ret = new CCCircleWave();
    if (ret->init(startRadius, endRadius, duration, fadeIn, easeOut)) {
        ret->autorelease();
        return ret;
    }
	else {
        delete ret;
        return nullptr;
    }
}
/*
	
	Overload with easing hard coded to true... for some reason.
	
*/
CCCircleWave* CCCircleWave::create(float startRadius, float endRadius, float duration, bool fadeIn) {
    return CCCircleWave::create(startRadius, endRadius, duration, fadeIn, true);
}