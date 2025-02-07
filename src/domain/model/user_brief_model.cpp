#include "user_brief_model.h"

int UserBriefModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant UserBriefModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::UserId:
        return element.userId;
    case Role::EMail:
        return element.email;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> UserBriefModel::roleNames() const {
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(UserId, "userId");
        roles.insert(EMail, "email");
    }
    return roles;
}

void UserBriefModel::resetModel(std::vector<UserBrief>&& model) {
    QMetaObject::invokeMethod(
        this,
        [&]() {
            beginResetModel();
            m_data = std::move(model);
            endResetModel();
        },
        Qt::BlockingQueuedConnection);
}

UserBriefModel* UserBriefModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

UserBriefModel* UserBriefModel::getInstance() {
    static UserBriefModel singleton;
    return &singleton;
}
