/// ��¥ / �̸� / ��������
/// 2025-07-02 �ǿ�� ���ʹ��� �ۼ�
/// 2025-07-09 �ǿ�� MonoBehaviour ���� �ٷ� �����Ҽ� �ֵ��� GetOwner() �Լ� �߰� this�� �����ϰ� �غ����� �ߴµ� ��� ��ȯ ���� �߻�����

#pragma once


/// <summary>
/// ������Ʈ Ŭ����
/// </summary>
class Component {
public:
	friend class GameObject;

	Component() = default;
    virtual ~Component() = default;

    GameObject* GetOwner() const { return m_owner; }

protected:
    void SetOwner(GameObject* owner) { m_owner = owner; }

private:
    GameObject* m_owner = nullptr;
};
