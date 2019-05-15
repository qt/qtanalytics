/****************************************************************************
**
** Copyright (C) 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the analytics module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#pragma once

#include <QtCore>
#include <QtNetwork>
#include <QtQml>

class IContext {
public:
    virtual ~IContext();
    virtual QVariant configValue(const QString &key, const QVariant &defaultValue) const = 0;
    virtual QNetworkReply* httpGet(const QNetworkRequest& request) const = 0;
    virtual QNetworkReply* httpPost(const QNetworkRequest& request, const QByteArray &data) const = 0;
};

class Context : public QObject, public IContext
{
    Q_OBJECT
public:
    Context(QObject *parent=nullptr);
    ~Context();
    void setConfig(const QVariantMap &config);
    void updateConfig(const QVariantMap &o);
    QVariantMap config() const;
    void setNetwork(QNetworkAccessManager *network);
    QNetworkAccessManager *network() const;
    bool hasNetwork() const;
    QVariant configValue(const QString &key, const QVariant &defaultValue=QVariant()) const;
    QString configString(const QString &key, const QString &defaultValue=QString()) const;
    QNetworkReply* httpGet(const QNetworkRequest& request) const;
    QNetworkReply* httpPost(const QNetworkRequest& request, const QByteArray &data) const;
    void discoverNetwork(QObject *object);
    void onReplyFinished(QNetworkReply *reply);
private:
    QVariantMap m_config;
    QNetworkAccessManager *m_network;
};
