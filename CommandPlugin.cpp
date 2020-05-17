#include "CommandPlugin.hpp"

#include "ui/CommandPluginSettings.hpp"

CommandPlugin *CommandPlugin::instance = nullptr;

std::unique_ptr<QvPluginKernel> CommandPlugin::CreateKernel()
{
    return nullptr;
}

bool CommandPlugin::UpdateSettings(const QJsonObject &conf)
{
    settings = CommandPluginConfig::fromJson(conf);
    return true;
}

bool CommandPlugin::Initialize(const QString &, const QJsonObject &settings)
{
    instance = this;
    this->settings.loadJson(settings);
    eventHandler = std::make_shared<SimpleEventHandler>(this);
    return true;
}

const QJsonObject CommandPlugin::GetSettngs()
{
    return settings.toJson();
}

std::shared_ptr<QvPluginEventHandler> CommandPlugin::GetEventHandler()
{
    return eventHandler;
}

std::unique_ptr<QWidget> CommandPlugin::GetSettingsWidget()
{
    return std::make_unique<CommandPluginSettings>();
}

std::unique_ptr<QvPluginEditor> CommandPlugin::GetEditorWidget(UI_TYPE)
{
    return nullptr;
}

std::shared_ptr<QvPluginSerializer> CommandPlugin::GetSerializer()
{
    return nullptr;
}
