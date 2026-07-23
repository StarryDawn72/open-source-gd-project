#define GM GameManager::sharedState()
/*
	====== GameLevelManager::downloadLevel ======
	
	Makes a POST request to downloadGJLevel22.php to
	download a user level, daily level, or gauntlet level.
	
*/
void GameLevelManager::downloadLevel(int id, bool gauntletLevel, int dailyID)
{
    const char* levelDownloadKey = getLevelDownloadKey(id, gauntletLevel, dailyID);

    if (!isDLActive(levelDownloadKey))
    {
        addDLToActive(levelDownloadKey);
        bool isFirstDownload = !hasDownloadedLevel(id);
		
        gd::string postString = getBasePostString();

		// Wmfd2893gb7
        const char* commonSecret = CCString::createWithFormat("%c%s%s%c%c%s", 'W', "mfd", "2893", 'g', 'b', "7")->getCString();
        const char* levelInfo = CCString::createWithFormat("&levelID=%i&inc=%i&secret=%s", id, isFirstDownload, commonSecret)->getCString();
        postString += levelInfo;
		
        if (isFirstDownload) {

            gd::string random = gen_random(10); // Randomized string of characters
            postString += "&rs=";
            postString += random;

            GJAccountManager* AM = GJAccountManager::sharedState();
            int accountID = AM->m_accountID - AM->m_unkInt1; // m_unkInt1 real name unknown

			// xI25fpAapCQg
            const char* chkSecret = CCString::createWithFormat("%c%s%s%c%c%s", 'x', "I25", "fpAa", 'p', 'C', "Qg")->getCString();
            gd::string toHash = CCString::createWithFormat("%i%i%s%i%s%i%s", id, isFirstDownload, random, accountID, GM->m_playerUDID, GM->m_playerUserID, chkSecret)->getCString();

			unsigned char hash[20];
            rtsha1::calc(toHash.c_str(), toHash.size(), hash);

			char hashHex[41];
			rtsha1::toHexString(hash, hashHex);

        	gd::string xorKey = "41274";
			gd::string chk = ZipUtils::base64EncodeEnc(gd::string(hashHex), xorKey);

			postString += "&chk=";
			postString += chk;
        }

        gd::string endpoint = "https://www.boomlings.com/database/downloadGJLevel22.php";
        ProcessHttpRequest(endpoint, postString, gd::string(levelDownloadKey), GJHttpType::DownloadLevel);
    }
}