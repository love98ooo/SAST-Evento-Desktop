#include "latest_evento_model.h"

int LatestEventoModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant LatestEventoModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.title;
    case Role::Time:
        return element.time;
    case Role::Description:
        return element.description;
    case Role::Department:
        return element.department;
    case Role::Url:
        return element.image;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> LatestEventoModel::roleNames() const {
    static QHash<int, QByteArray> roles;

    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Time, "time");
        roles.insert(Description, "description");
        roles.insert(Department, "department");
        roles.insert(Url, "url");
    }
    return roles;
}

void LatestEventoModel::resetModel(std::vector<LatestEvento>&& model) {
    QMetaObject::invokeMethod(
        this,
        [&]() {
            beginResetModel();
            m_data = std::move(model);
            endResetModel();
        },
        Qt::BlockingQueuedConnection);
}

LatestEventoModel* LatestEventoModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

LatestEventoModel* LatestEventoModel::getInstance() {
    static LatestEventoModel singleton;
    return &singleton;
}
