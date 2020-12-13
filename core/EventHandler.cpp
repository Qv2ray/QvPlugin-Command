#include "EventHandler.hpp"

#include "CommandPlugin.hpp"

#include <QProcess>

#if QT_VERSION_MAJOR >= 6
using QRegExp = QRegularExpression;
    #define SkipEmpty Qt::SkipEmptyParts
#else
    #define SkipEmpty QString::SkipEmptyParts
#endif

using namespace Qv2rayPlugin;
SimpleEventHandler::SimpleEventHandler() : Qv2rayPlugin::PluginEventHandler(){};
QvPlugin_EventHandler(SimpleEventHandler, Connectivity)
{
    ///
    /// Variables:
    /// $$DISPLAYNAME
    /// $$INBOUND_inboundProtocol
    ///  --> port for that protocol, (e.g. $INBOUND_http as HTTP port)
    ///
    const auto settings = CommandPluginConfig::fromJson(CommandPluginInstance->GetSettngs());

    QStringList actions;
    switch (pluginEvent.eventType)
    {
        case Events::Connectivity::Connected:
        {
            actions << settings.afterConnection.split(QRegExp("[\r\n]"), SkipEmpty);
            break;
        }
        case Events::Connectivity::Connecting:
        {
            actions << settings.beforeConnection.split(QRegExp("[\r\n]"), SkipEmpty);
            break;
        }
        case Events::Connectivity::Disconnected:
        {
            actions << settings.afterDisConnection.split(QRegExp("[\r\n]"), SkipEmpty);
            break;
        }
        case Events::Connectivity::Disconnecting:
        {
            actions << settings.beforeDisConnection.split(QRegExp("[\r\n]"), SkipEmpty);
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
                CommandPluginInstance->PluginLog("Failed to execute command : \"" + action + "\"");
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
    const auto settings = CommandPluginConfig::fromJson(CommandPluginInstance->GetSettngs());
    QStringList actions;
    switch (pluginEvent.systemProxyState)
    {
        case Events::SystemProxy::SetProxy:
        {
            actions << settings.setSystemProxy.split(QRegExp("[\r\n]"), SkipEmpty);
            break;
        }
        case Events::SystemProxy::ClearProxy:
        {
            actions << settings.clearSystemProxy.split(QRegExp("[\r\n]"), SkipEmpty);
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
                CommandPluginInstance->PluginLog("Failed to execute command : \"" + action + "\"");
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
    const auto settings = CommandPluginConfig::fromJson(CommandPluginInstance->GetSettngs());
    QStringList actions;
    switch (pluginEvent.eventType)
    {
        case Events::ConnectionEntry::Created:
        {
            actions << settings.connectionCreated.split(QRegExp("[\r\n]"), SkipEmpty);
            break;
        }
        case Events::ConnectionEntry::FullyRemoved:
        case Events::ConnectionEntry::RemovedFromGroup:
        {
            actions << settings.connectionDeleted.split(QRegExp("[\r\n]"), SkipEmpty);
            break;
        }
        case Events::ConnectionEntry::Renamed:
        {
            actions << settings.connectionRenamed.split(QRegExp("[\r\n]"), SkipEmpty);
            break;
        }
        case Events::ConnectionEntry::Edited:
        {
            actions << settings.connectionUpdated.split(QRegExp("[\r\n]"), SkipEmpty);
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
                CommandPluginInstance->PluginLog("Failed to execute command : \"" + action + "\"");
            }
        }
        else
        {
            QProcess::startDetached(_command);
        }
    }
}
