#include "CommandPluginSettings.hpp"

#include "CommandPlugin.hpp"
#include "ui_CommandPluginSettings.h"

CommandPluginSettings::CommandPluginSettings(QWidget *parent) : Qv2rayPlugin::QvPluginSettingsWidget(parent), ui(new Ui::CommandPluginSettings)
{
    ui->setupUi(this);
    ui->preConnTxt->setPlainText(settings.beforeConnection);
    ui->postConnTxt->setPlainText(settings.afterConnection);
    ui->preDisconnTxt->setPlainText(settings.beforeDisConnection);
    ui->postDisconnTxt->setPlainText(settings.afterDisConnection);
    //
    ui->connCreateTxt->setPlainText(settings.connectionCreated);
    ui->connRenameTxt->setPlainText(settings.connectionRenamed);
    ui->connUpdateTxt->setPlainText(settings.connectionUpdated);
    ui->connDeleteTxt->setPlainText(settings.connectionDeleted);
    //
    ui->setSystemProxyTxt->setPlainText(settings.setSystemProxy);
    ui->clearSystemProxyTxt->setPlainText(settings.clearSystemProxy);
}

CommandPluginSettings::~CommandPluginSettings()
{
    delete ui;
}

void CommandPluginSettings::on_preConnTxt_textChanged()
{
    settings.beforeConnection = ui->preConnTxt->toPlainText();
}

void CommandPluginSettings::on_postConnTxt_textChanged()
{
    settings.afterConnection = ui->postConnTxt->toPlainText();
}

void CommandPluginSettings::on_preDisconnTxt_textChanged()
{
    settings.beforeDisConnection = ui->preDisconnTxt->toPlainText();
}

void CommandPluginSettings::on_postDisconnTxt_textChanged()
{
    settings.afterDisConnection = ui->postDisconnTxt->toPlainText();
}

void CommandPluginSettings::on_connCreateTxt_textChanged()
{
    settings.connectionCreated = ui->connCreateTxt->toPlainText();
}

void CommandPluginSettings::on_connRenameTxt_textChanged()
{
    settings.connectionRenamed = ui->connRenameTxt->toPlainText();
}

void CommandPluginSettings::on_connUpdateTxt_textChanged()
{
    settings.connectionUpdated = ui->connUpdateTxt->toPlainText();
}

void CommandPluginSettings::on_connDeleteTxt_textChanged()
{
    settings.connectionDeleted = ui->connDeleteTxt->toPlainText();
}

void CommandPluginSettings::on_setSystemProxyTxt_textChanged()
{
    settings.setSystemProxy = ui->setSystemProxyTxt->toPlainText();
}

void CommandPluginSettings::on_clearSystemProxyTxt_textChanged()
{
    settings.clearSystemProxy = ui->clearSystemProxyTxt->toPlainText();
}
