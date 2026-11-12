double GJBaseGameLayer::performMathRounding(double value, int type)
{
    switch (type) {
        case 1:
            return round(value);
        case 2:
            return floor(value);
        case 3:
            return ceil(value);
        default:
            return value;
    }
}