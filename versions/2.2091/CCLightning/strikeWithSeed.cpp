void CCLightning::strikeWithSeed(uint64_t seed)
{
    m_seed = seed;
    strike();
}