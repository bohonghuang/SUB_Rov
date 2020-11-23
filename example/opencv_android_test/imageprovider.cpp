#include "imageprovider.h"

ImageProvider::ImageProvider(): QQuickImageProvider (QQuickImageProvider::Pixmap)
{

}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 1280;
    int height = 720;

    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    return QPixmap::fromImage(img);
}
