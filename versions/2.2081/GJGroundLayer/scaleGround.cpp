float GJGroundLayer::scaleGround(float scale)
{
    setScaleX(scale);
    setScaleY(getScaleY() >= 0.0f ? scale : -scale);

    float preWidth = m_groundWidth;
    updateGroundWidth(true);
    float postWidth = m_groundWidth;

    updateShadows();

    return postWidth - preWidth;
}