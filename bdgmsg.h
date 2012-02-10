#define PEER_NAME_ID_LEN 16

#define TK_NET_DATA_LEN 64

#define TK_NET_BDG_MSG_FLAG     0

#define BDG_READ_OPT_ANY             0
#define BDG_READ_OPT_ADDR_FILTER     1
#define BDG_READ_OPT_MSG_FILTER      2

#define BRIDGE_MSG_INFO_UNKNOWN           0
#define BRIDGE_MSG_INFO_REGISTER          1
#define BRIDGE_MSG_INFO_CONNECT           2
#define BRIDGE_MSG_INFO_CONNECT_ADDR      3
#define BRIDGE_MSG_INFO_HELLO_BDG         4
#define BRIDGE_MSG_INFO_ECHO_REQUEST      5
#define BRIDGE_MSG_INFO_IAM_HERE          6
#define BRIDGE_MSG_ERR_NAMEID_EXIST       7
#define BRIDGE_MSG_INFO_ECHO              8
#define BRIDGE_MSG_INFO_RGST_OK           9
#define BRIDGE_MSG_ERR_NO_NAMEID          10
#define BRIDGE_MSG_INFO_PUNCHING          11
#define BRIDGE_MSG_INFO_PUNCHING_FINISH   12
#define BRIDGE_MSG_INFO_CONNECT_BEGIN     13
#define BRIDGE_MSG_INFO_IAM_WAIT          14

struct BridgeHelloStepPa
{
	BOOL           res;
	struct NetAddr ValidAddr;
};

struct BridgeClientProcPa
{
	char *pMyNameID;
	char *pTargetNameID;
	uchar MyNatType;
};

struct BridgeProc
{
	struct PeerData *pPeerDataRoot;
	struct Iterator *pSeedPeerCache;
	struct Process  proc;
	struct Sock     *pSock;
	struct ProcessingList *pProcList;
	struct NetAddr  s,a,b;
	uchar           ConRelayID;
	uchar           ConStepFlag;
	struct NetAddr  PunAddr,ConAddr;
	void   *Else;
};

struct BridgeMsg
{
	uchar          info;
	struct NetAddr addr;
	uint           RelayID;
	char           NameID[PEER_NAME_ID_LEN];
	uchar          NATType;
	uchar          Relays;
};

struct TkNetMsg
{
	uchar           flag;
	union
	{
		struct BridgeMsg BdgMsg;
		char DataMsg[TK_NET_DATA_LEN];
	}msg;
};

DECLARATION_STRUCT_CONSTRUCTOR( BridgeProc )

void 
ConsAndStartBridgeServer(struct BridgeProc * , struct PeerData * , struct ProcessingList * , struct Sock *,struct Iterator *);

void 
FreeBridgeServer(struct BridgeProc *);

void 
BridgeMakeHelloProc(struct BridgeProc *,struct BridgeHelloStepPa * , struct Sock *,struct NetAddr *);

void 
BridgeMakeClientProc(struct BridgeProc *, struct Sock * ,struct NetAddr *, char * ,uchar , char*);

void 
FreeBdgClientProc(struct BridgeProc *);
