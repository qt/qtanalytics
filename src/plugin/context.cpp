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
#include "context.h"
#include "configutil.h"


/*!
 * \class IContext
 * \inmodule QtAnalytics
 * \brief An interface to allow independent testing for builders.
 */

/*!
 * \class Context
 * \inmodule QtAnalytics
 * \brief A set of operations exposed to builders.
 */

IContext::~IContext()
{

}


Context::Context(QObject *parent)
    : QObject (parent)
    , m_network(nullptr)
{
}

Context::~Context()
{
}

QVariantMap Context::config() const
{
    return m_config;
}

// network provides access to the network manager
// to send requests.
QNetworkAccessManager *Context::network() const
{
    qDebug() << Q_FUNC_INFO;
    return m_network;
}

bool Context::hasNetwork() const
{
    return m_network != nullptr;
}

QVariant Context::configValue(const QString &key, const QVariant &defaultValue) const
{
    return m_config.value(key, defaultValue);
}

QString Context::configString(const QString &key, const QString &defaultValue) const
{
    return configValue(key, defaultValue).toString();
}

QNetworkReply *Context::httpGet(const QNetworkRequest &request) const
{
    qDebug() << Q_FUNC_INFO << request.url();
    return network()->get(request);
}

QNetworkReply *Context::httpPost(const QNetworkRequest &request, const QByteArray &data) const
{
    qDebug() << Q_FUNC_INFO << request.url() << data;
    return network()->post(request, data);
}

void Context::discoverNetwork(QObject *object)
{
    qDebug() << Q_FUNC_INFO;
    if (m_network) {
        return;
    }
    if (object) {
        // try network via qmlengine
        QQmlEngine *engine = qmlEngine(object);
        if (engine) {
            m_network = engine->networkAccessManager();
            connect(m_network, &QNetworkAccessManager::finished, this, &Context::onReplyFinished);
        }
    }
    // create a custome network manager
    if (!m_network) {
        m_network = new QNetworkAccessManager(this);
        connect(m_network, &QNetworkAccessManager::finished, this, &Context::onReplyFinished);
    }
}

void Context::onReplyFinished(QNetworkReply *reply)
{
    qDebug() << "reply finished: " << reply->url().toString();
}

void Context::setConfig(const QVariantMap &config)
{
    m_config = config;
}

void Context::updateConfig(const QVariantMap &o)
{
    setConfig(ConfigUtil::mergeMap(m_config, o));
}

void Context::setNetwork(QNetworkAccessManager *network)
{
    m_network = network;
}

