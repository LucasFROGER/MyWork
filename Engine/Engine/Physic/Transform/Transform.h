#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <vector>

#include "SpaceType.h"

#include "../../Core/Maths/Vector/Vec3.h"
#include "../../Core/Maths/Vector/Vec4.h"
#include "../../Core/Maths/Matrix/Mat4.h"
#include "../../Core/Maths/Quaternion.h"

namespace engine
{
	namespace physic
	{

		class Transform
		{
		public:
			Transform();
			Transform(const Transform& copy) = default;
			Transform(Transform* parent);
			~Transform();

			static engine::core::maths::Mat4 GetLocalToWorldMatrix(Transform* subject);
			static engine::core::maths::Mat4 GetWorldToLocalMatrix(Transform* subject);
			static engine::core::maths::Quaternion GetRotation(Transform* subject, ESpace space = ESpace::WORLD);

			void Remove(Transform* child);

			void Translate(const engine::core::maths::Vec3& translation, ESpace space = ESpace::LOCAL);
			void Rotate(const engine::core::maths::Quaternion& rotation, ESpace space = ESpace::LOCAL);
			// Local space only.
			void Scale(const engine::core::maths::Vec3& scale);

			Transform* GetParent();

			engine::core::maths::Vec3 GetPosition(ESpace space = ESpace::WORLD) const;
			engine::core::maths::Quaternion GetRotation(ESpace space = ESpace::WORLD) const;
			engine::core::maths::Vec3 GetScale(ESpace space = ESpace::WORLD) const;

			const engine::core::maths::Mat4& GetLocalToWorldMatrix();
			const engine::core::maths::Mat4& GetWorldToLocalMatrix();

			// The right of the objet in the world space
			engine::core::maths::Vec3 GetRight() const;
			// The up of the objet in the world space
			engine::core::maths::Vec3 GetUp() const;
			// The forward of the objet in the world space
			engine::core::maths::Vec3 GetForward() const;

			void SetParent(Transform* parent);

			void SetPosition(const engine::core::maths::Vec3& position, ESpace space = ESpace::WORLD);
			void SetRotation(const engine::core::maths::Quaternion& rotation, ESpace space = ESpace::WORLD);
			// Local space only.
			void SetScale(const engine::core::maths::Vec3& scale);

			void SetRight(const engine::core::maths::Vec3& right);
			void SetUp(const engine::core::maths::Vec3& up);
			void SetForward(const engine::core::maths::Vec3& forward);

			Transform& operator=(const Transform& other) = default;
			Transform& operator=(Transform&& other) = default;

		private:
			Transform* m_parent;
			std::vector<Transform*> m_children;

			engine::core::maths::Vec3 m_localPosition;
			engine::core::maths::Quaternion m_localRotation;
			engine::core::maths::Vec3 m_localScale;

			engine::core::maths::Mat4 m_localToWorldMatrix;
			engine::core::maths::Mat4 m_worldToLocalMatrix;

			bool m_isLocalWorldUpToDate;
			bool m_isWorldLocalUpToDate;

			void ChangeState();
			void Update();
		};
	}
}
#endif