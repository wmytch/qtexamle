#include "qwbattery.h"
#include "qwbatteryplugin.h"

#include <QtPlugin>

QwBatteryPlugin::QwBatteryPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QwBatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QwBatteryPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QwBatteryPlugin::createWidget(QWidget *parent)
{
    return new QwBattery(parent);
}

QString QwBatteryPlugin::name() const
{
    return QLatin1String("QwBattery");
}

QString QwBatteryPlugin::group() const
{
    return QLatin1String("My Widget");
}

QIcon QwBatteryPlugin::icon() const
{
    return QIcon();
}

QString QwBatteryPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QwBatteryPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QwBatteryPlugin::isContainer() const
{
    return false;
}

QString QwBatteryPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QwBattery\" name=\"qwBattery\">\n</widget>\n");
}

QString QwBatteryPlugin::includeFile() const
{
    return QLatin1String("qwbattery.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qwbatteryplugin, QwBatteryPlugin)
#endif // QT_VERSION < 0x050000
