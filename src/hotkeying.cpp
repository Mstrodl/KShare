#include "hotkeying.hpp"

#include <QAction>
#include <QHotkey>
#include <QMap>
#include <KGlobalAccel>
#include <settings.hpp>

QMap<QString, QAction *> hotkeys;

// func gets bound only on first set, or load
void hotkeying::hotkey(QString seqName, QKeySequence seq, std::function<void()> func) {
    QAction* action;
    printf("Seq name: %s\n", seqName.toStdString().c_str());
    if (hotkeys.contains(seqName)) {
        printf("(Already knew)\n");
        action = hotkeys[seqName];
    } else {
        printf("Building a new action\n");
        action = new QAction(nullptr);
        action->setText(seqName);
        action->setObjectName(seqName);
        action->setProperty("componentDisplayName", seqName);
        QObject::connect(action, &QAction::triggered, func);
    }
    action->setShortcut(seq);
    KGlobalAccel::self()->setDefaultShortcut(action, QList<QKeySequence>() << seq, KGlobalAccel::NoAutoloading);
    KGlobalAccel::self()->setShortcut(action, QList<QKeySequence>() << seq, KGlobalAccel::NoAutoloading);
    KGlobalAccel::setGlobalShortcut(action, seq);
}

// forces the hotkey from settings
void hotkeying::load(QString seqName, std::function<void()> func, QString def) {
    QString name = seqName;
    name.prepend("hotkey_");
    if (hotkeys.contains(seqName)) return;
    QString k = settings::settings().value(name).toString();
    if (!k.isEmpty()) {
        hotkeying::hotkey(seqName, QKeySequence(k), func);
    } else {
        hotkeying::hotkey(seqName, def.isEmpty() ? "" : def, func);
    }
}

bool hotkeying::valid(QString seq) {
    return seq.isEmpty() || !QKeySequence(seq).toString().isEmpty();
}

QString hotkeying::sequence(QString seqName) {
    return hotkeys.contains(seqName) ?
        hotkeys.value(seqName)->shortcut().toString() : "";
}
