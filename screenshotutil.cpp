#include "screenshotutil.hpp"

#include <QApplication>
#include <QClipboard>
#include <QPainter>
#include <QPixmap>
#include <QScreen>
#include <platformbackend.hpp>

QPixmap *screenshotutil::fullscreen() {
    QPixmap *noCursor = window(0);
    QScopedPointer<QPixmap> p(noCursor);
    QPixmap *withCursor = new QPixmap(noCursor->size());
    QPainter painter(withCursor);
    auto cursorData = PlatformBackend::inst().getCursor();
    painter.drawPixmap(std::get<0>(cursorData), std::get<1>(cursorData));
    return withCursor;
}

QPixmap *screenshotutil::window(long wid) {
    QScreen *w = QApplication::primaryScreen();
    QPixmap screen = w->grabWindow(wid);
    QPixmap *pm = new QPixmap(screen.size());
    screen.swap(*pm);
    return pm;
}

void screenshotutil::toClipboard(QString value) {
    QApplication::clipboard()->setText(value);
}
