#include <iostream>
#include "DbusNotifier.h"

void DbusNotifier::notify(const std::string &summary, const std::string &body) {
    // TODO
    DBusMessage *message;
    buildMessage(message, summary, body);
    // TODO
}

int DbusNotifier::buildMessage(DBusMessage *notifyMsg, const std::string &summary, const std::string &body) {
    DBusMessageIter args, actions, hints;
    const char *appName = "";
    int replacesId = -1;
    const char *appIcon = "dialog-information";
    int timeout = -1;

    dbus_message_iter_init_append(notifyMsg, &args);
    int returnCode = dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &appName);
    returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &replacesId);
    returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &appIcon);
    returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &summary);
    returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &body);

    returnCode |= dbus_message_iter_open_container(&args, DBUS_TYPE_ARRAY, DBUS_TYPE_STRING_AS_STRING, &actions);
    returnCode |= dbus_message_iter_close_container(&args, &actions);

    returnCode |= dbus_message_iter_open_container(&args,
                                                   DBUS_TYPE_ARRAY,
                                                   DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
                                                           DBUS_TYPE_STRING_AS_STRING
                                                           DBUS_TYPE_VARIANT_AS_STRING
                                                           DBUS_DICT_ENTRY_END_CHAR_AS_STRING,
                                                   &hints);
    returnCode |= dbus_message_iter_close_container(&args, &hints);

    returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_INT32, &timeout);

    return returnCode;
}
