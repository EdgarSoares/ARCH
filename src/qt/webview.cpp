/*
 * Qt5 webview naviagation
 *
 * Developed by OnsightIT 2014-2015
 * onsightit@gmail.com
 */
#include "webview.h"
#include "util.h"

#include <QPushButton>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <stdarg.h>

using namespace std;

WebView::WebView(QWidget *parent) :
    QWebView(parent)
{
}

WebView::~WebView()
{
}

// Receives web nav buttons from parent webview
void WebView::sendButtons(QPushButton *bb, QPushButton *hb, QPushButton *fb, QLineEdit *ule, QPushButton *ulb)
{
    // Get the addresses of the nav buttons
    backButton = bb;
    homeButton = hb;
    forwardButton = fb;
    urlLineEdit = ule;
    urlLoadButton = ulb;

    if (!urlLineEdit) return;

    urlLineEdit->setPlaceholderText("Enter an i2p address");
}

void WebView::myBack()
{
    if (this->history()->currentItemIndex() > 1) // 0 is a blank page
    {
        this->back();
    }
    setButtonStates((this->history()->currentItemIndex() > 1), (this->history()->currentItemIndex() > 1), this->history()->canGoForward());
}

void WebView::myHome()
{
    if ((this->history()->currentItemIndex() > 1))
    {
        this->history()->goToItem(this->history()->itemAt(1)); // 0 is a blank page
    }
    setButtonStates((this->history()->currentItemIndex() > 1), (this->history()->currentItemIndex() > 1), this->history()->canGoForward());
}

void WebView::myForward()
{
    if (this->history()->canGoForward())
    {
        this->forward();
    }
    setButtonStates((this->history()->currentItemIndex() > 1), (this->history()->currentItemIndex() > 1), this->history()->canGoForward());
}

void WebView::myReload()
{
    this->reload();
}

void WebView::myOpenUrl(QUrl url)
{
    try
    {
        this->load(url);
    }
    catch (...)
    {
        printf("WebView: Error loading: %s\n", url.toString().toStdString().c_str());
    }
    // This uses canGoBack() and currentItemIndex > 0 as opposed to currentItemIndex > 1 like the other setButtonStates calls.
    setButtonStates(this->history()->canGoBack(), (this->history()->currentItemIndex() > 0), this->history()->canGoForward());
}

void WebView::myLoadUrl()
{
    QUrl url;

    if (!urlLineEdit) return;

    if (!urlLineEdit->text().isEmpty() && urlLineEdit->text().contains(".i2p"))
    {
        url.setUrl(urlLineEdit->text());
        myOpenUrl(url);
    }
    else
    {
        urlLineEdit->setText("");
        urlLineEdit->setPlaceholderText("Invalid i2p address");
    }
}

// Set button enabled/disabled states
void WebView::setButtonStates(bool canGoBack, bool canGoHome, bool canGoForward)
{
    backButton->setEnabled(canGoBack);
    homeButton->setEnabled(canGoHome);
    forwardButton->setEnabled(canGoForward);
}

void WebView::sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist)
{
    qnr->ignoreSslErrors();
}
