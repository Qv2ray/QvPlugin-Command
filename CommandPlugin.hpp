#pragma once

#include "QvPluginInterface.hpp"
#include "core/CommandConfig.hpp"
#include "core/EventHandler.hpp"

#include <QObject>
#include <QtPlugin>

class QLabel;
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
            QIcon(":/assets/qv2ray.png"),                        //
            { CAPABILITY_CONNECTION_ENTRY,                       //
              CAPABILITY_CONNECTIVITY,                           //
              CAPABILITY_SYSTEM_PROXY },                         //
            {}                                                   //
        };
    }
    //
    std::shared_ptr<QvPluginKernel> GetKernel() override;
    std::shared_ptr<QvPluginSerializer> GetSerializer() override;
    std::shared_ptr<QvPluginEventHandler> GetEventHandler() override;
    std::unique_ptr<QvPluginEditor> GetEditorWidget(UI_TYPE) override;
    std::unique_ptr<QWidget> GetSettingsWidget() override;
    //
    static CommandPlugin *instance;
    //
    bool UpdateSettings(const QJsonObject &) override;
    bool Initialize(const QString &, const QJsonObject &) override;
    const QJsonObject GetSettngs() override;
    const CommandPluginConfig Settings()
    {
        return settings;
    }
    //
  signals:
    void PluginLog(const QString &) const override;
    void PluginErrorMessageBox(const QString &) const override;

  private:
    CommandPluginConfig settings;
    std::shared_ptr<QvPluginEventHandler> eventHandler;
};
