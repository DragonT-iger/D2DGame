#pragma once

class YSort : public MonoBehaviour
{
public:
    YSort() = default;
    YSort(int offset) { m_offset = offset; }
    virtual ~YSort() = default;

    void SetStatic(bool isStatic) { m_isStatic = isStatic; }

    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;

    void SetOffset(int offset) { m_offset = offset; }

private:
    void Apply();

    SpriteRenderer* m_sprite = nullptr;
    Transform* m_transform = nullptr;
    bool m_isStatic = true;

    int m_offset = 0;
};