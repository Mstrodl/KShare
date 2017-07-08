#include "pathitem.hpp"

#include <settings.hpp>

PathItem::PathItem() {
}

PathItem::~PathItem() {
    delete path;
}

void PathItem::mouseDragEvent(QGraphicsSceneMouseEvent *, CropScene *scene) {
    if (path == nullptr) {
        path = new QPainterPath(scene->cursorPosition());
        pathItem = scene->addPath(*path, scene->pen(),
                                  settings::settings().value("brushPath", false).toBool() ? scene->brush() : QBrush());
    } else {
        path->quadTo(path->currentPosition(), scene->cursorPosition());
        pathItem->setPath(*path);
    }
}

void PathItem::mouseDragEndEvent(QGraphicsSceneMouseEvent *, CropScene *) {
}
