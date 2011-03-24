#include "webview.h"
#include <QWebPage>
#include <QWebFrame>
#include <assert.h>
#include <string.h>

#include <QImage>
#include <QPainter>
#include "simple_texture.h"

struct WebView
{
    QWebPage* qpage;
};

WebView* CreateWebView(const char* Provider)
{
    assert(strcmp(Provider, "webkit") == 0);

    WebView* view = new WebView();
    view->qpage = new QWebPage();

    view->qpage->mainFrame()->load(QUrl("http://www.google.com"));

    return view;
}

void DestroyWebView(WebView* view)
{
    delete view->qpage;
    delete view;
}

bitmap* WebViewGetPixelData(WebView* view)
{
    QSize size(400, 400);
    view->qpage->setViewportSize(size);

    QImage img(size, QImage::Format_RGB32);
    QPainter painter(&img);

    view->qpage->mainFrame()->render(&painter);
    painter.end();

    assert(img.width() * img.height() * 4 == img.numBytes());
    int* data = new int[img.numBytes()/4];
    const int* pixels = (int*)((const QImage)img).bits();
    for(int i=0; i<img.numBytes()/4; i++)
    {
        data[i] = pixels[i] << 8;
    }
    //memcpy(data, ((const QImage)img).bits(), img.numBytes());

    return create_bitmap(img.width(),
                         img.height(),
                         data,
                         data);
}
