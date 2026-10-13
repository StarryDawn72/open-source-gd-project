#define kMathRoundingRound 1
#define kMathRoundingFloor 2
#define kMathRoundingCeil 3

double GJBaseGameLayer::performMathRounding(double value, int type)
{
    switch (type) {
    case kMathRoundingRound: return round(value);
    case kMathRoundingFloor: return floor(value);
    case kMathRoundingCeil: return ceil(value);
    }
    return value;
}