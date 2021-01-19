#include "ImageProvider2.h"
#include "../RovApplication.h"

ImageProvider2::ImageProvider2(): QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}
QPixmap ImageProvider2::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = rovApp()->getToolbox()->getSettingsManager()->getThermalWidth();
    int height = width * 9 / 16;

    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width   ,
                   requestedSize.width() > 0 ? requestedSize.height() : height );

    return QPixmap::fromImage(img);
}

QImage ImageProvider2::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return img;
}
