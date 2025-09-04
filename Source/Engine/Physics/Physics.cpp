#include "Physics.h"

namespace viper {
	float Physics::ms_pixlesPerUnit = 48.0f;

	bool Physics::Initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
		m_worldId = b2CreateWorld(&worldDef);

		return true;
	}
	void Physics::Shutdown() {
		b2DestroyWorld(m_worldId);
	}
	void Physics::Update(float dt) {
		b2World_Step(m_worldId, 1.0f / 60.0f, 4);
		ProcessCollisionEvent();
	}
	void Physics::ProcessCollisionEvent() {
		b2ContactEvents contactEvents = b2World_GetContactEvents(m_worldId);

		// begin contact
		for (int i = 0; i < contactEvents.beginCount; ++i) {
			b2ContactBeginTouchEvent* contactEvent = contactEvents.beginEvents + i;

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) continue;

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}

		// end contact
		for (int i = 0; i < contactEvents.endCount; ++i) {
			b2ContactEndTouchEvent* contactEvent = contactEvents.endEvents + i;

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) continue;

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}
		/*
		// sensor contact
		b2SensorEvents sensorEvents = b2World_GetSensorEvents(m_worldId);
		for (int i = 0; i < sensorEvents.beginCount; ++i) {
			b2SensorBeginTouchEvent* contactEvent = sensorEvents.beginEvents + i;

			b2BodyId bodyA = b2Shape_GetBody(sensorEvents->sensorShapeId);
			b2BodyId bodyB = b2Shape_GetBody(sensorEvents->sensorShapeId);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) continue;

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}
		*/
	}
}