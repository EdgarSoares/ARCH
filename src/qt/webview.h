/*
 * Qt5 webview naviagation
 *
 * Developed by OnsightIT 2014-2015
 * onsightit@gmail.com
 */
#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>
#include <QWebFrame>
#include <QWebHistory>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QUrl>

namespace Ui {
class WebView;
}

class WebView : public QWebView
{
    Q_OBJECT

public:
    explicit WebView(QWidget *parent = 0);
    ~WebView();

    // Receives web nav buttons from parent webview
    void sendButtons(QPushButton *bb, QPushButton *hb, QPushButton *fb, QLineEdit *ule = 0, QPushButton *ulb = 0);

public slots:
    void myBack();
    void myHome();
    void myForward();
    void myReload();
    void myLoadUrl();
    void myOpenUrl(QUrl url);
    void sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist);

private:
    Ui::WebView *ui;

    bool fTrustedUrlsSet;
    // Forwarded button addresses
    QPushButton *backButton;
    QPushButton *homeButton;
    QPushButton *forwardButton;
    QPushButton *urlLoadButton;
    QLineEdit *urlLineEdit;

    // Set button enabled/disabled states
    void setButtonStates(bool canGoBack, bool canGoHome, bool canGoForward);

    QList<QString> trustedUrls;
};

#endif // WEBVIEW_H
