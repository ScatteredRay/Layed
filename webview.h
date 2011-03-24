#ifndef _WEBVIEW_H_
#define _WEBVIEW_H_

struct WebView;

WebView* CreateWebView(const char* Provider);
void DestroyWebView(WebView* view);
struct bitmap* WebViewGetPixelData(WebView* view);

#endif //_WEBVIEW_H_
