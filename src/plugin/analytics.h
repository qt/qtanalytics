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
#include <QtQml>
#include <QtNetwork>

class Context;
class HitBuilder;
class Analytics;

class AnalyticsAttached : public QObject
{
    Q_OBJECT

    /**
     * In QML it shall look like
     *  Analytics.customVariables: {
     *     "myVariable1": "myValue1",
     *     "myVariable2": "myValue2"
     *  }
     */
    Q_PROPERTY(QVariantMap variables READ variables WRITE setVariables NOTIFY variablesChanged)
public:
    AnalyticsAttached(QObject *parent = nullptr);
    virtual ~AnalyticsAttached();

    Q_INVOKABLE void sendPing();
    Q_INVOKABLE void sendVisit(const QString &path, const QString &name);
    Q_INVOKABLE void sendEvent(const QString &category, const QString &action, const QString &name, const QString &value);

    QVariantMap variables() const { return m_variables; }

public slots:
    void setVariables(QVariantMap variables);

signals:
    void variablesChanged();

private:
    QVariantMap m_variables;
};


class Analytics : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Analytics)
public:
    explicit Analytics(QObject *parent = nullptr);
    virtual ~Analytics();

    static Analytics *instance(QObject *attached);
    static AnalyticsAttached* qmlAttachedProperties(QObject* );
    HitBuilder *getBuilder();
    void sendPing();
    void sendVisit(const QString &path, const QString &name);
    void sendEvent(const QString &category, const QString &action,
                   const QString &name, const QString &value);
    Context *context() const;

private:
    //    QString userAgent() const;
    //    QString userLanguage() const;
    void dispatch(HitBuilder *builder);
    void processQueue();
    void onReplyFinished(QNetworkReply* reply);
signals:
    void sendHitRequest(const QUrl& url);
    void replyFinished(QNetworkReply* reply);
private:
    static Analytics *s_instance;
    Context *m_context;
    HitBuilder *m_builder;
};



QML_DECLARE_TYPEINFO(Analytics, QML_HAS_ATTACHED_PROPERTIES)
