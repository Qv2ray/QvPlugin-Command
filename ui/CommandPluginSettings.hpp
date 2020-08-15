#pragma once
#include "core/CommandConfig.hpp"
#include "interface/QvGUIPluginInterface.hpp"

#include <QWidget>

namespace Ui
{
    class CommandPluginSettings;
}

class CommandPluginSettings : public Qv2rayPlugin::QvPluginSettingsWidget
{
    Q_OBJECT
  public:
    explicit CommandPluginSettings(QWidget *parent = nullptr);
    ~CommandPluginSettings();

    void SetSettings(const QJsonObject &settings) override
    {
        this->settings.loadJson(settings);
    }

    QJsonObject GetSettings() override
    {
        return settings.toJson();
    }

  private slots:
    void on_preConnTxt_textChanged();
    void on_postConnTxt_textChanged();
    void on_preDisconnTxt_textChanged();
    void on_postDisconnTxt_textChanged();
    void on_connCreateTxt_textChanged();
    void on_connRenameTxt_textChanged();
    void on_connUpdateTxt_textChanged();
    void on_connDeleteTxt_textChanged();
    void on_setSystemProxyTxt_textChanged();
    void on_clearSystemProxyTxt_textChanged();

  private:
    CommandPluginConfig settings;
    Ui::CommandPluginSettings *ui;
};
