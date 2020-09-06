#pragma once

#include "QvPluginInterface.hpp"
#include "core/CommandConfig.hpp"
#include "core/EventHandler.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class CommandPlugin
    : public QObject
    , Qv2rayInterface
{
    Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
    Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
    Q_OBJECT
  public:
    //
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{
            "Qv2ray Command Plugin",                             //
            "Qv2ray Workgroup",                                  //
            "qvplugin_command",                                  //
            "Run any command when an event from Qv2ray occurs.", //
            "v3.0.0",                                            //
            "Qv2ray/QvPlugin-Command",                           //
            {
                COMPONENT_EVENT_HANDLER, //
                COMPONENT_GUI            //
            },
            UPDATE_GITHUB_RELEASE //
        };
    }
    bool InitializePlugin(const QString &, const QJsonObject &) override;

  signals:
    void PluginLog(const QString &) const override;
    void PluginErrorMessageBox(const QString &, const QString &) const override;
};
