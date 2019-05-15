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
#include "googlebuilder.h"

#include "context.h"


/*!
 * \class GoogleBuilder
 * \inmodule QtAnalytics
 * \brief Plugin for the google tracking platform.
 */

// See https://developers.google.com/analytics/devguides/collection/protocol/v1/

const QString GoogleBuilder::TRACKER_ID("tid");
const QString GoogleBuilder::VERSION("v");
const QString GoogleBuilder::DATA_SOURCE("ds");
const QString GoogleBuilder::DOCUMENT_PATH("dp");
const QString GoogleBuilder::DOCUMENT_TITLE("dt");
const QString GoogleBuilder::EVENT_CATEGORY("ec");
const QString GoogleBuilder::EVENT_ACTION("ea");
const QString GoogleBuilder::EVENT_LABEL("el");
const QString GoogleBuilder::EVENT_VALUE("ev");
const QString GoogleBuilder::HIT_TYPE("t");
const QString GoogleBuilder::CLIENT_ID("cid");

GoogleBuilder::GoogleBuilder(Context *context, QObject *parent)
    : HitBuilder(context, parent)
{
}

GoogleBuilder::~GoogleBuilder()
{
}

void GoogleBuilder::initQuery()
{
    const QString& server = configString("server", "https://www.google-analytics.com/collect");
    m_url = QUrl(server);
    addQueryItem(VERSION, "1");
    configQueryItem(TRACKER_ID);
    configQueryItem(CLIENT_ID);
}

void GoogleBuilder::trackPage(const QString &path, const QString &title)
{
    addQueryItem(HIT_TYPE, "pageview");
    addQueryItem(DOCUMENT_PATH, path);
    addQueryItem(DOCUMENT_TITLE, title);
}

void GoogleBuilder::trackEvent(const QString &category, const QString &action, const QString &label, const QString &value)
{
    addQueryItem(EVENT_CATEGORY, category);
    addQueryItem(EVENT_ACTION, action);
    if (!label.isNull()) {
        addQueryItem(EVENT_LABEL, label);
    }
    if (!value.isNull()) {
        addQueryItem(EVENT_VALUE, value);
    }
}

QNetworkReply *GoogleBuilder::sendQuery()
{
    return HitBuilder::sendQuery();
}
