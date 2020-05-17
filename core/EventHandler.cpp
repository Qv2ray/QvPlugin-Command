#include "EventHandler.hpp"

#include "CommandPlugin.hpp"

using namespace Qv2rayPlugin;
SimpleEventHandler::SimpleEventHandler(QObject *parent) : Qv2rayPlugin::QvPluginEventHandler(parent)
{
}

QvPlugin_EventHandler(SimpleEventHandler, Connectivity)
{
    ///
    /// Variables:
    /// $$DISPLAYNAME
    /// $$INBOUND_inboundProtocol
    ///  --> port for that protocol, (e.g. $INBOUND_http as HTTP port)
    ///
    const auto settings = CommandPlugin::instance->Settings();

    QStringList actions;
    switch (pluginEvent.eventType)
    {
        case Events::Connectivity::Connected:
        {
            actions << settings.afterConnection.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::Connectivity::Connecting:
        {
            actions << settings.beforeConnection.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::Connectivity::Disconnected:
        {
            actions << settings.afterDisConnection.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::Connectivity::Disconnecting:
        {
            actions << settings.beforeDisConnection.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
    }
    for (const auto &action : actions)
    {
        auto _command = action;
        _command.replace("$$DISPLAYNAME", pluginEvent.displayName);
        for (const auto &protocol : pluginEvent.inboundPorts.keys())
        {
            _command.replace("$$INBOUND_" + protocol, QString::number(pluginEvent.inboundPorts[protocol]));
        }
        bool detached = _command.contains("$$CALL");
        _command.replace("$$CALL", "");
        if (detached)
        {
            auto returnvalue = QProcess::execute(_command);
            if (returnvalue != 0)
            {
                CommandPlugin::instance->PluginLog("Failed to execute command : \"" + action + "\"");
            }
        }
        else
        {
            QProcess::startDetached(_command);
        }
    }
}
QvPlugin_EventHandler(SimpleEventHandler, SystemProxy)
{
    ///
    /// Variables:
    /// $$HTTP: HTTP port (could be 0)
    /// $$SOCKS: SOCKS port (could be 0)
    ///
    const auto settings = CommandPlugin::instance->Settings();
    QStringList actions;
    switch (pluginEvent.systemProxyState)
    {
        case Events::SystemProxy::SetProxy:
        {
            actions << settings.setSystemProxy.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::SystemProxy::ClearProxy:
        {
            actions << settings.clearSystemProxy.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
    }
    for (const auto &action : actions)
    {
        auto _command = action;
        _command.replace("$$HTTP", QString::number(pluginEvent.systemProxyPortSettings[Events::SystemProxy::SystemProxy_HTTP]));
        _command.replace("$$SOCKS", QString::number(pluginEvent.systemProxyPortSettings[Events::SystemProxy::SystemProxy_SOCKS]));
        bool detached = _command.contains("$$CALL");
        _command.replace("$$CALL", "");
        if (detached)
        {
            auto returnvalue = QProcess::execute(_command);
            if (returnvalue != 0)
            {
                CommandPlugin::instance->PluginLog("Failed to execute command : \"" + action + "\"");
            }
        }
        else
        {
            QProcess::startDetached(_command);
        }
    }
}
QvPlugin_EventHandler(SimpleEventHandler, ConnectionEntry)
{
    ///
    /// Variables:
    /// $$DISPLAYNAME
    /// $$ORIGINAL_NAME
    ///
    const auto settings = CommandPlugin::instance->Settings();
    QStringList actions;
    switch (pluginEvent.eventType)
    {
        case Events::ConnectionEntry::Created:
        {
            actions << settings.connectionCreated.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::ConnectionEntry::FullyRemoved:
        case Events::ConnectionEntry::RemovedFromGroup:
        {
            actions << settings.connectionDeleted.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::ConnectionEntry::Renamed:
        {
            actions << settings.connectionRenamed.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::ConnectionEntry::Edited:
        {
            actions << settings.connectionUpdated.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
            break;
        }
        case Events::ConnectionEntry::LinkedWithGroup:
        {
            break;
        }
    }
    for (const auto &action : actions)
    {
        auto _command = action;
        _command.replace("$$DISPLAYNAME", pluginEvent.displayName);
        _command.replace("$$ORIGINAL_NAME", pluginEvent.originalDisplayName);
        bool detached = _command.contains("$$CALL");
        _command.replace("$$CALL", "");
        if (detached)
        {
            auto returnvalue = QProcess::execute(_command);
            if (returnvalue != 0)
            {
                CommandPlugin::instance->PluginLog("Failed to execute command : \"" + action + "\"");
            }
        }
        else
        {
            QProcess::startDetached(_command);
        }
    }
}
