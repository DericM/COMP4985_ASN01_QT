

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <winsock2.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_g1_resolve_clicked()
{
    struct	hostent *hp;
    struct  in_addr in;
    char	**p;

    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);

    QString qHost = ui->g1_host->text();
    std::string str = qHost.toStdString();
    const char* host = str.c_str();

    if ((hp = gethostbyname (host)) == NULL)
    {
        return;
    }

    p = hp->h_addr_list;
    memcpy(&in.s_addr, *p, sizeof (in.s_addr));

    ui->output->append(inet_ntoa(in));
    WSACleanup();
}

void MainWindow::on_g2_resolve_clicked()
{
    int		a;
    struct	hostent *hp;
    struct	in_addr my_addr, *addr_p;
    char	ip_address[256];      // String for IP address
    char	**p;

    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);

    addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
    addr_p = &my_addr;

    QString qIP = ui->g2_ip->text();
    std::string str = qIP.toStdString();
    const char* IP = str.c_str();

    if (!isdigit(IP[1]))	// Dotted IP?
    {
        return;
    }

    if ((a = inet_addr(IP)) == 0)
    {
        return;
    }

    strcpy(ip_address, IP);
    addr_p->s_addr=inet_addr(ip_address) ;

    hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof (my_addr));

    if (hp == NULL)
    {
        return;
    }

    for (p = hp->h_addr_list; *p != 0; p++)
    {
        struct in_addr in;
        char **q;

        ui->output->append(hp->h_name);


        for (q = hp->h_aliases; *q != 0; q++){
            QString print = "\tAliases: ";
            print.append(*q);
            ui->output->append(print);
        }
            //printf(" \t\t\t\t   Aliases: %s\n", );
        //putchar('\n');
    }

    //ui->output->append(hp->h_name);
    WSACleanup();
}

void MainWindow::on_g3_resolve_clicked()
{
    struct servent *sv;

    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);

    QString qService = ui->g3_service->text();
    std::string str = qService.toStdString();
    const char* service = str.c_str();
    QString qProtocol = ui->g3_protocol->text();
    std::string str2 = qProtocol.toStdString();
    const char* protocol = str2.c_str();

    sv = getservbyname (service, protocol);
    if (sv == NULL)
    {
        return;
    }

    int numberPort = ntohs(sv->s_port);
    QString print = QString::number(numberPort);
    ui->output->append(print);
    WSACleanup();
}

void MainWindow::on_g4_resolve_clicked()
{
    struct servent *sv;
    int s_port;

    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);

    QString qPort = ui->g4_port->text();
    std::string str = qPort.toStdString();
    const char* port = str.c_str();
    QString qProtocol = ui->g4_protocol->text();
    std::string str2 = qProtocol.toStdString();
    const char* protocol = str2.c_str();

    s_port = atoi(port);

    sv = getservbyport (htons(s_port), protocol);
    if (sv == NULL)
    {
        return;
    }

    ui->output->append(sv->s_name);
    WSACleanup();
}
