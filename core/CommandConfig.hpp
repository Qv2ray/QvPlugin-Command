#pragma once
#include "lib/QJsonStruct/QJsonStruct.hpp"
class CommandPluginConfig
{
  public:
    QString beforeConnection;
    QString afterConnection;
    QString beforeDisConnection;
    QString afterDisConnection;
    //
    QString connectionCreated;
    QString connectionRenamed;
    QString connectionUpdated;
    QString connectionDeleted;
    //
    QString setSystemProxy;
    QString clearSystemProxy;
    //
    JSONSTRUCT_REGISTER(CommandPluginConfig,                                                           //
                        F(beforeConnection, afterConnection, beforeDisConnection, afterDisConnection), //
                        F(connectionCreated, connectionRenamed, connectionUpdated, connectionDeleted), //
                        F(setSystemProxy, clearSystemProxy))
};
