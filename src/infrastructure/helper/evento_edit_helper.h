#ifndef EVENTOEDITHELPER_H
#define EVENTOEDITHELPER_H

#include <QtQml>
#include "dto/evento.h"

class EventoEditHelper : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(EventoEditHelper)
    QML_SINGLETON

    Q_PROPERTY(QString departmentJson MEMBER m_departmentJson NOTIFY departmentJsonChanged)
    Q_PROPERTY(QString locationJson MEMBER m_locationJson NOTIFY locationJsonChanged)
    Q_PROPERTY(QString typeJson MEMBER m_typeJson NOTIFY typeJsonChanged)
    Q_PROPERTY(int typeId MEMBER m_typeId NOTIFY typeIdChanged)
    Q_PROPERTY(bool allowConflict MEMBER m_allowConflict NOTIFY allowConflictChanged)
    Q_PROPERTY(bool isEdited MEMBER m_isEdited NOTIFY isEditedChanged)
    Q_PROPERTY(QString eventStart MEMBER m_eventStart NOTIFY eventStartChanged)
    Q_PROPERTY(QString eventEnd MEMBER m_eventEnd NOTIFY eventEndChanged)
    Q_PROPERTY(QString registerStart MEMBER m_registerStart NOTIFY registerStartChanged)
    Q_PROPERTY(QString registerEnd MEMBER m_registerEnd NOTIFY registerEndChanged)

public:
    static EventoEditHelper *getInstance();

    static EventoEditHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateEventoEdit(const QString &departmentJson, const QString &m_locationJson,
                          const QString &m_typeJson, const DTO_Evento &evento = DTO_Evento());

private:
    EventoEditHelper() = default;

    QString m_departmentJson;
    QString m_locationJson;
    QString m_typeJson;
    bool m_isEdited; // true: 编辑模式 false: 创建模式
    // 编辑模式属性
    int m_typeId;
    bool m_allowConflict;
    QString m_eventStart;
    QString m_eventEnd;
    QString m_registerStart;
    QString m_registerEnd;

signals:
    void departmentJsonChanged();
    void locationJsonChanged();
    void typeJsonChanged();
    void typeIdChanged();
    void allowConflictChanged();
    void isEditedChanged();
    void eventStartChanged();
    void eventEndChanged();
    void registerStartChanged();
    void registerEndChanged();
};

#endif // EVENTOEDITHELPER_H
