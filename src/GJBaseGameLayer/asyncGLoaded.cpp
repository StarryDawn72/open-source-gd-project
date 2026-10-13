void GJBaseGameLayer::asyncGLoaded(int ground)
{
    createGroundLayer(ground, 0);
    updateLevelColors();
}