# Piwik Demo

## Install Docker

* https://docs.docker.com/install/
* https://docs.docker.com/compose/install/

## Start Server

    docker-compose up


## Login

    http://127.0.01:8080

Follow the instructions

* Database Server: db
* Login: root
* Password: securepassword
* Database name: matomo

Create superuser

User: root
Password: securepassword
Email: mail@example.org

## Create First App to Track

Name: QtExampleApp
Website: http://example.org
Time Zone: UTC
Ecommerce: No

## Add Tracker Code

Browse down to MobileApps and SDKs, in the list search for Qt.

Finish installation and login again

## Shutdown Server

Just press Ctrl-C or in a another shell, same directory

    docker-compose down




