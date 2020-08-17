#ifndef IMAGEPROVIDER2_H
#define IMAGEPROVIDER2_H
#include <QQuickImageProvider>
#include <QObject>
#include <QImage>
#include <QPixmap>

class ImageProvider2 : public QQuickImageProvider
{
public:
    ImageProvider2();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
    QImage img;
};

#endif // IMAGEPROVIDER2_H
