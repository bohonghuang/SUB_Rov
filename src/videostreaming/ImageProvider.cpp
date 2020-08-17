#include "ImageProvider.h"
#include "../RovApplication.h"
#include "../Settings/SettingsManager.h"
#include <RovToolbox.h>

ImageProvider::ImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = rovApp()->getToolbox()->getSettingsManager()->getWinWidth();
    int height = width * 9 / 16;

    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width   ,
                   requestedSize.width() > 0 ? requestedSize.height() : height );

    return QPixmap::fromImage(img);
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return img;
}
