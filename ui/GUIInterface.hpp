#pragma once

#include "interface/QvGUIPluginInterface.hpp"
#include "ui/CommandPluginSettings.hpp"

using namespace Qv2rayPlugin;

class CommandGUIInterface : public Qv2rayPlugin::PluginGUIInterface
{
  public:
    QIcon Icon() const override
    {
        return QIcon(":/assets/qv2ray.png");
    }

    QList<PluginGuiComponentType> GetComponents() const override
    {
        return { GUI_COMPONENT_SETTINGS };
    }

    std::unique_ptr<QvPluginSettingsWidget> createSettingsWidgets() const override
    {
        return std::make_unique<CommandPluginSettings>();
    }

    QList<typed_plugin_editor> createInboundEditors() const override
    {
        return {};
    }

    QList<typed_plugin_editor> createOutboundEditors() const override
    {
        return {};
    }

    std::unique_ptr<QvPluginMainWindowWidget> createMainWindowWidget() const override
    {
        return nullptr;
    }
};
