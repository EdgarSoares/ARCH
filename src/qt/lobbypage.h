#ifndef LOBBYPAGE_H
#define LOBBYPAGE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QTimer>

namespace Ui {
    class LobbyPage;
}
class ClientModel;
class WalletModel;

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Trade page widget */
class LobbyPage : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyPage(QWidget *parent = 0);
    ~LobbyPage();

    void setModel(ClientModel *clientModel);
    void setModel(WalletModel *walletModel);

public slots:

// signals:

private:
    Ui::LobbyPage *ui;
    ClientModel *clientModel;
    WalletModel *walletModel;

private slots:

};

#endif // LOBBYPAGE_H
