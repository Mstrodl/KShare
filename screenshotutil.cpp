#include "screenshotutil.hpp"
#include "screengrabber.hpp"

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QProcessEnvironment>
#include <QScreen>
#include <platformbackend.hpp>

QPixmap screenshotutil::fullscreen(bool cursor) {
    auto e = QProcessEnvironment::systemEnvironment();
    auto XDG_SESSION_TYPE = e.value(QStringLiteral("XDG_SESSION_TYPE"));
    auto WAYLAND_DISPLAY = e.value(QStringLiteral("WAYLAND_DISPLAY"));
    QPixmap image;
    if (XDG_SESSION_TYPE == QLatin1String("wayland") ||
        WAYLAND_DISPLAY.contains(QLatin1String("wayland"), Qt::CaseInsensitive)) {
      ScreenGrabber grabber(nullptr);
      bool ok;
      grabber.freeDesktopPortal(ok, image);
      return image;
    }

    QPainter painter;

    // Hack for https://bugreports.qt.io/browse/QTBUG-58110
    static QStringList qVer = QString(qVersion()).split('.');
#ifdef Q_OS_LINUX
    if (qVer.at(0).toInt() == 5 && qVer.at(1).toInt() < 9) {
        image = window(0);
        painter.begin(&image);
    } else {
#endif
        int height = 0, width = 0;
        for (QScreen *screen : QApplication::screens()) {
            QRect geo = screen->geometry();
            width = qMax(geo.left() + geo.width(), width);
            height = qMax(geo.top() + geo.height(), height);
        }
        image = QPixmap(width, height);
        image.fill(Qt::transparent);
        width = 0;
        painter.begin(&image);

        for (QScreen *screen : QApplication::screens()) {
            QPixmap currentScreen = window(0, screen);
            painter.drawPixmap(screen->geometry().topLeft(), currentScreen);
            width += screen->size().width();
        }
#ifdef Q_OS_LINUX
    }
#endif

#ifdef PLATFORM_CAPABILITY_CURSOR
    if (cursor) {
        auto cursorData = PlatformBackend::inst().getCursor();
        painter.drawPixmap(QCursor::pos() - std::get<0>(cursorData), std::get<1>(cursorData));
    }
#endif
    painter.end();
    return image;
}

QPixmap screenshotutil::window(WId wid, QScreen *w) {
    return w->grabWindow(wid);
}

void screenshotutil::toClipboard(QString value) {
    QApplication::clipboard()->setText(value);
}

QPixmap screenshotutil::fullscreenArea(bool cursor, qreal x, qreal y, qreal w, qreal h) {
    return fullscreen(cursor).copy(x, y, w, h);
}
