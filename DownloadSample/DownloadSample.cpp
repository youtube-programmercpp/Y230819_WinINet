// WinINet 使用サンプル Copyright(C) 2023 https://www.youtube.com/programmercpp
#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "WinInet")
#include <fstream>

int main()
{
	// WinINet 使用開始に先立って InternetOpenA 関数を呼び出す
	if (const auto hInternet = InternetOpenA
	( /*_In_opt_ LPCSTR lpszAgent      */"downloader"
	, /*_In_     DWORD  dwAccessType   */INTERNET_OPEN_TYPE_PRECONFIG
	, /*_In_opt_ LPCSTR lpszProxy      */nullptr
	, /*_In_opt_ LPCSTR lpszProxyBypass*/nullptr
	, /*_In_     DWORD  dwFlags        */0
	)) {
		//URL を開く
		if (const auto hRequest = InternetOpenUrlA
		( /*_In_                            HINTERNET hInternet      */hInternet
		, /*_In_                            LPCSTR    lpszUrl        */"https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q10284688440"
		, /*_In_reads_opt_(dwHeadersLength) LPCSTR    lpszHeaders    */nullptr  
		, /*_In_                            DWORD     dwHeadersLength*/0
		, /*_In_                            DWORD     dwFlags        */0
		, /*_In_opt_                        DWORD_PTR dwContext      */0
		)) {
			//内容を読み取ってファイルに保存する
			if (std::ofstream file{ "q10284688440.htm", std::ios_base::binary }) {
				for (;;) {
					DWORD cbBuf        ;
					char  rgchBuf[4096];
					if (::InternetReadFile
					( /*_In_                                                                 HINTERNET hFile                */       hRequest
					, /*_Out_writes_bytes_(dwNumberOfBytesToRead) __out_data_source(NETWORK) LPVOID    lpBuffer             */       rgchBuf 
					, /*_In_                                                                 DWORD     dwNumberOfBytesToRead*/sizeof rgchBuf 
					, /*_Out_                                                                LPDWORD   lpdwNumberOfBytesRead*/       &cbBuf  
					)) {
						if (cbBuf) {
							//ローカルファイルに書き出す
							if (file.write(rgchBuf, cbBuf))
								continue;//成功したので継続
							else
								break;//エラー
						}
						else
							break;//読み込み終了
					}
				}
			}
			(void)InternetCloseHandle(hRequest);
		}
		(void)InternetCloseHandle(hInternet);
	}
}
/*
https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q10284688440
ID非公開さん

2023/8/19 13:46

1回答

C++でC#のDownloadStringのようなURLからテキストを取得する方法を教えてください

C言語関連・10閲覧・50
*/
