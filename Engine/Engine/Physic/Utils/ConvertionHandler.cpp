#include "ConvertionHandler.h"

physx::PxVec2 engine::physic::ConvertionHandler::EngineToPhysx(engine::core::maths::Vec2 vec)
{
	return physx::PxVec2(vec.m_x, vec.m_y);
}

physx::PxVec3 engine::physic::ConvertionHandler::EngineToPhysx(engine::core::maths::Vec3 vec)
{
	physx::PxVec3 vec3;
	vec3.x = vec.m_x;
	vec3.y = vec.m_y;
	vec3.z = vec.m_z;

	return vec3;
}

physx::PxVec4 engine::physic::ConvertionHandler::EngineToPhysx(engine::core::maths::Vec4 vec)
{
	return physx::PxVec4(vec.m_x, vec.m_y, vec.m_z, vec.m_w);
}

physx::PxMat44 engine::physic::ConvertionHandler::EngineToPhysx(engine::core::maths::Mat4 mat)
{
	physx::PxMat44 matrix;
	for(int i { 0 }; i < 4; i++)
		for (int j{ 0 }; j < 4; j++)
		{
			matrix[i][j] = mat.m_matrix[j][i];
		}
	return matrix;
}

physx::PxQuat engine::physic::ConvertionHandler::EngineToPhysx(engine::core::maths::Quaternion quat)
{
	return physx::PxQuat(quat.m_x, quat.m_y, quat.m_z, quat.m_w);
}

physx::PxTransform engine::physic::ConvertionHandler::EngineToPhysx(engine::physic::Transform trans)
{
	physx::PxTransform transform;
	transform.p = EngineToPhysx(trans.GetPosition(engine::physic::ESpace::WORLD));
	transform.q = EngineToPhysx(trans.GetRotation(engine::physic::ESpace::WORLD));
	return transform;
}



engine::core::maths::Vec2 engine::physic::ConvertionHandler::PhysxToEngine(physx::PxVec2  vec)
{
	return engine::core::maths::Vec2(vec.x, vec.y);
}

engine::core::maths::Vec3 engine::physic::ConvertionHandler::PhysxToEngine(physx::PxVec3 vec)
{
	return engine::core::maths::Vec3(vec.x, vec.y, vec.z);
}

engine::core::maths::Vec4 engine::physic::ConvertionHandler::PhysxToEngine(physx::PxVec4 vec)
{
	return engine::core::maths::Vec4(vec.x, vec.y, vec.z, vec.w);
}

engine::core::maths::Mat4 engine::physic::ConvertionHandler::PhysxToEngine(physx::PxMat44 mat)
{
	engine::core::maths::Mat4 matrix;
	for (int i{ 0 }; i < 4; i++)
		for (int j{ 0 }; j < 4; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	return matrix;
}

engine::core::maths::Quaternion engine::physic::ConvertionHandler::PhysxToEngine(physx::PxQuat quat)
{
	return engine::core::maths::Quaternion(quat.w, quat.x, quat.y, quat.z);
}

engine::physic::Transform engine::physic::ConvertionHandler::PhysxToEngine(physx::PxTransform trans)
{
	engine::physic::Transform transform;
	transform.SetPosition(PhysxToEngine(trans.p), engine::physic::ESpace::WORLD);
	transform.SetRotation(PhysxToEngine(trans.q), engine::physic::ESpace::WORLD);
	return transform;
}
