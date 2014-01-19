#ifndef CTSERVICEAPI_H
#define CTSERVICEAPI_H

#pragma warning (disable : 4786)

#include "CTCommon/CTServiceCharacter.h"
#include "CTCommon/CTServiceServer.h"
#include "CTCommon/CTEnum.h"


namespace CTService 
{

class CTServiceAPICore;

typedef unsigned short	CTUnicodeChar;

//--------------------------------------
class CTServiceAPI
//--------------------------------------
{
public:
	CTServiceAPI(const char *hostName, const char *game);  //  hostName: "addr1:port1 addr2:port2"
	virtual ~CTServiceAPI();

	virtual void onConnect(const char *host, const short port, const short current, const short max) = 0;
	virtual void onDisconnect(const char *host, const short port, const short current, const short max) = 0;
	void process();

	// ----- Requests generated by API -----

//	unsigned requestTest(const char *astring, const unsigned anint, void *user);
//	unsigned replyTest(const unsigned server_track, const unsigned value, void *user);
	unsigned replyMoveStatus(const unsigned server_track, const unsigned status, const unsigned result, const CTUnicodeChar *reason, void *user);
	unsigned replyValidateMove(const unsigned server_track, const unsigned result, const CTUnicodeChar *reason, const CTUnicodeChar *suggestedName, void *user);
	unsigned replyMove(const unsigned server_track, const unsigned result, const CTUnicodeChar *reason, void *user);
	unsigned replyCharacterList(const unsigned server_track, const unsigned result, const unsigned count, const CTServiceCharacter *characters, void *user);
	unsigned replyServerList(const unsigned server_track, const unsigned result, const unsigned count, const CTServiceServer *servers, void *user);
	unsigned replyDestinationServerList(const unsigned server_track, const unsigned result, const unsigned count, const CTServiceServer *servers, void *user);
	unsigned replyDelete(const unsigned server_track, const unsigned result, const CTUnicodeChar *reason, void *user);
	unsigned replyRestore(const unsigned server_track, const unsigned result, const CTUnicodeChar *reason, void *user);
	unsigned replyTransferAccount(const unsigned server_track, const unsigned result, const CTUnicodeChar *reason, void *user);

	// ----- Normal Callbacks as a response to requests sent -----

//	virtual void onTest(const unsigned track, const int resultCode, const unsigned value, void *user) = 0;
//	virtual void onReplyTest(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyMoveStatus(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyValidateMove(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyMove(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyDelete(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyRestore(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyTransferAccount(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyCharacterList(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyServerList(const unsigned track, const int resultCode, void *user) = 0;
	virtual void onReplyDestinationServerList(const unsigned track, const int resultCode, void *user) = 0;

	// ----- Callbacks generated by the server directly -----

	virtual void onServerTest(const unsigned server_track, const char *game, const char *param) = 0;
	virtual void onRequestMoveStatus(const unsigned server_track, const char *language, 
										const unsigned transactionID) = 0;
	virtual void onRequestValidateMove(const unsigned server_track, const char *language, 
										const CTUnicodeChar *sourceServer,
										const CTUnicodeChar *destServer, 
										const CTUnicodeChar *sourceCharacter,
										const CTUnicodeChar *destCharacter, const unsigned uid, 
										const unsigned destuid, bool withItems, bool override) = 0;
	virtual void onRequestMove(const unsigned server_track, const char *language, 
										const CTUnicodeChar *sourceServer,
										const CTUnicodeChar *destServer, 
										const CTUnicodeChar *sourceCharacter,
										const CTUnicodeChar *destCharacter, const unsigned uid, 
										const unsigned destuid, const unsigned transactionID, 
										bool withItems, 
										bool override) = 0;
	virtual void onRequestDelete(const unsigned server_track, const char *language, 
										const CTUnicodeChar *sourceServer,
										const CTUnicodeChar *destServer, 
										const CTUnicodeChar *sourceCharacter,
										const CTUnicodeChar *destCharacter, const unsigned uid, 
										const unsigned destuid, const unsigned transactionID, 
										bool withItems, 
										bool override) = 0;
	virtual void onRequestRestore(const unsigned server_track, const char *language, 
										const CTUnicodeChar *sourceServer,
										const CTUnicodeChar *destServer, 
										const CTUnicodeChar *sourceCharacter,
										const CTUnicodeChar *destCharacter, const unsigned uid, 
										const unsigned destuid, const unsigned transactionID, 
										bool withItems, 
										bool override) = 0;
	virtual void onRequestTransferAccount(const unsigned server_track,
										const unsigned uid, 
										const unsigned destuid, 
										const unsigned transactionID) = 0;
	virtual void onRequestCharacterList(const unsigned server_track, const char *language, 
										const CTUnicodeChar *server, const unsigned uid) = 0;
	virtual void onRequestServerList(const unsigned server_track, const char *language) = 0;
	virtual void onRequestDestinationServerList(const unsigned server_track, const char *language,
										const CTUnicodeChar *character, const CTUnicodeChar *server) = 0;

private:
	CTServiceAPICore	*m_apiCore;
};

}; // namespace

#endif	//CTSERVICEAPI_H


