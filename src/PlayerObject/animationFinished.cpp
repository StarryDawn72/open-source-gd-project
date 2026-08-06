void PlayerObject::animationFinished(const char* key)
	{
		gd::string keyString = gd::string(key);

		if (keyString == "jump_start") {
			m_robotSprite->runAnimation("jump_loop");
		}
		else if (keyString == "fall_start") {
			m_robotSprite->runAnimation("fall_loop");
			m_spiderSprite->runAnimation("fall_loop");
		}
		else if (keyString == "idle02") {
			if (m_isRobot)
				m_robotSprite->runAnimation("idle01");
			else if (m_isSpider)
				m_spiderSprite->runAnimation("idle01");
		}
			
	}