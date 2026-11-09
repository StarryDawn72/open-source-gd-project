#pragma once

// A list of all macros used in this repository

#define GM (GameManager::sharedState())
#define PL GameManager::sharedState()->getPlayLayer()

#define kFollowPlayerYStoreTimeInterval 0.01f
#define kGVDisableHighObjectAlert "0082"
#define kGVDisableSongAlert "0083"
#define kGVShownCoinDisclaimer "0063"
#define kGVCheckIfServerOnline "0055"

#define kMaxBirdFrame 149
#define kMaxDartFrame 96
#define kMaxDashLength 17.310005f
#define kMaxJetpackFrame 8
#define kMaxPlayerFrame 485
#define kMaxPlayerStreak 7
#define kMaxRobotFrame 68
#define kMaxRollFrame 118
#define kMaxShipFrame 169
#define kMaxSwingFrame 43
#define kFollowPlayerYStoreTimeInterval 0.01f

#define kMiddlegroundBaseScale 1.2f
#define kMiddlegroundBaseSpeed 0.3f

#define kObjectAllowDartSlideModifier 1755
#define kObjectAllowHeadHitModifier 1859
#define kObjectDashStopModifier 1829
#define kObjectFlipModifier 2866
#define kObjectForceBlock 2069
#define kObjectForceCircle 3645
#define kObjectNoAutoJumpModifier 1813
#define kObjectSpawnTrigger 1268

#define kPlayerCommandStopSlide 543
#define kPlayerTouchToggleBlock 3643

#define kStickDistance 5.0f
#define kStickDistancePlatformer 10.0f

#define kTagActionCompletionPlayerFadeOut 4
#define kTagAlertSongWarning 9
#define kTagBirdParticles 7
#define kTagGroundFade 3
#define kTagGroundLine 2
#define kTagGroundShadowLeft 0
#define kTagGroundShadowRight 1
#define kTagPlatformerJumpAnimation 13
#define kTagPlatformerJumpUnk 14 // TODO: find usage and name
#define kTagPlayerBlink 11
#define kTagPlayerScaleEffect 6
#define kTagScaleSpider 10
