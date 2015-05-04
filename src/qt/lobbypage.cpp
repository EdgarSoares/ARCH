#include "lobbypage.h"
#include "ui_lobbypage.h"

#include "clientmodel.h"
#include "walletmodel.h"
#include "guiutil.h"
#include "guiconstants.h"
#include "util.h"
#include "webview.h"

using namespace GUIUtil;

LobbyPage::LobbyPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LobbyPage),
    walletModel(0)
{
    ui->setupUi(this);

    this->layout()->setContentsMargins(0, 0, 0, 0);

    ui->webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAsNeeded);
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    ui->frame->setVisible(true); // Set to true to enable webView navigation buttons
    connect(ui->webView->page()->networkAccessManager(), SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )), ui->webView, SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> & )));
    connect(ui->webView->page(), SIGNAL(linkClicked(QUrl)), ui->webView, SLOT(myOpenUrl(QUrl)));

    // buttons
    ui->back->setDisabled(true);
    ui->home->setDisabled(true);
    ui->forward->setDisabled(true);
    ui->webView->sendButtons(ui->back, ui->home, ui->forward);
    connect(ui->back, SIGNAL(clicked()), ui->webView, SLOT(myBack()));
    connect(ui->home, SIGNAL(clicked()), ui->webView, SLOT(myHome()));
    connect(ui->forward, SIGNAL(clicked()), ui->webView, SLOT(myForward()));
    connect(ui->reload, SIGNAL(clicked()), ui->webView, SLOT(myReload()));
}

LobbyPage::~LobbyPage()
{
    delete ui;
}

void LobbyPage::setModel(WalletModel *model)
{
    this->walletModel = model;

    QUrl url("https://archcoin.co/wlt/lobby/index.htm");
    ui->webView->myOpenUrl(url);
}
