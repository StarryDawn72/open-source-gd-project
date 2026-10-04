#define kTagAlertSongWarning 9

void LevelInfoLayer::showSongWarning()
{
    FLAlertLayer* warning = FLAlertLayer::create(
        this,
        "No Song", 

        "This level uses a <cl>custom song</c> that has not been <cg>downloaded</c> yet.\n"
        "Do you want to play without music?\n"
        "<cy>Download by using the bar below</c>",
        
        "Cancel",
        "Play",
        300.0
    );
    warning->setTag(kTagAlertSongWarning);
    warning->show();
}