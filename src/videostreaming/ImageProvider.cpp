#include "ImageProvider.h"
#include "../RovApplication.h"
#include "../Settings/SettingsManager.h"


ImageProvider::ImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = rovApp()->getToolbox()->getSettingsManager()->getWinWidth();
    int height = width * 9 / 16;

    if( size ){
        *size = QSize(width, height);
    }

    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width   ,
                   requestedSize.width() > 0 ? requestedSize.height() : height );

    //pixmap.fill(QColor(id).rgba());
    return QPixmap::fromImage(img);
}
