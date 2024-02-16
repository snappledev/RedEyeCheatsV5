#pragma once
#include <Windows.h>
#include <stdint.h>
#define INVALID_HTTP_REQUEST_HANDLE 0
#define INVALID_STEAM_API_CALL_HANDLE 0

typedef uint32_t HTTPRequestHandle;
typedef uint64_t SteamAPICallHandle;

#define HTTP_REQUEST_CALLBACK 2101
#pragma pack(push, 8)
struct HTTPRequestCompleted
{
	HTTPRequestHandle m_hRequest;
	uint64_t m_ulContextValue;
	bool m_bRequestSuccessful;
	int m_eStatusCode;
	uint32_t m_unBodySize;
};
#pragma pack(pop)
enum HTTPMethod
{
	HTTP_METHOD_INVALID = 0,
	HTTP_METHOD_GET,
	HTTP_METHOD_HEAD,
	HTTP_METHOD_POST,
	HTTP_METHOD_PUT,
	HTTP_METHOD_DELETE,
	HTTP_METHOD_OPTIONS,
	HTTP_METHOD_PATCH
};
class ISteamHTTP
{
public:
	virtual HTTPRequestHandle CreateHTTPRequest(HTTPMethod eHTTPRequestMethod, const char* pchAbsoluteURL) = 0;
	virtual bool SetHTTPRequestContextValue(HTTPRequestHandle hRequest, uint64_t ulContextValue) = 0;
	virtual bool SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle hRequest, uint32_t unTimeoutSeconds) = 0;
	virtual bool SetHTTPRequestHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, const char* pchHeaderValue) = 0;
	virtual bool SetHTTPRequestGetOrPostParameter(HTTPRequestHandle hRequest, const char* pchParamName, const char* pchParamValue) = 0;
	virtual bool SendHTTPRequest(HTTPRequestHandle hRequest, SteamAPICallHandle* pCallHandle) = 0;
	virtual bool SendHTTPRequestAndStreamResponse(HTTPRequestHandle hRequest, SteamAPICallHandle* pCallHandle) = 0;
	virtual bool DeferHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool PrioritizeHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool GetHTTPResponseHeaderSize(HTTPRequestHandle hRequest, const char* pchHeaderName, uint32_t* unResponseHeaderSize) = 0;
	virtual bool GetHTTPResponseHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, uint8_t* pHeaderValueBuffer, uint32_t unBufferSize) = 0;
	virtual bool GetHTTPResponseBodySize(HTTPRequestHandle hRequest, uint32_t* unBodySize) = 0;
	virtual bool GetHTTPResponseBodyData(HTTPRequestHandle hRequest, uint8_t* pBodyDataBuffer, uint32_t unBufferSize) = 0;
	virtual bool GetHTTPStreamingResponseBodyData(HTTPRequestHandle hRequest, uint32_t cOffset, uint8_t* pBodyDataBuffer, uint32_t unBufferSize) = 0;
	virtual bool ReleaseHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool GetHTTPDownloadProgressPct(HTTPRequestHandle hRequest, float* pflPercentOut) = 0;
	virtual bool SetHTTPRequestRawPostBody(HTTPRequestHandle hRequest, const char* pchContentType, uint8_t* pubBody, uint32_t unBodyLen) = 0;
};
class ISteamHTTPRequestCallback
{
public:
	virtual void Run(HTTPRequestCompleted* pvParam) = 0;
	virtual void Run(HTTPRequestCompleted* pvParam, bool bIOFailure, SteamAPICallHandle hSteamAPICall) = 0;
	virtual int GetCallbackSizeBytes()
	{
		return sizeof(HTTPRequestCompleted);
	};
protected:
	uint8_t m_nCallbackFlags = 0;
	int m_iCallback = HTTP_REQUEST_CALLBACK;
};

struct SteamContext
{
	void* __pad[11];
	ISteamHTTP* m_pSteamHTTP;
};