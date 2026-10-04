// RobTop's discovered macros from his old twitch streams and screenshots
#define kStickDistance 5.0f
#define kStickDistancePlatformer 10.0f
#define kPlayerSqueezeTolerance m_isPlatformer ? 0.8f : 0.7f
#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()
#define kBlockInset 0.3f
#define kGVRandomOption001 "0095" // In EndLevelLayer, "Game Variable"
#define kTagScaleSpider 10 // In PlayerObject::resetObject
#define bgOpacity 100 // In EndLevelLayer
#define kFEInstantCollisionTrigger 3609 // Object ID, probably "Frame Editor"
#define kSFEInstantCollisionTrigger "edit_eCollisionBtn_001.png" // Probably "String Frame Editor" or "Sprite Frame Editor"

// Might be a macro, need to look into it
// addFrameKey(kSFEInstantCollisionTrigger, kFEInstantCollisionTrigger);