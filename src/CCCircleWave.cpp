#include "CCCircleWave.h"

void CCCircleWave::updatePosition(float dt)
{
	if (m_target) setPosition(m_target->getPosition());
}

CCCircleWave::~CCCircleWave()
{
    if (m_target) m_target->release();
}

void CCCircleWave::setPosition(const CCPoint& position)
{
    setPosition(position);
    m_position = position;
}

void CCCircleWave::draw()
{
	if (m_blendAdditive)
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE);

	if (m_circleMode == CircleMode::Outline)
		glLineWidth(m_lineWidth);

	float opacity = MIN(MAX(0.0f, m_opacityMod * m_opacity), 255.0f);

	ccDrawColor4B(m_color.r, m_color.g, m_color.b, opacity);

	unsigned int segments;
	if      (m_radius < 10.0f)  segments = 10;
	else if (m_radius < 20.0f)  segments = 15;
	else if (m_radius < 40.0f)  segments = 20;
	else if (m_radius < 200.0f) segments = 30;
	else                        segments = 50;

	if (m_circleMode == CircleMode::Outline)
		ccDrawCircle(m_position, m_radius, 0.0, segments, false);
	else
		ccDrawFilledCircle(m_position, m_radius, 0.0, segments);

	if (m_blendAdditive)
		ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

void CCCircleWave::removeMeAndCleanup()
{
    if (m_delegate)
        m_delegate->circleWaveWillBeRemoved(this);

    CCNode::removeMeAndCleanup();
}

void CCCircleWave::updateTweenAction(float value, const char *key)
{
	gd::string keyString = gd::string(key);

	if (keyString == "opacity") m_opacity = value;
	else if (keyString == "radius") m_radius = value;

	if (m_target) setPosition(m_target->getPosition());
}

CCCircleWave::CCCircleWave()
{
	m_target = nullptr;
    m_width = 0.0f;
    m_radius = 0.0f;
    m_opacity = 0.0f;
    m_circleMode = CircleMode::Filled;
    m_lineWidth = 0;
    m_opacityMod = 0.0;
    m_blendAdditive = 0;
    m_delegate = nullptr;
}

void CCCircleWave::baseSetup(float radius)
{
    m_color.r = 255;
    m_color.g = 255;
    m_color.b = 255;
    m_lineWidth = 2;
    m_blendAdditive = true;
    m_circleMode = CircleMode::Filled;
    m_radius = radius;
    m_target = nullptr;
    m_opacity = 255.0f;
    m_opacityMod = 1.0f;
}

bool CCCircleWave::init(float startRadius, float endRadius, float duration, bool fadeIn, bool easeOut)
{
	baseSetup(startRadius);
	CCAction* waveAction;

	// 1. Fade in and out over duration seconds.
	if (fadeIn) {
		m_opacity = 0.0f;

		auto radiusTween = CCActionTween::create(duration, "radius", m_radius, endRadius);

		auto fadeInTween = CCActionTween::create(duration * 0.5f, "opacity", m_opacity, 255.0f);
		auto fadeOutTween = CCActionTween::create(duration * 0.5f, "opacity", 255.0f, 0.0f);
		auto cleanupAction = CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));

		auto waveSequence = CCSequence::create(fadeInTween, fadeOutTween, cleanupAction, nullptr);
		waveAction = CCSpawn::create(radiusTween, waveSequence, nullptr);
	}
	// 2. Fade out only.
	else {
		m_opacity = 255.0f;

		CCActionInterval* radiusTween = CCActionTween::create(duration, "radius", m_radius, endRadius);
		CCActionInterval* opacityTween = CCActionTween::create(duration, "opacity", m_opacity, 0.0f);

		if (easeOut) {
			// Ease the radius and fade tweens if the "easeOut" parameter is true

			radiusTween = CCEaseOut::create(radiusTween, 2.0f);
			auto fadeOutTween = CCActionTween::create(duration, "opacity", m_opacity, 0.0f);
			opacityTween = CCEaseOut::create(fadeOutTween, 2.0f);
		}

		auto spawnAction = CCSpawn::create(radiusTween, opacityTween, nullptr);
		auto cleanupAction = CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));

		waveAction = CCSequence::create(spawnAction, cleanupAction, nullptr);
	}

	CCDirector::sharedDirector()->getActionManager()->addAction(waveAction, this, false);
	return true;
}

CCCircleWave* CCCircleWave::create(float startRadius, float endRadius, float duration, bool fadeIn, bool easeOut)
{
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

CCCircleWave* CCCircleWave::create(float startRadius, float endRadius, float duration, bool fadeIn)
{
    return CCCircleWave::create(startRadius, endRadius, duration, fadeIn, true);
}

void CCCircleWave::followObject(CCNode *newTarget, bool staticPosition)
{
	if (m_target) m_target->release();
	m_target = newTarget;
	m_target->retain();

	unschedule(schedule_selector(CCCircleWave::updatePosition));

	if (!staticPosition)
		schedule(schedule_selector(CCCircleWave::updatePosition), 0);

	setPosition(m_target->getPosition());
}