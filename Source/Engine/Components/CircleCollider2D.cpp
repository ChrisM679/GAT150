#include "CircleCollider2D.h"

namespace viper {

    void CircleCollider2D::Update(float dt) {
        //
    }

    bool CircleCollider2D::CheckCollision(ColliderComponent& other) {
        float distance = (owner->m_transform.position - other.owner->m_transform.position).Length();
        auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);
        if (circleCollider) {
            float radii = radius + circleCollider->radius;
            if (distance <= radii) {
                return true;
            }
        }
        return false;
    }

}

