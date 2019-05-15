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

#include "hitbuilder.h"
#include "context.h"

/*!
 * \class HitBuilder
 * \inmodule QtAnalytics
 * \brief An abstract interface for tracking platforms.
 */

HitBuilder::HitBuilder(Context *context, QObject *parent)
    : QObject(parent)
    , m_context(context)
{
}

HitBuilder::~HitBuilder()
{
}

void HitBuilder::initQuery()
{
    m_url = QUrl(configString("server"));
}

void HitBuilder::trackPage(const QString &/*path*/, const QString &/*title*/)
{
}

void HitBuilder::trackEvent(const QString &/*category*/, const QString &/*action*/, const QString &/*label*/, const QString &/*value*/)
{
}

QNetworkReply *HitBuilder::sendQuery()
{
    QUrl url(m_url);
    qDebug() << "url to request: " << url;
    url.setQuery(query());
    qDebug() << "url to request: " << url;
    QNetworkRequest request(url);
    // by default use http get requests
    return httpGet(request);
}

void HitBuilder::reset()
{
    m_query.clear();
    m_url.clear();
}


void HitBuilder::addQueryItem(const QString &key, const QString &value)
{
    if (value.isEmpty()) {
        return;
    }
    m_query.addQueryItem(key, value);
}

void HitBuilder::configQueryItem(const QString &key, const QString &defaultValue)
{
    QString value = configString(key, defaultValue);
    if (value.isEmpty()) {
        return;
    }
    m_query.addQueryItem(key, value);
}

QVariant HitBuilder::configValue(const QString &key, const QVariant &defaultValue) const
{
    return context()->configValue(key, defaultValue);
}

QString HitBuilder::configString(const QString &key, const QString &defaultValue) const
{
    return context()->configString(key, defaultValue);
}

QNetworkReply *HitBuilder::httpGet(const QNetworkRequest &request)
{
    return context()->httpGet(request);
}

QNetworkReply *HitBuilder::httpPost(const QNetworkRequest &request, const QByteArray &data)
{
    return context()->httpPost(request, data);
}

Context *HitBuilder::context() const
{
    return m_context;
}

QUrlQuery HitBuilder::query() const
{
    return m_query;
}

QUrl HitBuilder::url() const
{
    return m_url;
}

