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

#include "analytics.h"
#include "hitbuilder.h"
#include "matomobuilder.h"
#include "googlebuilder.h"
#include "configutil.h"
#include "context.h"

/*!
 * \qmlmodule Analytics
 */

/*!
 * \qmltype Analytics
 * \inqmlmodule Analytics
 * \brief Provides tracking operations for visits and events.

 * To use this API you need to have an analytics.json configuration file located
 * either as resource file or in your home folder. The configuration file needs to provide the
 * server url, tracker id, client id as a minimum.

 * The API will send request to the Matomo server to track certain user interface statistics. You need to
 * place tracking code inside your user interface to track this behavior.
 */

/*!
 * \class AnalyticsAttached
 * \inmodule QtAnalytics
 * \brief The attached object to the Analytics.
 */

/*!
 * \class Analytics
 * \inmodule QtAnalytics
 * \brief Proxy class to access the selected tracker platform.
 */

/*!
 * \brief Construct a new attached object.
 * \param parent Parent object
 */
AnalyticsAttached::AnalyticsAttached(QObject *parent)
    : QObject(parent)
{
}

AnalyticsAttached::~AnalyticsAttached()
{
}

/*!
 * \qmlmethod void Analytics::sendPing()
 * Sends a heartbeat request to the tracking server
 *
 * A ping will only update the visit's total time.
 * It is used to provide accurate "visit duration" metrics.
 */
void AnalyticsAttached::sendPing()
{
    Analytics::instance(this)->sendPing();
}

/*!
 * \qmlmethod void Analytics::sendVisit(path, action, dimensions)
 *
 * Sends a visit request to the tracking server
 *
 * The visit location will be identified by the \a path. The optional \a action identifies what is happening. The optional \a dimensions allows you
 * to send further information as defined by the servers custom dimensions. Additional to this information also the
 * custom variables defined will be send to the server.
 *
 */
void AnalyticsAttached::sendVisit(const QString &path, const QString &action)
{
    Analytics::instance(this)->sendVisit(path, action);
}

/*!
 * \qmlmethod void Analytics::sendEvent(path, category, action, name, int value, dimensions)
 *
 * Sends an event request to the tracking server. The path provides the location inside the user interface.
 * The action what is happening. The event category where somethign is heppening (e.g. videos, music. games). The
 * name the event name to track. A value can be an additional information to track. Additional you can provide
 * a set of key/value pairs as defined on the Matamo server.
 */
void AnalyticsAttached::sendEvent(const QString &category, const QString &action,
                                  const QString &name, const QString &value)
{
    Analytics::instance(this)->sendEvent(category, action, name, value);
}

void AnalyticsAttached::setVariables(QVariantMap customVariables)
{
    if (m_variables == customVariables) {
        return;
    }
    m_variables = customVariables;
    emit variablesChanged();
}


// Analytics

Analytics* Analytics::s_instance = nullptr;

Analytics::Analytics(QObject *parent)
    : QObject(parent)
    , m_context(new Context(this))
    , m_builder(nullptr)
{
    const QJsonObject& data = ConfigUtil::loadJSON("analytics");
    const QVariantMap& o = ConfigUtil::toVariantMap(data);
    m_context->setConfig(o);
}

Analytics::~Analytics()
{
}

Analytics *Analytics::instance(QObject *attached)
{
    qDebug() << Q_FUNC_INFO;
    if (!Analytics::s_instance) {
        Analytics::s_instance = new Analytics(QCoreApplication::instance());
    }
    if (attached && !Analytics::s_instance->context()->hasNetwork()) {
        Analytics::s_instance->context()->discoverNetwork(attached->parent());
    }
    return Analytics::s_instance;
}

AnalyticsAttached *Analytics::qmlAttachedProperties(QObject* object)
{
    return new AnalyticsAttached(object);
}

void Analytics::sendPing()
{
    qDebug() << Q_FUNC_INFO;
}


void Analytics::sendVisit(const QString &path, const QString &action)
{
    qDebug() << Q_FUNC_INFO << path << action;
    HitBuilder* builder = getBuilder();
    if (builder) {
        builder->initQuery();
        builder->trackPage(path, action);
        builder->sendQuery();
        builder->reset();
    }
}


void Analytics::sendEvent( const QString &category,
                           const QString &action, const QString &name,
                           const QString &value) {

    qDebug() << Q_FUNC_INFO << category << action;
    HitBuilder* builder = getBuilder();
    if (builder) {
        builder->initQuery();
        builder->trackEvent(category, action, name, value);
        builder->sendQuery();
        builder->reset();
    }
}


HitBuilder* Analytics::getBuilder()
{
    if (!m_builder) {
        QString tracker = context()->configString("tracker");
        qDebug() << "found tracker " << tracker;
        if (tracker == "matomo") {
            m_builder = new MatomoBuilder(context(), this);
        } else if (tracker == "google") {
            m_builder = new GoogleBuilder(context(), this);
        } else {
            qWarning() << "not supported builder" << tracker;
        }
    }
    return m_builder;
}

void Analytics::onReplyFinished(QNetworkReply *reply)
{
    emit replyFinished(reply);
    qDebug() << "network reply finished: " << reply->url();
    reply->deleteLater();
}

Context *Analytics::context() const
{
    return m_context;
}

//QString Analytics::userAgent() const
//{
//    const QString& name = settings()->value("applicationName").toString();
//    const QString& version = settings()->value("applicationVersion").toString();
//    const QString& lang = userLanguage();
//    const QString& os = settings()->value("os").toString();
//    return QString("%1/%2 (%3;%4) Analytics/1.0 (Qt/%5)").arg(name).arg(version).arg(os).arg(lang).arg(QT_VERSION_STR);
//}

//QString Analytics::userLanguage() const
//{
//    return QLocale::system().name().toLower().replace("_", "-");
//}

