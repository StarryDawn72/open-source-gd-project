void GJBaseGameLayer::createBackground(int index)
{
    if (m_background && m_background->getTag() == index)
        return;

    if (m_background)
        removeBackground();

    index = MIN(MAX(index, 1), 59);

    bool useMirroredRepeat = true;

    // Some backgrounds shouldn't mirror vertically
    switch (index) {
        case 16:
        case 35:
        case 37:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
            useMirroredRepeat = false;
            break;
        default:
            break;
    }

    CCSprite* sprite = CCSprite::create(GM->getBGTexture(index));
    m_background = sprite;

    sprite->setTag(index);

    ccTexParams params = ccTexParams{};
    params.minFilter = GL_LINEAR;
    params.magFilter = GL_LINEAR;
    params.wrapS     = GL_REPEAT;
    params.wrapT     = useMirroredRepeat ? GL_MIRRORED_REPEAT : GL_REPEAT;

    CCTexture2D* texture = m_background->getTexture();
    texture->setTexParameters(&params);

    m_objectParent->addChild(m_background, -60);

    m_background->setAnchorPoint(ccp(0.0f, 0.0f));
    m_background->setScale(AppDelegate::get()->bgScale());
    m_background->setBlendFunc({GL_ONE, GL_ZERO});
    m_background->setColor(ccc3(40, 126, 255));

    m_gameState.m_backgroundWidth = m_background->m_obRect.size.width * m_background->getScale();
}